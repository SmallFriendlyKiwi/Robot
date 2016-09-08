#include <NewPing.h>
 
#define TRIGGER_PIN  12
#define ECHO_PIN     11
#define MAX_DISTANCE 200
 
NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE);

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

const int min_object_distance = 20;  // Minimum distance to an object that will
                                     // cause the robot to stop 

int get_distance(NewPing sonar)
  {
     int uS = sonar.ping();
     int distance = uS / US_ROUNDTRIP_CM;
     return distance;
  }

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
  
  void ConfigStopped()
  {
    digitalWrite(_direction_control_pin_01, LOW);
    digitalWrite(_direction_control_pin_02, LOW);
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
  Serial.begin(115200);
}

// Delare two motor instances
Motor LHMotor(in1, in2, enA);
Motor RHMotor(in3, in4, enB);

// The main code loop runs here
void loop()
{
  int object_distance;
  boolean motors_stopped;
  
  motors_stopped == false;
  
  while(true)
  {
    object_distance = get_distance(sonar);
    
    if(object_distance >= min_object_distance)
    {
      // Move ahead!!!
      Serial.println("The path ahead is clear for the robot to proceed...");
      if (motors_stopped == true)  // Only run the code below when transitioning from stopped to started
      {
        RHMotor.ConfigForwards();
        LHMotor.ConfigForwards();
        RHMotor.PowerUp(min_speed, boost_speed, boost_time);
        LHMotor.PowerUp(min_speed, boost_speed, boost_time);
        motors_stopped = false;
      }
    }
   else  // There's an object approaching
    {
      // Stop!!!
      Serial.println("STOP - There's an object approaching...");
      RHMotor.ConfigStopped();
      LHMotor.ConfigStopped();
      
      motors_stopped = true;
    } 
    
  }
}
