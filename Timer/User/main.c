/*****************************************************************
 * File Name          : main.c
 * Author             : Julio C. M. Silveira
 * Version            : V0.0.1
 * Date               : 08/08/2024
 * Last modified      : 08/08/2024
 * Description        : Usando o Timer 1, para base de tempo
 * IDE                : MounRiver Studio
 * Device             : CH32V003F4P6
*****************************************************************/

#include "debug.h"
#include <stdlib.h>  // Para a funcao abs

/*==============================================================*/
int Timer = 0;
int last = 0;
int Seg = 0;
int Min = 0;
int Hor = 0;
int setInterval = 1000;
/*==============================================================*/

void Start_Two_TIM(u16 arr, u16 psc)
{
    TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure = {0};

    // Habilita os clocks para TIM1 e TIM2
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1, ENABLE);
    //RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);

    // Configura os parametros basicos do TIM1
    TIM_TimeBaseInitStructure.TIM_Period = arr;
    TIM_TimeBaseInitStructure.TIM_Prescaler = psc;
    TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;
    TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;
    TIM_TimeBaseInitStructure.TIM_RepetitionCounter = 0x00;
    TIM_TimeBaseInit(TIM1, &TIM_TimeBaseInitStructure);

    // Configura os parametros basicos do TIM2
    /*
    TIM_TimeBaseInitStructure.TIM_Period = arr;
    TIM_TimeBaseInitStructure.TIM_Prescaler = psc;
    TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;
    TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;
    TIM_TimeBaseInit(TIM2, &TIM_TimeBaseInitStructure);
    */
    // Inicia os timers
    TIM_Cmd(TIM1, ENABLE);
    //TIM_Cmd(TIM2, ENABLE);
}


int main(void)
{
    Delay_Init();
    USART_Printf_Init(115200);
    printf("SystemClk:%d\r\n", SystemCoreClock);

    Start_Two_TIM(0xEA5F, 48000 - 1); //59999us

    while (1)
    {
        Timer = TIM1->CNT;

        if((abs(Timer - last)) >= (setInterval)){
            Seg++;
            if(Seg > 59){Seg = 0; Min++;}
            if(Min > 59){Min = 0; Hor++;}
            printf("TIM1 cnt:%d\r\n", Timer);
            printf("Current: %d : %d : %d\r\n", Hor, Min, Seg);
            last = Timer;
        }
    }
}
