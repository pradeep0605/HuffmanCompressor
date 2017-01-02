#include<iostream>
#include<string.h>

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
   s[k]='\0';
}

int main()
{
   char str1[100],str2[200];
   cout<<"Enter the string:";
   cin>>str1;
    strrev(str1);
   cout<<"\nREverse string is:"<<str1<<endl;
   return 0;
}
