// Copyright (c) 2024 Michael Neill Hartman. All rights reserved.
// mnh_license@proton.me
// https://github.com/hartmanm

#define STATE_FILE "../build/state"
#define MAX_LINE_LENGTH 1024

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void set_value(const char *key,const char *value){
char line[MAX_LINE_LENGTH];
FILE* file=fopen(STATE_FILE,"r");
FILE* new_state_file=fopen("new_state_file.txt","w");
if(file==NULL||new_state_file==NULL){
perror("Error opening file");
return;
}
int found=0;
while(fgets(line,sizeof(line),file)!=NULL){
char *token=strtok(line,"::::");
if(token!=NULL&&strcmp(token,key)==0){
fprintf(new_state_file,"%s::::%s\n",key,value);
found=1;
}else{
fputs(line,new_state_file);
}
}
if(!found){
fprintf(new_state_file,"%s::::%s\n",key,value);
}
fclose(file);
fclose(new_state_file);
remove(STATE_FILE);
rename("new_state_file.txt",STATE_FILE);
printf("Updated: %s = %s\n",key,value);
}
void manage_data(const char *command,const char *key,const char *value){
if(strcmp(command,"set")==0){
set_value(key,value);
}else if(strcmp(command,"get")==0){
char line[MAX_LINE_LENGTH];
FILE* file=fopen(STATE_FILE,"r");
if(file==NULL){
perror("Error opening file for reading");
return;
}
while(fgets(line,sizeof(line),file)!=NULL){
char *token=strtok(line,"::::");
if(token!=NULL&&strcmp(token,key)==0){
token=strtok(NULL,"::::");
fclose(file);
printf("Get: %s = %s\n",key,token?token:"Value not found");
return;
}
}
fclose(file);
printf("Key not found: %s\n",key);
}else{
printf("Invalid command: %s\n",command);
}
}

int process_state_parameters(int f_number_of_parameters,char* f_parameters[]){
if(f_number_of_parameters<3){printf("  %s <set/get> <key> [value]\n",f_parameters[0]);
return 1;}
if(strcmp(f_parameters[1],"set")==0&&argc==4){
manage_data(f_parameters[1],f_parameters[2],f_parameters[3]);}
else if(strcmp(f_parameters[1],"get")==0&&f_number_of_parameters==3){
manage_data(f_parameters[1],f_parameters[2],NULL);}
else{printf("Invalid command or parameters.\n");}
return 0;
}

// process_state_parameters(f_number_of_parameters,f_parameters);

// f_parameters ==== <set/get> <key> [value]
