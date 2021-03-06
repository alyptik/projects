/*
  Web Server

 A simple web server that shows the value of the analog input pins.
 using an Arduino Wiznet Ethernet shield.

 Circuit:
 * Ethernet shield attached to pins 10, 11, 12, 13
 * Analog inputs attached to pins A0 through A5 (optional)

 created 18 Dec 2009
 by David A. Mellis
 modified 9 Apr 2012
 by Tom Igoe
 modified 02 Sept 2015
 by Arturo Guadalupi

 */

#include <SD.h>
#include <SPI.h>
#include <Ethernet.h>

// Enter a MAC address and IP address for your controller below.
// The IP address will be dependent on your local network:
byte mac[] = {
  0xfe, 0xed, 0xde, 0xad, 0xbe, 0xef,
};
/* IPAddress ip(192, 168, 1, 126); */
File myFile;

// Initialize the Ethernet server library
// with the IP address and port you want to use
// (port 80 is default for HTTP):
EthernetServer server(80);

void setup()
{
  if (Serial)
    serialStart();

  // On the Ethernet Shield, CS is pin 4. It's set as an output by default.
  // Note that even if it's not used as the CS pin, the hardware SS pin
  // (10 on most Arduino boards, 53 on the Mega) must be left as an output
  // or the SD library functions will not work.
  pinMode(10, OUTPUT);

  // just to be safe, I disable the w5100 SPI while starting the SD SPI
  // I had problems in restarting without this in my FTP code
  digitalWrite(10, HIGH);

  // sets SD chip
  pinMode(4, OUTPUT);

  //disables SD chip
  //digitalWrite(4, HIGH);

  if (!SD.begin(4)) {
    if (Serial)
      Serial.println("initialization failed!");
    return;
  }
  Serial.println("initialization done.");

  if (SD.exists("example.txt")) {
    if (Serial)
      Serial.println("example.txt exists.");
  } else {
    if (Serial)
      Serial.println("example.txt doesn't exist.");
  }

  // open a new file and immediately close it:
  if (Serial)
    Serial.println("Creating example.txt...");
  myFile = SD.open("example.txt", FILE_WRITE);
  myFile.close();

  // Check to see if the file exists:
  if (SD.exists("example.txt")) {
    if (Serial)
      Serial.println("example.txt exists.");
  } else {
    if (Serial)
      Serial.println("example.txt doesn't exist.");
  }

  // delete the file:
  if (Serial)
    Serial.println("Removing example.txt...");
  SD.remove("example.txt");

  if (SD.exists("example.txt")){
    if (Serial)
      Serial.println("example.txt exists.");
  } else {
    if (Serial)
      Serial.println("example.txt doesn't exist.");
  }

  // so disable the w5100 SPI
  digitalWrite(10,HIGH);

  // start the Ethernet connection and the server:
  Ethernet.begin(mac);
  /* Ethernet.begin(mac, ip); */

  server.begin();
    if (Serial)
      serialEnd();
}


void loop()
{
  // listen for incoming clients
  EthernetClient client = server.available();
  if (client) {
    Serial.println("new client");
    // an http request ends with a blank line
    boolean currentLineIsBlank = true;
    boolean button_on[6] = {false, false, false, false, false, false};
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
              
            if (sensorReading == 0)
                button_on[analogChannel] = button_on[analogChannel] ? false : true;
                
            client.print("analog input ");
            client.print(analogChannel);
            client.print(" is ");
            client.print(sensorReading);
//            client.print(button_on[analogChannel] ? 0 : sensorReading);
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
    client.stop();
    Serial.println("client disconnected");
    Ethernet.maintain();
  }
}

void serialStart()
{
  // Open serial communications and wait for port to open:
  Serial.begin(9600);

  // wait for serial port to connect. Needed for native USB port only
  while (!Serial);
  Serial.print("Initializing SD card...");
}

void serialEnd()
{
  // print ip address
  Serial.print("server is at ");
  Serial.println(Ethernet.localIP());
}
