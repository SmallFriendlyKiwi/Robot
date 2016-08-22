// Pin assignments
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
  int dcAPin;  // Direction Control A
  int dcBPin;  // Direction Control B
  int pwmPin;

  // Constructor
  public:
  Motor(int xdcAPin, int xdcBPin, int xpwmPin)
  {
    dcAPin = xdcAPin;
    dcBPin = xdcBPin;
    pwmPin = xpwmPin;
    
    pinMode(dcAPin, OUTPUT);
    pinMode(dcBPin, OUTPUT);
    pinMode(pwmPin, OUTPUT);
  }

  void ConfigForwards()
  {
    digitalWrite(dcAPin, HIGH);
    digitalWrite(dcBPin, LOW);
  }
  
  void ConfigBackwards()
  {
    digitalWrite(dcAPin, LOW);
    digitalWrite(dcBPin,HIGH);
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
