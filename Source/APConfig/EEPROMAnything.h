#ifndef EEPROMAnything_H
#define EEPROMAnything_H

#include <EEPROM.h>
#include <Arduino.h>  // for type definitions

// Converts any class to a byte array for writing to EEPROM
template <class T> int EEPROM_writeAnything(int ee, const T& value)
{
    const byte* p = (const byte*)(const void*)&value;
    unsigned int i;
    for (i = 0; i < sizeof(value); i++)
          EEPROM.write(ee++, *p++);
	  
    return i;
}

// Converts any class from a byte array for reading from EEPROM
template <class T> int EEPROM_readAnything(int ee, T& value)
{
    byte* p = (byte*)(void*)&value;
    unsigned int i;
    for (i = 0; i < sizeof(value); i++)
          *p++ = EEPROM.read(ee++);
    return i;
}

#endif
