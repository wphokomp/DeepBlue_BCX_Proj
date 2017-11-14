
#include <ESP8266WiFi.h>
#include <Wire.h>
#include <ESP8266HTTPClient.h>
#include <Adafruit_PWMServoDriver.h>

Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver(0x41);
Adafruit_PWMServoDriver pwm1 = Adafruit_PWMServoDriver(0x40);

#define SERVOMIN 150
#define SERVOMAX 600

const char* ssid = "ASUS";
const char* password = "";

WiFiServer server(80);
/*
void straight(){
  pwm1.setPWM(11, 0, 160);
  pwm1.setPWM(10, 0, 120);
  pwm1.setPWM(9, 0, 140);
  pwm1.setPWM(8, 0, 260);
   
  pwm.setPWM(11, 0, 140);//140
  pwm.setPWM(10, 0, 120);//120
  pwm.setPWM(9, 0, 280);//260/500/
  pwm.setPWM(8, 0, 180);//180
}
*/
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
  spine();
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
void loop() {
  LED();
  // Check if a client has connected
  WiFiClient client = server.available();
  if (!client) {
    return;
  }
  
  // Wait until the client sends some data
  Serial.println("new client");
  while(!client.available()){
    delay(1);
  }
  
  // Read the first line of the request
  String req = client.readStringUntil('\r');
  Serial.println(req);
  client.flush();
  
  // Match the request
  String val;
  if (req.indexOf("/hands_up") != -1){
    hands_up();
    val = "Hands Are Up";
  }
  else if (req.indexOf("/hands_down") != -1){
    hands_down(&down);
    val = "Hads Are Down";
    raand = 0;
  }
  else if(req.indexOf("/wave_left") != -1){
    wave_left_hand(&right_wave);
    val = "Left Hand Waving";
    raand = 0;
  }
  else if (req.indexOf("/neck") != -1){
    val = "Neck Test";
    neck();
  }
  else if (raand == 5000){
    Serial.println("invalid request");
    client.stop();
    return;
  }
  client.flush();

  // Prepare the response
  String s = "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n<!DOCTYPE HTML>\r\n<html>\r\n ";
  s += val;
  s += "</html>\n";

  // Send the response to the client
  client.print(s);
  delay(1);
  Serial.println("Client disonnected");
  
  // The client will actually be disconnected 
  // when the function returns and 'client' object is detroyed
  /*raand++;
  if (raand > 500000){
    idle();
  }*/
}

