// PWM PCB to Arduino Uno pin assignments
const int in1 = 2;  // Motor 1 Direction Control
const int in2 = 3;  // Motor 1 Direction Control
const int enA = 5;  // Motor 1 Enable or PWM

const int in3 = 7;  // Motor 2 Direction Control
const int in4 = 4;  // Motor 2 Direction Control
const int enB = 6;  // Motor 2 Enable or PWM

// Other stuff
const int min_speed = 48;      // Minimum motor speed
const int boost_speed = 128;   // Boost speed to get the motor moving
const int boost_time = 50;     // Time in milliseconds for boost_speed

class Motor
{
  public:
    Motor(int direction_control_pin_01,
          int direction_control_pin_02,
          int pwm_pin)
          : _direction_control_pin_01(direction_control_pin_01),
            _direction_control_pin_02(direction_control_pin_02),
            _pwm_pin(pwm_pin)
    { 
      pinMode(_direction_control_pin_01, OUTPUT);
      pinMode(_direction_control_pin_02, OUTPUT);
      pinMode(_pwm_pin, OUTPUT);
    }

  void ConfigForwards()
  {
    digitalWrite(_direction_control_pin_01, HIGH);
    digitalWrite(_direction_control_pin_02, LOW);
  }
  
  void ConfigBackwards()
  {
    digitalWrite(_direction_control_pin_01, LOW);
    digitalWrite(_direction_control_pin_02, HIGH);
  }
  
  void PowerUp(int pwm_ratio, int boost_speed, int boost_time)
  {
    // Give the motor a kick to get it going in case a low PWM ratio is passed in
    analogWrite(_pwm_pin, boost_speed);
    delay(boost_time);
    // Now set the requested PWM
    analogWrite(_pwm_pin, pwm_ratio);
  }
    
  private:
    int _direction_control_pin_01;
    int _direction_control_pin_02;
    int _pwm_pin;
};

void setup()
{
}

// Delare two motor instances
Motor LHMotor(in1, in2, enA);
Motor RHMotor(in3, in4, enB);

// The main code loop runs here
void loop()
{
  while(true)
  {
    delay(2000);
    RHMotor.ConfigForwards();
    LHMotor.ConfigBackwards();
    RHMotor.PowerUp(min_speed, boost_speed, boost_time);
    LHMotor.PowerUp(min_speed, boost_speed, boost_time);
    delay(2000);
    RHMotor.ConfigBackwards();
    LHMotor.ConfigForwards();
    RHMotor.PowerUp(min_speed, boost_speed, boost_time);
    LHMotor.PowerUp(min_speed, boost_speed, boost_time);
  }
}
