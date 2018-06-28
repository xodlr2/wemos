int LED4 = 2;    // Use D4
int LED3 = 0;    // Use D3

void setup() {
  // put your setup code here, to run once:
pinMode(LED3, OUTPUT);     // Initialize the LED pin as an output
pinMode(LED4, OUTPUT);     // Initialize the LED pin as an output
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(LED4, LOW);   // Turn the LED
  digitalWrite(LED3, HIGH);   // Turn the LED
  delay(1000);    // Wait for a seconds
  digitalWrite(LED4, HIGH);  // Turn the LED
  digitalWrite(LED3, LOW);   // Turn the LED
  delay(1000);    // Wait for a seconds
}
