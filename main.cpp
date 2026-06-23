#include <AS5600.h>  // https://github.com/RobTillaart/AS5600
#include <LCD_I2C.h> // https://github.com/blackhack/LCD_I2C


// AS5600L as5600;
AS5600 as5600;
LCD_I2C lcd(0x27, 16, 2); // address, width, height. address specific to PCF8574 chip

int last_time;
int now;


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

  last_time = millis();
  delay(1000);
}


void loop()
{

now = millis();

if (now - last_time > 500) { // serial print position & speed every 500ms
    last_time = millis();
    Serial.print("t = ");
    Serial.print(last_time);
    Serial.print("\tω = ");
    Serial.println(as5600.getAngularSpeed(AS5600_MODE_RPM));
    Serial.print(" rev/min\n");
    Serial.print("\tθ = ");
    Serial.println(as5600.getAngle(AS5600_MODE_DEGREE));
    Serial.print(" degrees\n");
}



last_time = now;

}