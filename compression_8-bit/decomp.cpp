
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
#include "tree_generator.cpp"

using namespace std;

unsigned long int bytesDetected=0;

class Table
{
   public:
   unsigned short indicesSize;
   unsigned char  *indexes;
   unsigned int   *arr;
   unsigned int   no_bytes;
   Table()
   {
      indicesSize=0;
      no_bytes=0;
   }

   Table(int size)
   {
     indexes=new unsigned char[size];
     arr=new unsigned int[size];
   }

   Table(unsigned int *,unsigned char *,unsigned int,unsigned int);
   
   void display();
   void writeToFile(ofstream &out);
   void readFromFile(ifstream &in);
};

   void Table::writeToFile(ofstream &out)
   {
       out.write((char *) &indicesSize,sizeof(indicesSize));
       out.write((char *)   indexes, indicesSize*sizeof(unsigned char));
       out.write((char *)       arr, indicesSize*sizeof(unsigned int));
       out.write((char *) &no_bytes,sizeof(no_bytes));
   } 
   
   void Table::readFromFile(ifstream &in)
   {
       in.read((char *) &indicesSize,sizeof(indicesSize));
       in.read((char *)   indexes, indicesSize*sizeof(unsigned char));
       in.read((char *)       arr, indicesSize*sizeof(unsigned int));
       in.read((char *) &no_bytes,sizeof(no_bytes));
   }
   
   
Table::Table(unsigned int a[],unsigned char c[],unsigned int arraySize,unsigned int no_bytes)
{
   arr=new unsigned int[arraySize];
   indexes=new unsigned char[arraySize];
   indicesSize=(unsigned short)arraySize;
   this->no_bytes=no_bytes;
     
   for(int i=0;i<arraySize;i++)
   {
      arr[i]=a[i];
      indexes[i]=c[i];
   }  
}


void Table:: display()
{
   cout<<"Size:"<<indicesSize<<endl;
   for(int i=0;i<indicesSize;i++)
   {
      cout<<"|"<<int(indexes[i])<<","<<arr[i];
   } 
    cout<<endl<<"No.bytes:"<<no_bytes<<endl;
}


using namespace std;

bitset <8> toBits(unsigned char ch)
{
   return bitset<8>(ch);
}

unsigned char toChar(bitset <8> b)
{
  short ch=0;
  for(int i=7;i>=0;i--)
  {
     ch=ch<<1;
     ch=ch+short(b[i]);
  }
  return char(ch);
}

void writeDecompressedCode(ofstream &,ifstream & ,String *,unsigned int, node *);

int main(int argc, char *argv[])
{  
  	
   if(argc<2)
   {
     cout<<"Improper arguments";
     return 0;
   }
    
    Table t=Table(256);
    ifstream in(argv[1],ios::binary);
    t.readFromFile(in);
    //t.display();
    
    unsigned int arr[256];
     node roots[t.indicesSize];
    
    for(int i=0;i<t.indicesSize;i++)
    {
       arr[(unsigned int) t.indexes[i]]=t.arr[i];
       roots[i]=node( arr[(unsigned int) t.indexes[i]], t.indexes[i]);
    }    
    
   node *ROOT=constructTree(roots,t.indicesSize);
    
   String code[256];
   generateCodes(ROOT,code);
   
   /*    
   for(int i=0;i<256;i++)
   {
      if(code[i].getLength()>0)
      {
         cout<<(unsigned char)i<<":"<<code[i]<<endl;
      }
   }
   */
   
   char *folder=new char[50];
   strcpy(folder,"mkdir ");
   String temp=String(argv[1]);
   temp=temp.subString(0,temp.getLength()-5);
   strcat(folder,temp.str);
   strcat(folder,".pkrout");
   if (system(folder) < 0) {
	cerr << "Error in executing command: " << folder << endl;
   }

   strcpy(folder,&(folder[6]));
   strcat(folder,"/");
   strcat(folder,temp.str);
   ofstream out(folder,ios::binary);
   
   writeDecompressedCode(out,in,code,t.no_bytes,ROOT);
   cout<<endl<<"Bytes Detected:"<<bytesDetected;
}


String toString(bitset <8> b)
{
  String temp(10);
  for(int i=0;i<8;i++)
  {
    temp.str[i]= (unsigned char) (b[7-i] +48);
  }
  return temp;
}


int getDecompressedChar(String &s,node *ROOT)
{
   node *temp;
   temp=ROOT;
   int k=0;
   
   while(s.getLength()>0)
   {
        if(temp->lchild == null && temp->rchild==null)
        {  
           strcpy(s.str,&(s.str[k]));
           bytesDetected++;
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
     unsigned char ch=0;
     int i=0;
     String s(5000);
     for(int i=0;i<100;i++)
         s.str[i]='\0';
         
     s.str[0]='\0';
     bitset <8> b;
      while(!in.eof())
      {
         ch=in.get();
         b=toBits(ch);
         s=s+toString(b);
         
         i=getDecompressedChar(s,ROOT);
         while(i!=-1 && nobytes>0)
         {
           ch=(unsigned char)i;
           out.write((char *) & ch , sizeof(unsigned char));
           nobytes--;
           i=getDecompressedChar(s,ROOT);
         }
         //continue
      }
}









