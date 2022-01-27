# LED Control With Gesture Using Thermo Camera
Use hand gesture to control the on/off of LEDs and adjust brightness.

## Introduction
Internet of things has been a major part in future homes. People like to control their house facilities without finding physical controllers or press buttons on the walls. Smarter remote control should be what we pursuit. 

In this project, we use thermo camera to identify human hands, according to different gestures we detect, LED statuses are changing between open/close/low brightness/high brightness. The whole process is real time, as the camera keeps on scanning and recognizing gestures.

The application is on Raspberry Pi **4b**, the sensor we use is Melexis **MLX90640** IR Array, the sensor communicates in **I2C** bus.

## References
> [Sensor Github Page](https://github.com/melexis/mlx90640-library.git).\n
> [Sensor Datasheet](MLX90640-Datasheet-Melexis.pdf).
