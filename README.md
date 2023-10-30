# README: Creating a Yocto Image for Raspberry Pi 3 b+

This README provides step-by-step instructions for creating a Yocto image to Control raspberry pi using socket programming.

## Prerequisites

Before proceeding, ensure you have the following prerequisites:

- Raspberry Pi3 b+ board
- 7segment 
- 4 leds
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
3. Save and close the file.

4. Edit ssid and password for your wifi:
    - `cd recipes-connectivity/wpa-supplicant/wpa-supplicant/`
    - rename file `mv wpa_supplicant-nl80211-wlan0.conf.example wpa_supplicant-nl80211-wlan0.conf`
    - Open the `wpa_supplicant-nl80211-wlan0.conf` file in a text editor and modify ssid and password.

## Step 4: Start the build process: 
```shell
bitbake rpictrl 
``` 
