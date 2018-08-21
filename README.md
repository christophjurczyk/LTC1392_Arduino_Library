# LTC1392_Arduino_Library
A simple Arduino Library for the Linear Technology LTC1392 Micropower Temperature, Power Supply and Differential Voltage Monitor.

## Usage
To use the library include the header-file and initialize an object as follows:
```c
#include "LTC1392.h"
...
// LTC init
LTC1392 ltc(LTC_CS, LTC_SCK, LTC_DATA);
```
The pins CS, SCK and DATA have to be digital in-/outputs pins.

To read the in-chip temperature and supply voltage, call the following functions:
```c
float temperature = ltc.get_temperature(); // in degC
float voltage = ltc.get_supply_voltage(); // in V
```

To read the differential voltage between +Vin and -Vin, call the following function:
```c
float dif_voltage = ltc.get_differential_voltage(false); // in V
```
You can choose between two measurement ranges: `false` for 0-1 V range and `true` for 0-0.5 V range.

To read the current trough a shunt resistor between +Vin and -Vin (see datasheet page 1), first initialize the value of the shunt resistor and call the following function to get the current:

```c
ltc.set_shunt(1.0); // value in ohms
float current = ltc.get_current(false); // in A
```
You can choose between two measurement ranges: `false` for 1 V range and `true` for 0.5 V range. This voltage range is used to measure the voltage drop over shunt resistor based on the current. The current is internally calcluated with the following equation:

I_shunt = (+Vin-(-Vin))/R_shunt
