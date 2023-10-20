SUMMARY = "module for 7 segment display"
DESCRIPTION = "${SUMMARY}"
LICENSE = "GPLv2"
LIC_FILES_CHKSUM = "file://COPYING;md5=12f884d2ae1ff87c09e5b7ccc2c4ca7e"

inherit module

SRC_URI = "file://Makefile \
           file://seg7_display_mod.h \
           file://seg7_display_mod.c \
           file://COPYING \
          "

S = "${WORKDIR}"

# insmod seg7_display_mod.ko
KERNEL_MODULE_AUTOLOAD += "seg7_display_mod"

# The inherit of module.bbclass will automatically name module packages with
# "kernel-module-" prefix as required by the oe-core build environment.
RPROVIDES_${PN} += "kernel-module-7seg-display"
