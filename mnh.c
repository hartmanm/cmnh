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
#include <sys/stat.h>

int check_executable(const char *path,const char *exec_name){
struct stat statbuf;
char exec_path[512];
snprintf(exec_path,sizeof(exec_path),"%s/%s",path,exec_name);
return(stat(exec_path,&statbuf)==0&&(statbuf.st_mode&S_IXUSR));
}
int main(int number_of_parameters,char *parameters[]){
if(number_of_parameters<2){
fprintf(stderr,"Usage: %s <target_executable> [<additional_parameters>...]\n",parameters[0]);
return EXIT_FAILURE;
}
char *exec_name=parameters[1];
char exec_path[512];
if(check_executable("wrap",exec_name)){
snprintf(exec_path,sizeof(exec_path),"wrap/%s",exec_name);
}else if(check_executable("/bin",exec_name)){
snprintf(exec_path,sizeof(exec_path),"/bin/%s",exec_name);
}else if(check_executable("/usr/bin",exec_name)){
snprintf(exec_path,sizeof(exec_path),"/usr/bin/%s",exec_name);
}else{
fprintf(stderr,"target executable '%s' not found in 'wrap', '/bin', or '/usr/bin'\n",exec_name);
return EXIT_FAILURE;
}
char *command[number_of_parameters];
command[0]=exec_path;
for(int i=1;i<number_of_parameters;i++){
command[i]=parameters[i];
}
execv(exec_path,command);
perror("failed to execute target_executable");
return EXIT_FAILURE;
}

// gcc -o build/wgcc wrap/wgcc.c

// ./build/wgcc src/get_json_key_value.c . "-Wall -O2"

// 