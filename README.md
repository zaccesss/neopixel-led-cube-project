<p align="center">
  <img src="https://capsule-render.vercel.app/api?type=waving&color=gradient&height=110&section=header&text=NeoPixel%20LED%20Cube%20Project&fontSize=34&fontAlignY=32&fontColor=ffffff&animation=fadeIn" />
</p>

# Project Contact & Links
<p align="center">
  <a href="https://linktr.ee/zaccess">
    <img src="https://img.shields.io/badge/Linktree-zaccess-1de9b6?style=for-the-badge&logo=linktree&logoColor=white">
  </a>
  <a href="https://www.linkedin.com/in/isaacadjei">
    <img src="https://img.shields.io/badge/LinkedIn-Isaac_Adjei-0a66c2?style=for-the-badge&logo=linkedin&logoColor=white">
  </a>
  <a href="mailto:offices.isaac@gmail.com">
    <img src="https://img.shields.io/badge/Email-Contact-ff6f61?style=for-the-badge&logo=gmail&logoColor=white">
  </a>
  
</p>
<p align="center">
  <img src="https://img.shields.io/badge/License-MIT-green?style=for-the-badge">
</p>


# Quick Navigation
<p align="center">
  🔎 •  
  <a href="#1-project-overview">Overview</a> •
  <a href="#2-key-features">Features</a> •
  <a href="#3-hardware-components">Hardware</a> •
  <a href="#4-software-architecture">Software</a> •
  <a href="#5-build-documentation">Build</a> •
  <a href="#6-user-operation">Usage</a> •
  <a href="#7-technical-specifications">Specs</a> •
  <a href="#8-serial-monitor-output">Serial output</a> •
  <a href="#9-demonstration-media">Media</a> •
  <a href="#10-future-enhancements">Future</a> •
  <a href="#11-license-credits-and-attribution">License and credits</a> •
  <a href="#12-repository-structure">Repo structure</a> •
  <a href="#contact-and-support">Contact</a> •
  <a href="#faq">FAQ</a>
</p>

---

## 1. Project Overview

The NeoPixel LED Cube Project is an interactive 4×4×4 LED display system developed as part of an academic engineering assignment. This adaptive lighting system combines hardware assembly with embedded software to create a fully functional LED cube capable of displaying multiple dynamic patterns while automatically adjusting brightness based on ambient light conditions.

The project demonstrates practical applications of digital input handling, analog sensing, PWM-based LED control and real-time logic in embedded systems. The cube features user-controlled pattern selection, automatic brightness adjustment via an LDR sensor and audio feedback through a buzzer, providing an engaging and responsive visual experience.

**Lead Developer:** Isaac "Zac" Adjei  
**Team:** NeoPixel Innovators   
**Platform:** Arduino Uno  
**LED Count:** 64 WS2812B addressable LEDs

---

## 2. Key Features

- **4×4×4 LED Matrix Architecture** – 64 individually addressable WS2812B NeoPixel LEDs arranged in a cubic structure
- **Four Dynamic Animation Modes** – Color Wipe, Smooth RGB Fade, Fire Effect and Rainbow Cycle
- **Adaptive Brightness Control** – LDR sensor automatically adjusts LED intensity based on ambient light
- **Interactive User Controls** – Physical buttons for power toggle and mode cycling
- **Audio Feedback System** – Buzzer provides confirmation tones for user interactions
- **Real-Time Serial Monitoring** – Debug output displays system state, brightness levels and active patterns
- **Modular Software Design** – Clean, well-documented code structure for easy modification and expansion

---

## 3. Hardware Components

### 3.1 Component List

| Component | Specification | Quantity | Purpose |
|-----------|---------------|----------|---------|
| Arduino Uno | ATmega328P | 1 | Main microcontroller |
| WS2812B LEDs | 5V addressable RGB | 64 | LED cube matrix |
| Power Button | Digital momentary switch | 1 | System power toggle |
| Mode Button | Digital momentary switch | 1 | Pattern selection |
| LDR Sensor | Analog light sensor | 1 | Ambient brightness detection |
| Buzzer | 5V active buzzer | 1 | Audio feedback |
| Electrolytic Capacitor | 1000µF, 6.3V+ | 1 | Power supply smoothing |
| Breadboard | Standard size | 1 | Component mounting |
| Power Supply | 5V, ≥2A | 1 | System power |
| Enclosure | Custom wooden box | 1 | Housing and protection |

### 3.2 Pin Configuration

| Arduino Pin | Component | Function |
|-------------|-----------|----------|
| D2 | Power Button | Digital input (pull-up) |
| D3 | Mode Button | Digital input (pull-up) |
| D4 | Buzzer | Digital output |
| D6 | NeoPixel Data | Data output to LED strip |
| A0 | LDR Sensor | Analog input (0-1023) |
| 5V | Power Rail | Positive supply |
| GND | Ground | Common ground |

### 3.3 Circuit Design

The circuit design incorporates several key safety and performance features:

- **Shared Ground Architecture** – All components share a common ground connection with the Arduino to ensure stable signal communication
- **Power Supply Decoupling** – A large electrolytic capacitor on the 5V rail protects the LEDs from voltage spikes during rapid switching
- **Current Limiting** – Power supply rated at minimum 2A to safely drive all 64 LEDs at full brightness
- **Button Debouncing** – Software-based debouncing prevents false triggering from mechanical switch bounce
- **Signal Integrity** – Short data line from Arduino to first LED minimizes signal degradation

---

## 4. Software Architecture

### 4.1 Code Structure

The software is organized around a state machine architecture with real-time input processing and pattern rendering:

**Main Components:**
- **Setup Function** – Initializes hardware peripherals, configures pin modes and establishes serial communication
- **Loop Function** – Continuously polls button states, reads sensor data and executes the active animation pattern
- **Pattern Functions** – Four independent animation routines with non-blocking timing control
- **Helper Functions** – Utility routines for LED control, color conversion and display updates

### 4.2 Animation Patterns

#### Mode 0: Color Wipe
Sequentially illuminates each LED in a cascading pattern, cycling through red, green and blue. This pattern creates a smooth wave effect across the cube structure.

#### Mode 1: Smooth RGB Fade
All LEDs fade in and out synchronously, transitioning between red, green and blue. The fade effect uses incremental brightness adjustment for smooth color transitions.

#### Mode 2: Fire Effect
Simulates realistic flickering flames using a heat simulation algorithm. Each LED is assigned a dynamic heat value that determines its color, ranging from deep red through orange to bright yellow-white.

#### Mode 3: Rainbow Cycle
Displays a moving rainbow gradient across the entire LED array. The color wheel algorithm ensures smooth hue transitions and continuous animation flow.

### 4.3 Brightness Control System

The adaptive brightness system maps the LDR sensor reading to LED intensity:

- **Sensor Range:** 0-1023 (10-bit analog reading)
- **Brightness Range:** 20-255 (8-bit PWM value)
- **Mapping Logic:** Inverted relationship – brighter ambient light results in dimmer LEDs to reduce eye strain
- **Update Frequency:** Real-time adjustment on every loop iteration
- **Minimum Threshold:** 20/255 ensures LEDs remain visible in all lighting conditions

### 4.4 Required Libraries

- **Adafruit NeoPixel** – Provides low-level control interface for WS2812B LED strips

---

## 5. Build Documentation

### 5.1 Physical Construction

The LED cube uses a custom copper wire frame structure that provides both mechanical support and electrical connections. The 4×4×4 matrix is built layer by layer, with each layer soldered into place before proceeding to the next.

**Construction Process:**
1. Created a jig to ensure precise LED spacing and alignment
2. Bent and cut copper wire segments to form the structural framework
3. Soldered LEDs in series, maintaining proper data line polarity
4. Stacked and connected layers with vertical wire supports
5. Verified continuity and tested each layer before final assembly

### 5.2 Enclosure Design

The wooden enclosure houses the Arduino, breadboard and power distribution components while providing a stable platform for the LED cube. The design includes:

- Cable management channels to organize wiring
- Ventilation space to prevent heat buildup
- Access ports for USB programming and power input
- Front-panel mounting positions for control buttons

---

## 6. User Operation

### 6.1 Power On/Off

Press the power button (D2) to toggle the system state. The buzzer will emit a confirmation tone and the cube will either illuminate with the default pattern or turn completely off.

### 6.2 Changing Patterns

While the system is powered on, press the mode button (D3) to cycle through the four available animation patterns. The active pattern name is displayed in the serial monitor.

### 6.3 Brightness Adjustment

Brightness adjusts automatically based on ambient light detected by the LDR sensor. No manual intervention is required. Current brightness values are continuously displayed in the serial monitor.

---

## 7. Technical Specifications

| Parameter | Value |
|-----------|-------|
| LED Type | WS2812B (addressable RGB) |
| Total LED Count | 64 |
| Matrix Configuration | 4×4×4 cube |
| Operating Voltage | 5V DC |
| Maximum Current Draw | ~3.8A (all LEDs at full white) |
| Recommended Power Supply | 5V, ≥2A |
| Microcontroller | Arduino Uno (ATmega328P) |
| Clock Speed | 16 MHz |
| Serial Baud Rate | 9600 bps |
| LDR Analog Resolution | 10-bit (0-1023) |
| LED Brightness Resolution | 8-bit (0-255) |

---

## 8. Serial Monitor Output

The Arduino continuously transmits diagnostic information via serial communication at 9600 baud. This output includes:

- System power state changes
- Active animation pattern name
- Real-time LDR sensor readings
- Calculated brightness values

**Example Output:**
```
Setup complete. Ready.
System ON - Pattern: Color Wipe
LDR: 512 | Brightness: 137
LDR: 498 | Brightness: 144
Pattern: Smooth RGB Fade
LDR: 720 | Brightness: 85
```

---

## 9. Demonstration Media

### 9.1 Visual Documentation

The project includes comprehensive visual documentation:

- **cube-build-layer-top-view-1.jpeg** – Construction process showing layer assembly
- **cube-lit-full-bright-front-1.jpeg** – Completed cube displaying full brightness pattern
- **power-circuit-capacitor-closeup-1.jpeg** – Detail view of power supply filtering
- **enclosure-arduino-breadboard-top-1.jpeg** – Internal component layout
- **cube-enclosure-final-setup-1.jpeg** – Final assembled project

### 9.2 Video Content

- **neopixel-demo.mp4** – Full demonstration of all four animation patterns
- **neopixel-description.mp4** – Project walkthrough and technical explanation

---

## 10. Future Enhancements

Potential improvements and expansions for future development:

- **Wireless Control** – Integration of Bluetooth or Wi-Fi module for remote pattern selection and parameter adjustment
- **Audio Reactivity** – Addition of microphone sensor to create sound-responsive lighting effects
- **Extended Pattern Library** – Implementation of additional animation algorithms such as 3D spirals, plane sweeps and particle effects
- **Mobile Application** – Development of companion smartphone app for advanced control and customization
- **Persistence of Vision Effects** – High-speed pattern switching to create complex visual illusions
- **Temperature Monitoring** – Addition of thermal sensor to prevent LED overheating during extended operation

---

## 11. License, Credits and Attribution

### 11.1 License

This project is released under the MIT License with an additional academic use notice.

**MIT License**

Copyright (c) 2024 Isaac "Zac" Adjei, NeoPixel Innovators 

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

**Academic Use Notice**

This project was developed as part of an academic engineering assignment. While the code and design are open source, users incorporating this work into their own academic projects should provide appropriate attribution and ensure compliance with their institution's academic integrity policies.

### 11.2 Attribution

**Lead Developer:** Isaac "Zac" Adjei  
**Team:** NeoPixel Innovators 
**Project Repository:**   
**Dependencies:** Adafruit NeoPixel Library

### 11.3 Credits

This project was designed and developed by **Isaac “Zac” Adjei** & **Neopixel Innovators** 

---

## 12. Repository Structure

The project is organised into separate folders for software, hardware, documentation and media so it is easy to navigate and reuse parts of the work.

-  **docs/** – [Documentation folder](docs/) – reports, portfolios, planning files and final presentation  
- **hardware/** – [Hardware resources](hardware/) – hardware overview slides and build notes  
- **media/** – [Images and videos](media/) – photos and videos used in reports and the README  
- **software/** – [Arduino code and software docs](software/) – Arduino firmware and supporting documentation


<details>
<summary><b>Click to expand full directory tree</b></summary>

```text
neopixel-led-cube/
│
├── .gitignore
├── LICENSE.md
├── README.md
│
├── docs/
│   ├── README.md
│   ├── code-screenshot-1.png
│   ├── code-screenshot-2.png
│   ├── finance-report.xlsx
│   ├── gantt-chart.xlsx
│   ├── market-analysis.docx
│   ├── neopixel-demo.mp4
│   ├── neopixel-description.mp4
│   ├── notes-and-drafts.docx
│   ├── presentation-final.pptx
│   ├── software-portfolio.docx
│   └── software-portfolio-v2.docx
│
├── hardware/
│   ├── README.md
│   └── hardware-overview.pptx
│
├── media/
│   ├── README.md
│   ├── code-screenshot-1.png
│   ├── code-screenshot-2.png
│   ├── cube-build-layer-top-view-1.jpeg
│   ├── cube-build-layer-top-view-2.jpeg
│   ├── cube-build-top-view-1.jpeg
│   ├── cube-enclosure-final-setup-1.jpeg
│   ├── cube-frame-complete-angle-1.jpeg
│   ├── cube-lit-full-bright-front-1.jpeg
│   ├── cube-lit-full-bright-front-2.jpeg
│   ├── enclosure-arduino-breadboard-top-1.jpeg
│   ├── enclosure-arduino-breadboard-top-2.jpeg
│   ├── neopixel-demo.mp4
│   ├── neopixel-description.mp4
│   ├── power-circuit-capacitor-closeup-1.jpeg
│   └── power-circuit-connected-to-cube-1.jpeg
│
└── software/
    ├── README.md
    ├── software-portfolio.docx
    ├── software-portfolio-v2.docx
    └── neopixel-cube/
        ├── README.md
        └── neopixel-cube.ino
```

</details>

---

## Contact and Support

For questions, suggestions or collaboration opportunities related to this project, please open an issue in the repository or contact the development team through the provided channels.

You can reach Zac at: **offices.isaac@gmail.com** or via my **GitHub profile**.

**Project Status:** Completed  
**Last Updated:** December 2025

---

## FAQ

### Can I use this project for my coursework?
Yes, but attribution is required under the Academic Use Notice.

### Can I add more LED patterns?
Absolutely. The software is modular – add another case to the mode switch.

### Can I adapt this for a 5×5×5 cube?
Yes. Update NUM_LEDS and adjust wiring accordingly.

---


