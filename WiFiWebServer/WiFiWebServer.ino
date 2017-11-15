
#include <ESP8266WiFi.h>
#include <Wire.h>
#include <ESP8266HTTPClient.h>
#include <Adafruit_PWMServoDriver.h>

Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver(0x41);
Adafruit_PWMServoDriver pwm1 = Adafruit_PWMServoDriver(0x40);

#define SERVOMIN 150
#define SERVOMAX 600

const char* ssid = "robotic-lab-3";
const char* password = "deepblue69";

WiFiServer server(80);
WiFiClient client;

void setup() {
  Serial.begin(115200);
  delay(10);

  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  
  WiFi.begin(ssid, password);
  pinMode(LED_BUILTIN, OUTPUT);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
  
  // Start the server
  server.begin();
  Serial.println("Server started");
  // Print the IP address
  IPAddress ip_address = WiFi.localIP();
  Serial.println(ip_address);

  String ip_send = "http://whatever.beer/init.php?body=";
  ip_send += ip_address.toString();
  HTTPClient http;
  http.begin(ip_send);
  int httpCode = http.GET();
  if (httpCode > 0){
    String payload = http.getString();
    Serial.println(payload);
  }
  Serial.printf("Sentmsg: status %d", httpCode);
  http.end();
  
  pwm.begin();
  pwm.setPWMFreq(60);

  pwm1.begin();
  pwm1.setPWMFreq(60);
  yield();
  sit();
}

void  setServoPulse(uint8_t n, double pulse)
{
  double pulselen;

  pulselen = 1000000;
  pulselen /= 60;
  Serial.print(pulselen);
  pulselen /= 4096;
  Serial.print(pulselen);
  pulse *= 1000;
  pulse /= pulselen;
}

int   down = 0;
int   right_wave = 0;
int   left_wave = 0;
int   raand = 0;
int up = 0;

void loop() {
  LED();
  // Check if a client has connected
  WiFiClient client = server.available();
  if (!client) {
    return;
  }
  
  // Wait until the client sends some data
  while(!client.available()){
    delay(1);
  }
  Serial.println("new client");
  
  // Read the first line of the request
  String req = client.readStringUntil('\r');
  Serial.println(req);
  //client.flush();
  
  // Match the request
  String val;
  if (req.indexOf("/nod") != -1){
    nod();
    val = "Nodding Head";
  }
  else if (req.indexOf("/center") != -1){
    sit();
    val = "Center";
  }
  else if (req.indexOf("/hands_up") != -1){
    hands_up(&down, &up, &right_wave, &left_wave);
    val = "Hands Are Up";
  }
  else if (req.indexOf("/look_right") != -1){
    twist_left();
    val = "Looking Left";
  }
  else if (req.indexOf("/look_left") != -1){
    twist_right();
    val = "Looking Right";
  }
  else if (req.indexOf("/hands_down") != -1){
    Serial.println(left_wave);
    hands_down(&down, up, right_wave, left_wave);
    val = "Hands Are Down";
    raand = 0;
  }
  else if(req.indexOf("/wave_left") != -1){
    wave_left_hand(&left_wave);
    val = "Left Hand Waving";
    raand = 0;
  }
  else if (req.indexOf("/wave_right") != -1){
    wave_right_hand(&right_wave);
    val = "Right Hands Waving";
    raand = 0;
  }
  else{
    Serial.println("invalid request");
    client.stop();
    return;
  }

  if (req.indexOf("/wave_right") != -1){
    wave_right_hand(&right_wave);
    val = "Right Hands Waving";
    raand = 0;
  }
  //client.flush();

  // Prepare the response
  String s = "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n<!DOCTYPE HTML>\r\n<html>\r\n ";
  s += val;
  s += "</html>\n";

  // Send the response to the client
  client.print(s);
  client.stop();
  delay(1);
  Serial.println("Client disonnected");
  
  // The client will actually be disconnected 
  // when the function returns and 'client' object is detroyed
  
}

