#include <reg52.h>
sbit LED = P0 ^ 0;
sbit ADDR0 = P1 ^ 0;
sbit ADDR1 = P1 ^ 1;
sbit ADDR2 = P1 ^ 2;
sbit ADDR3 = P1 ^ 3;
sbit ENLED = P1 ^ 4;
void main()
{
    unsigned char cnt = 0; // 定义一个计数变量，记录 T0 溢出次数
    ENLED = 0;             // 使能 U3，选择独立 LED
    ADDR3 = 1;
    ADDR2 = 1;
    ADDR1 = 1;
    ADDR0 = 0;
    TMOD = 0x01; // 设置 T0 为模式 1
    TH0 = 0xB8;  // 为 T0 赋初值 0xB800
    TL0 = 0x00;
    TR0 = 1; // 启动 T0
    while (1)
    {
        if (TF0 == 1) // 判断 T0 是否溢出
        {
            TF0 = 0;    // T0 溢出后，清零中断标志
            TH0 = 0xB8; // 并重新赋初值
            TL0 = 0x00;
            cnt++;         // 计数值自加 1
            if (cnt >= 50) // 判断 T0 溢出是否达到 50 次
            {
                cnt = 0;    // 达到 50 次后计数值清零
                LED = ~LED; // LED 取反：0-->1、1-->0
            }
        }
    }
}