#include <stdio.h>



const int tamanho = 20 // indica o tamanho do vetor




int main()

{
    
int k[tamanho]={2,3,5,7,11,13,17,19,23,29,31,37,41,43,47,53,59,61,67,71};   // declaração do vetor
    
int j;
    
for (j=1;j<tamanho;j++) // incrementa j de um até o tamanho do vetor de um em um
        
	printf("PRIMO %i = %i; \n",j ,k[j-1]);    //exibe o vetor k[j]
   

   
return 0;

}
