// Copyright (c) 2024 Michael Neill Hartman. All rights reserved.
// mnh_license@proton.me
// https://github.com/hartmanm

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#include "constants.h"

void create_state_file(){
FILE *file = fopen(STATE_FILE,"a");
if(file==NULL){
perror("failed to create state file");
exit(EXIT_FAILURE);
}
fclose(file);
}

void set_value(const char* key,const char* value){
char line[PARAMETER_SIZE];
FILE* file=fopen(STATE_FILE,"r");
FILE* alt_state=fopen("alt_state","w");
if(file==NULL||alt_state==NULL){
perror("error opening state");
return;
}
int found=0;
while(fgets(line,sizeof(line),file)!=NULL){
char* token=strtok(line,"::::");
if(token!=NULL&&strcmp(token,key)==0){
fprintf(alt_state,"%s::::%s\n",key,value);
found=1;
}else{
fputs(line,alt_state);
}
}
if(!found){
fprintf(alt_state,"%s::::%s\n",key,value);
}
fclose(file);
fclose(alt_state);
remove(STATE_FILE);
rename("alt_state",STATE_FILE);
printf("\nset: %s = %s\n",key,value);
}
void manage_data(const char* command,const char* key,const char* value,char* state_buffer){
if(strcmp(command,"set")==0){
set_value(key,value);
}else if(strcmp(command,"get")==0){
char line[PARAMETER_SIZE];
FILE* file=fopen(STATE_FILE,"r");
if(file==NULL){
perror("error opening state");
return;
}
while(fgets(line,sizeof(line),file)!=NULL){
char* token=strtok(line,"::::");
if(token!=NULL&&strcmp(token,key)==0){
token=strtok(NULL,"::::");
if(token!=NULL){
memcpy(state_buffer,token,strlen(token)+1);
}else{
state_buffer[0]='\0';
}
fclose(file);
printf("\nget: %s = %s\n",key,token?token:"value not found");
return;
}
}
fclose(file);
printf("key not found: %s\n",key);
}else{
printf("invalid command: %s\n",command);
}
}

int process_state_parameters(char* f_parameters[],char* state_buffer){
printf("char* f_parameters[] %s %s %s\n",f_parameters[0],f_parameters[1],f_parameters[2]);
create_state_file();
if(strcmp(f_parameters[0],"set")==0){
manage_data(f_parameters[0],f_parameters[1],f_parameters[2],state_buffer);}
else if(strcmp(f_parameters[0],"get")==0){
manage_data(f_parameters[0],f_parameters[1],f_parameters[2],state_buffer);
}
else{
printf("invalid command or parameters.\n");
printf("  %s <set/get> <key> [value]\n",f_parameters[0]);
}
return 0;
}

// process_state_parameters(f_number_of_parameters,f_parameters);

// f_parameters ==== <set/get> <key> [value]
