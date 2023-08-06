#ifndef NRF_H
#define NRF_H

#include <RF24.h>
#include <nRF24L01.h>
// #include<printf.h>
// #include "Config.h"

#define CE_PIN 5
#define CSN_PIN 10

#define PACKET_SIZE 32
#define ADDRESS_SIZE 5
#define MAX_RETRY 15
#define RETRY_DELAY 5
#define MAX_PIPES 6

#define DEFAULT_ACK_PAYLOAD "Dynamic Ack Payloads Ok"

/*
b: bool return type
v: void return type
uc: uint8_t return type
us: uint16_t return type
ul: uint32_t return type
ull: uint64_t return type
*/

typedef struct NRF_Config
{
    rf24_datarate_e data_rate = RF24_250KBPS;
    rf24_pa_dbm_e power_level = RF24_PA_MAX;
    int max_retry = MAX_RETRY;
    int retry_delay = RETRY_DELAY;
    char ackPayload[PACKET_SIZE];
    bool open_writing_pipe = true;
    bool open_reading_pipe = true;
    bool enableAckPayload = false;
    uint8_t pipes[MAX_PIPES] = {1};
    uint8_t number_of_pipes = 1;
    uint8_t nRF_Address[MAX_PIPES][ADDRESS_SIZE]; // Tx, Rx
    
    bool nrf_master_role = true;                 // true: master(sender), false: slave(receiver).

} NRF_Config;

/**@brief
 * Config nrf device as master or slave.
 * nrf_master_role = false;
 * true: master(sender), false: slave(receiver).
 */
void vNRF_Config(RF24 &radio, NRF_Config &config, bool debug);
/**@brief
 * Send data for master only.
 */
bool bNRF_Send(RF24 &radio, NRF_Config &config, char *data_to_send, bool debug);
/**@brief
 * Send data for master only.
 */
bool bNRF_Send_Int(RF24 &radio, NRF_Config &config, int data, bool debug);

/**@brief
 * Receive data for slave only.
 */
bool bNRF_Rreceive(RF24 &radio, char *data_to_receive, bool debug);
/**@brief
 * Load dynamic payload(sensor data) for sending ack to master.
 */
void vMakeAckPayload(RF24 &radio, uint8_t pipe, char *payload);
/**@brief
 * Print NRF debug message
 */
void vPrintDebugMessage(RF24 &radio);
/**@brief
 * Make 5 byte address from string of integer
 * Mainly used to convert device ID to NRF address
 */
void vMakeAddress(NRF_Config &config, int index, char *addr);
/**@brief
 * Shows the converted address to serial monitor
 */
void vShowAddress(byte *addr, int size);

#endif // !NRF_H