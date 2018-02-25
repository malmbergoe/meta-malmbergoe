# Base this image on the core-image-minimal.
include recipes-core/images/core-image-minimal.bb

DESCRIPTION = "my first layer... targeted for raspberrypi 3"
LICENSE = "MIT"

IMAGE_FEATURES += "ssh-server-dropbear splash"

IMAGE_INSTALL += " \
		kernel-modules \
		i2c-tools \
		displayhello \
		"
