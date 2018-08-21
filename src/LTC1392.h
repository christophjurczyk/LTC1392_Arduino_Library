/* --------------------------------------------------------------
	Arduino Library for the Linear Technology LTC1392

	Author: Christoph Jurczyk
	Version: 1.0
	Changelog:
		1.0		21.08.2018:		Initial Upload

  -------------------------------------------------------------- */

#ifndef LTC1392_H
#define LTC1392_H

#include "Arduino.h"

class LTC1392
{
  public:
    // initialization
    LTC1392(int cs_pin, int sck_pin, int data_pin);

    // funtion to get temperature
    // return in degC
    float get_temperature(void);

    // function to get supply voltage
    // return in V
    float get_supply_voltage(void);

    // function to get differential voltage
    // scale_mode: true=0.5V  false=1V
    // return in V
    float get_differential_voltage(bool scale_mode);

    // funtion to set shunt value
    // value in Ohm
    void set_shunt(float value);

    // function to get current
    // first set r_sense
    // scale_mode: true=0.5V  false=1V
    // return in A
    float get_current(bool scale_mode);

  private:
    int _cs_pin;
    int _sck_pin;
    int _data_pin;
    float _r_sense;
    uint16_t select_read_msb(uint8_t mode);
    void clock_cycle(void);
};

#endif
