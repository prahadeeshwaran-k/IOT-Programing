#define zerocross 2       //pin for the external interrupt (Input with Pullup)                         
#define MOSFET 1           //pin to trigger the MOSFET (Output)
#define potentiometer A3  //pin for the potentiometer (Analog Input)
int potvalue;             //variable to store the current potentiometer value
int oldpotvalue;          //variable to store the old potentiometer value
int setpotvalue;          //variable to store the set potentiometer value
bool zero = 0;            //variable as a status flag which shows whether a zero crossing point occured

void setup() {
  pinMode(zerocross, INPUT_PULLUP);
  pinMode(MOSFET, OUTPUT);
  pinMode(potentiometer, INPUT);
  digitalWrite(MOSFET, LOW);                  //pull the MOSFET pin at the beginning low so that the MOSFET is off
  TCCR0A = 0;                                 //clear timer0 register (TCCR0A)
  TCCR0A |= (1 << WGM01);                     //set the CTC mode for timer0 with OCRA as top
  TCCR0B = 0;                                 //clear timer0 register (TCCR0B)
  TCCR0B |= (1 << CS00) | (1 << CS02);        //set prescaler of timer0 to 1024
  TIMSK1 |= (1 << OCIE0B);                     //activate timer compare match interrupt for OCR0A and OCR0B
  attachInterrupt(0, zerocrossing, FALLING);  //activate external interrupt on pin 2 at a falling edge
  sei();                                      //activate interrupts
  potvalue = analogRead(potentiometer);       //read in potentiometer value and store it in potvalue
  oldpotvalue = potvalue;                     
  setpotvalue = potvalue;;
}

void zerocrossing() {                         //external interrupt, occurs after every zero crossing point
  OCR0B = map(setpotvalue, 0, 1023, 3, 70);   //set OCR0B value between 3 and 70 (0.384ms - 8.96ms) according to the potentiometer value
  TCNT0 = 0;                                  //clear timer0 counter
  zero = 1;                                   //set zero crossing point flag to 1
  digitalWrite(MOSFET, HIGH);
}

ISR(TIMER0_COMPB_vect) {                      //compare match interrupt for OCR0B
  if (zero == 1) {        
    digitalWrite(MOSFET, LOW);                //if a zero crossing occurred, deactivate the MOSFET
    zero = 0;                                 //set the zero crossing point flag to 0
  }
}

void loop() { 
  potvalue = analogRead(potentiometer);
  if ((potvalue > oldpotvalue) && ((potvalue - oldpotvalue) > 30)){
    oldpotvalue = potvalue;
    setpotvalue = potvalue;
  }
  if ((potvalue < oldpotvalue) && ((oldpotvalue - potvalue) > 30)){
    oldpotvalue = potvalue;
    setpotvalue = potvalue;                    //small function in the loop, read in the potentiometer value and only change the set potentiometer value for the timer if there is a bigger change (>30) in the read in value, then wait for a bit and repeat
  }
  delayMicroseconds(50000);
}
