# NeoPixel Cube Software

This directory contains the Arduino sketch that controls the 4×4×4 NeoPixel LED Cube. The firmware implements button-based user interaction, sensor-driven brightness control and four distinct animation patterns.

## File Contents

- `neopixel-cube.ino` – Main Arduino sketch

## Pin Configuration

The following pin assignments are used in the code:

| Pin | Component | Type | Description |
|-----|-----------|------|-------------|
| D2 | Power Button | Digital Input | System on/off toggle |
| D3 | Mode Button | Digital Input | Animation pattern selector |
| D4 | Buzzer | Digital Output | Audio feedback |
| D6 | NeoPixel Data | Digital Output | LED data signal |
| A0 | LDR Sensor | Analog Input | Ambient light measurement |

## Animation Patterns

### Mode 0: Color Wipe

Sequentially lights each LED in red, green and blue order. The pattern uses a static state variable to track the current color phase and LED index. A 50ms interval between LEDs creates a smooth wave effect across the cube.

**Key Features:**
- Non-blocking timing using `millis()`
- Automatic color cycling (red → green → blue → red)
- Complete LED clear between color transitions

### Mode 1: Smooth RGB Fade

All LEDs fade in and out synchronously through the RGB spectrum. The algorithm incrementally adjusts brightness from 0 to 255, then reverses direction. A 3ms delay between steps ensures smooth visual transitions.

**Key Features:**
- Synchronized fade across all LEDs
- Smooth brightness ramping
- Continuous color cycling

### Mode 2: Fire Effect

Simulates realistic flickering flames using a heat simulation algorithm. Each LED maintains a heat value that determines its color mapping. The pattern includes three key stages:

1. **Cooling** – Random heat reduction per LED
2. **Heat Diffusion** – Upward heat propagation between adjacent LEDs
3. **Sparking** – Random ignition events at the base

**Parameters:**
- `Cooling: 55` – Rate of heat loss
- `Sparking: 120` – Frequency of new spark generation
- `SpeedDelay: 15` – Animation update interval

**Color Mapping:**
- Low heat → Dark red
- Medium heat → Orange/yellow
- High heat → Bright yellow/white

### Mode 3: Rainbow Cycle

Displays a continuously moving rainbow gradient across the LED array. The color wheel function maps positions 0-255 to smooth RGB transitions:

- 0-84: Red to green
- 85-169: Green to blue
- 170-255: Blue to red

**Key Features:**
- Smooth hue transitions
- Continuous animation flow
- Configurable speed (20ms default delay)

## Setup and Loop Functions

### setup()

Executes once at power-on:

1. Initializes NeoPixel library with 64 LEDs on pin D6
2. Configures pin modes for buttons, buzzer and sensor
3. Establishes serial communication at 9600 baud
4. Outputs "Setup complete. Ready." confirmation message

### loop()

Main execution cycle that runs continuously:

1. Reads button states with edge detection
2. Processes power toggle with buzzer feedback
3. Handles mode cycling when system is on
4. Reads LDR sensor and calculates brightness
5. Executes active animation pattern
6. Outputs debug information to serial monitor

## Brightness Control System

The adaptive brightness algorithm uses the following logic:
```
Analog Reading (0-1023) → Mapped Value (255-20) → Constrained (20-255)
```

**Mapping Details:**
- Lower ambient light (lower LDR value) → Higher LED brightness
- Higher ambient light (higher LDR value) → Lower LED brightness
- Minimum brightness: 20 (ensures visibility in bright environments)
- Maximum brightness: 255 (full intensity in dark environments)

The inverted mapping prevents excessive brightness in well-lit environments, reducing eye strain and power consumption.

## Helper Functions

### showStrip()

Updates the physical LED display with current color values. Includes preprocessor directives for compatibility with both Adafruit NeoPixel and FastLED libraries.

### setPixel(int Pixel, byte red, byte green, byte blue)

Sets the color of a specific LED by index. Accepts RGB values in the range 0-255.

### setAll(byte red, byte green, byte blue)

Sets all 64 LEDs to the same color. Internally calls `setPixel()` for each LED, then updates the display.

### setPixelHeatColor(int Pixel, byte temperature)

Converts a heat value (0-255) to an appropriate flame color. Uses temperature zones to determine RGB values:

- Cool (0-63): Dark to bright red
- Medium (64-127): Red to orange/yellow
- Hot (128-255): Yellow to white

### Wheel(byte WheelPos)

Maps a position value (0-255) to a color on the RGB spectrum. Returns a pointer to a static 3-byte array containing RGB values. Used by the rainbow cycle animation.

## Required Libraries

### Adafruit NeoPixel

**Installation:**
1. Open Arduino IDE
2. Navigate to Sketch → Include Library → Manage Libraries
3. Search for "Adafruit NeoPixel"
4. Install the latest version

**Library Configuration:**

The library is initialized with the following parameters:
```cpp
Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUM_LEDS, PIN, NEO_GRB + NEO_KHZ800);
```

- `NUM_LEDS: 64` – Total LED count in 4×4×4 cube
- `PIN: 6` – Data output pin
- `NEO_GRB` – Color order (Green-Red-Blue for WS2812B)
- `NEO_KHZ800` – Communication frequency (800kHz standard)

## State Variables

The code uses several state-tracking variables:

- `isOn` – Boolean flag for system power state
- `currentMode` – Integer (0-3) for active animation pattern
- `lastPowerButtonState` – Previous power button state for edge detection
- `lastModeButtonState` – Previous mode button state for edge detection
- `modeChanged` – Boolean flag to control serial output of pattern names

Additional static variables within pattern functions preserve animation state between loop iterations.

## Serial Output Format

Debug information is continuously transmitted via serial at 9600 baud:
```
Setup complete. Ready.
System ON - Pattern: Color Wipe
LDR: 512 | Brightness: 137
LDR: 498 | Brightness: 144
Pattern: Smooth RGB Fade
```

## Memory Usage

The code is optimized for Arduino Uno's limited resources:

- Program storage: ~10KB (32% of available flash)
- Dynamic memory: ~800 bytes (40% of available SRAM)
- Static variables used to minimize heap fragmentation

## Modification Guide

### Adding a New Pattern

1. Create a new function following the existing pattern structure
2. Add a case to the switch statement in `loop()`
3. Increment the modulo value in mode cycling logic
4. Add a serial print statement for the pattern name

### Adjusting Brightness Range

Modify the `map()` function parameters:
```cpp
int brightness = map(lightValue, 0, 1023, [MIN], [MAX]);
```

Replace `[MIN]` and `[MAX]` with desired brightness bounds.

### Changing Button Pins

Update the pin definitions at the top of the sketch and verify pull-up resistor configuration.

For complete hardware specifications and assembly instructions, refer to the root README.md.