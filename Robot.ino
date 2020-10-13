/*
  Robot class. UTEK-SD. 2021.  
*/
#include "Robot.h"

/*
 *  MOTOR
*/
class Motor {
    
  int pwm_output_a = DEFAULT_SPEED;
  int pwm_output_b = DEFAULT_SPEED;
  int motor1_a = -1;
  int motor1_b = -1;
  int motor2_a = -1;
  int motor2_b = -1;
  int en_a = -1;
  int en_b = -1;

public:

   Motor() {
     //ctor
  }

  ~Motor(){
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
  int init_motor_driver(int motor1_a, int motor1_b, int motor2_a, int motor2_b, int enA, int enB){

    this->motor1_a = motor1_a;
    this->motor1_b = motor1_b;
    this->motor2_a = motor2_a;
    this->motor2_b = motor2_b;
    this->en_a = enA;
    this->en_b = enB;

    //turn on the pins
    pinMode(motor1_a, OUTPUT);
    pinMode(motor1_b, OUTPUT);
    pinMode(motor2_a, OUTPUT);
    pinMode(motor2_b, OUTPUT);

    pinMode(en_a, OUTPUT);
    pinMode(en_b, OUTPUT);

    return 0;
    
  }

  /*
    @input: motor: motor_a = 0, motor_b = 1
    @output: motor speed, negative number upon failure
    Get the speed of a motors. 
  */
  int get_speed(int motor){

    if (motor == 1){
      return this->pwm_output_b;
    }
    else if (motor == 0){
      return this->pwm_output_a;
    }
    else return -1;
    
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
        this->update_speeds();
        return 0;
    }

    else return -1;
  }

  /*
    @input: speed: motor speed (0 - 255)
            motor: 0 ->  motor_a, 1 -> motor_b
    @output: 0 upon success, -1 upon failure
    Initialise the L298N motor driver.    
    Set the speed of a specific motor. If the enable pins are not connected then this function has no effect.
  */
  int set_speed(int speed, int motor){
    
    if (this->en_a != -1 && this->en_b != -1) {
        
        if (motor == 0){
          this->pwm_output_a = speed;      
          this->update_speeds();
          return 0;
        }        
        
        else if (motor == 1){
          this->pwm_output_b = speed;      
          this->update_speeds();
          return 0;
        }
               
    }

    else return -1;
  }

  /*
   * Set motor A's direction of rotation
    @inputt: 0 -> forward, 1 -> reverse    
  */
  int set_motor_a_direction(int dir){

    //forwards
    if (dir == 0){
      digitalWrite(this->motor1_a, LOW);
      digitalWrite(this->motor1_b, HIGH);
    }
    //backwards
    else if (dir == 1){
      digitalWrite(this->motor1_a, HIGH);
      digitalWrite(this->motor1_b, LOW);
    }
    
  }

  /*
   * Set motorb 's direction of rotation
    @inputt: 0 -> forward, 1 -> reverse    
  */
  int set_motor_b_direction(int dir){

    //forwards
    if (dir == 0){
      digitalWrite(this->motor2_a, LOW);
      digitalWrite(this->motor2_b, HIGH);
    }
    //backwards
    else if (dir == 1){
      digitalWrite(this->motor2_a, HIGH);
      digitalWrite(this->motor2_b, LOW);
    }
    
  }


  /*
    @output: 0 -> forward, 1 -> reverse, -1 on an unknown state
    Return the current direction of rotation for motorA
  */
  int get_motor_a_direction(){

    //forwards
    if (digitalRead(this->motor1_a) == 0 && digitalRead(this->motor1_b) == 1){
      return 0;
    }
    //backwards
    else if (digitalRead(this->motor1_a) == 1 && digitalRead(this->motor1_b) == 0){
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

    //forwards
    if (digitalRead(this->motor2_a) == 0 && digitalRead(this->motor2_b) == 1){
      return 0;
    }
    //backwards
    else if (digitalRead(this->motor2_a) == 1 && digitalRead(this->motor2_b) == 0){
      return 1;
    }
    else {
      return -1;
    }
    
  }

  /*
   * Start the motors by setting the motor1_a and motor2_a pins to logic level HIGH.
    @output: 0 upon successful test of internal variables, 1 otherwise
  */
  int start(){

    digitalWrite(this->motor1_a, HIGH);
    digitalWrite(this->motor2_a, HIGH);
    analogWrite(this->en_a, pwm_output_a);
    analogWrite(this->en_b, pwm_output_b);    
    return 0;
      
  }

  /*
    @output: 0 upon successful test of internal variables, 1 otherwise
  */
  int verify() {
    
    Serial.println(this->motor1_a);
    Serial.println(this->motor1_b);
    Serial.println(this->motor2_a);
    Serial.println(this->motor2_b);
    Serial.println(this->en_a);
    Serial.println(this->en_b);
    Serial.println(this->pwm_output_a);
    Serial.println(this->pwm_output_b);
    return 0;
    
  }

private:

    /* Synchronize motor speed settings
     * @output 0 upon success
     */
    int update_speeds(){

      analogWrite(this->en_a, this->pwm_output_a);
      analogWrite(this->en_b, this->pwm_output_b);
      
    }
  
};

/*
 *  ULTRASONIC SENSOR
*/


void Ultrasonic::start_sensor(int echo, int trig) {

  this->trig_pin = trig;
  this->echo_pin = echo;
  this->sonar = new NewPing(this->trig_pin,  this->echo_pin, MAX_DISTANCE);
  
}

int Ultrasonic::verify() {
      
    if (this->trig_pin > 0 || this->echo_pin > 0){
        return 0;
    }
    else {
        return -1;
    }      
  
}

int Ultrasonic::get_distance() {

  if (this->sonar == nullptr){    
    Serial.println("Sonar not initialised.");
    return -1;
  }

  return (this->sonar)->ping_cm();
    
}

void Ultrasonic::release() {

  delete this->sonar;
  this->sonar = nullptr;
    
}
