#include <Arduino.h>

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

char randomCharacter() {
  uint8_t randVal = getRandomNumber() % 36;
  if (randVal < 10) {
    return '0' + randVal;
  } else {
    return 'A' + (randVal - 10);
  }
}

void setup() {
  Serial.begin(9600);
  while (!Serial);

  initRNG();
}

void loop() {
  const int codeWordLength = 8;
  char codeWord[codeWordLength + 1];

  for (int i = 0; i < codeWordLength; i++) {
    codeWord[i] = randomCharacter();
  }

  codeWord[codeWordLength] = '\0'; // Null-terminate the string
  
  Serial.print("Random Code Word: ");
  Serial.println(codeWord);

  delay(1000);
}
