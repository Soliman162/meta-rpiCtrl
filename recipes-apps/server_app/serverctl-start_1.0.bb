LICENSE = "MIT"
LIC_FILES_CHKSUM = "file://${COMMON_LICENSE_DIR}/MIT;md5=0835ade698e0bcf8506ecda2f7b4f302"

SRC_URI_append = " file://systemd-start-server.service"

SYSTEMD_AUTO_ENABLE = "enable"
SYSTEMD_SERVICE_${PN} = "systemd-start-server.service"

S = "${WORKDIR}"

DEPENDS = "systemd main-app wpa-supplicant"
REQUIRED_DISTRO_FEATURES = "systemd"

inherit systemd features_check

do_install() {
  install -d ${D}${systemd_system_unitdir}
  install -m 0644 ${WORKDIR}/systemd-start-server.service ${D}${systemd_system_unitdir}
}

FILES_${PN} += "${systemd_system_unitdir}/systemd-start-server.service"
