#include <WiFi.h>
#include <ESPAsyncWebServer.h>
#include <DHT.h>
#include <Adafruit_BMP085.h>
#include <SPIFFS.h>

#define LDR 33
#define DHT_PIN 5
#define DHT_TYPE DHT11

DHT dht(DHT_PIN, DHT_TYPE);
Adafruit_BMP085 bmp;

const char* ssid     = "TP-Link_FFBC";
const char* password = "sorriso0";

AsyncWebServer server(80);

void setup() {
  if (!SPIFFS.begin(true)) {
    Serial.println("An Error has occurred while mounting SPIFFS");
    return;
  }
  Serial.begin(115200);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
    String html = "<!DOCTYPE html>";
    html += "<html>";
    html += "  <head>";
    html += "    <meta charset='UTF-8'>";
    html += "    <link rel='icon' href='./icon.png' type='image/png'>";
    html += "    <title> Meteorology </title>";
    html += "    <style>";
    html += "      body {";
    html += "        text-align: center;";
    html += "        margin: 0;";
    html += "        height: 100%;";
    html += "      }";
    html += "      header {";
    html += "        background-color: lightblue;";
    html += "        font-size: 40px;";
    html += "        padding: 10px;";
    html += "      }";
    html += "      article{";
    html += "        font-size: 20px;";
    html += "        position: absolute;";
    html += "        top: 50%;";
    html += "        left: 50%;";
    html += "        -ms-transform: translate(-50%, -50%);";
    html += "        transform: translate(-50%, -50%);";
    html += "      }";
    html += "      footer {";
    html += "        background-color: grey;";
    html += "        position: absolute;";
    html += "        bottom: 0;";
    html += "        width: 100%;";
    html += "      }";
    html += "      img {";
    html += "        margin: 10px;";
    html += "      }";
    html += "    </style>";
    html += "    <script>";
    html += "     setInterval(function() {";
    html += "       var xhr = new XMLHttpRequest();";
    html += "       xhr.open('GET', '/sensors', true);";
    html += "       xhr.onreadystatechange = function() {";
    html += "         if (xhr.readyState == XMLHttpRequest.DONE && xhr.status == 200) {";
    html += "           var txt = xhr.responseText;";
    html += "           var txt = txt.split('/');";
    html += "           document.getElementById('temperature').innerHTML = txt[0];";
    html += "           document.getElementById('humidity').innerHTML = txt[1];";
    html += "           document.getElementById('luminosity').innerHTML = txt[2];";
    html += "           document.getElementById('atmospheric-pressure').innerHTML = txt[3];";
    html += "         }";
    html += "       };";
    html += "       xhr.send();";
    html += "     }, 1000);";
    html += "    </script>";
    html += "  </head>";
    html += "  <body>";
    html += "    <header> <strong> Weather Station </strong> </header>";
    html += "";
    html += "    <article>";
    html += "      <strong> Temperature: </strong>";
    html += "      <span id='temperature'> - oC </span> <br>";
    html += "      <strong> Humididty: </strong>";
    html += "      <span id='humidity'> -% </span> <br>";
    html += "      <strong> Luminosity: </strong>";
    html += "      <span id='luminosity'> -% </span> <br>";
    html += "      <strong> Atmospheric pressure: </strong>";
    html += "      <span id='atmospheric-pressure'> - Atm </span> <br>";
    html += "    </article>";
    html += "";
    html += "    <footer>";
    html += "      <a href='https://github.com/lucashudson2002/' target='_blank'>";
    html += "        <img src='github.png' alt='Link GitHub' width='75' height='75'>";
    html += "      </a>";
    html += "";
    html += "      <a href='https://www.linkedin.com/in/lucas-hudson-mg/' target='_blank'>";
    html += "        <img src='linkedin.png' alt='Link Linkedin' width='75' height='75'>";
    html += "      </a>";
    html += "    </footer>";
    html += "  </body>";
    html += "</html>";

    request->send(200, "text/html", html);
  });
  server.on("/sensors", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(200, "text/plain", String(dht.readTemperature()) + " oC/" + String(dht.readHumidity()) + " %/" + String(100.0*analogRead(LDR)/4096.0) + " %/" + String(bmp.readPressure()/101325.0) + " Atm");
  });
  server.serveStatic("/icon.png", SPIFFS, "/icon.png");
  server.serveStatic("/github.png", SPIFFS, "/github.png");
  server.serveStatic("/linkedin.png", SPIFFS, "/linkedin.png");
  server.begin();

  dht.begin();
  bmp.begin();
  pinMode(LDR, INPUT);
}

void loop() {
  Serial.print("Temperature: ");
  Serial.println(dht.readTemperature());
  Serial.print("Humidity: ");
  Serial.println(dht.readHumidity());
  Serial.print("Luminosity: ");
  Serial.println(100.0*analogRead(LDR)/4096.0);
  Serial.print("Atm: ");
  Serial.println(bmp.readPressure()/101325.0);
  Serial.println();
  delay(500);
}
