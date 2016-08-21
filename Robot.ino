const int in1 = 2;
const int in2 = 3;
const int enA = 5;

const int in3 = 7;
const int in4 = 4;
const int enB = 6;

const int minSpeed = 48;
const int boostSpeed = 128;
const int boostTime = 50;

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
