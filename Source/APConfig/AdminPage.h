#ifndef AdminPage_h
#define AdminPage_h

const char adminPage[] PROGMEM = 
    "<html>"
      "<head>"
        "<style>input {font-size: 1.2em; width: 100%; max-width: 350px; display: block; margin: 5px auto; } </style>"
        "<script> function checkValid() { var password1 = document.getElementById('password1'); var password2 = document.getElementById('password2');"
        "if (password1.value != password2.value) { password2.setCustomValidity('Passwords must match'); } else { password2.setCustomValidity(''); }} </script>"
      "</head>"
      "<body>"
        "<form id='form' action='/admin' method='post'>"
          "<input name='newssid' type='text' minlength='8' maxlength='16' placeholder='New SSID'>"
          "<input name='newpassword' id='password1' type='password' minlength='8' maxlength='16' placeholder='New Password'>"
          "<input id='password2' type='password' minlength='8' maxlength='16' placeholder='Confirm Password' onchange='checkValid()'>"
          "<input type='submit' value='Update'>"
        "</form>"
      "</body>"
    "</html>";


//Creates a webpage that allows the user to change the SSID and Password from the browser
void serveAdmin(ESP8266WebServer *webServer) {
  String message;  
    
  // Check to see if we've been sent any arguments and instantly return if not
  if(webServer->args() == 0) {
    webServer->sendHeader("Content-Length", String(strlen(adminPage)));
    webServer->send(200, "text/html", adminPage);
  }
  else {      
    // Create a string containing all the arguments, send them out to the serial port
    // Check to see if there are new values (also doubles to check the length of the new value is long enough)
    if((webServer->arg("newssid").length() >= MIN_STR_LEN) &&
       (webServer->arg("newssid").length() < MAX_STR_LEN)) 
      webServer->arg("newssid").toCharArray(config.ssid, sizeof(config.ssid));

    if(webServer->arg("newpassword").length() < MAX_STR_LEN) 
      webServer->arg("newpassword").toCharArray(config.pass, sizeof(config.pass));
    
    // Store the new settings to EEPROM
    SaveConfig();
    PrintConfig();

    // Construct a message to tell the user that the change worked
    message = "New settings will take effect after restart";     

    // Reply with a web page to indicate success or failure
    message = "<html><head><meta http-equiv='refresh' content='5;url=/' /></head><body>" + message;
    message += "<br/>Redirecting in 5 seconds...</body></html>";
    webServer->sendHeader("Content-Length", String(message.length()));
    webServer->send(200, "text/html", message);
  } 
}
#endif
    

