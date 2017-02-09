
#include <stdio.h>
#include <stdlib.h>
#include<time.h>

#define LIMIT 10000000
/*
 * 
 */

int ArrayMultiply(char *s, int n, int noOfDigits)
{
    int temp=0,i;
    int carry=0;
    
    for(i=0;i<noOfDigits;i++)
    {
        temp = s[i]*n + carry;
        s[i] = temp % 10;
        carry = temp/10;
    }
    
    while(carry!=0) {
        s[noOfDigits++] = (carry%10);
        carry /= 10;
    }
    
    return noOfDigits;
}

int main(int argc, char** argv) {
    char digits[LIMIT]= {0};
    int input=0,counter=0,i,noOfDigits,temp;
	do {    
	printf("\nEnter value of n (to compute n!) : ");
    scanf("%d", &input);
   
    digits[0]=1; noOfDigits = 1;
    
    /*clock_t startTime = clock();
   	for(temp=0; temp < 1000;temp ++){ */
    for(i=2;i<=input;i++)
        noOfDigits = ArrayMultiply(digits,i,noOfDigits); 
	//digits[0]=1; noOfDigits = 1;
	//}
    
    clock_t endTime = clock();
    
    //printf("\nNo of Digits%d\n",noOfDigits);
    for(i=noOfDigits-1; i >= 0;i--) printf("%d",digits[i]);
    /*long double elapsed = ((long double) (endTime - startTime)) / (double)CLOCKS_PER_SEC;
    printf("\nRun Time is %Lf\n\n",elapsed); */ 
	} while(input != 0);  
    return (0);
}

