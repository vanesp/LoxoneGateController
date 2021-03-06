Loxone Gate Controller
======================

I have a Beninca Brainy gate controller at 230V (https://www.beninca.com/en/accessories/control-panels/swinging-gates.html), with a number of Beninca ToGo WP remote controllers. Originally I intended to create Loxone control using a Sonoff SV relay over Wifi. However, I found out that the Wifi range did not extend all the way out to the gate.

I then looked at the remotes. The ToGo WP is fitted with a fixed code, 433.92MHz remote. It's
settings are done using DIP switches. Opening up I found a Holtec HT12E encoder chip. https://www.holtek.com/productdetail/-/vg/2_12e

rc-switch
---------

This Arduino library (https://github.com/sui77/rc-switch) provides the ability to analyse and 
control 433 MHz ASK / on-off-keying applications. With the library I was able to decode the sequence sent by my keyfob, and emulate it.

Nodo-Arduino-Small
------------------

From earlier experiments I still had A Nodo-Arduino-Small board lying around, with an Aurel RX-4MS receiver and a TX-4MSIL transmitter. Some of the better performing units in the field.
(http://www.nodo-domotica.nl/nodoinfo.html). A small program, based on rcc-switch code is installed on that Nodo. It monitors one of it's GPIO pins (number 7), and if that pin goes high, it transmits the RF code. When the pin goes down, it stops transmitting the code.

Adafruit Huzzah ESP8266 breakout
--------------------------------

This simple breakout board is flashed with the Tasmota software. https://github.com/arendst/Tasmota It is given a fixed ip address (.55) based on it's MAC address in my dhcp server.

The configuration template is as follows:

    {"NAME":"Huzzah","GPIO":[255,255,255,255,6,5,0,0,255,255,255,255,255],"FLAG":1,"BASE":18}

This means that GPIO pin 12 is coupled to "Relay1" and is switched ON or OFF with the button on the web-interface.

GPIO pin 13 is linked to a LED1 pin (but not used).

Connections
-----------

    Huzzah              Nodo Arduino Small
    pin 13              pin 7 (relay pin of Huzzah is detection pin of NAS)
    pin Vbat            pin 1 (+VCC)
    pin GND             pin 28 (GND)

Loxone Configuration
--------------------

In Loxone a normal Gate Controller is used (and added to the visualisation), with a single Toggle (virtual) output.

![Gate Controller](img/gatecontrol.png)

The details of the gatecontroller and visualisation are as follows:

![Gate Controller Parameters](img/gate.png)

The output (VQ) is a Toggle switch.

![VQ Toggle](img/virtualout.png)

Which is only linked to the fixed IP address of the Adafruit Huzzah with Tasmota

![Output](img/virtout.png)

There the Tasmota HTTP webrequests take the form of:

    http://<ip>/cm?cmnd=Power%20On
    http://<ip>/cm?cmnd=Power%20Off

And the gate parameters ensure that the duration they are on is 2 seconds, enough for a 433 MHz remote control to train (it sends the commands in batches of 16 repeats anyway).
    
![Commands](img/togglecommand.png)


