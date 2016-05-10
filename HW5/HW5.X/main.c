#include<xc.h>           // processor SFR definitions
#include<sys/attribs.h>  // __ISR macro
#include "IMU.h"
#include "I2C.h"
#include "LCD.h"
#include <math.h>

// DEVCFG0
#pragma config DEBUG = 0x1 // no debugging
#pragma config JTAGEN = 0 // no jtag
#pragma config ICESEL = 11 // use PGED1 and PGEC1
#pragma config PWP = 111111111 // no write protect
#pragma config BWP = 0 // no boot write protect
#pragma config CP = 1 // no code protect

// DEVCFG1
#pragma config FNOSC = 011 // use primary oscillator with pll
#pragma config FSOSCEN = 0 // turn off secondary oscillator
#pragma config IESO = 0 // no switching clocks
#pragma config POSCMOD = 10 // high speed crystal mode
#pragma config OSCIOFNC = 1 // free up secondary osc pins
#pragma config FPBDIV = 00 // divide CPU freq by 1 for peripheral bus clock
#pragma config FCKSM = 0x1 // do not enable clock switch
#pragma config WDTPS = 00000 // slowest wdt
#pragma config WINDIS = 1 // no wdt window
#pragma config FWDTEN = 0 // wdt off by default
#pragma config FWDTWINSZ = 11 // wdt window at 25%

// DEVCFG2 - get the CPU clock to 48MHz
#pragma config FPLLIDIV = 001 // divide input clock to be in range 4-5MHz
#pragma config FPLLMUL = 111 // multiply clock after FPLLIDIV
#pragma config FPLLODIV = 001 // divide clock after FPLLMUL to get 48MHz
#pragma config UPLLIDIV = 001 // divider for the 8MHz input clock, then multiply
    //by 12 to get 48MHz for USB
#pragma config UPLLEN = 0 // USB clock on

// DEVCFG3
#pragma config USERID = 0xbebe // some 16bit userid, doesn't matter what
#pragma config PMDL1WAY = 0 // allow multiple reconfigurations
#pragma config IOL1WAY = 0 // allow multiple reconfigurations
#pragma config FUSBIDIO = 1 // USB pins controlled by USB module
#pragma config FVBUSONIO = 1 // USB BUSON controlled by USB module


int main() {

    __builtin_disable_interrupts();

    // set the CP0 CONFIG register to indicate that kseg0 is cacheable (0x3)
    __builtin_mtc0(_CP0_CONFIG, _CP0_CONFIG_SELECT, 0xa4210583);

    // 0 data RAM access wait states
    BMXCONbits.BMXWSDRM = 0x0;

    // enable multi vector interrupts
    INTCONbits.MVEC = 0x1;

    // disable JTAG to get pins back
    DDPCONbits.JTAGEN = 0;
    
    TRISAbits.TRISA4 = 0;
    LATAbits.LATA4 = 1;
    TRISBbits.TRISB4 = 1;
    
    __builtin_enable_interrupts();
    
    SPI1_init();
    LCD_init();
    
//    static unsigned char data[14]; 
//    static short short_data[7];
//    
//    int i=0;
//    for(i=0; i<14; i++) {
//        data[i] = 0x00;
//    }
//    for(i=0; i<7; i++) {
//        short_data[i] = 0x0000;
//    }
    
    while(1) {
        
//        _CP0_SET_COUNT(0);  // set system clock to zero
//        while(_CP0_GET_COUNT() < 24000) { // wait 1ms
//        ; }
//        
//        readIMU(0b00100000, data, 14);
//        int i;
//        for(i=0; i<7; i++) {
//            short_data[i] = (data[2*i+1] << 8 | data[2*i]);
//        }
//        OC1RS = (int)((((float)short_data[4]*2 + 32767.0)/65535.0)*(6000));
//        OC2RS = (int)((((float)short_data[5]*2 + 32767.0)/65535.0)*(6000)); 
        
        LCD_clearScreen(GREEN);
        
        char string[25];
        int num = 1337;
        sprintf(string, "Hello World %d!", num);
        LCD_drawString(28,32,string);
        
        _CP0_SET_COUNT(0);  // set system clock to zero
        while(_CP0_GET_COUNT() < 24000*10000) { // wait 10s
        ; }
       
    }
    
}