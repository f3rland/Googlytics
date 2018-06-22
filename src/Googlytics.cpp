#include <Arduino.h>
#include "Googlytics.h"
#include <ESP8266WiFi.h>
#include <WiFiClientSecure.h>

void Googlytics::operator()(PayloadType payloadType, const char* payloadCategory, const char* payloadAction, const char* payloadLabel, int sensorValue = 0){
  // Macro to simplify code reading
  // Append a string
  #define s(x) payloadData += F(x)
  // Append a string + value
  #define sd(x,y) payloadData += F(x); payloadData += y

  // int tmpDeviceId = (_deviceId + (random(0,11) % 3));  // Simulate multiple clients

  // https://developers.google.com/analytics/devguides/collection/protocol/v1/parameters
  String payloadData = F("v=1"); // Protocol Version
  sd("&tid=", _token); // Tracking ID / Web Property ID
  sd("&t=", types[payloadType]);
  sd("&av=", _appVersion); // Application Version
  sd("&cid=", _deviceId); // Client ID
  sd("&ec=", payloadCategory); // Event Category
  sd("&ea=", payloadAction); // Event Action
  // sd("-", _deviceId);
  sd("&el=", payloadLabel); // Event Label
  sd("&ev=", sensorValue); // Event Value
  s("&ds=arduino");
  s("&ua=Arduino");
  s("&an=Googlytics");
  // s("&cn=Googlytics"); // Campaign Name
  // s("&cs=Googlytics"); // Campaign Source
  // sd("&ck=Googlytics", payloadAction); // Campaign Keyword
  // sd("&dl=Googlytics", payloadAction); // Document location URL

  GOOGLYTICS_DEBUG_PRINT(payloadData);

  sendPayloadData(payloadData);
}

void Googlytics::sendPayloadData(String payloadData) {

  if (WiFi.isConnected()) {

    if (http.begin(host, 443, F("/collect"), fingerprint)) {
      http.addHeader(F("Content-Type"), F("application/x-www-form-urlencoded"));
      http.POST(payloadData);
      http.end();

    } else {
      GOOGLYTICS_DEBUG_PRINT(F("error connecting.. just skipping a beat for now"));
    }

  } else {
    GOOGLYTICS_DEBUG_PRINT(F("no connection.. just skipping a beat for now"));
  }
}
