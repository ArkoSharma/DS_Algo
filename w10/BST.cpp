/*
    Programmer : Arko Sharma
    Roll       : 111601002
    Task       : Write a menu based program to implement a (unique key) binary search tree with the following operations :
			
			1. Searching for a key (say "found" if key is present in the tree and "not found" otherwise 
			2. Inserting a key (avoid duplicates)
			3. Findminkey
			4. InOrderTraversal
			5. PostOrderTraversal
			6. FindPrecedingKey (should print "no predecessor" if the key given is the minimum otherwise print 					the preceding key in inorder traversal. )
			7. DeleteKey
			8. PrintTree 
    
    Date       : 08.03.2018
           
*/

#include <bits/stdc++.h>
#define COUNT 10
using namespace std;


// Nodes of BinarySearchTree
typedef struct node {
  
  struct node* parent;
  struct node* left;
  struct node* right;
  int key;
  int height; 
}node;

typedef struct BST {
  node *root;
}BST;


// inserts a node with the given key value to the BST rooted at T
node* insert_unique(node* T, int key) {


  //T has no subtree
  if(T == NULL) {                                 
    node* newnode=(node*)malloc(sizeof(node));
    assert(newnode);
    newnode->key = key;
    newnode->parent = newnode->left = newnode->right = NULL;
    newnode->height = 0; 
    T=newnode;
  }
  
  //else first check left subtree
  else if (T->key > key) { 
    T->left = insert_unique(T->left, key);
    T->left->parent = T;
  }
  //else right subtree
  else{
    T->right = insert_unique(T->right, key);
    T->right->parent = T;
  }
  return T;                                          
}

//prints nodes in an inorder traversal of the BST rooted at T
void inorder(node* T) {

  if(T == NULL) return;
    inorder(T->left);                              
    cout<< T->key << ' ';                          
    inorder(T->right);                            
}
//prints nodes in an postorder traversal of the BST rooted at T
void postorder(node* T) {
  if(T == NULL) return;
    postorder(T->left);                              
    postorder(T->right);
    cout<< T->key << ' ';                          
}


//returns the minimum key value in the BST rooted at T
int FindMinKey(node* T) {
    
    if(T == NULL)
      // BST is empty
      return -1;             
    else if (T->left == NULL) return T->key;
    //go left recursively
    else return FindMinKey(T->left);         
}

int FindMaxKey(node* T) {
    if (T == NULL)        return -1;          
    else if (T->right == NULL) return T->key;           
    else                       return FindMaxKey(T->right);
}

//prints the BST rooted at T as a rooted tree
void print_recursive(node *T ,int space){
  // Base case
  if(T ==NULL)
    return;
  
  // Increase distance between levels
  space+=COUNT;
  // Process right child first
  print_recursive(T->right, space);
  // Print current node after space
  cout<<"\n";
  for(int i = COUNT; i < space; i++)
    cout<<" ";
  cout<<T->key;
  // Process left child
  print_recursive(T->left,space);
}


//checks for presence of key 'v' in the BST rooted at v 
//returns a pointer to the node containging the key; else returns NULL 
node* search(node* T, int v) {
    //not found if T becomes NULL
    if(T == NULL) 
    { 
      return T;
    }
    else if (T->key == v) {
     return T;
    }
    //if current key is less then go to right subtree
    else if (T->key < v)  return search(T->right, v);  
    //else go left
    else return search(T->left, v);  
}


//inorder successor
int successor(node* T) { 
    // if right subtree is present
    if (T->right != NULL)                      
      return FindMinKey(T->right); 
    else {
      node* par = T->parent;
      node* cur = T;
      // if parent is not root and current is its right children
      while ((par != NULL) && (cur == par->right)) {
        cur = par;                                         
        par = cur->parent;
      }
      return par == NULL ? -1 : par->key;
    }
}




//returns the predecessor of the node having given "key" in inorder traversal
int FindPrecedingKey(node* T){
    // if left subtree is present
    if (T->left != NULL)       
      // the predecessor is the maximum of left subtree                 
      return FindMaxKey(T->left); 
    else {
      node* par = T->parent;
      node* cur = T;
      // if parent is not root and current is its left child
      while ((par != NULL) && (cur == par->left)) { 
        // continue moving up
        cur = par;
        par = cur->parent;
      }
      return par == NULL ? -1 : par->key;
    }
}


//removes the node having the passed key from the BST rooted at T and returns the updated BST
node* delete_node_withkey(node* T, int v) {
  // cannot find the item to be deleted
  if (T == NULL)  return T;              

  // if this node has to be deleted
  if(T->key == v){
    //if it's a leaf
    if(T->left == NULL && T->right == NULL)
        // delete 
        T = NULL;                                      

    //else if only right subtree present
    else if (T->left == NULL && T->right != NULL) { 
    

      T->right->parent = T->parent;
      T = T->right;
    }
    //only left subtree present
    else if (T->left != NULL && T->right == NULL) {
        T->left->parent = T->parent;           
        T = T->left;                           
      }
      
    //both children present; taking inorder successor 
    else{
       
       node* search_node=search(T,v);
       int successorV = successor(search_node);
        // replace this key with the successor's key
        T->key = successorV;
        // delete the old successorV
        T->right=delete_node_withkey(T->right, successorV);    
      }
    }
    // search to the right
    else if (T->key < v)                                  
      T->right=delete_node_withkey(T->right, v);
    else                                                  
    // search to the left
      T->left=delete_node_withkey(T->left, v);
    return T;
}


int main(){

  int choice,key,result;
  BST newBst;
  node* search_node;
  node *res;
  BST *T=&newBst;
  T->root=NULL;
  while(1){

   cout<<"\nEnter choices as follows\n\n1. Searching for a key \n2. Inserting a key (avoid duplicates)\n3. Findminkey\n4. InOrderTraversal\n5. PostOrderTraversal\n6. FindPrecedingKey\n7. DeleteKey\n8. PrintTree \n0. EXIT\n\n";
   
   cin>>choice; 
   switch(choice){
     
     case 1:
       cout<<"Enter key value to be searched :\n";
       cin>>key;
       res = search(T->root, key);
       if( res == NULL )
         cout<<"NOT FOUND\n\n";
       else cout<<"FOUND\n";
       break;
     
     case 2:
       cout<<"Enter the key value to insert(avoid duplicates)\n\n";
       cin>>key; 
       T->root = insert_unique(T->root, key);
       break;
      
     case 3:
       result=FindMinKey(T->root);
       if(result!=-1)
         cout<<"Minimum key is "<<result<<"\n";
       else
         cout<<"Tree is empty\n";
       break;
       
     case 4:
       if(T->root!=NULL){
         cout<<"Inorder Traversal\n\n";
         inorder(T->root);
         cout<<"\n";
       }
       else cout<<"Tree is empty\n";
       break;
       
     case 5:
       if(T->root!=NULL){
         cout<<"Postorder Traversal\n\n";
         postorder(T->root);
         cout<<"\n";
       }
       else cout<<"Tree is empty\n";
       break;
       
     case 6:
       cout<<"Enter the key whose inorder predecessor is to be found\n";
       cin>>key;
       search_node=search(T->root,key);
       result=FindPrecedingKey(search_node);  
       if(result==-1) cout<<"No predecessor\n";
       else cout<<"Inorder predecessor is "<<result<<"\n";
       break;
       
     case 7:
       cout<<"Enter the key of the node to be deleted\n";
       cin>>key;
       T->root=delete_node_withkey(T->root,key);
       break;
       
     case 8:
       cout<<"Tree is as follows :: \n\n";
       print_recursive(T->root,0);
       cout<<"\n";
       break;
       
     case 0:
       exit(0);
    }
   }
}

