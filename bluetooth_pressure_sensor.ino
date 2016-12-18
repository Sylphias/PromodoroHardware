//#include <SoftwareSerial.h>
//#include <Wire.h> // Must include Wire library for I2C
//#include <SFE_MMA8452Q.h> 
//
//MMA8452Q accel(0x1D); 
//SoftwareSerial BT(11, 10); 
//// creates a "virtual" serial port/UART
//// connect BT module TX to D10
//// connect BT module RX to D11
//// connect BT Vcc to 5V, GND to GND
//void setup()  
//{
//  // set digital pin to control as an output
//  pinMode(2, OUTPUT);
//  // set the data rate for the SoftwareSerial port
//  BT.begin(9600);
//  // Send test message to other device
//  BT.println("Bluetooth Online!");
//  accel.init(SCALE_2G, ODR_12);
//  BT.println("Accelerometer Online!");
//}
//char a; // stores incoming character from other device
//byte state;
//void loop() 
//{
//  if (BT.available())
//  {
//    if (accel.available())
//  {
//    // First, use accel.read() to read the new variables:
//    accel.read();
//
//    printOrientation();
//     
//  }
////    a=(BT.read());
////    if (a=='1')
////    {
////      digitalWrite(2, HIGH);
////      BT.println("LED on");
////    }
////    if (a=='2')
////    {
////      digitalWrite(2, LOW);
////      BT.println("LED off");
////    }
////    if (a=='?')
////    {
////      BT.println("Send '1' to turn LED on");
////      BT.println("Send '2' to turn LED on");
////    }   
//    // you can add more "if" statements with other characters to add more commands
//  }
//  delay(500 );
//}
//
//void printOrientation()
//{
//  // accel.readPL() will return a byte containing information
//  // about the orientation of the sensor. It will be either
//  // PORTRAIT_U, PORTRAIT_D, LANDSCAPE_R, LANDSCAPE_L, or
//  // LOCKOUT.
//  byte pl = accel.readPL();
//
//  if(state != pl){
//    switch (pl)
//  {
//  case PORTRAIT_U:
//    BT.print("Portrait Up");
//    BT.println();
//    break;
//  case PORTRAIT_D:
//    BT.print("Portrait Down");
//    BT.println();
//    break;
//  case LANDSCAPE_R:
//    BT.print("Landscape Right");
//    BT.println();
//    break;
//  case LANDSCAPE_L:
//    BT.print("Landscape Left");
//    BT.println();
//    break;
//  case LOCKOUT:
//    BT.print("Flat");
//    BT.println();
//    break;
//  }
//  }
//  state = pl;
//}

#include <SoftwareSerial.h>
/* FSR testing sketch. 
 
Connect one end of FSR to power, the other end to Analog 0.
Then connect one end of a 10K resistor from Analog 0 to ground 
 
For more information see www.ladyada.net/learn/sensors/fsr.html */
 
int fsrPin = 5;     // the FSR and 10K pulldown are connected to a0
int fsrReading;     // the analog reading from the FSR resistor divider
int fsrVoltage;     // the analog reading converted to voltage
unsigned long fsrResistance;  // The voltage converted to resistance, can be very big so make "long"
unsigned long fsrConductance; 
char state = 0;
long fsrForce;       // Finally, the resistance converted to force
SoftwareSerial BT(11,10);
 
void setup(void) {
  Serial.begin(9600);   // We'll send debugging information via the Serial monitor
  BT.begin(9600);
  BT.println("BT ONLINE");
  
}
 
void loop(void) {
  fsrReading = analogRead(fsrPin);  
//  Serial.print("Analog reading = ");
//  Serial.println(fsrReading);
 
  // analog voltage reading ranges from about 0 to 1023 which maps to 0V to 5V (= 5000mV)
  fsrVoltage = map(fsrReading, 0, 1023, 0, 5000);
  printSeatState();
//  Serial.print("Voltage reading in mV = ");
//  Serial.println(fsrVoltage);  
// 
//    // The voltage = Vcc * R / (R + FSR) where R = 10K and Vcc = 5V
//    // so FSR = ((Vcc - V) * R) / V        yay math!
//    fsrResistance = 5000 - fsrVoltage;     // fsrVoltage is in millivolts so 5V = 5000mV
//    fsrResistance *= 10000;                // 10K resistor
//    fsrResistance /= fsrVoltage;
//    BT.print("FSR resistance in ohms = ");
//    BT.println(fsrResistance);
// 
//    fsrConductance = 1000000;           // we measure in micromhos so 
//    fsrConductance /= fsrResistance;
//    BT.print("Conductance in microMhos: ");
//    BT.println(fsrConductance);
// 
//    // Use the two FSR guide graphs to approximate the force
//    if (fsrConductance <= 1000) {
//      fsrForce = fsrConductance / 80;
//      BT.print("Force in Newtons: ");
//      BT.println(fsrForce);      
//    } else {
//      fsrForce = fsrConductance - 1000;
//      fsrForce /= 30;
//      BT.print("Force in Newtons: ");
//      BT.println(fsrForce);            
//    }
//  if(BT.available()){
//    char a=BT.read();
//    BT.println(a);
//  }
  delay(1000);
}

void printSeatState(){
  int pl = 0;
    if (fsrVoltage == 0) {
    pl = 0;
     
  } else{
    pl = 1;
  }

    if(state != pl){
    switch (pl)
  {
  case 1:
    BT.print("1");
    break;
  case 0:
    BT.print("0");
    break;
  }
  state = pl;
  }
}

