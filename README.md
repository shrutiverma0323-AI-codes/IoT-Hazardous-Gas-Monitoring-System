# IoT Based Hazardous Gas Monitoring System

An IoT-based safety system that detects hazardous gases (LPG, propane, methane, smoke, etc.) and sends real-time alerts to your smartphone via the Blynk app.

![NodeMCU](https://img.shields.io/badge/Platform-NodeMCU%20ESP8266-blue)
![Arduino](https://img.shields.io/badge/IDE-Arduino-teal)
![Blynk](https://img.shields.io/badge/App-Blynk-green)
![License](https://img.shields.io/badge/License-MIT-yellow)

## Overview

Safety plays a major role in today's world, and it is necessary that good safety systems are implemented in places of education, work, and home. This project implements a microcontroller-based toxic gas detecting and alerting system using IoT technology.

The system detects hazardous gases like **LPG, propane, methane, hydrogen, alcohol, smoke, and carbon monoxide**. When gas levels exceed the threshold, it triggers:
- Buzzer alarm for audio alert
- LED indicators for visual alert
- Push notification to smartphone via Blynk app

## Features

- **Real-time Monitoring**: Continuously monitors gas concentration levels
- **Mobile Alerts**: Instant push notifications via Blynk app
- **Visual Indicators**: Green LED (safe) / Red LED (danger)
- **Audio Alarm**: Buzzer activates on gas detection
- **Remote Monitoring**: Monitor gas levels from anywhere via internet
- **Low Cost**: Built with affordable, easily available components

## Hardware Components

| Component | Description |
|-----------|-------------|
| NodeMCU ESP8266 | WiFi-enabled microcontroller |
| MQ2 Gas Sensor | Detects LPG, propane, methane, hydrogen, alcohol, smoke, CO |
| Buzzer | Audio alarm for gas detection |
| LED (Green) | Indicates danger/gas detected |
| LED (Red) | Indicates safe/normal operation |
| Resistor 220Ω | Current limiting for LEDs |
| Breadboard | For prototyping |
| Jumper Wires | For connections |

## Software Requirements

- [Arduino IDE](https://www.arduino.cc/en/software)
- [Blynk App](https://blynk.io/) (iOS/Android)
- ESP8266 Board Package for Arduino IDE
- Blynk Library

## Circuit Diagram

### Pin Connections

```
NodeMCU          Component
────────         ─────────
Vin         →    Power Bus (+)
GND         →    Power Bus (-)
A0          →    MQ2 Sensor (A0)
D1          →    Buzzer (via transistor)
D5          →    Green LED (+)
D6          →    Red LED (+)

MQ2 Sensor
────────────
VCC         →    Power Bus (+)
GND         →    Power Bus (-)
A0          →    NodeMCU A0
```

## Installation & Setup

### 1. Arduino IDE Setup

1. Install [Arduino IDE](https://www.arduino.cc/en/software)
2. Add ESP8266 board support:
   - Go to `File` → `Preferences`
   - Add this URL to "Additional Board Manager URLs":
     ```
     http://arduino.esp8266.com/stable/package_esp8266com_index.json
     ```
   - Go to `Tools` → `Board` → `Board Manager`
   - Search "ESP8266" and install
3. Install Blynk Library:
   - Go to `Sketch` → `Include Library` → `Manage Libraries`
   - Search "Blynk" and install

### 2. Blynk App Setup

1. Download Blynk app from [App Store](https://apps.apple.com/app/blynk-iot/id1559317868) or [Play Store](https://play.google.com/store/apps/details?id=cloud.blynk)
2. Create a new project
3. Select "NodeMCU" as device
4. Copy the **Auth Token** (sent to your email)
5. Add widgets:
   - **Gauge** widget on Virtual Pin V1 (range: 0-1023)
   - **Notification** widget for alerts

### 3. Upload Code

1. Open `src/gas_monitor.ino` in Arduino IDE
2. Update the following in the code:
   ```cpp
   char auth[] = "YOUR_BLYNK_AUTH_TOKEN";
   char ssid[] = "YOUR_WIFI_SSID";
   char pass[] = "YOUR_WIFI_PASSWORD";
   ```
3. Select Board: `Tools` → `Board` → `NodeMCU 1.0 (ESP-12E Module)`
4. Select Port: `Tools` → `Port` → (Your COM port)
5. Upload the code

## Usage

1. Power on the NodeMCU
2. Wait for WiFi connection (check Serial Monitor at 115200 baud)
3. Open Blynk app and run the project
4. The gauge shows real-time gas concentration (0-1023)
5. When gas level exceeds threshold (200):
   - Green LED turns ON
   - Buzzer sounds
   - Push notification sent to phone
6. When gas level is normal:
   - Red LED stays ON (indicating system is active)

## Project Structure

```
IoT-Hazardous-Gas-Monitoring-System/
├── src/
│   └── gas_monitor.ino      # Main Arduino code
├── docs/
│   ├── Project_Report.pdf   # Detailed project report
│   └── Presentation.pptx    # Project presentation
├── demo/
│   └── demo_video.mp4       # Working demonstration
├── images/
│   └── circuit_diagram.png  # Circuit schematic
├── README.md
└── LICENSE
```

## Demo

Check out the working demonstration video in the `demo/` folder.

## Algorithm

```
START
  │
  ▼
Connect to WiFi
  │
  ▼
Initialize Blynk App
  │
  ▼
Set Sensor Limit = 200
  │
  ▼
┌─────────────────────────┐
│ Read Gas Level from A0  │◄────┐
└───────────┬─────────────┘     │
            │                   │
            ▼                   │
    ┌───────────────┐           │
    │ Gas > Limit?  │           │
    └───────┬───────┘           │
       YES/  \NO                │
          /    \                │
         ▼      ▼               │
   ┌─────────┐ ┌──────────┐     │
   │ Buzzer  │ │ Red LED  │     │
   │  ON     │ │   ON     │     │
   │Green LED│ │Green LED │     │
   │  ON     │ │   OFF    │     │
   │ Notify  │ └────┬─────┘     │
   └────┬────┘      │           │
        │           │           │
        └─────┬─────┘           │
              │                 │
              ▼                 │
        Delay 100ms             │
              │                 │
              └─────────────────┘
```

## Authors

- **Shruti Verma** - [GitHub](https://github.com/shrutiverma0323-AIAgent)
- **Prajwal Rajput**

## Acknowledgements

- Prof. Kamlesh Chandravanshi (Project Guide)
- AICRA Tacthub & Prof. Sumit Chatterjee (IoT Training)
- Lakshmi Narain College of Technology, Bhopal

## References

- [ESP8266 Arduino Core Documentation](https://github.com/esp8266/Arduino)
- [Blynk Documentation](https://docs.blynk.io/)
- [Arduino Official Website](https://www.arduino.cc)
- [MQ2 Gas Sensor Datasheet](https://www.pololu.com/file/0J309/MQ2.pdf)

## License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.

---

⭐ If you found this project helpful, please give it a star!
