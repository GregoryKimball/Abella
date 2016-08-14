/*
 *
 * Abella Sine Generator for ATMEGA328
 * 
 *
 * Gregory Kimball 2015
 * 
 * 
 */
 
 
#include "avr/pgmspace.h"
#include "math.h"

// table of 256 sine values / one sine period / stored in flash memory
PROGMEM  prog_uchar sine256[]  = 

{127,132,136,141,145,150,155,159,164,168,172,177,181,185,189,193,196,200,203,207,210,213,216,218,221,223,226,228,230,231,233,234,236,236,237,238,238,239,239,239,239,238,238,237,236,235,234,232,230,229,227,225,223,221,218,216,214,211,208,205,202,200,197,194,191,187,184,181,178,175,172,168,165,162,159,155,153,150,147,143,141,138,135,132,130,128,125,123,121,119,117,115,114,112,111,110,109,108,106,106,105,104,104,104,104,104,103,104,104,104,105,105,107,107,108,109,110,111,113,114,115,117,118,120,121,122,124,125,127,129,130,132,133,134,136,137,139,140,141,143,144,145,146,147,147,149,149,150,150,150,151,150,150,150,150,150,149,148,148,146,146,144,143,142,140,139,137,135,133,131,129,126,124,122,119,116,113,111,107,104,101,99,95,92,89,86,82,79,76,73,70,67,64,60,57,54,52,49,46,43,40,38,36,33,31,29,27,25,24,22,20,19,18,17,16,16,15,15,15,15,16,16,17,18,19,20,21,23,24,26,28,31,33,36,38,41,44,47,51,54,58,61,65,69,73,77,82,86,90,95,99,104,109,113,118,122
};//multi sine





int notes[] = 
{  110,117,123,131,138,147,155,165,175,185,196,207,220, 233,247, 262,277,294,311,330,349,370,392,415,440};  //two octaves chromatic


int Cmajor[] = {131,147,165,175,196,220,247,262,294,330,349,392,440,494,523};
int Dmajor[] = {147,165,185,196,220,247,277,294,330,370,392,440,494,554,587};
int Emajor[] = {165,185,208,220,247,277,311,330,370,415,440,494,554,622,660};
int Fmajor[] = {174,196,220,233,262,294,330,349,392,440,466,523,587,659,698};
int Gmajor[] = {196,220,247,262,294,330,370,392,440,494,523,587,659,740,784};
int Amajor[] = {110,123,139,147,165,185,208,220,247,277,294,330,370,415,440};
int Bmajor[] = {123,139,155,165,185,208,233,247,277,311,330,370,415,466,494};

int Csharpmajor[] = {139,156,175,185,208,233,262,277,311,349,370,415,466,523,554};
int Dsharpmajor[] = {156,175,196,208,233,277,294,311,349,392,415,466,523,554,622};
int Fsharpmajor[] = {185,208,233,247,277,311,349,370,415,466,494,554,622,698,740};
int Gsharpmajor[] = {104,117,131,139,156,175,196,208,233,262,277,311,349,392,415};
int Asharpmajor[] = {117,131,147,156,175,196,220,233,262,294,311,349,392,440,466};

//cde ga
int Cmajorpent[] = {131,147,165,    196,220,    262,294,330,    392,440,    523};
int Dmajorpent[] = {147,165,185,    220,247,    294,330,370,    440,494,    587};
int Emajorpent[] = {165,185,208,    247,277,    330,370,415,    494,554,    660};
int Fmajorpent[] = {174,196,220,    262,294,    349,392,440,    523,587,    698};
int Gmajorpent[] = {196,220,247,    294,330,    392,440,494,    587,659,    784};
int Amajorpent[] = {110,123,139,    165,185,    220,247,277,    330,370,    440};
int Bmajorpent[] = {123,139,155,    185,208,    247,277,311,    370,415,    494};

int Csharpmajorpent[] = {139,156,175,    208,233,    277,311,349,    415,466,    554};
int Dsharpmajorpent[] = {156,175,196,    233,277,    311,349,392,    466,523,    622};
int Fsharpmajorpent[] = {185,208,233,    277,311,    370,415,466,    554,622,    740};
int Gsharpmajorpent[] = {104,117,131,    156,175,    208,233,262,    311,349,    415};
int Asharpmajorpent[] = {117,131,147,    175,196,    233,262,294,    349,392,    466};

int chromatic[] = {  110,117,123,131,139,147,156,165,175,185,196,208,220, 233,247, 262,277,294,311,330,349,370,392,415,440} ;
//int pentatonic[] = {116,139, 156,185,208,233,277,311,370,415,466};
//int pentatonic3[] = {116,139, 156,185,208,233,277,311,370,415,466,554,622,740,830,932};
//int Cmajorpentatonic[] = {262, 293, 330, 392, 440, 523, 587, 659, 784, 880, 1047};
//int Cminorpentatonic[] = {262, 311, 349, 392, 466, 523, 622, 698, 784, 932, 1047};



int all_notes[] = {131,138,147,155,165,175,185,196,207,220, 233,247, 262,277,294,311,330,349,370,392,415,440};

int notes_len = 15;
int all_notes_len = 25;
int bin_size = 1024/notes_len;
const int colorOffset = 2;//first note c



#define cbi(sfr, bit) (_SFR_BYTE(sfr) &= ~_BV(bit))
#define sbi(sfr, bit) (_SFR_BYTE(sfr) |= _BV(bit))

int ledPin = 13;                 // LED pin 7
byte bb;

double dfreq;

double acc_z;
double last_z;
double now_x;
double now_z;
double tilt;


// const double refclk=31372.549;  // =16MHz / 510
const double refclk=31376.6;      // measured

// variables used inside interrupt service declared as voilatile
volatile byte icnt;              // var inside interrupt
volatile byte icnt1;             // var inside interrupt
volatile byte c4ms;              // counter incremented all 4ms
volatile unsigned long phaccu;   // pahse accumulator
volatile unsigned long tword_m;  // dds tuning word m



 const int myPins[] = {10, 9, 6, 3};
 const int pinCount = 4;
 const int White = 6;
 const int Blue = 10;
 const int Green = 9;
 const int Red = 3;
 
 const int r_int[] = {100, 80, 60,  0,  0,  0, 80};
 const int g_int[] = {  0, 30, 60,100, 50,  0,  0};
 const int b_int[] = {  0,  0,  0,  0, 50,120,100};
 const int w_int[] = {  0,  0,  0,  0,  0, 0,  0};





void setup()
{
 
  Serial.begin(115200);        // connect to the serial port
  Serial.println("DDS Test");
  pinMode(11, OUTPUT);     // pin11= PWM  output / frequency output
  pinMode(2,INPUT); //half stepper
  
  for (int thisPin =0; thisPin < pinCount; thisPin++)
  { 
    setPwmFrequency(myPins[thisPin], 1);
    pinMode(myPins[thisPin], OUTPUT); 
  }

  Setup_timer2();

  // disable interrupts to avoid timing distortion
  cbi (TIMSK0,TOIE0);              // disable Timer0 !!! delay() is now not available
  sbi (TIMSK2,TOIE2);              // enable Timer2 Interrupt

  dfreq=440.0;                     // initial output frequency = 440 Hz
  tword_m=pow(2,32)*dfreq/refclk;  // calulate DDS new tuning word 

}


void loop()
{
  int c = 0,cc=0;int d = 0, e=0;
  
  int freq_in=0;int last_freq=0;int freq_color=0;int raw_freq = 0;
  
  while(1) {
    if (c4ms > 10) 
    {                 // timer / wait fou a full second
      c4ms=0;
      c4ms++;       

      acc_z =  (analogRead(3) - 227)/-1.5;      
      d= analogRead(1);
      e = analogRead(2);

      SetScale(d);      
      raw_freq = analogRead(0);      
      
      freq_in=raw_freq;
      freq_color=raw_freq;
      

      if ((freq_in < last_freq + 7 && freq_in > last_freq - 7 ) || e > 100 )
      {
          Serial.print("NOO  ");
          if (freq_in < last_freq + 7 && freq_in > last_freq - 7 ) 
            freq_color=last_freq;
          freq_in = last_freq;        
      }
      else
      {        
         last_freq = freq_in;         
      }


  
      
      c = freq_in/bin_size;
      if (c==notes_len)
         c=notes_len-1;
         
      cc = freq_color/bin_size;
      if (cc==notes_len)
         cc=notes_len-1;      
      
      dfreq= notes[c] + acc_z;       
  
      SetLightContinuous(notes[cc]);

      cbi (TIMSK2,TOIE2);              // disble Timer2 Interrupt
      tword_m=pow(2,32)*dfreq/refclk;  // calulate DDS new tuning word
      sbi (TIMSK2,TOIE2);              // enable Timer2 Interrupt 


      Serial.print("   ");
      Serial.print(d);

      // serial commands for debugging
      /*
      Serial.print(e);
      Serial.print("   ");
      Serial.print(c);
      Serial.print("   ");
      Serial.print(raw_freq);
      Serial.print("   ");         
      Serial.print(last_freq);
      Serial.print("   ");
      Serial.print(dfreq);*/
            
       Serial.println("  ");

     
    }

   
  }
}



 /* KHM 2009 /  Martin Nawrath
 * Kunsthochschule fuer Medien Koeln
 * Academy of Media Arts Cologne */
// set prscaler to 1, PWM mode to phase correct PWM,  16000000/510 = 31372.55 Hz clock
void Setup_timer2() 
{

  // Timer2 Clock Prescaler to : 1
  sbi (TCCR2B, CS20);
  cbi (TCCR2B, CS21);
  cbi (TCCR2B, CS22);

  // Timer2 PWM Mode set to Phase Correct PWM
  cbi (TCCR2A, COM2A0);  // clear Compare Match
  sbi (TCCR2A, COM2A1);

  sbi (TCCR2A, WGM20);  // Mode 1  / Phase Correct PWM
  cbi (TCCR2A, WGM21);
  cbi (TCCR2B, WGM22);
}


 /* KHM 2009 /  Martin Nawrath
 * Kunsthochschule fuer Medien Koeln
 * Academy of Media Arts Cologne */
// Timer2 Interrupt Service at 31372,550 KHz = 32uSec
// this is the timebase REFCLOCK for the DDS generator
// FOUT = (M (REFCLK)) / (2 exp 32)
// runtime : 8 microseconds ( inclusive push and pop)
ISR(TIMER2_OVF_vect) 
{
 // sbi(PORTD,7);          // Test / set PORTD,7 high to observe timing with a oscope
  phaccu=phaccu+tword_m; // soft DDS, phase accu with 32 bits
  icnt=phaccu >> 24;     // use upper 8 bits for phase accu as frequency information
  // read value fron ROM sine table and send to PWM DAC
  OCR2A=pgm_read_byte_near(sine256 + icnt);    
  if(icnt1++ == 125) 
  {  // increment variable c4ms all 4 milliseconds
    c4ms++;
    icnt1=0;
  }   
  //cbi(PORTD,7);            // reset PORTD,7
}





//convert an audio frequency value in Hz into the corresponding color output
void SetLight(int c)
{
  c = c + colorOffset;  
  if (c < 0 ) c= c+7;
  if (c > 6) c = c-7;
  if (c > 6) c = c-7;   
  analogWrite(Red,r_int[c]);
  analogWrite(Green,g_int[c]);
  analogWrite(Blue,b_int[c] );
  analogWrite(White,w_int[c]);  
}




//convert an audio frequency value in Hz into the corresponding color output
void SetLightContinuous(double freq)
{
   double  angle = 517 * log(freq)-2419-30;
   int r = 100 * sin(radians(angle+90))+50;
   int g = 140 * sin(radians(angle+330))+50;
   int b = 100 * sin(radians(angle+210))+50;
   int w = 300 * pow(sin(radians(angle*3+170)),5)-150;
   
   if (r<0) r = 0;
   if (g<0) g = 0;
   if (b<0) b = 0;
   if (w<0) w = 0;
   
   if (r > 255) r= 255;
   if (g > 255) g= 255;
   if (b > 255) b= 255;   
   if (w > 255) w= 255;   
   
   analogWrite(Red,r);
   analogWrite(Green,g);
   analogWrite(Blue,b);
   analogWrite(White,w);
}


//convert the DIP switch voltage divider into the corresponding key or scale
void SetScale(double s)
{  
    const int b = 2;//may need to increase as device ages
   
    if (s > 50 -b && s< 50 +b) SetArray(notes,Cmajor,15);
    if (s >  70 -b && s<  70 +b) SetArray(notes,Dmajor,15);
    if (s > 112 -b && s< 112 +b) SetArray(notes,Emajor,15);
    if (s > 161 -b && s< 161 +b) SetArray(notes,Fmajor,15);
    if (s > 234 -b && s< 234 +b) SetArray(notes,Gmajor,15);
    if (s > 335 -b && s< 335 +b) SetArray(notes,Amajor,15);
    if (s > 468 -b && s< 468 +b) SetArray(notes,Bmajor,15);    
    if (s > 654 -b && s< 654 +b) SetArray(notes,Cmajorpent,11);
    if (s > 663 -b && s< 663 +b) SetArray(notes,Dmajorpent,11);
    if (s > 686 -b && s< 686 +b) SetArray(notes,Emajorpent,11);
    if (s > 710 -b && s< 710 +b) SetArray(notes,Fmajorpent,11);
    if (s > 744 -b && s< 744 +b) SetArray(notes,Gmajorpent,11);
    if (s > 786 -b && s< 786 +b) SetArray(notes,Amajorpent,11);
    if (s > 836 -b && s< 836 +b) SetArray(notes,Bmajorpent,11);


    // if you would like to switch the DIP parameters to the sharped major scales...    
    /*if (s >  96 -b && s<  96 +b) SetArray(notes,Csharpmajor,15);
    if (s > 147 -b && s< 147 +b) SetArray(notes,Dsharpmajor,15);
    if (s > 324 -b && s< 324 +b) SetArray(notes,Fsharpmajor,15);
    if (s > 461 -b && s< 461 +b) SetArray(notes,Gsharpmajor,15);
    if (s > 639 -b && s< 639 +b) SetArray(notes,Asharpmajor,15);
    if (s > 678 -b && s< 678 +b) SetArray(notes,Csharpmajorpent,11);
    if (s > 704 -b && s< 704 +b) SetArray(notes,Dsharpmajorpent,11);
    if (s > 794 -b && s< 794 +b) SetArray(notes,Fsharpmajorpent,11);
    if (s > 856 -b && s< 856 +b) SetArray(notes,Gsharpmajorpent,11);
    if (s > 932 -b && s< 932 +b) SetArray(notes,Asharpmajorpent,11);*/
    
    if (s > 0  -b && s< 0  + b)SetArray(notes,chromatic,25);
}


void SetArray(int a[], int b[],int len)
{
  notes_len = len;
  bin_size = 1024/notes_len;
  for (int i =0; i < notes_len; i++)
  { 
    a[i] = b[i]; 
  }
}




//used to eliminate interference between PWM channels
void setPwmFrequency(int pin, int divisor) 
{
  byte mode;
  if(pin == 5 || pin == 6 || pin == 9 || pin == 10) 
  {
    switch(divisor) {
      case 1: mode = 0x01; break;
      case 8: mode = 0x02; break;
      case 64: mode = 0x03; break;
      case 256: mode = 0x04; break;
      case 1024: mode = 0x05; break;
      default: return;
    }
    if(pin == 5 || pin == 6) 
    {
      TCCR0B = TCCR0B & 0b11111000 | mode;
    } else 
    {
      TCCR1B = TCCR1B & 0b11111000 | mode;
    }
  } 
  else if(pin == 3 || pin == 11) 
  {
    switch(divisor) 
    {
      case 1: mode = 0x01; break;
      case 8: mode = 0x02; break;
      case 32: mode = 0x03; break;
      case 64: mode = 0x04; break;
      case 128: mode = 0x05; break;
      case 256: mode = 0x06; break;
      case 1024: mode = 0x7; break;
      default: return;
    }
    TCCR2B = TCCR2B & 0b11111000 | mode;
  }
}
