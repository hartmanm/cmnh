// Copyright (c) 2024 Michael Neill Hartman. All rights reserved.
// mnh_license@proton.me
// https://github.com/hartmanm

// gcc -o mnh mnh.c

// ./mnh <target_executable> [ <additional_parameters> ... ]

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <dirent.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/stat.h>
#include <ctype.h>
#include <limits.h>

#include "include/state.h"
#include "include/path.h"

int check_executable(const char* path,const char* exec_name){
struct stat statbuf;
char exec_path[DIRECTORY_SIZE];
snprintf(exec_path,sizeof(exec_path),"%s/%s",path,exec_name);
return(stat(exec_path,&statbuf)==0&&(statbuf.st_mode&S_IXUSR));
}
void execute_command(const char* exec_path,char** parameters,int number_of_parameters){
size_t command_length=strlen(exec_path)+1;
for(int i=1;i<number_of_parameters;i++){
if(parameters[i]&&strlen(parameters[i])>0){
command_length+=strlen(parameters[i])+1;
}}
char* command=calloc(command_length,sizeof(char));
if(command==NULL){perror("\nmemory allocation error");exit(EXIT_FAILURE);}
memcpy(command,exec_path,strlen(exec_path));
size_t current_length=strlen(exec_path);
for(int i=1;i<number_of_parameters;i++){
if(parameters[i]&&strlen(parameters[i])>0){
if(current_length>0){command[current_length]=' ';current_length++;}
size_t param_length=strlen(parameters[i]);
memcpy(command+current_length,parameters[i],param_length);
current_length+=param_length;
}}
command[current_length]='\0';
FILE *fp=popen(command,"r");
if(fp==NULL){perror("\npopen failed");free(command);exit(EXIT_FAILURE);}
char buffer[DIRECTORY_SIZE];
while(fgets(buffer,sizeof(buffer),fp)!=NULL){printf("%s",buffer);}
if(pclose(fp)==-1){perror("\npclose failed");}
free(command);
}
int main(int number_of_parameters,char* parameters[]){
if(number_of_parameters<2){fprintf(stderr,"  %s <exec_path> <param1> [<param2> ...]\n",parameters[0]);return EXIT_FAILURE;}

// process_state_parameters(f_number_of_parameters,f_parameters);
char** state_parameters = (char**)calloc(PARAMETER_SIZE,sizeof(char*));
state_parameters[0]=(void*)0;
state_parameters[1]=(void*)0;
state_parameters[2]=(void*)0;
state_parameters[3]=(void*)0;
 state_parameters[0] = (char*)calloc(PARAMETER_SIZE,sizeof(char));
 state_parameters[1] = (char*)calloc(PARAMETER_SIZE,sizeof(char));
 state_parameters[2] = (char*)calloc(PARAMETER_SIZE,sizeof(char));
 state_parameters[3] = (char*)calloc(PARAMETER_SIZE,sizeof(char));
//uint8_t f_number_of_parameters=0;
state_parameters[0]="set";
state_parameters[1]="level_zero";
wgetcwd(state_parameters[2]);
state_parameters[3]=(void*)0;
process_state_parameters(3,state_parameters);

state_parameters[0]="get";
state_parameters[1]="level_zero";
state_parameters[2]=(void*)0;
state_parameters[3]=(void*)0;
process_state_parameters(2,state_parameters);

// f_parameters ==== <set/get> <key> [value]

char* exec_name=parameters[1];
char exec_path[DIRECTORY_SIZE];
if(check_executable("build",exec_name)){
snprintf(exec_path,sizeof(exec_path),"build/%s",exec_name);
}else if(check_executable("wrap",exec_name)){
snprintf(exec_path,sizeof(exec_path),"wrap/%s",exec_name);
}else if(check_executable("/bin",exec_name)){
snprintf(exec_path,sizeof(exec_path),"/bin/%s",exec_name);
}else if(check_executable("/usr/bin",exec_name)){
snprintf(exec_path,sizeof(exec_path),"/usr/bin/%s",exec_name);
}else{
fprintf(stderr,"target executable '%s' not found in 'build', 'wrap', '/bin', or '/usr/bin'\n",exec_name);
return EXIT_FAILURE;
}
execute_command(exec_path,parameters,number_of_parameters-1);

free(state_parameters[0]); 
free(state_parameters[1]);
free(state_parameters[2]);
free(state_parameters[3]);

return EXIT_FAILURE;
}

// gcc -o mnh mnh.c

// gcc -o build/wgcc wrap/wgcc.c

// ./build/wgcc src/get_json_key_value.c . "-Wall -O2"

// ./build/wgcc src/get_json_key_value.c . "-Wall -O2 -static"

// wget https://hartmanm.github.io/config/m11.json

// ./build/get_json_key_value m11.json START

// ./mnh get_json_key_value m11.json START

//

// process_state_parameters(f_number_of_parameters,f_parameters);

// f_parameters ==== <set/get> <key> [value]
