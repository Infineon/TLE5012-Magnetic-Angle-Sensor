# TLE5012B-Angle-Sensor

[![Build Status](https://travis-ci.org/Infineon/TLE5012-Magnetic-Angle-Sensor.svg?branch=master)](https://travis-ci.org/Infineon/TLE5012-Magnetic-Angle-Sensor)

| <img src="https://www.infineon.com/export/sites/default/media/products/Sensors/TLE_5012B_DSO-8-16_plain_lowres.jpg_945841647.jpg" width=200 style="background:white"> | <img src="https://raw.githubusercontent.com/infineon/assets/master/Pictures/TLE5012B_horizontal.png" width=400 style="background:white"> |
|:--:|:--:|
| *bulk sensor* | *Sensor2Go kit* 

Library of Infineon's highly sensitive [TLE5012B](https://www.infineon.com/cms/en/product/sensor/magnetic-sensors/magnetic-position-sensors/angle-sensors) 360° magnetic angle sensor for Arduino.

## Summary
The [TLE5012B](https://www.infineon.com/cms/en/product/evaluation-boards/tle5012b_e1000_ms2go/) is a 360° angle sensor that detects the orientation of a magnetic field. This is achieved by measuring sine and cosine angle components with monolithic integrated Giant Magneto Resistance (iGMR) elements. These raw signals (sine and cosine) are digitally processed internally to calculate the angle orientation of the magnetic field (magnet). The TLE5012B is a pre-calibrated sensor. The calibration parameters are stored in laser fuses. At start-up the values of the fuses are written into flip-flops, where these values can be changed by the application-specific parameters. Further precision of the angle measurement over a wide temperature range and a long lifetime can be improved by enabling an optional internal auto calibration algorithm. Data communications are accomplished with a bi-directional Synchronous Serial Communication (SSC) that is SPI-compatible. The sensor configuration is stored in registers, which are accessible by the SSC interface. Additionally four other interfaces are available with the TLE5012B: Pulse-Width-Modulation (PWM) Protocol, Short-PWM-Code (SPC) Protocol, Hall Switch Mode (HSM) and Incremental Interface (IIF). These interfaces can be used in parallel with SSC or alone. Pre-configured sensor derivate with different interface settings are available.

## Key Features and Benefits
* Giant Magneto Resistance (GMR)-based principle
* Integrated magnetic field sensing for angle measurement
* 360° angle measurement with revolution counter and angle speed measurement
* Two separate highly accurate single bit SD-ADC
* 15 bit representation of absolute angle value on the output (resolution of 0.01°)
* 16 bit representation of sine / cosine values on the interface
* Max. 1.0° angle error over lifetime and temperature-range with activated auto-calibration
* Bi-directional SSC Interface up to 8 Mbit/s
* Interfaces: SSC, PWM, Incremental Interface (IIF), Hall Switch Mode (HSM), Short PWM Code (SPC, based on SENT protocol defined in SAE J2716)
* Output pins can be configured (programmed or pre-configured) as push-pull or open-drain
* Bus mode operation of multiple sensors on one line is possible with SSC or SPC interface

## Installation
For the description of library [installation](docs/Installation.md)

## Examples
For the description of the [examples](docs/Examples.md)

## Library documentation
The doxygen [library documentation](https://infineon.github.io/TLE5012-Magnetic-Angle-Sensor/).

## Hardware
Please find the datasheet of the TLE5012B [here](https://www.infineon.com/dgdl/Infineon-TLE5012B_Exxxx-DS-v02_01-EN.pdf?fileId=db3a304334fac4c601350f31c43c433f). It depends on the evaluation board which you are using or the respective configuration of the sensor on your PCB which communication protocol as well as addresses you need to use for communicating with the sensor. This library only works with the SPI compatible Synchronous Serial Communication (SSC) interface of the TLE5012B.

### Sens2Go
The Infineon TLE5012B Sens2Go evaluation kit use 3-wire SPI on board, so MISO/MOSI pin 0 and 1 are short. Here the Sensor PCB is
breakable from the XMC2Go part. If you do so, than you can attache the Sensor PCB to any SPI interface but still only as a 3-wire SPI.
The left over XMC2Go can also used for any other project but also has only a 3-wire SPI on board, otherwise it is identical to the XMC2Go.

### XMC1100 Boot Kit
Use the 5V instead of the 3.3V connector for proper SPI connection due to the attached LED to the SCK pin.

### XMC4700 Relax Kit
The Infineon XMC4700 Relax Kit has up to five different SPI channels, whereas the default SPI is in the arduino header at its
default position, SPI3 and SPI4 are already in use, so that at the end three SPIs can be used. On the XMC4700 Relax Kit the sensor
can run with 3.3V or 5V (depending on the board version)

### Arduino/Genuino UNO
Due to very limited memory this both microcontroller can not run all examples. In that case an error message appears.

### Bulk Sensor
To connect the 3-wire SSC interface to an Arduino with a 4-wire SPI interface you will need a resistor with a value between 3.3k Ohm and 10k Ohm.
Connect the resistor between DATA and MOSI (pin 11 on an UNO). If you are connecting multiple sensors they can all share one DATA line and one resistor.
The Sensor2Go evaluation board uses 3-wire SSC, so no resistor is needed between MISO and MOSI.

| TLE5012B Pin | Sensor2Go Pin | Pin Function | Arduino Pin | Function | 
|:------------:|---------------|--------------|:-----------:|----------|
|       2      | 3 / P0.8      | SCK          |      13     | SCK      |
|       3      | 4 / P0.9      | CSQ          |      10     | SS       |
|       4      | 2 / P0.7      | DATA         |      12     | MISO     | 
|              | no resistor   | resistor     |      11     | MOSI     |
|       6      | 14 /3.3V      | Vdd          |  3.3V or 5V | Power    |
|       7      | 15            | GND          |     GND     | Ground   |

### Variants
The TLE5012 sensor comes in various Interface variants but the SSC interface is always possible.
See the documentation which options and settings are available for each interface and for the
Sensor2Go kit see the checkmark at the back of the package. If you don't know which sensor setup
you have use the examples/Read_Sensor_Type/Read_Sensor_Type.ino or the  examples/Read_Sensor_Registers/Read_Sensor_Registers.ino
scetch to check.
* TLE5012B E1000 automotive predefined variant with SSC & IIF communication protocols
* TLE5012B E5000 automotive predefined variant with SSC & PWM communication protocols
* TLE5012B E9000 automotive predefined variant with SSC & SPC communication protocols
* TLI5012B E1000 industrial predefined variant with SSC & IIF communication protocols


## More information and links
* [Infineon Maker page](https://www.infineon.com/cms/en/tools/landing/infineon-for-makers/#overview)
* [Infineon Microcontroller](https://www.infineon.com/cms/en/tools/landing/infineon-for-makers/microcontroller-boards/)
* [Infineon XENSIV™ - Sensor 2GO kits](https://www.infineon.com/cms/en/product/promopages/sensors-2go/#shields2go-myiot)
* [Infineon Magnetic Sensor Kits](https://www.infineon.com/cms/en/product/promopages/sensors-2go)
* [TLE5012B variants](https://www.infineon.com/cms/en/product/promopages/sensors-2go/#angle-sensor-2go)
* [TLE5012B manual](https://www.infineon.com/dgdl/Infineon-Angle_Sensor_TLE5012B-UM-v01_02-en-UM-v01_02-EN.pdf?fileId=5546d46146d18cb40146ec2eeae4633b)
* [GUI for Angle Sensor 2GO](https://www.infineon.com/dgdl/Infineon-Software-Magnetic-Angle-Sensor-2Go-SW-v01_01-SW-v01_01-EN.zip?fileId=5546d462675a69720167799771c5519e)