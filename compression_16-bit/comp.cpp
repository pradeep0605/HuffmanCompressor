#include<iostream>
#include<fstream>
#include<bitset>
#include "bitHandling.cpp"
#include "table.cpp"
#include "treeGenerator.cpp"

using namespace std;

void writeCompressedCode(ofstream &,ifstream &,String *,unsigned int);


int main(int argc, char *argv[])
{
   if(argc<2)
   {
      cout<<"Improper Arguments\n";
      return -1;
   }
   
   unsigned int fileSize=0;
   ifstream tp(argv[1],ios::binary);
   
   tp.seekg(0,ios::end);
   fileSize=tp.tellg();
   tp.close();
   
   ifstream in(argv[1],ios::binary);
   
   unsigned short arr[65536];
   for(int i=0;i<65536;i++)
      arr[i]=0;
   
   
   unsigned short readArr[1025];
     
   unsigned int temp=fileSize;
     
   cout<<"Building Initial data Structues..\n";
     
   while(temp>2047)
   {
      in.read((char *) readArr,2048);
      for(int i=0;i<1024;i++)
      {
         arr[readArr[i]]++; 
      }
      temp-=2048;
   }
   
   in.read((char *) readArr,temp);
   for(int i=0;i<temp/2;i++)
   {
      arr[readArr[i]]++;
   }
   if(fileSize%2==1)
   {
       unsigned char ch;
       in.read((char*)&ch,1);
       arr[(unsigned short)ch]++;
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
   

   in.close();
    
   ifstream ins(argv[1],ios::binary);

   ofstream out(strcat(argv[1],".pkr"),ios::binary);  
  
 
   Table t;
   { 
     unsigned short indexes[properCount];
     unsigned short  array[properCount];
     k=0;
     for(int i=0;i<65536;i++)
     {
       if(arr[i]!=0)
        {
            indexes[k]=(unsigned short)i;
            array[k]=(unsigned short)arr[i];
            k++;
        }
     }
    t=Table(array,indexes,properCount,(unsigned int)fileSize);
   }
 
   t.writeToFile(out);
   //t.display();
   cout<<"\nWriting Compressed data..\n";
   writeCompressedCode(out,ins,codes,fileSize);

}


 void writeCompressedCode(ofstream &out,ifstream &in,String  *code,unsigned int nobytes)
  {
    unsigned int originalSize=nobytes;
    
    bool oddFile=((nobytes%2)==1)?true:false;
    nobytes=nobytes -  int(oddFile);
    char *finalCode=new char[50];
    for(int i=0;i<50;i++)
           finalCode[i]='\0';
    unsigned short ch=0;
    bitset <16> b;
     
    cout.precision(3);

    while(nobytes>=2)
    {
       while(strlen(finalCode) < 16 && nobytes >1)
       {
          in.read((char*)&ch,sizeof(unsigned short));
          //cout<<code[ch].str<<"\t\t\t\t\t"<<ch<<endl;
          strcat(finalCode,code[ch].str);
          nobytes-=2;
       }
       
       while(strlen(finalCode) >=16)
       {
          for(int i=0;i<16;i++)
          {
             b[15-i]= int(finalCode[i])-48;
          }
          ch=toShort(b);
          out.write((char *)&ch,2);
          strcpy(finalCode,&finalCode[16]);
       }
      
      if(nobytes%15==0)
        cout<<"\r"<< float(  ( float(originalSize - nobytes) / originalSize) *100)<<" %";
       
    }

    if(oddFile==true)
    {
       unsigned char chr=0;
       in.read((char*)&chr,1);
       strcat(finalCode,code[int(chr)].str);

       while(strlen(finalCode) >=16)
       {
          for(int i=0;i<16;i++)
          {
             b[15-i]= int(finalCode[i])-48;
          }
          ch=toShort(b);
          out.write((char *)&ch,2);
          strcpy(finalCode,&finalCode[16]);
       }
     }
    for(int i=0;i<strlen(finalCode);i++)
    {
       b[15-i]= int(finalCode[i])-48;
    }
    ch=toShort(b);
    out.write((char *)&ch,2);
  }




  
  





/*
  unsigned short readShort=0;
   
   while(temp>1)
   {
       in.read((char *)&readShort,sizeof(unsigned short));
       arr[readShort]++;
       temp=temp-2;
   }
    if(temp==1)
    {
       unsigned char ch=0;
       in.read((char*)&ch,sizeof(unsigned char));
       arr[(unsigned short)ch]++;
       temp--;
    }
*/

