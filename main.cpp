#include <avr/io.h>
#include <util/delay.h>

#define setbit(register,bit) (register|=(1<<bit))
#define clearbit(register,bit) (register &= ~(1<<bit))


void eeprom_write(char data){
    if(EECR & (1<<EEPE)){}
    EEAR = 0X00;
    EEDR = data;
    setbit(EECR,EEMPE);
    setbit(EECR,EEPE);

}

char eeprom_read(){
    if(EECR & (1<<EEPE)){}
    EEAR = 0X00;
    EECR |= (1<<EERE);
    return EEDR;
}

void uart_init(){
    UCSR0B |= (1<<TXEN0);
    UCSR0C |= (1<<UCSZ00)|(1<<UCSZ01);
    UBRR0L = 103;
    UBRR0H = 0;
}

void uart_tx(char info){
    while(!(UCSR0A & (1<<UDRE0))){}
    UDR0=info;
}

int main(void){

    uart_init();
    eeprom_write('4');




    while(1){
    
        char data = eeprom_read();
        uart_tx(data);

    }
}