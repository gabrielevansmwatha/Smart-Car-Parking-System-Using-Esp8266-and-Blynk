#define BLYNK_TEMPLATE_ID "TMPL2HBXlcPCU"
#define BLYNK_TEMPLATE_NAME "Car Parking"
#define BLYNK_AUTH_TOKEN "lI94-_83AHxPv8rozJhVhyfln-Bhi5Jp"
#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

// You should get Auth Token in the Blynk App.
char auth[] = BLYNK_AUTH_TOKEN;

// Your WiFi credentials.
char ssid[] = "Eagle!";
char pass[] = "123456789";

// LED widget virtual pins
#define LED_SLOT1 V1
#define LED_SLOT2 V2
#define LED_SLOT3 V3

// GPIO pins for IR sensors
const int IR_PIN1 = 5; // D1
const int IR_PIN2 = 4; // D2
const int IR_PIN3 = 0; // D3

// Parking slot status
bool slot1Available = true;
bool slot2Available = true;
bool slot3Available = true;

void setup() {
  Serial.begin(9600);
  Blynk.begin(auth, ssid, pass);


  // Set IR sensor pins as inputs
  pinMode(IR_PIN1, INPUT);
  pinMode(IR_PIN2, INPUT);
  pinMode(IR_PIN3, INPUT);

  // Update LED widgets on Blynk app
  updateLEDs();
}

void loop() {
  Blynk.run();

  // Read IR sensor values
  bool irVal1 = digitalRead(IR_PIN1);
  bool irVal2 = digitalRead(IR_PIN2);
  bool irVal3 = digitalRead(IR_PIN3);

  // Update slot availability based on IR sensor readings
  slot1Available = !irVal1; // Slot occupied if IR sensor is triggered
  slot2Available = !irVal2;
  slot3Available = !irVal3;

  // Update LED widgets on Blynk app and physical LEDs
  updateLEDs();

  delay(500); // Delay to prevent flickering
}

// Function to update LED widgets on Blynk app
void updateLEDs() {
  Blynk.virtualWrite(LED_SLOT1, slot1Available);
  Blynk.virtualWrite(LED_SLOT2, slot2Available);
  Blynk.virtualWrite(LED_SLOT3, slot3Available);
}