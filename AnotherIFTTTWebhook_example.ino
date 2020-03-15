// The MIT License
// 
// Copyright (c) 2020 Simon Ogden
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.

// ====================================================================
// ====================================================================
// Sample application using an adapted version of IFTTT Trigger
//
// How to use:
// 1. Place AnotherIFTTTWebhook.h in the same directory as your project
// 2. Add #include "AnotherIFTTTWebhook.h" to your main project file
// 3. Send webhook using function in main file:
//    send_webhook(EVENT, KEY, Value1, Value2, Value3);
//
// Visit me @ https://www.siytek.com
// ====================================================================
// ====================================================================

#include <Arduino.h>
#include <ESP8266WiFi.h>
#include "AnotherIFTTTWebhook.h"

// Set WiFi credentials
#define WIFI_SSID “YOUR SSID“
#define WIFI_PASS “YOUR PASSWORD“

// Set IFTTT Webhooks event name and key
#define IFTTT_Key "uCGRJ3uhsVRht-fPA6B_h"
#define IFTTT_Event "email"

void setup()
{
  // Setup serial port
  Serial.begin(115200);
  Serial.println();

  //Begin WiFi
  WiFi.begin(WIFI_SSID, WIFI_PASS);

  // Connecting to WiFi...
  Serial.print("Connecting to ");
  Serial.print(WIFI_SSID);
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(100);
    Serial.print(".");
  }

  // Connected to WiFi
  Serial.println();
  Serial.print("Connected! IP address: ");
  Serial.println(WiFi.localIP());

  // Send Webook to IFTTT
  send_webhook(IFTTT_Event,IFTTT_Key,"AnotherIFTTT","ESP device","Webhook");

}

void loop() {

  
  
  }
