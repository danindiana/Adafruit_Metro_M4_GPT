#include <arduinoFFT.h> 

#define MAX_SAMPLE_SIZE 1024  // Maximum size
#define SAMPLING_FREQUENCY 500 // Assuming a 500 Hz sample rate

double vReal[MAX_SAMPLE_SIZE];
double vImag[MAX_SAMPLE_SIZE];

arduinoFFT FFT = arduinoFFT(vReal, vImag, MAX_SAMPLE_SIZE, SAMPLING_FREQUENCY);

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
    FFT.Windowing(FFT_WIN_TYP_HAMMING, FFT_FORWARD);
    FFT.Compute(FFT_FORWARD);
    FFT.ComplexToMagnitude();

    // Print the FFT results to the Serial monitor
    Serial.println("FFT results (Frequency bin : Magnitude):");
    for (uint16_t i = 0; i < size / 2; i++) {
      float freq = (i * 1.0 * SAMPLING_FREQUENCY) / size;
      Serial.print(freq);
      Serial.print(" Hz : ");
      Serial.println(vReal[i]);
    }
    Serial.println();

    // Inverse FFT
    FFT.Windowing(FFT_WIN_TYP_HAMMING, FFT_REVERSE);
    FFT.Compute(FFT_REVERSE);
    FFT.ComplexToMagnitude();

    // Print the Inverse FFT results to the Serial monitor
    Serial.println("Inverse FFT results:");
    for (uint16_t i = 0; i < size; i++) {
      Serial.print(i);
      Serial.print(" : ");
      Serial.println(vReal[i]);
    }
    Serial.println();

    // Give some delay between loops
    delay(5000);
  }
}
