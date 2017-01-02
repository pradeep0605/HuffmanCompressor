#include<iostream>
#include "tree.cpp"

using namespace std;
/*
int root_partition(node *, int, int);


void rootSort(node arr[],int l,int r)
{
   if(l<r)
   {
      int p=root_partition(arr,l,r);
      rootSort(arr,l,p-1);
      rootSort(arr,p+1,r);
   }
}

int root_partition(node a[],int l,int r)
{   
   int i=0,j=0;
   node pivot=a[l];
   i=l+1;
   j=r;
   while(i<=j)
   { 
      while(a[i].value<=pivot.value && i<r)
      {
         i++;
      }
      while(a[j].value>=pivot.value && j>l)
      {
         j--;
      }
      if(i<j)
      {
         node *temp=new node();
         *temp=a[i];
         a[i]=a[j];
         a[j]=*temp;
         continue;
      }
      else
      {
         break;
      }
   }
   a[l]=a[j];
   a[j]=pivot;
   return j; 
}*/


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
        
        /*for(int i=0;i<n;i++)
        { 
           cout<<"|"<<(unsigned short)i<<":"<<arr[i].value<<"|  ";
        }
        cout<<endl;
        cout<<"firstINdex:"<<firstIndex<<"  secondIndex:"<<secondIndex<<endl<<endl;
        */
        node *left=new node(arr[firstIndex]);
        node *right=new node( arr[secondIndex] ); 
        left->leaf=true;
        right->leaf=true;
        
        arr[firstIndex]=node();
             
        arr[secondIndex].lchild=left;
        arr[secondIndex].rchild=right;
        arr[secondIndex].value=left->value+right->value;
        arr[secondIndex].ch=-1;
        arr[secondIndex].leaf=false;
        k++;
    }
    
    return &arr[secondIndex];
}













