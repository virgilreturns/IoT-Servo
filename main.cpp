#include <AS5600.h>  // https://github.com/RobTillaart/AS5600
#include <LCD_I2C.h> // https://github.com/blackhack/LCD_I2C


// AS5600L as5600;
AS5600 as5600;
LCD_I2C lcd(0x27, 16, 2); // address, width, height. address specific to PCF8574 chip

int last_time; int now; int angle; int speed;
uint8_t header, mode, value;



void setup()
{
  while(!Serial);
  Serial.begin(115200);
  Serial.println();
  Serial.println(__FILE__);
  Serial.print("AS5600_LIB_VERSION: ");
  Serial.println(AS5600_LIB_VERSION);
  Serial.println();

  Wire.begin();

  as5600.begin(4);  //  set direction pin.
  as5600.setDirection(AS5600_CLOCK_WISE);  //  default, just be explicit.

  Serial.println(as5600.getAddress());

  // as5600.setAddress(0x40);  //  AS5600L only

  int b = as5600.isConnected();
  Serial.print("Connect: ");
  Serial.println(b);
 
  lcd.begin();
  lcd.backlight();

  last_time = millis();
  delay(1000);
}

/*
TODO:

LCD display current rpm, angle
encoder knob for user control
serial control?


*/ 


void loop()
{

now = millis();

if (Serial.available() >= 3){
  uint8_t header = Serial.read();
  uint8_t mode   = Serial.read();
  uint8_t value  = Serial.read();
}

if (now - last_time > 250) { // serial print position & speed every 500ms

  speed = as5600.getAngularSpeed(AS5600_MODE_ANGULAR_SPEED_RPM);
  angle = as5600.getAngle(AS5600_MODE_DEGREE);

  Serial.print("\tω = ");
  Serial.println(speed);
  Serial.print(" rev/min\n");
  Serial.print("\tθ = ");
  Serial.println(angle);
  Serial.print(" degrees\n");

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Speed: ");
  lcd.print(speed);
  lcd.print(" rpm");
  lcd.setCursor(0, 1);
  lcd.print("Angle: ");
  lcd.print(angle);
  lcd.print(" deg");



}





last_time = now;
}