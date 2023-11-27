#include<stdio.h>
#include<stdlib.h>

void goodSwap(double *pX, double *pY);

int main(){
    double x=5.0, y=10.0;
    double *px=&x, *py=&y;

    goodSwap(px,py);

    }

void goodSwap(double *pX, double *pY){
    printf('*px=',pX,'py=',pY);
    double temp=*pX;
    printf('temp',temp);
    *pX=*pY;
    printf('*pX=',pX);
    *pY=*pX;
    printf('*pX',pX);
    

}