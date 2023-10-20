FILESEXTRAPATHS:prepend := "${THISDIR}/files:"
# :forcevariable is important to prevent machine specific overrides from overriding your logo such as in case of raspberry pi layers.
SPLASH_IMAGES:forcevariable = "file://test_rpi.png;outsuffix=one \
                               file://psplash-raspberrypi-img.h;outsuffix=raspberrypi"
