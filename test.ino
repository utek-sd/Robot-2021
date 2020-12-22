Ultrasonic u;
Motor r;

#define DIAMETRE 0.125f
#define RADIUS DIAMETRE/2
#define WHEEL_RADIUS 0.065f
#define RPM 230.0f //as per the technical information on the website https://amzn.to/3mHQPCJ
#define RPS RPM/60 

#define CONSTANT_A_SPEED 220
#define CONSTANT_B_SPEED 255

void rotation_test(){

  r.set_speed(0);
  r.set_speed(255, 0);
  delay(500);
  r.set_speed(0);
  r.set_speed(255, 1);
  delay(500);

}

void acceleration_test(){

  r.set_speed(0);
  int START = 150;

  for (int i = START; i < 255; i+= 255/10){

    r.set_speed(i,0);
    Serial.println(i);
    delay(25);

  }

  r.set_speed(0);
  delay(500);

  for (int i =START ; i < 255; i+= 255/10){

    r.set_speed(i,1);
    Serial.println(i);
    delay(25);

  }


}

void direction_test(){

    #define TEST_SPEED 128
    r.set_speed(0);    

    r.set_motor_a_direction(0);
    r.set_speed(TEST_SPEED,0);        
    delay(1000);
    r.set_speed(0);
    delay(500);
    
    r.set_motor_a_direction(1);
    r.set_speed(TEST_SPEED,0);        
    delay(1000);
    r.set_speed(0);
    delay(500);
        
    r.set_motor_b_direction(0);
    r.set_speed(TEST_SPEED,1);        
    delay(1000);
    r.set_speed(0);
    delay(500);
    
    r.set_motor_b_direction(1);    
    r.set_speed(TEST_SPEED,1);    
    delay(1000);
    r.set_speed(0);    
    delay(500);

}

void setup() {

  Serial.begin(9600);
  Serial.setTimeout(250);
  r.init_motor_driver(2, 3, 4, 5, 9, 10);        
  r.set_speed(0,1);
  r.set_speed(0,0);
  r.start();    
  r.verify(); 

  u.start_sensor(13,12);
  u.verify();

}

void move_back(){

  r.set_motor_a_direction(1);
  r.set_motor_b_direction(1);
  r.set_speed(220, 0);
  r.set_speed(255, 1);
  
}

void turn_left(){

  float distance_to_turn = (PI*RADIUS)*0.5f;  
  float time_to_turn = distance_to_turn / (RPS *  WHEEL_RADIUS);  

  int orig_a = r.get_motor_a_direction();
  int orig_b = r.get_motor_b_direction();
  
  int orig_a_speed = r.get_speed(0);
  int orig_b_speed = r.get_speed(1);
  
  r.set_motor_a_direction(0);
  r.set_motor_b_direction(1);
  r.set_speed(CONSTANT_A_SPEED, 0);
  r.set_speed(CONSTANT_B_SPEED, 1);
  delay(time_to_turn*1000); 
  Serial.println(time_to_turn);

  r.set_motor_a_direction(orig_a);
  r.set_motor_b_direction(orig_b);
  r.set_speed(orig_a_speed, 0);
  r.set_speed(orig_b_speed, 1);
  
}

void stop(){

  r.set_speed(0);
  
}

void loop() {

//  int distance = u.get_distance();
//  
//  if (distance < 5){
//
//    Serial.println(distance);
//    move_back();
//    
//  }
//
//  else {
//
//    stop();
//    
//  }

  turn_left();
  delay(4000);

}

void serialEvent() {
    
  int p = Serial.parseInt();
  r.set_speed(p, 0);

}
