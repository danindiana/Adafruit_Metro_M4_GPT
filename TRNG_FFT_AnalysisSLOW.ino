#include <arduinoFFT.h>

#define SAMPLING_FREQUENCY 1000  // Maximum expected frequency
#define BUFFER_SIZE 100

unsigned int sampling_period_us;
unsigned long microseconds;

double vReal[BUFFER_SIZE];
double vImag[BUFFER_SIZE];

arduinoFFT FFT = arduinoFFT();

void setup() {
  Serial.begin(115200);
  while (!Serial)
    ;

  Serial.println("TRNG test\n");
  MCLK->APBCMASK.bit.TRNG_ = 1;  // enable clock  (APBC clock is already enabled)
  TRNG->CTRLA.bit.ENABLE = 1;    // enable the TRNG

  sampling_period_us = round(1000*(1.0/SAMPLING_FREQUENCY));

  for(uint16_t i=0; i<BUFFER_SIZE; i++){
    vImag[i] = 0;
  }
}

uint32_t get_trng() {
  while ((TRNG->INTFLAG.reg & TRNG_INTFLAG_MASK) == 0)
    ;  // Busy loop waiting for next RN to be created
  return (TRNG->DATA.reg);   // return the new number.
}

void loop() {
  microseconds = micros();

  for(uint16_t i=0; i<BUFFER_SIZE; i++){
    vReal[i] = get_trng();
    Serial.print("Buffer at index ");
    Serial.print(i);
    Serial.print(" : ");
    Serial.println(vReal[i]);
    while(micros() - microseconds < sampling_period_us){
      // wait for sampling period to pass
    }
    microseconds += sampling_period_us;
  }

  Serial.println("Performing FFT computation");
  FFT.Windowing(vReal, BUFFER_SIZE, FFT_WIN_TYP_HAMMING, FFT_FORWARD);
  FFT.Compute(vReal, vImag, BUFFER_SIZE, FFT_FORWARD);
  FFT.ComplexToMagnitude(vReal, vImag, BUFFER_SIZE);

  double peak = FFT.MajorPeak(vReal, BUFFER_SIZE, SAMPLING_FREQUENCY);
  Serial.println(peak);  //Print out frequency of audio peak
  
  Serial.println("Completed FFT computation");
  delay(1000);
}
