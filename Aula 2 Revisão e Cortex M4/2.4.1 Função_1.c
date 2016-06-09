#include <stdio.h>

int MDC (int num1,int num2 ){
    int hcf,i;
    for (i=1; i<=num1 || i<=num2; ++i)
        if(num1%i==0 &&  num2%i==0)
            hcf=i;
    
    return hcf;
    
}   

int main(){
    int num1 ,num2;
    
    int i,hcf;
    
    printf("Numero 1: \n");
    scanf("%d" , &num1);
    
    printf("Numero 2: \n");
    scanf("%d" , &num2);
    
    
    hcf=MDC ( num1,num2 );
    
    printf("H.C.F of  %d and %d is %d  \n" , num1, num2, hcf);
    return 0;
}