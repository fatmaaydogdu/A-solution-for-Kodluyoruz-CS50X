#include <stdio.h>
#include <cs50.h>
#include <math.h>
int main(void){

int parasayisi=0;
int paraustu;
float tutar;
do{
tutar=get_float("Change: ");
paraustu = round(tutar * 100);
}while(tutar<0);
parasayisi+= paraustu/25;
paraustu=paraustu%25;

parasayisi+= paraustu/10;
paraustu=paraustu%10;

parasayisi+= paraustu/5;
paraustu=paraustu%5;

parasayisi+= paraustu/1;
paraustu=paraustu%1;

printf("para sayisi: %d\n",parasayisi);
}
