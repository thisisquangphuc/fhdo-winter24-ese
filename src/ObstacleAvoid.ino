#define trigPin 4
#define echoPin 3
#define blueLED 5
#define yellowLED 6
#define redLED 7
#define IDLE 0
#define OBSTACLE_FOUND 1
#define WARNING_ZONE 2
// Distance thresholds
const float alertThreshold = 50.0;  // Alert threshold in cm
const float brakingThreshold = 15.0; // Braking threshold in cm
int DISTANCESTATE = IDLE;
void setup() {
  
  // put your setup code here, to run once:
  pinMode(blueLED, OUTPUT);
  pinMode(yellowLED, OUTPUT);
  pinMode(redLED, OUTPUT);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin,INPUT); 
  Serial.begin(9600);
}

void loop() {
  //====================ultrasonic sensor===================
  float distance;
  distance = getDistance();
  switch (DISTANCESTATE){
    case IDLE:
      setLEDState(HIGH, LOW, LOW);
      if(distance > brakingThreshold && distance <= alertThreshold){
        DISTANCESTATE = OBSTACLE_FOUND;
      }
      else if(distance <= brakingThreshold){
        DISTANCESTATE = WARNING_ZONE;
      }
      break;
    case OBSTACLE_FOUND:
      setLEDState(LOW, HIGH, LOW);
      Serial.print("Obstacle detected with distance: ");
      Serial.print(distance);
      Serial.println(" m");
      if(distance > alertThreshold){
        DISTANCESTATE = IDLE;
      }
      else if(distance <= brakingThreshold){
        DISTANCESTATE = WARNING_ZONE;
      }
      break;
    case WARNING_ZONE:
      setLEDState(LOW, LOW, HIGH);
      Serial.print("Obstacle close WARNING with distance: ");
      Serial.print(distance);
      Serial.println(" m");
      if(distance > alertThreshold){
        DISTANCESTATE = IDLE;
      }
      else if(distance > brakingThreshold && distance <= alertThreshold){
        DISTANCESTATE = OBSTACLE_FOUND;
      }
      break;
    default:
      setLEDState(LOW, LOW, LOW);
      DISTANCESTATE = IDLE;
      break;
  }
  delay(500);
}

//====================ultrasonic sensor===================
float getDistance(){
  /* two variables to store duraion and distance value */
  long duration;
  float distance;
  digitalWrite(trigPin, LOW); //set trigger signal low for 2us
  delayMicroseconds(2);
  
  /*send 10 microsecond pulse to trigger pin of HC-SR04 */
  digitalWrite(trigPin, HIGH);  // make trigger pin active high
  delayMicroseconds(10);            // wait for 10 microseconds
  digitalWrite(trigPin, LOW);   // make trigger pin active low
  
  /*Measure the Echo output signal duration or pulss width */
  duration = pulseIn(echoPin, HIGH); // save time duration value in "duration variable
  distance= duration*0.034/2; //Convert pulse duration into distance

  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" m");
  return distance;
}
// Function to set LED states
void setLEDState(int greenState, int yellowState, int redState) {
  digitalWrite(blueLED, greenState);
  digitalWrite(yellowLED, yellowState);
  digitalWrite(redLED, redState);
}

 
 