// Code Created by Make 2 Fix (Eng.Ahmed Hafez)
//24/08/2024

#include <avr/io.h>
#include <avr/interrupt.h>
#include <Adafruit_GFX.h>           // Core graphics library
#include <Adafruit_ST7789.h>        // Hardware-specific library for ST7789
#include <SPI.h>                    // Arduino SPI library
#include <Fonts/FreeSerif12pt7b.h>  // Add a custom font
#include <OneButton.h>

// ST7789 TFT module connections
#define TFT_CS   10  // define chip select pin
#define TFT_DC   6   // define data/command pin
#define TFT_RST  7   // define reset pin, or set to -1 and connect to Arduino RESET pin
//  SDA to pin 11
//  SCL to pin 13
#define E_calc   8   // define button to enable energy calculation

// Analog Pin Config
#define Vin     14
#define Cin     15
#define Vout    16
#define Cout    17

// Initialize Adafruit ST7789 TFT library

// OPTION 1 (recommended) is to use the HARDWARE SPI pins, which are unique
// to each board and not reassignable. For Arduino Uno: MOSI = pin 11 and
// SCLK = pin 13. This is the fastest mode of operation.

// To use this mode we have to modify Adafruit-GFX-Library as shown in the
// following link:
// https://github.com/adafruit/Adafruit-GFX-Library/pull/313

Adafruit_ST7789 tft = Adafruit_ST7789(TFT_CS, TFT_DC, TFT_RST);


// OPTION 2 lets you interface the display using ANY TWO or THREE PINS,
// tradeoff being that performance is not as fast as hardware SPI above.
#define TFT_MOSI 11  // Data out
#define TFT_CLK 13  // Clock out

//Adafruit_ST7789 tft = Adafruit_ST7789(TFT_CS, TFT_DC, TFT_MOSI, TFT_CLK,TFT_RST);   // Uncomment to use option 2

float p = 3.1415926;

// Define the reference voltage for the Arduino (usually 5V)
const float referenceVoltage = 5.00;

// Number of calibration points
const int numPointsVIN  = 23; 
const int numPointsVOUT = 23; 
const int numPointsCIN  = 10; 
const int numPointsCOUT = 10; 


// Calibration points
float inputVoltagePoints[]  = {0.0, 0.2054, 0.3101, 0.4170, 0.5218, 0.6289, 0.7351, 0.8402, 0.9447, 1.0508, 1.1575, 1.2648, 1.3697, 1.4755, 1.5796, 2.1106, 2.5343, 2.7554, 2.9667, 3.5943, 3.9904, 4.1816, 4.6421};
float correspondingVIN[]    = {0.0, 1.007,  1.501,  2.007,  2.500,  3.004,  3.501,  4.000,  4.501,  5.000,  5.506,  6.009,  6.502,  7.004,  7.501,  10.004, 12.00,  13.003, 14.013, 17.011, 19.00,  20.024, 23.03};

float outputVoltagePoints[] = {0.0, 0.2033, 0.3075, 0.4116, 0.5152, 0.6209, 0.7263, 0.8300, 0.9329, 1.0378, 1.1428, 1.2480, 1.3517, 1.4565, 1.5589, 2.0822, 2.5013, 2.7191, 2.9292, 3.5507, 3.9450, 4.1371, 4.6164};
float correspondingVOUT[]   = {0.0, 1.007,  1.501,  2.007,  2.500,  3.004,  3.501,  4.000,  4.501,  5.000,  5.506,  6.009,  6.502,  7.004,  7.501,  10.004, 12.00,  13.003, 14.013, 17.011, 19.00,  20.024, 23.03};

float inputCurrentPoints[]  = {0.0098, 0.0144, 0.0381, 0.2435, 0.5017, 1.0053, 1.5143, 2.0220, 2.5282, 4.0565};
float correspondingCIN[]    = {0.0,    0.050,  0.102,  0.500,  1.010,  2.005,  3.005,  4.010,  5.004,  8.005};

float outputCurrentPoints[] = {0.0196, 0.0302, 0.0566, 0.2688, 0.5379, 1.0628, 1.5909, 2.1220, 2.6555, 4.2350};
float correspondingCOUT[]   = {0.0,    0.050,  0.102,  0.500,  1.010,  2.005,  3.005,  4.010,  5.004,  8.005};

// The more point is taken the more accurate measured values,but with more memory usage.
// Calibration is described in get_values function.


//variables
float VIN  = 0;
float VOUT = 0;
float CIN  = 0; 
float COUT = 0; 
float rawVIN  = 0;
float rawVOUT  = 0;
float rawCIN  = 0;
float rawCOUT  = 0;
float PIN  = 0;
float POUT = 0;
float Efficiency=0;
float energy = 0;
float energy_Wh =0 ;
float voltage_compenstion = 0;
unsigned long previousMillis = 0;
unsigned long loop_delay = 10;
unsigned long currentMillis = 0;
bool E_enable = 0;


OneButton button;


void setup() {
  // setup OneButton
  Serial.begin(9600);               //for testing
  button.setup(E_calc, INPUT_PULLUP, true);
  analogReadResolution(12);         // Changing the ADC resolution to 12 bit

  // link the button function.
  button.attachClick(singleclick);
  
  // if the display has CS pin try with SPI_MODE0
  tft.init(135, 240, SPI_MODE0);    // Init ST7789 display 135x240 pixel

  tft.setRotation(3);               // if the screen is flipped, remove this command
  tft.setTextWrap(false);
  tft.fillScreen(ST77XX_BLACK);
  tft.setFont(&FreeSerif12pt7b);    // Set a custom font
  tft.setTextSize(0);               // Set text size. We are using custom font so you should always set text size as 0
  tft.setCursor(30, 30);            // Set position (x,y)
  tft.setTextColor(ST77XX_WHITE);   // Set color of text. We are using custom font so there is no background color supported
  tft.println("Efficiency Meter");  // Print a text or value
  tft.setCursor(40, 60);
  tft.print("Smile Dude :)");
  energy_Wh = 1;
  delay(1000); 
  tft.setCursor(180, 125);
  tft.print("M2F"); 
  delay(500);
  // Stop using a custom font:
  tft.setFont();                    // Reset to standard font, to stop using any custom font previously set
  tft.fillScreen(ST77XX_BLACK);
}



void loop() {
  // keep watching the push button:
  button.tick();
  
  currentMillis = millis();
  if (currentMillis - previousMillis >= loop_delay)
  {
    get_values();
    display_data();
    previousMillis = currentMillis;
  } 
}




// THIS FUNCTION WILL MAP THE float VALUES IN THE GIVEN RANGE
// This function was built using ChatGPT.
float linearizeVoltage(float x, float* xValues, float* yValues, int points) {
  // If x is out of bounds, clamp it to the min or max
  if (x <= xValues[0]) return yValues[0];
  if (x >= xValues[points - 1]) return yValues[points - 1];

  // Find the interval x is in
  for (int i = 0; i < points - 1; i++) {
    if (x >= xValues[i] && x <= xValues[i + 1]) {
      // Linear interpolation formula
      float x0 = xValues[i];
      float x1 = xValues[i + 1];
      float y0 = yValues[i];
      float y1 = yValues[i + 1];
      return y0 + (y1 - y0) * ((x - x0) / (x1 - x0));
    }
  }
  // Should never reach here
  return 0.0;
}


//This functions will calculate the curret, voltage, power and energy values
void get_values()
{
  rawVIN  = 0;
  rawVOUT = 0;
  rawCIN  = 0;
  rawCOUT = 0;
  // For loops is for averaging measured values we choose 50.
  // If needed this value can be increased to get more stable readings.
  for(int x = 0; x < 50; x++){
    rawVIN  += analogRead(Vin)  * (referenceVoltage / 4095.0);        
    delay(1);
  }
  for(int x = 0; x < 50; x++){
    rawVOUT += analogRead(Vout) * (referenceVoltage / 4095.0);
    delay(1);
  }
  for(int x = 0; x < 50; x++){
    rawCIN  += analogRead(Cin)  * (referenceVoltage / 4095.0);           
    delay(1);
  }
  for(int x = 0; x < 50; x++){
    rawCOUT += analogRead(Cout) * (referenceVoltage / 4095.0);           
    delay(1);
  }
  
  rawVIN  = rawVIN/50;
  rawVOUT = rawVOUT/50;
  rawCIN  = rawCIN/50;
  rawCOUT = rawCOUT/50;

  VIN  = linearizeVoltage(rawVIN,  inputVoltagePoints,  correspondingVIN,  numPointsVIN) ;
  VOUT = linearizeVoltage(rawVOUT, outputVoltagePoints, correspondingVOUT, numPointsVOUT) ;
  CIN  = linearizeVoltage(rawCIN,  inputCurrentPoints,  correspondingCIN,  numPointsCIN) ;
  COUT = linearizeVoltage(rawCOUT, outputCurrentPoints, correspondingCOUT, numPointsCOUT) ;

  //Voltage calibration:
  /*Serial.print("Input Voltage: ");         
  Serial.print(rawVIN,4);                  
  Serial.print(" V, Output Voltage: "); 
  Serial.println(rawVOUT,4);*/

  //Current calibration:
  /*Serial.print("Input Voltage: ");        
  Serial.print(rawCIN,4);                  
  Serial.print(" V, Output Voltage: "); 
  Serial.println(rawCOUT,4);*/


/* Calibration Processs: 
     Voltage Readings:
         - We connect input and output voltage terminal together to use one source for calibration.
         - then connect an accurate and stable voltage source to them with an accurate voltmeter.
         - Uncomment Voltage calibration serial print code.
         - Set the voltage source for an example to 1V then open the terminal to see the MCU readings
           in my case Input Voltage = 0.2054V and Output Voltage = 0.2033V, record these readings 
           in the inputVoltagePoints outputVoltagePoints Lists with respect to corresponding voltages in 
           correspondingVIN and correspondingVOUT lists.
         - repeat this step with different voltages until reaching an accurate readings in LCD equal to 
           voltmeter in our available voltage range, in my case is 0-23V range.

      Current Readings:
         - We connect input and output voltage terminal together to use one source for calibration.
         - then connect a bench power supply to input terminals and in output terminals we use 
           an accurate and stable constant current load in series with an accurate ammeter.
         - Uncomment Current calibration serial print code.
         - Set the current load for an example to 1A then open the terminal to see the MCU readings
           in my case Input Voltage = 0.5017V and Output Voltage = 0.5379V, record these readings 
           in the inputCurrentPoints outputCurrentPoints Lists with respect to corresponding currents in 
           correspondingCIN and correspondingCOUT lists.
         - Don't forget to calibrate zero ampare point first.
         - Repeat this step with different loads until reaching an accurate readings in LCD equal to 
           ammeter in our available current range, in my case is 0-10A range.
         - I reached a maximum current reading of 8A as I don't have power supply or constant load can handle more than this.*/
   
 
  PIN = VIN*CIN;              //Calculate power and energy
  POUT = VOUT*COUT;
  if(PIN == 0){
    Efficiency = 0;
  }
  else{
  Efficiency = (POUT/PIN)*100;
  Efficiency = constrain(Efficiency,0,100); //Limit settings values to a range
  }
}


// This function will be called when the button1 was pressed 1 time.
void singleclick() {
  if(E_enable == 0){
    E_enable = 1;
  }
  else if(E_enable ==1){
    E_enable = 0;
    energy = 0;
    energy_Wh = 1;
  }
}
