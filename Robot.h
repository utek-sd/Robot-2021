#include <Adafruit_TCS34725.h>
#include <NewPing.h>
#define DEFAULT_SPEED 255


class Ultrasonic {
     
    #define MAX_DISTANCE 200 // Maximum distance we want to ping for (in centimeters). Maximum sensor distance is rated at 400-500cm.
    #define TRIGGER_PIN  12  // Arduino pin tied to trigger pin on the ultrasonic sensor.
    #define ECHO_PIN     11  // Arduino pin tied to echo pin on the ultrasonic sensor.
    
private:
    
    int trig_pin = -1;
    int echo_pin = -1;
    //NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE); // NewPing setup of pins and maximum distance.    
    NewPing* sonar = nullptr;

public:
    /*
      Start the ultrasonic sensor. 
      Input: echo pin, trigger pin
    */
    void start_sensor(int echo = ECHO_PIN,int trigger = TRIGGER_PIN);

    /*
      Returns the distance in centimetres.
      Output: Distance in centimetres. -1 upon an error.
    */
    int get_distance();

    /*
     * Ensure the trigger and echo pins are not set to an invalid value.
     * Output: Returns 0 upon success. Otherwise a non-positive and a non-zero value.
    */
    int verify();

    /*
      Clean up resources used by this sensor.
    */
    void release();
    
};
