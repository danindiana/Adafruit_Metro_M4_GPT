#define NUMBER_MIN 1
#define NUMBER_MAX 999999
#define LENGTH_MIN 5
#define LENGTH_MAX 15

const char* consonants = "bcdfghjklmnpqrstvwxyz";
const char* vowels = "aeiou";

void setup() {
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }

  // Initialize TRNG:
  MCLK->APBCMASK.bit.TRNG_ = 1;
  TRNG->CTRLA.bit.ENABLE = 1;
}

void loop() {
  Serial.println("Random Number:");
  int randomNumber = get_trng() % (NUMBER_MAX - NUMBER_MIN + 1) + NUMBER_MIN;
  Serial.println(randomNumber);
  delay(1000);

  int randomStringLength = get_trng() % (LENGTH_MAX - LENGTH_MIN + 1) + LENGTH_MIN;
  String randomString = generateRandomAlphanumericString(randomStringLength);
  Serial.println("Random Alphanumeric String of length " + String(randomStringLength) + ":");
  Serial.println(randomString);
  Serial.println("Estimated Chain Rule Kolmogorov complexity: " + String(estimateChainRuleKolmogorovComplexity(randomString)));
  delay(1000);

  int randomPseudowordLength = get_trng() % (LENGTH_MAX - LENGTH_MIN + 1) + LENGTH_MIN;
  String pseudoWord = generatePseudoword(randomPseudowordLength);
  Serial.println("Random Pseudoword of length " + String(randomPseudowordLength) + ":");
  Serial.println(pseudoWord);
  Serial.println("Estimated Chain Rule Kolmogorov complexity: " + String(estimateChainRuleKolmogorovComplexity(pseudoWord)));
  delay(1000);
}

String generateRandomAlphanumericString(int length) {
  String randomString = "";
  for (int i = 0; i < length; i++) {
    byte randomValue = get_trng() % 62;
    if (randomValue < 10)
      randomString += '0' + randomValue;
    else if (randomValue < 36)
      randomString += 'A' + randomValue - 10;
    else
      randomString += 'a' + randomValue - 36;
  }
  return randomString;
}

String generatePseudoword(int length) {
  String word = "";
  for (int i = 0; i < length; i++) {
    if (i % 2 == 0)
      word += consonants[get_trng() % strlen(consonants)];
    else
      word += vowels[get_trng() % strlen(vowels)];
  }
  return word;
}

int estimateChainRuleKolmogorovComplexity(String input) {
  int n = input.length();
  if (n <= 1) return n;
  
  int complexity = estimateSimpleComplexity(input.substring(0, 1));

  for (int i = 1; i < n; i++) {
    complexity += estimateSimpleComplexity(input.substring(i, i+1) + input.substring(0, i));
  }

  return complexity;
}

int estimateSimpleComplexity(String input) {
  String compressed = "";
  int count = 1;
  for (int i = 0; i < input.length(); i++) {
    if (input[i] == input[i + 1] && i < input.length() - 1) {
      count++;
    } else {
      compressed += input[i];
      if (count > 1) {
        compressed += String(count);
      }
      count = 1;
    }
  }
  return compressed.length();
}

uint32_t get_trng() {
  while ((TRNG->INTFLAG.reg & TRNG_INTFLAG_MASK) == 0) ;  
  return (TRNG->DATA.reg);
}
