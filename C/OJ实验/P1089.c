#include<stdio.h>
int main(){
        int c,b=0,save=0,i;                        //c=每个月花的钱，s=自己手里的钱，save=存给麻麻的红色毛爷爷数量
        for(i=1;i<=12;i++)            //从一月循环到十二月
        {
                scanf("%d",&c);                   //读入每个月花的钱
                b-=c-300;                          //等效于s=s+300-c，算出这个月过去之后还剩多少钱
                if(b<0)                               //如果（“哇这个月过去之后我就没钱了！”）
                {
                        printf("-%d",i);                //直接输出“-月份”
                        return 0;                        //然后结束程序（没钱啦不活啦！//并不需要读完所有数据）
                }
                else save+=b/100,b%=100;     //如果这个月过去之后还有钱，我们就把整百的钱（s/100）存给麻麻，并给自己留下零钱（s%100）
        }
        printf("%d",120*save+b);             //成功抵达12月，每张100元将会变成120元，加上自己手里的零钱，输出
        return 0;
}
