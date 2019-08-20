# Installation

## Integration of Library
Please download this repository from GitHub by clicking on the following field in the latest [release](https://github.com/Infineon/TLE5012-Magnetic-Angle-Sensor/releases) of this repository:

![Download Library](https://raw.githubusercontent.com/infineon/assets/master/Pictures/Releases_Generic.jpg)

To install the TLE5012B angle sensor library in the Arduino IDE, please go now to **Sketch** > **Include Library** > **Add .ZIP Library...** in the Arduino IDE and navigate to the downloaded .ZIP file of this repository. The library will be installed in your Arduino sketch folder in libraries and you can select as well as include this one to your project under **Sketch** > **Include Library** > **TLE5012B**.

![Install Library](https://raw.githubusercontent.com/infineon/assets/master/Pictures/Library_Install_ZIP.png)

## Usage
Please follow the example sketches in the /examples directory in this library to learn more about the usage of the library. Especially, take care of the SPI and I²C configuration of the sensor. For more information, please consult the datasheet [here](https://www.infineon.com/dgdl/Infineon-Angle_Sensor_TLE5012B-UM-v01_02-en-UM-v01_02-EN.pdf?fileId=5546d46146d18cb40146ec2eeae4633b).
 For more information:
* see here for the sensors user manual [TLE5012B](https://www.infineon.com/cms/en/product/sensor/magnetic-sensors/magnetic-position-sensors/angle-sensors/)
* you can find several application notes concerning the sensor position and disc magnet design on the same page
* there is a handy [pin out picture](https://raw.githubusercontent.com/infineon/assets/master/Pictures/TLE5012B_Sensor_2Go_Pin_out.png)
<img src="https://raw.githubusercontent.com/infineon/assets/master/Pictures/TLE5012B_Sensor_2Go_Pin_out.png" width=100%>

## Installation of XMC
If you use a Sensor2Go evolution kit or any Infineon XMC microcontroller like the XMC1100 Boot Kit or the XMC4700 Relax Kit, than you must also
install the [XMC-for-Arduino library from here](https://github.com/Infineon/XMC-for-Arduino).
The Sensor2Go will be recognized as MC1100 XMC 2Go.
