#include <stdio.h>
#define clockwise 0           // clockwise direction macro
#define anti_clockwise 1   // anti clockwise direction macro

#define nbr_pulses 25
#define pulse_high 1000
#define pulse_low 10000

sbit LEFT_STEER at RF4_bit;
sbit RIGHT_S at RF6_bit;
sbit Dir_pin at RG7_bit;     //pulses
sbit pulses at RG3_bit;  //Dir_pin

sbit TRACK_R at RF0_bit;
sbit TRACK_C at RF1_bit;
sbit TRACK_L at RF2_bit;

sbit motor_dir at RG0_bit;
sbit pwm at RE4_bit;
sbit limit_F at RF3_bit;
sbit limit_R at RF5_bit;


sbit LEFT_STEER_Direction at TRISF4_bit;
sbit RIGHT_S_Direction at TRISF6_bit;
sbit Dir_pin_Direction at TRISG7_bit;
sbit pulses_Direction at TRISG3_bit;

sbit TRACK_R_Direction at TRISF0_bit;
sbit TRACK_C_Direction at TRISF1_bit;
sbit TRACK_L_Direction at TRISF2_bit;

sbit motor_dir_Direction at TRISG0_bit;
sbit pwm_Direction at TRISE4_bit;
sbit limit_F_Direction at TRISF3_bit;
sbit limit_R_Direction at TRISF5_bit;

unsigned int duty1 = 0;
void Init(){
    CM1CON0 = 0;      // Disable comparators
    CM2CON1 = 0;

    OSCCON1 = 0X60;  //HFINTOSC & 1:1 Divider
    OSCTUNE = 0X1F; //mAximum Frequency
    OSCFRQ = 0X08; //64 Mhz

    ANSELF = 0; //as digital pins
    ANSELG = 0;
    ANSELE  = 0;                                    // Configure AN pins as digital I/O
    //UART4
    TRISC.B0 = 0;         //TX , OUTPUT    uart4
    TRISC.B1 = 1;         // RX, INPUT

    TRISG = 0x00;          //port G as OUTPUT
    PORTG = 0x00;

    TRISF = 0xFF;          //port F as inputs
    PORTF = 0xFF;

    PORTE.B4 = 0x00;
    TRISE.B4 = 0x00;    //pwm2

    PWM2_Init(20000);
    PWM2_Start();
    duty1 = 55;

    LEFT_STEER_Direction = 1;
    RIGHT_S_Direction = 1;
    TRACK_R_Direction = 1;
    TRACK_C_Direction = 1;
    TRACK_L_Direction = 1;
    limit_F_Direction = 1;
    limit_R_Direction = 1;

    pulses_Direction = 0;
    Dir_pin_Direction = 0;
    motor_dir_Direction = 0;

    pulses = 0;
    Dir_pin = 0;
    motor_dir = 0;

    UART4_Init(115200);
    Delay_ms(100);
    UART4_Write_Text("START_motor");
    UART4_Write(10);
    UART4_Write(13);
}

void step_driver(char direction){

    if(direction == anti_clockwise){

         pulses = 1;Delay_us(pulse_high);
         pulses = 0;Delay_us(pulse_low);
     }
    else if(direction == clockwise){

             pulses = 1;Delay_us(pulse_high);
             pulses = 0;Delay_us(pulse_low);
     }
     else {
         pulses = 0;
         Dir_pin = 0;
     }
}
void full_driver(char direction){
 char loop_cnt;
    if(direction == anti_clockwise){
             Dir_pin = 0;
             for (loop_cnt = 0; loop_cnt < nbr_pulses; loop_cnt++)
             {
              pulses = 1;Delay_us(pulse_high);
              pulses = 0;Delay_us(pulse_low);
             }

     }
     else if(direction == clockwise){
             Dir_pin = 1;
             for (loop_cnt = 0; loop_cnt < nbr_pulses; loop_cnt++)
             {
              pulses = 1;Delay_us(pulse_high);
              pulses = 0;Delay_us(pulse_low);
             }

     }
     else {

         pulses = 0;
         Dir_pin = 0;
     }
}
void centre_align(){

   Delay_ms(100);
   if(RIGHT_S == 1){    // right      STEER_R ,PORTH.B0(TRISH.B0)

       while(RIGHT_S == 1 && LEFT_STEER != 1){
          Dir_pin = 1;
          step_driver(anti_clockwise);
          UART4_Write_Text("Steer right is ON.");
          UART4_Write(10);UART4_Write(13);
       }

    }
    Delay_ms(100);
    if(LEFT_STEER == 1){   //Left       STEER_L ,PORTH.B3(TRISH.B3)

       while(LEFT_STEER == 1 && RIGHT_S != 1){
          Dir_pin = 0;
          step_driver(clockwise);
          UART4_Write_Text("Steer left is ON.");
          UART4_Write(10);UART4_Write(13);
       }
    }
}