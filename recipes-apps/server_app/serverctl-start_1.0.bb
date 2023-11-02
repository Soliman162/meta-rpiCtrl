LICENSE = "MIT"
LIC_FILES_CHKSUM = "file://${COMMON_LICENSE_DIR}/MIT;md5=0835ade698e0bcf8506ecda2f7b4f302"

SYSTEMD_AUTO_ENABLE = "enable"
SYSTEMD_SERVICE_${PN} = "start-server.service"

SRC_URI_append = " file://start-server.service"

S = "${WORKDIR}"

DEPENDS = "systemd main-app"

inherit systemd features_check

REQUIRED_DISTRO_FEATURES = "systemd"

do_install() {
  install -d ${D}/${systemd_unitdir}/system
  install -m 0644 start-server.service ${D}/${systemd_unitdir}/system
}

FILES_${PN} += "${systemd_unitdir}/system/start-server.service"
