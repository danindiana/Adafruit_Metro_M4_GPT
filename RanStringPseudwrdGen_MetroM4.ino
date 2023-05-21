#define NUMBER_MIN 1
#define NUMBER_MAX 999999
#define LENGTH_MIN 5 // User can modify this value to their preferred minimum string length
#define LENGTH_MAX 15 // User can modify this value to their preferred maximum string length

const char* consonants = "bcdfghjklmnpqrstvwxyz";
const char* vowels = "aeiou";

void setup() {
  // Open serial communications and wait for port to open:
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }

  // Initialize random seed:
  randomSeed(analogRead(0));
}

void loop() {
  Serial.println("Random Number:");
  Serial.println(random(NUMBER_MIN, NUMBER_MAX + 1));
  delay(1000);

  int randomStringLength = random(LENGTH_MIN, LENGTH_MAX + 1);
  Serial.println("Random Alphanumeric String of length " + String(randomStringLength) + ":");
  Serial.println(generateRandomAlphanumericString(randomStringLength));
  delay(1000);

  int randomPseudowordLength = random(LENGTH_MIN, LENGTH_MAX + 1);
  Serial.println("Random Pseudoword of length " + String(randomPseudowordLength) + ":");
  Serial.println(generatePseudoword(randomPseudowordLength));
  delay(1000);
}

String generateRandomAlphanumericString(int length) {
  String randomString = "";
  for (int i = 0; i < length; i++)
  {
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
  for (int i = 0; i < length; i++)
  {
    if (i % 2 == 0)
      word += consonants[random(0, strlen(consonants) - 1)];
    else
      word += vowels[random(0, strlen(vowels) - 1)];
  }
  return word;
}
