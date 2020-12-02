# arduinoDue_NeoPixel_TimerInterrupt

- Polls the voltage on pin A1 every 500ms using a timer interrupt on TC0, channel 0, at a frequency of 1MHz.
- Statemachine contains four states (A - D), where the state depends on the voltage measured on pin A1.
- Depending on the state, the NeoPixelController object will make the LEDs in the ledstrip glow a different color (red, orange, yellow, green)
