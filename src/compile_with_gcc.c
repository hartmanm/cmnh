// Copyright (c) 2024 Michael Neill Hartman. All rights reserved.
// mnh_license@proton.me
// https://github.com/hartmanm

// gcc -o compile_with_gcc compile_with_gcc.c

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>

static inline int compile_with_gcc(const char* source_file,const char* level_zero_directory,const char* flags){
char build_directory[512];
snprintf(build_directory,sizeof(build_directory),"%s/build",level_zero_directory);
struct stat st;
if(stat(build_directory,&st)==-1){
if(mkdir(build_directory,0755)==-1){
perror("failed to make build directory");
return EXIT_FAILURE;
}}
char command[512];
snprintf(command,sizeof(command),"gcc %s -o %s/%s %s",flags,build_directory,source_file,source_file);
int result=system(command);
if(result==-1){
perror("gcc failed");
return EXIT_FAILURE;
}
printf("exec ready\n",build_directory,source_file);
return EXIT_SUCCESS;
}