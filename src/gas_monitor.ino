/*
 * IoT Based Hazardous Gas Monitoring System
 *
 * This project detects hazardous gases using MQ2 sensor and sends
 * real-time alerts to smartphone via Blynk app.
 *
 * Hardware:
 * - NodeMCU ESP8266
 * - MQ2 Gas Sensor
 * - Buzzer
 * - Green LED (indicates gas detected)
 * - Red LED (indicates normal operation)
 *
 * Authors: Shruti Verma, Prajwal Rajput
 * Date: 2020
 *
 * Pin Connections:
 * - A0: MQ2 Sensor Analog Output
 * - D1: Buzzer (via transistor)
 * - D5: Green LED
 * - D6: Red LED
 */

#define BLYNK_PRINT Serial

#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

// ============== CONFIGURATION ==============
// Replace with your Blynk Auth Token
char auth[] = "YOUR_BLYNK_AUTH_TOKEN";

// Replace with your WiFi credentials
char ssid[] = "YOUR_WIFI_SSID";
char pass[] = "YOUR_WIFI_PASSWORD";

// ============== PIN DEFINITIONS ==============
#define SENSOR_PIN    A0    // MQ2 sensor analog pin
#define BUZZER_PIN    D1    // Buzzer pin
#define LED_GREEN     D5    // Green LED - Gas detected
#define LED_RED       D6    // Red LED - Normal operation

// ============== CONSTANTS ==============
#define SENSOR_LIMIT  200   // Gas threshold value (0-1023)
#define DELAY_TIME    100   // Delay between readings (ms)

// ============== GLOBAL VARIABLES ==============
int sensorValue = 0;
bool alertSent = false;

// ============== BLYNK TIMER ==============
BlynkTimer timer;

/*
 * Function: sendSensorData
 * Description: Reads sensor value and sends to Blynk app
 */
void sendSensorData() {
  // Read gas sensor value
  sensorValue = analogRead(SENSOR_PIN);

  // Print to Serial Monitor
  Serial.print("Gas Level: ");
  Serial.println(sensorValue);

  // Send to Blynk app on Virtual Pin V1
  Blynk.virtualWrite(V1, sensorValue);

  // Check if gas level exceeds threshold
  if (sensorValue > SENSOR_LIMIT) {
    // Gas detected - DANGER!
    digitalWrite(LED_GREEN, HIGH);   // Turn ON green LED (danger indicator)
    digitalWrite(LED_RED, LOW);      // Turn OFF red LED
    digitalWrite(BUZZER_PIN, HIGH);  // Turn ON buzzer
    delay(DELAY_TIME);
    digitalWrite(BUZZER_PIN, LOW);   // Turn OFF buzzer after delay

    // Send notification only once per detection
    if (!alertSent) {
      Blynk.notify("ALERT: Gas Leakage Detected!");
      Serial.println("*** ALERT: Gas Leakage Detected! ***");
      alertSent = true;
    }
  }
  else {
    // Normal operation - SAFE
    digitalWrite(BUZZER_PIN, LOW);   // Buzzer OFF
    digitalWrite(LED_GREEN, LOW);    // Green LED OFF
    digitalWrite(LED_RED, HIGH);     // Red LED ON (system active)
    alertSent = false;               // Reset alert flag
  }
}

/*
 * Function: setup
 * Description: Initialize pins, serial communication, and Blynk
 */
void setup() {
  // Initialize Serial Communication
  Serial.begin(115200);
  Serial.println();
  Serial.println("================================");
  Serial.println("IoT Hazardous Gas Monitoring System");
  Serial.println("================================");

  // Initialize pin modes
  pinMode(SENSOR_PIN, INPUT);
  pinMode(BUZZER_PIN, OUTPUT);
  pinMode(LED_GREEN, OUTPUT);
  pinMode(LED_RED, OUTPUT);

  // Set initial states
  digitalWrite(BUZZER_PIN, LOW);
  digitalWrite(LED_GREEN, LOW);
  digitalWrite(LED_RED, HIGH);  // Red LED on during startup

  // Connect to Blynk
  Serial.print("Connecting to WiFi: ");
  Serial.println(ssid);
  Blynk.begin(auth, ssid, pass);

  Serial.println("Connected to WiFi!");
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());
  Serial.println("Blynk connected!");
  Serial.println("Monitoring started...");
  Serial.println("--------------------------------");

  // Setup timer to send sensor data every 1 second
  timer.setInterval(1000L, sendSensorData);
}

/*
 * Function: loop
 * Description: Main loop - runs Blynk and timer
 */
void loop() {
  Blynk.run();
  timer.run();
}

/*
 * Alternative simple version without Blynk timer
 * Uncomment below and comment out the timer-based version above if needed
 */

/*
void loop() {
  // Read gas sensor value
  int sensor_value = analogRead(SENSOR_PIN);

  Serial.print("Gas Level: ");
  Serial.println(sensor_value);

  // Send data to Blynk
  Blynk.virtualWrite(V1, sensor_value);

  if (sensor_value > SENSOR_LIMIT) {
    // Gas detected
    digitalWrite(LED_GREEN, HIGH);
    digitalWrite(LED_RED, LOW);
    digitalWrite(BUZZER_PIN, HIGH);
    delay(100);
    digitalWrite(BUZZER_PIN, LOW);
    Blynk.notify("Alert: Gas Leakage Detected");
  }
  else {
    // Normal
    digitalWrite(BUZZER_PIN, LOW);
    digitalWrite(LED_GREEN, LOW);
    digitalWrite(LED_RED, HIGH);
  }

  delay(100);
  Blynk.run();
}
*/
