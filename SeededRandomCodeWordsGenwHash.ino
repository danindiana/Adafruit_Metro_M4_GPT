#include <Arduino.h>

// Function to initialize the hardware random number generator on the ATSAMD51
void initRNG() {
  // Enable the APBC clock for the RNG
  MCLK->APBCMASK.reg |= MCLK_APBCMASK_TRNG;

  // Set up and enable the RNG
  TRNG->CTRLA.reg = TRNG_CTRLA_ENABLE;
}

// Function to generate a random number using the hardware RNG
uint32_t getRandomNumber(uint8_t seed) {
  while (TRNG->INTFLAG.bit.DATARDY == 0);  // Wait for a random number to be ready
  return TRNG->DATA.reg ^ (static_cast<uint32_t>(seed) << 24);  // Read the random number and XOR with the seed
}

char randomCharacter(uint8_t seed) {
  uint8_t randVal = getRandomNumber(seed) % 36;
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
  
  Serial.println("Enter an alphanumeric string to seed the random generator and press enter.");
  Serial.println("The string can be of any length and should contain only alphabets (A-Z, a-z) and numbers (0-9).");
}

String inputSeed = "";
bool isSeeded = false;

void loop() {
  if (!isSeeded) {
    if (Serial.available() > 0) {
      char c = Serial.read();
      if (c == '\n') {
        isSeeded = true;
        Serial.println("Random Code Word generation started...");
      } else if (isalnum(c)) {
        inputSeed += c;
      } else {
        Serial.println("Only alphanumeric characters are allowed.");
      }
    }
  } else {
    const int codeWordLength = 8;
    char codeWord[codeWordLength + 1];

    for (int i = 0; i < codeWordLength; i++) {
      codeWord[i] = randomCharacter(inputSeed[i % inputSeed.length()]);
    }

    codeWord[codeWordLength] = '\0'; // Null-terminate the string
    
    Serial.print("Random Code Word: ");
    Serial.println(codeWord);

    delay(1000);
  }
}
