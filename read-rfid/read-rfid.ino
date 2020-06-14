#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>
#include <String.h>
#include "wifi.h"

ESP8266WiFiMulti WiFiMulti;

void setup()
{
  Serial.begin(115200);
  for (uint8_t t = 4; t > 0; t--)
  {
    Serial.printf("[SETUP] WAIT %d...\n", t);
    Serial.flush();
    delay(1000);
  }
  WiFi.mode(WIFI_STA);
  WiFiMulti.addAP(ssid, password);
}

void loop()
{
  if (Serial.available() > 0)
  {
    String uid = Serial.readString(); // read the incoming byte:
    uid.replace("\n", "");
    uid.replace(" ", "");
    uid.replace("\t", "");
    Serial.println(uid);
    uid = host + "&key_name=" + uid;
    if ((WiFiMulti.run() == WL_CONNECTED))
    {

      WiFiClient client;
      HTTPClient http;
      Serial.print("[HTTP] begin...\n");
      if (http.begin(client, uid))
      { // HTTP
        Serial.print("[HTTP] GET...\n");
        // start connection and send HTTP header
        int httpCode = http.GET();

        // httpCode will be negative on error
        if (httpCode > 0)
        {
          // HTTP header has been send and Server response header has been handled
          Serial.printf("[HTTP] GET... code: %d\n", httpCode);

          // file found at server
          if (httpCode == HTTP_CODE_OK || httpCode == HTTP_CODE_MOVED_PERMANENTLY)
          {
            String payload = http.getString();
            Serial.println(payload);
          }
        }
        else
        {
          Serial.printf("[HTTP] GET... failed, error: %s\n", http.errorToString(httpCode).c_str());
        }

        http.end();
      }
      else
      {
        Serial.printf("[HTTP} Unable to connect\n");
      }
    }
    delay(100);
  }
}

int get_uid()
{
}

char *string_from_bytes(byte *buffer, byte bufferSize)
{
  byte_array(buffer, bufferSize);
  char str[(bufferSize) + 1];
  memcpy(str, buffer, bufferSize);
  str[bufferSize] = 0; // Null termination.
  Serial.println(str);
  return str;
}

void byte_array(byte *buffer, byte bufferSize)
{
  for (byte i = 0; i < bufferSize; i++)
  {
    Serial.print(buffer[i] < 0x10 ? " 0" : " ");
    Serial.print(buffer[i], HEX);
  }
}
