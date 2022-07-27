/* Sketch for LCD display and sonic sensor with the DHT11 sensor
 *  the menue is also included. 
 *  please note that the pins are not exactly arranged in an orderly manner.
 *  you can change the pins in the configuration of the arduino to fit your desired presentation but remember to change them in the code also. 
*/


#include <LiquidCrystal.h>

const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

#include <DHT.h>



#define DHTPIN 6

#define DHTTYPE DHT11

DHT dht(DHTPIN, DHTTYPE);


int upButton = 10;
int downButton = 13;
int selectButton = 9;
int menu = 1;

long duration;
long duration1;
long duration2;
double distance;
double distance1;
double distance2;
double motion;
double obspeed;



const int trigPin = 8;
const int echoPin = 7;

void setup() {
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(upButton, INPUT_PULLUP);
  pinMode(downButton, INPUT_PULLUP);
  pinMode(selectButton, INPUT_PULLUP);
  updateMenu();
  dht.begin();

  Serial.begin(9600);
}

void loop() {
  if (!digitalRead(downButton)){
    menu++;
    updateMenu();
    delay(100);
    while (!digitalRead(downButton));
  }
  if (!digitalRead(upButton)){
    menu--;
    updateMenu();
    delay(100);
    while(!digitalRead(upButton));
  }
  if (!digitalRead(selectButton)){
    executeAction();
    updateMenu();
    delay(100);
    while (!digitalRead(selectButton));
  }
}

void updateMenu() {
  switch (menu) {
    case 0:
      menu = 1;
      break;
    case 1:
      lcd.clear();
      lcd.begin(16, 2);
      lcd.print(">Distance");
      lcd.setCursor(0, 1);
      lcd.print(" Temperature");
      break;
    case 2:
      lcd.clear();
      lcd.begin(16, 2);
      lcd.print(" Distance");
      lcd.setCursor(0, 1);
      lcd.print(">Temperature");
      break;
    case 3:
      lcd.clear();
      lcd.begin(16, 2);
      lcd.print(" Temperature");
      lcd.setCursor(0, 1);
      lcd.print(">Humidity");
      break;
    case 4:
      lcd.clear();
      lcd.begin(16, 2);
      lcd.print(" Humidity");
      lcd.setCursor(0, 1);
      lcd.print(">Object Speed");
      break;

    case 5:
      lcd.clear();
      lcd.begin(16, 2);
      lcd.print(" Object Speed");
      lcd.setCursor(0, 1);
      lcd.print(">Stored Values");
      break;

    case 6:
      lcd.clear();
      lcd.begin(16, 2);
      lcd.print(" Stored Values");
      lcd.setCursor(0, 1);
      lcd.print(">Resert Device");
      break;
    case 7:
      menu = 1;
      break;
  }
}

void executeAction() {
  switch (menu) {
    case 1:
      action1();
      break;
    case 2:
      action2();
      break;
    case 3:
      action3();
      break;
    case 4:
      action4();
      break;

    case 5:
      action5();
      break;

    case 6:
      action6();
      break;      
  }
}

void action1() {
  lcd.clear();
  lcd.begin(16, 2);
  lcd.print("Beta Call Miles");
  lcd.setCursor(0, 1);
  lcd.print("0789296068");
  delay(2500);
  //int count = millis();

  
  lcd.clear();
  lcd.begin(16, 2);
  lcd.print("Beta Call Miles");
  
  for(int i = 0; i < 5000; i++)
  {
    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);

    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);

    duration = pulseIn(echoPin, HIGH);
    distance = duration*0.034/2;

    lcd.setCursor(0, 1);
    lcd.print("Distance: ");

    lcd.print(distance);
   if (!digitalRead(selectButton)){
      break;
      delay(100);
    while (!digitalRead(selectButton));
  }
  }
  
  delay(2500);
}
void action2() {
  lcd.clear();

  lcd.begin(16, 2);
  lcd.print("Beta Call Miles");
  lcd.setCursor(0, 1);
  lcd.print("0789296068");
  delay(2500);
  //int count = millis();
  
  for(int i = 0; i < 5000; i++)
  {
  float humidity = dht.readHumidity();

  float temp = dht.readTemperature();

  if (isnan(humidity) || isnan(temp))
  {
    lcd.print("Failed to read from DHT Sensor");
    return;
  }

  lcd.setCursor(0, 1);
  lcd.print("Temperature:");
  lcd.print(temp, 1);
  lcd.print("C");
   if (!digitalRead(selectButton)){
      break;
      delay(100);
    while (!digitalRead(selectButton));
  }
  }

  delay(2500);
}
void action3() {
  lcd.clear();

  lcd.begin(16, 2);
  lcd.print("Beta Call Miles");
  lcd.setCursor(0, 1);
  lcd.print("0789296068");
  delay(2500);
  //int count = millis();
  lcd.clear();
  lcd.begin(16, 2);
  lcd.print("Beta Call Miles");
  for(int i = 0; i < 5000; i++)
  {

  float humidity = dht.readHumidity();

  float temp = dht.readTemperature();

  if (isnan(humidity) || isnan(temp))
  {
    lcd.print("Failed to read from DHT Sensor");
    return;
  }

  lcd.setCursor(0, 1);
  lcd.print("Humidity:");
  lcd.print(humidity, 1);
  lcd.print("g.kg-1");
   if (!digitalRead(selectButton)){
    break;
    delay(100);
    while (!digitalRead(selectButton));
  }
  }
  delay(2500);
}


void action4() {
  lcd.clear();

  lcd.begin(16, 2);
  lcd.print("Beta Call Miles");
  lcd.setCursor(0, 1);
  lcd.print("0789296068");
  delay(2500);
  //int count = millis();
  lcd.clear();
  lcd.begin(16, 2);
  lcd.print("Beta Call Miles");

  for(int i = 0; i < 5000; i++)
  {
        duration1 = pulseIn(echoPin, HIGH);
        delay(160);

        duration2 = pulseIn(echoPin, HIGH);
        delay(160);

        distance1 = duration1*0.034/2;
        distance2 = duration2*0.034/2;
        motion = distance1 + distance2;

        obspeed = motion/0.625;
    

  lcd.setCursor(0, 1);
  lcd.print("Speed: ");
  lcd.print(obspeed);
   if (!digitalRead(selectButton)){
    break;
    delay(100);
    while (!digitalRead(selectButton));
  }
  }
  delay(2500);
}


void action5(){
  
  lcd.begin(16, 2);
  lcd.print("Beta Call Miles");
  lcd.setCursor(0, 1);
  lcd.print("0789296068");
  delay(2500);
  //int count = millis();
  lcd.clear();
  lcd.begin(16, 2);
  lcd.print("Beta Call Miles");
  for(int i = 0; i < 5000; i++)
  {

  lcd.setCursor(0, 1);
  lcd.print("No Stored Values");
   if (!digitalRead(selectButton)){
    break;
    delay(100);
    while (!digitalRead(selectButton));
  }
  }
  delay(2500);
}



void action6(){
  
  lcd.begin(16, 2);
  lcd.print("Beta Call Miles");
  lcd.setCursor(0, 1);
  lcd.print("0789296068");
  delay(2500);
  //int count = millis();
  lcd.clear();
  lcd.begin(16, 2);
  lcd.print("Beta Call Miles");
  for(int i = 0; i < 5000; i++)
  {

  lcd.setCursor(0, 1);
  lcd.print("Resert Complete...");
   if (!digitalRead(selectButton)){
    break;
    delay(100);
    while (!digitalRead(selectButton));
  }
  }
  delay(2500);
}
