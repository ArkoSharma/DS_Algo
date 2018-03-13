//practice

/*
    Programmer : Arko Sharma
    Roll       : 111601002
    Task       : Given a directed graph, perform DFS starting from an arbitrary vertex. Display
                 the timestamps for starting and ending and classify the edges based on the values
                 of the timestamps.
    Date       : 05.01.2018
                 

*/

#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#define fo(i,a,b) for(int i=(a);i<(b);i++)
#define sin(a) scanf("%d",&(a))

FILE *in,*out;

//nodes of Ad.List
typedef struct node{
 int data;
 // for differentiating tree edges and forward edges ; by default 0 (forward) and 1 for tree
 int treetype;                        
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

int *visited,*starting,*ending;
int tim=0;

//adds a node with a given value to a given linked list 
void add(int a,list *b){
 node *new = (node *)malloc(sizeof(node));
 new->data=a;
 //by default 0; if changed to 1 then it means tree edge
 new->treetype=0;      
 new->next=b->head;
 b->head=new;
}

//reads a given graph from stdin in AdjList format
void read_graph(Graph* g){
 fscanf(in,"%d",&(g->V));
 //dynamically allocate an array of LinkedLists
 g->adjlist = (list * )malloc((g->V)*sizeof(list));
 fo(i,0,g->V){
  g->adjlist[i].head=NULL;
 }
 int read;
 int aa;
 int c=0,num_ver=0;
 while(num_ver < g->V ){
  fscanf(in,"%d",&aa);
  if(aa==-1) num_ver++;
  else if(num_ver < g->V ) add(aa,&(g->adjlist[num_ver]));
 }
}

//perform DFS (single vertex) 
void dfs(Graph *a,int vertex){
 if(!visited[vertex]){
  visited[vertex]=1;
  tim++;
  starting[vertex]=tim;
  node* iterator=(a->adjlist[vertex]).head;
  while(!(iterator==NULL)){
   if(!visited[iterator->data]){
    //mark the tree edges
    iterator->treetype=1; 
    dfs(a,iterator->data);
   }
   iterator=iterator->next;
  }
  tim++;
  ending[vertex]=tim;
 }
 else return;
} 



/* function to print the type of the edges depending upon the dfs timestamps and  "type" attributes of AdjList */
void print_edge_type(Graph *g){
 
 int curr_vertex=0;
 fprintf(out,"\n	Edge From		Edge To		Edge Type\n\n");
 while(curr_vertex < g->V){
  node* iterator=g->adjlist[curr_vertex].head;
  while(iterator!=NULL){


   // Check 3 cases
   // case 1 [u [v v] u]
   int u=curr_vertex;
   int v=iterator->data;
   if(starting[u] < starting[v] && ending[v] < ending[u])
   {
    if(iterator->treetype ==1)
     fprintf(out,"		%d		%d              TreeE\n",u,v);	
    else
     fprintf(out,"		%d		%d              ForwardE\n",u,v);
   }
   // case 2 [v [u u] v]
   else if(starting[v] < starting[u] && ending[u] < ending[v])	
    fprintf(out,"		%d		%d              BackE\n",u,v); 
   //case 3 [v v] [u u]
   else if(starting[v]< starting[u] && ending[v]<starting[u])
    fprintf(out,"		%d		%d              CrossE\n",u,v);   
   iterator=iterator->next;
  }
  curr_vertex++; 
 }
}




int main(){
 
 char fin[20],fout[20];
 printf("Enter the name of the input file\n");
 scanf(" %[^\n]s",fin);
 in=fopen(fin,"r");
 if(in==NULL){ 
  
  printf("Error in opening file\n\n");
  return 0;
 }
 printf("Enter the name of the output file\n");
 scanf(" %[^\n]s",fout);
 out=fopen(fout,"w");
 if(out==NULL){ 
  
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
  memset(visited,0,sizeof visited);
  //perform DFS
  fo(i,0,(g->V))
   if(!visited[i]) dfs(g,i);
  
  //print timestamps
  fprintf(out,"Starting DFS from first vertex (indexed 0)\n\n"); 
  fprintf(out,"		Vertex		StartTime	EndTime\n\n"); 
  fo(i,0,g->V){
   fprintf(out,"		%d		%d		%d\n",i,starting[i],ending[i]);
  }
  print_edge_type(g);
 }
 else fprintf(out,"Graph is empty\n");
 fclose(in);
 fclose(out);
 return 0;
}		
 



