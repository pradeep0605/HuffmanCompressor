#include<iostream>
#include "tree.cpp"
#include<cstring>


using namespace std;

void strrev(char *s)
{
   short tp=0;
   char temp[tp=strlen(s)];
   strcpy(temp,s);
   int k=0;
   for(int i=tp-1;i>=0;i--)
   {
     s[k++]=temp[i];
   }
//   s[k]='\0';
}

class group
{
   public:
   short value; //groupValue
   short *indexes;
   short indx;
   group()
   {
      value=indx=0;
      indexes=new short[256];
      
   }
   void add(int index,int value)
   {
       this->value=value;
       indexes[indx++]=index;
   }
   
   void append(String *codes,char ch)
   { 
       for(int i=0;i<indx;i++)
       { 
           codes[indexes[i]].str[codes[indexes[i]].index++]=ch;
       }
         
   }
   
   void display(String *codes)
   {
         for(int i=0;i<indx;i++)
         {
             cout<<"|"<<char(indexes[i])<<" :  "<<codes[indexes[i]].str<<"| ";
         }
         cout<<endl;
   }
};

void merge(group &g2, group &g1)
{
    for(int i=0;i<g2.indx;i++)
    {
        g1.indexes[g1.indx++]=g2.indexes[i];
    }
    g1.value=g1.value+g2.value;
    g2.value=0;
    //delete [] g2.indexes;
}


void get2LeastIndexes(group *arr,unsigned int n,unsigned int *indexes)
{ 
   unsigned int least=arr[0].value;
   unsigned int index1=0,index2=0,i;
   for(i=1;i<n;i++)
   {
      if(arr[i].value<=least && arr[i].value>0)
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


void generateCodes(unsigned int *arr,String *codes,int n)
{
   group *gp=new group[n];
   int j=0;
   for(int i=0;i<256;i++)
   {
      if(arr[i]>0)
      {
         gp[j++].add(i,arr[i]);
      }
   }
   /*
   for(int m=0;m<j;m++)
   {
      cout<<gp[m].value<<"\t";
   }*/
   
   int k=0;
   unsigned int *indexes=new unsigned int[2];
   while(k<n-1)
   { 
     
        get2LeastIndexes(gp,n,indexes);
        //cout<<"\nindex[0]=" << indexes[0]<<"\tindex[1]="<<indexes[1];
        gp[indexes[0]].append(codes,'0');
        gp[indexes[1]].append(codes,'1');
        /*gp[indexes[0]].display(codes);
        gp[indexes[1]].display(codes);*/
        k++;
        merge(gp[indexes[0]],gp[indexes[1]] );
        //cout<<"\t"<<gp[indexes[1]].value;
        
   }
       gp[indexes[1]].append(codes,'\0'); 
   for(int i=0;i<256;i++)
   {
          strrev(codes[i].str);
   }
}












