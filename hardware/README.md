# Hardware

This directory documents the physical components, circuit design and assembly process for the NeoPixel LED Cube Project. The hardware consists of a 4×4×4 matrix of addressable RGB LEDs controlled by an Arduino Uno with button inputs, sensor feedback and audio output.

## Component List

### Primary Components

| Component | Specification | Quantity | Purpose |
|-----------|---------------|----------|---------|
| Arduino Uno | ATmega328P microcontroller | 1 | Main control board |
| WS2812B LED | 5V addressable RGB LED | 64 | Cube matrix elements |
| Power Button | SPST momentary switch | 1 | System power control |
| Mode Button | SPST momentary switch | 1 | Pattern selection |
| LDR Sensor | Photoresistor (5-10kΩ) | 1 | Ambient light detection |
| Buzzer | 5V active buzzer | 1 | Audio feedback |
| Electrolytic Capacitor | 1000µF, 6.3V or higher | 1 | Power supply filtering |
| Resistor | 10kΩ | 2 | Button pull-up resistors |
| Resistor | 10kΩ | 1 | LDR voltage divider |
| Breadboard | Standard 830-point | 1 | Component mounting |
| Jumper Wires | Male-to-male | ~20 | Circuit connections |
| Copper Wire | 22-24 AWG solid core | ~5 meters | LED cube structure |
| Power Supply | 5V DC, 2A minimum | 1 | System power |
| Power Jack | 2.1mm barrel connector | 1 | Power input |
| USB Cable | Type A to Type B | 1 | Programming and serial |
| Enclosure | Custom wooden box | 1 | Housing and protection |

### Supporting Materials

- Solder and soldering iron
- Wire strippers
- Pliers
- Hot glue gun
- Electrical tape
- Heat shrink tubing (optional)

## Circuit Design

### Power Distribution

The power system uses a 5V DC supply with a minimum 2A rating to safely drive all 64 LEDs. Key design features:

**Voltage Regulation:**
- Arduino Uno powered via barrel jack or USB
- LEDs receive 5V directly from power supply
- Shared common ground between Arduino and LED power

**Current Protection:**
- Large electrolytic capacitor (1000µF) across 5V and GND rails
- Capacitor placed physically close to first LED in chain
- Smooths voltage spikes during rapid LED color changes

**Estimated Current Draw:**
- All LEDs at maximum white: ~3.8A (64 LEDs × 60mA)
- Typical operation: 1.5-2A (mixed colors and brightness)
- Recommended supply rating: 2A minimum, 3A preferred

### Signal Connections

**NeoPixel Data Line:**
- Single data wire from Arduino pin D6 to first LED in chain
- Each subsequent LED receives data from previous LED
- Total of 64 LEDs wired in series
- Keep data line short to minimize signal degradation

**Button Inputs:**
- Power button connected between D2 and GND
- Mode button connected between D3 and GND