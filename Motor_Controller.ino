#include <Servo.h>


int motorPin = 14; // Name pin 14 as motorPin for motor pin identification
int potPin = A6;  // potPin represents pin connecting potentiometer
int previousValue = 93; //previous value starts at off
int currentValue = 0; //currentValue represents the current mapped value that the potentiometer reads(range 93-180)
int accelerateDelay = 100; //delay time for the motor to accelerate and deaccelerate


Servo myservo;

void setup() {
  Serial.begin(9600);
  myservo.attach(motorPin);
  pinMode(potPin, INPUT); //enable potPin to read analog values
}

void loop() {
  currentValue = analogRead(potPin); //read the current analog value
  currentValue = map(currentValue, 0, 1023, 93, 180); // map the value from 93-180
  
  /*checks to see if the is a difference greater than 5. 
  If there is accelarate the motor to currentValue*/
  if(currentValue - previousValue > 5){ 
    Serial.println("Enter if statement");
    Serial.println(currentValue);
    
    /*increases previousValue till it is equal to the currentValue.
    As you loop through update currentValue. 
    If currentValue is less than  or equal to previousValue, break out of this section*/
    for(previousValue; previousValue <= currentValue; previousValue++){ 
      currentValue = analogRead(potPin);      //update currentValue 
      currentValue = map(currentValue, 0, 1023, 93, 180); //map new currentValue from 93-180
      Serial.println(previousValue);
      myservo.write(previousValue); //write previousValue to the motor
      Serial.print("Current Value: ");
      Serial.println(currentValue);
      delay(accelerateDelay);  //delays the acceleration by accelerateDelay
      if(currentValue<=previousValue){  //check to see if you need to break
        break;
      }
    }
  }

  /*checks to see if the is a difference greater than 5. 
  If there is deaccelarate the motor to currentValue*/
  if(previousValue- currentValue> 5){  
    Serial.println("Enter if statement");
    Serial.println(currentValue);

    /*decreases previousValue till it is equal to the currentValue.
    As you loop through update currentValue. 
    If currentValue is greater than or eqaul to previousValue, break out of this section*/
    for(previousValue; previousValue >= currentValue; previousValue--){ 
      currentValue = analogRead(potPin); //update currentValue
      currentValue = map(currentValue, 0, 1023, 93, 180);  //map new currentValue from 93-180
      Serial.println(previousValue);
      myservo.write(previousValue);  //write previousValue to the motor
      Serial.print("Current Value: ");
      Serial.println(currentValue);
      delay(accelerateDelay);    //delays the acceleration by accelerateDelay
      if(currentValue>=previousValue){   //check to see if you need to break
        break;
      }
    }
  }

  /* if the currentValue is closer than 5 away from the previous, 
  write the currentValue to the servo*/
  else{
    myservo.write(currentValue);
  }
  
}
