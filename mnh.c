// Copyright (c) 2024 Michael Neill Hartman. All rights reserved.
// mnh_license@proton.me
// https://github.com/hartmanm

// gcc -o mnh mnh.c

// ./mnh <target_executable> [ <additional_parameters> ... ]

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <sys/types.h>
#include <unistd.h>

int main(int number_of_parameters,char* parameters[]){
if(number_of_parameters<2){
fprintf(stderr,"Usage: %s <target_executable> [<additional_parameters>...]\n",parameters[0]);
return EXIT_FAILURE;
}
char* exec_name=parameters[1];
char exec_path[512];
snprintf(exec_path,sizeof(exec_path),"wrap/%s",exec_name);
DIR* dir=opendir("wrap");
if(!dir){
perror("failed to open wrap");
return EXIT_FAILURE;
}
struct dirent* entry;
int found=0;
while((entry=readdir(dir))!=NULL){
if(strcmp(entry->d_name,exec_name)==0){
found=1;
break;
}}
closedir(dir);
if(!found){
fprintf(stderr,"target executable '%s' not found\n",exec_name);
return EXIT_FAILURE;
}
char* command[number_of_parameters];
command[0]=exec_path;
for(int i=1;i<number_of_parameters;i++){
command[i]=parameters[i];
}
execv(exec_path,command);
perror("failed to execute target_executable");
return EXIT_FAILURE;
}
