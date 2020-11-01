/*
 * File:   main.c
 * Author: Ilay
 *
 * Created on 31 октября 2020 г., 19:04
 */
// PIC18F4550 Configuration Bit Settings

// 'C' source line config statements

// CONFIG1L

// #pragma config statements should precede project file includes.
// Use project enums instead of #define for ON and OFF.
#include "main.h"
#include "string.h"

//VAR
unsigned char bt, tmp;

void __interrupt () INTERRUPT_InterruptManager(void);  //функция прерывания
void Uart_init();  //инициализация UART
void blink();      //Моргалка
void led_ini();    //Настройка ног светодиода
void led_on();     //Вклчение светодиода
void led_off();    // Выклчение свеодиода
void delay(int msek);     //функция задержки
void USART_Transmit(unsigned char tx_byte);  //функция передачи данных по уарт
void USART_Transmit_Arr(unsigned char *tx_buff,unsigned int tx_len);
void USART_Transmit_Str(char *str_buff);  //передача массива строк
void blink2(char x_bt);


//////////////////////////////////////////////
//void interrupt() my_isr(void)
void __interrupt () INTERRUPT_InterruptManager(void)
{
  if(RCIF)
  {
    if(FERR)  //ошика кадра
    {
      tmp = RCREG;
      return;
    }
    else if (OERR)  //переполнение
    {
      CREN = 0;      
      CREN = 1;
      return;
    }
    bt=RCREG;    //принимаем байт
    //PORTB=bt;
    blink2(bt);
  }
}
///////////////////////////////////////////
void Uart_init(){ //инициализация UART
    TRISC6 = 1; //USART (TX);
    TRISC7 = 1; //USART (RX);
    //Натройка TXSTA передатчика
    TX9=0; //8 bit режим
    TXEN=1; //включение передачи
    SYNC=0;  //асинхронный режим
    SENDB=0;
    BRGH=1;  //High baudrate
    TX9D=0;  //
    //Настройка RCSTA приемника
    SPEN=1;  //Serial port enable
    RX9=0;  //8 bit mode
    CREN=1;  //Continius Recieve bit enable
    //FERR=0;   //No framing error
    //OERR=0;   //Overrun Error bit
    RX9D=0;   //9th bit of Received Data
    
    RCIE=1;   //Разрешение прерываний от приемника
    GIE=1;     //Разрешение глоальных прерываний
    PEIE=1;    //Разрешение прерываний от переферии
    
    //
    BRG16=0;        //SPBRG only
    //Настройка скорости
    SPBRG=126;  //9600
    //SPBRG=64;   //19200
}
////////////////////////////////////////////
void delay(int msek){
    while(msek>0){
        __delay_ms(1);
        msek--;
    }
}
////////////////////////////////////////////
void led_ini(){
    TRISDbits.RD0=0;
}
void led_on(){
    PORTDbits.RD0=1;
}
void led_off(){
    PORTDbits.RD0=0;
}
void blink(){
    led_on();
    delay(300);
    led_off();
    delay(300);
}
/////////////////////////////////////////////
void USART_Transmit(unsigned char tx_byte){
    while(!TRMT);
        TXREG=tx_byte;
    
}
////////////////////////////////////////////
void USART_Transmit_Arr(unsigned char *tx_buff,unsigned int tx_len){
    unsigned int cnt=0;
    while(cnt<tx_len){
        USART_Transmit(tx_buff[cnt]);
        cnt++;
    }
}
/////////////////////////////////////////////
void USART_Transmit_Str(char *str_buff){
    unsigned int cnt=0;
    unsigned int tx_len = strlen(str_buff);
    while(cnt<tx_len){
        USART_Transmit(str_buff[cnt]);
        cnt++;
    }
}
/////////////////////////////////////////////
void blink2(char x_bt){
    unsigned short int time;
    time=100;
    while(x_bt>0){
        led_on();
        delay(time);
        led_off();
        delay(time);
        x_bt--;
    }
}
////////////////////////////////////////////



/////////////////////////////////////////////
void main(void) {
    char str1[15];
    int i;
    
    Uart_init();
    led_ini();
    while(1){
        
       
        
        
        
        /*
         for(i=0;i<256;i++){
        //USART_Transmit(i);
            // USART_Transmit_Arr("1234567890\r\n",12);
             //USART_Transmit_Str("1234567890\r\n");
             sprintf(str1,"String%03d\r\n",i);
             USART_Transmit_Str(str1);
             delay(105);
        }  
        */
  }
    
    
    
}
