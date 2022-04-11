# Smart Light Bulb Control via WiFi with Gesture <br />(Using Thermo Camera)
Use hand gesture to control the on/off of HUE light bulbs and adjust brightness.


## Introduction
Internet of things has been a major part in future homes. People like to control their house facilities without finding physical controllers or press buttons on the walls. Smarter remote control should be what we pursuit. 

In this project, we use thermo camera to identify human hands, according to different gestures we detect, LED statuses are changing between open/close/low brightness/high brightness. The whole process is real time, as the camera keeps on scanning and recognizing gestures.

The application is on Raspberry Pi **4b**, the sensor we use is Melexis **MLX90640** IR Array, the sensor communicates in **I2C** bus, the light bulb we use is **Philips Hue White Filament Regular A60 LED**.


## Project Flowchart
![](flowchart2.png)

## Prerequistes
**IMPORTANT** 
1. To clone the lib, don't forget the **--recursive** command to also clone the submodules.
```
git clone --recursive https://github.com/Maripoforest/Smart-Light-Bulb-Control-with-Gesture.git
```
This project has dependencies on [cURL](https://github.com/curl/curl.git) and [cpr](https://github.com/curl/curl.git) , the cpr submodule in lib will configure both for you.


2. To build cpr, we need the OPENSSL developer kit:
```
sudo apt-get install libssl-dev
```

3. To use the I2C bus, make sure the linux I2C dev library is installed:
```
sudo apt-get install libi2c-dev
```

##  Hue light bulb brightness control c++: How to use
At the very first beginning, make the executable:

```
mkdir build && cd build
cmake ..
make
```

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

## MLX90640 Sensor: How to use:
```
mkdir build && cd build
cmake ..
make
sudo ./event
```

## Diagram
<img src="https://github.com/Maripoforest/GestureHueLight/blob/main/sequence%20diagram%20for%20data%20transfer.png" width="500px">

## References
> [Sensor Github Page](https://github.com/melexis/mlx90640-library.git).

> [Sensor Datasheet](MLX90640-Datasheet-Melexis.pdf).

> [The Hue developer page](https://developers.meethue.com/).

> [The cURL Offical Page](https://https://curl.se/)

Command line tool and library for transferring data with URLs. (since 1998)


> [The cpr GitHub Page](https://github.com/libcpr/cpr)

cpr for C++ Requests, it is a simple wrapper around libcurl inspired by the excellent Python Requests project.


## Update
Feb.8.2022, added a python demo for wireless light bulb control. -Xiangmin XU (Removed by Xiangmin XU on Feb 25th)

Feb.25.2022, added a C++ demo for wireless light bulb control, this demo relies on lib [cURL](https://github.com/curl/curl.git) and lib [cpr](https://github.com/curl/curl.git) which simplifies the cURL lib. -Xiangmin XU


## Logo
<img src="https://github.com/Maripoforest/GestureHueLight/blob/main/logo.png" width="200px"  div al ign=center>

