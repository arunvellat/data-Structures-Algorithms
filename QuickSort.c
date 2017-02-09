/*
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include <time.h>

long long *temp; //temporary array for merge sort

void generateRandomSequence(long long *array, long long lowest,long long highest,long long size)
{
    srand((unsigned)time(NULL));
    long long count=0;
    long double range=(highest-lowest)+1;
    for(count=0; count<size; count++)
    {
        //array[count] = (rand()%ra) + 1;
        array[count] = lowest+(long long)((range*rand())/(RAND_MAX + 1.0));
    } 
}

void generateRandomPermutation(long long *array,long long size)
{
    srand((unsigned)time(0));
    long long i,j,temp;
    for(i=size-1;i>=1;i--)
    {
        j = (long long)((i*(long double)rand())/(RAND_MAX + 1.0)); // random no between 0 and i inclusive
        //exchange array[j] and array[i]
        temp=array[i];
        array[i] = array[j];
        array[j] = temp;
    }
}

long long partition(long long *array,long long left,long long right,long long pivotIndex)
{
    /* It partitions the portion of the array between indexes left and right, inclusively, by moving all elements less than array[pivotIndex] before the pivot, and the equal or greater elements after it. In the process it also finds the final position for the pivot element, which it returns. */
    
    long long finalPivotIndex = left;
    long long tempValue = 0,i;
    long long pivotValue = array[pivotIndex];
    
    //swap the pivot the right end temporarily
    array[pivotIndex] = array[right];
    array[right] = pivotValue;
    
    for(i=left;i<right;i++)
    {
        if(array[i]<pivotValue)
        {
            //swap array[i] and array[finalPivotIndex]
            tempValue = array[i];
            array[i] = array[finalPivotIndex];
            array[finalPivotIndex] = tempValue;
            finalPivotIndex++;
            
        }
    }
    
    //move Pivot to final Place
    tempValue = array[finalPivotIndex];
    array[finalPivotIndex] = array[right];
    array[right] = tempValue;
    
    return finalPivotIndex;
}

void quickSort(long long *array,long long leftLower,long long rightUpper)
{
    if(leftLower>=rightUpper) return; 
    
    //choose middle element as pivot
   long long midPivotIndex = (leftLower + rightUpper)/2;
    //the array is partitioned and NewPivotIndex will contain the index of the pivot element after partitioning
    long long NewPivotIndex = partition(array,leftLower,rightUpper,midPivotIndex);
    if(NewPivotIndex < midPivotIndex) // to reduce storage overload we sort the smaller partition first
    {
        quickSort(array,leftLower,NewPivotIndex-1);
        quickSort(array,NewPivotIndex+1,rightUpper);
    }
    else
    {
        quickSort(array,NewPivotIndex+1,rightUpper);
        quickSort(array,leftLower,NewPivotIndex-1);
    }
}

void merge(long long *array,long long left,long long right,long long mid)
{
    //long long C[right-left+1];
    long long i=left, j=mid+1, k=0;
    while(i < mid+1 && j<=right)
    {
        if(array[i]<array[j])
        {
            temp[k]=array[i]; k++; i++;
        }
        else
        {
            temp[k]= array[j]; k++; j++;
        }
    }
    while(i<mid+1) {temp[k]=array[i]; k++; i++;}
    while(j<=right) {temp[k]=array[j]; k++; j++;}
    
    for(k=left;k<=right;k++)
    {
        array[k] = temp[k-left];
    }
    
}
void mergeSort(long long *array,long long i,long long j)
{
    if(i>=j) return;
    int mid = (i+j)/2;
    mergeSort(array,i,mid);
    mergeSort(array,mid+1,j);
    merge(array,i,j,mid);
}

void copy(long long *A,long long *B,long long size)
{
    long long i;
    for(i=0;i<size;i++)
        B[i]=A[i];
}

int main() {
    long long *A,*B,*C;
    long long n,count;
    int choice;
    clock_t startTime,endTime;
    long double elapsed;
    
    printf("\nEnter n:");
    scanf("%Lu",&n);
    printf("\nEnter choice(1 or 2):");
    scanf("%d",&choice);
    
    A=malloc(n*sizeof(long long));
    B=malloc(n*sizeof(long long));
    C=malloc(n*sizeof(long long));
    temp=malloc(n*sizeof(long long));
    
    generateRandomSequence(A,1,n,n);
    copy(A,B,n);
    copy(A,C,n);
    
    if(choice == 1)
    {
        printf("\nRandom Sequence of numbers:\n");
        for(count=0; count<n; count++)
            printf("%Lu ",A[count]);
        
        
        quickSort(C,0,n-1);
        printf("\n\nSorted List by QuickSort:\n");
        for(count=0; count<n; count++)
            printf("%Lu ",C[count]);
        
        mergeSort(B,0,n-1);
        printf("\n\nSorted List by MergeSort:\n");
        for(count=0; count<n; count++)
            printf("%Lu ",B[count]);
    }
    else if(choice==2)
    {
        startTime = clock();
        quickSort(B,0,n-1);
        endTime = clock();
        elapsed = (((long double) (endTime - startTime))*1000)/(double) (CLOCKS_PER_SEC); 
        printf("Time taken for QuickSort: %Lf ms\n",elapsed);
        
        startTime = clock();
        mergeSort(C,0,n-1);
        endTime = clock();
        elapsed = (((long double) (endTime - startTime))*1000)/(double) (CLOCKS_PER_SEC); 
        printf("Time taken for MergeSort: %Lf ms\n",elapsed);
    }
 
   
    return 0;
}
