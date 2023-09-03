SUMMARY = "Recipe to setup script that start service2"
SECTION = "custom"

LICENSE = "MIT"
LIC_FILES_CHKSUM = "file://${COMMON_LICENSE_DIR}/MIT;md5=0835ade698e0bcf8506ecda2f7b4f302" 

SRC_URI  = "file://service2-script"

inherit update-rc.d

INITSCRIPT_NAME = "service2"
INITSCRIPT_PARAMS = "defaults 80"

do_install() {
  install -d ${D}${sysconfdir}/init.d
  install -m 755 ${WORKDIR}/service2-script ${D}${sysconfdir}/init.d/service2
}
