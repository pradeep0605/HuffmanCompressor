#include<iostream>
#include "tree.cpp"

using namespace std;

void get2LeastIndexes(node *arr,unsigned int n,unsigned int *indexes)
{ 
   unsigned int least=arr[0].value;
   unsigned int index1=0,index2=0,i;
   for(i=1;i<n;i++)
   {
      if(arr[i].value<=least && arr[i].value!=0)
      {
         least = arr[i].value;
         index2=index1;
         index1=i;
      }
   }
   
   least=-1;

   if(index1==index2)
   {
      for(i=0;i<n;i++)
      {
         if(arr[i].value<=least && i!=index1 && arr[i].value>0)
         {
            index1=i;
            least=arr[i].value; 
         }
      }
   }   
   indexes[0]=index1;
   indexes[1]=index2;
}

node *  constructTree(node *arr,unsigned int n)
{ 
    int k=0;
    unsigned int firstIndex=0,secondIndex=0;
    unsigned int *indexes=new unsigned int[2];
    cout.precision(3);
    cout<<endl;
    
    while(k<n-1)
    {   
      
        get2LeastIndexes(arr,n,indexes);
        
        firstIndex=indexes[0];
        secondIndex=indexes[1];
        
        /*if(firstIndex==secondIndex)
        {
         for(int i=0;i<n;i++)
         { 
            cout<<"|"<<(unsigned short)arr[i].ch<<":"<<arr[i].value<<"|  ";
         }
         cout<<endl;
         cout<<"firstINdex:"<<firstIndex<<"  secondIndex:"<<secondIndex<<endl<<endl;
        }*/
        node *left=new node(arr[firstIndex]);
        node *right=new node( arr[secondIndex] ); 
                          
        arr[firstIndex].ch=0;
        arr[firstIndex].value=0;
               
        arr[secondIndex].lchild=left;
        arr[secondIndex].rchild=right;
        arr[secondIndex].value=left->value + right->value;
        arr[secondIndex].ch=0;
        
        if ( k%15 ==0 ) 
        {
           cout<<"\r"<< (  float(k)/(n-2))*100<<" %";
        } 
        k++; 
    }
    
    return &arr[secondIndex];

}













