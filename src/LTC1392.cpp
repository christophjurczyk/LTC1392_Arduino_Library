/* --------------------------------------------------------------
	Arduino Library for the Linear Technology LTC1392

	Author: Christoph Jurczyk
  -------------------------------------------------------------- */

#include "Arduino.h"
#include "LTC1392.h"
#include <SPI.h>

// initialization
LTC1392::LTC1392(int cs_pin, int sck_pin, int data_pin)
{
  // init chip select pin
  pinMode(cs_pin, OUTPUT);
  digitalWrite(cs_pin, HIGH);
  pinMode(sck_pin, OUTPUT);
  _cs_pin = cs_pin;
  _sck_pin = sck_pin;
  _data_pin = data_pin;
}

// function to read temperature
float LTC1392::get_temperature(void) {
  float data = select_read_msb(0); // read data from LTC1392
  return  data / 4 - 130; // return value in degC
}

// function to read supply voltage
float LTC1392::get_supply_voltage(void) {
  float data = select_read_msb(1); // read data from LTC1392
  return data * 4.84 / 1024 + 2.42; // return value in V
}

// function to read differential voltage
float LTC1392::get_differential_voltage(bool scale_mode) {
  float data = select_read_msb(2 + scale_mode); // read data from LTC1392
  if (scale_mode) {
    // 0.5V mode
    return 0.5 * data / 1024; // return value in V
  } else {
    // 1V mode
    return data / 1024; // return value in V
  }
}

// function to read current (returns value in A with shunt value r_sense)
float LTC1392::get_current(bool scale_mode) {
  float data = select_read_msb(2 + scale_mode); // read data from LTC1392
  if (scale_mode) {
    // 0.5V mode
    return 0.5 * data / (1024 * _r_sense); // return value in A
  } else {
    // 1V mode
    return data / (1024 * _r_sense); // return value in A
  }
}

// function to set shunt value
void LTC1392::set_shunt(float value) {
  _r_sense = value;
}

// private function to generate clock cylce
void LTC1392::clock_cycle(void) {
  digitalWrite(_sck_pin, HIGH);
  digitalWrite(_sck_pin, LOW);
}

// private funtion to start transmission and to select mode (MSB-first mode only)
uint16_t LTC1392::select_read_msb(uint8_t mode) {
  // writing
  pinMode(_data_pin, OUTPUT);
  digitalWrite(_sck_pin, LOW); // select chip
  digitalWrite(_cs_pin, LOW);
  // start transmission
  digitalWrite(_data_pin, LOW); // wakeup
  clock_cycle();
  digitalWrite(_data_pin, HIGH); // start bit
  clock_cycle();
  digitalWrite(_data_pin, bitRead(mode, 1)); // select 1
  clock_cycle();
  digitalWrite(_data_pin, bitRead(mode, 0)); // select 0
  clock_cycle();
  digitalWrite(_data_pin, HIGH); // msb first mode
  clock_cycle();

  // reading
  uint16_t input_data = 0;
  digitalWrite(_sck_pin, HIGH);
  pinMode(_data_pin, INPUT);
  digitalWrite(_sck_pin, LOW);
  for (int i = 9; i >= 0; i--) {
    digitalWrite(_sck_pin, HIGH);
    bitWrite(input_data, i, digitalRead(_data_pin));
    digitalWrite(_sck_pin, LOW);
  }
  digitalWrite(_cs_pin, HIGH); // deselect chip
  return input_data;
}
