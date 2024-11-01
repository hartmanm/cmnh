// Copyright (c) 2024 Michael Neill Hartman. All rights reserved.
// mnh_license@proton.me
// https://github.com/hartmanm

#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <limits.h>

#include "constants.h"

int wgetcwd(char* return_buffer){
char cwd[PATH_MAX];
if(getcwd(cwd,sizeof(cwd))!=NULL){
size_t len=strlen(cwd);
if(len<PATH_SIZE){
memcpy(return_buffer,cwd,len+1);
}else{
memcpy(return_buffer,cwd,PATH_SIZE-1);
return_buffer[PATH_SIZE-1]='\0';
}
return 0;
}else{
return -1;
}
}

