#define STRING_LENGTH 10

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
  Serial.println(random(10000, 99999));
  delay(1000);

  char randomString[STRING_LENGTH + 1];
  for (int i = 0; i < STRING_LENGTH; i++)
  {
    byte randomValue = random(0, 62);
    if (randomValue < 10)
      randomString[i] = '0' + randomValue;
    else if (randomValue < 36)
      randomString[i] = 'A' + randomValue - 10;
    else
      randomString[i] = 'a' + randomValue - 36;
  }
  randomString[STRING_LENGTH] = 0; // null character
  Serial.println("Random Alphanumeric String:");
  Serial.println(randomString);
  delay(1000);

  Serial.println("Random Pseudoword:");
  Serial.println(generatePseudoword());
  delay(1000);
}

String generatePseudoword() {
  String word = "";
  for (int i = 0; i < STRING_LENGTH; i++)
  {
    if (i % 2 == 0)
      word += consonants[random(0, strlen(consonants) - 1)];
    else
      word += vowels[random(0, strlen(vowels) - 1)];
  }
  return word;
}
