#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

#define USESERIAL
#define USELED

#include "Config.h"
#include "FirmwareReset.h"
#include "AdminPage.h"

ESP8266WebServer webServer(80);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);  Serial.printf("\nAP Config Demo\n");
    
  InitConfig();
  
  //Start the wifi with the required username and password
  WiFi.mode(WIFI_AP);

  LoadConfig();
  PrintConfig();

  //Check to see if the flag is still set from the previous boot
  if(checkResetFlag()) {
    //Do the firmware reset here
    Serial.printf("Reset Firmware\n");

    //Set the ssid to default value and turn off the password
    WiFi.softAP("APConfig", "", 1, false, 1);
  } 
  else {
    WiFi.softAP(config.ssid, config.pass, 1, false, 1);
  }

  //Serve a very basic page on the root url
  webServer.on("/", [](){
    webServer.send(200, "text/plain", "Hello World");
  });

  // Set up the admin page
  webServer.on("/admin", std::bind(serveAdmin, &webServer));
  webServer.begin();
}


void loop() {
  // put your main code here, to run repeatedly:
  webServer.handleClient();  
}



