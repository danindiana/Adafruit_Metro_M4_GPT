#include <arduino.h>
#include <sam.h>

// Function to initialize the hardware random number generator on the ATSAMD51
void initRNG() {
  MCLK->APBCMASK.reg |= MCLK_APBCMASK_TRNG;
  TRNG->CTRLA.reg = TRNG_CTRLA_ENABLE;
}

// Function to generate a random number using the hardware RNG
uint32_t getRandomNumber() {
  while (TRNG->INTFLAG.bit.DATARDY == 0);
  return TRNG->DATA.reg;
}

// Generate an alphanumeric string of specified length from a random number
String randAlphanumeric(uint32_t randNum, int length) {
  String alphanumeric = "";
  for(int i = 0; i < length; i++) {
    uint8_t randVal = (randNum >> (i * 4)) & 0x0F;
    if (randVal < 10)
      alphanumeric += '0' + randVal;
    else
      alphanumeric += 'A' + (randVal - 10);
  }
  return alphanumeric;
}

// Generate a pseudoword of specified length
String generatePseudoWord(int length) {
  const String consonants = "bcdfghjklmnpqrstvwxyz";
  const String vowels = "aeiou";
  String pseudoWord = "";
  
  for (int i = 0; i < length; i++) {
    uint32_t randNum = getRandomNumber();
    uint8_t randVal = (randNum >> (i * 2)) & 0x0F;
    if (i % 2 == 0) 
      pseudoWord += consonants[randVal % consonants.length()];
    else
      pseudoWord += vowels[randVal % vowels.length()];
  }
  
  return pseudoWord;
}

void setup() {
  Serial.begin(9600);
  while (!Serial);

  initRNG();
}

void loop() {
  int length = 8;  // Set your desired length here
  uint32_t randNum = getRandomNumber();
  String alphanumeric = randAlphanumeric(randNum, length);
  String pseudoWord = generatePseudoWord(length);

  Serial.print("Random Number: ");
  Serial.print(randNum);
  Serial.print(", Alphanumeric String: ");
  Serial.print(alphanumeric);
  Serial.print(", Pseudo Word: ");
  Serial.println(pseudoWord);

  delay(1000);
}
