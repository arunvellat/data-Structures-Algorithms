/*
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include <time.h>

//these are the workspace variables/arrays
long long n=1,size;
char *result,*temp,*X,*Y;
char *resultTr; //this will store the trivial algorithm result

int carry=0,twoCplmtFlag=0,i=0;
int tempDigit;
inline int addSubtract(char *arr,long long left,long long mid,int opt)
{
    //will do X1 <- X1 + X2 ; if opt = 0;
    //opt = 1 => X1 is negative; opt = 2 => X2 is negative; opt=0 => both +ve
    int flag=0; //flag stores sign of result (0 is positive; 1 is negative)
    carry=0;twoCplmtFlag=0;
    
    //carry out two's complement of whichever X1 or X2 is negative
    if(opt == 2)
    {
        for(i=mid;i>=left;i--)
        {
            if(twoCplmtFlag) arr[i+(mid+1-left)]=(!arr[i+(mid+1-left)]);
            else if(arr[i+(mid+1-left)]) twoCplmtFlag = 1;
        }
    }
    else if(opt == 1)
    {
        for(i=mid;i>=left;i--)
        {
            if(twoCplmtFlag) arr[i]=(!arr[i]);
            else if(arr[i]) twoCplmtFlag = 1;
        }
    }
    
   
    //now do the addition
    for(i=mid;i>=left;i--)
        
    {
        tempDigit =(arr[i]+arr[i+(mid+1-left)]+carry)%2;
        carry = ((arr[i]+arr[i+(mid+1-left)]+carry)/2);
        arr[i]=tempDigit;
    }
    
     if(twoCplmtFlag!=carry) // => answer is negative, so take note of it in flag and do two's complement to get corresponding positive number
    {
        flag = 1; //toggle flag
        twoCplmtFlag=0;
        for(i=mid;i>=left;i--)
        {
            if(twoCplmtFlag) arr[i]=(!arr[i]);
            else if(arr[i]) twoCplmtFlag = 1;
        }
    }
    
    //do two's complement for X2 if opt = 2
    if(opt==2)
    {   twoCplmtFlag = 0;
        for(i=mid;i>=left;i--)
        {
            if(twoCplmtFlag) arr[i+(mid+1-left)]=(!arr[i+(mid+1-left)]);
            else if(arr[i+(mid+1-left)]) twoCplmtFlag = 1;
        }
    }
    
    return flag;
}
    
void multiplyRecursive(long long left, long long right) 
//left and right are the index positions in the X & Y input arrays, which specify the numbers being multiplied
{           //tempNumber[0]=tempNumber[1]=tempNumber[2]=tempNumber[3]=0;
    //char tempNumber[n];
    
    if(left==right)
    {
        result[2*left] = 0;
        result[2*left + 1] = (X[left] && Y[left]);
        return;
    }
    long long mid = (left+right)/2,i;
    long long interval = (right-left+1);
    int flag = 0; //flag is used to handle sign (for subtraction)
    carry=0,twoCplmtFlag=0;

    multiplyRecursive(left,mid);
    multiplyRecursive(mid+1,right);
    
       
    //copy the result array to temp array
    for(i=2*left;i<=(2*right + 1);i++)
        temp[i] = result[i];

    
     //modify temp array to obtain (2^n)(X1*Y1) + (X2*Y2) + (2^(n/2))(X1*Y1 + X2*Y2)
    carry=0,twoCplmtFlag=0;
    for(i=(2*right+1-(interval/2));i>=(2*left+(interval/2));i--)
    {
        temp[i]=(result[i]+result[i+(interval/2)]+result[i-(interval/2)]+carry) % 2;
        carry = (result[i]+result[i+(interval/2)]+result[i-(interval/2)]+carry) / 2;
    }    
    while(carry)
    {   
        tempDigit = (temp[i]+carry)%2;
        carry =  (temp[i]+carry)/2;
        temp[i] = tempDigit;
        i--;
    }

    
   //copy first half of temp to second half of result
    for(i=2*left;i<=(2*mid+1);i++)
    {
        result[i+interval] = temp[i];
    }
    
    
    //now we do X1 <- X1 - X2 (where X1 is left half and X2 is second half of X
    // and Y1 <- Y1 - Y2
    int flagLeftX = addSubtract(X,left,mid,2);
    int flagLeftY = addSubtract(Y,left,mid,2);
    flag = (flagLeftX + flagLeftY) % 2;
   
    //now do the third and final multiplication step (X1 - X2)*(Y1 - Y2)
    multiplyRecursive(left,mid);
   
   // now we do X1 <- X1 + X2
    // and Y1 <- Y1 + Y2
   addSubtract(X,left,mid,flagLeftX);
   addSubtract(Y,left,mid,flagLeftY);
   
   //copy second half of result to first half of temp
    for(i=2*left;i<=(2*mid+1);i++)
    {
        temp[i] = result[i+interval];
    }
   
    //now modify temp array to get (2^n)(X1*Y1) + (X2*Y2) + (2^(n/2))(X1*Y1 + X2*Y2 - (X1-X2)*(Y1-Y2))
    carry=0;twoCplmtFlag=0;
    long long count=0;
    for(i=(2*right+1-(interval/2));i>=(2*left+(interval/2));i--)
    {
        if(!twoCplmtFlag)
        {
            tempDigit=(temp[i]+result[2*mid+1-count]+carry)%2;
            carry=(temp[i]+result[2*mid+1-count]+carry)/2;
            temp[i] = tempDigit;
        }
        else
        {
        
            tempDigit=(temp[i]+(!result[2*mid+1-count])+carry)%2;
            carry=(temp[i]+(!result[2*mid+1-count])+carry)/2;
            temp[i] = tempDigit;
        }
      
        if(result[2*mid+1-count] && (!flag)) twoCplmtFlag=1;
        count++;
    }    
    while(i>=2*left)
    {   
        if(twoCplmtFlag)
        {
            tempDigit = (1+temp[i]+carry)%2;
            carry =  (1+temp[i]+carry)/2;
            temp[i] = tempDigit;
        }
        else
        {
            tempDigit = (temp[i]+carry)%2;
            carry =  (temp[i]+carry)/2;
            temp[i] = tempDigit;
        }
               
        i--;
    }
    
    //copy temp to result
    for(i=2*left;i<=(2*right + 1);i++)
        result[i] = temp[i];
}


void generateRandomSequence(char *array, int lowest,int highest,long long size)
{
    
    long long count=0;
    long double range=(highest-lowest)+1;
    for(count=0; count<size; count++)
    {
        //array[count] = (rand()%ra) + 1;
        array[count] = lowest+(int)((range*rand())/(RAND_MAX + 1.0));
    } 
}


void multiplyTrivial(long long size)
{
    long long j;
    
    for(i=size-1;i >= 0;i--)
    {
       
        for(j=size-1;j >= 0;j--)
            temp[j] = (X[j]&&Y[i]);
                  
        //do result = result + temp
        
        carry = 0;
        for(j=size+i;j>i;j--  )
        {
            tempDigit = ((resultTr[j]+temp[j-i-1])+carry)%2;
            carry = ((resultTr[j]+temp[j-i-1])+carry)/2;
            resultTr[j]=tempDigit;
        }
        
        while(carry)
        {
            tempDigit=(resultTr[j]+carry) % 2;
            carry = (resultTr[j]+carry) / 2;
            resultTr[j]=tempDigit;
            j--;
        }
       
    }
}

int main() {
    
    long long count;
    int choice;
    clock_t startTime,endTime;
    long double elapsed;
   
    printf("\nEnter n:");
    scanf("%Lu",&size);
    
    printf("\nEnter choice(1 or 2):");
    scanf("%d",&choice);
    
    //padding is required to make n a power of 2
     while(n<size)
        n *= 2;
  
    
    X=malloc(n*sizeof(char));
    Y=malloc(n*sizeof(char));
    result=malloc(2*n*sizeof(char));
    resultTr=malloc(2*n*sizeof(char));
    temp=malloc(2*n*sizeof(char));
        
    srand((unsigned)time(NULL));
    generateRandomSequence(X,0,1,size);
    generateRandomSequence(Y,0,1,size);
    
    if(choice == 1)
    {
        printf("\nRandom Sequence of numbers:\nX = ");
        for(count=0; count<size; count++)
            printf("%d",X[count]);
        printf("\nY = ");
        for(count=0; count<size; count++)
            printf("%d",Y[count]);
        
        multiplyRecursive(0,n-1);
        printf("\n\nX * Y by Karatsuba Recursive Method:\n");
        for(count=0; count<2*size; count++)
            printf("%d",result[count]);
        
        
        multiplyTrivial(n);
        printf("\n\nX * Y by Trivial method:\n");
        for(count=0; count<2*size; count++)
            printf("%d",resultTr[count]);
        
        printf("\n");
    }
    else if(choice==2)
    {
        startTime = clock();
        multiplyRecursive(0,n-1);
        endTime = clock();
        elapsed = (((long double) (endTime - startTime))*1000)/(double) (CLOCKS_PER_SEC); 
        printf("Time taken by Recursive Algorithm: %Lf ms\n",elapsed);
        
        startTime = clock();
        multiplyTrivial(n);
        endTime = clock();
        elapsed = (((long double) (endTime - startTime))*1000)/(double) (CLOCKS_PER_SEC); 
        printf("Time taken by Trivial Algorithm: %Lf ms\n",elapsed);
    }
 
   
    return 0;
}
