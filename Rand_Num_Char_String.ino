#include <arduino.h>
#include <sam.h>

// Function to initialize the hardware random number generator on the ATSAMD51
void initRNG() {
  // Enable the APBC clock for the RNG
  MCLK->APBCMASK.reg |= MCLK_APBCMASK_TRNG;

  // Set up and enable the RNG
  TRNG->CTRLA.reg = TRNG_CTRLA_ENABLE;
}

// Function to generate a random number using the hardware RNG
uint32_t getRandomNumber() {
  while (TRNG->INTFLAG.bit.DATARDY == 0);  // Wait for a random number to be ready
  return TRNG->DATA.reg;  // Read the random number
}

void setup() {
  Serial.begin(9600);
  while (!Serial);

  initRNG();
}

void loop() {
  uint32_t randNum = getRandomNumber();
  char alphanumeric[9];
  
  for(int i = 0; i < 8; i++) {
    uint8_t randVal = (randNum >> (i * 4)) & 0x0F;
    if (randVal < 10)
      alphanumeric[i] = '0' + randVal;
    else
      alphanumeric[i] = 'A' + (randVal - 10);
  }

  alphanumeric[8] = '\0';  // Null-terminate the string

  Serial.print("Random Number: ");
  Serial.print(randNum);
  Serial.print(", Alphanumeric String: ");
  Serial.println(alphanumeric);

  delay(1000);
}
