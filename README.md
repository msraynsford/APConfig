# APConfig
A simple framework for creating an standalone access point for an ESP8266. 
Once connected to the device it is possible to change the SSID and Password from within a browser, it is also possible to reset the device should the password be forgotten.

# Connecting to the access point
When the micro controller device is connected to a power supply via a usb cable,
The ESP8266 will start a new WiFi connection called "APConfig XXXXXX". You should be able to find this network from your phone/laptop and connect to it using the password:'password'.

![alt text](https://github.com/msraynsford/APConfig/blob/master/WifiNetwork.png "Wifi List")

Once the connection has been established you can connect to the device through a browser using the default IP address http://192.168.4.1/

![alt text](https://github.com/msraynsford/APConfig/blob/master/Browser.png "Browser Image")


#Changing the SSID and Password
It is recommended to change the password for the WiFi network as soon as possible, there is a separate admin page that allows you to do this. If you navigate the browser to http://192.168.4.1/admin you will be presented with this page

![alt text](https://github.com/msraynsford/APConfig/blob/master/Admin.png "Admin Image")

This page allows you to change the password without entering the previous password because you already have to be connected to the WiFi using the existing password. 

#Connecting to the device without a password
If you forget the password it is still possible to connect to the device and update the SSID and password. When you turn the device on, the led will illuminate after 2 seconds and remain on for 1 second. 

![alt text](https://github.com/msraynsford/APConfig/blob/master/Device.png "Device Image")

If you press the reset button during this window the device will start a new wifi network called "APConfig". This network has no password so anybody can connect to it, the next time the device is turned on it will return to normal, passworded, operation.

![alt text](https://github.com/msraynsford/APConfig/blob/master/APConfig.png "APConfig Image")


