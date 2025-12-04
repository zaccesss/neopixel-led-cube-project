# Software

This directory contains all software and firmware used in the NeoPixel LED Cube Project. The code is written in C/C++ for the Arduino platform and implements real-time control of 64 addressable RGB LEDs with interactive user input and sensor-based brightness adjustment.

## Overview

The software architecture is designed around a state machine model that continuously monitors user inputs, processes sensor data and renders dynamic lighting patterns. The implementation prioritizes modularity, readability and real-time responsiveness.

## Directory Structure
```
software/
├── README.md (this file)
└── neopixel-cube/
    ├── README.md
    └── neopixel-cube.ino
```

## Core Functionality

### Input Processing

The system monitors two physical buttons and one analog sensor:

- **Power Button (D2)** – Toggles the entire system on and off. Uses edge detection to prevent repeated triggering.
- **Mode Button (D3)** – Cycles through four distinct animation patterns. Active only when system is powered on.
- **LDR Sensor (A0)** – Continuously reads ambient light levels and maps the value to appropriate LED brightness.

Button inputs use software debouncing with a 200ms delay to ensure clean state transitions. The code implements rising-edge detection by comparing current and previous button states.

### Animation System

The software includes four pre-programmed lighting patterns:

1. **Color Wipe** – Sequential LED illumination in red, green and blue
2. **Smooth RGB Fade** – Synchronized fading across all LEDs
3. **Fire Effect** – Realistic flame simulation using heat mapping
4. **Rainbow Cycle** – Continuous rainbow gradient animation

Each pattern is implemented as a separate function with non-blocking timing control using `millis()` timestamps. This architecture allows smooth animation while maintaining responsive input handling.

### Brightness Adaptation

The LDR sensor reading (0-1023 analog value) is mapped to LED brightness (20-255 PWM value) using an inverted relationship. Higher ambient light results in dimmer LEDs to reduce visual fatigue and power consumption. The minimum brightness threshold of 20 ensures LEDs remain visible in all lighting conditions.

### Audio Feedback

A buzzer connected to pin D4 provides audio confirmation when the system is powered on or off. The `beep()` function generates a 100ms tone using a simple HIGH-LOW digital output sequence.

### Serial Communication

Real-time system state information is transmitted via serial output at 9600 baud. The debug output includes:

- System power state changes
- Active animation pattern names
- LDR sensor readings
- Calculated brightness values

This diagnostic information is invaluable for troubleshooting and understanding system behavior.

## Code Organization

### Main Functions

- `setup()` – Initializes the NeoPixel library, configures pin modes and establishes serial communication
- `loop()` – Main execution loop that handles button polling, sensor reading and pattern rendering
- `beep()` – Audio feedback generator

### Pattern Functions

- `colorCycle()` – Implements sequential color wipe animation
- `RGBLoop()` – Handles synchronized RGB fade effect
- `Fire()` – Renders realistic flame simulation
- `rainbowCycle()` – Generates moving rainbow gradient

### Helper Functions

- `showStrip()` – Updates LED display with current color values
- `setPixel()` – Sets individual LED color
- `setAll()` – Sets all LEDs to the same color
- `setPixelHeatColor()` – Converts heat values to flame colors
- `Wheel()` – Maps position to rainbow color spectrum

## Dependencies

The software requires the following library:

- **Adafruit NeoPixel** – Official library for controlling WS2812B addressable LEDs

Install via Arduino Library Manager:
```
Sketch → Include Library → Manage Libraries → Search "Adafruit NeoPixel"
```

## Compilation and Upload

### Requirements

- Arduino IDE 1.8.x or newer
- Arduino Uno board or compatible ATmega328P-based board
- USB cable for programming

### Steps

1. Open `neopixel-cube.ino` in Arduino IDE
2. Select board: Tools → Board → Arduino Uno
3. Select port: Tools → Port → [appropriate COM port]
4. Verify code: Sketch → Verify/Compile
5. Upload to board: Sketch → Upload

### Serial Monitor

To view real-time debug output:

1. Tools → Serial Monitor
2. Set baud rate to 9600
3. Observe system state messages and sensor readings

## Customization

The software is designed for easy modification:

### Adding New Patterns

Create a new function following the existing pattern structure and add a case to the `switch` statement in the main loop.

### Adjusting Animation Speed

Modify the delay values within each pattern function to change animation speed. Ensure delays are short enough to maintain responsive button handling.

### Changing Brightness Mapping

Adjust the parameters in the `map()` function call to modify how ambient light affects LED brightness.

### Modifying Audio Feedback

Change the buzzer pin or adjust the duration in the `beep()` function.

## Performance Considerations

- The code uses non-blocking timing to ensure responsive input handling
- Pattern functions should avoid long `delay()` calls to maintain system responsiveness
- Serial output is primarily for debugging and can be removed for production use
- Memory usage is minimal with static variables used to preserve animation state between loop iterations

## Troubleshooting

**LEDs not responding:**
- Verify power supply voltage and current capacity
- Check data line connection to pin D6
- Ensure shared ground between Arduino and LED power supply

**Buttons not working:**
- Confirm pull-up resistor configuration
- Check physical button connections
- Adjust debounce delay if needed

**Brightness not changing:**
- Verify LDR connection to A0
- Test LDR functionality with Serial Monitor output
- Check mapping range in code

For additional details on specific functions and implementation, refer to the inline comments in `neopixel-cube.ino`.