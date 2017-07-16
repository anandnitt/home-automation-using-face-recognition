#include<avr/io.h>
#include<avr/interrupt.h>

long int milli=0,ledmonitor=0;
char ch;
int flag=0;
int flag1=0;
int stops=0;
int timeover=0;
void usart_int(void)
{
  UCSR0B=(1<< RXEN0)|(1<< TXEN0);//TRANSMIT AND RECEIVE ENABLE
  UCSR0C=(1<<UCSZ01)|(1<<UCSZ00);//ASYNCHRONOUS, 8 BIT TRANSFER
  UBRR0L= 0x67 ; //BAUD RATE 9600
  
}

int main()
{sei();
  //usart_int();
  Serial.begin(9600);
  DDRB=0xFF;
  PORTD=0x00;
 EIMSK=0b00000011;
 EICRA=0b00001111;
   OCR1A=250;
    TCCR1A |= (1<<COM1A1)|(1<<WGM10);
   TCCR1B=(1<<WGM12)|(1<<CS11)|(1<<CS10);
    TIMSK1|=(1<<OCIE1A);
    int flag=0;
  while(1)
  {
    
    PORTB&=~(1<<1);
   // while(UCSR0A!= (UCSR0A|(1<<RXC0)));
     ch=UDR0;
     //Serial.println("l");
     
     Serial.println(ch);
     if(ch=='l')
     {PORTB|=(1<<0);
     
     }
     else if(ch=='n')
     {
      PORTB&=~(1<<0);
      }
      if(ch=='b')
     
    {  PORTB|=(1<<2);
    if(flag1==0)
  ledmonitor=milli;
  flag1=1;
  
    }
     
     else if(ch=='t')
    { PORTB&=~(1<<2);
    flag1=0;
    }
    
    
    
    
    }
    
  }

   ISR(TIMER1_COMPA_vect)
{
  
  milli++;
  if(flag1==1)
  {
    if(milli==ledmonitor+6000)
    {PORTB&=~(1<<2);
    milli=0;
    flag1=0;
    
    }
    }
      
  }

ISR(INT0_vect)
  {
    
    PORTB=0x00;
    stops++;
    }

 ISR(INT1_vect)
 {
  PORTB|=(1<<1);
  }


