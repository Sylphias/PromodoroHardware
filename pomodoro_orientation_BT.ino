#include <SoftwareSerial.h>
#include <Wire.h> // Must include Wire library for I2C
#include <SFE_MMA8452Q.h> 

MMA8452Q accel(0x1D); 
SoftwareSerial BT(11, 10); 
// creates a "virtual" serial port/UART
// connect BT module TX to D10
// connect BT module RX to D11
// connect BT Vcc to 5V, GND to GND
void setup()  
{
  // set digital pin to control as an output
  pinMode(2, OUTPUT);
  // set the data rate for the SoftwareSerial port
  BT.begin(9600);
  // Send test message to other device
  BT.println("Bluetooth Online!");
  accel.init(SCALE_2G, ODR_12);
  BT.println("Accelerometer Online!");
}
char a; // stores incoming character from other device
byte state;
void loop() 
{
//  if (BT.available())
if(true)
  {

    if (accel.available())
  {
    // First, use accel.read() to read the new variables:
    accel.read();

    printOrientation();
     
  }
//    a=(BT.read());
//    if (a=='1')
//    {
//      digitalWrite(2, HIGH);
//      BT.println("LED on");
//    }
//    if (a=='2')
//    {
//      digitalWrite(2, LOW);
//      BT.println("LED off");
//    }
//    if (a=='?')
//    {
//      BT.println("Send '1' to turn LED on");
//      BT.println("Send '2' to turn LED on");
//    }   
    // you can add more "if" statements with other characters to add more commands
  }
  delay(100);
}

void printOrientation()
{
  // accel.readPL() will return a byte containing information
  // about the orientation of the sensor. It will be either
  // PORTRAIT_U, PORTRAIT_D, LANDSCAPE_R, LANDSCAPE_L, or
  // LOCKOUT.
  byte pl = accel.readPL();

  if(state != pl){
    switch (pl)
  {
  case PORTRAIT_U:
    BT.print("0");
    break;
  case PORTRAIT_D:
    BT.print("1");
    break;
  case LANDSCAPE_R:
    BT.print("2");
    break;
  case LANDSCAPE_L:
    BT.print("3");
    break;
  case LOCKOUT:
    BT.print("4");
    break;
  }
  }
  state = pl;
}
