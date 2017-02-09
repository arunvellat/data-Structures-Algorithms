#include <stdio.h>
#include <time.h>

void multiply(long long [2][2], long long [2][2], long m); //used by power function which is in turn used by fibMatrix
void power(long long [2][2], long long n, long m); //used by fibMatrix


long fibRecursive(long long n,long m)
{
	
	if(n==0 || n==1)
		return (n%m);
	else
		return (fibRecursive(n-1,m) + fibRecursive(n-2,m))%m;
}
		
long fibIter(long long n,long m)
{
	long secondLast=0 ,Last=(1%m);
	long long j=0;
	long fiba = 0;

	while(j < n-1)
	{
		fiba=(secondLast + Last)%m;
		secondLast = Last;
		Last=fiba;
		j++;
	}

	if(n==0 || n==1) return (n%m);
	else return (fiba);
}

long fibMatrix(long long n, long m)
{
  long long baseMatrix[2][2] = {{1,1},{1,0}};
  if(n == 0 || n==1) return (n%m);
    
  power(baseMatrix, n-1, m);
  return (baseMatrix[0][0]%m);
}


void power(long long curr_Matrix[2][2], long long n, long m)
{
  if( n == 0 || n == 1)
      return;
  long long baseMatrix[2][2] = {{1,1},{1,0}};
 
  power(curr_Matrix, n/2, m);
  multiply(curr_Matrix, curr_Matrix, m);
 
  if( n%2 != 0 )
     multiply(curr_Matrix, baseMatrix, m);
}

void multiply(long long Matrix1[2][2], long long Matrix2[2][2], long m)
{
  long long x =  Matrix1[0][0]*Matrix2[0][0] + Matrix1[0][1]*Matrix2[1][0];
  long long y =  Matrix1[0][0]*Matrix2[0][1] + Matrix1[0][1]*Matrix2[1][1];
  long long z =  Matrix1[1][0]*Matrix2[0][0] + Matrix1[1][1]*Matrix2[1][0];
  long long w =  Matrix1[1][0]*Matrix2[0][1] + Matrix1[1][1]*Matrix2[1][1];
 
  Matrix1[0][0] = x % m;
  Matrix1[0][1] = y % m;
  Matrix1[1][0] = z % m;
  Matrix1[1][1] = w % m;
}


int main()
{
	clock_t startTime, endTime;
	long long n;
	long m;
	long result;
	int choice = 0;
	long double elapsed;
	int temp=0;
	//printf("%Ld", LLONG_MAX);
	
	printf("Enter choice(1.Recursion; 2.Iteration; 3. Matrix Exponentiation by Repeated Squaring): ");
	scanf("%d",&choice);

	printf("Enter Value of n: ");
	scanf("%Ld",&n);

	printf("Enter Value of m: ");
	scanf("%ld",&m);

	

	switch(choice)
	{
		case 1:
		//recursion
			/*startTime = clock();
			for(temp=0;temp < 1000;temp++)*/
			result = fibRecursive(n,m);
			/*endTime = clock();
	
			elapsed = ((double) (endTime - startTime)) / CLOCKS_PER_SEC; */

			printf("Result Recursion :: %ld \n",result);
			//printf("Run Time of Recursion is %llf s\n\n",elapsed);   
			break;

		case 2:	
		  // iteration
			//startTime = clock();
			result = fibIter(n,m);
			/*endTime = clock();

			elapsed = ((double) (endTime - startTime)) / CLOCKS_PER_SEC;*/

			printf("Result Iteration :: %ld \n",result);
			//printf("Run Time of Iteration is %llf s\n\n",elapsed);    
			break;

		case 3:
		//matrix exponentiation by repeated squaring
			//startTime = clock();
			//for(temp=0; temp < 1000000;temp++)
				result = fibMatrix(n,m);
			/*endTime = clock();
  
			elapsed = (((long double) (endTime - startTime))) / (double)CLOCKS_PER_SEC;*/
  
			printf("Result Matrix Method :: %ld \n", result);
 			//printf("Run Time is %llf microsec\n\n", elapsed);	
			break;
	
		default:
			printf("Invalid choice entered!\n");
			break;
	}
	
	 
}
