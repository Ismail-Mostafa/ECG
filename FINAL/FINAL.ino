#include <compat/deprecated.h>
#include <FlexiTimer2.h>
//http://www.arduino.cc/playground/Main/FlexiTimer2

#define SAMPFREQ 256                      // ADC sampling rate 256
#define TIMER2VAL (1024/(SAMPFREQ))       // Set 256Hz sampling frequency                    
#define LED1  13
#define CAL_SIG 9

// Global constants and variables
volatile unsigned char CurrentCh;         //Current channel being sampled.
volatile unsigned char counter = 0;	  //Additional divider used to generate CAL_SIG
volatile unsigned int ADC_Value = 0;	  //ADC current value
int value;
byte signal1,signal2;
byte heart_rate;
byte heart;
byte flag=0;
volatile unsigned int rate = 0;
void Toggle_LED1(void){

 if((digitalRead(LED1))==HIGH){ digitalWrite(LED1,LOW); }
 else{ digitalWrite(LED1,HIGH); }
 
}


void toggle_GAL_SIG(void){
  
 if(digitalRead(CAL_SIG) == HIGH){ digitalWrite(CAL_SIG, LOW); }
 else{ digitalWrite(CAL_SIG, HIGH); }
 
}

void setup() {

 noInterrupts();  // Disable all interrupts before initialization
 
 // LED1
 pinMode(LED1, OUTPUT);  //Setup LED1 direction
 digitalWrite(LED1,LOW); //Setup LED1 state
 pinMode(CAL_SIG, OUTPUT);

 FlexiTimer2::set(TIMER2VAL, Timer2_Overflow_ISR);
 FlexiTimer2::start();
 
 // Serial Port
 Serial.begin(57600);
 //Set speed to 57600 bps
 
 // MCU sleep mode = idle.
 //outb(MCUCR,(inp(MCUCR) | (1<<SE)) & (~(1<<SM0) | ~(1<<SM1) | ~(1<<SM2)));
 
 interrupts();  // Enable all interrupts after initialization has been completed
}

void Timer2_Overflow_ISR()
{
  // Toggle LED1 with ADC sampling frequency /2
  Toggle_LED1();
  

    ADC_Value = analogRead(0);
	signal1=ADC_Value;
        signal2=ADC_Value>>8;
    Serial.print("ss");
    Serial.write(signal1);
    Serial.print("nn");
    Serial.write(signal2);
    Serial.print("ht");
    Serial.write(heart);
  if(rate>=312)//15 sec
  {
  heart_rate=4*heart;  
   rate=0;
   heart=0; 
  }
 if(ADC_Value>700&&flage==0)
 {
  heart++;
  flag=1; 
 }
 if(ADC_Value<600&&flage==1)
 {
   flag=0; 
 }		
  
  // Generate the CAL_SIGnal
  counter++;		// increment the devider counter
  if(counter == 12){	// 250/12/2 = 10.4Hz ->Toggle frequency
    counter = 0;
     rate++;            //every 48 ms
    toggle_GAL_SIG();	// Generate CAL signal with frequ ~10Hz
  }
}

void loop() {
  
 __asm__ __volatile__ ("sleep");
 
}
