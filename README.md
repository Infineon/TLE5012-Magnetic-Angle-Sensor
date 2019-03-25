# TLE5012B-Angle-Sensor

[![Build Status](https://travis-ci.org/Infineon/TLE5012-Magnetic-Angle-Sensor.svg?branch=master)](https://travis-ci.org/Infineon/TLE5012-Magnetic-Angle-Sensor)

<img src="https://www.infineon.com/export/sites/default/media/products/Sensors/TLE_5012B_DSO-8-16_plain_lowres.jpg_945841647.jpg" width=200>

Library of Infineon's highly sensitive [TLE5012B] 360° magnetic angle sensor(https://www.infineon.com/cms/en/product/sensor/magnetic-position-sensor/angle-sensor/tle5012b-e1000/) for Arduino.

## Summary
The [TLE5012B](https://www.infineon.com/cms/en/product/sensor/magnetic-position-sensor/angle-sensor/tle5012b-e1000/) is a 360° angle sensor that detects the orientation of a magnetic field. This is achieved by measuring sine and cosine angle components with monolithic integrated Giant Magneto Resistance (iGMR) elements. These raw signals (sine and cosine) are digitally processed internally to calculate the angle orientation of the magnetic field (magnet). The TLE5012B is a pre-calibrated sensor. The calibration parameters are stored in laser fuses. At start-up the values of the fuses are written into flip-flops, where these values can be changed by the application-specific parameters. Further precision of the angle measurement over a wide temperature range and a long lifetime can be improved by enabling an optional internal autocalibration algorithm. Data communications are accomplished with a bi-directional Synchronous Serial Communication (SSC) that is SPI-compatible. The sensor configuration is stored in registers, which are accessible by the SSC interface. Additionally four other interfaces are available with the TLE5012B: Pulse-Width-Modulation (PWM) Protocol, Short-PWM-Code (SPC) Protocol, Hall Switch Mode (HSM) and Incremental Interface (IIF). These interfaces can be used in parallel with SSC or alone. Pre-configured sensor derivates with different interface settings are available.

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

## Hardware
Please find the datasheet of the TLE5012B [here](https://www.infineon.com/dgdl/Infineon-TLE5012B_Exxxx-DS-v02_01-EN.pdf?fileId=db3a304334fac4c601350f31c43c433f). It depends on the evaluation board which you are using or the respective configuration of the sensor on your PCB which communication protocol as well as addresses you need to use for communicating with the sensor. This library only works with the SPI compatible Synchronous Serial Communication (SSC) interface of the TLE5012B.

## Installation

### Integration of Library
Please download this repository from GitHub by clicking on the following field in the latest [release](https://github.com/Infineon/TLE5012-Magnetic-Angle-Sensor/releases) of this repository:

![Download Library](https://raw.githubusercontent.com/infineon/assets/master/Pictures/Releases_Generic.jpg)

To install the TLE5012B angle sensor library in the Arduino IDE, please go now to **Sketch** > **Include Library** > **Add .ZIP Library...** in the Arduino IDE and navigate to the downloaded .ZIP file of this repository. The library will be installed in your Arduino sketch folder in libraries and you can select as well as include this one to your project under **Sketch** > **Include Library** > **TLE5012B**.

![Install Library](https://raw.githubusercontent.com/infineon/assets/master/Pictures/Library_Install_ZIP.png)

## Usage
Please follow the example sketches in the /examples directory in this library to learn more about the usage of the library. Especially, take care of the SPI and I²C configuration of the sensor. For more information, please consult the datasheet [here](https://www.infineon.com/dgdl/Infineon-TLE5012B_Exxxx-DS-v02_01-EN.pdf?fileId=db3a304334fac4c601350f31c43c433f).
