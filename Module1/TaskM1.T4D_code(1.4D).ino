//constant values
const uint8_t LED = 4;
const int triggerPIN = 6;
const int echoPIN = 7;
const uint8_t button = 2;

const uint8_t LED2 = 13;
const int PIRsignal = 3;

const uint8_t LED3 = 12;
const int PIRsignal2 = 5;

const uint8_t LED4 = 11; //(TIMER)

//declare global variables and assign values 
uint8_t ledState = LOW;
bool pressed = false;
bool timer_LEDstate = true;
volatile byte PIR = LOW;
volatile byte PIR2 = LOW;

void setup()
{
    //setup PINs for all components
    pinMode(LED, OUTPUT); //LED
    pinMode(triggerPIN, OUTPUT); //triggerPIN
    pinMode(echoPIN, INPUT); //echoPIN
    pinMode(button, INPUT_PULLUP); //button
  
    pinMode(LED2, OUTPUT); //LED2
    pinMode(PIRsignal, INPUT); //PIRSignal PIN 	
  
    pinMode(LED3, OUTPUT); //LED3
    //pinMode(PIRsignal2, INPUT); //PIRSignal PIN2
  
    //pinMode(LED4, OUTPUT); //LED4(INTERNAL_TIMER)
  	//reseting internal timer and set it to blink every 1000ms (1s)
  	TCCR1A = 0;
  	TCCR1B = 0;
  	TCCR1B |= (1 << CS12);    //using 256 prescaler 
 	TIMSK1 |= (1 << OCIE1A); //enable timer compare interrupt
  	OCR1A = 62500; 
   
  	//enabling PCINT 
  	PCICR |= B00000100;
  	PCMSK2 |= B00100000;
  
    Serial.begin(9600);
  
    //implement external interrupts     
    attachInterrupt(digitalPinToInterrupt(button), off_led, RISING);
    attachInterrupt(digitalPinToInterrupt(PIRsignal), PIR_triggered, RISING);
    // Serial Communication is starting with 9600 of baudrate speed
    Serial.println("Ultrasonic Sensor HC-SR04 Data & Motion Detector");
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
  
    digitalWrite(LED2, PIR);  
    digitalWrite(LED3, PIR2);  
  
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
    Serial.println(" cm\n");
}

//off led function
void off_led() {
    pressed = !pressed;
    ledState = !ledState;
    digitalWrite(LED, ledState);
}

void PIR_triggered(){
  if (PIR == HIGH){
    PIR = !PIR;
    Serial.println("Motion Detected. Setting Light 1 is OFF\n");
  }
  else 
  {
    PIR = !PIR;
    Serial.println("Motion Detected. Setting Light 1 is ON\n");
  }
}

void PIR_triggered2(){
  if (PIR2 == HIGH){
    PIR2 = !PIR2;
    Serial.println("Motion Detected. Setting Light 2 is OFF\n");
  }
  else 
  {
    PIR2 = !PIR2;
    Serial.println("Motion Detected. Setting Light 2 is ON\n");
  }
}
  
ISR (PCINT2_vect){
  PIR_triggered2();
}

ISR (TIMER1_COMPA_vect){
	TCNT1 = 0;
  	timer_LEDstate = !timer_LEDstate;
  	digitalWrite(LED4, timer_LEDstate);
}
