/*
    Programmer : Arko Sharma
    Roll       : 111601002
    Task       : Given a directed graph (no of vertices followed by no of edges followed by edgellist ; perform BellmanFord 			 algorithm to print the shortest distances.Detect and print a negative cycle reachable from source if found.
    Date       : 06.03.2018
                 

*/

#include<bits/stdc++.h>
#include<cassert>
#define INF (INT_MAX/2)
using namespace std;
int *parent,*dist;
FILE *out;

//(3-tuple)
typedef struct triple{
  int fi;
  int se;
  int thi;	
}triple;

//Graph structure
typedef struct Graph{
 int V;
 int E;
 triple *elist;
}Graph;

//reads a given graph from stdin in Edgelist format
void read_graph(Graph* g){
 scanf("%d %d",&(g->V),&(g->E));
 int u,v,w;
 int c=0,num_edge=0;
 g->elist =(triple *)malloc((g->E)*sizeof(triple));
 assert(g->elist);
 while(num_edge < g->E ){
   scanf("%d %d %d",&u,&v,&w);
   g->elist[num_edge].fi=u;
   g->elist[num_edge].se=v;
   g->elist[num_edge].thi=w;
   num_edge++;
 }
}

//performs Bellman Ford algo on a graph with a given edge list
void BellmanFord(Graph *g,int source){
  for(int i=1;i<=(g->V);i++){
	int change_flag=0;
    for(int j=0;j<(g->E);j++){
	  int u=g->elist[j].fi;
	  int v=g->elist[j].se;
	  int w=g->elist[j].thi;
	  //relax
	  if(dist[v] > dist[u]+w){

		  dist[v]=dist[u]+w;
		  parent[v]=u;
		  change_flag=1;
	        
	          if(i==(g->V)){
	          
			  //negative cycle detected
			  cout<<"NEGATIVE CYCLE DETECTED\n\n";
			  int *Stack=(int *)malloc((g->V)*sizeof(int));
			  int *visited=(int *)malloc(((g->V)+1)*sizeof(int));
			  assert(Stack);
			  assert(visited);
			  int top=0;
			  memset(visited,0,sizeof(visited));
			  //push the first vertex into the stack
			  Stack[top]=v;
			  top++;
			  visited[v]=1;
			  int current=u;
			  //follow parent pointers till a vertex is repeated
			  while(visited[current]==0){
			    Stack[top]=current;
			     top++;
	    		     visited[current]=1;
	    		     current=parent[current];
			  }
			  //when visited becomes true, a cycle is completed
			  //since this cycle is present in the predecessor subgraph, its weight must be -ve
			  cout<<current;
			  top--;
			  while(top>0){
			    int uu=Stack[top];
			    top--;
			    cout<<" -> "<<uu;
			    if(uu==current) break;
			  }
			  cout<<" -> "<<current<<"\n\n";
			  exit(0);
               }
	}
    }
    if(change_flag==0)
      break;
  }
 return ;
}  

int main(){
  Graph newgraph;
  Graph *g=&newgraph;
  int source,i;
  read_graph(g);
  cin>>source;
  if(g->V !=0){
    dist=(int *)malloc((g->V)*sizeof(int));
    parent=(int *)malloc((g->V)*sizeof(int));
    assert(dist);
    assert(parent);
    //initialise the dists and parents
    memset(parent,-1,sizeof(parent));
    for(int i=0;i<(g->V);i++){
	  dist[i]=INF;
    }
    dist[source]=0;
    parent[source]=source;
    BellmanFord(g,source);
    cout<<" Printing shortest dists..\n\n";
    for(i=0;i<(g->V);i++){
	  if(dist[i]!=INF) 
   	   cout<<"Vertex "<<i<<" :: "<<dist[i]<<'\n';     
   	  else
   	   cout<<"Vertex "<<i<<" :: "<<"infinity"<<'\n';     
   	  
    }    
  }
  else printf("Graph is empty\n");
  return 0;
}

