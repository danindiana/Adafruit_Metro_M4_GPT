#include <Adafruit_ZeroFFT.h>
#include <sam.h>

#define MAX_SAMPLE_SIZE 1024  // Maximum size
#define SAMPLING_FREQUENCY 500 // Assuming a 500 Hz sample rate

int16_t vReal[MAX_SAMPLE_SIZE];
int16_t vImag[MAX_SAMPLE_SIZE];

void setup() {
  Serial.begin(115200);

  // Generate a test input signal, random data
  randomSeed(analogRead(0));  // Initialize random seed

  for (uint16_t i = 0; i < MAX_SAMPLE_SIZE; i++) {
    vReal[i] = random(0, 1023) - 512;  // generate random data in the range of -512 to 511
    vImag[i] = 0;
  }
}

void loop() {
  // Test different FFT sizes
  for (uint16_t size = 16; size <= MAX_SAMPLE_SIZE; size *= 2) {
    Serial.println("Testing FFT size: " + String(size));

    // Perform FFT
    ZeroFFT(vReal, size);

    // Print the FFT results to the Serial monitor
    Serial.println("FFT results (Frequency bin : Magnitude):");
    for (uint16_t i = 0; i < size / 2; i++) {
      // Calculate the magnitude of the result (sqrt(re^2 + im^2))
      int16_t magnitude = sqrt(vReal[i] * vReal[i] + vImag[i] * vImag[i]);
      float freq = (i * 1.0 * SAMPLING_FREQUENCY) / size;
      Serial.print(freq);
      Serial.print(" Hz : ");
      Serial.println(magnitude);
    }
    Serial.println();
  }

  // Give some delay between loops
  delay(5000);
}
