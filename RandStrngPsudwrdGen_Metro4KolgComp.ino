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
  randomSeed(analogRead(0));
}

void loop() {
  Serial.println("Random Number:");
  int randomNumber = random(NUMBER_MIN, NUMBER_MAX + 1);
  Serial.println(randomNumber);
  delay(1000);

  int randomStringLength = random(LENGTH_MIN, LENGTH_MAX + 1);
  String randomString = generateRandomAlphanumericString(randomStringLength);
  Serial.println("Random Alphanumeric String of length " + String(randomStringLength) + ":");
  Serial.println(randomString);
  Serial.println("Estimated Kolmogorov complexity: " + String(estimateKolmogorovComplexity(randomString)));
  delay(1000);

  int randomPseudowordLength = random(LENGTH_MIN, LENGTH_MAX + 1);
  String pseudoWord = generatePseudoword(randomPseudowordLength);
  Serial.println("Random Pseudoword of length " + String(randomPseudowordLength) + ":");
  Serial.println(pseudoWord);
  Serial.println("Estimated Kolmogorov complexity: " + String(estimateKolmogorovComplexity(pseudoWord)));
  delay(1000);
}

String generateRandomAlphanumericString(int length) {
  String randomString = "";
  for (int i = 0; i < length; i++) {
    byte randomValue = random(0, 62);
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
      word += consonants[random(0, strlen(consonants))];
    else
      word += vowels[random(0, strlen(vowels))];
  }
  return word;
}

int estimateKolmogorovComplexity(String input) {
  // Run-Length Encoding as a simple compression algorithm
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
