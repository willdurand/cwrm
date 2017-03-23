#include <ESP8266WiFi.h>         //https://github.com/esp8266/Arduino
#include <DNSServer.h>
#include <ESP8266WebServer.h>

#define FOCUS_PIN     0
#define SHUTTER_PIN   2
#define FOCUS_DELAY   800
#define SHUTTER_DELAY 1200
#define WEB_PORT      80
#define DNS_PORT      53
#define AP_NAME       "Canon WiFi Remote Module"
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
void indexHTML();
void redirectTo(String);
void triggerFocus();
void triggerShutter();

// global vars
IPAddress apIP(192, 168, 10, 1);
ESP8266WebServer webServer(WEB_PORT);
DNSServer dnsServer;

String responseHTML = "<!DOCTYPE html><title>"
                      AP_NAME
                      "</title><style>#focus-btn,#shutter-btn{background-color:#6a5acd;border:0;border-radius:5px;width:100%;max-width:250px;padding:10px;color:#fff;font-size:1rem}#focus-btn{background-color:#009688}#every-input{text-align:center;width:50px}button:disabled{opacity:.65;cursor:not-allowed}</style><body style=text-align:center><h1>"
                      AP_NAME
                      "</h1><p><button id=shutter-btn>take picture</button><p>Every <input id=every-input type=number value=5> seconds <button id=every-btn>start</button><p style=padding-top:1rem><button id=focus-btn>focus</button></p><script>!function(t,e){function n(t){return t&&e.XDomainRequest&&!/MSIE 1/.test(navigator.userAgent)?new XDomainRequest:e.XMLHttpRequest?new XMLHttpRequest:void 0}function o(t,e,n){t[e]=t[e]||n}var r=[\"responseType\",\"withCredentials\",\"timeout\",\"onprogress\"];t.ajax=function(t,a){function s(t,e){return function(){c||(a(void 0===f.status?t:f.status,0===f.status?\"Error\":f.response||f.responseText||e,f),c=!0)}}var u=t.headers||{},i=t.body,d=t.method||(i?\"POST\":\"GET\"),c=!1,f=n(t.cors);f.open(d,t.url,!0);var l=f.onload=s(200);f.onreadystatechange=function(){4===f.readyState&&l()},f.onerror=s(null,\"Error\"),f.ontimeout=s(null,\"Timeout\"),f.onabort=s(null,\"Abort\"),i&&(o(u,\"X-Requested-With\",\"XMLHttpRequest\"),e.FormData&&i instanceof e.FormData||o(u,\"Content-Type\",\"application/x-www-form-urlencoded\"));for(var p,m=0,v=r.length;v>m;m++)p=r[m],void 0!==t[p]&&(f[p]=t[p]);for(var p in u)f.setRequestHeader(p,u[p]);return f.send(i),f},e.nanoajax=t}({},function(){return this}())</script><script>var interval=!1,$shutterBtn=document.querySelector(\"#shutter-btn\"),$focusBtn=document.querySelector(\"#focus-btn\"),$everyInput=document.querySelector(\"#every-input\"),$everyBtn=document.querySelector(\"#every-btn\"),trigger=function(t,e){t.setAttribute(\"disabled\",\"disabled\"),nanoajax.ajax({url:e,method:\"POST\"},function(e,r){t.removeAttribute(\"disabled\")})},startInterval=function(){var t=parseInt($everyInput.value,10);NaN===t||t<1||(interval=setInterval(function(){trigger($shutterBtn,\"/trigger/shutter\")},1e3*t),$everyBtn.innerHTML=\"stop\")},stopInterval=function(){interval&&(clearInterval(interval),interval=!1,$everyBtn.innerHTML=\"start\")};$shutterBtn.addEventListener(\"click\",function(){trigger($shutterBtn,\"/trigger/shutter\")},!1),$focusBtn.addEventListener(\"click\",function(){trigger($focusBtn,\"/trigger/focus\")},!1),$everyBtn.addEventListener(\"click\",function(){if(interval)return void stopInterval();startInterval()},!1)</script>"
                      ;

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

  webServer.on("/", HTTP_GET, indexHTML);
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

void indexHTML() {
  webServer.send(200, "text/html", responseHTML);
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
