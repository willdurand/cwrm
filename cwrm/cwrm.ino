#include <ESP8266WiFi.h>         //https://github.com/esp8266/Arduino
#include <DNSServer.h>
#include <ESP8266WebServer.h>
#include "cwrm_generated.h"

#define FOCUS_PIN     0
#define SHUTTER_PIN   2
#define FOCUS_DELAY   800
#define SHUTTER_DELAY 1200
#define WEB_PORT      80
#define DNS_PORT      53
#define AP_PASSWORD   "LetMeJoin"

#define DEBUG

#ifdef DEBUG
#define DEBUG_PRINT(message) Serial.println(message)
#else
#define DEBUG_PRINT(message)
#endif

// prototypes
void setup();
void loop();
void indexAction();
void redirectTo(String);
void triggerFocus();
void triggerShutter();

// global vars
IPAddress apIP(192, 168, 10, 1);
ESP8266WebServer webServer(WEB_PORT);
DNSServer dnsServer;

void setup() {
  pinMode(FOCUS_PIN, OUTPUT);
  pinMode(SHUTTER_PIN, OUTPUT);
  digitalWrite(FOCUS_PIN, LOW);
  digitalWrite(SHUTTER_PIN, LOW);

#ifdef DEBUG
  Serial.begin(115200); // open serial
#endif

  WiFi.mode(WIFI_AP);
  WiFi.softAPConfig(apIP, apIP, IPAddress(255, 255, 255, 0));
  WiFi.softAP(AP_NAME, AP_PASSWORD);

  // if DNSServer is started with "*" for domain name, it will reply with
  // provided IP to all DNS request
  dnsServer.start(DNS_PORT, "*", apIP);

  webServer.on("/", HTTP_GET, indexAction);
  webServer.on("/trigger/shutter", HTTP_POST, triggerShutter);
  webServer.on("/trigger/focus", HTTP_POST, triggerFocus);
  webServer.onNotFound([]() {
    redirectTo("/");
  });
  webServer.begin();
}

void loop() {
  dnsServer.processNextRequest();
  webServer.handleClient();
}

void indexAction() {
  webServer.send(200, "text/html", indexHTML);
}

void redirectTo(String path) {
  webServer.sendHeader("Location", "http://" + apIP.toString() + path);
  webServer.send(302);
}

void triggerFocus() {
  redirectTo("/");

  DEBUG_PRINT("Focus: start");
  digitalWrite(FOCUS_PIN, HIGH);
  delay(FOCUS_DELAY);
  DEBUG_PRINT("Focus: stop");
  digitalWrite(FOCUS_PIN, LOW);
}

void triggerShutter() {
  redirectTo("/");

  DEBUG_PRINT("Shutter: start");
  digitalWrite(SHUTTER_PIN, HIGH);
  delay(SHUTTER_DELAY);
  DEBUG_PRINT("Shutter: stop");
  digitalWrite(SHUTTER_PIN, LOW);
}
