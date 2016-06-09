#include <stdio.h>

int main()

{
    
int k[20]={2,3,5,7,11,13,17,19,23,29,31,37,41,43,47,53,59,61,67,71};   
    
int j;

    
for (j=0;j<=19;j++) 
{
        
	printf("PRIMO %i = %i; \n",j+1 ,*(k+j));  
   
}
   
return 0;

}