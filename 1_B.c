 
/* 
 * Group Number : 06
 * Name : Swapnaneel Ray
 * Roll : 002311001015
 * Name : Swarnendu Banerjee
 * Roll : 002311001016
 * Name : Rahul Pandey
 * Roll : 002311001021 
 *
 * Assignment No: 1B
 * Assignment Details: Program to GET and SET the Environment variable and to know use of getenv and setenv system calls
 *
 * Input Description: None
 * Output Description: Displays the SYSTEM environment variables USER, HOME, HOST, ARCH, DISPLAY, PRINTER, PATH and two custom environment variables GROUP and TEAM
 *
 * Compilation command: gcc A1_06_1B.c -o out
 * Execution sequence: ./out
 *
 * Output :
 * System Generated Environment Variables: 
 * $USER = be2321
 * $HOME = /home/usr/student/ug/yr23/be2321
 * $HOST = (null)
 * $ARCH = (null)
 * $DISPLAY = (null)
 * $PRINTER = (null)
 * $PATH = /usr/lib64/qt-3.3/bin:/usr/local/bin:/usr/bin:/usr/local/sbin:/usr/sbin:/home/usr/student/ug/yr23/be2321/.local/bin:/home/usr/student/ug/yr23/be2321/bin
 *
 * Custom Environment Variables
 * $GROUP = A1
 * $TEAM = 00
 * $TEAM = 06
*/

#include <stdio.h>
#include <stdlib.h>

void print_env_var(const char* name){
        char* value = getenv(name);
        printf("$%s = %s\n",name,value);
}

void set_env_var(const char* env_name, const char* env_val, int overwrite){
        if(setenv(env_name, env_val, overwrite)!=0){
                perror("Error in setting environment variable\n");
        }
        print_env_var(env_name);
}

int main(){
        // displaying system generated env variables
        printf("System Generated Environment Variables: \n");
        print_env_var("USER");
        print_env_var("HOME");
        print_env_var("HOST");
        print_env_var("ARCH");
        print_env_var("DISPLAY");
        print_env_var("PRINTER");
        print_env_var("PATH");

        // setting and printing custom env variables
        printf("\nCustom Environment Variables\n");
        set_env_var("GROUP","A1",0);
        set_env_var("TEAM","00",0);
        set_env_var("TEAM","06",1); // overwriting

        return 0;
 }








