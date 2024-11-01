// Copyright (c) 2022 Michael Neill Hartman. All rights reserved.
// mnh_license@proton.me
// https://github.com/hartmanm

// get_json_key_value.c

// gcc -o get_json_key_value get_json_key_value.c

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void trim_quotes(char* str){
size_t len=strlen(str);
if(len>0 && str[0]=='"'){
memmove(str,str+1,len-1);
str[len-2]='\0';
}
}

int main(int number_of_parameters,char* parameters[]){
if(number_of_parameters!=3){
fprintf(stderr,"  %s <json_file> <key>\n",parameters[0]);
return EXIT_FAILURE;
}
const char* json_file=parameters[1];
const char* target_key=parameters[2];
FILE* file=fopen(json_file,"r");
if(!file){
perror("file not found");
return EXIT_FAILURE;
}
char line[1024];
int line_number=0;
int target_line_number=-1;
while(fgets(line,sizeof(line),file)){
line_number++;
char* key_start=strchr(line,'"');
if(key_start){
char* key_end=strchr(key_start+1,'"');
if(key_end){
*key_end='\0';
char key[512];
strcpy(key,key_start+1);
trim_quotes(key);
if(strcmp(key,target_key)==0){
target_line_number=line_number;
}
}
}
}
fclose(file);
if(target_line_number==-1){
printf("key not found\n");
return EXIT_SUCCESS;
}
file=fopen(json_file,"r");
if(!file){
perror("file not found");
return EXIT_FAILURE;
}
line_number=0;
while(fgets(line,sizeof(line),file)){
line_number++;
if(line_number==target_line_number){
char* value_start=strchr(line,':');
if(value_start){
value_start++;
while(*value_start==' ') value_start++;
char value[512];
strcpy(value,value_start);
trim_quotes(value);
printf("%s\n",value);
}
break;
}
}
fclose(file);
return EXIT_SUCCESS;
}