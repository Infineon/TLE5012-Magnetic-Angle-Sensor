##################################################################################
#
# Attention: this file is used for compilation checks together with
# Jenkins, SonarQube and OpenShift cluster
# 


/usr/local/share/arduino-1.8.10/arduino-builder -dump-prefs -logger=machine -hardware /usr/local/share/arduino-1.8.10/hardware -hardware /home/jenkins/.arduino15/packages -tools /usr/local/share/arduino-1.8.10/tools-builder -tools /usr/local/share/arduino-1.8.10/hardware/tools/avr -tools /home/jenkins/.arduino15/packages -built-in-libraries /usr/local/share/arduino-1.8.10/libraries -libraries /home/jenkins/Arduino/libraries -fqbn=Infineon:arm:XMC1100_Boot_Kit:UART=debug -ide-version=10810 -build-path /tmp/arduino_build_119384 -warnings=none -build-cache /tmp/arduino_cache_548841 -prefs=build.warn_data_percentage=75 -prefs=runtime.tools.XMCFlasher.path=/home/jenkins/.arduino15/packages/Infineon/tools/XMCFlasher/1.2.1 -prefs=runtime.tools.XMCFlasher-1.2.1.path=/home/jenkins/.arduino15/packages/Infineon/tools/XMCFlasher/1.2.1 -prefs=runtime.tools.arm-none-eabi-gcc.path=/home/jenkins/.arduino15/packages/Infineon/tools/arm-none-eabi-gcc/5.4-2016q3 -prefs=runtime.tools.arm-none-eabi-gcc-5.4-2016q3.path=/home/jenkins/.arduino15/packages/Infineon/tools/arm-none-eabi-gcc/5.4-2016q3 -verbose /home/jenkins/Arduino/libraries/Tle94112/examples/Control2Motors/Control2Motors.ino
##################################################################################
#
# XMC1100 Boot Kit     Infineon:arm:XMC1100_Boot_Kit   
# XMC1100 H-Bridge 2Go Infineon:arm:XMC1100_H_BRIDGE2GO
# XMC1100 XMC2Go       Infineon:arm:XMC1100_XMC2GO     
# XMC1300 Boot Kit     Infineon:arm:XMC1300_Boot_Kit   
# XMC1300 Sense2GoL    Infineon:arm:XMC1300_Sense2GoL  
# XMC4700 Relax Kit    Infineon:arm:XMC4700_Relax_Kit 
#
# Arduino BT                        arduino:avr:bt          
# Arduino Duemilanove or Diecimila  arduino:avr:diecimila   
# Arduino Esplora                   arduino:avr:esplora     
# Arduino Ethernet                  arduino:avr:ethernet    
# Arduino Fio                       arduino:avr:fio         
# Arduino Gemma                     arduino:avr:gemma       
# Arduino Industrial 101            arduino:avr:chiwawa     
# Arduino Leonardo                  arduino:avr:leonardo    
# Arduino Leonardo ETH              arduino:avr:leonardoeth 
# Arduino Mega ADK                  arduino:avr:megaADK     
# Arduino Mini                      arduino:avr:mini        
# Arduino NG or older               arduino:avr:atmegang    
# Arduino Nano                      arduino:avr:nano        
# Arduino Pro or Pro Mini           arduino:avr:pro         
# Arduino Robot Control             arduino:avr:robotControl
# Arduino Robot Motor               arduino:avr:robotMotor  
# Arduino Uno WiFi                  arduino:avr:unowifi     
# Arduino Yún                       arduino:avr:yun         
# Arduino Yún Mini                  arduino:avr:yunmini     
# Arduino/Genuino Mega or Mega 2560 arduino:avr:mega        
# Arduino/Genuino Micro             arduino:avr:micro       
# Arduino/Genuino Uno               arduino:avr:uno         
# LilyPad Arduino                   arduino:avr:lilypad     
# LilyPad Arduino USB               arduino:avr:LilyPadUSB 
#
# arduino make file needs arduino-builder
#


# Library
FILE := ./library.properties
name := $(shell grep -m 1 name ${FILE} | sed 's/^.*=//g')
version := $(shell grep -m 1 version ${FILE} | sed 's/^.*=//g')

# Directories
LIB_NAME ?= $(name)
BUILDER_PATH ?= /usr/local/share/arduino-1.8.10
BUILDER ?= arduino-builder
HARDWARE_PATH ?= /home/jenkins/.arduino15/packages
LIB_PATH ?= /home/jenkins/Arduino/libraries

# target list
#targets := Infineon:arm:XMC1100_Boot_Kit Infineon:arm:XMC1100_XMC2GO Infineon:arm:XMC4700_Relax_Kit arduino:avr:uno
#targets := Infineon:arm:XMC1100_Boot_Kit:UART=debug Infineon:arm:XMC1100_XMC2GO:UART=debug Infineon:arm:XMC4700_Relax_Kit arduino:avr:uno
target := Infineon:arm:XMC1100_Boot_Kit:UART=debug

# example list
examples := control2Motors rampSpeedTests rampTest speedControl

# Tools
CD ?= cd
ECHO ?= echo
BASH ?= bash
MAKE_ECHO ?= echo
MKDIR_P := mkdir -p
RM ?= rm
RM_DIR ?= rm -rf
COPY ?= cp
BUILDDIR := ./build

.PHONY: all directories clean compile

all: clean directories
	for example in $(examples); do \
		echo > $(BUILDDIR)/$${example}.sh; \
		echo ${BUILDER_PATH}/${BUILDER} \
		-compile \
		-logger=machine \
		-hardware ${BUILDER_PATH}/hardware \
		-hardware ${HARDWARE_PATH} \
		-tools ${BUILDER_PATH}/tools-builder \
		-tools ${BUILDER_PATH}/hardware/tools/avr \
		-tools ${HARDWARE_PATH} \
		-built-in-libraries ${BUILDER_PATH}/libraries \
		-libraries ${LIB_PATH} \
		-fqbn=$(target) \
		-ide-version=10810 \
		-build-path ${LIB_PATH}/${LIB_NAME}/build/$${example} \
		-warnings=none \
		-prefs=build.warn_data_percentage=75 \
		-prefs=runtime.tools.XMCFlasher.path=${HARDWARE_PATH}/Infineon/tools/XMCFlasher/1.2.1 \
		-prefs=runtime.tools.XMCFlasher-1.2.1.path=${HARDWARE_PATH}/Infineon/tools/XMCFlasher/1.2.1 \
		-prefs=runtime.tools.arm-none-eabi-gcc.path=${HARDWARE_PATH}/Infineon/tools/arm-none-eabi-gcc/5.4-2016q3 \
		-prefs=runtime.tools.arm-none-eabi-gcc-5.4-2016q3.path=${HARDWARE_PATH}/Infineon/tools/arm-none-eabi-gcc/5.4-2016q3 \
		${LIB_PATH}/${LIB_NAME}/examples/$${example}/$${example}.ino >> $(BUILDDIR)/$${example}.sh; \
	done;

compile:
	$(BASH) $(BUILDDIR)/$(example).sh)

directories:
	$(MKDIR_P) $(BUILDDIR)

clean:
	rm -rf $(BUILDDIR)
