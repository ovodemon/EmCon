// Lab 1
// ENGR-2350
// Name: Yijia Zhou, Zhuokai Wang
// RIN: 661995479, 66204681

#include "engr2350_msp432.h"

void GPIOInit();
void TestIO();
void ControlSystem();

uint8_t LEDL = 0; // Two variables to store the state of
uint8_t LEDR = 0;// the LEDs
uint8_t ss1 = 0;
uint8_t ss2 = 0;
uint8_t bmp0 = 0;
uint8_t bmp5 = 0;
uint8_t ctr = 0;
int main(void)
{

    SysInit();
    GPIOInit();

    printf("\r\n\n"
           "***********\r\n"
           "Lab 1 Start\r\n"
           "***********\r\n");

    while(1){
        //TestIO();
        printf("turn = %u\r\n",ctr);
        ControlSystem();
        ctr += 1;

    }
}

void GPIOInit(){
    P2DIR &= ~0x08;
    P3DIR &= ~0x04;
    P2DIR |= 0x30;
    P3DIR |= 0xC0;
    P4DIR &= ~0x81;
    P5DIR |= 0x30;
    P8DIR |= 0x21;
    GPIO_setAsInputPinWithPullUpResistor(GPIO_PORT_P4,GPIO_PIN7);
    GPIO_setAsInputPinWithPullUpResistor(GPIO_PORT_P4,GPIO_PIN0);
}



void TestIO(){
    // Add printf statement(s) for testing inputs

    // Example code for testing outputs
    while(1){
        uint8_t cmd = getchar();

        if(cmd == 'a'){
            GPIO_setOutputHighOnPin(GPIO_PORT_P8,GPIO_PIN0);// Turn LEDL On
            printf("Turn LEDL on\r\n");
        }else if(cmd == 'z'){
            GPIO_setOutputLowOnPin(GPIO_PORT_P8,GPIO_PIN0);// Turn LEDL Off
            printf("Turn LEDL off\r\n");
        }else if(cmd == 's'){
            GPIO_setOutputHighOnPin(GPIO_PORT_P8,GPIO_PIN5);// Turn LEDR On
            printf("Turn LEDR on\r\n");
        }else if(cmd == 'x'){
            GPIO_setOutputLowOnPin(GPIO_PORT_P8,GPIO_PIN5);// Turn LEDR Off
            printf("Turn LEDR off\r\n");
        }else if(cmd == 'q'){
            GPIO_setOutputHighOnPin(GPIO_PORT_P2,GPIO_PIN4);// Turn BiLED Red
            GPIO_setOutputLowOnPin(GPIO_PORT_P2,GPIO_PIN5);
            printf("BiLED Red\r\n");
        }else if(cmd == 'w'){
            GPIO_setOutputLowOnPin(GPIO_PORT_P2,GPIO_PIN4|GPIO_PIN5);// Turn BiLED off
            printf("BiLED off\r\n");
        }else if(cmd == 'e'){
            GPIO_setOutputHighOnPin(GPIO_PORT_P2,GPIO_PIN5);// Turn BiLED Green
            GPIO_setOutputLowOnPin(GPIO_PORT_P2,GPIO_PIN4);
            printf("BiLED Green\r\n");
        }else if(cmd == 'd'){
            GPIO_setOutputHighOnPin(GPIO_PORT_P3,GPIO_PIN7);// Turn Left Motor On
            printf("Left Motor on\r\n");
        }else if(cmd == 'c'){
            GPIO_setOutputLowOnPin(GPIO_PORT_P3,GPIO_PIN7);// Turn Left Motor off
            printf("Left Motor off\r\n");
        }else if(cmd == 'f'){
            GPIO_setOutputLowOnPin(GPIO_PORT_P5,GPIO_PIN4);// Turn Left Motor Forward
            printf("Left Motor Forward\r\n");
        }else if(cmd == 'v'){
            GPIO_setOutputHighOnPin(GPIO_PORT_P5,GPIO_PIN4);// Turn Left Motor Reverse
            printf("Left Motor Reverse\r\n");
        }else if(cmd == 'g'){
            GPIO_setOutputHighOnPin(GPIO_PORT_P3,GPIO_PIN6);// Turn Right Motor on
            printf("Right Motor on\r\n");
        }else if(cmd == 'b'){
            GPIO_setOutputLowOnPin(GPIO_PORT_P3,GPIO_PIN6);// Turn Right Motor Off
            printf("Right Motor off\r\n");
        }else if(cmd == 'h'){
            GPIO_setOutputLowOnPin(GPIO_PORT_P5,GPIO_PIN5);// Turn Right Motor Forward
            printf("Right Motor Forward\r\n");
        }else if(cmd == 'n'){
            GPIO_setOutputHighOnPin(GPIO_PORT_P5,GPIO_PIN5);// Turn Right Motor Reverse
            printf("Right Motor Reverse\r\n");
        }else{
            GPIO_setOutputLowOnPin(GPIO_PORT_P2,GPIO_PIN4|GPIO_PIN5);// Turn Everything Off
            GPIO_setOutputLowOnPin(GPIO_PORT_P3,GPIO_PIN6|GPIO_PIN7);
            GPIO_setOutputLowOnPin(GPIO_PORT_P5,GPIO_PIN4|GPIO_PIN5);
            GPIO_setOutputLowOnPin(GPIO_PORT_P8,GPIO_PIN0|GPIO_PIN5);
            printf("Turn everything off\r\n");
        }// ...
    }
}

void ControlSystem(){
    ss1 = (P3IN & 0x04) != 0;// Check ss1 state
    ss2 = (P2IN & 0x08) != 0;// Check ss2 state
    bmp0 = (P4IN & 0x01) == 0;// Check bmp0 state
    bmp5 = (P4IN & 0x80) == 0;// Check bmp5 state
    LEDL = (P8OUT & 0x01) != 0;// Check LEDL state
    LEDR = (P8OUT & 0x20) != 0;// Check LEDR state
    while(!ss1){
        printf("ss1 open\r\n");
        GPIO_setOutputLowOnPin(GPIO_PORT_P2,GPIO_PIN4|GPIO_PIN5);// Turn BiLED off
        GPIO_setOutputLowOnPin(GPIO_PORT_P3,GPIO_PIN7);// Turn Left Motor off
        GPIO_setOutputLowOnPin(GPIO_PORT_P3,GPIO_PIN6);// Turn Right Motor Off
        break;
    }
    while (ss1){
        printf("ss1 close\r\n");
        if (ss2){
            printf("BiLED Green\r\n");
            GPIO_setOutputHighOnPin(GPIO_PORT_P2,GPIO_PIN5);// Turn BiLED Green
            GPIO_setOutputLowOnPin(GPIO_PORT_P2,GPIO_PIN4);
            //GPIO_setOutputHighOnPin(GPIO_PORT_P3,GPIO_PIN7);// Turn Left Motor On
            //GPIO_setOutputHighOnPin(GPIO_PORT_P3,GPIO_PIN6);// Turn Right Motor on
            GPIO_setOutputLowOnPin(GPIO_PORT_P5,GPIO_PIN4);// Turn Left Motor Forward
            GPIO_setOutputLowOnPin(GPIO_PORT_P5,GPIO_PIN5);// Turn Right Motor Forward
        }else{
            printf("BiLED Red\r\n");
            GPIO_setOutputHighOnPin(GPIO_PORT_P2,GPIO_PIN4);// Turn BiLED Red
            GPIO_setOutputLowOnPin(GPIO_PORT_P2,GPIO_PIN5);
            //GPIO_setOutputHighOnPin(GPIO_PORT_P3,GPIO_PIN7);// Turn Left Motor On
            //GPIO_setOutputHighOnPin(GPIO_PORT_P3,GPIO_PIN6);// Turn Right Motor on
            GPIO_setOutputHighOnPin(GPIO_PORT_P5,GPIO_PIN4);// Turn Left Motor Reverse
            GPIO_setOutputHighOnPin(GPIO_PORT_P5,GPIO_PIN5);// Turn Right Motor Reverse
        }
        //__delay_cycles(240e3);
        if (bmp0){
            //__delay_cycles(240e3);
            printf("bmp0 press\r\n");
            if (LEDR){
                GPIO_setOutputLowOnPin(GPIO_PORT_P8,GPIO_PIN5);// Turn LEDR Off
                LEDR = 0;
            }else if(!LEDR){
                GPIO_setOutputHighOnPin(GPIO_PORT_P8,GPIO_PIN5);// Turn LEDR On
                LEDR = 1;
            }
            while (bmp0){
                bmp0 = (P4IN & 0x01) == 0;// Check bmp0 state
            }
        }
        //__delay_cycles(240e3);
        if (bmp5){
            //__delay_cycles(240e3);
            printf("bmp5 press\r\n");
            if (LEDL){
                GPIO_setOutputLowOnPin(GPIO_PORT_P8,GPIO_PIN0);// Turn LEDL Off
                LEDL = 0;
            }else if(!LEDL){
                GPIO_setOutputHighOnPin(GPIO_PORT_P8,GPIO_PIN0);// Turn LEDL On
                LEDL = 1;
            }
            while(bmp5){
                __delay_cycles(240e3);
                bmp5 = (P4IN & 0x80) == 0;// Check bmp5 state
                __delay_cycles(240e3);
            }
        }
        // Assign LEDR/L States to R/L Motors
        printf("LEDL check and assign\r\n");
        if (LEDL){
            GPIO_setOutputHighOnPin(GPIO_PORT_P3,GPIO_PIN7);// Turn Left Motor On
        }else{
            GPIO_setOutputLowOnPin(GPIO_PORT_P3,GPIO_PIN7);// Turn Left Motor off
        }
        printf("LEDR check and assign\r\n");
        if (LEDR){
            GPIO_setOutputHighOnPin(GPIO_PORT_P3,GPIO_PIN6);// Turn Right Motor on
        }else{
            GPIO_setOutputLowOnPin(GPIO_PORT_P3,GPIO_PIN6);// Turn Right Motor Off
        }
        break;
    }
}
