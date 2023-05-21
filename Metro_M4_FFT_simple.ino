#include <Adafruit_ZeroFFT.h>
#include <sam.h>

#define SAMPLES 1024  // Must be a power of two
#define SAMPLING_FREQUENCY 500 // Assuming a 500 Hz sample rate

int16_t vReal[SAMPLES];
int16_t vImag[SAMPLES];

void setup() {
  Serial.begin(115200);

  // Generate a test input signal, a 5 Hz sine wave at 500 Hz sample rate
  for (uint16_t i = 0; i < SAMPLES; i++) {
    vReal[i] = 1000 * sin((2 * PI * 5 * i) / SAMPLES);  // reduce the amplitude to avoid overflow
    vImag[i] = 0;
  }

  // Print the test signal to the Serial monitor
  Serial.println("Test signal:");
  for (uint16_t i = 0; i < SAMPLES; i++) {
    Serial.println(vReal[i]);
  }
  Serial.println();
}

void loop() {
  // Apply window function (we'll use Blackman-Nuttall)
  for (uint16_t i = 0; i < SAMPLES; i++) {
    float multiplier = 0.355768 - 0.487396 * cos(2 * PI * i / (SAMPLES - 1)) + 0.144232 * cos(4 * PI * i / (SAMPLES - 1)) - 0.012604 * cos(6 * PI * i / (SAMPLES - 1));
    vReal[i] *= multiplier;
  }

  // Perform FFT
  ZeroFFT(vReal, SAMPLES);

  // Print the FFT results to the Serial monitor
  Serial.println("FFT results (Frequency bin : Magnitude):");
  for (uint16_t i = 0; i < SAMPLES / 2; i++) {
    // Calculate the magnitude of the result (sqrt(re^2 + im^2))
    int16_t magnitude = sqrt(vReal[i] * vReal[i] + vImag[i] * vImag[i]);
    float freq = (i * 1.0 * SAMPLING_FREQUENCY) / SAMPLES;
    Serial.print(freq);
    Serial.print(" Hz : ");
    Serial.println(magnitude);
  }
  Serial.println();

  // Give some delay between loops
  delay(2000);
}
