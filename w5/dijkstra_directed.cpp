/*
    Programmer : Arko Sharma
    Roll       : 111601002
    Task       : Given a undirected graph (no of vertices followed by no of edges followed by edgellist and a source vertex perform Dijkstra's algorithm to store the minimum distances and the previous vertex in the shortest path tree.
    Date       : 30.01.2018
                 

*/

#include<bits/stdc++.h>
#include<cassert>
#define PARENT(i) (i)/2
#define LEFT(i) 2*(i)
#define RIGHT(i) 2*(i)+1
using namespace std;
int *previous,*dist,*heapindex;

//defines a structure to hold a pair of integers
typedef struct Pair_int{
  //first and second(vertex index,distance)
  int fi;
  int se;

}Pair;


//heap structure (each node is a pair -having two fields:: vertex no . and Distance)
typedef struct heap{
  Pair A[101];
  int heapsize;
}heap;

//swap the contents of addresses of two Pairs and also the heapindices of the vertices
void swap(Pair *a,Pair *b){
  Pair temp=*a;
  *a=*b;
  *b=temp;
  int tempindex=heapindex[a->fi];
  heapindex[a->fi]=heapindex[b->fi];
  heapindex[b->fi]=tempindex;
}


FILE *in,*out;

//nodes of Ad.llist-each node has two integer attributes :: Vertex Number and EdgeWeight 
typedef struct node{
 int first;
 int second;
 struct node* next;
}node;


//Linkedlist structure( note cant name "list" ;which is defined in STL )
typedef struct llist{
 node *head;
}llist;

//Graph structure
typedef struct Graph{
 int V;
 int E;
 llist *adjllist;
}Graph;

//perform min-heapify on a given array with a specified root position-use the distance(second attribute) 
void min_heapify(heap *h,int pos_root){
  int l=LEFT(pos_root);
  int r=RIGHT(pos_root);
  int smallest=pos_root;
  if(l <= h->heapsize && h->A[l].se <h->A[pos_root].se){
    smallest=l;
  }
  if(r<= h->heapsize && h->A[r].se <h->A[smallest].se){
    smallest=r;
  }
  if(smallest!=pos_root){
    swap(&(h->A[smallest]),&(h->A[pos_root]));
    min_heapify(h,smallest);
  }

}

//perform build_heap op on a given heap-structure
void build_heap(heap *h){
  int i;
  for(i=(h->heapsize)/2;i>=1;i--){
    min_heapify(h,i);
  }
}

//decreases the key value of the element indexed at a given index
int heap_decrease_key(heap *h,int i,int key){
  if(key > h->A[i].se){
    cout<<"Decrease-key operation failed\n\n";
    return 1;
  }
  h->A[i].se=key;
  while(i>1 && h->A[PARENT(i)].se >h->A[i].se){
    swap(&(h->A[PARENT(i)]),&(h->A[i]));
    i=PARENT(i);
  }
  return 0;
}


//deletes and returns the minimum element(vertex no. for this program) of a min-heap
int delete_min(heap *h){
  if(h->heapsize < 1){
    cout<<"Heap underflow\n\n";
    return -1;
  }
  // first attribute is vertex index
  int result=h->A[1].fi;
  swap(&(h->A[1]),&(h->A[h->heapsize]));
  h->heapsize--;
  min_heapify(h,1);
  return result;

}

//prints elements from a min-heap in ascending order (NOTE this assumes heap is built already!)
void sort_and_kill(heap *h){
  if(h->heapsize==0){
    cout<<"No elements in the heap!\n\n";
    return;
  }
  cout<<"Sorted elements :: \n";
  int ret;
  while(h->heapsize > 0){
	ret=delete_min(h);
	cout<<ret<<" ";
  }
  cout<<'\n';
  return;
  
}

//adds a node with  given values of vertex index and weight to a given linked llist 
void add(int v,int w,llist *u){
 node *newn = (node *)malloc(sizeof(node));
 newn->first=v;
 newn->second=w;
 newn->next=u->head;
 u->head=newn;
}

//reads a given graph from stdin in Adjllist format
void read_graph(Graph* g){
 scanf("%d %d",&(g->V),&(g->E));
 //dynamically allocate an array of Linkedllists
 g->adjllist = (llist * )malloc((g->V)*sizeof(llist));
 for(int i=0;i<g->V;i++){
  g->adjllist[i].head=NULL;
 }
 int u,v,w;
 int c=0,num_edge=0;
 while(num_edge < g->E ){
  num_edge++;
  scanf("%d %d %d",&u,&v,&w);
  assert(w>=0);
  add(v,w,&(g->adjllist[u]));
 }
}


//initialise the dists to infinity 
void initialise_single_source(Graph *a,int source){
  for(int i=0;i<a->V;i++){
   dist[i]=(INT_MAX)/2;
   previous[i]=-1;
  }
  dist[source]=0;
  previous[source]=source;
  return;
}

//relax method-takes two vertices and the weight of the edge joining the two and relaxes the second
void relax(heap*h,int u,int v,int w){
  if(dist[v]>dist[u]+w){
   dist[v]=dist[u]+w;
   heap_decrease_key(h,heapindex[v],dist[v]);
   previous[v]=u;
  }
  return ;
}

//performs Dijkstra's algo on a graph with a given source
void dijkstra(Graph *g, int source){
  initialise_single_source(g,source);
  heap hh;
  heap* h=&hh;
  h->heapsize=g->V;
  for(int i=0;i<g->V;i++){
    //insert the vertex
    h->A[i+1].fi=i;
    //insert the dist
    h->A[i+1].se=dist[i];
    //initialise the indices of the vertices in the heap
    heapindex[i]=i+1;
  }
  swap(&(h->A[1]),&(h->A[heapindex[source]]));
  while(h->heapsize>0){
    int mini=delete_min(h);
    node* iterator=(g->adjllist[mini]).head;
    while(!(iterator==NULL)){
      relax(h,mini,iterator->first,iterator->second);
      iterator=iterator->next;
    }
 }
 return ;
}  

int main(){
  int i,j,source;
  out=fopen("out.txt","w");
  if( out==NULL){ 
    printf("Error in opening file\n\n");
    return 0;
  }
  Graph newgraph;
  Graph *g=&newgraph;
  read_graph(g);
  scanf("%d",&source);
  if(g->V !=0){
    dist=(int *)malloc((g->V)*sizeof(int));
    previous=(int *)malloc((g->V)*sizeof(int));
    heapindex=(int *)malloc((g->V)*sizeof(int));
    assert(heapindex);
    assert(dist);
    assert(previous);
    dijkstra(g,source);
    fprintf(out,"Printing shortest distances from vertex %d and parents in a shortest path tree.\n\n",source);
    for(i=0;i<(g->V);i++)
    {
      if(dist[i]<(INT_MAX)/2)  
        fprintf(out,"Distance of vertex %d is :: %d ; PARENT :: %d \n ",i,dist[i],previous[i]);
      else
        fprintf(out,"Distance of vertex %d is INFINITY\n",i);
    }    
  }
  else fprintf(out,"Graph is empty\n");
  printf("  Output is in file \"out.txt\" \n\n");
  fclose(out);
  return 0;
}
