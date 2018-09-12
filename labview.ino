// Pin definitions:
// The 74HC595 uses a type of serial connection called SPI
// (Serial Peripheral Interface) that requires three pins:

int datapin = 2; 
int clockpin = 3;
int latchpin = 4;

// We'll also declare a global variable for the data we're
// sending to the shift register:

byte data = 0;


void setup()
{
  digitalWrite(13, LOW);
  // Set the three SPI pins to be outputs:

  pinMode(datapin, OUTPUT);
  pinMode(clockpin, OUTPUT);  
  pinMode(latchpin, OUTPUT);
}


void loop()
{
  binaryCount();        // Bit patterns from 0 to 255
}


void shiftWrite(int desiredPin, boolean desiredState)
{
// This function lets you make the shift register outputs
// HIGH or LOW in exactly the same way that you use digitalWrite().

  bitWrite(data,desiredPin,desiredState); //Change desired bit to 0 or 1 in "data"
  
  // Now we'll actually send that data to the shift register.
  // The shiftOut() function does all the hard work of
  // manipulating the data and clock pins to move the data
  // into the shift register:

  shiftOut(datapin, clockpin, MSBFIRST, data); //Send "data" to the shift register

  //Toggle the latchPin to make "data" appear at the outputs
  digitalWrite(latchpin, HIGH); 
  digitalWrite(latchpin, LOW); 
}

void binaryCount()
{
// This function creates a visual representation of the on/off pattern
// of bits in a byte. 

  int delayTime = 1000; // time (milliseconds) to pause between LEDs
                        // make this smaller for faster switching
  
  // Send the data byte to the shift register:

  shiftOut(datapin, clockpin, MSBFIRST, data);

  // Toggle the latch pin to make the data appear at the outputs:

  digitalWrite(latchpin, HIGH);
  digitalWrite(latchpin, LOW);
  
  // Add one to data, and repeat!
  // (Because a byte type can only store numbers from 0 to 255,
  // if we add more than that, it will "roll around" back to 0
  // and start over).

  data++;

  // Delay so you can see what's going on:

  delay(delayTime);
}
