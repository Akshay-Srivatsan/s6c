#include <Arduino.h>
#include "RH_RF24.h"

//#define MAX_MSG_LENGTH 23
//#define NPAR 20
//#define FRAME_SIZE ( MAX_MSG_LENGTH + NPAR )

#include "ecc.h"

// see https://github.com/arduino/ArduinoCore-samd/blob/master/variants/arduino_zero/variant.cpp

#define GFSK_SDN 13
#define GFSK_IRQ 12
#define GFSK_GATE 5
#define GFSK_GPIO_0 7
#define GFSK_GPIO_1 8
#define GFSK_GPIO_2 20
#define GFSK_GPIO_3 21
#define GFSK_CS 38
#define GFSK_SCK 5
#define GFSK_MOSI 4
#define GFSK_MISO 18

#define RF_FREQ 433.5

#define LED_PIN 27

#define PRINT_TIMING
#define PRINT_ENCODED_DATA
#define PRINT_RSSI

#define PIN_ARM1 18 //SER01 - PA05 - 18
#define PIN_ARM2 9 //SER03 - PA07 - 9
#define PIN_ARM3 1 //SER22 - PA10 - 1
#define PIN_ARM4 0 //SER23 - PA11 - 0
/*
S6B GFSK Library
This library provides an abstraction for the S6B hardware developed by SSI.
*/

class S6C
{
public:
  S6C();
  void configureRF();
  void encode_and_transmit(void *msg_data, uint8_t msg_size);
  uint8_t tryToRX(void *msg_data, uint8_t msg_size);
  uint8_t getRSSI();
  String getSyndrome();
  RH_RF24 *rf24;    //the RadioHead Driver Object
  void configureLED();
  void LEDOn(bool = false);
  void LEDOff(bool = false);
  void blinkStatus(int blinks);

private:
  void RadioOff();
  void RadioOn();
  void configurePins();
  uint8_t lastRssi; //RSSI of last reception
  String errorSyndrome;
};
