#include <stdio.h>
#include <cs50.h>
#include<stdlib.h>
int satirsayisi;
int main(){
    do{
satirsayisi=get_int("height: ");


}while(satirsayisi<1 || satirsayisi>8 );

    int yildizsayisi=1;
    int bosluksayisi=satirsayisi-1;
    for(int i=1;i<=satirsayisi;i++){
        for(int j=1;j<=bosluksayisi;j++ ){
            printf(" ");
        }

        for(int j=1;j<=yildizsayisi;j++){
            printf("#");
        }
        printf("  ");
        for(int j=1;j<=yildizsayisi;j++){
            printf("#");
        }
        printf("\n");
        yildizsayisi++;
        bosluksayisi--;

    }

}
