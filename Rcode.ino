#include <LiquidCrystal.h>
#include <Servo.h>
Servo servo; 
int sensorvalue =0;  //flex reading input pin (A0)
int ThermistorPin=4; // thermistor reading input for arduino (A4)
int Vo;              // for equation thermistor
float R1=100000;       
float logR2,R2,T;
float c1=0.8272069482e-03,c2=2.087897328e-04,c3=0.8062131944e-07;
int reading=1;        // for Fsr input reading to the arduino
const int buzzer = 9;  
LiquidCrystal lcd(12,11,5,4,3,2);
void setup()
{
            pinMode(buzzer, OUTPUT);
            lcd.begin(16,2);
            lcd.clear(  );
            Serial.begin(9600);
            pinMode(A1,INPUT);//FSR input
            pinMode(A0,INPUT);// voltage divider value input
            pinMode(8,OUTPUT);// PWM output to servo
            servo.attach(8);// telling where signal pin of servo attached(must be a PWM pin)
}
void loop()
{
             sensorvalue = analogRead(A0); //read analog value from Flex sensor
             servo.write(sensorvalue-380);// take read of flex and send it output to servo 
             Serial.print("FlexReading=");
             Serial.println(sensorvalue);
             reading = analogRead(A1); // input to FSR
             Vo=analogRead(ThermistorPin);        //input to thermistor
             R2=R1*((5.0/(float)Vo)-1.0);
             logR2=log(R2);
             T=(1.0/(c1+c2*logR2+c3*logR2*logR2*logR2));
             T = T+27;
         
             lcd.print("Temp=");
             lcd.print(T);
             lcd.print("C");
             delay(500);
             lcd.clear();
             Serial.print("temp is");
             Serial.println(T);
             if(reading>700)
           {
            for(int i=0;i<=2;i++)
            {
               lcd.setCursor(0,0);  
            lcd.print("pressure is high");
            tone(buzzer,1500); // Send 1KHz sound signal...
            delay(500);
            noTone(buzzer);     // Stop sound...
            delay(500);
            }// ...for 1sec
            lcd.clear();
           }      
            
            Serial.print("FSR Reading =");
            Serial.println(reading);
}


