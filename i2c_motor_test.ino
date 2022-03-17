#include <Wire.h>

#define SLAVE_ADDRESS 0x08
//data from RPI
//data_to_echo[0] is the direction and data_to_echo[1] is the speed
int data_to_echo[2];

int motor1pin1 = 2;
int motor1pin2 = 3;

int motor2pin1 = 4;
int motor2pin2 = 5;

void setup() {
  // put your setup code here, to run once:
  pinMode(motor1pin1, OUTPUT);
  pinMode(motor1pin2, OUTPUT);
  pinMode(motor2pin1, OUTPUT);
  pinMode(motor2pin2, OUTPUT);

  pinMode(10, OUTPUT); 
  pinMode(11, OUTPUT);
  
  Wire.begin(SLAVE_ADDRESS);

  Wire.onReceive(receiveData);
  Wire.onRequest(sendData);

  Serial.begin(9800);
}

void loop() {
  // put your main code here, to run repeatedly:   

  //Controlling speed (0 = off and 255 = max speed):
  if(data_to_echo[0] == 1){
        analogWrite(10, data_to_echo[1]); //ENA pin
        analogWrite(11, data_to_echo[1]); 
        digitalWrite(motor1pin1, HIGH);
        digitalWrite(motor1pin2, LOW);

        digitalWrite(motor2pin1, LOW);
        digitalWrite(motor2pin2, HIGH);
  }else if(data_to_echo[0] == 2){
        analogWrite(10, data_to_echo[1]); //ENA pin
        analogWrite(11, data_to_echo[1]); 
        digitalWrite(motor1pin1, LOW);
        digitalWrite(motor1pin2, HIGH);

        digitalWrite(motor2pin1, HIGH);
        digitalWrite(motor2pin2, LOW);
  }else if(data_to_echo[0] == 0){
        analogWrite(10, 0); //ENA pin
        analogWrite(11, 0); //ENB pin
  }
  //Controlling spin direction of motors:
  //digitalWrite(motor1pin1, HIGH);
  //digitalWrite(motor1pin2, LOW);

  //digitalWrite(motor2pin1, HIGH);
  //digitalWrite(motor2pin2, LOW);
//  delay(10000);

//  digitalWrite(motor1pin1, LOW);
//  digitalWrite(motor1pin2, HIGH);
//
//  //digitalWrite(motor2pin1, LOW);
//  //digitalWrite(motor2pin2, HIGH);
//  delay(1000);
}
//Data received from the RPI
void receiveData(int bytecount)
{
  //for (int i = 0; i < bytecount; i++) {
    for(int i = 0; i<2;i++){
    data_to_echo[i] = Wire.read();
    Serial.println(data_to_echo[i]);
  }
}
//Sending data to the RPI
void sendData()
{
  for(int i = 0; i<2; i++){
  Wire.write(data_to_echo[i]);
  }
}
