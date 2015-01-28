
int mode = 1;
double distance; 
double calibration;
 
void setup()
{
  Serial.begin(9600);
  pinMode(12, INPUT);
}
 
void loop()
{
  if(mode == 1)
  {
  //Read duration in microSeconds
  long duration = pulseIn(12, HIGH);
   
  //58 uS per cm for MB1240 XL-MaxSonar
  //Operation Range: 20 cm min (50 cm for accurate)
  distance = duration / 58.0; 
  calibration = 1;
  }
   
  double cmToInch = 0.393701;
 
  //Analog Seems to be More Accurate due to PWM timing
  Serial.println((distance+calibration)*cmToInch);
  delay(100);
}
