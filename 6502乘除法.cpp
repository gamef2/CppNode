#include <stdio.h>
#include <string.h>
int flag_c=false;//标志位
//6502乘除法by悠然小赐
void ROL(unsigned char &val)//循环左移
{
    unsigned char ret=val>>7;//右移最高位
    val<<=1;//左移位
    val|=flag_c;//是1则相或
    flag_c=false;//清除标志位
    flag_c|=ret;//读取最高位是否是1
}
void ASL(unsigned char &val)//算术左移
{
    flag_c=false;//清除标志位
    unsigned char ret=val>>7;//右移最高位
    val<<=1;//左移位
    flag_c|=ret;//读取最高位是否是1
}

unsigned char ADC(unsigned char& a, unsigned char& b)
{
    unsigned short ret=a+b+(flag_c&1);
    //当是1与1相与得1表示上次中有进位，
    flag_c=false;//清除标志位

    flag_c|=(ret>>8)&1;//判断01 00高位有没有进位
    return ret;
}
unsigned char SBC(unsigned char& a, unsigned char& b)
{
    unsigned short ret=a-b-((flag_c&1)^1);
    //当是1与1相与得1再与1异或得0，表示上一次flag_c未变，够减。反之不够减
    flag_c=false;//清除标志位
    flag_c|=((ret>>8)&1)^1;//判断ff 00高位有没有溢出(当是1则相与得1，异或得0)
    return ret;
}
//24乘8位
void mul(int &a,int &b)
{
    int len=10;
    unsigned char arr[10];
    memset(arr,0,len);
    //初始从arr[2]开始的三个字节，乘以arr[6]单个
    strncpy((char*)arr+2, (char*)&a, 3);
    strncpy((char*)arr + 6, (char*)&b, 1);
    for(arr[7]=24; arr[7]!=0; --arr[7])
    {
        ASL(arr[0]);
        ROL(arr[1]);
        ROL(arr[2]);
        ROL(arr[3]);
        ROL(arr[4]);

        if(flag_c)
        {
            flag_c=false;//清除进位标志
            arr[0]=ADC(arr[0],arr[5]);
            arr[1]=ADC(arr[1],arr[6]);
            if(flag_c)
            {
                arr[2]++;
            }
        }
    }
    strncpy((char*)arr, (char*)arr+1, 3);
    strncpy((char*)&a, (char*)arr, 3);
}
//24除16位
void div(int &a,int &b)
{
    int len=10;
    unsigned char arr[10];
    memset(arr,0,len);

    //初始从arr[0]开始的三个字节，除以arr[6]开始的两个除数
    strncpy((char*)arr, (char*)&a, 3);
    strncpy((char*)arr + 6, (char*)&b, 3);

    arr[9]=24;
    while(arr[9])
    {
        ASL(arr[0]);//算术左移：ASL移位功能是将字节内各位依次向左移1位,最高位移进标志位C中,最底位补0
        ROL(arr[1]);//循环左移：移位功能是将字节内容连同进位C一起依次向左移1位
        ROL(arr[2]);//左移
        ROL(arr[3]);//左移
        ROL(arr[4]);//左移
        ROL(arr[5]);//左移
        unsigned char t1 = arr[3];//临时保存
        flag_c=1;//减之前标志位置1
        arr[3]=SBC(arr[3], arr[6]);
        unsigned char t2 = arr[4];
        arr[4]=SBC(arr[4], arr[7]);
        unsigned char t3=SBC(arr[5], arr[8]);//t3保存arr[5]运算的值,视情况是否存入
        if(flag_c)
        {
            arr[5]=t3;
            arr[0]++;
        }
        else
        {
            arr[3]=t1;
            arr[4]=t2;
        }
        arr[9]--;
    }
    strncpy((char*)&a, (char*)arr, 3);
    strncpy((char*)&b, (char*)arr + 3, 3);
}
void multest(int a,int b)//24除8位
{
    printf("%d 乘%d", a, b);
    mul(a, b);
    printf(" = %d\t\n", a);
}
void divtest(int a, int b)//24除16位
{
    printf("%d 除%d", a, b);
    div(a, b);
    printf(" = %d\t余数为：%d\n", a, b);
}
int main()
{
    multest(80, 6);
    multest(120, 23);
    divtest(99, 8);
    divtest(70, 23);
    divtest(30, 6);

    return 0;
}
