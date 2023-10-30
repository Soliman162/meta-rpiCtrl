# Creating a Yocto Image for Raspberry Pi 3 b+

### This README provides step-by-step instructions for creating a Yocto image to Control raspberry pi using socket programming.

## Prerequisites

Before proceeding, ensure you have the following prerequisites:

- Raspberry Pi3 b+ board
- 7 segment  x2
- leds       x4
- Host machine (Linux recommended)
- Internet connection
- Basic familiarity with the command line

## Step 1: Set up the Build Environment

1. Follow this [link](https://docs.yoctoproject.org/ref-manual/system-requirements.html) to Install the required dependencies. 
2. Clone this repo.
3. Install the required Layers 
    - [poky](https://github.com/yoctoproject/poky.git)
    - [meta-openembedded](https://github.com/openembedded/meta-openembedded.git)
    - [meta-raspberrypi](https://github.com/agherzan/meta-raspberrypi.git)

> [!IMPORTANT] 
> make sure that all branches of these repositories match with dunfell as this layer was built and tested under Dunfell. 

## Step 2: Initialize the build environment:
```shell
source poky/oe-init-build-env 
bitbake-layers add-layer <path_to_raspberrypi_layer>
bitbake-layers add-layer <path_to_openembedded_layer/meta-oe>
bitbake-layers add-layer <path_to_this_repo_folder>
```
## Step 3: Configure the Build:

1. Open the conf/local.conf file in a text editor.

2. Modify the configuration .
    - `MACHINE = "raspberrypi3-64-machine"`
    - `DISTRO = "rpictrl-distro"`
    - `EXTRA_IMAGE_FEATURES = "dev-pkgs tools-sdk"`
    - `PACKAGE_CLASSES = "package_deb"`

3. Edit ssid and password for your wifi:
    - change dirctory to wpa-supplicant `cd recipes-connectivity/wpa-supplicant/wpa-supplicant/`
    - rename file `mv wpa_supplicant-nl80211-wlan0.conf.example wpa_supplicant-nl80211-wlan0.conf`
    - Open the `wpa_supplicant-nl80211-wlan0.conf` file in a text editor and modify ssid and password.

## Step 4: Start the build process: 
```shell
bitbake rpictrl 
``` 
## Step 5: Deploy the Image to the Raspberry Pi:

1. Once the build is finished, navigate to the build directory 
`cd tmp/deploy/images/<target-machine>/`

2. Copy the generated image file to an SD card 
`sudo bmaptool copy --bmap *.rootfs.wic.bmap  *.rootfs.wic.bz2  /dev/<storage_device>`

## Step 7: Hardware connection:
- seven segment0 pins (a:GPIO2 b:GPIO3 c:GPIO4 d:GPIO17 e:GPIO27 f:GPIO22 g:GPIO10 com:GPIO26)
- seven segment1 pins (a:GPIO18 b:GPIO23 c:GPIO24 d:GPIO25 e:GPIO8 f:GPIO7 g:GPIO12 com:GPIO16)
- leds pins (GPIO5,GPIO6,GPIO13,GPIO19)
