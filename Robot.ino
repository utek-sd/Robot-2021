/*
  Robot class. UTEK-SD. 2021.  
*/

#include <Adafruit_TCS34725.h>

#define DEFAULT_SPEED 255

class Robot {

  int pwm_output_a = DEFAULT_SPEED;
  int pwm_output_b = DEFAULT_SPEED;
  int motor1_a = -1;
  int motor1_b = -1;
  int motor2_a = -1;
  int motor2_b = -1;
  int en_a = -1;
  int en_b = -1;

  Robot() {
     //ctor
  }

  ~Robot(){
    //dtor  
  }
  
  /*
    @input: motor1_a/b and motor2_a/b: inputs for the motor direction controls
    @output: 0 upon success, -1 otherwise    
    Initialise the L298N motor driver.
    Assuming that the both enable pins have been connected with a 2 pin header.    
  */
  int init_motor_driver(int motor1_a, int motor1_b, int motor2_a, int motor_2b ){

    this->motor1_a = motor1_a;
    this->motor1_b = motor1_b;
    this->motor2_a = motor2_a;
    this->motor2_b = motor2_b;

    pinMode(motor1_a, OUTPUT);
    pinMode(motor1_b, OUTPUT);
    pinMode(motor2_a, OUTPUT);
    pinMode(motor_2b, OUTPUT);

    return 0;
    
  }

  /*
    @input: motor1_a/b and motor2_a/b: inputs for the motor direction controls
            enA: The enable signal A
            enB: The enable signal B
    @output: 0 upon success, -1 otherwise    
    Initialise the L298N motor driver.    
    This method allows for using the enable pins on the robot so that motor speed can be controlled.    
  */
  int init_motor_driver(int motor1_a, int motor1_b, int motor2_a, int motor_2b, int enA, int enB){

    this->motor1_a = motor1_a;
    this->motor1_b = motor1_b;
    this->motor2_a = motor2_a;
    this->motor2_b = motor2_b;
    this->en_a = en_a;
    this->en_b = en_b;

    //turn on the pins
    pinMode(motor1_a, OUTPUT);
    pinMode(motor1_b, OUTPUT);
    pinMode(motor2_a, OUTPUT);
    pinMode(motor_2b, OUTPUT);

    pinMode(en_a, OUTPUT);
    pinMode(en_b, OUTPUT);

    return 0;
    
  }

  /*
    @input: speed: motor speed (0 - 255)
    @output: 0 upon success, -1 otherwise    
    Set the speed of both motors. If the enable pins are not connected then this function has no effect.
  */
  int set_speed(int speed){
    
    if (this->en_a != -1 && this->en_b != -1) {
        this->pwm_output_a = speed;      
        this->pwm_output_b = speed;
        return 0;
    }

    else return -1;
  }

  /*
    @input: speed: motor speed (0 - 255)
            motor: 1 -> right motor, 0 -> left motor
    @output: 0 upon success, -1 upon failure
    Initialise the L298N motor driver.    
    Set the speed of a specific motor. If the enable pins are not connected then this function has no effect.
  */
  int set_speed(int speed, int motor){
    
    if (this->en_a != -1 && this->en_b != -1) {
        
        if (motor == 0){
          this->pwm_output_a = speed;      
          return 0;
        }        
        
        else if (motor == 1){
          this->pwm_output_b = speed;      
          return 0;
        }
               
    }

    else return -1;
  }

  /*
    @output: 0 -> forward, 1 -> reverse, -1 on an unknown state
    Return the current direction of rotation for motorA
  */
  int get_motor_a_direction(){

    if (this->motor1_a == 0 && this->motor1_b == 1){
      return 0;
    }
    else if (this->motor1_a == 1 && this->motor1_b == 0){
      return 1;
    }
    else {
      return -1;
    }
    
  }

  /*
    @output: 0 -> forward, 1 -> reverse, -1 on an unknown state
    Return the current direction of rotation for motorA
  */
  int get_motor_b_direction(){

    if (this->motor1_a == 0 && this->motor1_b == 1){
      return 0;
    }
    else if (this->motor1_a == 1 && this->motor1_b == 0){
      return 1;
    }
    else {
      return -1;
    }
    
  }

  /*
    @output: 0 upon successful test of internal variables, 1 otherwise
  */
  int verify() {
    
  }
  
};

void setup(){}
void loop(){}
