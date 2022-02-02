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
uint8_t ss1;
uint8_t ss2;

int main(void)
{

    SysInit();
    GPIOInit();

    printf("\r\n\n"
           "***********\r\n"
           "Lab 1 Start\r\n"
           "***********\r\n");

    while(1){
        TestIO();
        //ControlSystem();
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
            GPIO_setOutputHighOnPin(GPIO_PORT_P8,GPIO_PIN5);
            printf("Turn LEDR on\r\n");
        }else if(cmd == 'x'){
            GPIO_setOutputLowOnPin(GPIO_PORT_P8,GPIO_PIN5);
            printf("Turn LEDR off\r\n");
        }else if(cmd == 'q'){
            GPIO_setOutputHighOnPin(GPIO_PORT_P2,GPIO_PIN4);
            GPIO_setOutputLowOnPin(GPIO_PORT_P2,GPIO_PIN5);
            printf("BiLED Red\r\n");
        }else if(cmd == 'w'){
            GPIO_setOutputHighOnPin(GPIO_PORT_P2,GPIO_PIN4|GPIO_PIN5);
            printf("BiLED off\r\n");
        }else if(cmd == 'e'){
            GPIO_setOutputHighOnPin(GPIO_PORT_P2,GPIO_PIN5);
            GPIO_setOutputLowOnPin(GPIO_PORT_P2,GPIO_PIN4);
            printf("BiLED Green\r\n");
        }else if(cmd == 'd'){
            GPIO_setOutputHighOnPin(GPIO_PORT_P3,GPIO_PIN7);
            printf("Left Motor on\r\n");
        }else if(cmd == 'c'){
            GPIO_setOutputLowOnPin(GPIO_PORT_P3,GPIO_PIN7);
            printf("Left Motor off\r\n");
        }else if(cmd == 'f'){
            GPIO_setOutputLowOnPin(GPIO_PORT_P5,GPIO_PIN4);
            printf("Left Motor Forward\r\n");
        }else if(cmd == 'v'){
            GPIO_setOutputHighOnPin(GPIO_PORT_P5,GPIO_PIN4);
            printf("Left Motor Reverse\r\n");
        }else if(cmd == 'g'){
            GPIO_setOutputHighOnPin(GPIO_PORT_P3,GPIO_PIN6);
            printf("Right Motor on\r\n");
        }else if(cmd == 'b'){
            GPIO_setOutputLowOnPin(GPIO_PORT_P3,GPIO_PIN6);
            printf("Right Motor off\r\n");
        }else if(cmd == 'h'){
            GPIO_setOutputLowOnPin(GPIO_PORT_P5,GPIO_PIN5);
            printf("Right Motor Forward\r\n");
        }else if(cmd == 'n'){
            GPIO_setOutputHighOnPin(GPIO_PORT_P5,GPIO_PIN5);
            printf("Right Motor Reverse\r\n");
        }else{
            GPIO_setOutputLowOnPin(GPIO_PORT_P2,GPIO_PIN4|GPIO_PIN5);
            GPIO_setOutputLowOnPin(GPIO_PORT_P3,GPIO_PIN6|GPIO_PIN7);
            GPIO_setOutputLowOnPin(GPIO_PORT_P5,GPIO_PIN4|GPIO_PIN5);
            GPIO_setOutputLowOnPin(GPIO_PORT_P8,GPIO_PIN0|GPIO_PIN5);
            printf("Turn everything off\r\n");
        }// ...
    }
}

void ControlSystem(){

}
