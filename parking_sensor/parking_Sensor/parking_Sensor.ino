
const int pingPin = 7; // Trigger Pin of Ultrasonic Sensor
const int echoPin = 6; // Echo Pin of Ultrasonic Sensor
const int buzzerPin = 5; // Select Pin of buzzer to operate
const int ledPin = 3;  // Interact with the LED

void setup() {
   Serial.begin(9600); // Starting Serial Terminal
   pinMode(buzzerPin,OUTPUT);
   pinMode(ledPin, OUTPUT);
}

void loop() {
   long duration = getDuration();
   long inches = microsecondsToInches(duration);
   long cm = microsecondsToCentimeters(duration);
   debug(inches, cm);
   
   if(cm < 50){
     beep(1000, 200);
     delay(cm * 20 - 20);
   }else
     delay(50);
}

long microsecondsToInches(long microseconds) {
   return microseconds / 74 / 2;
}

long microsecondsToCentimeters(long microseconds) {
   return microseconds / 29 / 2;
}

void debug(long inches, long cm){
   Serial.print(inches);
   Serial.print("in, ");
   Serial.print(cm);
   Serial.print("cm");
   Serial.println();
}

long getDuration(){
   pinMode(pingPin, OUTPUT);
   digitalWrite(pingPin, LOW);
   delayMicroseconds(2);
   digitalWrite(pingPin, HIGH);
   delayMicroseconds(10);
   digitalWrite(pingPin, LOW);
   pinMode(echoPin, INPUT);
   return (pulseIn(echoPin, HIGH));
}

void beep(int note, int duration)
{
   //Play tone on buzzerPin
   tone(buzzerPin, note);
   digitalWrite(ledPin, HIGH);
   delay(duration);
   digitalWrite(ledPin, LOW);
   noTone(buzzerPin);
}
