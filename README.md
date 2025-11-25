## 🔊 Secure Access and Smart Sound Monitoring System (Bi-Directional IoT Application)

This project develops an IoT system using an **ESP32** board that validates physical access via **RFID** and dynamically controls a **Servo Motor** and an **RGB LED** based on the ambient sound level. All sensor data and device statuses are monitored and displayed in real-time on the **Blynk** cloud platform.

---

### ✨ Key Features

* **Card Access Control (RFID):** Reads and validates the RFID card UID for authorized user login/system activation.
* **Smart Environment Monitoring:** Continuously measures the ambient sound level.
* **Dynamic Control:** Changes the Servo Motor angle and RGB LED color based on the measured sound level.
* **Cloud Integration (Blynk):** Sends RFID UID, sound sensor data, and device status to the Blynk dashboard in real-time.
* **Bi-Directional Communication:** Sensor data is sent to the cloud (Uplink), and the circuit is controlled (potentially, future Downlink control can be added).

### 🎯 Application Purpose (Scenario)

The primary goal of this application is to develop a smart monitoring system that visually and mechanically indicates the ambient sound level **after authorized access** has been granted (via RFID verification).

| Condition | Sound Level (Based on Thresholds) | Servo Motor Angle | RGB LED Color | Blynk Status Message |
| :---: | :---: | :---: | :---: | :---: |
| 1 | Silence | 0° | Blue | Sound level low. |
| 2 | Middle | 45° | Green | Sound level medium. |
| 3 | High | 90° | Red | Sound level high! |

All status information, RFID readings, and the raw sound sensor value are monitored on the Blynk dashboard.

---

### ⚙️ Technical Details

| Component | Selection | Description |
| :--- | :--- | :--- |
| **IoT Board** | ESP-32 | Chosen for its integrated Wi-Fi connectivity and robust processing power. |
| **Cloud Platform** | Blynk | Provides an easy mobile/web interface for real-time monitoring and fast prototyping. |
| **Sensor** | Sound Sensor | Reads the ambient sound level as an analog value. |
| **Wireless Comm.** | RFID | Used for access control and system activation. |
| **DC Motor** | Servo Motor | Indicates the sound level with angular movement (0°, 45°, 90°). |
| **LED** | Common Cathode RGB | Indicates the sound level with color change (Blue, Green, Red). |
| **IDE/Language** | Arduino IDE / C/C++ | Standard development environment for ESP32 programming. |

### 🛠️ Required Libraries

The following Arduino libraries are required to compile and run this project:

* `WiFi.h` (Built-in for ESP32)
* `BlynkSimpleEsp32.h`
* `MFRC522.h` (For the RFID reader)
* `ESP32Servo.h` (or similar Servo library)

---

### 🔌 Circuit Diagram

The circuit diagram was designed using Fritzing. 

**Key Connections:**

* **RFID Reader (MFRC522):** Connected to the ESP32 via the SPI interface (MOSI, MISO, SCK).
* **Sound Sensor:** Analog output (A0) connected to an ADC pin on the ESP32.
* **Servo Motor:** Connected to a PWM-enabled digital pin.
* **Common Cathode RGB LED:** R, G, B pins connected to ESP32 PWM pins via current-limiting resistors.

### 🚀 Usage and Setup

1.  **Blynk Setup:** Create a new project in Blynk and obtain the AUTH TOKEN. Set up the necessary Virtual Pins (V-Pins) on your dashboard (for Sound Value, RFID UID, Status Messages, Servo Angle).
2.  **Library Installation:** Install the libraries listed above into your Arduino IDE.
3.  **Code Update:** Update the `AUTH_TOKEN`, Wi-Fi SSID, and Password fields in the code with your credentials.
4.  **Circuit Assembly:** Build the circuit according to the Fritzing diagram.
5.  **Upload:** Upload the code to the ESP32 board and open the serial monitor.
6.  **Operation:** Tap the authorized RFID card to activate the system. Then, monitor the motor and LED response based on changes in ambient sound. All data should be reflected simultaneously in the Blynk mobile/web application.
