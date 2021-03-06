#
# This file was derived from the 'Hello World!' example recipe in the
# Yocto Project Development Manual.
#

SUMMARY = "Simple helloworld application for the i2c display"
SECTION = "bundle"
LICENSE = "MIT"
LIC_FILES_CHKSUM = "file://${COMMON_LICENSE_DIR}/MIT;md5=0835ade698e0bcf8506ecda2f7b4f302"

SRCREV = "${AUTOREV}"
SRC_URI = "git://git@github.com/malmbergoe/DisplayHelloWorld.git;protocol=ssh"

S = "${WORKDIR}"

do_compile() {
	     ${CXX} -std=c++11 ${LDFLAGS} git/displayHello.cpp -o helloworld_display
}

do_install() {
	     install -d ${D}${bindir}
	     install -m 0755 helloworld_display ${D}${bindir}
}
