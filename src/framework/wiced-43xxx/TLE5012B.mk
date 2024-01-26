#############################################
# Makefile for CYPRESS WICED WICED 43xxx ####
#############################################
# Include library folder in "libraries/drivers/sensors".
# Add lib to demo or snipped to the makefile
# variable $(NAME)_COMPONENTS += libraries/drivers/sensors

NAME := Lib_TLE5012B

GLOBAL_DEFINES   := TLE5012_FRAMEWORK=TLE5012_FRMWK_WICED

GLOBAL_INCLUDES  := src/config \
					src/corelib \
					src/pal \
					src/framework/wiced-43xxx/pal \
					src/framework/wiced-43xxx/wrapper

$(NAME)_SOURCES  := src/corelib/TLE5012b.cpp \
					src/corelib/tle5012b_reg.cpp \
					src/pal/gpio.cpp \
					src/pal/spic.cpp \
					src/framework/wiced-43xxx/pal/timer-wiced.cpp \
					src/framework/wiced-43xxx/pal/gpio-wiced.cpp \
					src/framework/wiced-43xxx/pal/spic-wiced.cpp \
					src/framework/wiced-43xxx/pal/TLE5012-pal-wiced.cpp

VALID_PLATFORMS := CYW943907AEVAL1F