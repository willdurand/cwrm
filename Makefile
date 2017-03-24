SHELL = bash

NAME=Camera WiFi Remote Module
VERSION=1.0.0
SRC_DIR=./cwrm
GENERATED_HEADER_FILE=$(SRC_DIR)/cwrm_generated.h

SKETCH=$(SRC_DIR)/cwrm.ino
BUILD_DIR=./build
UPLOAD_PORT=/dev/cu.usbserial-A50285BI

include makeEspArduino.mk

# https://github.com/kangax/html-minifier
compile-html:
	@echo '/* This file has been automatically generated, do not edit it */' > $(GENERATED_HEADER_FILE)
	@echo '' >> $(GENERATED_HEADER_FILE)
	@echo '#ifndef CWRM_GENERATED_H' >> $(GENERATED_HEADER_FILE)
	@echo '#define CWRM_GENERATED_H' >> $(GENERATED_HEADER_FILE)
	@echo '' >> $(GENERATED_HEADER_FILE)
	@echo '#define AP_NAME "$(NAME)"' >> $(GENERATED_HEADER_FILE)
	@echo '' >> $(GENERATED_HEADER_FILE)
	@echo -n 'const String indexHTML = R"(' >> $(GENERATED_HEADER_FILE)
	@html-minifier \
		--minify-css \
		--minify-js \
		--remove-style-link-type-attributes \
		--remove-script-type-attributes \
		--remove-redundant-attributes \
		--remove-optional-tags \
		$(SRC_DIR)/index.html \
		| sed 's/AP_NAME/$(NAME)/g' \
		| head -c -2 >> $(GENERATED_HEADER_FILE)
	@echo ')";' >> $(GENERATED_HEADER_FILE)
	@echo '' >> $(GENERATED_HEADER_FILE)
	@echo '#endif' >> $(GENERATED_HEADER_FILE)

.PHONY: compile-html
