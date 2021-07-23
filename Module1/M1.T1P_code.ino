//constant value
#define LED 4
#define triggerPIN 6
#define echoPIN 7

//declare value type 
long duration;
int distance;

void setup()
{
  pinMode(LED, OUTPUT); //LED
  pinMode(triggerPIN, OUTPUT); //triggerPIN
  pinMode(echoPIN, INPUT); //echoPIN
  Serial.begin(9600);
  // Serial Communication is starting with 9600 of baudrate speed
  Serial.println("Ultrasonic Sensor HC-SR04 Data"); 
  // print some text in Serial Monitor
  
}

void loop()
{
  // Clears the trigPin condition
  digitalWrite(triggerPIN, LOW);
  delay(500);
  // Sets the trigPin (ACTIVE) for 1 second
  digitalWrite(triggerPIN, HIGH);
  delay(500);
  digitalWrite(triggerPIN, LOW);
  // Reads the echoPin, returns the value
  duration = pulseIn(echoPIN, HIGH);
  // Calculating the distance
  distance = duration * 0.034 / 2; 
  // Speed of sound wave divided by 2
  // Displays the distance on the Serial Monitor
  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");
  
  //if distance is smaller than 100, LED will turn on
  if (distance <= 100)
  {
    digitalWrite(LED, HIGH);
  } 
  //else distance is longer than 100, LED will turn off
  else 
  {
    digitalWrite(LED, LOW);
  }
}
