
/* For performance improvement I cant do the following things
  1. better sorting alogrith thatn quick sort.
  2. Or to eliminate sorting.
  3. Have least access to the hard disk as it increases the execution time.
  4. Remove as many couts as possible.
  5. Remove waste  code.
  */
 
#include<iostream>
#include<fstream>
#include<bitset> 
#include "bitHandling.cpp"
#include "table.cpp"
#include "treeGenerator.cpp"

using namespace std;


void writeDecompressedCode(ofstream &,ifstream & ,String *,unsigned int, node *);

int main(int argc, char *argv[])
{  
  	
   if(argc<2)
   {
     cout<<"Improper arguments";
     return 0;
   }
    
   unsigned short size=0;
   ifstream in (argv[1],ios::binary);
   in.read((char*)&size,2);
   in.seekg(0,ios::beg);
   
   Table t(size+2);
   t.readFromFile(in);
   
   unsigned short arr[65536];
     for(int i=0;i<65536;i++)  
           arr[i]=0;
           
  for(int i=0;i<t.indicesSize;i++)
  {
     arr[t.indexes[i]]=t.arr[i];       
  } 
  
  
  unsigned int properCount=0,k=0;
   
   for(int i=0;i<65536;i++)
   {
      if(arr[i]>0)
      {
        properCount++;
        //cout<<arr[i]<<"  "<<i<<"| ";
      }
   }   
     
   node roots[properCount];
   String codes[65536];
   
   for(unsigned int i=0;i<=65535;i++)
   {
        if(arr[i]>0)
        {
           roots[k].value=arr[i];
           roots[k].ch=(unsigned short) i;
           k++;
        }                
   }
   
   
    
   cout<<"Building Tree data Structures..";
   node *ROOT=constructTree(roots,properCount);
   
   generateCodes(ROOT,codes);
   
   /* 
   for(int i=0;i<65536;i++)
   {
       if(codes[i].getLength()>0)
       {
          cout<<codes[i]<<"\t\t\t\t\t\t"<<(unsigned short)i<<endl;
       }
   } */  

     
   char *folder=new char[50];
 
   strcpy(folder,"mkdir ");
   
   
   String temp=String(argv[1]);
   temp=temp.subString(0,temp.getLength()-5);
   strcat(folder,temp.str);
   strcat(folder,".pkrout");
   if (system(folder) < 0) {
	cerr << "Unable to execute the command: " << folder << endl;
   }

   strcpy(folder,&(folder[6])) ;
   strcat(folder,"/");
   strcat(folder,temp.str);
   
   ofstream out(folder,ios::binary);
   
    
   cout<<"\nWriting Decompressed data..\n";    
   writeDecompressedCode(out,in,codes,t.no_bytes,ROOT);
    
}


String toString(bitset <16> b)
{
  String temp(17);
  for(int i=0;i<16;i++)
  {
    temp.str[i]= (unsigned char) (b[15-i] +48);
  }
  return temp;
} 


int getDecompressedShort(String &s,node *ROOT)
{
   node *temp;
   temp=ROOT;
   int k=0;
   
   while(s.getLength()>0)
   {
       
         
        if(temp->lchild == null && temp->rchild==null)
        {  
           /*String tp(s.str);
           tp.str[k]='\0';
           cout<<tp.str<<"\t\t\t\t\t"<<temp->ch<<endl;*/
           strcpy(s.str,&(s.str[k]));
            
           return ((unsigned int) temp->ch);
        }  
        else
        {
           if(s.str[k]=='\0')
                return -1;
                
           if(s.str[k]=='0')
           {
              temp=temp->lchild;
              k++;
           }
           else
           {
              temp=temp->rchild;
              k++;
           }
        }  
      
   }
   return -1;
}


void writeDecompressedCode(ofstream &out,ifstream &in ,String code[],unsigned int nobytes, node *ROOT)
{
     unsigned int originalSize= nobytes;
     unsigned short ch=0;
     int i=0;
     String s(100);
     for(int i=0;i<100;i++)
         s.str[i]='\0';
         
     bitset <16> b;
     while(nobytes>1)
     {
       in.read((char *)&ch,2);
       b=toBits(ch);
       s=s+ toString(b);       
       i=getDecompressedShort(s,ROOT);
       while(i!=-1 && nobytes > 1)
       {
         ch=(unsigned short)i;
         
         out.write((char*)&ch,2);
         nobytes-= 2;
         
         if(nobytes%15==0)
               cout<<"\r"<< float(  ( float(originalSize - nobytes) / originalSize) *100)<<" %";
         
         i=getDecompressedShort(s,ROOT);   
       }
     }
     
     /*if(nobytes==1)
     {
        in.read((char*)&ch,2);
        b=toBits(ch);
        s=s+ toString(b);       
        i=getDecompressedShort(s,ROOT);
        while(i!=-1 && nobytes > 1)
        {
          ch=(unsigned short)i;
          
          out.write((char*)&ch,2);
          nobytes-= 2;
          
          i=getDecompressedShort(s,ROOT);   
        }
     }*/
}

 /*unsigned short size=0;
   ifstream in (argv[1],ios::binary);
   in.read((char*)&size,2);
   in.seekg(0,ios::beg);
   
   Table t(size+2);
   t.readFromFile(in);
   //t.display();
   
   node roots[t.indicesSize+1];

   for(int i=0;i<t.indicesSize;i++)
   {
       roots[i].value=t.arr[i];
       roots[i].ch=t.indexes[i];       
   }
  */









