/*
    Programmer : Arko Sharma
    Roll       : 111601002
    Task       : Given a undirected graph (no of vertices followed by no of edges followed by edgellist ; perform Kruskal's 			 algorithm to print the edges of the MST.
    Date       : 13.02.2018
                 

*/

#include<bits/stdc++.h>
#include<cassert>
#define PARENT(i) (i)/2
#define LEFT(i) 2*(i)
#define RIGHT(i) 2*(i)+1
using namespace std;
int *parent,*rank;


void makeset(int u){
  parent[u]=u;
}
//find by path-compression
int find(int u){
  return u==parent[u] ?  u : (parent[u]=find(parent[u]));
}


void union_byrank(int u,int v){
  int ru=rank[u];
  int rv=rank[v];
  int pu=find(u);
  int pv=find(v);
  
  if(ru==rv){
    parent[pu]=pv;
    rank[pv]++;
  }
  else if(ru<rv){
    parent[pu]=pv;
  }
  else{
    parent[pv]=pu;
  }
}

//defines a structure to hold a 3-tuple of integers
typedef struct triple{
  //(vertex indices,weight)
  int fi;
  int se;
  int thi;

}triple;


//heap structure (each node is a 3-tuple )
typedef struct heap{
  triple A[101];
  int heapsize;
}heap;

//swap the contents of addresses of two tuples 
void swap(triple *a,triple *b){
  triple temp=*a;
  *a=*b;
  *b=temp;
}


FILE *out;


//Graph structure
typedef struct Graph{
 int V;
 int E;
 triple *elist;
}Graph;

//perform min-heapify on a given array with a specified root position-use the key(third attribute) 
void min_heapify(heap *h,int pos_root){
  int l=LEFT(pos_root);
  int r=RIGHT(pos_root);
  int smallest=pos_root;
  if(l <= h->heapsize && h->A[l].thi <h->A[pos_root].thi){
    smallest=l;
  }
  if(r<= h->heapsize && h->A[r].thi <h->A[smallest].thi){
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
  if(key > h->A[i].thi){
    cout<<"Decrease-key operation failed\n\n";
    return 1;
  }
  h->A[i].thi=key;
  while(i>1 && h->A[PARENT(i)].thi >h->A[i].thi){
    swap(&(h->A[PARENT(i)]),&(h->A[i]));
    i=PARENT(i);
  }
  return 0;
}


//deletes and returns the minimum edge
triple delete_min(heap *h){
  triple result;
  result.fi=result.se=result.thi=-1; 
  if(h->heapsize < 1){
    cout<<"Heap underflow\n\n";
    return result;
  }
  // first attribute is vertex index
  result=h->A[1];
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
  triple ret;
  while(h->heapsize > 0){
	ret=delete_min(h);
	cout<<ret.thi<<" ";
  }
  cout<<'\n';
  return;
  
}

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

//performs Kruskal's algo on a graph with a given edge list
void Kruskal(Graph *g){
  heap hh;
  heap* h=&hh;
  h->heapsize=g->E;
  for(int i=0;i<g->V;i++){
    makeset(i);
  }
  for(int i=0;i<g->E;i++){
    //insert the vertices
    h->A[i+1].fi=g->elist[i].fi;
    h->A[i+1].se=g->elist[i].se;
    //insert the key
    h->A[i+1].thi=g->elist[i].thi;
  }
  build_heap(h);
  int count=0;
  while(count < (g->V) -1 ){
    assert(h->heapsize > 0);
    triple mini=delete_min(h);
    if(find(mini.fi)!=find(mini.se)){
      union_byrank(mini.fi,mini.se);
      fprintf(out,"Adding edge %d--%d \n",mini.fi,mini.se);
      count++;
    }
 }
 return ;
}  

int main(){
  out=fopen("out.txt","w");
  assert(out!=NULL);
  Graph newgraph;
  Graph *g=&newgraph;
  read_graph(g);
  if(g->V !=0){
    rank=(int *)malloc((g->V)*sizeof(int));
    parent=(int *)malloc((g->V)*sizeof(int));
    assert(rank);
    assert(parent);
    memset(rank,0,sizeof(rank));
    fprintf(out,"Printing a MST by Kruskal's algorithm .\n\n");
    Kruskal(g);
        
  }
  else fprintf(out,"Graph is empty\n");
  printf("  Output is in file \"out.txt\" \n\n");
  fclose(out);
  return 0;
}

