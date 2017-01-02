#include<iostream>
#include<bitset>
using namespace std;


bitset <16> toBits(unsigned short ch)
{
   return bitset<16>(ch);
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


unsigned short toShort(bitset <16> b)
{
  unsigned short ch=0;
  for(int i=15;i>=0;i--)
  {
     ch=ch<<1;
     ch=ch+short(b[i]);
  }
  return ch;
}

void to2Chars(unsigned short sh)
{
   bitset <16> b;
   bitset <8> b2;
   b=toBits(sh);
       
          
   for(int i=8;i>=0;i--)
   {
       b2[i]=b[i];   
   }
       cout<<toChar(b2);   
      
   for(int i=15;i>=8;i--)
   {
       b2[i-8]=b[i];
    }
    cout<<toChar(b2);
}
