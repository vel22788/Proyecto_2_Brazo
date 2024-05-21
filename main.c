/*
 * main.c
 *
 * Created: 4/26/2024 3:19:03 PM
 *  Author: angel
 */ 

#define F_CPU 16000000

#include <xc.h>
#include <util/delay.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/eeprom.h>
#include <stdio.h>


#include "PWM0/PMW0.h"
#include "PWM2/PWM2.h"
#include "ADC/ADC.h"
#include "UART/UART.h"
#include "Timer1/Timer1.h"

volatile uint8_t modo=1;
volatile uint8_t espacio_memoria=1;
volatile uint8_t valor[3][4];
volatile uint8_t valor_l;
volatile uint8_t bandera=0;
volatile uint8_t pwm_editar;
volatile uint8_t espacio;
	

int CharToInt(char num){
	return num - '0';
}

int unir(int n1, int n2, int n3){
	return n1*100+ n2*10 + n3;
}

void init_Pines(void){
	//Entradas:
		//Botones:
			//Cambiar entre modos
			DDRB &= ~(1 << DDB4); 
			PORTB |= (1 << PORTB4);
			 //Cambiar localidad
			DDRD &= ~(1 << DDD4);
			PORTD |= (1 << PORTD4);
			//Guardar localidad
			 DDRC &= ~(1 << DDC0);
			 PORTC |= (1 << PORTC0);
		//POT
			DDRC &= ~(1 << DDC1) & ~(1 << DDC2) & ~(1 << DDC3) & ~(1 << DDC4);
			PORTC |= (1 << PORTC1)|(1 << PORTC2)|(1 << PORTC3)|(1 << PORTC4);
	//Salidas:
		//Leds Modo:
			DDRB |= (1 << DDB0)|(1 << DDB1); //PB0 LED_MODO0 |  PB1 LED_MODO1 
		//Leds espacio en memoria:
			DDRB |= (1 << DDB2);		//DDB2 LEDG_1 | DDD7 LED_G2 | DDD2 LED_G3
			DDRD |= (1 << DDD2)|(1 << DDD7);		
	//Interrupciones:
		//Interrupciones por botones
		PCICR |=  (1 << PCIE2) | (1 << PCIE1)| (1 << PCIE0); 
		PCMSK0 |= (1 << PCINT4); // PB4
		PCMSK2 |= (1 << PCINT20); // PD4
		PCMSK1 |= (1 << PCINT8); // PC0
}

void f_memoria(void){
	if (espacio_memoria==1)
	{
		PORTB |= (1 << PINB2);
		PORTD &= ~(1 << PIND7) & ~(1 << PIND2) ;
		
	}else if (espacio_memoria==2)
	{
		PORTD |= (1 << PIND7);
		PORTD &= ~(1 << PIND2);
		PORTB &= ~(1 << PINB2) ;
		
	}else if (espacio_memoria==3)
	{
		PORTD |= (1 << PIND2);
		PORTD &= ~(1 << PIND7);
		PORTB &= ~(1 << PINB2) ;
	}else if (espacio_memoria==4)
	{
		PORTD |= (1 << PIND2);
		PORTD |= (1 << PIND7);
		PORTB |= (1 << PINB2) ;
	}
}

void guardar(uint8_t espacio){
	if (espacio==1){
		eeprom_write_byte((uint8_t*)0, OCR0A);
		eeprom_write_byte((uint8_t*)1, OCR0B);
		eeprom_write_byte((uint8_t*)2, OCR2A);
		eeprom_write_byte((uint8_t*)3, OCR2B);
		
		PORTD &= ~(1 << PIND7) & ~(1 << PIND2) ;
		PORTB &= ~(1 << PINB2) ;
		_delay_ms(500);
		f_memoria();
		
	}
	if (espacio==2){
		eeprom_write_byte((uint8_t*)4, OCR0A);
		eeprom_write_byte((uint8_t*)5, OCR0B);
		eeprom_write_byte((uint8_t*)6, OCR2A);
		eeprom_write_byte((uint8_t*)7, OCR2B);
		
		PORTD &= ~(1 << PIND7) & ~(1 << PIND2) ;
		PORTB &= ~(1 << PINB2) ;
		_delay_ms(500);
		f_memoria();
	}
	if (espacio==3){
		eeprom_write_byte((uint8_t*)8, OCR0A);
		eeprom_write_byte((uint8_t*)9, OCR0B);
		eeprom_write_byte((uint8_t*)10, OCR2A);
		eeprom_write_byte((uint8_t*)11, OCR2B);
		
		PORTD &= ~(1 << PIND7) & ~(1 << PIND2) ;
		PORTB &= ~(1 << PINB2) ;
		_delay_ms(500);
		f_memoria();
	}
	if (espacio==4){
		eeprom_write_byte((uint8_t*)12, OCR0A);
		eeprom_write_byte((uint8_t*)13, OCR0B);
		eeprom_write_byte((uint8_t*)14, OCR2A);
		eeprom_write_byte((uint8_t*)15, OCR2B);
		
		PORTD &= ~(1 << PIND7) & ~(1 << PIND2) ;
		PORTB &= ~(1 << PINB2) ;
		_delay_ms(500);
		f_memoria();
	}
}

void cargar(uint8_t memoria){
	if (memoria==1){
		valor_l=eeprom_read_byte((uint8_t*)0);
		OCR0A= valor_l;
		valor_l=eeprom_read_byte((uint8_t*)1);
		OCR0B= valor_l;
		valor_l=eeprom_read_byte((uint8_t*)2);
		OCR2A= valor_l;
		valor_l=eeprom_read_byte((uint8_t*)3);
		OCR2B= valor_l;
	}
	if (memoria==2){
		valor_l=eeprom_read_byte((uint8_t*)4);
		OCR0A= valor_l;
		valor_l=eeprom_read_byte((uint8_t*)5);
		OCR0B= valor_l;
		valor_l=eeprom_read_byte((uint8_t*)6);
		OCR2A= valor_l;
		valor_l=eeprom_read_byte((uint8_t*)7);
		OCR2B= valor_l;
	}
	if (memoria==3){
		valor_l=eeprom_read_byte((uint8_t*)8);
		OCR0A= valor_l;
		valor_l=eeprom_read_byte((uint8_t*)9);
		OCR0B= valor_l;
		valor_l=eeprom_read_byte((uint8_t*)10);
		OCR2A= valor_l;
		valor_l=eeprom_read_byte((uint8_t*)11);
		OCR2B= valor_l;
	}
	if (memoria==4){
			valor_l=eeprom_read_byte((uint8_t*)12);
			OCR0A= valor_l;
			valor_l=eeprom_read_byte((uint8_t*)13);
			OCR0B= valor_l;
			valor_l=eeprom_read_byte((uint8_t*)14);
			OCR2A= valor_l;
			valor_l=eeprom_read_byte((uint8_t*)15);
			OCR2B= valor_l;
		}
	}

void f_modo(void){
	uint8_t valorADC;
	
	long temp;
	uint8_t temp_m;
	char valorOCR0A[10];
	char valorOCR0B[10];
	char valorOCR2A[10];
	char valorOCR2B[10];
	char valorM1[10];
	char valorM2[10];
	char valorM3[10];
	char valorM4[10];
	
	
	char recibido1;
	char recibido2;
	char recibido3;
	
	int n1;
	int n2;
	int n3;
	
	int num;
	
	long valorPWM;
	
	if (modo==1)
	{
		bandera=0;
		PORTB |= (1 << PINB1);
		PORTB &= ~(1 << PINB0);
		f_memoria();
		
		//9,7% maximo: OCR0A 23, 2,3% minimo: OCR0A 5 GARRA
		//LEER ADC1 Y CAMBIAR DUTYCYCLE0A
		valorADC=readADC(1);
		valorPWM=(map(valorADC,0,255,5,23));
		valorADC=valorPWM;
		duty_cycleA(valorADC);
		
		//9.4% maximo: OCR0A 23, 3,5% minimo: OCR0B 8 PARTE B
		//LEER ADC2 Y CAMBIAR DUTYCYCLE0B
		valorADC=readADC(2);
		valorPWM=(map(valorADC,0,255,8,23));
		valorADC=valorPWM;
		duty_cycleB(valorADC);
		
		//10% maximo: OCR2A 24, 2,3% minimo: OCR2A 5 PARTE A
		//LEER ADC3 Y CAMBIAR DUTYCYCLE2A
		valorADC=readADC(3);
		valorPWM=(map(valorADC,0,255,10,22));
		valorADC=valorPWM;
		duty_cycle2A(valorADC);
		
		//15% maximo: OCR2B 37, 2,3% minimo: OCR2B 5 PARTE BASE
		//LEER ADC4 Y CAMBIAR DUTYCYCLE2B
		valorADC=readADC(4);
		valorPWM=(map(valorADC,0,255,5,37));
		valorADC=valorPWM;
		duty_cycle2B(valorADC);
		
		
		}else if (modo==2){
		
		bandera=0;
		PORTB |= (1 << PINB0);
		PORTB &= ~(1 << PINB1);
		f_memoria();
		
		}else if (modo==3){
			
		PORTB |= (1 << PINB1)|(1 << PINB0);
		
		//PORTD &= ~(1 << PIND7) & ~(1 << PIND2) ;
		//PORTB &= ~(1 << PINB2) ;
		
		if (bandera==0){
			
			writeUART_car('S');
			
			temp = (map(OCR0A,5,23,000,255));
			sprintf(valorOCR0A,"%03ld",temp);
			
			temp = (map(OCR0B,8,23,000,255));
			sprintf(valorOCR0B,"%03ld",temp);
			
			temp = (map(OCR2A,10,22,000,255));
			sprintf(valorOCR2A,"%03ld",temp);
			
			temp = (map(OCR2B,5,37,000,255));
			sprintf(valorOCR2B,"%03ld",temp);
			
			
			writeUART_Text(valorOCR0A);
			writeUART_Text(valorOCR0B);
			writeUART_Text(valorOCR2A);
			writeUART_Text(valorOCR2B);
			
			
			temp_m=eeprom_read_byte((uint8_t*)0);
			temp = (map(temp_m,5,23,000,255));
			sprintf(valorM1,"%03ld",temp);
			
			temp_m=eeprom_read_byte((uint8_t*)1);
			temp = (map(temp_m,8,23,000,255));
			sprintf(valorM2,"%03ld",temp);
			
			
			temp_m=eeprom_read_byte((uint8_t*)2);
			temp = (map(temp_m,10,22,000,255));
			sprintf(valorM3,"%03ld",temp);
			
			temp_m=eeprom_read_byte((uint8_t*)3);
			temp = (map(temp_m,5,37,000,255));
			sprintf(valorM4,"%03ld",temp);
			
			writeUART_Text(valorM1);
			writeUART_Text(valorM2);
			writeUART_Text(valorM3);
			writeUART_Text(valorM4);

			temp_m=eeprom_read_byte((uint8_t*)4);
			temp = (map(temp_m,5,23,000,255));
			sprintf(valorM1,"%03ld",temp);
			
			temp_m=eeprom_read_byte((uint8_t*)5);
			temp = (map(temp_m,8,23,000,255));
			sprintf(valorM2,"%03ld",temp);
			
			
			temp_m=eeprom_read_byte((uint8_t*)6);
			temp = (map(temp_m,10,22,000,255));
			sprintf(valorM3,"%03ld",temp);
			
			temp_m=eeprom_read_byte((uint8_t*)7);
			temp = (map(temp_m,5,37,000,255));
			sprintf(valorM4,"%03ld",temp);
			
			writeUART_Text(valorM1);
			writeUART_Text(valorM2);
			writeUART_Text(valorM3);
			writeUART_Text(valorM4);
			
			temp_m=eeprom_read_byte((uint8_t*)8);
			temp = (map(temp_m,5,23,000,255));
			sprintf(valorM1,"%03ld",temp);
			
			temp_m=eeprom_read_byte((uint8_t*)9);
			temp = (map(temp_m,8,23,000,255));
			sprintf(valorM2,"%03ld",temp);
			
			
			temp_m=eeprom_read_byte((uint8_t*)10);
			temp = (map(temp_m,10,22,000,255));
			sprintf(valorM3,"%03ld",temp);
			
			temp_m=eeprom_read_byte((uint8_t*)11);
			temp = (map(temp_m,5,37,000,255));
			sprintf(valorM4,"%03ld",temp);
			
			writeUART_Text(valorM1);
			writeUART_Text(valorM2);
			writeUART_Text(valorM3);
			writeUART_Text(valorM4);
			
			temp_m=eeprom_read_byte((uint8_t*)12);
			temp = (map(temp_m,5,23,000,255));
			sprintf(valorM1,"%03ld",temp);
			
			temp_m=eeprom_read_byte((uint8_t*)13);
			temp = (map(temp_m,8,23,000,255));
			sprintf(valorM2,"%03ld",temp);
			
			
			temp_m=eeprom_read_byte((uint8_t*)14);
			temp = (map(temp_m,10,22,000,255));
			sprintf(valorM3,"%03ld",temp);
			
			temp_m=eeprom_read_byte((uint8_t*)15);
			temp = (map(temp_m,5,37,000,255));
			sprintf(valorM4,"%03ld",temp);
			
			writeUART_Text(valorM1);
			writeUART_Text(valorM2);
			writeUART_Text(valorM3);
			writeUART_Text(valorM4);
				
			
			
			bandera=1;
			}
			
		if (bandera==1)
		{
			writeUART_car('P');
			pwm_editar = receivedChar();
			
			if (pwm_editar==0b0110100) //4
			{
				recibido1=receivedChar();
				recibido2=receivedChar();
				recibido3=receivedChar();
				
				n1=CharToInt(recibido1);
				n2=CharToInt(recibido2);
				n3=CharToInt(recibido3);
				
				num= unir(n1,n2,n3);
				
				valorPWM=(map(num,0,255,5,23));
				valorADC=valorPWM;
				duty_cycleA(valorADC);
			}
			
			if (pwm_editar==0b110011) //3
			{
			recibido1=receivedChar();
			recibido2=receivedChar();
			recibido3=receivedChar();
			
			n1=CharToInt(recibido1);
			n2=CharToInt(recibido2);
			n3=CharToInt(recibido3);
			
			num= unir(n1,n2,n3);
			
			valorPWM=(map(num,0,255,8,23));
			valorADC=valorPWM;
			duty_cycleB(valorADC);
			}
			
			if (pwm_editar==0b0110010) //2
			{
			recibido1=receivedChar();
			recibido2=receivedChar();
			recibido3=receivedChar();
			
			n1=CharToInt(recibido1);
			n2=CharToInt(recibido2);
			n3=CharToInt(recibido3);
			
			num= unir(n1,n2,n3);
			
			valorPWM=(map(num,0,255,10,22));
			valorADC=valorPWM;
			duty_cycle2A(valorADC);
			}
			
			if (pwm_editar==0b0110001) //1
			{
				recibido1=receivedChar();
				recibido2=receivedChar();
				recibido3=receivedChar();
				
				n1=CharToInt(recibido1);
				n2=CharToInt(recibido2);
				n3=CharToInt(recibido3);
				
				num= unir(n1,n2,n3);
				
				valorPWM=(map(num,0,255,5,37));
				valorADC=valorPWM;
				duty_cycle2B(valorADC);
			}
			if (pwm_editar==0b1000111) //G
			{
				espacio=receivedChar();
				if (espacio==0b0110001){
					espacio_memoria=1;
				}
				if (espacio==0b0110010)
				{
					espacio_memoria=2;
				}
				if (espacio==0b110011)
				{
					espacio_memoria=3;
				}
				if (espacio==0b0110100)
				{
					espacio_memoria=4;
				}
				f_memoria();
				_delay_ms(1000);
				guardar(espacio_memoria);
				
			}
			if (pwm_editar==0b01000011){ //C
				espacio=receivedChar();
				if (espacio==0b0110001){
					espacio_memoria=1;
				}
				if (espacio==0b0110010)
				{
					espacio_memoria=2;
				}
				if (espacio==0b110011)
				{
					espacio_memoria=3;
				}
				if (espacio==0b0110100)
				{
					espacio_memoria=4;
				}
				f_memoria();
				_delay_ms(1000);
				cargar(espacio_memoria);
				temp = (map(OCR0A,5,23,000,255));
				sprintf(valorOCR0A,"%03ld",temp);
				
				temp = (map(OCR0B,8,23,000,255));
				sprintf(valorOCR0B,"%03ld",temp);
				
				temp = (map(OCR2A,10,22,000,255));
				sprintf(valorOCR2A,"%03ld",temp);
				
				temp = (map(OCR2B,5,37,000,255));
				sprintf(valorOCR2B,"%03ld",temp);
				
				
				writeUART_Text(valorOCR0A);
				writeUART_Text(valorOCR0B);
				writeUART_Text(valorOCR2A);
				writeUART_Text(valorOCR2B);
				
				
				
			}
			if(pwm_editar==0b01010001){ //Q
				modo=1;
			}
			if(pwm_editar==0b110000){
			}

		}

	}
}

// Rutina de interrupción para el botón PB5
ISR(PCINT0_vect) {
	_delay_ms(80);
	if (!(PINB & (1 << PINB4))) {
		if (modo==3){
			modo=1;
		} else{
			modo++;
		}
	}
}

// Rutina de interrupción para el botón PD4
ISR(PCINT2_vect) {
	_delay_ms(20);
	if (!(PIND & (1 << PIND4))) {
		if ((modo==1)|(modo==2)){
			if (espacio_memoria==4){
				espacio_memoria=1;
			}else{
				espacio_memoria++;
			}
		}
	}
}

// Rutina de interrupción para el botón PC0
ISR(PCINT1_vect) {
	_delay_ms(20);
	if (!(PINC & (1 << PINC0))) {
		if (modo==1)
		{
			if (espacio_memoria==1){
				eeprom_write_byte((uint8_t*)0, OCR0A);
				eeprom_write_byte((uint8_t*)1, OCR0B);
				eeprom_write_byte((uint8_t*)2, OCR2A);
				eeprom_write_byte((uint8_t*)3, OCR2B);
				
				PORTD &= ~(1 << PIND7) & ~(1 << PIND2) ;
				PORTB &= ~(1 << PINB2) ;
				_delay_ms(500);
				f_memoria();
				
			}
			if (espacio_memoria==2){
				eeprom_write_byte((uint8_t*)4, OCR0A);
				eeprom_write_byte((uint8_t*)5, OCR0B);
				eeprom_write_byte((uint8_t*)6, OCR2A);
				eeprom_write_byte((uint8_t*)7, OCR2B);
				
				PORTD &= ~(1 << PIND7) & ~(1 << PIND2) ;
				PORTB &= ~(1 << PINB2) ;
				_delay_ms(500);
				f_memoria();
			}
			if (espacio_memoria==3){
				eeprom_write_byte((uint8_t*)8, OCR0A);
				eeprom_write_byte((uint8_t*)9, OCR0B);
				eeprom_write_byte((uint8_t*)10, OCR2A);
				eeprom_write_byte((uint8_t*)11, OCR2B);
				
				PORTD &= ~(1 << PIND7) & ~(1 << PIND2) ;
				PORTB &= ~(1 << PINB2) ;
				_delay_ms(500);
				f_memoria();
			}
			if (espacio_memoria==4){
				eeprom_write_byte((uint8_t*)12, OCR0A);
				eeprom_write_byte((uint8_t*)13, OCR0B);
				eeprom_write_byte((uint8_t*)14, OCR2A);
				eeprom_write_byte((uint8_t*)15, OCR2B);
				
				PORTD &= ~(1 << PIND7) & ~(1 << PIND2) ;
				PORTB &= ~(1 << PINB2) ;
				_delay_ms(500);
				f_memoria();
			}
		}else if (modo==2)
		{
			if (espacio_memoria==1){
				valor_l=eeprom_read_byte((uint8_t*)0);
				OCR0A= valor_l;
				valor_l=eeprom_read_byte((uint8_t*)1);
				OCR0B= valor_l;
				valor_l=eeprom_read_byte((uint8_t*)2);
				OCR2A= valor_l;
				valor_l=eeprom_read_byte((uint8_t*)3);
				OCR2B= valor_l;
			}
			if (espacio_memoria==2){
				valor_l=eeprom_read_byte((uint8_t*)4);
				OCR0A= valor_l;
				valor_l=eeprom_read_byte((uint8_t*)5);
				OCR0B= valor_l;
				valor_l=eeprom_read_byte((uint8_t*)6);
				OCR2A= valor_l;
				valor_l=eeprom_read_byte((uint8_t*)7);
				OCR2B= valor_l;
			}
			if (espacio_memoria==3){
				valor_l=eeprom_read_byte((uint8_t*)8);
				OCR0A= valor_l;
				valor_l=eeprom_read_byte((uint8_t*)9);
				OCR0B= valor_l;
				valor_l=eeprom_read_byte((uint8_t*)10);
				OCR2A= valor_l;
				valor_l=eeprom_read_byte((uint8_t*)11);
				OCR2B= valor_l;
			}
			if (espacio_memoria==4){
				valor_l=eeprom_read_byte((uint8_t*)12);
				OCR0A= valor_l;
				valor_l=eeprom_read_byte((uint8_t*)13);
				OCR0B= valor_l;
				valor_l=eeprom_read_byte((uint8_t*)14);
				OCR2A= valor_l;
				valor_l=eeprom_read_byte((uint8_t*)15);
				OCR2B= valor_l;
			}
			}
		}
			
	}

int main(void)
{
	init_Pines();
	initUART(9600,0,0,0,0,1,8,103);
	
	sei();
	
	init_ADC(0,0,128);
	
	init_PMW0A(0,0,1024);
	init_PMW0B(0);
	
	init_PMW2A(0,0,1024);
	init_PMW2B(0);
	
	duty_cycleA(38);
	duty_cycle2A(38);
	
	duty_cycleB(5);
	duty_cycle2B(5);
	
    while(1)
    {
       f_modo();
	}   
}