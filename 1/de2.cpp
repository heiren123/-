#include<iostream>
#include<stdio.h>
#include<cstring>
using namespace std;
void scanner(char*);
int p = 0,num = 0,line = 1,error = 0,i = 0,remark = 0;
char temp[8] = "-";
int errorMes[20] = {0};
int main(){
    char arr[1000];
    while(1){
	    p = 0;
       int k;
       char ch =getchar();
       while(ch=='\n')ch = getchar();
       for(k = 0;ch!='\n';k++)
         {
   	      arr[k] = ch;
   	      ch =getchar();
   	    }
       arr[k] = '#';
       while(arr[p]!='#'&&num<=34)
           {
                scanner(arr);
         	    if(num<=33)
                printf("<%d,%s>,",num,temp);
                strcpy(temp,"-");
           }
       if(remark >=2)break;
       line++;
       printf("\n");
    	}
	if(error>0){
		printf("\nLexicalError(s) on line(s) ");
		for(int j = 0;j<error;j++)
		printf("%d,",errorMes[j]);
	  }

    return 0;
}
void scanner(char* arr){
    while(arr[p]==' ')p++;
    if(arr[p]=='+'){
        p++;
        num = 3;
    }
    else if(arr[p]=='-'){
        p++;
        num = 4;
    }
    else if(arr[p]=='*'){
        p++;
        num = 5;
    }

    else if(arr[p]=='/'){
        p++;
		if(arr[p]=='/')
		   num = 34;
		else if(arr[p] == '*'){
			char a = getchar(),b = getchar();
			 while(a=='*'&&b == '/'){
				 a = b;
				 b = getchar();
				}num = 35;
			}         
		else
          num = 6;   
    }

    else if(arr[p]=='%'){
        p++;
        num = 7;
    }

    else if(arr[p]=='<'){
            p++;
        if(arr[p] == '='){
            num = 9;
            p++;
        }
        else num = 8;
    }
    else if(arr[p]=='>'){
            p++;
         if(arr[p] == '='){
            num = 11;
            p++;
        }
        else num = 10;
    }
    else if(arr[p]=='='){
        p++;
         if(arr[p] == '='){
            num = 12;
            p++;
        }
        else num = 16;
    }
    else if(arr[p]=='!'){
        p++;
         if(arr[p] == '='){
            num = 13;
            p++;
        }
        else num = 0;
    }
    else if(arr[p]=='&'){
        p++;
         if(arr[p] == '&'){
            num = 14;
            p++;
        }
        else num = 0;
    }
    else if(arr[p]=='|'){
        p++;
        if(arr[p] == '|'){
            num = 15;
            p++;
        }
        else num = 0;
    }
    else if(arr[p]=='('){
                p++;
                num = 17;
            }
    else if(arr[p]==')'){
        p++;
        num = 18;
    }
    else if(arr[p]=='['){
        num = 19;
        p++;
    }

    else if(arr[p]==']'){
        p++;
        num = 20;
    }

    else if(arr[p]=='{'){
        p++;
        num = 21;
    }

    else if(arr[p]=='}'){
        p++;
        num = 22;
        remark++;
    }
    else if(arr[p]==';'){
        p++;
         num = 23;
    }
    else if(arr[p]==','){
        p++;
        num = 24;
    }
    else if((arr[p]<='z'&&arr[p]>='a')||(arr[p]<='Z'&&arr[p]>='A')){
            int i = 0;
            char te[8];
             te[i++] = arr[p];
            p++;
            while((arr[p]<='z'&&arr[p]>='a')||(arr[p]<='Z'&&arr[p]>='A')){
                te[i++] = arr[p];
                p++;
            }
            while(arr[p]<='9'&&arr[p]>='0'){
              te[i++] = arr[p];
                p++;
            }
        te[i++] = '\0';
        if(!strcmp(te,"void"))
            num = 25;
        else if(!strcmp(te,"int"))
            num = 26;
        else if(!strcmp(te,"float"))
            num = 27;
        else if(!strcmp(te,"char"))
            num = 28;
        else if(!strcmp(te,"if"))
            num = 29;
        else if(!strcmp(te,"else"))
            num = 30;
        else if(!strcmp(te,"while"))
            num = 31;
        else if(!strcmp(te,"do"))
            num = 32;
        else if(!strcmp(te,"return"))
            num = 33;
        else{
            num = 1;
			strcpy(temp,te);
        }

    }
   else if(arr[p]<='9'&&arr[p]>='0'){
       int k = 0;
	    num = 2;
       temp[k++] = arr[p];
       p++;
		if((arr[p]<='z'&&arr[p]>='a')||(arr[p]<='Z'&&arr[p]>='A')){
			p++;
			error = error+1;
			printf("LexicalError,");
			errorMes[i++] = line;
			strcpy(temp,"-");
         while((arr[p]<='z'&&arr[p]>='a')||(arr[p]<='Z'&&arr[p]>='A'))
				p++;
			num = 34;
		}
		else{
			  while(arr[p]<='9'&&arr[p]>='0'){
              temp[k++] = arr[p];
                p++;
            }
		}
        
   }
   else if(arr[p] == '#'){
	    num = 34;
   }
   else{printf("error%c",arr[p]);}

}
