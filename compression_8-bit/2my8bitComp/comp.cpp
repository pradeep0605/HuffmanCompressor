
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
#include "treeGenerator.cpp"

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
  return( (unsigned char)ch);
}


void writeCompressedCode(ofstream &,ifstream &,String *,unsigned int);

int main(int argc, char *argv[])
{  
  
      if(argc<2)
   {
     cout<<"Improper arguments";
     return 0;
   }
   unsigned int fileSize=0,fileSizeTemp;
   ifstream in(argv[1],ios::binary);
   in.seekg(0,ios::end);
   fileSize=in.tellg();
   fileSizeTemp=fileSize;
   in.seekg(0,ios::beg);
   unsigned int arr[256];

   for(int i=0;i<256;i++)
     arr[i]=0;

   unsigned char ch;
   unsigned long int nobytes=0;

   while(fileSizeTemp>0)
   {
      in.read((char*) &ch,sizeof(char));
      arr[(unsigned int)ch]++;
      fileSizeTemp--;
   }

   in.close();

   
   unsigned int properCount=0;
   for(int i=0;i<256;i++)
   {
     if(arr[i]>0)
     {
           properCount++;
          // cout<<" |"<<arr[i]<<","<<char(i)<<"| ";
     }
   }
   

 /*  node roots[properCount]; 
   int k=0;

   for(int i=0;i<256;i++)
   {                         
     if(arr[i]!=0)                  
     {                                      
       roots[k]=node(arr[i],(unsigned char)i);                 
       k++;                                        
     }                                        
   }                 
   */
   //node *ROOT=constructTree(roots,properCount);
   
 
   String code[256];
 
   generateCodes(arr,code,properCount);
 
   /*
   for(int i=0;i<256;i++)
   {
      if(code[i].getLength()>0)
      {
         cout<<(unsigned char)i<<":"<<code[i]<<endl;
      }
   }
   */
   /*long double no_of_bits=0;
   double no_of_comp_bytes=0;
   unsigned char no_of_rem_bits=0;
   
   for(int i=0;i<255;i++)
   {
     if( code[i].getLength()>0)
     {
       no_of_bits= no_of_bits + (arr[i] * code[i].getLength());
       //cout<<char(i)<<" : "<<code[i]<<endl;
     }
   }
  

   no_of_comp_bytes=no_of_bits/8;
   no_of_rem_bits=long (no_of_bits) % 8;  
   
   cout<<"Total compressed bytes :"<<(unsigned long)no_of_comp_bytes<<endl;
   cout<<"Remaining bits :"<<(int)no_of_rem_bits<<endl;*/

   in.close();
   ifstream ins;
   ins.open(argv[1],ios::binary);
   ins.seekg(0,ios::beg);
   ofstream out(strcat(argv[1],".pkr"),ios::binary);  
   
   
   unsigned char indexes[properCount];
   unsigned int  array[properCount];
   int k=0;
   for(int i=0;i<256;i++)
   {
     if(arr[i]>0)
      {
          indexes[k]=(unsigned char)i;
          array[k]=arr[i];
          k++;
      }
   } 
   Table t=Table(array,indexes,properCount,(unsigned int)fileSize);
   t.writeToFile(out);
   //t.display();
   
   writeCompressedCode(out,ins,code,fileSize);
   
}



  void writeCompressedCode(ofstream &out,ifstream &in,String *code,unsigned int fileSize)
  {
    unsigned int originalSize=fileSize;
    char *finalCode=new char[50];
    unsigned long writtenBytes=0;
    for(int i=0;i<50;i++)
           finalCode[i]='\0';
    unsigned char ch=65;
    bitset <8> b;

    while(fileSize >= 1)
    {
    
        while(strlen(finalCode) <8 && fileSize>0)
        {
          in.read((char*)&ch,1);
          fileSize--;
          /*if(fileSize%999==0)
              cout<<"\r"<< float(originalSize-fileSize)/originalSize*100<<" %";*/
          strcat(finalCode, code[(unsigned int)ch].str);
        }
       
       while(strlen(finalCode)>=8 )
       {
          for(int i=0;i<8;i++)
          { 
             b[7-i]=int(finalCode[i])-48;
          }

          ch=toChar(b);
          out.write((char *) &ch,sizeof(unsigned char));
          out.flush();
          writtenBytes++;
          strcpy(finalCode,&finalCode[8]);
       }
    }
    while(strlen(finalCode)>=8)
    {
      for(int i=0;i<8;i++)
      { 
         b[7-i]=int(finalCode[i])-48;
      }
      ch=toChar(b);
      out.write((char *) &ch,sizeof(unsigned char));
      writtenBytes++;
      strcpy(finalCode,&(finalCode[8]));
    } 
      
      for(int i=0;i<strlen(finalCode);i++)
      { 
         b[7-i]=int(finalCode[i])-48;
      }
      ch=toChar(b);
      out.write((char *) &ch,sizeof(unsigned char));
      writtenBytes++;    
      strcpy(finalCode,&(finalCode[8]));
      cout<<endl<<"WRITTEN BYTES:"<<writtenBytes<<endl;
      cout<<endl<<"rem bits :"<<strlen(finalCode);
  }    













