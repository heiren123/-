#include <iostream>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
using namespace std;
char str[15],line[300];
int num=0, zhushi = 0, over = 0, errArr[50],err = 0;
int first(char arr[])
{
    int i=0,j=0;
    while(i<strlen(arr))
    {
        if(zhushi == 1){
            zhushi = 0;
            return 0;
        }else if(zhushi == 2){
            if(arr[i]=='*'&&arr[i+1]=='/')
                zhushi = 0;
            return 0;
        }
        if(arr[i]==' ' || arr[i]=='\t'){
            i++;
            continue;
        }
        memset(str,0,sizeof(str));
        j=0;
        if((arr[i]<='z'&&arr[i]>='a')||(arr[i]<='Z'&&arr[i]>='A')){
            str[j]=arr[i];
            i++;
            while((arr[i]>='0'&&arr[i]<='9')||(arr[i]>='a'&&arr[i]<='z')||(arr[i]>='A'&&arr[i]<='Z')){
                str[++j]=arr[i];
                i++;
            }
            str[++j]='\0';
			int c = 0;
            if(strcmp(str,"void")==0)
                     c = 25;
			else if(strcmp(str,"int")==0)
                     c = 26;
			else if(strcmp(str,"float")==0)
                     c = 27;
			else if(strcmp(str,"char")==0)
                     c = 28;
			else if(strcmp(str,"if")==0)
                     c = 29;
			else if(strcmp(str,"else")==0)
                     c = 30;
			else if(strcmp(str,"while")==0)
                     c = 31;
			else if(strcmp(str,"do")==0)
                     c = 32;
			else if(strcmp(str,"return")==0)
                     c = 33;
            if(c==0){
                printf("<1,%s>,",str);
            }
            else {
                printf("<%d,->,",c);
            }
        }
        else if(arr[i]>='0'&&arr[i]<='9')
        {
            str[j]=arr[i++];
            if((arr[i]<='z'&&arr[i]>='a')||(arr[i]<='Z'&&arr[i]>='A')){
                errArr[err++]=num;
                printf("LexicalError,");
                while(arr[i]!=' ')
                    i++;
            }else{
            while(arr[i]>='0'&&arr[i]<='9'){
                str[++j]=arr[i++];
            }
  str[i]='\0';
            printf("<2,%s>,",str);
        }
        }
        else{
            switch(arr[i]){
                case '+':{
                    printf("<3,->,");
                    i++;
                    break;
                }
                case '-':{
                    printf("<4,->,");
                    i++;
                    break;
                }
                case '*':{
                    if(arr[i+1]=='/'){
                        zhushi = 0;
                        break;
                    }
                    printf("<5,->,");
                    i++;
                    break;
                }
                case '/':{
                    if(arr[i+1]=='/'){
                        zhushi = 1;
                        return 1;
                    }
                    else if(arr[i+1]=='*'){
                        zhushi = 2;
                        return 1;
                    }
                    else{
                        printf("<6,->,");
                    }
                    i++;
                    break;
                }
                case '%':{
                    printf("<7,->,");
                    i++;
                    break;
                }
                case '(':{
                    printf("<17,->,");
                    i++;
                    break;
                }
                case ')':{
                    printf("<18,->,");
                    i++;
                    break;
                }
                case '[':{
                    printf("<19,->,");
                    i++;
                    break;
                }
                case ']':{
                    printf("<20,->,");
                    i++;
                    break;
                }
                case '{':{
                    printf("<21,->,");
                    i++;
                    break;
                }
                case '}':{
                    printf("<22,->,");
                    i++;
                    break;
                }
                case ';':{
                    printf("<23,->,");
                    i++;
                    break;
                }
                case ',':{
                    printf("<24,->,");
                    i++;
                    break;
                }
                case '<':{
                    if(arr[i+1]=='='){
                        printf("<9,->,");
                        i++;
                    }
                    else
                        printf("<8,->,");
                    i++;
                    break;
                }
                case '>':{
                    if(arr[i+1]=='='){
                        printf("<11,->,");
                        i++;
                    }
                    else
                        printf("<10,->,");
                    i++;
                    break;
                }
                case '=':{
                    if(arr[i+1]=='='){
                        printf("<12,->,");
                        i++;
                    }
                    else
                        printf("<16,->,");
                    i++;
                    break;
                }
                case '!':{
                    if(arr[i+1]=='='){
                        printf("<13,->,");
                        i++;
                        i++;
                    }

                    break;
                }
                case '&':{
                    if(arr[i+1]=='&'){
                        printf("<14,->,");
                        i++;
                        i++;
                    }
                    break;
                }
                case '|':{
                    if(arr[i+1]=='|'){
                        printf("<15,->,");
                        i++;
                        i++;
                    }

                    break;
                }
                case '#':{
                    over = 1;
                    i++;
                    return 0;
                }
            }
        }
    }
    return 1;
}

int main()
{
    while(!over){
        gets(line);
        if(strlen(line)>0){
            if(strcmp(line," ")==0)continue;
            num++;
            if(first(line)==1)
                printf("\n");
        }
    }
    if(err>0){
    printf("\nLexicalError(s) on line(s) ");
    for(int i=0;i<err;i++)
        printf("%d,",errArr[i]);
	}
    return 0;
}
