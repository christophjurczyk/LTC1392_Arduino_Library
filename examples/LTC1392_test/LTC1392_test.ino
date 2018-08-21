/* --------------------------------------------------------------
  Example sketch to read data from the LTC1392
  Schematic (see datasheet page 1):
  Arduino   LTC1392     Arduino            
          ------------
    4     |Din    VCC|    5V
    4     |Dout  -VIN|    R_sense (ground side)
    3     |CLK   +VIN|    5V (R_sense (supply side))
    2     |CS     GND|    GND
          ------------
  
  Author: Christoph Jurczyk
 -------------------------------------------------------------- */

#include "LTC1392.h"

// Pins
#define LTC_CS 2
#define LTC_SCK 3
#define LTC_DATA 4


// LTC init
LTC1392 ltc(LTC_CS, LTC_SCK, LTC_DATA);


void setup() {
  Serial.begin(115200);

  // definition of shunt value
  ltc.set_shunt(1.0); // value in ohms
}


void loop() {
  // read data
  float temperature = ltc.get_temperature();
  float voltage = ltc.get_supply_voltage();
  float dif_voltage = ltc.get_differential_voltage(false);
  float current = ltc.get_current(false);

  // print data
  Serial.print("Temperature: ");
  Serial.print(temperature);
  Serial.print(" degC\tSupply Voltage: ");
  Serial.print(voltage);
  Serial.print(" V\tDifferential Voltage: ");
  Serial.print(dif_voltage * 1000);
  Serial.print(" mV\tCurrent: ");
  Serial.print(current*1000);
  Serial.print(" mA ");
  Serial.println("");

  delay(1000);
}
