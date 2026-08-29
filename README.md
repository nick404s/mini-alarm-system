# Arduino Mini Alarm System

<p align="left">
<img src="https://img.shields.io/badge/Arduino-Uno%20R3-00979D" />
<img src="https://img.shields.io/badge/C++-Embedded-blue" />
<img src="https://img.shields.io/badge/Ultrasonic%20Sensor-HC--SR04-orange" />
<img src="https://img.shields.io/badge/IR%20Receiver-Remote%20Control-8A2BE2" />
<img src="https://img.shields.io/badge/Passive%20Buzzer-Alert-red" />
<img src="https://img.shields.io/badge/RGB%20LED-Status%20Indicator-green" />
<img src="https://img.shields.io/badge/3--State%20System-OFF%2FIDLE%2FON-yellow" />
<img src="https://img.shields.io/badge/License-MIT-green" />
</p>

  A compact, sensor‑driven Arduino alarm system featuring a three‑state logic machine, remote‑controlled activation, and clear LED‑based status indicators. Designed to demonstrate embedded programming, sensor integration, and real‑time state transitions on the Arduino Uno R3.

##
**Mini Alarm System**  
This is a **3-state alarm system (OFF / IDLE / ON)** indicated by an **RGB LED (BLUE / GREEN / RED)**.

- **Ultrasonic sensor** activates the alarm  
- **IR receiver** resets the system states  
- **Passive buzzer** provides audible alerts  
- **RGB LED** provides visual feedback

---

## Tech Used

- C++
- Uno R3 Board
- Ultrasonic Sensor (HC‑SR04)
- IR Receiver Module
- Passive Buzzer
- RGB LED

---

## Features
### Three‑State Alarm System:
- OFF (Blue) — System inactive
- IDLE (Green) — System armed, object detected
- ON / Alarm (Red) — Object removed → buzzer activated

### Sensor-Driven Activation
Ultrasonic sensor monitors object distance and triggers the alarm when the object is removed.

### Remote-Controlled Reset
IR receiver listens for remote input to toggle system states and disable the alarm.

### Persistent Alarm Logic
Once triggered, the alarm remains active even if the object is returned — only the IR remote can reset it.

### Clear Visual Indicators
RGB LED communicates system state at all times.

---

## System Behavior

The alarm operates as a simple state machine:

1. **OFF State**  
   - LED: Blue  
   - Waiting for IR remote activation  

2. **IDLE State**  
   - LED: Green  
   - Object must remain within a defined distance  
   - If object is removed → transition to Alarm  

3. **ON / Alarm State**  
   - LED: Red  
   - Buzzer activated  
   - Alarm persists until IR remote disables it  

---

## To Start the Project

### Requirements
- Arduino IDE  
- Uno R3 board  
- Listed hardware components  

### Upload the Code
1. Connect the Uno R3  
2. Open the `.ino` file in Arduino IDE  
3. Select correct board + COM port  
4. Upload  

---
