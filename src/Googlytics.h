#ifndef GOOGLYTICS_H
#define GOOGLYTICS_H

#include <ESP8266HTTPClient.h>

#ifndef ANALYTICS_HOST
  #define ANALYTICS_HOST "www.google-analytics.com"
#endif

#ifndef ANALYTICS_FINGERPRINT
  #define ANALYTICS_FINGERPRINT "83:0E:B7:32:E9:C0:2A:F3:67:66:4F:A6:06:8B:CA:90:DC:14:90:31"
#endif

#ifdef DEBUG_GOOGLYTICS
  #define GOOGLYTICS_DEBUG_PRINT(x) Serial.println(x)
#else
  #define GOOGLYTICS_DEBUG_PRINT(x) void()
#endif

class Googlytics{
public:

  enum PayloadType {
    pageview    = 0,
    screenview  = 1,
    event       = 2,
    transaction = 3,
    item        = 4,
    social      = 5,
    exception   = 6,
    timing      = 7
  };

  Googlytics(const char* token, int appVersion, int deviceId) :
    _token(token), _appVersion(appVersion), _deviceId(deviceId) {};

  void operator()(PayloadType payloadType, const char* payloadCategory, const char* payloadAction, const char* payloadLabel, int sensorValue);

private:

  const char* types[PayloadType::timing + 1] = { "pageview", "screenview", "event", "transaction", "item", "social", "exception", "timing" };

  // Got using https://www.grc.com/fingerprints.htm
  const char* fingerprint = ANALYTICS_FINGERPRINT;
  const char* host        = ANALYTICS_HOST;

  const char* _token;
  int         _appVersion;
  int         _deviceId;

  HTTPClient  http;

  void sendPayloadData(String payloadData);
};

#endif
