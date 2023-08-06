#include "NRF.h"

void vNRF_Config(RF24 &radio, NRF_Config &config, bool debug)
{

    if (!radio.begin())
    {
        if (debug)
        {
            Serial.println(F("Radio hardware not responding"));
        }
        while (1);
    }

    radio.setPALevel(config.power_level);
    radio.setDataRate(config.data_rate);
    radio.setRetries(config.retry_delay, config.max_retry);

    // enable ack payload for sending & receiving ack payload.
    if (config.enableAckPayload)
    {
        radio.enableDynamicPayloads();
        radio.enableAckPayload();
    }

    // master (sender) config.
    if (config.nrf_master_role)
    {
        if (config.open_writing_pipe)
        {
            radio.openWritingPipe(config.nRF_Address[0]);
        }
        radio.stopListening();
    }

    // slave (receiver) config.
    else
    {
        // set reading pipe for data reading from master.
        if (config.open_reading_pipe)
        { // config all reading pipes
            for (uint8_t i = 0; i < config.number_of_pipes; i++)
            {
                radio.openReadingPipe(config.pipes[i], config.nRF_Address[config.pipes[i]]);
                // Serial.print(config.pipes[i]);
                // Serial.println(config.nRF_Address[config.pipes[i]]);
            }
        }

        if (config.enableAckPayload)
        {
            memcpy(config.ackPayload, DEFAULT_ACK_PAYLOAD, PACKET_SIZE);
            radio.writeAckPayload(1, &config.ackPayload, sizeof(config.ackPayload));
        }

        radio.startListening();
    }
}

bool bNRF_Send(RF24 &radio, NRF_Config &config, char *data_to_send, bool debug)
{
    if (debug)
    {
        Serial.print(F("Sending: "));
        Serial.println(data_to_send);
    }
    radio.stopListening();
    bool result = radio.write(data_to_send, strlen(data_to_send));

    if (result)
    {
        if (config.enableAckPayload)
        {
            if (radio.isAckPayloadAvailable())
            {
                radio.read(&config.ackPayload, sizeof(config.ackPayload));
                Serial.print(F("Ack Payload From Slave:"));
                Serial.println(config.ackPayload);
            }
            else
            {
                Serial.println(F("Acknowledge but no data"));
            }
        }
        if (debug)
        {
            Serial.println(F("Data sent successfully"));
        }
    }
    else
    {
        if (debug)
        {
            Serial.println(F("Data sending failed"));
        }
    }

    return result;
}

bool bNRF_Send_Int(RF24 &radio, NRF_Config &config, int data, bool debug)
{
    if (debug)
    {
        Serial.print(F("Sending: "));
        Serial.println(data);
    }
    radio.stopListening();
    bool result = radio.write(&data, sizeof(int));

    if (result)
    {
        if (config.enableAckPayload)
        {
            if (radio.isAckPayloadAvailable())
            {
                radio.read(&config.ackPayload, sizeof(config.ackPayload));
                Serial.print(F("Ack Payload From Slave:"));
                Serial.println(config.ackPayload);
            }
            else
            {
                Serial.println(F("Acknowledge but no data"));
            }
        }
        if (debug)
        {
            Serial.println(F("Data sent successfully"));
        }
    }
    else
    {
        if (debug)
        {
            Serial.println(F("Data sending failed"));
        }
    }
    

    return result;
}

bool bNRF_Rreceive(RF24 &radio, char *data_to_receive, bool debug)
{

    if (radio.available())
    {
        radio.read(data_to_receive, PACKET_SIZE);
        if (debug)
        {
            Serial.print(F("data_to_receive: "));
            Serial.println(data_to_receive);
        }
        return true;
    }
    return false;
}

/*
Warning: need to update this function.
*/
// radio.writeAckPayload(nrf_config.pipes[0], &data_to_receive, sizeof(data_to_receive));
void vMakeAckPayload(RF24 &radio, uint8_t pipe, char *payload)
{
    radio.writeAckPayload(pipe, &payload, sizeof(payload));
}

void vPrintDebugMessage(RF24 &radio)
{
    Serial.println();
    Serial.println();
    radio.printDetails();
    Serial.println();
    Serial.println();
}

void vMakeAddress(NRF_Config &config, int index, char *addr)
{
    uint32_t ul_addr = strtoul(addr, NULL, 10);
    for (int i = 0; i < ADDRESS_SIZE; i++)
    {
        config.nRF_Address[index][ADDRESS_SIZE - i - 1] = (uint8_t)((ul_addr >> i * 8) & 0xFF);
    }
}

void vShowAddress(byte *addr, int size)
{
    Serial.print(F("0x"));
    for (int i = size - 1; i >= 0; i--)
    {
        Serial.print(addr[i], HEX);
    }
    Serial.println();
}
