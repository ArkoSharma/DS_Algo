/*
    Programmer : Arko Sharma
    Roll       : 111601002
    Task       : Given a directed graph,check if it is a DAG and order the vertices in a topological ordering.
    Date       : 19.01.2018
                 

*/

#include<stdio.h>
#include<assert.h>
#include<string.h>
#include<stdlib.h>

FILE *in,*out;

//nodes of Ad.List
typedef struct node{
 int data;
 struct node* next;
}node;

//list structure
typedef struct list{
 node *head;

}list;

//Graph structure
typedef struct Graph{
 int V;
 list *adjlist;
}Graph;

int *visited,*starting,*ending,*topo;
int tim=0;
int head=0;
int endpoint;

//adds a node with a given value to a given linked list 
void add(int a,list *b){
 node *new = (node *)malloc(sizeof(node));
 new->data=a;
 //by default 0; if changed to 1 then it means tree edge
 new->next=b->head;
 b->head=new;
}

//reads a given graph from stdin in AdjList format
void read_graph(Graph* g){
 scanf("%d",&(g->V));
 //dynamically allocate an array of LinkedLists
 g->adjlist = (list * )malloc((g->V)*sizeof(list));
 for(int i=0;i<g->V;i++){
  g->adjlist[i].head=NULL;
 }
 int aa;
 int c=0,num_ver=0;
 while(num_ver < g->V ){
  scanf("%d",&aa);
  if(aa==-1) num_ver++;
  else if(num_ver < g->V ) add(aa,&(g->adjlist[num_ver]));
 }
}

//perform DFS (single vertex) 
int dfs(Graph *a,int vertex){
  int ret;
  visited[vertex]=1;
  tim++;
  starting[vertex]=tim;
  node* iterator=(a->adjlist[vertex]).head;
  while(!(iterator==NULL)){
   //for self loops
   if(iterator->data==vertex ){
    fprintf(out,"A directed cycle is detected :\n\n");
    fprintf(out,"%d <- %d",vertex,vertex);
    printf("  Output is in file \"out.txt\" \n\n");
    exit(0);
   }
   if(!visited[iterator->data]){
    ret=dfs(a,iterator->data);
    //if a cycle has been found
    if(ret==1){
	 //if the current vertex is the endpoint
	 if(endpoint==vertex){
	  fprintf(out," %d",endpoint);
	  exit(0);
     }
     //otherwise keep printing the cycle vertices
     else{
      fprintf(out," %d <-",vertex);
      return 1;
     }
	} 
     
   }
   else{
    //check back edge for visited vertices
    // [v [u u] v] for edge u->v
    if(starting[vertex] > starting [iterator->data] && ending[iterator->data]==0){
     
     fprintf(out,"A directed cycle is detected :\n\n");
     endpoint=iterator->data;
     fprintf(out,"%d <- %d <-",endpoint,vertex);
     printf("  Output is in file \"out.txt\" \n\n");
     //notify the ancestors that a cycle has been found
     return 1;
    }
   }
   iterator=iterator->next;
  }
  tim++;
  topo[head++]=vertex;
  ending[vertex]=tim;
  return 0;
} 






int main(){
 int i,j;
 //in=fopen("a.in","r");
 out=fopen("out.txt","w");
 if( out==NULL){ 
  printf("Error in opening file\n\n");
  return 0;
 }
 
 Graph newgraph;
 //Graph *g=(Graph*)malloc(sizeof (Graph));
 Graph *g=&newgraph;
 read_graph(g);
 if(g->V !=0){
  visited=(int *)malloc((g->V)*sizeof(int));
  starting=(int *)malloc((g->V)*sizeof(int));
  ending=(int *)malloc((g->V)*sizeof(int));
  topo=(int *)malloc((g->V)*sizeof(int));
  assert(visited);
  assert(topo);
  assert(starting);
  assert(ending);
  memset(visited,0,sizeof visited);
  memset(starting,0,sizeof starting);
  memset(visited,0,sizeof ending);
  
  //perform DFS
  for(i=0;i<(g->V);i++)
  if(!visited[i]) 
   j=dfs(g,i);
  
  assert(j==0);
  //if program did not exit then reaches here
  for(i=0;i<(g->V);i++)
   fprintf(out,"%d ",topo[(g->V)-i-1]);
  
 }
 else fprintf(out,"Graph is empty\n");
 printf("  Output is in file \"out.txt\" \n\n");
 //fclose(in);
 fclose(out);
 return 0;
}
