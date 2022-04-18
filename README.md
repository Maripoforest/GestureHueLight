<!-- PROJECT LOGO -->
<h1 align="center">GestureHueLight</h1>
<p align="center">
<br/>
<p align="center">
<img src="https://github.com/Maripoforest/GestureHueLight/blob/main/logo2.png" width="400" height="400">
  </p>
<br/>
<p align="center">
    <a href="https://youtu.be/0vhuDy584RA">Youtube</a>
    &nbsp;
    &nbsp;
    <a href="https://www.bilibili.com/video/BV1ja411v7GH?share_source=copy_web">Bilibili</a>
    &nbsp;
    &nbsp;
    <a href="https://twitter.com/home">Twitter</a>
</p>
<p align="center">
    <a href="https://github.com/Maripoforest/GestureHueLight/graphs/contributors" alt="Contributors">
        <img src="https://img.shields.io/github/contributors/Maripoforest/GestureHueLight.svg" /></a>
    <a href="https://github.com/Maripoforest/GestureHueLight/issues" alt="Issues">
        <img src="https://img.shields.io/github/issues/Maripoforest/GestureHueLight.svg" /></a>
    <a href="https://github.com/Maripoforest/GestureHueLight/blob/main/LICENSE" alt="License">
        <img src="https://img.shields.io/github/license/Maripoforest/GestureHueLight.svg?color=red" /></a>
    <a href="https://github.com/Maripoforest/GestureHueLight/releases" alt="Tag">
        <img src="https://img.shields.io/github/v/release/Maripoforest/GestureHueLight?color=pink" alt="build status"></a>
</p>

## Introduction
During the COVID crisis, people find it more important than ever to control their office facilities without physical touch. 
The touchless control should be what we pursue in the future. 
Although we already have sound-controlled or simple IR-controlled light switches, it is not likely to change the brightness of the object light bulb with them. 
In this case, a camera based gesture control switch came up in our mind. 
It has to be simple to use, flexible enough to change the room brightness, and most important, touchless.

## Project Flowchart
![](flowchart2.png)

## Hareware
<img src="https://github.com/Maripoforest/GestureHueLight/blob/20-license-haiyang/hardware.svg" width="500" height="500">

## Prerequistes
**IMPORTANT** 
1. This project has dependencies on [cURL](https://github.com/curl/curl.git). To build cURL, we need the OPENSSL developer kit and curl lib:
```
sudo apt-get install libssl-dev
sudo apt install curl
```

2. To use the I2C bus, make sure the linux I2C dev library is installed:
```
sudo apt-get install libi2c-dev
```

3. To use the Qt lib, make sure **ALL** Qt dependencies have been installed:
```
sudo apt-get install qtdeclarative5-dev-tools libqwt-qt5-dev qtmultimedia5-dev qtbase5-dev
```

4. To enable the tests, remember you have BOOST lib installed:
```
sudo apt install build-essential libboost-system-dev libboost-thread-dev libboost-program-options-dev libboost-test-dev
```

## First things first: Build the program:
```
mkdir build && cd build
cmake ..
make
```

### 1. Unit Tests
```
make test
```

### 2. Hue light bulb brightness control: How to use
If you are new user to Hue, this command will automatically set the light bulb ready for you, you just need press the physicall hue button:
```
./Hue new
```
Then press the Hue Bridge button, you will get the json reply, following is an example:
```
[{"success":{"username":"HmAE6GByMxd1-3Lufz77SJUTJhRgIEFQhvUkEa3E"}}]
```
The IP and username are stored in log.txt, you can just go to the last step to adjust the brightness.

If you want to modify your static IP or username, you can:
```
./Hue user HmAE6GByMxd1-3Lufz77SJUTJhRgIEFQhvUkEa3E
```
```
./Hue ip 192.168.0.112
```
You can also do:
```
./Hue ip 192.168.0.112 user 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
```
Or just modify the **log.txt**:
```
192.168.0.100 <Your Bridge IP here>
S7BnUlaWvwAs6dZgYErkLO8GAWdRHTdTGi1wxwL0 <Your username here>
```
to modify both IP and user mannually.

After set IP and username, adjust the brightness like this:
```
./Hue 200
```
**200** is brightness, integer, from 0-255, 0 means off.

### 3. MLX90640 main program: How to use:
```
sudo ./main
```

## Sequence diagram
<img src="https://github.com/Maripoforest/GestureHueLight/blob/main/sequence%20diagram%20for%20data%20transfer.png" width="500px">

## References
> [Sensor Github Page](https://github.com/melexis/mlx90640-library.git).

> [Sensor Datasheet](MLX90640-Datasheet-Melexis.pdf).

> [The Hue developer page](https://developers.meethue.com/).

> [The cURL Offical Page](https://https://curl.se/)

Command line tool and library for transferring data with URLs. (since 1998)

### Authors
 <a href="https://github.com/Maripoforest">Xiangmin Xu</a> <br/>
 <a href="https://github.com/rhythm232">Haiyang You</a> <br/>
 <a href="https://github.com/hjyyjh">Jiyuan He</a> <br/>


