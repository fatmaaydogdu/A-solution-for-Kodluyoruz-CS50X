#include <stdio.h>
#include <cs50.h>
int main(){
    long long KartNumarasi=get_long_long("Numara:");
    int hane1=0,hane2=0;
    int sonToplam=0;
    int KartHanesi=0;
    int sayac=0;
    int duzToplam=0;
    int ikilenenToplam=0;
    while(KartNumarasi>0){
        hane2=hane1;
        hane1=KartNumarasi%10;
        if(sayac%2==0){
            duzToplam +=hane1;
        }else{
            int atanacakDeger=2*hane1;
            ikilenenToplam+=(atanacakDeger/10)+(atanacakDeger%10);
        }

        KartNumarasi /=10;
        sayac++;
    }

    bool gecerliKart=(duzToplam+ikilenenToplam)%10==0;
    int ilkSimgeci=(hane1*10)+hane2;
    if((hane1==4)&&((sayac==13)||(sayac==16))&&gecerliKart)
    {
        printf("VISA\n");
    }else if((ilkSimgeci<56&&ilkSimgeci>50)&&(sayac==16)&&gecerliKart){
        printf("MASTERCARD\n");
    }else if(((ilkSimgeci==34)||(ilkSimgeci==37))&&(sayac==15)&&gecerliKart){
        printf("AMEX\n");
    }else{
        printf("INVALID\n");
        }
}
