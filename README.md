# Rodeo IoT Application Examples

Rodeo IoT enables customs application through its SDK. If you have purchased a Rodeo EVK and would like to develop your
own application, this is the place to start.

## System Requirements

The build should require very little configuration of your system. We recommend a Debian based Linux distribution. The
first step is to download an install the SDK in the correct location. The archive provided should be unpacked using the
following command:

```
sudo tar xf se-rodeo-iot-sdk-v1.0.0.tar.gz -C /opt/se-rodeo-iot-sdk
sudo chown -R 1000:1000 /opt/se-rodeo-iot-sdk
```

The previous commands need to be run as root because the /opt directory is protected. The SDK includes all header files,
libraries and the toolchain required to build a custom application. 

The build requires cmake be installed on the build machine. On any Ubuntu or Debian based machine use the following
commands to install cmake:

```
sudo apt-get install cmake
```

The organization name must be overriden in the CMakePreset.json configuration:

- ORG_NAME: the oraganization name assigned at time of purchase, usually the company name.

If your organization name is not set correctly, the device will fail to connect to the Rodeo IoT cloud.

## Building

Next configure and build the example applications:

```
cmake --preset debug
make -j -C build/debug
```

The outputs will be located in `build/debug/<app name>`. There are two outputs per example application which will be of
interest. One has the extension .axf, the other with the extension .bin. Depending on how you are loading the code on
target, you can select the appropriate file. The `debug` preset can be substituted for `release`. These are just
recommendations, and any presets may be added to the preset file as required.

## Debugging

### Loading code via serial bootloader
If you have a device with the serial bootloader configured, you can use x-modem to load a binary file (the one with the
*.bin extension) onto the deivce without the need for a JTAG debugger. When the deivce boots, there is a  5 second delay
to press `x` in order to enter serial bootloader mode. Once entered, the bootloader will begin to erase all the
application flash in preparation for the transfer. Once completed, the letter `C` will be printed out repeatedly. At his
point start an x-modem client application such as teraterm or minicom and send the file to the device. The application
will be started automatically once the transfer is completed.

### Loading code via SEGGER JLink
If you have a SEGGER JLink, you can load the code and debug by plugging into the 10 pin debug header on the Wrangler.
First start the JLink GDB server in a separate terminal using the following command:

```
JLinkGDBServerCLExe -nosilent -select USB -endian little -noir -speed auto -vd -device  MIMXRT1021DAG5A -if
SWD -halt
```

Leave that running and then open a new terminal and ensure the compiler path is loaded into the environment. Start the
ARM cross compiler GDB and connect to the GDB server. Load the code using the file with the extension *.axf in the
output directory and run.

```
export PATH=/opt/se-rodeo-iot-sdk/toolchain/bin:$PATH
arm-none-eabi-gdb build/<app dir>/<app executable>.axf
target remote localhost:2331
monitor reset
load
c
```

The application should now be running and you can use GDB to debug as needed.

## Documentation

The SDK provides additional documentation for specific drivers and subsystems. These are located in the
`/opt/se-rodeo-iot-sdk/share/rodeo-iot/doxygen-homepage.html` and can be viewed with any browser. These files have been
automtically generated using doxygen.
