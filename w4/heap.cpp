/*
    Programmer : Arko Sharma
    Roll       : 111601002
    Q          : Write a menu driven Program to :
                  1. Build a min-heap from an array(using repeated min_heapify)
                  2. Insert an element
                  3. Delete the minimum
                  4. Heapsort(should destroy the heap)
                  5. Display the heap as a rooted tree
    Date       : 19.01.2018


*/

#include <bits/stdc++.h>
#define PARENT(i) (i)/2
#define LEFT(i) 2*(i)
#define RIGHT(i) 2*(i)+1
#define COUNT 10
using namespace std;

//heap structure
typedef struct heap{

  int A[101];
  int heapsize;
}heap;

//swap the contents of addresses of two ints
void swap(int *a,int *b){
  int temp=*a;
  *a=*b;
  *b=temp;
}

//perform min-heapify on a given array with a specified root position
void min_heapify(heap *h,int pos_root){
  int l=LEFT(pos_root);
  int r=RIGHT(pos_root);
  int smallest=pos_root;
  if(l <= h->heapsize && h->A[l]<h->A[pos_root]){
    smallest=l;
  }
  if(r<= h->heapsize && h->A[r]<h->A[smallest]){
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
  if(key>h->A[i]){
    cout<<"Decrease-key operation failed\n\n";
    return 1;
  }
  h->A[i]=key;
  while(i>1 && h->A[PARENT(i)]>h->A[i]){
    swap(&(h->A[PARENT(i)]),&(h->A[i]));
    i=PARENT(i);
  }
  return 0;
}


//insert a node with a given key value in a given heap
void insert_key(heap *h,int key){
  int ret=-1;
  h->heapsize=h->heapsize+1;
  h->A[h->heapsize]=INT_MAX;
  ret=heap_decrease_key(h,h->heapsize,key);
  if(ret==1){
    cout<<"Insert operation failed \n\n";
  }
  return ;
}
//deletes and returns the minimum element of a min-heap
int delete_min(heap *h){
  if(h->heapsize < 1){
    cout<<"Heap underflow\n\n";
    return -1;
  }
  int result=h->A[1];
  h->A[1]=h->A[h->heapsize];
  h->heapsize--;
  min_heapify(h,1);
  return result;

}

//prints elements from a min-heap in ascending order (NOTE this assumes heap if built already!)
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
void print_recursive(heap *h ,int root,int space){
  // Base case
  if(root > h->heapsize)
    return;
  
  // Increase distance between levels
  space+=COUNT;
  // Process right child first
  print_recursive(h,RIGHT(root), space);
  // Print current node after space
  cout<<"\n";
  for(int i = COUNT; i < space; i++)
    cout<<" ";
 
  cout<<h->A[root];
  // Process left child
  print_recursive(h,LEFT(root),space);
}

//displays the heap as a rooted tree
void display_heap(heap *h){
  if(h->heapsize==0){
    cout<<"No elements in the heap!\n\n";
    return ;
  }
  cout<<"################################################################################\n";
  print_recursive(h,1,0); 	
  cout<<"\n################################################################################\n";
  
  cout<<"\n\n";
}


int main() {
  ios_base::sync_with_stdio(false);
  //cin.tie(nullptr);  
  int choice=0,i,ret,ele;
  heap h;
  h.heapsize=0;
  while(1){
	  cout<<"\n Enter the choice \n\n1. Build a heap from an array\n2. Insert an element\n3. Delete the minimum\n4. Heapsort(would destroy the heap)\n5. Display the heap as a rooted tree\n6.  -1 to exit \n\n";
	  cin>>choice;
	  if(choice==-1) exit(0);
	  switch(choice)
	  {
		case 1:
		 cout<<"Enter the number of elements\n";
		 cin>>h.heapsize;
		 while(!(h.heapsize>0 && h.heapsize <=100))
		 {
		   cout<<"Invalid heapsize.Please try again\n";
		   cin>>h.heapsize;
		 }
		 //now heapsize is valid
		 cout<<"Enter the elements of the heap : \n";
		 for(i=1;i<=h.heapsize;i++){
		   cin>>h.A[i];
		 }
		 build_heap(&h);
		 break;

		case 2:
		  cout<<"Enter an element to insert :  ";
		  cin>>ele;
		  insert_key(&h,ele);
		  break;
		case 3:
		  ret=delete_min(&h);
		  if(ret!=-1)
		  cout<<"The deleted element is "<<ret<<"\n\n";
		  break;
		case 4:
		  sort_and_kill(&h);
		  break;
		case 5:
		  display_heap(&h);
		  break;
		default: cout<<"__INVALID choice__\n\n";
	 }
  }
  return 0;
}
