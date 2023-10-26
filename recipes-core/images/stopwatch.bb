# custom-rpi image
require /home/soliman/Embedded_Linux/yocto_project/poky/meta/recipes-core/images/core-image-base.bb
#################################################################################################################################

# set image file format
IMAGE_FSTYPES += "wic wic.bmap"

# Remove old image 
RM_OLD_IMAGE = "1"

# install vim & python3 
IMAGE_INSTALL += "vim"

IMAGE_INSTALL:append = " systemd systemd-conf"

# Enable systemd
INIT_MANAGER = "systemd"

IMAGE_INSTALL += " kmod"

# install wpa-supplicant
IMAGE_INSTALL:append = " wpa-supplicant"

# enable wifi 
IMAGE_INSTALL += " linux-firmware-rpidistro-bcm43430"

# install dev tools
IMAGE_INSTALL:append = " gcc g++ cmake make gdb ninja"

# install ssh
IMAGE_INSTALL:append = " openssh"

# install tzdata
IMAGE_INSTALL:append = " tzdata tzdata-africa"

# IMAGE_INSTALL_:append = " psplash"
# IMAGE_FEATURES += " splash "

# install net-tools
IMAGE_INSTALL:append = " net-tools ethtool"

# install kernel modules
IMAGE_INSTALL += " kernel-modules seg7-mod"

IMAGE_INSTALL:append = " main-app "

###############################################

inherit extrausers

EXTRA_USERS_PARAMS = "\
    usermod -p $(openssl passwd Soliman162_Watch) root; \
 "
