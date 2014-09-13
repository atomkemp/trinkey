/***********
TrinKey example
written by atomkemp
@atomkemp

derived from Adafruit's Trinket Keyboard example

DON'T FORGET TO WRITE DOWN YOUR PASSWORDS....ON PAPER....THIS PROGRAM IS SUPPLIED AS-IS
AND I HOLD NO RESPONSIBLITY FOR LOST PASSWORDS AND LOCKED ACCOUNTS

This program is designed to generate 32bit passwords based on Google's password rules.
Change as needed, and read through the comments for full functionality and use.
************/


#include <TrinketKeyboard.h>
#include <EEPROM.h>

#define pass1Button 0
#define pass2Button 2
#define resetPass 1

void setup()
{ 
  // set up inputs
  pinMode(pass1Button, INPUT);
  pinMode(pass2Button, INPUT);
  pinMode(resetPass, INPUT);

  // set up outpus
  digitalWrite(pass1Button, HIGH);
  digitalWrite(pass2Button, HIGH);

  // start USB stuff
  TrinketKeyboard.begin();
}

void loop()
{
  // the poll function must be called at least once every 10 ms
  // or cause a keystroke
  // if it is not, then the computer may think that the device
  // has stopped working, and give errors
  TrinketKeyboard.poll();

  //checks for button1 to be pressed, then prints 32 bits from the first 32 EEPROM locations
  if (digitalRead(pass1Button) == LOW){
    pinMode(resetPass, OUTPUT);
    digitalWrite(resetPass, HIGH);
    for (int i = 0; i < 32; i++) {
      TrinketKeyboard.write(EEPROM.read(i));
    }
    digitalWrite(resetPass, LOW);
    pinMode(resetPass, INPUT);
  }

  //checks for button1 to be pressed, then prints 32 bits from the first 32 EEPROM locations
  else if (digitalRead(pass2Button) == LOW){
    pinMode(resetPass, OUTPUT);
    digitalWrite(resetPass, HIGH);
    // type out a string using the Print class
    for (int i = 32; i < 64; i++) {
      TrinketKeyboard.write(EEPROM.read(i));
    }
    digitalWrite(resetPass, LOW);
    pinMode(resetPass, INPUT);
  }

  //checks for a high pull on the pin1 pad. this will initialize a regen of both 32 bit passwords
  else if (digitalRead(resetPass) == HIGH){
    //reset them passwords
    resetPasses();
  }
}

//function to reset both passwords
void resetPasses() {
  int chooseChar = 0;
  
  //sets password 1 by polling one of four functions that generate a random character and writes it to EEPROM
  for (int i = 0; i < 32; i++) {
    TrinketKeyboard.poll();
    chooseChar = random(0,4);
    switch(chooseChar) {
      case 0:
        EEPROM.write(i,upper());
        break;
      case 1:
        EEPROM.write(i,lower());
        break;
      case 2:
        EEPROM.write(i,number());
        break;
      case 3:
        EEPROM.write(i,wild());
        break;
    }
  }
  
  //sets password 2 by polling one of four functions that generate a random character and writes it to EEPROM
  for (int i = 32; i < 64; i++) {
    TrinketKeyboard.poll();
    chooseChar = random(0,4);
    switch(chooseChar) {
      case 0:
        EEPROM.write(i,upper());
        break;
      case 1:
        EEPROM.write(i,lower());
        break;
      case 2:
        EEPROM.write(i,number());
        break;
      case 3:
        EEPROM.write(i,wild());
        break;
    }
  }
}
        
//the uppercase alphabet
byte upper() {
  int temp = 0;
  temp = random(65,90); //A-Z
  return temp;
}

//the lowercase alphabet
byte lower() {
  int temp = 0;
  temp = random(97,122); //dec a-z
  return temp;
}

//numbers
byte number() {
  int temp = 0;
  temp = random(48,57); //dec for 0-9
  return temp;
}

//wild cards
byte wild() {
  int temp = 0;
  int choice = random(0,4);
  switch(choice) {
    case 0:
      temp = 45; //-
      break;
    case 1:
      temp = 95; //_
      break;
    case 2:
      temp = 96; //'
      break;
    case 3:
      temp = 46; //.
      break;
  }
  return temp;
}
  
  
