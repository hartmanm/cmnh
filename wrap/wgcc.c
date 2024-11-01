// Copyright (c) 2024 Michael Neill Hartman. All rights reserved.
// mnh_license@proton.me
// https://github.com/hartmanm

// gcc -o wgcc wgcc.c

// ./wgcc <target_file>.c /path/to/level_zero_directory "-Wall -O2"

// ./wgcc ../src/get_json_key_value.c .. "-Wall -O2"

#include <stdio.h>
#include "../include/compile_with_gcc.h"

int main(int number_of_parameters,char* parameters[]){
if(number_of_parameters<3||number_of_parameters>4){
fprintf(stderr,"Usage: %s <source_file.c> <level_zero_dir> [<build_flags>]\n",parameters[0]);
return EXIT_FAILURE;
}
const char* build_flags=(number_of_parameters==4)?parameters[3]:"";
return compile_with_gcc(parameters[1],parameters[2],build_flags);
}
