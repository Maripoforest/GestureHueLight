'''
Author: enwi(https://github.com/enwi)
Modified by: Xiangmin XU(https://github.com/Maripoforest)
Time: Feb.8.2022
File: hue.py
Describe: Light bulb communication methods in py, the bridge-detection is removed for a fixed ip and identifier connection.
'''

import requests
import socket
import json
import datetime
from time import sleep

AUTH_FAILURE_RETRIES = 6
AUTH_FAILURE_SLEEP = 10

class Hue:
    station_ip = "192.168.0.101"

    # Hue appears to expect your username to be a 32 character hash
    client_identifier = "5daQ2SXNSEGAoArorhImVWtK0VqvxTG0roB1vfQs"

    devicetype = "python-hue"
    last_update_state = None
    is_allowed = True
    state = {}
    lights = {}
    groups = {}
    schedules = {}
    config = {}

    def __init__(self, station_ip="192.168.0.101", client_identifier="5daQ2SXNSEGAoArorhImVWtK0VqvxTG0roB1vfQs"):
        self.station_ip = station_ip

        self.client_identifier = client_identifier

        self.get_state()

    def get_station_ip(self):
         ## Needs more error checking, currently assumes connection will work
         ## and that returns proper json.
         self.station_ip = requests.get('https://www.meethue.com/api/nupnp').json[0]

    def get_client_identifier(self, tries=AUTH_FAILURE_RETRIES):
        resp = requests.post("http://{}/api".format(self.station_ip), json={
            "devicetype":"python-hue#{}".format(socket.getfqdn())
        })
        data = resp.json()
        #try:
        print(data)
        #except KeyError, exc:
        #    logger.exception("Could not get client identifier")
        #    raise ClientException("Could not get client identifier")

        if isinstance(data, list) and data[0].get("error", None):
            if tries:
                sleep(AUTH_FAILURE_SLEEP)
                self.get_client_identifier(tries=tries-1)
            else:
                raise TooManyFailures()

        try:

            self.client_identifier = data[0]["success"]["username"]
        except KeyError:
            raise ClientException("No client identifier found in response")
        except IndexError:
            raise ClientException("No client identifier found in response")

    def request(self, *args, **kwargs):
        path = "http://%s/api/%s%s" % (
            self.station_ip,
            self.client_identifier,
            kwargs.get("path", ""),
        )
        method = kwargs.get("method", "GET")
        data = kwargs.get("data", None)

        ## Needs more error checking, currently assumes connection will work
        ## and that returns proper json.

        resp = requests.request(method, path, data=data)
        resp = json.loads(resp.content)

        if isinstance(resp, list) and resp[0].get("error", None):
            error = resp[0]["error"]
            if error["type"] == 1:
                ## Try to authenticate
                if self.authenticate():
                    return self.request(*args, **kwargs)
                else:
                    raise CouldNotAuthenticate()
        else:
            self.is_authenticated = True
            return resp

    def authenticate(self, tries=AUTH_FAILURE_RETRIES):
        path = "http://%s/api" % (
            self.station_ip
        )

        ## Needs more error checking, currently assumes connection will work
        ## and that returns proper json.
        auth = {
            "devicetype": self.devicetype,
            "username": self.client_identifier
        }

        resp = requests.post(path, data=json.dumps(auth))

        resp = json.loads(resp.content)

        if isinstance(resp, list) and resp[0].get("error", None):
            if tries:
                sleep(AUTH_FAILURE_SLEEP)
                self.authenticate()
            else:
                raise TooManyFailures()

        return True

    def get_state(self):
        self.last_resp = self.request()
        state = self.last_resp

        self.state = state
        self.config = state['config']
        self.schedules = state['schedules']
        self.groups = state['groups']

        for l in state['lights']:
            light = self.lights.get("l%s" % l, None)
            if not light:
                light = ExtendedColorLight(self, l)
                self.lights["l%s" % l] = light
            light.update_state_cache(state['lights'][l])

        self.last_update_state = datetime.datetime.now()

class ExtendedColorLight:
    last_status_time = None
    light_id = None
    state = {}
    hue = None

    def __init__(self, hue, light_id):
        self.hue = hue
        self.light_id = light_id

    def update_state_cache(self, values=None):
        if not values:
            values = self.hue.request(path="/lights/%s" % self.light_id)

        self.state.update(values)
        self.last_status_time = datetime.datetime.now()

    def set_state(self, state):
        self.hue.request(
            path="/lights/%s/state" % self.light_id,
            method="PUT",
            data=json.dumps(state))
        self.update_state_cache()
        return self

    def on(self, transitiontime=5):
        return self.set_state({"on": True, "transitiontime": transitiontime})

    def off(self, transitiontime=5):
        return self.set_state({"on": False, "transitiontime": transitiontime})


        return self.set_state(
            {"xy": [xyz[0], xyz[1]], "transitiontime": transitiontime})



class ClientException(Exception):
    pass

class TooManyFailures(ClientException):
    pass

class CouldNotAuthenticate(ClientException):
    pass
