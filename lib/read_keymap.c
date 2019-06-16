/* 读取keymap */
#include <stdio.h>
#include <stdlib.h>
#include "debug.h"
#include "../keyboard/monster/config.h"
#include <stdint.h>
#include <string.h>
#include <unistd.h>
#include "cJSON.h"
#include "read_keymap.h"

/* 读取所有的文件 */
char *getfileall(char *fname)
{
    FILE *fp;
    char *str;
    char txt[1000];
    int filesize;
    if ((fp=fopen(fname,"r"))==NULL){
        dprintf("打开文件%s错误\n",fname);
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

int setKeyMap(char *str,uint8_t keymap[][MATRIX_ROWS][MATRIX_COLS]){
    cJSON *json = cJSON_Parse(str);
    cJSON *key= NULL;
    cJSON* keymap_json_arr = cJSON_GetObjectItemCaseSensitive(json,"keymap");

    int idx = 0;
    uint8_t *_keymap = (uint8_t *)keymap;

    int isarr = cJSON_IsArray(keymap_json_arr);
    if(isarr){
        cJSON_ArrayForEach(key,keymap_json_arr){
            if(cJSON_IsNumber(key)){
                /*printf("%d ",key->valueint);*/
                _keymap[idx++] = key->valueint;
            }
        }
    }
    else{
        dprint("keymap.json -> keymap is not exists or not Array\n!");
        return -1;
    }

    return 0;
}

void free_json_malloc(char *str){
    free(str);
}


int read_keymap_init(char path[][255],uint8_t keymap[][MATRIX_ROWS][MATRIX_COLS]){
    for(int i=0;1;i++){
        int len = strlen(path[i]);
        if(!len) break;
        if(access(path[i],R_OK) ==0){
            char *keymap_str  = getfileall(path[i]);
            setKeyMap(keymap_str, keymap);
            free(keymap_str);
            dprintf("read keymap from %s \n",path[i]);
            break;
        }
    }

    return 0;
}

/*
 *int main(){
 *
 *    char *p;
 *    char *fname="1.json";
 *    p=getfileall(fname);
 *    if (p!=NULL) puts(p);
 *    cJSON *json = cJSON_Parse(p);
 *    cJSON *key= NULL;
 *    cJSON* keymap = cJSON_GetObjectItemCaseSensitive(json,"keymap");
 *    int isarr = cJSON_IsArray(keymap);
 *    printf("isarr %d\n",isarr);
 *    cJSON_ArrayForEach(key,keymap){
 *        if(cJSON_IsNumber(key)){
 *            printf("%d ",key->valueint);
 *        }
 *        
 *    }
 *    return 0;
 *}
 *
 */
