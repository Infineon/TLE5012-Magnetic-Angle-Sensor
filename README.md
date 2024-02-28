# XENSIV TLx5012B Angle Sensor

![PlatformIO CI](https://github.com/OlafFilies/TLE5012-Magnetic-Angle-Sensor/workflows/PlatformIO%20CI/badge.svg)
![Arduino CI](https://github.com/OlafFilies/TLE5012-Magnetic-Angle-Sensor/workflows/Arduino%20CI/badge.svg)
![Doxygen GH](https://github.com/OlafFilies/TLE5012-Magnetic-Angle-Sensor/workflows/Doxygen%20GH/badge.svg)

| <img src="https://github.com/infineon/TLE5012-Magnetic-Angle-Sensor/wiki/img/TLE_5012B_DSO-8-16_plain.jpg" width=200 style="background:white"> | <img src="https://github.com/infineon/TLE5012-Magnetic-Angle-Sensor/wiki/img/TLE5012B_breakout.png" width=150 style="background:white"> | <img src="https://github.com/infineon/TLE5012-Magnetic-Angle-Sensor/wiki/img/TLE5012B_horizontal.png" width=400 style="background:white"> |
|:--:|:--:|:--:|
| *bulk sensor* | *breakout board* | *Sensor2Go kit* 

Library of Infineon's highly sensitive [TLx5012B](https://www.infineon.com/cms/en/product/sensor/magnetic-sensors/magnetic-position-sensors/angle-sensors) 360° magnetic angle sensor.
### Supported Frameworks

<table>
    <tr>
        <td><img src="https://github.com/infineon/TLE5012-Magnetic-Angle-Sensor/wiki/img/arduino-logo.png" width=200></td>
        <td><img src="https://github.com/infineon/TLE5012-Magnetic-Angle-Sensor/wiki/img/wiced-logo.png" width=200></td>
        <td><img src="https://github.com/infineon/TLE5012-Magnetic-Angle-Sensor/wiki/img/cross-platform.png" width=200></td>
    </tr>
    <tr>
        <td style="text-align: center"><a href="https://github.com/Infineon/TLE5012-Magnetic-Angle-Sensor/wiki/Arduino-API">Arduino API</a></td>
        <td style="text-align: center"><a href="https://github.com/Infineon/TLE5012-Magnetic-Angle-Sensor/wiki/WICED-API">WICED API</a></td>
        <td style="text-align: center"><a href="https://github.com/Infineon/TLE5012-Magnetic-Angle-Sensor/wiki/TLE5012B-API/">TLE5012B API</a><br><a href="https://github.com/Infineon/TLE5012-Magnetic-Angle-Sensor/wiki/TLE5012BMotor-API">TLx5012B Register API</a></td>
    </tr>
    <tr>
        <td style="text-align: center"><a href="https://github.com/Infineon/TLE5012-Magnetic-Angle-Sensor/wiki/Ino-Getting-Started">Getting Started</a></td>
        <td style="text-align: center"><a href="https://github.com/Infineon/TLE5012-Magnetic-Angle-Sensor/wiki/CW-Getting-Started">Getting Started</a></td>
        <td style="text-align: center"><a href="https://github.com/Infineon/TLE5012-Magnetic-Angle-Sensor/wiki/Porting-Guide">Porting Guide</a></td>
    </tr>
</table>

## Summary
The [TLE5012B](https://www.infineon.com/cms/en/product/evaluation-boards/tle5012b_e1000_ms2go/) is a 360° angle sensor that detects the orientation of a magnetic field. This is achieved by measuring sine and cosine angle components with monolithic integrated Giant Magneto Resistance (iGMR) elements. These raw signals (sine and cosine) are digitally processed internally to calculate the angle orientation of the magnetic field (magnet). The TLx5012B is a pre-calibrated sensor. The calibration parameters are stored in laser fuses. At start-up the values of the fuses are written into flip-flops, where these values can be changed by the application-specific parameters. Further precision of the angle measurement over a wide temperature range and a long lifetime can be improved by enabling an optional internal auto calibration algorithm. Data communications are accomplished with a bi-directional Synchronous Serial Communication (SSC) that is SPI-compatible. The sensor configuration is stored in registers, which are accessible by the SSC interface. Additionally four other interfaces are available with the TLx5012B: Pulse-Width-Modulation (PWM) Protocol, Short-PWM-Code (SPC) Protocol, Hall Switch Mode (HSM) and Incremental Interface (IIF). These interfaces can be used in parallel with SSC or alone. Pre-configured sensor derivate with different interface settings are available.

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
## Installation, Documentation, Variants etc.
Please have a look at the [wiki](https://github.com/infineon/TLE5012-Magnetic-Angle-Sensor/wiki) for all questions about this library and the sensor.

## More information and links
* [Infineon Maker page](https://www.infineon.com/cms/en/tools/landing/infineon-for-makers/#overview)
* [Infineon Microcontroller](https://www.infineon.com/cms/en/tools/landing/infineon-for-makers/microcontroller-boards/)
* [Infineon XENSIV™ - Sensor 2GO kits](https://www.infineon.com/cms/en/product/promopages/sensors-2go/#shields2go-myiot)
* [Infineon Magnetic Sensor Kits](https://www.infineon.com/cms/en/product/promopages/sensors-2go)
* [TLx5012B variants](https://www.infineon.com/cms/en/product/promopages/sensors-2go/#angle-sensor-2go)
* [TLx5012B manual](https://www.infineon.com/dgdl/Infineon-Angle_Sensor_TLE5012B-UM-v01_02-en-UM-v01_02-EN.pdf?fileId=5546d46146d18cb40146ec2eeae4633b)
* [GUI for Angle Sensor 2GO](https://www.infineon.com/dgdl/Infineon-Software-Magnetic-Angle-Sensor-2Go-SW-v01_01-SW-v01_01-EN.zip?fileId=5546d462675a69720167799771c5519e)
* [XMC-for-Arduino](https://github.com/Infineon/XMC-for-Arduino)
* [WICED Studio](https://community.cypress.com/community/software-forums/wiced-wifi/wiced-wifi-documentation)
* [Cypress Evaluation Kit CYW43907AEVAL1F](https://www.cypress.com/CYW943907AEVAL1F)

### License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.
