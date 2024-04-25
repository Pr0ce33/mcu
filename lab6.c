#include <reg52.h>
sbit ADDR0 = P1 ^ 0;
sbit ADDR1 = P1 ^ 1;
sbit ADDR2 = P1 ^ 2;
sbit ADDR3 = P1 ^ 3;
sbit ENLED = P1 ^ 4;
sbit KEY1 = P2 ^ 4;
sbit KEY2 = P2 ^ 5;
sbit KEY3 = P2 ^ 6;
sbit KEY4 = P2 ^ 7;
unsigned char code LedChar[] = { // 数码管显示字符转换表
    0xC0, 0xF9, 0xA4, 0xB0, 0x99, 0x92, 0x82, 0xF8,
    0x80, 0x90, 0x88, 0x83, 0xC6, 0xA1, 0x86, 0x8E};
void delay();
void main()
{
    bit keybuf = 1;        // 按键值暂存，临时保存按键的扫描值
    bit backup = 1;        // 按键值备份，保存前一次的扫描值
    unsigned char cnt = 0; // 按键计数，记录按键按下的次数
    ENLED = 0;             // 选择数码管 DS1 进行显示
    ADDR3 = 1;
    ADDR2 = 0;
    ADDR1 = 0;
    ADDR0 = 0;
    P2 = 0xF7;         // P2.3 置 0，即 KeyOut1 输出低电平
    P0 = LedChar[cnt]; // 显示按键次数初值
    while (1)
    {
        keybuf = KEY4;        // 把当前扫描值暂存
        if (keybuf != backup) // 当前值与前次值不相等说明此时按键有动作
        {
            delay(); // 延时大约 10ms

            if (keybuf == KEY4) // 判断扫描值有没有发生改变，即按键抖动
            {
                if (backup == 0) // 如果前次值为 0，则说明当前是弹起动作
                {
                    cnt++; // 按键次数+1
                    if (cnt >= 10)
                    { // 只用 1 个数码管显示，所以加到 10 就清零重新开始
                        cnt = 0;
                    }
                    P0 = LedChar[cnt]; // 计数值显示到数码管上
                }
                backup = keybuf; // 更新备份为当前值，以备进行下次比较
            }
        }
    }
}
/* 软件延时函数，延时约 10ms */
void delay()
{
    unsigned int i = 1000;
    while (i--)
        ;
}