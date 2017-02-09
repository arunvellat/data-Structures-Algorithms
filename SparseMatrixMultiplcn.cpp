/* Sparse Matrix Multiplication */

#include <cstdlib>
#include <iostream>
using namespace std;

struct node
{
  float value;
  node *right;
  node *down;
  int row_no,col_no; //the value nodes have rows & columns numbered from 1,...,n
};

class Matrix
{
  node *P, *Q; // P points to list of column head nodes and R to list of row-head nodes
  int size; //dimension of matrix
public:
  Matrix()
  {
    P = NULL; Q = NULL;
    size = 0;
  }
  void createMatrix(int n); //to create a n X n matrix
  void displayMatrix(); //display all the non-zero elements of the matrix
  void Insert(int row,int col,float value); //insert node with data=value at position (row,col)
  Matrix Multiply(Matrix secondMatrix); //returns (current matrix).(second Matrix)
  
};

void Matrix::createMatrix(int n)
{
    if(n<=0) return;
    size = n;
    node *temp;
    P = new node();
    P->row_no = 0;
    P->col_no = 1;
    P->down = NULL;
 
    temp = P;
    for(int j=2; j<=n; j++)
      {
         temp = ((temp->right) = new node());
         temp->row_no = 0;
         temp->col_no = j;
         temp->down = NULL;
      }
    temp->right = NULL;
    
    Q = new node();
    Q->col_no = 0;
    Q->row_no = 1;
    Q->right = NULL;
    
    temp = Q;
    for(int i=2; i<=n; i++)
      {
         temp = ((temp->down) = new node());
         temp->col_no = 0;
         temp->row_no = i;
         temp->right = NULL;
      }
    temp->down = NULL;
}

void Matrix::displayMatrix()
{
  node *temp;

  if(Q==NULL)
    {
      cout << "Matrix not created yet !!";
      return;
    }
  
  node *RowPointer = Q;
  node *tempCol;
  while(RowPointer!=NULL)
    {
      node *tempCol=(RowPointer->right);
      while(tempCol != NULL)
          {
            cout << endl << (tempCol->row_no) << " " << (tempCol->col_no) << " " << (tempCol->value);
            tempCol = tempCol->right;
          }
      RowPointer = RowPointer->down;
    }
  
}

void Matrix::Insert (int row, int col, float value)
{
  node *leftNode, *topNode; //will eventually point respectively to the non-zero element just to the left of and the element just above the desired element to be inserted.
  
  leftNode = Q; topNode = P;
  for(int i = 1; i < row; i++)
    leftNode = leftNode->down;
  for(int j=1; j < col; j++)
    topNode = topNode->right;

  while(topNode->down != NULL)
    {
      //cout << topNode->col_no;
      if((topNode->down)->row_no > (row-1)) break;
      topNode = topNode->down;
    }
   // cout << "All fine";
    
  while(leftNode->right != NULL)
    {
      if((leftNode->right)->col_no > (col-1)) break;
      leftNode = leftNode->right;
    }
  
  node *newNode = new node();
  newNode->value = value;
  newNode->col_no = col; newNode->row_no = row;
  
  node *temp;
  temp = topNode->down;
  topNode->down = newNode;
  newNode->down = temp;
  
  temp = leftNode->right;
  leftNode->right = newNode;
  newNode->right = temp;
  
}

Matrix Matrix::Multiply(Matrix secondMatrix)
{
  Matrix Product;
  Product.createMatrix(size);

  node *RowFirst, *ColSecond;
  RowFirst = Q;
  
  
  float sum=0;
  node *tempFirst, *tempSecond;
  while(RowFirst != NULL)
    {
      ColSecond = secondMatrix.P;
      
      while(ColSecond != NULL)
        {
          tempFirst = RowFirst->right;
          tempSecond = ColSecond->down;
          sum = 0;
          while(tempFirst != NULL && tempSecond != NULL)
            {
              
              if((tempFirst->col_no) > (tempSecond->row_no))
                  tempSecond=tempSecond->down;
              else if((tempFirst->col_no) < (tempSecond->row_no))
                  tempFirst=tempFirst->right;
              else
                {
                 
                  sum += ((tempFirst->value)*(tempSecond->value));
                  tempSecond=tempSecond->down;
                  tempFirst=tempFirst->right;
                }
            }
          
         if(sum!=0) Product.Insert(RowFirst->row_no,ColSecond->col_no,sum);
         
          ColSecond = ColSecond->right;
        }
       RowFirst = RowFirst->down;
    }
  return Product;
}

int main (int argc, char** argv)
{
  Matrix M[2];
  Matrix productMatrix;
  int size;
  cout << "\nEnter n(size of matrix): ";
  cin >> size;
  
  M[0].createMatrix(size);
  M[1].createMatrix(size);
  productMatrix.createMatrix(size);
  cout << "Enter matrix elements (enter 0 to end)\n";
  
  int MatrixNo=-1, row, col;
  float value;
  
  while(true)
    {
      cin >> MatrixNo;
      if(MatrixNo==0) break;
      cin >> row;
      cin >> col;
      cin >> value;
      M[MatrixNo-1].Insert (row,col,value);
    };

  productMatrix = M[0].Multiply (M[1]);

  cout << endl << "Product of 2 matrices (row,col,value):";
  productMatrix.displayMatrix();
  return 0;
}

