//*****************************************************************************
/*
 * File:   main.c
 * Author: Pablo
 * Ejemplo de implementación de la comunicación SPI 
 * Código Maestro
 * Created on 10 de febrero de 2020, 03:32 PM
 */
//*****************************************************************************
//*****************************************************************************
// Palabra de configuración
//*****************************************************************************
// CONFIG1
#pragma config FOSC = INTRC_NOCLKOUT// Oscillator Selection bits (RCIO oscillator: I/O function on RA6/OSC2/CLKOUT pin, RC on RA7/OSC1/CLKIN)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled and can be enabled by SWDTEN bit of the WDTCON register)
#pragma config PWRTE = OFF      // Power-up Timer Enable bit (PWRT disabled)
#pragma config MCLRE = OFF      // RE3/MCLR pin function select bit (RE3/MCLR pin function is digital input, MCLR internally tied to VDD)
#pragma config CP = OFF         // Code Protection bit (Program memory code protection is disabled)
#pragma config CPD = OFF        // Data Code Protection bit (Data memory code protection is disabled)
#pragma config BOREN = OFF      // Brown Out Reset Selection bits (BOR disabled)
#pragma config IESO = OFF       // Internal External Switchover bit (Internal/External Switchover mode is disabled)
#pragma config FCMEN = OFF      // Fail-Safe Clock Monitor Enabled bit (Fail-Safe Clock Monitor is disabled)
#pragma config LVP = OFF        // Low Voltage Programming Enable bit (RB3 pin has digital I/O, HV on MCLR must be used for programming)

// CONFIG2
#pragma config BOR4V = BOR40V   // Brown-out Reset Selection bit (Brown-out Reset set to 4.0V)
#pragma config WRT = OFF        // Flash Program Memory Self Write Enable bits (Write protection off)

// #pragma config statements should precede project file includes.
// Use project enums instead of #define for ON and OFF.

//*****************************************************************************
// Definición e importación de librerías
//*****************************************************************************
#include <xc.h>
#include <stdint.h>
#include "SPI.h"
#include "SERIAL.h"
#include "ADC.h"
//*****************************************************************************
// Definición de variables
//*****************************************************************************
#define _XTAL_FREQ 4000000
char POT1,POT2=0;
int Channel =0;
float Sensor1=0;
float Sensor2=0; 
float Sensor12=0;
float Sensor22=0; 
int   entero1=0;
int entero2=0; 
int decimal1=0;
int decimal2=0; 
float DECIMAL1=0;
float DECIMAL2=0; 
//*****************************************************************************
// Definición de funciones para que se puedan colocar después del main de lo 
// contrario hay que colocarlos todas las funciones antes del main
//*****************************************************************************
void setup(void);
  
//*****************************************************************************
// Código Principal
//*****************************************************************************
void __interrupt() ISR(){
    
    
    if (RCIF==1){
        PORTB = RCREG;
    }
}
void main(void) {
    

    setup();
    //*************************************************************************
    // Loop infinito
    //*************************************************************************
    while(1){
       
        spiWrite(1);
        POT1 = spiRead();

        __delay_ms(10);

        spiWrite(2);
        POT2 = spiRead();

        __delay_ms(10);
       
//        if(PORTAbits.RA7){
//            PORTB=POT1;
//        }
//        else{
//            PORTB=POT2;
//        }
//        Sensor12=(POT1*5)/254;
//        Sensor22=(POT2*5)/254;

        Sensor12= (float)(POT1*5)/255;
        Sensor22= (float)(POT2*5)/255;
        
        entero1=(int)Sensor12;
        entero2=(int)Sensor22;
        DECIMAL1= (float) (Sensor12-entero1)*100;
        decimal1=(int) DECIMAL1;
        DECIMAL2= (float) (Sensor22-entero2)*100;
        decimal2=(int) DECIMAL2;
        
//        entero1=Sensor12;
//        entero2=Sensor22;
//        DECIMAL1=(float)(Sensor12-entero1)*100;
//        decimal1=(int) DECIMAL1;
//        DECIMAL2=(float)(Sensor22-entero2)*100;
//        decimal2=(int) DECIMAL2;

        enviarSerial(111);
        enviarSerial(entero1);
        enviarSerial(decimal1);
        enviarSerial(entero2);
        enviarSerial(decimal2);
    }
}
//*****************************************************************************
// Función de Inicialización
//*****************************************************************************
void setup(void){
    
    configSerial(9600);
    TRISC=0b000010000;
    
    ANSEL = 0;
    ANSELH = 0;
    TRISC2 = 0;
    TRISB = 0;
    TRISD = 0;
    PORTB = 0;
    PORTD = 0;
    TRISAbits.TRISA7= 1;
    
    spiInit(SPI_MASTER_OSC_DIV4, SPI_DATA_SAMPLE_MIDDLE, SPI_CLOCK_IDLE_LOW, SPI_IDLE_2_ACTIVE);

    
    
}