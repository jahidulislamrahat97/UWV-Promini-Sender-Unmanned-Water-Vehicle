#include <Arduino.h>
#include <printf.h>
#include "Config.h"
#include "NRF.h"
#include "UWV.h"

UWV uwv;
RF24 radio(CE_PIN, CSN_PIN);
NRF_Config nrf_config;

void setup()
{
  Serial.begin(9600);
  printf_begin();

  uwv.init();

  nrf_config.open_writing_pipe = true;
  nrf_config.open_reading_pipe = false;
  nrf_config.enableAckPayload = false;
  nrf_config.nrf_master_role = true;

  vMakeAddress(nrf_config, 0, NRF_ID);
  vShowAddress(nrf_config.nRF_Address[nrf_config.pipes[0]], ADDRESS_SIZE);
  vNRF_Config(radio, nrf_config, DEBUG);
  vPrintDebugMessage(radio);

}

void loop()
{
  // uwv.readSpeed();
  // uwv.readRudder();

  uwv.readArmState();

  delay(150);
}