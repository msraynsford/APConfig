# APConfig.ino

The main point of entry for the program, this simply sets up a web server to send data out to the browser and it creates the access point using date retrieved from the non volatile memory.
The setup function also checks the reset flag before deciding which network to create. The main loop of the program simple handles the webserver.

# AdminPage.h

The admin page file encapsulates the web page for the SSID and Password updater. It's a very small page so it was easier to store it all in program memory rather than the SPIFFS file system.
The webpage itself performs simple checks upon the submitted data using javascript, this makes sure that the incoming data is the right length and that the new passwords match.

# Config.h

The config functions deal with loading data to and from the non volatile memory. It is able to validate the loaded data to ensure that it makes sense and it will perform a reset of that information if it appears to be corrupted.
This is mainly done by validating the two strings, SSID and Password, to ensure that they meet the desired criteria such as min/max lengths and all alphanumeric characters.

# EEPROMAnything.h

Taken from the Arduino Playground these helper functions enable the reading/writing of any item to EEPROM as a single operation rather than having to set each bit individually. 
The only difference with the ESP8266 is that you have to call 'EEPROM.commit()' after writing the data to make sure it actually gets set to EEPROM.

# FirmwareReset.h

These functions use the ticker library which calls back a function at some time in the future. 3 seconds after reset a flag is set in the non volatile memory, 1 second later the flag is cleared, the built in LED is illuminated during this window
If the device resets and the flag is still set (ie the reset button was pushed during that window) the device performs an alternate boot sequence. In this case it launches a default access point with known SSID with no password. 