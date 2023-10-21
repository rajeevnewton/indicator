const int leftIndicatorPin = 9;  // Pin for the left indicator
const int rightIndicatorPin = 8; // Pin for the right indicator
const int button1Pin = A0;        // Pin for button 1
const int button2Pin = A2;        // Pin for button 2

int leftIndicatorState = HIGH;     // Current state of the left indicator
int rightIndicatorState = HIGH;    // Current state of the right indicator

unsigned long previousMillis = 0;  // will store last time button was updated
const long interval = 2000;  // interval at which to blink (milliseconds)

void setup() {

  Serial.begin(115200);
  Serial.println("Turn Indicator");
  pinMode(leftIndicatorPin, OUTPUT);
  pinMode(rightIndicatorPin, OUTPUT);
  pinMode(button1Pin, INPUT);
  pinMode(button2Pin, INPUT);
}

int flag = 0;

bool superBikeFlashingEnabled = false;

int button1Prev = 0;
int button2Prev = 0;
int button1State = 0;
int button2State = 0;

void loop() {
  // Read the state of button 1 and button 2
  button1State = digitalRead(button1Pin);
  button2State = digitalRead(button2Pin);

  //capture send it to sequence
  if ( ( ( button1Prev != button1State ) || ( button2Prev != button2State ) ) && ( ( button1State == LOW ) || ( button2State == LOW ) ) ) {

    button1Prev = button1State;
    button2Prev = button2State;
    flag = flag + 1;
    Serial.println("Flag: ");
    Serial.println(flag);

    if ( flag == 3 ){
    flag = 0;
     Serial.println("This is super Bike");
     superBikeFlashingEnabled = true; 
     superBikeFlashing();
    }

  }
  
  if (button1State == LOW && button2State == HIGH  ) {
    // Button 1 is pressed, blink the left indicator
    blinkLeftIndicator();
    Serial.println("Left");
  }
  if (button1State == HIGH && button2State == LOW) {
    // Button 2 is pressed, blink the right indicator
    blinkRightIndicator();
    Serial.println("Right");
  }
  if (button1State == HIGH && button2State == HIGH){
    // Both buttons are released, turn off both indicators
    turnOffIndicators();
    // Serial.println("Neutral");
  }
  delay(10);
  
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;
    flag = 0;
  }

}

void blinkLeftIndicator() {
  digitalWrite(rightIndicatorPin, LOW); // Turn off the right indicator
  leftIndicatorState = !leftIndicatorState; // Toggle the state
  digitalWrite(leftIndicatorPin, leftIndicatorState); // Update the left indicator state
  if ( HIGH == digitalRead(button1Pin) && HIGH == digitalRead(button2Pin) ){
    superBikeFlashingEnabled = false;
    return;
   } 
  delay(100); // Adjust the delay time for the blink rate
  if ( HIGH == digitalRead(button1Pin) && HIGH == digitalRead(button2Pin) ){
    superBikeFlashingEnabled = false;
    return;
   } 
  delay(100); // Adjust the delay time for the blink rate
}

void blinkRightIndicator() {
  digitalWrite(leftIndicatorPin, LOW); // Turn off the left indicator
  rightIndicatorState = !rightIndicatorState; // Toggle the state
  digitalWrite(rightIndicatorPin, rightIndicatorState); // Update the right indicator state
  if ( HIGH == digitalRead(button1Pin) && HIGH == digitalRead(button2Pin) ){
    superBikeFlashingEnabled = false;
    return;
   } 
  delay(100); // Adjust the delay time for the blink rate
  if ( HIGH == digitalRead(button1Pin) && HIGH == digitalRead(button2Pin) ){
    superBikeFlashingEnabled = false;
    return;
   } 
  delay(100); // Adjust the delay time for the blink rate
}

void turnOffIndicators() {
  digitalWrite(leftIndicatorPin, LOW);
  digitalWrite(rightIndicatorPin, LOW);
}

void superBikeFlashing() {

  if (!superBikeFlashingEnabled) {
    return;
  }

  if ( LOW == digitalRead(button1Pin) && LOW == digitalRead(button2Pin) ){
    superBikeFlashingEnabled = false;
    return;
  }

  while (superBikeFlashingEnabled) {
    
    if ( HIGH == digitalRead(button1Pin) && HIGH == digitalRead(button2Pin) ){
      superBikeFlashingEnabled = false;
      return;
    }

    // Style 1: Rapid Alternating Flashes
    for (int i = 0; i < 4; i++) {
      digitalWrite(leftIndicatorPin, HIGH);
      digitalWrite(rightIndicatorPin, LOW);
      delay(100);
      if ( HIGH == digitalRead(button1Pin) && HIGH == digitalRead(button2Pin) ){
        superBikeFlashingEnabled = false;
        return;
      } 
      digitalWrite(leftIndicatorPin, LOW);
      digitalWrite(rightIndicatorPin, HIGH);
      delay(100);
      if ( HIGH == digitalRead(button1Pin) && HIGH == digitalRead(button2Pin) ){
        superBikeFlashingEnabled = false;
        return;
      } 
    }
      // Pause between styles

    delay(150);
    if ( HIGH == digitalRead(button1Pin) && HIGH == digitalRead(button2Pin) ){
      superBikeFlashingEnabled = false;
      return;
    }
    // Style 2: Simultaneous Flashing
    digitalWrite(leftIndicatorPin, HIGH);
    digitalWrite(rightIndicatorPin, HIGH);
    delay(100);
    if ( HIGH == digitalRead(button1Pin) && HIGH == digitalRead(button2Pin) ){
        superBikeFlashingEnabled = false;
        return;
    } 
    digitalWrite(leftIndicatorPin, LOW);
    digitalWrite(rightIndicatorPin, LOW);
    delay(100);
    if ( HIGH == digitalRead(button1Pin) && HIGH == digitalRead(button2Pin) ){
        superBikeFlashingEnabled = false;
        return;
    } 
    // Pause between styles
    delay(150);
    if ( HIGH == digitalRead(button1Pin) && HIGH == digitalRead(button2Pin) ){
      superBikeFlashingEnabled = false;
      return;
    }
    // Style 3: Alternating Fast Flash
    for (int i = 0; i < 3; i++) {
      digitalWrite(leftIndicatorPin, HIGH);
      delay(100);
      if ( HIGH == digitalRead(button1Pin) && HIGH == digitalRead(button2Pin) ){
        superBikeFlashingEnabled = false;
        return;
      }      
      digitalWrite(leftIndicatorPin, LOW);
      delay(100);
      if ( HIGH == digitalRead(button1Pin) && HIGH == digitalRead(button2Pin) ){
        superBikeFlashingEnabled = false;
        return;
      } 
      digitalWrite(rightIndicatorPin, HIGH);
      delay(100);
      if ( HIGH == digitalRead(button1Pin) && HIGH == digitalRead(button2Pin) ){
        superBikeFlashingEnabled = false;
        return;
      } 
      digitalWrite(rightIndicatorPin, LOW);
      delay(100);
      if ( HIGH == digitalRead(button1Pin) && HIGH == digitalRead(button2Pin) ){
        superBikeFlashingEnabled = false;
        return;
      } 
    }
  }
}
