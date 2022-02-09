'''
Author: Xiangmin XU(https://github.com/Maripoforest)/Haiyang YOU
Time: Feb.8.2022
File: lightonoff.py
Describe: Adjust the state of a light bulb: on/off and brightness
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
