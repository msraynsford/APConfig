#ifndef Config_H
#define Config_H

#include "EEPROMAnything.h"

#define MAX_STR_LEN 17
#define MIN_STR_LEN 17

#define SSID_DEFAULT "APConfig"
#define PASS_DEFAULT "password"

struct config_t{
  char ssid[MAX_STR_LEN] = SSID_DEFAULT;
  char pass[MAX_STR_LEN] = PASS_DEFAULT;
} config;

void InitConfig() {
  // Declare an area of eeprom where the variables are stored
  EEPROM.begin(sizeof(config));
}

// Writes the config values back to EEPROM
void SaveConfig() {
  Serial.printf("Save Config\n");

  // Store the new settings to EEPROM
  EEPROM_writeAnything(0,  config);    
  EEPROM.commit();
}

void ResetConfig() {
  Serial.printf("Reset Config\n");
  
  // If the EEROM isn't valid then create a unique name for the wifi
  sprintf(config.ssid, "%s %06X", SSID_DEFAULT, ESP.getChipId());
  sprintf(config.pass, PASS_DEFAULT);

  SaveConfig();
}

bool ValidateString(char* value) {
  bool valid = true;
  
  //Check to see if the string is an acceptable length
  if((strlen(value) < MIN_STR_LEN) && (strlen(value) >= MAX_STR_LEN)) {
    valid = false;
  }
  else {
    //Check each character in the string to make sure it is alphanumeric or space
    for(uint8_t i = 0; i < strlen(value); i++)
      if(!isAlphaNumeric(value[i]))
        if(!isSpace(value[i]))
          valid = false;
  }
  
  return valid;
}

// Loads the config values from EEPROM, leaves the default values if the EEPROM hasn't been set yet
void LoadConfig() {
  bool eepromValid = true;
  
  // Load the config variables from EEPROM
  config_t eepromConfig;
  EEPROM_readAnything(0, eepromConfig);

  //Check to see if the config variables loaded from eeprom are valid
  eepromValid &= ValidateString(eepromConfig.ssid);
  eepromValid &= ValidateString(eepromConfig.pass);

  if(eepromValid) {
    strcpy(config.ssid, eepromConfig.ssid);
    strcpy(config.pass, eepromConfig.pass);
  }  
  else {
    // If the EEROM isn't valid then create a unique name for the wifi
    ResetConfig();
    SaveConfig();
  }
}


// Sends a copy of the config values out to the serial port
void PrintConfig() {
  Serial.printf("SSID: '%s'\n", config.ssid);  
  Serial.printf("Pass: '%s'\n", config.pass);
}

#endif
