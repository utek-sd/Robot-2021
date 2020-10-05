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
    delay(2500);
    
  }

  r.set_speed(0);

  for (int i =START ; i < 255; i+= 255/10){

    r.set_speed(i,1);
    Serial.println(i);
    delay(2500);
    
  }

  
}

void direction_test(){

    r.set_speed(0);
    r.set_speed(255,0);
    
    r.set_motor_a_direction(0);
    delay(1000);
    r.set_motor_a_direction(1);
    delay(1000);

    r.set_speed(0);
    r.set_speed(255,1);

    r.set_motor_b_direction(0);
    delay(1000);
    r.set_motor_b_direction(1);
    delay(1000);
    
}
