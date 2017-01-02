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
   int value; //groupValue
   String *start, *end;
   group()
   {
      value=0;
      start=end=NULL;
   }
   void add(String *s,int value)
   {
       start=end=s;
       s->next=NULL;
       this->value=value;
   }
   
   void append(char ch)
   { 
       String *temp=start;
       while(temp!=NULL)
       {
           temp->str[temp->index++]=ch;
           temp=temp->next;
       }
   }
   
   void display()
   {
       String *temp=start;
       while(temp!=NULL)
       {
          //cout<<"|"<<temp->str<<"|  ";
          temp=temp->next;
       }
   }
};

void merge(group *g2, group *g1)
{
    g1->end->next=g2->start;
    g1->end=g2->end;
    g1->value=g1->value+g2->value;
    g2->value=0;
    
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
         gp[j++].add(&(codes[i]),arr[i]);
      }
   }
   
   for(int m=0;m<j;m++)
   {
      //cout<<gp[m].value<<"\t";
   }
   
   int k=0;
   unsigned int *indexes=new unsigned int[2];
   while(k<n-1)
   { 
     
        get2LeastIndexes(gp,n,indexes);
        gp[indexes[0]].append('0');
        gp[indexes[1]].append('1');
        gp[indexes[0]].display();
        gp[indexes[1]].display();
        k++;
        merge(&gp[indexes[0]],&gp[indexes[1]] );
   }
       gp[indexes[1]].append('\0'); 
   for(int i=0;i<256;i++)
   {
          strrev(codes[i].str);
   }
}












