#ifndef INCLUDE_H
#define INCLUDE_H

#define COMMAND_SIZE 256
#define MAX_PATH_LENGTH 256
#define MAX_FILES 4

#include <sys/stat.h>
#include <unistd.h>
#include <libconfig.h>

struct AppConfig 
{
    const char* script_path;
    const char* commands_file;
    const char* logs_file;
    const char* output_file;
    const char* errors_file;
    const char* vmname;
    int wait_time;
    int mode;
};

int my_strlen(const char *str);
char * my_strcpy(char * dest, const char * src);
char * my_mstrcpy(char * dest, const char * src);
char * my_mstrncpy(const char * src, int count);
char * my_strcat(const char * a, const char * b);
int my_strcmp(const char * str1, const char * str2);

int writeblankline(const char *filename);
void configure(const char *filename);
int read_config(const char *filename);
int initialize();
int writelogs(char data[COMMAND_SIZE]);
int preparefiles();
int executecmd(char cmd[COMMAND_SIZE]);
int vmconfig();
void launcher();
int menu();


#endif
