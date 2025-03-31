#define TRIG_PIN_R 2  
#define ECHO_PIN_R 3    // left and right sensor I/O pins
#define TRIG_PIN_L 4   
#define ECHO_PIN_L 5

#define SIDE_C 15.0 // known side of main triangle           
#define side_c 7.50 // known side of smaller triangle

float side_a = 0; 
float side_b = 0;     
float phi = 0;    // triangle variables
float theta = 0;
float radius = 0;

int distance = 0;     // these are the rounded, final values
int angle = 0;        // that will go to other subsystems

bool good_data = false; // target is in range or not
int water_level = 90;

#include <math.h>

#include <Servo.h>
Servo servoOne;   //Create Servo object to control Servo one
Servo servoTwo;   //Create Servo object to control Servo two

void setup() 
{
  Serial.begin(9600);

  pinMode(TRIG_PIN_L, OUTPUT);
  pinMode(ECHO_PIN_L, INPUT);       // set up I/O pin modes
  pinMode(TRIG_PIN_R, OUTPUT);
  pinMode(ECHO_PIN_R, INPUT);

  servoOne.attach(A0);
  servoTwo.attach(A1);

  servoOne.write(90);
  delay(500);
}

  //**************************
  //**************************
  //**************************

void loop() 
{
  // first, send an initial ping from both sensors
  // to see if target is in range

  digitalWrite(TRIG_PIN_L, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN_L, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN_L, LOW);

  side_b = pulseIn(ECHO_PIN_L, HIGH);
  side_b = (side_b / 58.00);

  delay(100);

  digitalWrite(TRIG_PIN_R, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN_R, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN_R, LOW);
  
  side_a = pulseIn(ECHO_PIN_R, HIGH);
  side_a = (side_a / 58.00);

  delay(100);

  if((side_b < 400) && (side_a < 400)) // target is in range
  {
    good_data = true;
  }

  else      // target is not in range
  {
    good_data = false;
  }


  //**************************
  //**************************
  //**************************


  if((good_data == true) && (water_level > 10)) // if data is good and we have enough water, track object
  {
    side_b = 0;   // reset side distances
    side_a = 0;
    float temp_side_b = 0;
    float temp_side_a = 0;
    float temp_phi = 0;      // these are temporary values used to sample and then average the data
    float temp_radius = 0;
    float temp_theta = 0;

    for (int i = 0; i < 5; i++) // take 5 readings then average them
    {
      digitalWrite(TRIG_PIN_L, LOW);
      delayMicroseconds(2);
      digitalWrite(TRIG_PIN_L, HIGH);
      delayMicroseconds(10);
      digitalWrite(TRIG_PIN_L, LOW);

      side_b = pulseIn(ECHO_PIN_L, HIGH);
      side_b = (side_b / 58.00);

      delay(100);

      digitalWrite(TRIG_PIN_R, LOW);
      delayMicroseconds(2);
      digitalWrite(TRIG_PIN_R, HIGH);
      delayMicroseconds(10);
      digitalWrite(TRIG_PIN_R, LOW);
      
      side_a = pulseIn(ECHO_PIN_R, HIGH);
      side_a = (side_a / 58.00);

      delay(100);

      temp_side_b = temp_side_b + side_b;
      temp_side_a = temp_side_a + side_a;
    }

    side_b = temp_side_b / 5;
    side_a = temp_side_a / 5;

    for(int i = 0; i < 5; i++)        // perform 5 calculations then average them
    {
      phi = acos(((sq(side_b)) + (sq(SIDE_C)) - (sq(side_a))) / (2*SIDE_C*side_b));

      radius = sqrt((sq(side_b)) + (sq(side_c)) - (2.00*side_b*side_c*cos(phi)));

      theta = acos((sq(side_a) + (sq(side_c)) - (sq(side_b))) / (2*side_a*side_c));

      theta = theta * (180/M_PI);    // convert angle to degrees

      temp_phi = temp_phi + phi;
      temp_radius = temp_radius + radius;
      temp_theta = temp_theta + theta;
    }

    phi = temp_phi / 5;
    radius = temp_radius / 5;
    theta = temp_theta / 5;

    distance = round(radius);   // round final values to integers
    angle = round(theta);

    delay(100);
  }

  //**************************
  //**************************
  //**************************

  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.print(" cm ");

  Serial.println("");

  Serial.print("Angle: ");
  Serial.print(angle);
  Serial.print(" degrees");

  Serial.println("");

  if(good_data == true)
    {
      if(angle >= 0 && angle < 10)
      {
        servoOne.write(175);
        delay(20);
      }
      else if(angle >= 10 && angle < 20)
      {
        servoOne.write(165);
        delay(20);
      }
      else if(angle >= 20 && angle < 30)
      {
        servoOne.write(155);
        delay(20);
      }
      else if(angle >= 30 && angle < 40)
      {
        servoOne.write(145);
        delay(20);
      }
      else if(angle >= 40 && angle < 50)
      {
        servoOne.write(135);
        delay(20);
      }
      else if(angle >= 50 && angle < 60)
      {
        servoOne.write(125);
        delay(20);
      }
      else if(angle >= 60 && angle < 70)
      {
        servoOne.write(115);
        delay(20);
      }
      else if(angle >= 70 && angle < 80)
      {
        servoOne.write(105);
        delay(20);
      }
      else if(angle >= 80 && angle < 90)
      {
        servoOne.write(95);
        delay(20);
      }
      else if(angle >= 90 && angle < 100)
      {
        servoOne.write(85);
        delay(20);
      }
      else if(angle >= 100 && angle < 110)
      {
        servoOne.write(75);
        delay(20);
      }
      else if(angle >= 110 && angle < 120)
      {
        servoOne.write(65);
        delay(20);
      }
      else if(angle >= 120 && angle < 130)
      {
        servoOne.write(55);
        delay(20);
      }
      else if(angle >= 130 && angle < 140)
      {
        servoOne.write(45);
        delay(20);
      }
      else if(angle >= 140 && angle < 150)
      {
        servoOne.write(35);
        delay(20);
      }
      else if(angle >= 150 && angle < 160)
      {
        servoOne.write(25);
        delay(20);
      }
      else if(angle >= 160 && angle < 170)
      {
        servoOne.write(15);
        delay(20);
      }
      else if(angle >= 170 && angle < 180)
      {
        servoOne.write(5);
        delay(20);
      }
    }
    else{}

  //**************************
  //**************************
  //**************************

  // Pump Dimensions
  // Base 5 x 5 cm
  // W: 5 cm
  // H: 6.5 cm
  // L: 7.8 - 8 cm


}
