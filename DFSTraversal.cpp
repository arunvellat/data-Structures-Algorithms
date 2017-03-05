/* DFS Traversal */

#include <cstdlib>
#include <iostream>
#include <stdio.h>
using namespace std;
#define UNMARKED -1
#define MIN(x,y) ((x<y)?x:y)

struct node
{
  int nodeNum;
  node *ptr;
  int bridge;
};

class Graph
{
  node** adj; //stores adjacency list
  int V,E; //stores number of vertices and edges
  int components; //number of connected components
  int* label;
  int* highpoint;
  int* DFN;
  int* AP;
  int* parent;
  int dfn;

public:
  void BuildGraph(int n); 
  void InsertEdge(int i,int j);
  void FindConnectedComponent();
  void dfs(int v);
  void PrintConnectedComponents();
  void PrintArticulationPoints();
  void PrintBridgeEdges();
  
};

void Graph::BuildGraph(int noOfNodes)
{
    label = new int[V];
	highpoint = new int[V];
    DFN = new int[V];
	AP = new int[V];
	label = new int[V];
	parent = new int[V]; 
    adj = new node* [noOfNodes];
	for(int i=0; i < noOfNodes; i++) adj[i] = NULL;
	components = 0;
	V = noOfNodes;
}	

void Graph::InsertEdge(int i,int j)
{
	//insert j into adjacency list of i	
	node *link=adj[i];	
	if(link != NULL)
	{
		while(link->ptr != NULL) link = link->ptr;
		link = (link->ptr=new node);
	}
	else
		adj[i]= link = new node;
		
	link->nodeNum = j;
	link->ptr = NULL;

	//insert i into adjacency list of j
    link = adj[j];
	if(link != NULL)
	{
		while(link->ptr != NULL) link = link->ptr;
		link = (link->ptr=new node);
	}
	else
		adj[j]= link = new node;
		
	link->nodeNum = i;
	link->ptr = NULL;
}	

void Graph::FindConnectedComponent()
{
	dfn=0;
   	for (int i = 0; i < V; i++)
    {
        		label[i] = UNMARKED;
        		AP[i]=0;
    }
    for (int i = 0; i < V; i++)
		if (label[i] == UNMARKED)
			{ parent[i] = -1; dfs(i); components++; }
}

void Graph::dfs(int v)
{
	label[v] = components;
	DFN[v]=dfn++;
	highpoint[v]= DFN[v];
	int countChildren = 0;
	node* link = adj[v];
	
	
	for (;link != NULL; link=link->ptr)
	{
		
		if (label[link->nodeNum] == UNMARKED) 
        {
			 countChildren++;
			 parent[link->nodeNum]=v;  
			 dfs(link->nodeNum);
			                               
			 highpoint[v] = MIN(highpoint[v],highpoint[link->nodeNum]); 
			
			 if(highpoint[link->nodeNum]>=DFN[v] && (parent[v]!=-1)) //root node has to handled differently. its is AP iff it has > 1 child
				AP[v]=1;
			 else if(parent[v]==-1 && countChildren > 1)
				AP[v] = 1;
			 if(highpoint[link->nodeNum]>DFN[v])
                (link->bridge) = 1;
        }
        else if (parent[v]!=link->nodeNum)
             highpoint[v] = MIN(highpoint[v],DFN[link->nodeNum]); 
	}
	//printf("(%d %d %d %d) ",v,DFN[v],parent[v],highpoint[v]);
	
}

void Graph::PrintConnectedComponents()
{
     int t;
	printf("\nThere are %d components in the graph. These are ",components);
	for(int i=0; i<components; i++)
	{
        t=0;
		printf("{");
		for(int j=0;j < V; j++)
			if(label[j]==i) 
            {
                            if(t++!=0)
                                      printf(",");
                            printf("%d",j);

            }
		printf("}")	;
		if(i!= components-1)
		       printf("  and  ");
	}
}
void Graph::PrintArticulationPoints()
{
     int t=0;
     printf("\n Articulation points are");
         printf(" {");
		 for(int j=0;j < V; j++)
			if(AP[j]==1) 
            {
                            if(t++!=0)
                                      printf(",");
                            printf("%d",j);

            }
         printf("}.")	;
     
}

void Graph::PrintBridgeEdges()
{
     node *link;
     int check=0;
     printf("\n Bridge Edges are ");
         
		 for(int j=0;j < V; j++)
		 {
			link = adj[j];
			for (;link != NULL; link=link->ptr)
			{
				if(link->bridge)
				{
					if(check)
						printf(", (%d,%d)",j,link->nodeNum);
					else
					{
						printf("(%d,%d)",j,link->nodeNum);
						check = 1;
					}
				}
				
			}
		}
     printf(".\n");
}

int main (int argc, char** argv)
{
  Graph G;
  int n,m,i,j;
  scanf("%d %d", &n, &m);
  G.BuildGraph(n);
  for(int count=0; count < m; count++)
  {
	  scanf("%d %d", &i, &j);
	  G.InsertEdge(i,j);
  }
 //   printf("check\n");
  G.FindConnectedComponent();
  //printf("check\n");
  G.PrintConnectedComponents();
  G.PrintArticulationPoints();
  G.PrintBridgeEdges();
}

