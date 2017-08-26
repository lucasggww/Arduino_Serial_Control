/*
Terminal2Arduino
Start OS X terminal.app
Find serial device name: ls /dev/tty.*
Open terminal session: screen [serial device name] 9600 
Close session: ctrl-A ctrl-\ = shift-alt-7 on some keyboards
*/
///////////////////Control Part///////////////////////////
#define LED 13 

boolean active = false;
String content = "";
  
void parseCommand(String command){
  // Serial.println("Inside parse command");
  
  if (command.startsWith("init", 0)) {
    Serial.println("Initiate servos position.");
  }

  if (command.startsWith("show", 0)) {
    Serial.println("Show all joints.");
  }
  
  if (command.startsWith("reset", 0)) {
    Serial.println("Reset servos position to original.");
  }

  if (command.startsWith("move", 0)) {
    int str_len = command.length(); 
    char char_array[str_len];
    
    command.toCharArray(char_array, str_len);

    char move_com[5];
    char joint[6];
    int joint_number;
    char to[3];
    int degree;
    sscanf(char_array,"%s %s %d %s %d", move_com, joint, &joint_number, to, &degree);
    
    Serial.print(move_com);
    Serial.print(' ');
    Serial.print(joint);
    Serial.print(' ');
    Serial.print(joint_number);
    Serial.print(' ');
    Serial.print(to);
    Serial.print(' ');
    Serial.println(degree);
    
  }
  Serial.println(' ');
  Serial.print('>');
  return ;
}

// Read serial input
char c;
void readSerialInput() {
  while(Serial.available()) {
    c = Serial.read();
    content.concat(c);

    int c_int = c - '0';
   
    //Enter key
    if ( c =='\r' ) {
      Serial.println('\n');
      parseCommand(content);
      content = "";  
    }

    // backspace key
    if ( c_int  == 79) { 
      Serial.println(' ');
      Serial.print('>');
      int str_len = content.length();  
      content.remove(str_len-2, 2);
      Serial.print(content);
    }
    else if(content != "") {
      Serial.print(c);
    }
  }
  
  return;
}  


/////////////////////Servo Part//////////////////////////
#include <Servo.h>

int servoPin2 = 2;
int servoPin3 = 3;
int servoPin4 = 4;
int servoPin5 = 5;
int servoPin6 = 6;
int servoPin7 = 7;
 
Servo servo1, servo2, servo3, servo4, servo5, servo6;  
 
int servoAngle = 0;   // servo position in degrees
int tempangle = 0;
int iniangle = 0;
int num = 0;
int flag = 1;
int hip_ulimit = 30, hip_llimit = 70;
int knee_ulimit = 90,knee_llimit = 130;

void setup() {
  ///////////////Control part/////////////////////
  Serial.begin(9600); //open the serial port
  pinMode(LED, OUTPUT); 
  Serial.println("Type b to start and s to stop blinking of the Arduino LED");
  Serial.print(">"); //simulate prompt

  ///////////////Servo Part///////////////////////
  servo1.attach(servoPin2);//hip
  servo2.attach(servoPin3);//knee
  servo3.attach(servoPin4);
  servo4.attach(servoPin5);
  servo5.attach(servoPin6);
  servo6.attach(servoPin7);

  
}

void loop() {
  readSerialInput();
}
