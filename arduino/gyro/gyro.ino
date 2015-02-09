#include <SPI.h>
#include <stdarg.h>

const int CSpin = 10;

void setup()
{
  Serial.begin(9600);
  pinMode(CSpin, OUTPUT);  // set CS pin as OUTPUT
  digitalWrite(CSpin, HIGH);  // sets cs to high
  SPI.setClockDivider(SPI_CLOCK_DIV16);  // sets SPI clock to 5MHz
  SPI.begin();  // start SPI
  GyroSetup();
}

void loop(){
  delay(50);
  Gyro_regular();
}

void GyroSetup(){
  delay(200);
  digitalWrite(CSpin, LOW);  // sets chip select to transfer data
  delay(100);
  /*long*/uint32_t result = SPI.transfer(0x20);  // sends a byte of data
  result = result << 8;
  result += SPI.transfer(0x00);
  result = result << 8;
  result += SPI.transfer(0x00);
  result = result << 8;
  result += SPI.transfer(0x03);
  Serial.print("bin ");
  Serial.println(result, BIN);  // output value
  digitalWrite(CSpin, HIGH);  // de-selects chip select
}

double total = 0;
double current = 0;
double prev = 0;
unsigned long time = 0;
int counter = 0;

void Gyro_regular(){
  
  digitalWrite(CSpin, LOW);
  uint32_t result = SPI.transfer(0x20);  //sends a byte of data
  result = result << 8;  
  result += SPI.transfer(0x00);
  result = result << 8;
  result += SPI.transfer(0x00);
  result = result << 8;
  result += SPI.transfer(0x00);
  
  counter++;
  
  if(counter > 10){
    current = ((signed short)((result >> 10) & 0xFFFF)/80.0) - 0.406;
  }
  
  
  total += current * (millis() - time) / 1000.0;
  
  Serial.print("time ");
  Serial.print(millis() / 1000.0);
  Serial.print(" deltaT ");
  Serial.print((millis() - time) / 1000.0);
  Serial.print(" total ");
  Serial.print(total);
  Serial.print(" current ");
  Serial.println(current);
  prev = current;
  
  time = millis();

  digitalWrite(CSpin, HIGH);  //de-selects chip select
}
