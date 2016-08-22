// PWM PCB to Arduino Uno pin assignments
const int in1 = 2;  // Motor 1 Direction Control
const int in2 = 3;  // Motor 1 Direction Control
const int enA = 5;  // Motor 1 Enable or PWM

const int in3 = 7;  // Motor 2 Direction Control
const int in4 = 4;  // Motor 2 Direction Control
const int enB = 6;  // Motor 2 Enable or PWM

// Other stuff
const int minSpeed = 48;      // Minimum motor speed
const int boostSpeed = 128;   // Boost speed to get the motor moving
const int boostTime = 50;     // Time in milliseconds for boostSpeed

class Motor
{
  // Member Variables
  int directionControlPin_01;  // Direction Control 01
  int directionControlPin_02;  // Direction Control 02
  int pwmPin;

  // Constructor
  public:
  Motor(int directionControlInput_01, int directionControlInput_02, int pwmInput)
  {
    directionControlPin_01 = directionControlInput_01;
    directionControlPin_02 = directionControlInput_02;
    pwmPin = pwmInput;
    
    pinMode(directionControlPin_01, OUTPUT);
    pinMode(directionControlPin_02, OUTPUT);
    pinMode(pwmPin, OUTPUT);
  }

  void ConfigForwards()
  {
    digitalWrite(directionControlPin_01, HIGH);
    digitalWrite(directionControlPin_02, LOW);
  }
  
  void ConfigBackwards()
  {
    digitalWrite(directionControlPin_01, LOW);
    digitalWrite(directionControlPin_02, HIGH);
  }
  
  void PowerUp(int pwmRatio)
  {
    // Give the motor a kick to get it going in case a low PWM ratio is passed in
    analogWrite(pwmPin, boostSpeed);
    delay(boostTime);
    // Now set the requested PWM
    analogWrite(pwmPin, pwmRatio);
  }
};

Motor LHMotor(in1, in2, enA);
Motor RHMotor(in3, in4, enB);

void setup()
  {
    while(true)
    {
      delay(500);
      RHMotor.ConfigForwards();
      LHMotor.ConfigForwards();
      RHMotor.PowerUp(minSpeed);
      LHMotor.PowerUp(minSpeed);
      delay(500);
      RHMotor.ConfigBackwards();
      LHMotor.ConfigBackwards();
      RHMotor.PowerUp(minSpeed);
      LHMotor.PowerUp(minSpeed);
    }
  }

void loop()
  {

  }
