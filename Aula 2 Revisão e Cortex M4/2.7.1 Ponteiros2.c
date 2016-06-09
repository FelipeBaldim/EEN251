#include <stdio.h>

void swap( int *p1 , int *p2 ) 
{
    int troca;

    troca = *p1;
    *p1=*p2;
    *p2=troca;
}



int main ( )
{
    int x=10 ;
    int y=20 ;

    swap(&x,&y);

// Voce deve c o n f i g u r a r e s s a funcao c o r r e t ame n t e

// Deve imp r imi r na t e l a x : 20 , y : 10
    printf( " x : % d , y : %d\n" , x , y ) ;
}