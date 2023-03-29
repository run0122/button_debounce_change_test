const int buttonPin = 2;  // the number of the pushbutton pin
const int ledPin1 = 4;
const int ledPin2 = 5;    // the number of the LED pin

int pushed = 0;
int pushedcount = 1;

// Variables will change:
int ledState1 = HIGH;        // the current state of the output pin
int ledState2 = LOW;
int buttonState;            // the current reading from the input pin
int lastButtonState = LOW;  // the previous reading from the input pin

// the following variables are unsigned longs because the time, measured in
// milliseconds, will quickly become a bigger number than can be stored in an int.
unsigned long lastDebounceTime = 0;  // the last time the output pin was toggled
unsigned long debounceDelay = 50;    // the debounce time; increase if the output flickers

void setup() {
  pinMode(buttonPin, INPUT);
  pinMode(ledPin1, OUTPUT);
  pinMode(ledPin2, OUTPUT);

  // set initial LED state
  digitalWrite(ledPin1, ledState1);
  digitalWrite(ledPin2, ledState2);
}

void loop() {
  // read the state of the switch into a local variable:
  int reading = digitalRead(buttonPin);

  // check to see if you just pressed the button
  // (i.e. the input went from LOW to HIGH), and you've waited long enough
  // since the last press to ignore any noise:

  // If the switch changed, due to noise or pressing:
  if (reading != lastButtonState) {
    // reset the debouncing timer
    lastDebounceTime = millis();
  }

  if ((millis() - lastDebounceTime) > debounceDelay) {
    // whatever the reading is at, it's been there for longer than the debounce
    // delay, so take it as the actual current state:

    // if the button state has changed:
    if (reading != buttonState) {
      buttonState = reading;
      
      // only toggle the LED if the new button state is HIGH
      if (buttonState == HIGH) {
        pushedcount++;
        if((pushedcount%4)==1){
          ledState1=HIGH;
          ledState2=LOW;
        }
        if((pushedcount%4)==2){
          ledState1=LOW;
          ledState2=HIGH;
        }
        if((pushedcount%4)==3){
          ledState1=HIGH;
          ledState2=HIGH;
        }
        if((pushedcount%4)==0){
          ledState1=LOW;
          ledState2=LOW;
        }
      }
    }
  }

  // set the LED:
  digitalWrite(ledPin1, ledState1);
  digitalWrite(ledPin2, ledState2);

  // save the reading. Next time through the loop, it'll be the lastButtonState:
  lastButtonState = reading;
}
