DESCRIPTION = "Service 3"
LICENSE = "GPL-2.0-only"
LIC_FILES_CHKSUM = "file://${COMMON_LICENSE_DIR}/GPL-2.0-only;md5=801f80980d171dd6425610833a22dbe6" 

SRC_URI += "file://service3.c \
file://custom_logger.c \
file://custom_logger.h"
SRC_URI[md5sum] = "f514a6acd74a12015444c66dc150042e"

TARGET_CC_ARCH += "${LDFLAGS}"

S = "${WORKDIR}"

do_compile() {
    $CC  $CFLAGS -DARM_BUILD custom_logger.c service3.c -Wall -o service3
}

do_install() {
    install -d ${D}/${bindir}
    install -m 0755 service3 ${D}/${bindir}/
}
