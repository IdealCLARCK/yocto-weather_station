SUMMARY = "A customized image for development purposes."

LICENSE = "MIT"
inherit core-image

IMAGE_FEATURES += "splash"
IMAGE_FEATURES += "tools-debug"
IMAGE_FEATURES += "tools-profile"
IMAGE_FEATURES += "tools-sdk"
IMAGE_FEATURES += "ssh-server-dropbear"
IMAGE_INSTALL:append = " mc"
IMAGE_INSTALL:append = " nano"
IMAGE_INSTALL:append = " service1"
IMAGE_INSTALL:append = " service2"
IMAGE_INSTALL:append = " service3"
IMAGE_INSTALL:append = " service1-start"
IMAGE_INSTALL:append = " service2-start"
IMAGE_INSTALL:append = " service3-start"
