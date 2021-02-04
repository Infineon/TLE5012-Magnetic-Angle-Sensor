NAME := App_readSpeedProcessing

$(NAME)_SOURCES    := readSpeedProcessing.cpp

$(NAME)_INCLUDES += ./

$(NAME)_COMPONENTS := drivers/sensors/TLE5012B

VALID_PLATFORMS	:= CYW943907AEVAL1F