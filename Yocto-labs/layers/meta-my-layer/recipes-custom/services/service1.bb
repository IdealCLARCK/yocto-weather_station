DESCRIPTION = "Service 1"
LICENSE = "GPL-2.0-only"
LIC_FILES_CHKSUM = "file://${COMMON_LICENSE_DIR}/GPL-2.0-only;md5=801f80980d171dd6425610833a22dbe6" 

SRC_URI = "file://service1.c"
SRC_URI[md5sum] = "f514a6acd74a12015444c66dc150042e"

TARGET_CC_ARCH += "${LDFLAGS}"

S = "${WORKDIR}"

do_compile() {
    $CC  $CFLAGS -DARM_BUILD service1.c -Wall -o service1
}

do_install() {
    install -d ${D}/${bindir}
    install -m 0755 service1 ${D}/${bindir}/
}
