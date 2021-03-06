Ultrasonic u;
Motor r;
Servo s;

struct Color {

  int red;
  int green;
  int blue;

};

#define DIAMETRE 0.125f
#define RADIUS DIAMETRE/2
#define WHEEL_RADIUS 0.065f
#define RPM 230.0f //as per the technical information on the website https://amzn.to/3mHQPCJ
#define RPS RPM/60

#define CONSTANT_A_SPEED 220
#define CONSTANT_B_SPEED 255

void rotation_test() {

  r.set_speed(0);
  r.set_speed(255, 0);
  delay(500);
  r.set_speed(0);
  r.set_speed(255, 1);
  delay(500);

}

void acceleration_test() {

  r.set_speed(0);
  r.start();
  int START = 150;

  for (int i = START; i < 260; i += 5) {

    r.set_speed(i, 0);
    Serial.println(i);
    delay(100);

  }


}

void direction_test() {

#define TEST_SPEED 128
  r.set_speed(0);

  r.set_motor_a_direction(0);
  r.set_speed(TEST_SPEED, 0);
  delay(1000);
  r.set_speed(0);
  delay(500);

  r.set_motor_a_direction(1);
  r.set_speed(TEST_SPEED, 0);
  delay(1000);
  r.set_speed(0);
  delay(500);

  r.set_motor_b_direction(0);
  r.set_speed(TEST_SPEED, 1);
  delay(1000);
  r.set_speed(0);
  delay(500);

  r.set_motor_b_direction(1);
  r.set_speed(TEST_SPEED, 1);
  delay(1000);
  r.set_speed(0);
  delay(500);

}

//Start the colour sensor.
Adafruit_TCS34725 tcs = Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_700MS, TCS34725_GAIN_1X);

void setup() {

  Serial.begin(9600);
  Serial.setTimeout(250);

  r.init_motor_driver(2, 3, 4, 5, 9, 10);
  r.set_speed(0, 1);
  r.set_speed(0, 0);
  r.start();
  u.start_sensor(13, 12);

  //    s.attach(6);

  //init colour sensor
  if (tcs.begin()) {
    Serial.println("Found sensor");
  } else {
    Serial.println("No TCS34725 found ... check your connections");
    while (1);
  }

  pinMode(7, INPUT);
  pinMode(8, INPUT);

}

void move_back() {

  r.set_motor_a_direction(1);
  r.set_motor_b_direction(1);
  r.set_speed(220, 0);
  r.set_speed(255, 1);

}

void turn_left() {

  float distance_to_turn = (PI * RADIUS) * 0.5f;
  float time_to_turn = distance_to_turn / (RPS *  WHEEL_RADIUS);

  int orig_a = r.get_motor_a_direction();
  int orig_b = r.get_motor_b_direction();

  int orig_a_speed = r.get_speed(0);
  int orig_b_speed = r.get_speed(1);

  r.set_motor_a_direction(0);
  r.set_motor_b_direction(1);
  r.set_speed(CONSTANT_A_SPEED, 0);
  r.set_speed(CONSTANT_B_SPEED, 1);
  delay(time_to_turn * 1000);
  Serial.println(time_to_turn);

  r.set_motor_a_direction(orig_a);
  r.set_motor_b_direction(orig_b);
  r.set_speed(orig_a_speed, 0);
  r.set_speed(orig_b_speed, 1);

}

void forward(int speed = -1) {
  if (speed == -1) {
    r.set_motor_a_direction(0);
    r.set_motor_b_direction(0);
    r.set_speed(CONSTANT_A_SPEED, 0)  ;
    r.set_speed(CONSTANT_B_SPEED, 1)  ;
  }
  else {

    r.set_motor_a_direction(0);
    r.set_motor_b_direction(0);
    r.set_speed(speed, 0)  ;
    r.set_speed(speed, 1)  ;
  }

}

void stop() {

  r.set_speed(0);

}

void backward(int speed = -1) {

  if (speed == -1) {
    r.set_motor_a_direction(1);
    r.set_motor_b_direction(1);
    r.set_speed(CONSTANT_A_SPEED, 0)  ;
    r.set_speed(CONSTANT_B_SPEED, 1)  ;
  }
  else {
    r.set_motor_a_direction(1);
    r.set_motor_b_direction(1);
    r.set_speed(speed, 0)  ;
    r.set_speed(speed, 1)  ;
  }

}


void left(int speed = -1) {

  if (speed == -1) {

    r.set_motor_a_direction(0);
    r.set_motor_b_direction(1);
    r.set_speed(CONSTANT_A_SPEED, 0);
    r.set_speed(CONSTANT_A_SPEED, 1);

  }

  else {

    r.set_motor_a_direction(0);
    r.set_motor_b_direction(1);
    r.set_speed(speed, 0); //left is 0
    r.set_speed(speed, 1); //right is 1

  }

}

void right(int speed = -1) {

  if (speed == -1) {

    r.set_motor_a_direction(1);
    r.set_motor_b_direction(0);
    r.set_speed(CONSTANT_A_SPEED, 0);
    r.set_speed(CONSTANT_B_SPEED, 1);

  }

  else {

    r.set_motor_a_direction(1);
    r.set_motor_b_direction(0);
    r.set_speed(speed, 0);
    r.set_speed(speed, 1);

  }

}

void test_colour() {

  //take reading with the lights off
  if (digitalRead(12) == LOW) {
    tcs.setInterrupt(true);  // turn off LED when true}
  }
  else {
    tcs.setInterrupt(false);  // turn off LED when true}
  }

  int r, g, b, c;
  tcs.getRawData((uint16_t*)&r, (uint16_t*)&g, (uint16_t*)&b, (uint16_t*)&c);
  convert_to_rgb(&r, &g, &b, &c);
  Serial.print("R:\t"); Serial.print(int(r));
  Serial.print("\tG:\t"); Serial.print(int(g));
  Serial.print("\tB:\t"); Serial.print(int(b));
  Serial.print("\n");

}

struct Color get_colour() {

  int r, g, b, c;
  tcs.getRawData((uint16_t*)&r, (uint16_t*)&g, (uint16_t*)&b, (uint16_t*)&c);
  convert_to_rgb(&r, &g, &b, &c);

  return {r, g, b};

}

int count = 1;

struct Color average_colour() {

  int redAvg = 0, greenAvg = 0, blueAvg = 0;

  for (int i = 0 ; i < count; i++) {
    struct Color col = get_colour();
    redAvg += col.red;
    greenAvg += col.green;
    blueAvg += col.blue;
  }

  return {redAvg / count, greenAvg / count, blueAvg / count};

}

int average_dist() {

  int x = 0;

  for (int i = 0 ; i < 5; i++) {
    x += u.get_distance();
  }

  return x / 5;

}

int  SrV = -1, SlV = -1, dist = -1;
int red = 87, g = 64, b = 117;


void controller() {

  SlV = digitalRead(7);
  SrV = digitalRead(8);
  dist = u.get_distance();
  Serial.println(dist);

  if (dist > 10) {

    if (SrV == LOW && SlV == LOW) {
      forward(225);
    }
    else if (SrV == HIGH && SlV == LOW)
    {
      right(255);
    }
    else if (SrV == LOW && SlV == HIGH)
    {
      left(255);
    }
    else if (SrV == HIGH && SlV == HIGH)
    {
      stop();
    }

    analogWrite(A0, 0);
    s.write(90);

  } else {

    stop();
    auto col = average_colour();
    
    //check whether the colour that has been detected is similar to the colour that needs to be sensed.
    //use Euclidean distance between the colour co-ordinates to detect similarity.
    //See https://github.com/systembolaget/Physical-computing-sensor-servo-tutorial-6a-Colour-finder-with-ams-TCS34725-and-HD-1900A for a tutorial.
    
    float magDiff = sqrt( (col.red - red) * (col.red - red) + (col.green - g) * (col.green - g) + (col.blue - b) * (col.blue - b) );
    Serial.println(magDiff);

    if (magDiff < 10) {
      analogWrite(A0, 128);
    }

  }

}

void loop() {

  controller();

}

void serialEvent() {



}
