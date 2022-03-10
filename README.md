# Smart Light Bulb Control via WiFi with Gesture <br />(Using Thermo Camera)
Use hand gesture to control the on/off of HUE light bulbs and adjust brightness.

## Introduction
Internet of things has been a major part in future homes. People like to control their house facilities without finding physical controllers or press buttons on the walls. Smarter remote control should be what we pursuit. 

In this project, we use thermo camera to identify human hands, according to different gestures we detect, LED statuses are changing between open/close/low brightness/high brightness. The whole process is real time, as the camera keeps on scanning and recognizing gestures.

The application is on Raspberry Pi **4b**, the sensor we use is Melexis **MLX90640** IR Array, the sensor communicates in **I2C** bus, the light bulb we use is **Philips Hue White Filament Regular A60 LED**.

## Project Flowchart
![](flowchart2.png)

##  Hue control c++: How to use
At the very first beginning, you should modify your Hue Bridge IP in HueOnandOFF.cpp, you can modify you user id if you know it, but it does not matter.

```
cd HueOnandOffCPP
mkdir build && cd build
cmake ..
make
```

If you have modified your user id, just simple:
```
./Hue <brightness(integer: 0-255)>
```

If you do not know your user id:
```
./Hue new
```
Then press the Hue Bridge button.

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

