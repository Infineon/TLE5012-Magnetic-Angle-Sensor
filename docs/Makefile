##################################################################################
# documentation build files
# - generates the html doxygen documentation
# needed software:
# - graphviz dot
# - doxygen 1.8.15 or higher

FILE     := ./library.properties
name	 := $(name < $(FILE))
version	 := $(version < $(FILE))

# Directories
DOXY_NAME ?= $(name)
DOXY_NUMBER ?= $(version)
SRC_DIR ?= ../
DOC_DIR ?= ./
DOC_IMG_DIR ?= ./img
DOC_BUILD_DIR ?= ./
DOT_PATH ?= /usr/bin/dot
# General settings
DOXYFILE ?= doxyfile_html
WORKING_DOXYFILE ?= temp_doxyfile
PROJECT_LOGO ?=  https://raw.githubusercontent.com/Infineon/Assets/master/Pictures/ifx_logo.png
DOXYGEN_WARNING ?= warn.log

# Tools
CD ?= cd
ECHO ?= echo
DOXYGEN_ECHO ?= echo
RM ?= rm
RM_DIR ?= rm -rf
COPY ?= cp
DOXYGEN ?= ${DOXY_BIN_PATH}/doxygen

html:
	@$(ECHO) Generating $@ 
	@$(COPY) $(DOXYFILE) $(WORKING_DOXYFILE)
	@$(DOXYGEN_ECHO) >> $(WORKING_DOXYFILE)
	@$(DOXYGEN_ECHO) INPUT=$(SRC_DIR) >> $(WORKING_DOXYFILE)
	@$(DOXYGEN_ECHO) PROJECT_NAME=$(DOXY_NAME) >> $(WORKING_DOXYFILE)
	@$(DOXYGEN_ECHO) PROJECT_NUMBER=$(DOXY_NUMBER) >> $(WORKING_DOXYFILE)
	@$(DOXYGEN_ECHO) OUTPUT_DIRECTORY = $(DOC_BUILD_DIR) >> $(WORKING_DOXYFILE)
	@$(DOXYGEN_ECHO) PROJECT_LOGO = $(PROJECT_LOGO) >> $(WORKING_DOXYFILE)
	@$(DOXYGEN_ECHO) IMAGE_PATH = $(DOC_IMG_DIR) >> $(WORKING_DOXYFILE)
	@$(DOXYGEN_ECHO) DOT_PATH = "$(DOT_PATH)" >> $(WORKING_DOXYFILE)
	@$(DOXYGEN) $(WORKING_DOXYFILE)

clean:
	@$(ECHO) Removing build directory
	@$(RM_DIR) $(DOC_BUILD_DIR)
	@$(ECHO) Removing temporary files
	@$(RM) $(DOXYGEN_WARNING)
	@$(RM) $(WORKING_DOXYFILE)
	@$(RM) $(LIBRARY_NAME).pdf

.PHONY: lib_doc clean
