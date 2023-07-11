void setup() {
  // put your setup code here, to run once:
int raw_vaule = 0,k;
double adc_vaule = 0.0;
DDRA = 0X00;//Make all Analog pin to INPUT
PORTA = 0X00;//Make  all Analog pin to 0
ADMUX =0X06;//01100000 Select VRS2 & ADLAR =1
ADCSRA =0x87//Enable the ADC & Fixing The Division Factor to 128
}

void loop() {
  // put your main code here, to run repeatedly:

}
