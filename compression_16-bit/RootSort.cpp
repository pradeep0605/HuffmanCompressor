#include<iostream>
#include "tree.cpp"


unsigned int * get2LeastIndexes(node arr[],unsigned int n)
{ 
   unsigned int least=arr[0].value;
   unsigned int index1=0,index2=0;
   for(int i=1;i<n;i++)
   {
      if(arr[i].value<=least && arr[i].value!=0)
      {
         least = arr[i].value;
         index2=index1;
         index1=i;
      }
   }
   unsigned int *indexes=new unsigned int [2];
   indexes[0]=index1;
   indexes[1]=index2;
   return indexes;
}

node *  constructTree(node arr[],unsigned int n)
{ 
    int k=0,i,j;
    unsigned int firstIndex=0,secondIndex=0;
    unsigned int *indexes=new unsigned int[2];
    while(k<n)
    {   
      
        indexes=get2LeastIndexes(arr,n);
        
        firstIndex=indexes[0];
        secondIndex=indexes[1];
        
        node *left=new node(arr[firstIndex]);
        node *right=new node( arr[secondIndex] ); 
        
        arr[firstIndex]=node();
             
        arr[secondIndex].lchild=left;
        arr[secondIndex].rchild=right;
        arr[secondIndex].value=left->value+right->value;
        arr[secondIndex].ch=-1;
        k++;
    }
    
    return &arr[secondIndex];
}













