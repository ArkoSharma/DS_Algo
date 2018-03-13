#include<bits/stdc++.h>
#include<fstream>
using namespace std;
int main(){
 int i,j;
 ofstream fout;
 fout.open("in.bin",ios::binary|ios::trunc);
 freopen("in.txt","w",stdout);
 srand(time(NULL));
 for(i=0;i<1000000;i++){
   j=rand()%INT_MAX;
   cout<<j<<' ';
   fout.write(reinterpret_cast<char *>(&j),sizeof(int));
 }
 fout.close();
}
