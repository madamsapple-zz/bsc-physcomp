#include <Servo.h>

//4 SERVO PINS
#define A2_pin A2
#define A3_pin A3
#define A4_pin A4
#define A5_pin A5

//servo objects
Servo servo_A2;
Servo servo_A3;
Servo servo_A4;
Servo servo_A5;

//variables for recording time elapsed after a servo moved to a certain angle
float time_atsweep;


//var for changing angles dynamically than hard coding
//I named two of them black and white since I had two servos with black and white arms initially and kept them as is
int black_angle = 170;
int white_angle = 1;
int A2_angle = 150;


/**A0 pin is an analog to digital pin; it reads the different voltage values (analog) generated when
  one/multiple switches are pressed in combination with parallel resistors.
  A0value is a variable which stores the corresponding analog-to-digital value of the pressed switch/es
**/
int A0value;

//In order to prevent angles changing at every instant of a button pressed and causing any disarray,
//angles will now change at every single "click" of the button
//two variables  ar made for tracking the analog values - if the differnce between the last recorded value and current value is more than the deesired threshold,
//only then will the servos trigger 
int prev_A0val;
const int threshold = 150;

//array storing frequency of square waves generated
int freq[] = {900, 380, 480, 580, 680, 780};




void setup() {
  //starts serial communication with the computer
  Serial.begin(9600);

  //servo code
  //attaches the servo library to the pin
  servo_A2.attach(A2_pin);
  servo_A3.attach(A3_pin);
  servo_A4.attach(A4_pin);
  servo_A5.attach(A5_pin);

  //right arm
  servo_A2.write(A2_angle);
  
  //left leg
  servo_A3.write(-1);

  //right leg
  servo_A4.write(-100);
  
  //left arm
  servo_A5.write(179);
}

void loop() {

  //stores the active analog value
  A0value = analogRead(A0);

  //will print the A0value to the serial monitor at every instance
  Serial.println(A0value);

  //if there is a significant diff between the last and currrent analog value, there has been a button click
  //only then the servo sweeps
  if (abs(A0value - prev_A0val) >= threshold) {

    //Serial.println("Button press");

    //these are A0values for the first button
    if ((A0value >= 505) && (A0value <= 540)) {

      //tone func sends frequency val to digital pin 8 (same as piezo buzzer output)
      tone(8, freq[1]);

      servo_A2.write(A2_angle);
      servo_A3.write(white_angle);

      servo_A4.write(white_angle);
      servo_A5.write(white_angle);

      black_angle -= 42;
      A2_angle -= 30;
      white_angle += 30;

      time_atsweep = millis();

      Serial.println("Button press 1");

    }

    //second button press
    else if ((A0value >= 370) && (A0value <= 450)) {

      tone(8, freq[2]);

      servo_A2.write(black_angle);
      servo_A3.write(white_angle);
      servo_A4.write(white_angle);
      servo_A5.write(white_angle);

      white_angle += 30;
      A2_angle -= 30;
      black_angle -= 42;

      time_atsweep = millis();

      Serial.println("Button press 2");

    }

    //third
    else if ((A0value >= 900) && (A0value <= 1001)) {

      tone(8, freq[3]);

      servo_A2.write(black_angle);
      servo_A3.write(white_angle);
      servo_A4.write(white_angle);
      servo_A5.write(white_angle);

      white_angle += 30;
      A2_angle -= 30;
      black_angle -= 42;

      time_atsweep = millis();

      Serial.println("Button press 3");

    }

    //fourth
    else if ((A0value >= 1020) && (A0value <= 1023)) {

      tone(8, freq[4]);

      servo_A2.write(black_angle);
      servo_A3.write(white_angle);
      servo_A4.write(white_angle);
      servo_A5.write(white_angle);

      white_angle += 30;
      A2_angle -= 30;
      black_angle -= 42;

      time_atsweep = millis();

      Serial.println("Button press 4");

    }
    else if ((A0value >= 600) && (A0value <= 700)) {

      tone(8, freq[0]);

      servo_A2.write(black_angle);
      servo_A3.write(white_angle);
      servo_A4.write(white_angle);
      servo_A5.write(white_angle);

      white_angle += 30;
      A2_angle -= 30;
      black_angle -= 42;

      time_atsweep = millis();

      Serial.println("first 2 Buttons");

    }
    
    else {
      //if any button is not being actively clicked, do not play any sound
      noTone(8);

    }

  }

  //resetting the angle once it has reached its limit
  if (servo_A4.read() <= 0 || servo_A2.read() <= 0 ) {
    //3 seconds have passed since the last click
    if ( (millis() - time_atsweep) == 3) {
      black_angle = 170;
    }
  }

  if (servo_A3.read() >= 180 || servo_A5.read() >= 180 ) {
    if ( (millis() - time_atsweep) == 3) {
      white_angle = 1;
    }
  }

  prev_A0val = A0value;
}
