Google Analytics Wrapper / Googlytics
=============
**Googlytics for arduino**

A simple Google Analytics Wrapper Library inspired on [:: Arduinolitics :: Google Analytics on Arduino](http://www.instructables.com/id/-Arduinolitics-Google-Analytics-on-Arduino/) by PuZZleDucK.

It allows you to log events on Google Analytics in 2 lines of code.

Currently working only on **ESP8266** platform.

## Usage

```cpp
#include <Googlytics.h>
#define APP_VERSION 1

// Replace with your own Google Analytics Tracking Id
Googlytics ga("XX-000000000-0", APP_VERSION, ESP.getChipId());

void setup() {
  // Init WiFi stuff BEFORE
  // ...

  // Log some int value
  ga(Googlytics::PayloadType::event, "Category", "Action", "Label", millis());

  // Log some string value
  ga(Googlytics::PayloadType::event, "Category", "Action", "Use the label to store string value");
}

void loop() {}
```

Available payload types:

```
Googlytics::PayloadType::pageview
Googlytics::PayloadType::screenview
Googlytics::PayloadType::event
Googlytics::PayloadType::transaction
Googlytics::PayloadType::item
Googlytics::PayloadType::social
Googlytics::PayloadType::exception
Googlytics::PayloadType::timing
```

More details about Google Analytics parameters here:
https://developers.google.com/analytics/devguides/collection/protocol/v1/parameters


## TODO

- [x] Use HTTPS
- [ ] Add complete examples
- [ ] Improve memory usage
- [ ] Handle more GA parameters (Campaigns, etc.)
- [ ] Make it compatible with more platforms (Atmel, ESP32, etc.)
  - [ ] ESP32
  - [ ] Atmel
  - [ ] etc.
