#include <WiFi.h>
#include <WiFiMulti.h>
#include <iostream>
#include <HTTPClient.h>
#include <string>
#include <json_parser.h>
#include <set>
#include <vector>
#include "secrets.h"

extern void setClock();
extern WiFiMulti wifiMulti;
extern void wifiInit();
extern void clientInit();
extern void clientDestroy();
extern void fetchStationIds();