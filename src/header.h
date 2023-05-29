#include <Arduino.h>
#include <ESP32Servo.h>
#include <Wire.h>
#include <FirebaseESP32.h>
#include <WiFi.h>
#include <time.h>
#include <NTPClient.h>
#include "HX711.h"
#include "SPI.h"
#include "Adafruit_SSD1306.h"
#include "Adafruit_GFX.h"

// UltraSonic Depan [1]
#define TRIG_PIN_1 14
#define ECHO_PIN_1 27
long duration_1, distance_1;

// UltraSonic Atas [2]
#define TRIG_PIN_2 12
#define ECHO_PIN_2 13
long duration_2, distance_2;

// Servo
Servo servo;
#define SERVO_PIN 4

// HX711
#define LOADCELL_DOUT_PIN 15
#define LOADCELL_SCK_PIN 18

// OLED
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

// UltraSonic settings
#define distance 10
#define height 100
#define SOUND_SPEED 0.034
#define CM_TO_INCH 0.393701

// Firebase
#define FIREBASE_HOST "https://tes-tr-default-rtdb.asia-southeast1.firebasedatabase.app/"
#define FIREBASE_AUTH "AIzaSyBXb8EPlBbozidWseN3gTlJc1V89YG8bVE"
#define WIFI_SSID "Apek"
#define WIFI_PASSWORD "kelvin108"

FirebaseData firebaseData;
FirebaseJson json;
FirebaseJson rts;
HX711 scale;

WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP);
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);
String databasePath;

// Firebase nodes
String weightPath = "/weight";
String datePath = "/date";
String timePath = "/time";
String statusPath = "/status";
String percentPath = "/fullness";

// Parent node
String parentPath;

unsigned long sendDataPrevMillis = 0;
unsigned long timerDelay = 60000;

int distanceCm;
int percentage;
int weight;