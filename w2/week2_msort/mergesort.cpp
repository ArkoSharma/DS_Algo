
/*
    Programmer : Arko Sharma
    Roll       : 111601002
    Task       : Perform external sorting by top down iterative merge sort process on an input binary file and create a readable output.
    Date       : 17.01.2018
                 

*/
#include <bits/stdc++.h>
#include <fstream>
using namespace std;
int main(){
    FILE *fin,*fim,*fout;           
    int i,j,size,blocksize, ele1,ele2 ,lcount = 0,rcount = 0,r,s, value;
    
    fin = fopen("in.bin","rb+");
    if(fin == NULL)
    {
     printf("Cannot open file!\n");
     return 0;
    }
    fseek(fin,0,SEEK_END);          
    //no of integers in the binary input file 
    size = ftell(fin)/sizeof(int);
    int flag = 0;

    fclose(fin);
    //blocksize is the size of the equal partitions
    for(blocksize = 1;blocksize <= size;blocksize = 2*blocksize)      
    {
	  //flag keeps track of which file to read from and  write to
      if(flag == 0)               
      {
       fin = fopen("in.bin","rb");
       fim = fopen("in.bin","rb");
       fout = fopen("buffer.bin","wb");
       flag = 1;
      }
      else
      {
       fout = fopen("in.bin","wb");
       fin = fopen("buffer.bin","rb");
       fim = fopen("buffer.bin","rb");
       flag = 0;
      }
      //traverse through the array as below
      for(i = 1;i <= size;i+=2*blocksize)     
      {
       fseek(fin,(i-1)*sizeof(int),SEEK_SET);
       fseek(fim,(i+blocksize-1)*sizeof(int),SEEK_SET);
       lcount = rcount = 0;
       //r,s store the limits of left and right partition respectively
       if((i+blocksize-1) > size)          
       {                           
        r = size - (i-1);
        s = 0;                  
        
       }
       else if((size - (i+blocksize-1)) < blocksize)
       {
        r = blocksize;
        s = size - (i+blocksize-1);
       }
       else
       {
        r = s = blocksize;
       }
       fread(&ele1,sizeof(int),1,fin);            
       fread(&ele2,sizeof(int),1,fim);
       
       //merge the partitions
       while(lcount < r && rcount < s)    
       {
        if(ele1<ele2)        
        {
         fwrite((char *)&ele1,sizeof(int),1,fout);
         fread(&ele1,sizeof(int),1,fin);
         lcount++;
        }
        else
        {
         fwrite((char *)&ele2,sizeof(int),1,fout);
         fread(&ele2,sizeof(int),1,fim);
         rcount++;
        }

       }
       while(lcount < r)
       {
        fwrite((char *)&ele1,sizeof(int),1,fout);
        fread(&ele1,sizeof(int),1,fin);
        lcount++;
       }
       while(rcount < s)
       {
        fwrite((char *)&ele2,sizeof(int),1,fout);
        fread(&ele2,sizeof(int),1,fim);
        rcount++;
       }
        
      }
      fclose(fin);
      fclose(fim);
      fclose(fout);
    }
    FILE *out,*out1;   
    out = fopen("output.txt","w");
    if(flag == 0)
    {
        out1 = fopen("in.bin","rb");
    }
    else
    out1 = fopen("buffer.bin","rb");
    for(i = 0;i < size;i++)
    {
     fread(&value,sizeof(int),1,out1);
     fprintf(out,"%d ",value);
    }
    fclose(out);
    fclose(out1);
    return 0;
}
