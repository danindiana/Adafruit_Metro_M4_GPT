#define INTERVALS 1000000

void setup() {
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }
  randomSeed(analogRead(0)); //Initialize the pseudo-random number generator with a somewhat random input
}

void loop() {
  uint32_t circle_points = 0;
  uint32_t total_points = 0;
  
  // Generate random points and count how many fall inside the circle
  for (uint32_t i = 0; i < INTERVALS; i++) {
    float rand_x = ((float)(random(UINT32_MAX))) / ((float)UINT32_MAX); // Random x position
    float rand_y = ((float)(random(UINT32_MAX))) / ((float)UINT32_MAX); // Random y position

    // Distance from (0, 0) using the Pythagorean theorem
    float dist = sqrt(rand_x * rand_x + rand_y * rand_y);

    // Check if point lies inside the circle
    if (dist <= 1.0) {
      circle_points++;
    }

    total_points++;
  }

  // Compute and display the estimated value of pi
  float pi = 4 * ((float)circle_points / total_points);
  Serial.print("Estimated value of Pi = ");
  Serial.println(pi, 6); // Print estimated value of pi with 6 decimal places

  delay(5000); // Wait for 5 seconds
}
