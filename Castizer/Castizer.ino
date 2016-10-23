/*
 * CASTIZER
 * Pablo Garcia
 * 
 * 
 * 
*/

#include <Potentiometer.h>
// Example and instructions: http://playground.arduino.cc/Code/Potentiometer#Functions

#define SW_ONOFF_PIN 2
//#define LED_ONOFF_PIN 8
#define LED_ONOFF_PIN LED_BUILTIN
#define POT_VOLUME_PIN 0
#define POT_DIAL_PIN 1
#define JOY_X_PIN 2
#define JOY_Y_PIN 3
#define JOY_BUTTON_PIN 4


int sw_onoff_val, sw_onoff_val_old;
int pot_volume_sector, pot_volume_sector1, pot_volume_sector2, pot_volume_sector_old;
int pot_dial_sector, pot_dial_sector_old;
int joy_button_val, joy_button_val_old;

int ledBlinkingState = LOW;
// Generally, you should use "unsigned long" for variables that hold time
// The value will quickly become too large for an int to store
unsigned long previousMillis = 0;        // will store last time LED was updated
const long interval = 1000;           // interval at which to blink (milliseconds)

int joyX = 0;
int joyY = 0;
int joyButton = 0;


Potentiometer potVolume = Potentiometer(POT_VOLUME_PIN);
Potentiometer potDial = Potentiometer(POT_DIAL_PIN);



int readPot()
{

  char pot_dial_sector_str[10];
  
  pot_dial_sector = potDial.getSector();
  if (pot_dial_sector != pot_dial_sector_old){
    pot_dial_sector_old = pot_dial_sector;
    Serial.print("C");
    sprintf(pot_dial_sector_str, "%02d", pot_dial_sector);
    Serial.print(pot_dial_sector_str);
    Serial.println();
    Serial.println(potDial.getValue(),DEC);
  }
  delay(200);

}


int readOnOffSwitch()
{

  sw_onoff_val = digitalRead(SW_ONOFF_PIN);
  if (sw_onoff_val != sw_onoff_val_old){
    sw_onoff_val_old = sw_onoff_val;
    Serial.print("S");
    if (sw_onoff_val==HIGH){
      Serial.print("01");
      digitalWrite(LED_ONOFF_PIN, HIGH);
    }
    else{
      Serial.print("00");
      digitalWrite(LED_ONOFF_PIN, LOW);
    }
    Serial.println();
  }
  
}

int readVolume()
{

  char pot_volume_sector_str[10];
  
  pot_volume_sector1 = potVolume.getSector();
  delay(100);
  pot_volume_sector2 = potVolume.getSector();
  pot_volume_sector = (pot_volume_sector1+pot_volume_sector2)/2;
  if (pot_volume_sector != pot_volume_sector_old){
    pot_volume_sector_old = pot_volume_sector;
    Serial.print("V");
    //Serial.println(potVolume.getValue(),DEC);
    sprintf(pot_volume_sector_str, "%02d", pot_volume_sector);
    Serial.print(pot_volume_sector_str);
    Serial.println();
  }

}

int readDial()
{

  char pot_dial_sector_str[10];
  
  pot_dial_sector = (potDial.getSector())/2;
  if (pot_dial_sector != pot_dial_sector_old){
    pot_dial_sector_old = pot_dial_sector;
    Serial.print("C");
    //Serial.println(potDial.getValue(),DEC);
    sprintf(pot_dial_sector_str, "%02d", pot_dial_sector);
    Serial.print(pot_dial_sector_str);
    Serial.println();
  }

}


int readJoystick()
{

/*
  joyX = analogRead(JOY_X_PIN);
  joyY = analogRead(JOY_Y_PIN);
  joyButton = digitalRead(JOY_BUTTON_PIN);

  Serial.print("X: ");
  Serial.print(joyX);
  Serial.print(" | Y: ");
  Serial.print(joyY);
  Serial.print(" | Button: ");
  Serial.println(joyButton);

  delay(100); // add some delay between reads
*/

  joy_button_val = digitalRead(JOY_BUTTON_PIN);
  if (joy_button_val != joy_button_val_old){
    joy_button_val_old = joy_button_val;
    Serial.print("J");
    if (joy_button_val==HIGH){
      // button is released
      Serial.print("00");
    }
    else{
      // button is clicked
      Serial.print("01");
    }
    Serial.println();
  }
  
  
}
  



// the setup function runs once when you press reset or power the board
void setup() {

  // initialize digital pin LED_BUILTIN as an output.
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(LED_ONOFF_PIN, OUTPUT);
  pinMode(SW_ONOFF_PIN, INPUT);
  pinMode(POT_VOLUME_PIN, INPUT);
  pinMode(POT_DIAL_PIN, INPUT);

  // Joystick
  pinMode(JOY_X_PIN, INPUT);
  pinMode(JOY_Y_PIN, INPUT);
  //activate pull-up resistor on the push-button pin
  pinMode(JOY_BUTTON_PIN, INPUT_PULLUP); 

  //delay(30000);

  Serial.begin(9800);
  //Serial.println("Castizer control program");
  potVolume.setSectors(10);
  potDial.setSectors(10);
  delay(2000);
  Serial.println("SSS");

  pot_volume_sector_old = -1;
  sw_onoff_val_old = -1;
  joy_button_val_old = -1;
  pot_dial_sector_old = -1;

}

// the loop function runs over and over again forever
void loop() {

  unsigned long currentMillis = millis();

//TODO: Al iniciar mandar el estado del switch y el volumen y el canal...

  if (currentMillis - previousMillis >= interval) {
    // save the last time you blinked the LED
    previousMillis = currentMillis;

    // if the LED is off turn it on and vice-versa:
    if (ledBlinkingState == LOW) {
      ledBlinkingState = HIGH;
    } else {
      ledBlinkingState = LOW;
    }

    // set the LED with the ledState of the variable:
    //digitalWrite(LED_BUILTIN, ledBlinkingState);
  }

  readVolume();
  readDial();
  readOnOffSwitch();
  readJoystick();
  
  //readPot();
  
  delay(50);

  //digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on (HIGH is the voltage level)
  //digitalWrite(LED_BUILTIN, LOW);

}
