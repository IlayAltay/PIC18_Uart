/*
 * File:   my_led.c
 * Author: Ilay
 *
 * Created on 11 но€бр€ 2020 г., 20:18
 */


#include <xc.h>
#define _XTAL_FREQ 20000000
/////////////////////////////////////////////
void delay(int msek){
    while(msek>0){
        __delay_ms(1);
        msek--;
    }
}
////////////////////////////////////////////
void led_ini(){
    TRISDbits.RD3=0;
}
void led_on(){
    PORTDbits.RD3=1;
}
void led_off(){
    PORTDbits.RD3=0;
}
void blink(){
    led_on();
    delay(300);
    led_off();
    delay(300);
}
void blink2(){
    led_on();
    delay(150);
    led_off();
    delay(150);
}
//////////////////////////////////////
