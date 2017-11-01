#include<iostream>
#include<stdio.h>
#include<stdlib.h>
#include<string>
using namespace std;
struct edge{
  string s;
  string a;
  string b;
};
string del(string src);
void show(string src);
int change(edge *e,int size,string src);
int main(){
  edge e[50];
  int size = 0;
  int end = 0;
  string temp;

  while(!end){
    cin>>temp;
	if(temp == "f")end = 1;
	e[size].s =temp;

	cin>>temp;
	if(temp == "{NULL}")
	   e[size].a = "";
	else{
	for(int i = 1;i<temp.length()-1;i+=2)
	e[size].a +=temp[i];
	}
   
   cin>>temp;
   if(temp == "{NULL}")
	   e[size].b = "";
	else
		{
	      for(int i = 1;i<temp.length()-1;i+=2)
	      e[size].b +=temp[i];
	}
	size++;
  }
	
	edge d[50];
	int size2 = 1,p = 0;
	d[p].s = e[p].s;
    
   for(;p<size2;p++)
	   {
            
          if(d[p].s.length()==1)
			  {
	          for(int i = 0;i<size;i++){
		            if(e[i].s == d[p].s){
			            d[p].a= e[i].a;
			            d[p].b = e[i].b;
			            i = size;
			            }
		          }
	          }
		 else {
		         
		    for(int i = 0;i<d[p].s.length();i++)
				{
		              for(int j = 0;j<size;j++)
						 {
			               if(e[j].s[0] == d[p].s[i])
							   {
								   
								   d[p].a+= e[j].a;
								   
								   d[p].b+= e[j].b;
								   j = size;
							   }
			            }
		          }
		         d[p].a= del(d[p].a); 
		         d[p].b= del(d[p].b); 
	    
		}
		if(d[p].a.length()>0){

        int have = 0;
		for(int i = 0;i<size2;i++)
		   {

			if(d[i].s==d[p].a)
				have = 1;
		}
		if(!have){
            d[size2].s = d[p].a;
			size2++;
		}
		}



		if(d[p].b.length()>0){

        int have = 0;
		for(int i = 0;i<size2;i++)
		   {

			if(d[i].s==d[p].b)
				have = 1;
		}
		if(!have){
            d[size2].s = d[p].b;
			size2++;
		}
		}
		
  }
   int array[size2][2];
   for (int i = 0;i<size2;i++)
   {

	   array[i][0] = change(d,size2,d[i].a);
	   array[i][1] = change(d,size2,d[i].b);
	   show(d[i].s);
	   printf("%C",'A'+i);
	   if (array[i][0]!=-1)
		   printf("%c",'A'+array[i][0]);
	   if (array[i][1]!=-1)
		   printf("%c",'A'+array[i][1]);
	   cout<<endl;
   }
  return 0;
 }
string del(string src){
	 
	 string temp = "";
	 for(int i = 0;i<src.length();i++){
		    int have = 0;
		    for(int j = 0;j<temp.length();j++){
			       if(temp[j] == src[i])
			       have = 1;
			    }
			  if(have==0)
				  temp+=src[i];
		 }
		 return temp;
	}
void show(string src){
	if(src.length()==0)return;
	cout<<"{";
	for (int i = 0;i<src.length();i++)
	{
		if(src.length()==1)
			cout<<src[i];
		else
			cout<<src[i]<<",";
	}
	cout<<"}";

}
int change(edge e[50],int size,string src){
	for (int i = 0;i<size;i++)
		if(e[i].s == src)
			return i;
	return -1;
}
