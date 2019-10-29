#include <RTCZero.h>
#include <ArduinoLowPower.h>
#include <SigFox.h>

#include <DHT.h>
#include <DHT_U.h>

#define DHTPIN 5     
#define DHTTYPE DHT11   
DHT dht(DHTPIN, DHTTYPE);

//CONSTANTS
#define MQ2SENSOR A0 //analog pins when implementing
#define MQ7SENSOR A1
#define LED_RED 6
#define LED_GREEN 7
#define LED_BLUE 8

//VARIABLES
int count = 1;  //Counts the number of readings taken

void setup() {
  Serial.begin(115200); // Starts the serial communication
  dht.begin();
  Serial.println("UN MAKERTHON AIR PROJECT:");
  Serial.println(" ");
  pinMode(LED_RED,OUTPUT);
  pinMode(LED_GREEN,OUTPUT);
  pinMode(LED_BLUE,OUTPUT);

  if (!SigFox.begin()){
    reboot();
  }
  
  SigFox.end();
  
  delay(1000); // 60s(1 min) for stabilization, of the SDS011, 3mins for the MQ sensors
}

void loop() {
  SigFox.begin();
  read();
  String_to_be_sent =  
  delay(2050);  //sampling time for the unit...VARY THIS
}

void read(){  
  Serial.print("Count: ");
  Serial.println(count++);  //comment this during simulation
 
  //MQ GAS SENSORS
  int mq2Value = analogRead(MQ2SENSOR);
  int mq7Value = analogRead(MQ7SENSOR);

  //DHT11 SENSOR
  float h = dht.readHumidity();
  float t = dht.readTemperature(); // Read temperature in Celsius (default)
    // Check if any reads from the DHT11 failed and exit early (to try again).
  if (isnan(h) || isnan(t)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }

  //OUTPUT:
  Serial.print("Smoke and LPG: ");
  Serial.print(mq2Value);
  Serial.println("ppm");
  Serial.print("CO concentration: ");
  Serial.print(mq7Value);
  Serial.println("ppm");
  Serial.print("Humidity: ");
  Serial.print(h);
  Serial.println("%");
  Serial.print("Temperature: ");
  Serial.print(t);
  Serial.println("*C");
  Serial.println(" ");

 
  //Conditional statements
//  if (limits)
  {
  RGB_color(255, 0, 0); // Red
  delay(1000);
  }

//  if(limits)
  {
  RGB_color(0, 255, 0); // Green
  delay(1000);
  }
  
//  if(limits)
  {
  RGB_color(0, 0, 255); // Blue
  delay(1000);
  }

//  if(limits)
  {
  RGB_color(255, 255, 125); // Raspberry
  delay(1000);
  }

//  if(limits)
  {
  RGB_color(0, 255, 255); // Cyan
  delay(1000);
  }

//  if(limits)
  {
  RGB_color(255, 0, 255); // Magenta
  delay(1000);
  }

//  if(limits)
  {
  RGB_color(255, 255, 0); // Yellow
  delay(1000);
  }

//  if(limits)
  {
  RGB_color(255, 255, 255); // White
  delay(1000);
  }
  
}

void RGB_color(int redValue, int greenValue, int blueValue)
 {
  analogWrite(LED_RED, redValue);
  analogWrite(LED_GREEN, greenValue);
  analogWrite(LED_BLUE, blueValue);
}
