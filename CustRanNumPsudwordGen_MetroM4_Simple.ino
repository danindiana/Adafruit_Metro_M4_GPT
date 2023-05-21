#define NUMBER_MIN 1
#define NUMBER_MAX 999999
#define STRING_LENGTH 10 // User can modify this value to their preferred string length
#define PSEUDOWORD_LENGTH 8 // User can modify this value to their preferred pseudoword length

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

  Serial.println("Random Alphanumeric String:");
  Serial.println(generateRandomAlphanumericString(STRING_LENGTH));
  delay(1000);

  Serial.println("Random Pseudoword:");
  Serial.println(generatePseudoword(PSEUDOWORD_LENGTH));
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
