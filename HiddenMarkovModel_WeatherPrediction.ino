// Include the necessary libraries
#include <stdlib.h>

// Define the states
enum State {
  Rainy,
  Sunny
};

State current_state = Sunny; // Start with a sunny day

void setup() {
  Serial.begin(9600);
  randomSeed(analogRead(0)); // Use noise on analog pin 0 to seed the random number generator
}

void loop() {
  // Transition probabilities
  float transition_sunny_rainy = 0.1;
  float transition_rainy_sunny = 0.3;

  // Generate a random number between 0 and 1
  float rand = (float)random(1000) / 1000.0;

  // Update the current state based on the transition probabilities
  if (current_state == Sunny) {
    if (rand < transition_sunny_rainy) {
      current_state = Rainy;
    }
  } else { // current_state is Rainy
    if (rand < transition_rainy_sunny) {
      current_state = Sunny;
    }
  }

  // Print the current state
  if (current_state == Sunny) {
    Serial.println("Sunny");
  } else {
    Serial.println("Rainy");
  }

  delay(1000); // Wait for 1 second
}
