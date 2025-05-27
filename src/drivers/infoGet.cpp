#include <WiFi.h>
#include <WiFiMulti.h>
#include <iostream>
#include <HTTPClient.h>
#include <string>
#include <json_parser.h>
#include <set>
#include <vector>
#include "secrets.h"
#include "infoGet.h"

const char* rootCert=\
"-----BEGIN CERTIFICATE-----\n"\
"MIIDrTCCA1OgAwIBAgIRAPJRaWCDqqraEYrae7upezEwCgYIKoZIzj0EAwIwOzEL\n"\
"MAkGA1UEBhMCVVMxHjAcBgNVBAoTFUdvb2dsZSBUcnVzdCBTZXJ2aWNlczEMMAoG\n"\
"A1UEAxMDV0UxMB4XDTI1MDQyODE3NDU1NloXDTI1MDcyNzE4NDU1M1owIjEgMB4G\n"\
"A1UEAxMXbGFwaS50cmFuc2l0Y2hpY2Fnby5jb20wWTATBgcqhkjOPQIBBggqhkjO\n"\
"PQMBBwNCAASn32oYtWvJZ7CsPhwHXYdOxEtqiMsBSPAF+QpmAita3kfYLyd3Y05S\n"\
"SAztZwQkXLFZ5tjczyCMdnJsMsM9HYPgo4ICTzCCAkswDgYDVR0PAQH/BAQDAgeA\n"\
"MBMGA1UdJQQMMAoGCCsGAQUFBwMBMAwGA1UdEwEB/wQCMAAwHQYDVR0OBBYEFMZ6\n"\
"tjl326PQdx91MJgyM5TFfIh6MB8GA1UdIwQYMBaAFJB3kjVnxP+ozKnme9mAeXvM\n"\
"k/k4MF4GCCsGAQUFBwEBBFIwUDAnBggrBgEFBQcwAYYbaHR0cDovL28ucGtpLmdv\n"\
"b2cvcy93ZTEvOGxFMCUGCCsGAQUFBzAChhlodHRwOi8vaS5wa2kuZ29vZy93ZTEu\n"\
"Y3J0MCIGA1UdEQQbMBmCF2xhcGkudHJhbnNpdGNoaWNhZ28uY29tMBMGA1UdIAQM\n"\
"MAowCAYGZ4EMAQIBMDYGA1UdHwQvMC0wK6ApoCeGJWh0dHA6Ly9jLnBraS5nb29n\n"\
"L3dlMS90eTgyZnFCMGhBdy5jcmwwggEDBgorBgEEAdZ5AgQCBIH0BIHxAO8AdgAS\n"\
"8U40vVNyTIQGGcOPP3oT+Oe1YoeInG0wBYTr5YYmOgAAAZZ9uF8XAAAEAwBHMEUC\n"\
"IGr2zWRoNPaaynQgo3LXLqmfbnNq9bn4gdxwhKnSubmZAiEA/l6P/k8aAYUJevJM\n"\
"SWG0sIHm4W9UkIEYKHRk4U2WU6YAdQAN4fIwK9MNwUBiEgnqVS78R3R8sdfpMO8O\n"\
"Qh60fk6qNAAAAZZ9uF8jAAAEAwBGMEQCIDc4XxDZGPu1U7Z82ctopiRkwXquQBFJ\n"\
"zX3Tu18SBjtaAiBO1B580fzAjaX9qvk7Cc9PHoKCFyZHcjFIYV1gFXZIgDAKBggq\n"\
"hkjOPQQDAgNIADBFAiEAtQa/2+GFxGquYK1kCCkEIP7tsWYs+LRQSCktRBPzngYC\n"\
"IAEsaRzX1bYru5pXfT7GRVvDQAZ40FUMBNeyXFSwkCgt\n"\
"-----END CERTIFICATE-----";

#define MAX_JSON_TOKENS 512
const String url="https://lapi.transitchicago.com/api/1.0/ttpositions.aspx?outputType=JSON&key="+String(apiKey);
WiFiClientSecure *client;

// using namespace std;
void setClock() {
  configTzTime("CDT",0, 0, "pool.ntp.org");

  Serial.print(F("Waiting for NTP time sync: "));
  time_t nowSecs = time(nullptr);
  while (nowSecs < 8 * 3600 * 2) {
    delay(500);
    Serial.print(F("."));
    yield();
    nowSecs = time(nullptr);
  }

  Serial.println();
  struct tm timeinfo;
  gmtime_r(&nowSecs, &timeinfo);
  Serial.print(F("Current time: "));
  Serial.print(asctime(&timeinfo));
}

WiFiMulti wifiMulti;
void wifiInit(){
	WiFi.mode(WIFI_STA);
	for(int i=0;i<sizeof(wifiInfo)/sizeof(*wifiInfo);i++)
		wifiMulti.addAP(wifiInfo[i][0],wifiInfo[i][0]);
  Serial.print("Waiting for WiFi to connect...");
  while((wifiMulti.run() != WL_CONNECTED)) {
    Serial.print(".");
  }
  Serial.println(" connected");
}

void clientInit(){
  client=new WiFiClientSecure;
  if(client){
    client -> setCACert(rootCert);
  } else {
    Serial.println("Failed to create WiFiClientSecure instance");
  }
}
void clientDestroy(){
  if(client){
    delete client;
    client = nullptr;
  }
}

void fetchStationIds() {
    HTTPClient https;
    https.begin(*client, url+"&rt=blue"); 

    int httpCode = https.GET();
    if (httpCode > 0) {
        String payload = https.getString();
        jparse_ctx_t jctx;
        json_tok_t tokens[MAX_JSON_TOKENS];
        std::set<int> stationIds;

        if (json_parse_start_static(&jctx, payload.c_str(), payload.length(), tokens, MAX_JSON_TOKENS) == OS_SUCCESS) {
            // Enter ctatt object
            if (json_obj_get_object(&jctx, "ctatt") == OS_SUCCESS) {
                // Enter route array
                int num_routes = 0;
                if (json_obj_get_array(&jctx, "route", &num_routes) == OS_SUCCESS && num_routes > 0) {
                    // Enter first route object
                    if (json_arr_get_object(&jctx, 0) == OS_SUCCESS) {
                        // Enter train array
                        int num_trains = 0;
                        if (json_obj_get_array(&jctx, "train", &num_trains) == OS_SUCCESS) {
                            for (int i = 0; i < num_trains; ++i) {
                                if (json_arr_get_object(&jctx, i) == OS_SUCCESS) {
                                    int staId = 0;
                                    if (json_obj_get_int(&jctx, "staId", &staId) == OS_SUCCESS) {
                                        stationIds.insert(staId);
                                    }
                                    json_arr_leave_object(&jctx);
                                }
                            }
                            json_obj_leave_array(&jctx);
                        }
                        json_arr_leave_object(&jctx);
                    }
                    json_obj_leave_array(&jctx);
                }
                json_obj_leave_object(&jctx);
            }
            json_parse_end_static(&jctx);
        }

        Serial.println("Station IDs with trains:");
        for (int id : stationIds) {
            Serial.println(id);
        }
    } else {
        Serial.printf("GET failed, error: %s\n", https.errorToString(httpCode).c_str());
    }
    https.end();
}
void fetchStationIdsTest() {
    wifiInit();
    clientInit();
    setClock();
    fetchStationIds();
    clientDestroy();
    Serial.println("Done fetching station IDs.");
}


// size_t writeFunction(void* ptr, size_t size, size_t nmemb, std::string* data) {
//     data->append((char*)ptr, size * nmemb);
//     return size * nmemb;
// }

// int main(int argc, char** argv) {
//     curl_global_init(CURL_GLOBAL_DEFAULT);
//     auto curl = curl_easy_init();
//     if (curl) {
//         curl_easy_setopt(curl, CURLOPT_URL, "http://lapi.transitchicago.com/api/1.0/ttpositions.aspx?key=0d10de258b5d4962b0e3e013fad674e6&rt=blue&outputType=JSON");
//         curl_easy_setopt(curl, CURLOPT_NOPROGRESS, 1L);
//         curl_easy_setopt(curl, CURLOPT_MAXREDIRS, 50L);
//         curl_easy_setopt(curl, CURLOPT_TCP_KEEPALIVE, 1L);

//         std::string response_string;
//         std::string header_string;
//         curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writeFunction);
//         curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response_string);
//         curl_easy_setopt(curl, CURLOPT_HEADERDATA, &header_string);

//         curl_easy_perform(curl);
//         cout << response_string;
//         curl_easy_cleanup(curl);
//         curl_global_cleanup();
//         curl = NULL;
//     }
// }