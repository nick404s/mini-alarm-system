
#define IR_USE_AVR_TIMER1
#include <IRremote.h>
#define IR_RECEIVE_PIN 2

// remote IR receiver
IRrecv irrecv(IR_RECEIVE_PIN);
const int POWER_BUTTON = 69; // power button raw HEX = 0xBA45FF00

// the rgb pins
const int redPin = 9;  
const int greenPin = 10;
const int bluePin = 3;

// buzzer pin  
const int buzzerPin = 8;

// ultrasonic pins
const int triggerPin = 5;
const int echoPin = 6;
const int sonicDelay = 33;
const int alarmDistance = 5;

// alarm states
enum Alarm { ON, OFF, IDLE };
Alarm currentAlarmState = OFF;
Alarm previousAlarmState = OFF; 
bool isAlarm = false;

void setup() {
  // debug
  Serial.begin(9600);
  // initialize the rgb pins
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);
  // buzzer
  pinMode(buzzerPin, OUTPUT);
  // handle sonic
  pinMode(triggerPin, OUTPUT);
  pinMode(echoPin, INPUT);
  // remote
  IrReceiver.begin(IR_RECEIVE_PIN, ENABLE_LED_FEEDBACK);
}

int getSonicDistance(){
 delay(sonicDelay);
  // int distance = sonic.ping_cm();
  // got this solution to avoid library conflict from here: https://forum.arduino.cc/t/newping-tone-conflict/179755/2
  unsigned long duration;
  int distance;
  digitalWrite(triggerPin, HIGH);
  delay(1);
  digitalWrite(triggerPin, LOW);
  duration = pulseIn(echoPin, HIGH, 5700); // timeout if distance > 100 cm
  // calculate the distance by divide by round-trip microseconds per cm to get cm
  distance = duration / 57;
  return distance;
}

void displayRGB(int red, int green, int blue)
{
  // got some info from this tutorial: https://learn.sparkfun.com/tutorials/sik-experiment-guide-for-arduino---v32/experiment-3-driving-an-rgb-led
  analogWrite(redPin, red);
  analogWrite(greenPin, green);
  analogWrite(bluePin, blue);
  delay(10);
}

int index = 0;
int input[3];

int getRemoteCommand(){
  // got some info from here: https://github.com/Arduino-IRremote/Arduino-IRremote/blob/master/examples/SimpleReceiverForHashCodes/SimpleReceiverForHashCodes.ino
  int result = 0;
  if (IrReceiver.decode()) {
    result = IrReceiver.decodedIRData.command;
    
    IrReceiver.resume(); //receive the next value
    if(result){
      Serial.println(result);

      input[index] = result;
      index++;

      if(index > 2){
        index = 0;
      }

    }
  } 
  
  return result;
}

void alarmOff(){
  displayRGB(0, 0, 255);
  noTone(buzzerPin);
}

void alarmIdle(){
  displayRGB(0, 255, 0);
  noTone(buzzerPin);
}

void alarmOn(){
  displayRGB(255, 0, 0);
  runBuzzer(1500);
}

void runBuzzer(int volume){
  tone(buzzerPin, volume); // in Hz
  delay(50);
  noTone(buzzerPin);
  delay(50);
}

bool isPowerButtonPressed(byte remoteValue){
  return remoteValue && remoteValue == POWER_BUTTON;
}

const int secretNumbers[3] = {1, 5, 9};

bool isSecretMatch(){
  for(int i = 0; i < 3; i++){
    if(secretNumbers[i] != input[i]){
      return false;
    }
  }
  return true;
}

void loop() {

  // get input from remote control
  int remoteCommand = getRemoteCommand();

  // get distance to the object
  int sonicDistance = getSonicDistance();

  // for double clicks debounce
  int debounceDelay = 50;

  // alarm state control
  switch (currentAlarmState){
    case OFF:
      alarmOff();
      if (isPowerButtonPressed(remoteCommand)){
        Serial.print("=== off -> idle value: ");
        Serial.println(remoteCommand);
        currentAlarmState = IDLE;
      }
    break;
    case IDLE:
      alarmIdle();
      if(sonicDistance > alarmDistance && previousAlarmState == OFF){
        Serial.println("=== idle -> on. no value: ");
        currentAlarmState = ON;
      }
    break;
    case ON:
      alarmOn();
      if (isPowerButtonPressed(remoteCommand)){
        Serial.print("=== on -> off value: ");
        Serial.println(remoteCommand);
        currentAlarmState = OFF;
        delay(debounceDelay);
      }
    break;
    default:
      currentAlarmState = OFF;
    break;
  }
}