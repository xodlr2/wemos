#include <ESP8266WiFi.h>
 
// const char* ssid     = "Hello_IoT"; // Server
const char* ssid     = "athena-2F"; // Client
const char* password = "a7162008";
 
WiFiServer server(80); //Initialize the server on Port 80

int LED4 = 2;    // Use D4
//int LED3 = 0;    // Use D3

void setup() {
  // put your setup code here, to run once:

  Serial.begin(115200); //Start communication between the ESP8266-12E and the monitor window
  
  /* Server Start
  WiFi.mode(WIFI_AP); //Our ESP8266-12E is an AccessPoint 
  WiFi.softAP(ssid, password); // Provide the (SSID, password); 
  Server end */

  /* Client Start */
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
  /* Client end */ 
  server.begin(); // Start the HTTP Server
  Serial.println("Server started");
  
  /* Server Start
  IPAddress HTTPS_ServerIP= WiFi.softAPIP(); // Obtain the IP of the Server 

  Serial.println(" ");
  Serial.print("Server IP is: "); // Print the IP to the monitor window 
  Serial.println(HTTPS_ServerIP);
  Server end */
  
  /* Client Start */
  Serial.println(WiFi.localIP());
  /* Client end */ 
//  pinMode(LED3, OUTPUT);     // Initialize the LED pin as an output
  pinMode(LED4, OUTPUT);     // Initialize the LED pin as an output
  
}

void loop() {
  // put your main code here, to run repeatedly:

  WiFiClient client = server.available();
  if (!client) { 
    return; 
  } 
  //Looking under the hood 
  Serial.println("Somebody has connected :)");
  
  //Read what the browser has sent into a String class and print the request to the monitor
  String request = client.readStringUntil('\r'); 
  //Looking under the hood 
  Serial.println(request);
  
  // Handle the Request
  
  if (request.indexOf("/OFF") != -1){ 
    digitalWrite(LED4, HIGH); }
  else if (request.indexOf("/ON") != -1){ 
    digitalWrite(LED4, LOW); 
  }

  String s = "HTTP/1.1 200 OK\r\n";
  s += "Content-Type: text/html\r\n\r\n";
  s += "<!DOCTYPE HTML>\r\n<html>\r\n";
  s += "<br><input type=\"button\" name=\"b1\" value=\"Turn LED ON\" onclick=\"location.href='/ON'\">";
  s += "<br><br><br>";
  s += "<input type=\"button\" name=\"b1\" value=\"Turn LED OFF\" onclick=\"location.href='/OFF'\">";
  s += "</html>\n";
  
  client.flush(); //clear previous info in the stream
  client.print(s); // Send the response to the client
  delay(1);
  Serial.println("Client disonnected"); //Looking under the hood
  
//  digitalWrite(LED4, LOW);   // Turn the LED
//  digitalWrite(LED3, HIGH);   // Turn the LED
//  delay(1000);    // Wait for a seconds
//  digitalWrite(LED4, HIGH);  // Turn the LED
//  digitalWrite(LED3, LOW);   // Turn the LED
//  delay(1000);    // Wait for a seconds
}
