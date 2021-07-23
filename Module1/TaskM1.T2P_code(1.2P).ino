//constant values
const uint8_t LED = 4;
const int triggerPIN = 6;
const int echoPIN = 7;
const uint8_t button = 2;


//declare global variables and assign values 
uint8_t ledState = LOW;
bool pressed = false;

void setup()
{
    //setup PINs for all components
    pinMode(LED, OUTPUT); //LED
    pinMode(triggerPIN, OUTPUT); //triggerPIN
    pinMode(echoPIN, INPUT); //echoPIN
    pinMode(button, INPUT_PULLUP); //button
    Serial.begin(9600);
    //implement external interrupts     
    attachInterrupt(digitalPinToInterrupt(button), off_led, RISING);
    // Serial Communication is starting with 9600 of baudrate speed
    Serial.println("Ultrasonic Sensor HC-SR04 Data");
    // print some text in Serial Monitor

}

void loop()
{
    // Declare local variables
    long distance;
    long duration;
    // Clears the trigPin condition
    digitalWrite(triggerPIN, LOW);

    // Sets the trigPin (ACTIVE)
    digitalWrite(triggerPIN, HIGH);
    digitalWrite(triggerPIN, LOW);

    // Reads the echoPin, returns the value
    duration = pulseIn(echoPIN, HIGH);
    
    //Calculate 
    distance = get_distance(duration);
    // Print Distance
    print_distance(distance);
    //delay for 500ms
    delay(500);

    //if distance is smaller than 100, LED will turn on
    //else distance is bigger than 100, LED will turn off
    //using Ternary Operator
    ledState = distance <= 100 ? HIGH : LOW;
    
    //check whether the button is pressed or not 
    //if yes, led will turn off when the object is within range 
    if (!pressed) 
    {
        digitalWrite(LED, ledState);
    }
  
  	if (pressed == true)
  	{
   	 Serial.println("WARNING:Button has been pressed.");
     Serial.println("LED OFF. Remember to switch it on.\n");
  	}
}

//calcualte distance 
long get_distance(long duration) {
    // Calculating the distance
    return duration * 0.017;
}

//print distance function
void print_distance(long distance) {
    // Displays the distance on the Serial Monitor
    Serial.print("Distance: ");
    Serial.print(distance);
    Serial.println(" cm");
}

//off led function
void off_led() {
    pressed = !pressed;
    ledState = !ledState;
    digitalWrite(LED, ledState);
}
