#include <Adafruit_NeoPixel.h>  // Include the NeoPixel library to control the LED strip

// Define the data pin for the NeoPixel strip
#define PIN 6                   // Pin D6 sends data to NeoPixel (data input for the LED cube)
#define NUM_LEDS 64             // Total number of NeoPixel LEDs used in the cube (4x4x4 = 64)

// Create the NeoPixel strip object
Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUM_LEDS, PIN, NEO_GRB + NEO_KHZ800);
// This creates a NeoPixel object 'strip' using:
// - NUM_LEDS: the number of LEDs
// - PIN: the pin used for data communication
// - NEO_GRB: the color ordering (Green-Red-Blue)
// - NEO_KHZ800: sets the communication frequency to 800kHz which is standard for most WS2812 LEDs

// Define input pins for buttons, sensor and buzzer
const int POWER_BUTTON = 2;     // Button connected to D2 for toggling ON or OFF
const int MODE_BUTTON  = 3;     // Button connected to D3 for cycling LED patterns
const int LDR_PIN      = A0;    // LDR (light sensor) connected to analog pin A0
const int BUZZER_PIN   = 4;     // Buzzer connected to D4 for audio feedback when toggling power

// State tracking variables
bool isOn = false;              // Keeps track if system is ON or OFF (initially OFF)
int currentMode = 0;            // Stores current LED pattern index (starts from mode 0)
bool lastPowerButtonState = LOW; // Stores previous state of the power button (used for edge detection)
bool lastModeButtonState  = LOW; // Stores previous state of the mode button (used for edge detection)
bool modeChanged = false;       // Flag to know if the mode was just changed (used when printing pattern name)

// -----------------------------------------------------------------------------
// Setup function - runs once at startup
// -----------------------------------------------------------------------------
void setup() {
  strip.begin();                // Initialize the NeoPixel strip so it is ready to receive data
  strip.show();                 // Sends a blank signal to turn off all LEDs at startup

  pinMode(POWER_BUTTON, INPUT); // Configure pin connected to the ON or OFF button as an input
  pinMode(MODE_BUTTON, INPUT);  // Configure pin connected to the mode change button as an input
  pinMode(LDR_PIN, INPUT);      // Set the LDR sensor pin as input to read light levels
  pinMode(BUZZER_PIN, OUTPUT);  // Set the buzzer pin as output so it can play sound

  Serial.begin(9600);           // Start serial communication at 9600 bps for monitoring and debugging
  Serial.println("Setup complete. Ready."); // Print confirmation message after setup is done
}

// -----------------------------------------------------------------------------
// Function to trigger buzzer feedback
// -----------------------------------------------------------------------------
void beep() {
  digitalWrite(BUZZER_PIN, HIGH);  // Turn the buzzer ON by sending HIGH signal
  delay(100);                      // Keep the buzzer on for 100 milliseconds
  digitalWrite(BUZZER_PIN, LOW);   // Turn the buzzer OFF by sending LOW signal
}

// -----------------------------------------------------------------------------
// Main loop
// -----------------------------------------------------------------------------
void loop() {
  // --- Read button states ---
  bool powerButtonState = digitalRead(POWER_BUTTON); // Read current state of power button (HIGH when pressed)
  bool modeButtonState  = digitalRead(MODE_BUTTON);  // Read current state of mode button (HIGH when pressed)

  // --- Power toggle logic ---
  if (lastPowerButtonState == LOW && powerButtonState == HIGH) { // Check for rising edge: button was just pressed
    isOn = !isOn;                     // Toggle the system ON or OFF
    beep();                           // Play buzzer sound to indicate power toggle
    delay(200);                       // Debounce delay to avoid repeated readings from a single press

    if (!isOn) {
      setAll(0, 0, 0);                // If turned OFF clear all LEDs by setting them to black
      Serial.println("System OFF");   // Print system status to Serial Monitor
    } else {
      currentMode = 0;                // If turned ON start with the first LED pattern (Color Wipe)
      Serial.println("System ON - Pattern: Color Wipe"); // Show current pattern in Serial Monitor
    }
  }

  lastPowerButtonState = powerButtonState; // Save current power button state for the next loop cycle

  // --- Pattern cycle button logic ---
  if (lastModeButtonState == LOW && modeButtonState == HIGH && isOn) {
    // Check for rising edge (button just pressed) and system is ON
    currentMode = (currentMode + 1) % 4; // Move to the next pattern and loop back to 0 after 3
    modeChanged = true;                  // Set flag to indicate the mode was changed
    delay(200);                          // Short delay to debounce the button
  }

  lastModeButtonState = modeButtonState; // Save current mode button state for use in the next loop

  // Exit loop early if system is OFF
  if (!isOn) return; // Stop if system is off so no patterns run

  // --- Adjust brightness using LDR ---
  int lightValue = analogRead(LDR_PIN);
  // Read the analog value from the LDR sensor. Range is 0 (very dark) to 1023 (very bright)

  int brightness = map(lightValue, 0, 1023, 255, 20);
  // Map the LDR value to a brightness level for the LEDs
  // Brighter environments yield lower brightness because of inverted mapping

  brightness = constrain(brightness, 20, 255);
  // Ensure brightness stays within a reasonable range and does not drop below 20 or go above 255

  strip.setBrightness(brightness);
  // Apply the calculated brightness level to the LED strip. This affects how bright each pixel appears

  Serial.print("LDR: ");
  Serial.print(lightValue);           // Output raw analog LDR value

  Serial.print(" | Brightness: ");
  Serial.println(brightness);         // Print mapped brightness value and move to a new line

  // --- Run the current LED pattern ---
  switch (currentMode) {
    // Use switch to select which LED pattern to run based on currentMode

    case 0:
      if (modeChanged) Serial.println("Pattern: Color Wipe");
      // Print pattern name only if just changed
      colorCycle();  // Run the Color Wipe animation
      break;

    case 1:
      if (modeChanged) Serial.println("Pattern: Smooth RGB Fade");
      RGBLoop();     // Run the Smooth RGB Fade animation
      break;

    case 2:
      if (modeChanged) Serial.println("Pattern: Fire Effect");
      Fire(55, 120, 15); // Run the Fire Effect animation with given cooling sparking and speed
      break;

    case 3:
      if (modeChanged) Serial.println("Pattern: Rainbow Cycle");
      rainbowCycle(20);  // Run the Rainbow Cycle animation with a specified delay speed
      break;
  }

  modeChanged = false; // Reset flag so pattern name is not printed repeatedly
}

// -----------------------------------------------------------------------------
// Pattern 1: Color Wipe - Sequentially lights up each LED in Red, Green, Blue
// -----------------------------------------------------------------------------
void colorCycle() {
  static int state = 0;             // Keeps track of the current color phase: 0 = Red, 1 = Green, 2 = Blue
  static int index = 0;             // Tracks which LED is currently being lit in the sequence
  static uint32_t lastUpdate = 0;   // Stores the last time an LED was updated (for timing control)
  const uint32_t interval = 50;     // Time delay between lighting each LED in milliseconds

  // Check if enough time has passed since the last update
  if (millis() - lastUpdate < interval) return;
  lastUpdate = millis();            // Update the last update time to now

  // Set the color of the current LED based on the current state (R G or B)
  switch (state) {
    case 0:
      strip.setPixelColor(index, strip.Color(255, 0, 0)); // Red
      break;
    case 1:
      strip.setPixelColor(index, strip.Color(0, 255, 0)); // Green
      break;
    case 2:
      strip.setPixelColor(index, strip.Color(0, 0, 255)); // Blue
      break;
  }

  strip.show();   // Push the updated pixel color to the LEDs
  index++;        // Move to the next LED

  // If we have reached the end of the strip
  if (index >= NUM_LEDS) {
    index = 0;            // Reset to the first LED
    state = (state + 1) % 3; // Switch to the next color (R to G to B to R)
    setAll(0, 0, 0);      // Turn off all LEDs before starting the new color cycle
  }
}

// -----------------------------------------------------------------------------
// Pattern 2: RGB Fade - Fades entire strip from Red to Green to Blue
// -----------------------------------------------------------------------------
void RGBLoop() {
  static int j = 0;          // Tracks which color we are currently fading (0 = Red, 1 = Green, 2 = Blue)
  static int k = 0;          // Brightness level for fading (0 to 255)
  static bool fadeOut = false; // Flag to determine if we are fading out or in

  if (!fadeOut) {            // If we are currently fading in
    if (k < 256) {
      // Gradually increase brightness of one color
      switch(j) {
        case 0: setAll(k, 0, 0); break; // Fade in Red
        case 1: setAll(0, k, 0); break; // Fade in Green
        case 2: setAll(0, 0, k); break; // Fade in Blue
      }
      k++;                   // Increase brightness
    } else {
      fadeOut = true;        // When fully bright switch to fade out mode
    }
  } else {
    if (k > 0) {
      k--;                   // Decrease brightness
      // Gradually decrease brightness of the current color
      switch(j) {
        case 0: setAll(k, 0, 0); break; // Fade out Red
        case 1: setAll(0, k, 0); break; // Fade out Green
        case 2: setAll(0, 0, k); break; // Fade out Blue
      }
    } else {
      fadeOut = false;       // Switch back to fade in mode
      j = (j + 1) % 3;       // Move to the next color: R to G to B to R
    }
  }

  showStrip();               // Update the LEDs with the current color values
  delay(3);                  // Small delay to make the fade effect smooth
}

// -----------------------------------------------------------------------------
// Pattern 3: Fire - Simulates flickering flame using heat values
// -----------------------------------------------------------------------------
void Fire(int Cooling, int Sparking, int SpeedDelay) {
  static byte heat[NUM_LEDS]; // Array to store the heat of each LED (0 to 255)
  int cooldown;               // Temporary variable for cooling calculation

  // Step 1: Cool down each cell by a random amount
  for (int i = 0; i < NUM_LEDS; i++) {
    cooldown = random(0, ((Cooling * 10) / NUM_LEDS) + 2); // Random cooldown based on Cooling parameter
    heat[i] = (cooldown > heat[i]) ? 0 : heat[i] - cooldown; // Subtract cooldown or set to 0 if it goes below 0
  }

  // Step 2: Heat drifts upward and diffuses
  for (int k = NUM_LEDS - 1; k >= 2; k--) {
    // Take average of lower neighboring heat values to simulate upward movement of heat
    heat[k] = (heat[k - 1] + heat[k - 2] + heat[k - 2]) / 3;
  }

  // Step 3: Randomly ignite new sparks at the bottom
  if (random(255) < Sparking) {
    int y = random(7);                     // Pick a random pixel near the bottom (first 7 LEDs)
    heat[y] = heat[y] + random(160, 255);  // Add high heat to simulate a spark
  }

  // Step 4: Convert heat values to color and assign to each pixel
  for (int j = 0; j < NUM_LEDS; j++) {
    setPixelHeatColor(j, heat[j]);         // Convert heat to RGB color and set the LED color
  }

  showStrip();                 // Update LED strip with new colors
  delay(SpeedDelay);           // Delay to control the speed of the animation
}

// Helper for fire pattern: converts heat values into RGB flame like colors
void setPixelHeatColor(int Pixel, byte temperature) {
  // Scale the temperature (0 to 255) to a 0 to 191 range for color interpolation
  byte t192 = round((temperature / 255.0) * 191);

  // Get the lower 6 bits (0 to 63) to use as a color ramp
  byte heatramp = t192 & 0x3F;   // Equivalent to t192 % 64

  // Multiply by 4 to scale heatramp to the 0 to 252 range
  heatramp <<= 2;

  // Depending on how hot the pixel is assign an appropriate RGB color
  if (t192 > 0x80) {
    // Very hot - whitish yellow (full red and full green and increasing blue)
    setPixel(Pixel, 255, 255, heatramp);
  } else if (t192 > 0x40) {
    // Medium heat - orange yellow (full red and increasing green)
    setPixel(Pixel, 255, heatramp, 0);
  } else {
    // Cooler - shades of red (only red ramping up from dark to bright)
    setPixel(Pixel, heatramp, 0, 0);
  }
}

// -----------------------------------------------------------------------------
// Pattern 4: Rainbow Cycle - cycles a rainbow effect smoothly across all LEDs
// -----------------------------------------------------------------------------
void rainbowCycle(int SpeedDelay) {
  static uint16_t j = 0;  // Used to shift the rainbow over time and increments on each loop

  byte *c;                // Pointer to RGB color array returned by Wheel

  // Loop through every LED on the strip
  for (uint16_t i = 0; i < NUM_LEDS; i++) {
    // Calculate a color index for this LED using its position and animation offset j
    // The & 255 ensures it wraps within the 0 to 255 range for the color wheel
    c = Wheel(((i * 256 / NUM_LEDS) + j) & 255);

    // Set each LED to the color returned by the Wheel function
    setPixel(i, *c, *(c + 1), *(c + 2)); // Unpack RGB values from the returned array
  }

  showStrip();             // Update the LED strip with new colors
  delay(SpeedDelay);       // Delay to control animation speed
  j++;                     // Increment animation offset to move the rainbow forward
}

// Maps a wheel position (0 to 255) to RGB values to create a smooth rainbow gradient
byte* Wheel(byte WheelPos) {
  static byte c[3];        // Array to hold RGB color values (Red Green Blue)

  // First segment: Red to Green
  if (WheelPos < 85) {
    c[0] = WheelPos * 3;         // Red increases
    c[1] = 255 - WheelPos * 3;   // Green decreases
    c[2] = 0;                    // Blue remains 0
  }

  // Second segment: Green to Blue
  else if (WheelPos < 170) {
    WheelPos -= 85;
    c[0] = 255 - WheelPos * 3;   // Red decreases
    c[1] = 0;                    // Green remains 0
    c[2] = WheelPos * 3;         // Blue increases
  }

  // Third segment: Blue to Red
  else {
    WheelPos -= 170;
    c[0] = 0;                    // Red remains 0
    c[1] = WheelPos * 3;         // Green increases
    c[2] = 255 - WheelPos * 3;   // Blue decreases
  }

  return c; // Return pointer to RGB color array
}

// -----------------------------------------------------------------------------
// Helper functions for updating the strip
// -----------------------------------------------------------------------------

// Refresh the LED strip display
void showStrip() {
  #ifdef ADAFRUIT_NEOPIXEL_H
    strip.show();   // If using Adafruit NeoPixel library update LED states
  #endif
  #ifndef ADAFRUIT_NEOPIXEL_H
    FastLED.show(); // If not using NeoPixel fallback to FastLED for compatibility
  #endif
}

// Set the color of a specific pixel by index
void setPixel(int Pixel, byte red, byte green, byte blue) {
  #ifdef ADAFRUIT_NEOPIXEL_H
    strip.setPixelColor(Pixel, strip.Color(red, green, blue)); // NeoPixel syntax
  #endif
  #ifndef ADAFRUIT_NEOPIXEL_H
    leds[Pixel].r = red;    // FastLED syntax for red
    leds[Pixel].g = green;  // FastLED syntax for green
    leds[Pixel].b = blue;   // FastLED syntax for blue
  #endif
}

// Set all LEDs in the strip to the same RGB color
void setAll(byte red, byte green, byte blue) {
  for (int i = 0; i < NUM_LEDS; i++) {
    setPixel(i, red, green, blue); // Set color for each LED
  }
  showStrip();                     // Refresh strip to display updated colors
}
