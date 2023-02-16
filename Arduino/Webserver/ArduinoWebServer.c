/*
Simpler Websever auf dem Arduino in kombination mitdem Ethernet Shield.
Der webserver Bringt eine HTML Standart-site auf der die Read-werte der pins: A0-A5, angezeigt werden 

Dokumentation basierend auf dem beispiel code von der arduino Docs seite; https://docs.arduino.cc/tutorials/ethernet-shield-rev2/web-server.
*/
//Doc Version:1.2
#include <SPI.h>
#include <Ethernet.h>

// Enter a MAC address and IP address for your controller below.
// Die IP Adresse die der Arduino erhalten sollte; sie sollte dem subnet des Netzwerks entsprechen! Der Arduino Fragt nicht nach DHCP!
byte mac[] = {
  0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED// Beispiel!
};
IPAddress ip(192, 168, 1, 177);// Beispiel!

EthernetServer server(80); // Initialisierung des Ethernet servers mit der <Ethernet.h> Bibliothek; Port 80 Ist standart für HTTP

void setup() {
  // Konfiguriere den ChipSelect pin für die verschiedenen Ethernet Module; Ethernet.init();
  //Ethernet.init(10);  // Most Arduino shields
  //Ethernet.init(5);   // MKR ETH shield
  //Ethernet.init(0);   // Teensy 2.0
  //Ethernet.init(20);  // Teensy++ 2.0
  //Ethernet.init(15);  // ESP8266 with Adafruit Featherwing Ethernet
  //Ethernet.init(33);  // ESP32 with Adafruit Featherwing Ethernet

  Serial.begin(9600); // Öffne den Seriellen kommunikations port 
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }
  Serial.println("Ethernet WebServer Example");

  // start the Ethernet connection and the server:
  Ethernet.begin(mac, ip);

  // Check for Ethernet hardware present
  if (Ethernet.hardwareStatus() == EthernetNoHardware) {
    Serial.println("Ethernet shield was not found.  Sorry, can't run without hardware. :(");
    while (true) {
      delay(1); // do nothing, no point running without Ethernet hardware
    }
  }
  if (Ethernet.linkStatus() == LinkOFF) {
    Serial.println("Ethernet cable is not connected.");
  }

  // start the server
  server.begin();
  Serial.print("server is at ");
  Serial.println(Ethernet.localIP());
}


void loop() {
  // listen for incoming clients
  EthernetClient client = server.available();
  if (client) {
    Serial.println("new client");
    // an http request ends with a blank line
    boolean currentLineIsBlank = true;
    while (client.connected()) {
      if (client.available()) {
        char c = client.read();
        Serial.write(c);
        // if you've gotten to the end of the line (received a newline
        // character) and the line is blank, the http request has ended,
        // so you can send a reply
        if (c == '\n' && currentLineIsBlank) {
          // send a standard http response header
          client.println("HTTP/1.1 200 OK");
          client.println("Content-Type: text/html");
          client.println("Connection: close");  // the connection will be closed after completion of the response
          client.println("Refresh: 5");  // refresh the page automatically every 5 sec
          client.println();
          client.println("<!DOCTYPE HTML>");
          client.println("<html>");
          // output the value of each analog input pin
          for (int analogChannel = 0; analogChannel < 6; analogChannel++) {
            int sensorReading = analogRead(analogChannel);
            client.print("analog input ");
            client.print(analogChannel);
            client.print(" is ");
            client.print(sensorReading);
            client.println("<br />");
          }
          client.println("</html>");
          break;
        }
        if (c == '\n') {
          // you're starting a new line
          currentLineIsBlank = true;
        } else if (c != '\r') {
          // you've gotten a character on the current line
          currentLineIsBlank = false;
        }
      }
    }
    // give the web browser time to receive the data
    delay(1);
    // close the connection:
    client.stop(); //stoppt den Client
    Serial.println("client disconnected");
  }
}
