#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>
#include "InfluxDb.h"

#define INFLUXDB_HOST "Your IP"   // IP of container
#define INFLUXDB_PORT 31777       // Port for container
#define WIFI_SSID "SSID"
#define WIFI_PASS "Password"

ESP8266WiFiMulti WiFiMulti;

Influxdb influx(INFLUXDB_HOST, INFLUXDB_PORT);

void setup() {
  Serial.begin(115200);
  Serial.println(" Started InfluxDB test.... ");

  WiFiMulti.addAP(WIFI_SSID, WIFI_PASS);
  Serial.print("Connecting to WIFI");
  while (WiFiMulti.run() != WL_CONNECTED) {
    Serial.print(".");
    delay(100);
  }
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());

  influx.setDb("ESP8266Test01");

  // Test of 2nd approach
  //influx.setDbAuth("ESP8266Test01", INFLUXDB_USER, INFLUXDB_PASS);
  //influxdb.opendb(DATABASE, DB_USER, DB_PASSWORD);

  Serial.println("Setup done");

}

int loopCount = 0;

void loop() {
  loopCount++;

  InfluxData row("temperature");
  row.addTag("device", "alpha");
  row.addTag("sensor", "one");
  row.addTag("mode", "pwm");
  row.addValue("loopCount", loopCount);
  row.addValue("value", random(10, 40));

  influx.write(row);

  delay(5000);
  
}
