
/*
Program Author -- Arko Sharma
Date           -  17/10/2017

Topic          - Graphs( Experiment 2 Problem 1)

Function       - Makes a dot file with 5 coloring( 5 or less colors ) of a given planar graph
*/


//in this program the adjacency matrix is used to keep track of neighbours of a vertex !



#include <stdio.h>
#include <stdlib.h>
#define pi(n) printf(" %d ",n)
#define fo(i,a,b) for(i=a;i<b;i++)
//vertices have 3 attributes , viz, color,value,distance
typedef struct vertex {
    
    int value;               // the label of the vertex
    char color;              // can be White, Gray ,Black
    int  dist;               // distance from source in BFS
    int par;                 // the parent in BFS tree
}ver;
typedef struct vertex* verp;

typedef struct nodee
{
  //nodes for the circular queue
  int data;
  struct nodee *next;
}nod;
typedef  nod *nodp;
typedef struct queue
{
  nodp front;
  nodp rear;
}qu;
typedef qu *queue;// pointers to struct "queue" will be called queue

typedef struct Node{
  int data;
  struct Node *next;
}node;
void add_node_at_head(node **head_r,node **tail_r,int value){ // head_r stores reference to head pointer.
        
          node * a=(node*)malloc(sizeof(node));
        
          a->data=value;
          if(*head_r == NULL) //ie first node
          {
           *tail_r=a;
          }
          else
           a->next=*(head_r);                   //new node's "next" pointer points to the node of previous "head" pointer  
          *head_r=a;                           // the "head" pointer points to newly added node
          (*tail_r)->next=a;                   // tail_r keeps track of the last node which finally points back to the newly added node
          return;
         
}
void print_data(node **start){

/*the function  prints the circular linked list starting from any node ,the reference to whose address is in "start"*/
          if(*start==NULL){           
            printf("The list is empty\n\n");
            return;                            //since nothing to print
          }
          node *first_pointer=  *start;
          node *cur_pointer=    *start;                   // now "cur_point" will traverse through,until it reaches "first_pointer" again
          printf("------------------------------------------------------------------\nhead-->");
          do{//do while loop as initially both pointers are same 
        
            printf(" %d -->",cur_pointer->data);
            cur_pointer=cur_pointer->next;              //following each "next" pointer to get next node.     
          }
          while(cur_pointer != first_pointer);
          printf("HEAD\n------------------------------------------------------------------\n\n");
          return;
}
queue newQueue(){
  //creates a new queue and returns its reference
  queue q=(queue)malloc(sizeof(qu));
  q->front=NULL;
  q->rear=NULL;
  return q;
}

int queueIsEmpty(queue q){
  //returns 1 if empty and 0 if not
  
  // doesn't change the queue so no need of pointer, but 
  //pass by reference saves memory as new structure not created
  if(q->front==NULL)
    return 1;
  else
    return 0;
}
int queueSize(queue q){
    //returns no of elements in the queue
  
  // doesn't change the queue so no need of pointer, but 
  //pass by reference saves memory as new structure not created
  
  
  int siz=0;
  nodp start=q->front;
  while(start!=NULL){
    siz++;
    if(start == q->rear)
      break;
    else
      start=start->next;
  }
  return siz;
}
void enQueue(queue q,int x){
  //takes a queue reference and adds x as a new node to it
  //note q is circular
    nodp np=(nodp)malloc(sizeof(nod));
    np->data=x;
    //fifo so insert at rear
    if(queueIsEmpty(q)==1){
      //if empty
      q->front=np;
    }
    else{
      q->rear->next=np;
    }
    q->rear=np;
    q->rear->next=q->front;
    return;
}
int deQueue(queue q){
    
  //takes reference of a queue, deletes front node, returns its "data"
  
  //since it changes the queue so it takes a pointer to the queue
  if(queueIsEmpty(q)==1)
  {
     
      printf("fatal error! queue is empty!\n");
    return -1111;
  }

  int temp=q->front->data;//for returning
  nodp temp1=q->front;  //for freeing

  if(queueSize(q)==1){
    //only 1 node
      q->front=NULL;
      q->rear=NULL;
  }
  else{
    //more than 1 nodes
    q->front=q->front->next;
    q->rear->next=q->front;
  }
  free(temp1);
  return temp;
}
 void queueFront(queue q){
  //prints front of the queue
  
  
  // doesn't change the queue so no need of pointer, but 
  //pass by reference saves memory as new structure not created
  
  
  if(queueIsEmpty(q)){
    printf("queue is empty!!\n\n");
  }
  else
    printf("%d\n",q->front->data );
  return ;
}
void free_memory(queue q){
    while(queueIsEmpty(q)!=1){
    int a=deQueue(q);
  }
  return ;
}

/*function to fill in required "value" attributes as vertex-labels*/
void mark_labels(verp v,int size){
    
    int i;
    fo(i,0,size){
        v[i].value=i;  //here labels are the indices themselves
    }
    
}

/*BFS function*/
/* the matrix "a " contains the adjacency matrix whereas the array v is the array of attributes  of vertices*/

void BFS(int a[][100],int source,int size,FILE *foo,int visited[],verp v){
    
    int i,u,j,neighbours;
    
    //note in initialising the attributes it is assumed that the graph is connected
    // so it is important not to use these attributes to determine the connectivity of the graph
    fo(i,0,size){


        
        //initialise attributes of vertices except source
        if(i!=source){
            v[i].color='W';                    // White => unexplored
            v[i].dist= 100000;                 //max distance assumed 100000
            v[i].par=-1;
        }
    }
    // now for source
    // gray => not explored completely
    v[source].color='G';        
    v[source].dist=0;
    v[source].par=-1;

    visited[source]=1;
    qu que=*(newQueue());
    //push the source in queue ( in case labels of vertices are not indices , use v[source].value instead of source )
    enQueue(&que,source);        
    
    // while queue is not empty
    while(queueIsEmpty(&que)!=1){
        u=deQueue(&que);
        neighbours=0;
        //for each j adjacent to u
        fo(j,0,size){
            
            if(a[u][j]==1){
                //count neighbours
                neighbours++;
                //if j is unvisited
                if(visited[j]==0){
                    visited[j]=1;
                    enQueue(&que,j);
                    v[j].dist=v[u].dist+1;
                    v[j].par=u;
                    v[j].color='G';
                }
            }
            
            
        }
        v[u].color='B';
        visited[u]=1;
    }
    //finished processing all vertices reachable from source.Now queue is empty
    return ;
 }

/*function to read an adjacency matrix into a given array*/
/*takes array,size and file pointer as parameters*/
void populate_am(int a[][100],int size,FILE *fp){
     
     int i,j;
     fo(i,0,size){
         fo(j,0,size){
             fscanf(fp,"%1d",&a[i][j]);
         }
     }
     return;
}



/*functon to copy values of a matrix in another*/
void get_copy(int b[][100],int a[][100]){
    int i,j;
    fo(i,0,100){
        fo(j,0,100){
            a[i][j]=b[i][j];
        }
    }
    return;
}
/*returns any vertex index which has degree less than or equal to 5 and turns it off */
int get_del_max5_deg_vertex(int ad_mat[][100],int size,int turnoff[]){

    int max_deg_index=0,max_edges=0,i,j,num_edges;
    fo(i,0,size){
      num_edges=0;
      fo(j,0,size){
        if(turnoff[j]!=1 && ad_mat[i][j]==1){
          num_edges++;
        }
      }
      if(turnoff[i]!=1 && num_edges<=5){
        turnoff[i]=1;
        return(i);
      }

    }
    //if no turned on vertex with deg <=5 then non planar
    return -1; 
}
/* makes a vertex ordering as per degeneracy rule and stores in array*/
void make_ver_ordering(int ad_mat[][100],int v_ord[],int size){
    int max5_deg_vertex,i;
    int* turnoff=(int *)calloc(size,sizeof(int));
    int copy_mat[100][100];
    get_copy(ad_mat,copy_mat);
    fo(i,0,size){
       //IN a k-deg graph,every subgraph has a vertex of degree at least k
       //so we continually find and turnoff this vertex for k=5
       //get and delete the max 5 degree vertex
       max5_deg_vertex=get_del_max5_deg_vertex(copy_mat,size,turnoff);
       if(max5_deg_vertex==-1){
        printf(" ERROR the graph is non planar ! ");
        exit(0);
       }
       v_ord[size-i-1]=max5_deg_vertex;
    }
}
/* allocates color from 0 to numColors-1*/
void color_ordering(int ad_mat[][100],int ordering[],int size,int colrArr[],int numColors){
  
  //colArr elements are set to -1 initially
  

  //palette for 6 colors
  int palette[5];
  int i,j,k=0,currLast,seen_already[100];
  
  fo(i,0,size){
    seen_already[i]=0;
  }
  
  fo(i,0,size){

    fo(j,0,5){
      palette[j]=1;
    }    
    currLast=ordering[size-i-1];
    //if the current last of the subseq is uncolored
    if(colrArr[currLast]==-1){
      //then color it with 0 ( initially )
      colrArr[currLast]=0;
      
      
    }
    
    //now check its neibours that come before( not seen already ) in the seq
    fo(j,0,size){
      if(ad_mat[currLast][j]==1 && seen_already[j]!=1){
        
       //first color uncolored neigbours 
       if(colrArr[j]==-1){
          // ..with a color 1 higher than than currLast
          colrArr[j]=(colrArr[currLast]+1)%numColors;
          
          
        }
        
       }
    }
    fo(j,0,size){
      if(ad_mat[currLast][j]==1){
        
       //then check colored neighbours for conflict 
      if(colrArr[j]!= -1){
          palette[colrArr[j]]=0;
          
        }
        
      }
    }
    fo(j,0,5){
      if(palette[j]==1){
        //to use minimum no of colors
        break;
      }
    }
    
    colrArr[currLast]=j;
    seen_already[currLast]=1;

  }

  return;
}
/*function to generate the dot file in the given pointer from AM*/
void am_to_dot(int a[][100],int size,FILE *foo){
    
    
    int i,j,count=0;
    fo(i,0,size){
        count=0;
        fo(j,0,size){
            
            
            // if there is an edge ,, only for upper triangular matrix elememts: 
            if(i<=j && a[i][j]==1) {         
                   
                       
                   fprintf(foo,"\t%d --%d;\n",i,j);
                   count++;
                
            }
            
        }
        if(count==0){
            
            //print isolated vertices
            
            fprintf(foo,"%d",i);             
        }
        //at the end go to new line after semicolon
        fprintf(foo,"\n");
    }
    fprintf(foo,"}");
    return;
    
}


int main() {
    char file_name[100],dot_fil_name[20],gr_name[100],id[3];
    const char *colors[20];
    int *color,size,x,y,d=0,numConnectedComp=0,i,j,trigger,eul=1,v_ord[100];
    ver v[100];
    int a[100][100],b[100][100],degree[100],visited[100],isolated[100];//default max assumed to be 100
    FILE *fp=NULL,*foo=NULL;
    //cols in indices 1 through 6
    colors[0]="red3";
    colors[1]="darkviolet";
    colors[2]="darkgoldenrod1";
    colors[3]="cyan";
    colors[4]="deeppink";
    colors[5]="forestgreen";
    

        
        printf("Enter the name of the file containing the graph\n(default max assumed to be 100 vertices!)\n\n");
        scanf(" %[^\n]s",file_name);
        fp=fopen(file_name,"r");
        if(fp==NULL){
            printf("Error in opening file \n\nExiting program \n\n");            
            return 0;
        }
        //reading from the user-entered file
        
        
    
      
        fscanf(fp," %[^\n]s",gr_name);
        // id contains either AM or AL 
        fscanf(fp," %[^\n]s",id);     
        fscanf(fp,"%d",&size);   

        // if the id is AM
        printf("Enter the name of the file for 5 coloring\n");
        scanf(" %[^\n]s",dot_fil_name);
        foo=fopen(dot_fil_name,"w");
        if(foo==NULL){
          printf("Error in opening file !");
          return 1;
        }
        
        if(id[1]=='M'){      
           
            //then populate the adj matrix  "b" 
            populate_am(b,size,fp); 

            //do operations on the adj matrix in here
            make_ver_ordering(b,v_ord,size);
            
            //coloring will be done in indices 0 to 5 
            color=(int *)(malloc(size*sizeof(int)));
            fo(i,0,size){
              color[i]=-1;
            }
            color_ordering(b,v_ord,size,color,5);
            fprintf(foo,"graph coloring{\n");
            fo(i,0,size){
              fprintf(foo,"%d[color=%s,style=filled]\n",i,colors[color[i]]);
            }
            am_to_dot(b,size,foo);
          }
        fclose(fp);
        fclose(foo);
        return 0;
}
