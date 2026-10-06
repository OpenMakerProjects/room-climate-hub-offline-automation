#include <Arduino.h>
#include <WiFi.h>
#include <WebServer.h>
#include "policy.h"
constexpr uint8_t DOOR=27,LIGHT=34,R=25,G=26,B=33;
OfflinePolicy policy;WebServer server(80);int adc=0;uint32_t lastReport=0;
String statusJson(){
 char out[210];
 snprintf(out,sizeof(out),"{\"id\":6,\"door_open\":%s,\"light_raw\":%d,\"dark\":%s,\"fault\":%s,\"rgb\":[%u,%u,%u]}",
 policy.doorOpen?"true":"false",adc,policy.dark?"true":"false",policy.fault?"true":"false",policy.red,policy.green,policy.blue);return String(out);
}
void setup(){
 Serial.begin(115200);pinMode(DOOR,INPUT_PULLUP);analogReadResolution(12);analogSetPinAttenuation(LIGHT,ADC_11db);
 ledcSetup(0,5000,8);ledcSetup(1,5000,8);ledcSetup(2,5000,8);
 ledcAttachPin(R,0);ledcAttachPin(G,1);ledcAttachPin(B,2);ledcWrite(0,0);ledcWrite(1,0);ledcWrite(2,0);
 WiFi.mode(WIFI_AP);WiFi.softAP("OMP-Offline-006");
 Serial.print("Lab-only open access point IP: ");Serial.println(WiFi.softAPIP());
 server.on("/",HTTP_GET,[]{server.send(200,"text/plain","Offline Automation: GET /api/status. Read-only lab demo.");});
 server.on("/api/status",HTTP_GET,[]{server.send(200,"application/json",statusJson());});server.begin();
}
void loop(){
 adc=analogRead(LIGHT);uint32_t now=millis();policy.update(digitalRead(DOOR)==HIGH,adc,now);
 ledcWrite(0,policy.red);ledcWrite(1,policy.green);ledcWrite(2,policy.blue);
 server.handleClient();if(uint32_t(now-lastReport)>=1000){lastReport=now;Serial.println(statusJson());}
 delay(5);
}
