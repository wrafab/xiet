//#include <FastIO.h>
//#include <I2CIO.h>
//#include <LCD.h>


//#include <LiquidCrystal_SR.h>
//#include <LiquidCrystal_SR2W.h>
//#include <LiquidCrystal_SR3W.h>


#include <dht_nonblocking.h>
#include <LiquidCrystal.h>

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
/* Uncomment according to your sensortype. */
#define DHT_SENSOR_TYPE DHT_TYPE_11
//#define DHT_SENSOR_TYPE DHT_TYPE_21
//#define DHT_SENSOR_TYPE DHT_TYPE_22

static const int DHT_SENSOR_PIN = 10;
DHT_nonblocking dht_sensor( DHT_SENSOR_PIN, DHT_SENSOR_TYPE );



/*
 * Initialize the serial port.
 */
void setup( )
{
  Serial.begin( 115200 );
    lcd.begin(16, 2);
}



/*
 * Poll for a measurement, keeping the state machine alive.  Returns
 * true if a measurement is available.
 */
static bool measure_environment( float *temperature, float *humidity )
{
  static unsigned long measurement_timestamp = millis( );

  /* Measure once every four seconds. */
  if( millis( ) - measurement_timestamp > 4000ul )
  {
    if( dht_sensor.measure( temperature, humidity ) == true )
    {
      measurement_timestamp = millis( );
      return( true );
    }
  }

  return( false );
}



/*
 * Main program loop.
 */
void loop( )
{
  float temperature;
  float humidity;

  /* Measure temperature and humidity.  If the functions returns
     true, then a measurement is available. */
  if( measure_environment( &temperature, &humidity ) == true )
  {
     lcd.clear();
    Serial.print( "T " );
    Serial.print( temperature, 1 );
    lcd.print(temperature);
  
 //   Serial.print( " C, H = " );
  //  Serial.print( humidity, 1 );
    
 //   Serial.println( "%" );
    
     delay(100);
    // clear the screen
   //lcd.clear();
    // read all the available characters
    // Serial.println(Serial.available());

   // while (Serial.available() > 0) {
      // display each character to the LCD
  //    lcd.write(Serial.read());
   // }
  
    
  }
}
