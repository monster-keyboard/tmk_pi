/* 读取keymap */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cJSON.h"
char *getfileall(char *fname)
{
	FILE *fp;
	char *str;
	char txt[1000];
	int filesize;
	if ((fp=fopen(fname,"r"))==NULL){
		printf("打开文件%s错误\n",fname);
		return NULL;
	}
 
	fseek(fp,0,SEEK_END); 
 
	filesize = ftell(fp);
	str=(char *)malloc(filesize);
	str[0]=0;
 
	rewind(fp);
	while((fgets(txt,1000,fp))!=NULL){
		strcat(str,txt);
	}
	fclose(fp);
	return str;
}
int main(){

    char *p;
	char *fname="1.json";
	p=getfileall(fname);
	if (p!=NULL) puts(p);
    cJSON *json = cJSON_Parse(p);
    cJSON *key= NULL;
    cJSON* keymap = cJSON_GetObjectItemCaseSensitive(json,"keymap");
    int isarr = cJSON_IsArray(keymap);
    printf("isarr %d\n",isarr);
    cJSON_ArrayForEach(key,keymap){
        if(cJSON_IsNumber(key)){
            printf("%d ",key->valueint);
        }
        
    }
    return 0;
}

