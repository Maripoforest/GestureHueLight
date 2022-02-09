'''
Author: Xiangmin XU/Dong CHEN
Time: Feb.8.2022
File: assign1
Describe: Assignment 1 for Course Digial Signal Processing
'''

from hue import Hue

def lighton():
    h = Hue()
    h.station_ip = '192.168.0.101'
    h.get_state()
    transition = 5

    #Turn off the light bulb

    h.lights['l1'].off()

    #Turn on the light bulb

    h.lights['l1'].set_state({
        "on": True,
        "bri": 10, #0-254
        "transitiontime": transition
    })

if __name__ == "__main__":
    lighton()
