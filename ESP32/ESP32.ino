#include <Tello.h>

#include <Tello.h>
#include "MPU6050.h"      //libs importing
#include "Wire.h"
#include "I2Cdev.h"

MPU6050 mpu;              //creating mpu object of the MPU6050 class
int16_t ax, ay, az;       //gyro axis variable declarations
int16_t gx, gy, gz;

struct MyData {
  byte X;                 //creating a structure storing the X and Y fields
  byte Y;
};

MyData data;              //creating a data object of the MyData data type

// SSID and password:
const char * networkName = "TELLO-??????";
const char * networkPswd = "";
boolean connected = false;

Tello tello;              //creating tello object

const int up = 27;
const int down = 4;
const int left = 5;       //pin numbering of voice commands
const int right = 18; 
const int fwd = 17;
const int backward = 16;

void setup()
{
  Serial.begin(115200);     //opening the serial port

  pinMode(up, INPUT_PULLDOWN);
  pinMode(down, INPUT_PULLDOWN);
  pinMode(left, INPUT_PULLDOWN);      //pin setting as input, with pull-down resistor
  pinMode(right, INPUT_PULLDOWN);
  pinMode(fwd, INPUT_PULLDOWN);
  pinMode(backward, INPUT_PULLDOWN);

  Wire.begin();
  mpu.initialize();                   //I2C bus configuration
  connectToWiFi(networkName, networkPswd);
}

void loop()
{
  if (connected) {
    mpu.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);
    data.X = map(ax, -17000, 17000, 0, 100); //mapping X axis values
    data.Y = map(ay, -17000, 17000, 0, 100); //mapping Y axis values

    delay(10);

    int upstate = digitalRead(up);
    int downstate = digitalRead(down);
    int leftstate = digitalRead(left);        //pin states readings
    int rightstate = digitalRead(right);
    int forwardstate = digitalRead(fwd);
    int backwardstate = digitalRead(backward);

    int height = tello.getHeight();         //current height saved to a variable
    delay(10);

    if (upstate == 1) {
      tello.sendRCcontrol(0, 0, 50, 0);     //increasing flight altitude - up command
      delay(1000);
    }

    if (downstate == 1 and height < 3) {
      tello.land();                        //landing - command down, below 3dm
      delay(5000);
    }

    if (downstate == 1 and height > 2) {
      tello.sendRCcontrol(0, 0, -40, 0);  //flight descent - command down, above 2 dm
      delay(2000);
    }

    if (leftstate == 1) {
      tello.sendRCcontrol(0, 0, 0, -40);    //cw
      delay(500);

    }

    if (rightstate == 1) {
      tello.sendRCcontrol(0, 0, 0, 40);     //ccw
      delay(500);
    }

    if (forwardstate == 1) {
      delay(100);
      tello.flip_front();                 //frontflip
      delay(500);
    }

    if (backwardstate == 1) {
      delay(100);
      tello.flip_back();                  //abackflip
      delay(500);
    }

    if (data.Y < 35) {
      tello.sendRCcontrol(-70, 0, 0, 0);    //fly left
      delay(100);
    }

    if (data.Y > 65) {
      tello.sendRCcontrol(70, 0, 0, 0);     //fly right
      delay(100);
    }

    if (data.X > 55) {
      tello.sendRCcontrol(0, -70, 0, 0);     //fly backward
      delay(100);
    }

    if (data.X < 35) {
      tello.sendRCcontrol(0, 70, 0, 0);      //fly forward
      delay(100);
    }

    if (data.X > 40 and data.X < 50 and data.Y < 60 and data.Y > 40) {
      tello.sendRCcontrol(0, 0, 0, 0);        //hold the position
      delay(100);
    }
  }
}

void connectToWiFi(const char * ssid, const char * pwd)
{
  Serial.println("Connecting to WiFi network " + String(ssid));
  WiFi.disconnect(true);
  WiFi.onEvent(WiFiEvent);
  WiFi.begin(ssid, pwd);
  Serial.println("Waiting for connection...");
}

void WiFiEvent(WiFiEvent_t event)
{
  switch (event)
  {
    case SYSTEM_EVENT_STA_GOT_IP:
      Serial.print("WiFi connected! IP address: ");
      Serial.println(WiFi.localIP());
      tello.init();
      delay(500);
      connected = true;
      tello.takeoff();        //takeoff procedure when an IP address is obtained
      delay(2000);
      break;

    case SYSTEM_EVENT_STA_DISCONNECTED:
      Serial.println("WiFi lost connection");     //connection lost
      connected = false;
      break;
  }
}
