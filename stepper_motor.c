
#include "msg.h"

void main(){
    unsigned char flag1, flag2, flag3;
    flag1 = 0;
    flag2 = 0;
    flag3 = 0;
    Init();

    Delay_ms(100);

    centre_align(); //Center alignment
    motor_dir = 1;    //motor_dir = 0; ----- clockwise
    PWM2_Set_Duty(duty1);
    Delay_us(10);
    while(1){
    
             if(limit_F == 1){
                   PWM2_Stop();
                   Delay_ms(500);   //half sec delay
                   PWM2_Start();
                   motor_dir = 0;    //it is rotating in backward direction
                   PWM2_Set_Duty(duty1);
                   Delay_us(10);

              }
              if(limit_R == 1){
                   PWM2_Stop();
                   Delay_ms(1000);   //1 sec
                   PWM2_Start();
                   motor_dir = 1;        // moving in forward direction
                   PWM2_Set_Duty(duty1);
                   Delay_us(10);
              }
              else{
                UART4_Write_Text("No F and R sensors are dectected. ");
              }
              UART4_Write_Text("Monitoring tracks: ");
              UART4_Write(10);UART4_Write(13);
              if(TRACK_R == 1)
              {

                if(flag1 == 1)
                {
                 UART4_Write_Text("Waiting for TRACK 2");
                 UART4_Write(10);UART4_Write(13);

                }
                 else if(flag1 == 0)
                 {
                   centre_align();
                   full_driver(anti_clockwise);   //clockwise   anti_clockwise
                   UART4_Write_Text("TRACK 1 Detected: Rotated Once");
                   UART4_Write(10);UART4_Write(13);
                   flag1 = 1;

                 }                     ;
              }
              else if(TRACK_L == 1)
              {
                 if(flag3 == 1)
                 {
                   UART4_Write_Text("Waiting for TRACK 2");
                   UART4_Write(10);UART4_Write(13);
                 }
                 else if(flag3 == 0)
                 {
                   centre_align();
                   full_driver(clockwise);  //anti_clockwise   clockwise
                   UART4_Write_Text("TRACK 3 Detected: Rotated Once");
                   UART4_Write(10);UART4_Write(13);
                   flag3 = 1;

                 }
              }

              else if(TRACK_C == 1)
              {
                 if(flag1 == 1)
                 {
                   centre_align();
                   //full_driver(clockwise); //anti_clockwise
                   flag1 = 0;
                   UART4_Write_Text("Setting flag1 to zero");
                   UART4_Write(10);UART4_Write(13);
                 }
                 if(flag3 == 1)
                 {
                    centre_align();
                    //full_driver(anti_clockwise);   //clockwise
                    flag3 = 0;
                    UART4_Write_Text("Setting flag3 to zero");
                    UART4_Write(10);UART4_Write(13);
                 }
               }

               else
               {
                 UART4_Write_Text("No Operation");
                 UART4_Write(10);UART4_Write(13);
               }
    
    }
}