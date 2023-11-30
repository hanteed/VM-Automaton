/*
 ▄ .▄ ▄▄▄·  ▐ ▄ ▄▄▄▄▄▄▄▄ .
██▪▐█▐█ ▀█ •█▌▐█•██  ▀▄.▀·
██▀▐█▄█▀▀█ ▐█▐▐▌ ▐█.▪▐▀▀▪▄ 
██▌▐▀▐█ ▪▐▌██▐█▌ ▐█▌·▐█▄▄▌
▀▀▀ · ▀  ▀ ▀▀ █▪ ▀▀▀  ▀▀▀ 
2023.
*/

#include <stdio.h>
#include <stdlib.h>
#include "../include.h"

char script_path[256];
char commands_file[256];
char logs_file[256];
char output_file[256];
char errors_file[256];
char vmname[256];
int mode;
int wait_time;

struct AppConfig configuration;

int writeblankline(const char *filename)
{
    FILE *fp = fopen(filename, "a");
    if (fp == NULL) return -1;
    fprintf(fp, "\n");
    fclose(fp);
    return 0;
}

void configure(const char *filename)
{
    config_t cfg;
    config_setting_t *root, *setting, *group;

    printf("Enter the bash script path: ");
    if(scanf("%255s", script_path) != 1)
    {
        fprintf(stderr, "Invalid input. Please enter a valid file path.\n");
        return;
    }

    printf("Enter the commands file path: ");
    if(scanf("%255s", commands_file) != 1)
    {
        fprintf(stderr, "Invalid input. Please enter a valid file path.\n");
        return;
    }

    printf("Enter the logs file path: ");
    if(scanf("%255s", logs_file) != 1)
    {
        fprintf(stderr, "Invalid input. Please enter a valid file path.\n");
        return;
    }

    printf("Enter the output file path: ");
    if(scanf("%255s", output_file) != 1)
    {
        fprintf(stderr, "Invalid input. Please enter a valid file path.\n");
        return;
    }

    printf("Enter the errors file path: ");
    if(scanf("%255s", errors_file) != 1)
    {
        fprintf(stderr, "Invalid input. Please enter a valid file path.\n");
        return;
    }

    printf("Enter the waiting time: ");
    if(scanf("%d", &wait_time) != 1 || wait_time < 0)
    {
        fprintf(stderr, "Invalid input. Please enter a valid wait time.\n");
        return;
    }

    printf("Enter the mode (0:VM / 1:Host): ");
    if(scanf("%d", &mode) != 1 || mode < 0)
    {
        fprintf(stderr, "Invalid input. Please enter a valid wait time.\n");
        return;
    }

    config_init(&cfg);
    root = config_root_setting(&cfg);

    group = config_setting_add(root, "config", CONFIG_TYPE_GROUP);

    setting = config_setting_add(group, "wait_time", CONFIG_TYPE_INT);
    config_setting_set_int(setting, wait_time);

    setting = config_setting_add(group, "mode", CONFIG_TYPE_INT);
    config_setting_set_int(setting, mode);

    setting = config_setting_add(group, "script_path", CONFIG_TYPE_STRING);
    config_setting_set_string(setting, script_path);

    setting = config_setting_add(group, "commands_file", CONFIG_TYPE_STRING);
    config_setting_set_string(setting, commands_file);

    setting = config_setting_add(group, "logs_file", CONFIG_TYPE_STRING);
    config_setting_set_string(setting, logs_file);

    setting = config_setting_add(group, "output_file", CONFIG_TYPE_STRING);
    config_setting_set_string(setting, output_file);

    setting = config_setting_add(group, "errors_file", CONFIG_TYPE_STRING);
    config_setting_set_string(setting, errors_file);

    if(!config_write_file(&cfg, filename))
    {
        fprintf(stderr, "Error while writing file.\n");
        config_destroy(&cfg);
        return;
    }

    fprintf(stderr, "New configuration successfully written to: %s\n", filename);

    config_destroy(&cfg);

}

int read_config(const char *filename)
{
    config_t cfg;
    config_init(&cfg);

    if (!config_read_file(&cfg, filename))
    {
        fprintf(stderr, "%s:%d - %s\n", config_error_file(&cfg),
                config_error_line(&cfg), config_error_text(&cfg));
        config_destroy(&cfg);
        return EXIT_FAILURE;
    }

    if (!config_lookup_int(&cfg, "config.wait_time", &configuration.wait_time))
        fprintf(stderr, "No 'wait_time' setting in configuration file.\n");

    if (!config_lookup_int(&cfg, "config.mode", &configuration.mode))
        fprintf(stderr, "No 'mode' setting in configuration file.\n");

    if (!config_lookup_string(&cfg, "config.script_path", &configuration.script_path))
        fprintf(stderr, "No 'script_path' setting in configuration file.\n");

    if (!config_lookup_string(&cfg, "config.commands_file", &configuration.commands_file))
        fprintf(stderr, "No 'commands_file' setting in configuration file.\n");

    if (!config_lookup_string(&cfg, "config.logs_file", &configuration.logs_file))
        fprintf(stderr, "No 'logs_file' setting in configuration file.\n");

    if (!config_lookup_string(&cfg, "config.output_file", &configuration.output_file))
        fprintf(stderr, "No 'output_file' setting in configuration file.\n");

    if (!config_lookup_string(&cfg, "config.errors_file", &configuration.errors_file))
        fprintf(stderr, "No 'errors_file' setting in configuration file.\n");

    return EXIT_SUCCESS;
}

void configure_vm(const char *filename)
{
    config_t cfg;
    config_setting_t *root, *setting, *group;

    printf("Enter the name of the VM main user: ");
    if(scanf("%255s", vmname) != 1)
    {
        fprintf(stderr, "Invalid input. Please enter a valid name.\n");
        return;
    }

    config_init(&cfg);
    root = config_root_setting(&cfg);

    group = config_setting_add(root, "config", CONFIG_TYPE_GROUP);

    setting = config_setting_add(group, "vmname", CONFIG_TYPE_STRING);
    config_setting_set_string(setting, vmname);

    if(!config_write_file(&cfg, filename))
    {
        fprintf(stderr, "Error while writing file.\n");
        config_destroy(&cfg);
        return;
    }

    fprintf(stderr, "New configuration successfully written to: %s\n", filename);

    config_destroy(&cfg);
}

int read_vm_config(const char *filename)
{
    config_t cfg;
    config_init(&cfg);

    if (!config_read_file(&cfg, filename))
    {
        fprintf(stderr, "%s:%d - %s\n", config_error_file(&cfg),
                config_error_line(&cfg), config_error_text(&cfg));
        config_destroy(&cfg);
        return EXIT_FAILURE;
    }

    if (!config_lookup_string(&cfg, "config.vmname", &configuration.vmname))
        fprintf(stderr, "No 'script_path' setting in configuration file.\n");

    return EXIT_SUCCESS;
}

int initialize()
{    
    FILE *fp = fopen(configuration.errors_file, "w"); 
    if (fp == NULL) 
    {
        perror("Error opening file.");
        return 1;
    }
    fclose(fp);
}

int writetofile(const char *filename, char *data)
{
    FILE *fp = fopen(filename, "a");
    if (fp == NULL) return -1;
    fprintf(fp, "%s\n", data);
    fclose(fp);
    return 0;
}

int preparefiles()
{
    writeblankline(configuration.output_file);
    writeblankline(configuration.logs_file);
    system(my_strcat("date >> ", configuration.output_file));
    system(my_strcat("date >> ", configuration.logs_file));
    writeblankline(configuration.output_file);
    writeblankline(configuration.logs_file);
    return 0;
}

int executecmd(char cmd[COMMAND_SIZE])
{
    writetofile(configuration.logs_file, cmd);
    if(system(cmd) == -1) return -1;
    return 0;
}

int vmconfig(const char *filename)
{
    char name[COMMAND_SIZE];
    char choice[COMMAND_SIZE];
    char command[COMMAND_SIZE];
    int i = 0;
    int ram = 0;
    int vram = 0;
    int capacity = 0;
    int status = 0;

    system("clear");

    printf("\nPlease enter the machine's name: ");
    scanf("%s", name);
    while(getchar() != '\n'); 

    do 
    {
        printf("Please enter the RAM of the machine (2048MB - 64000MB): ");
        if(scanf("%d", &ram) != 1) 
        {
            ram = 0;
        }
        while(getchar() != '\n');
    } while(ram < 2048 || ram > 64000);

    do 
    {
        printf("Please enter the VRAM of the machine (10MB - 128MB): ");
        if(scanf("%d", &vram) != 1) 
        {
            vram = 0;
        }
        while(getchar() != '\n');
    } while(vram < 10 || vram > 128);


    system("clear");
    printf("\nIs this configuration correct (y/n) ?\n\nName : %s\nRAM : %d\nVRAM : %d\n\n\n>",name,ram,vram);
    scanf("%s", choice);
    while(choice[0] != 'y' && choice[0] != 'n' || my_strlen(choice) != 1) 
    {
        system("clear");
        printf("\nIs this configuration correct (y/n) ?\n\nName : %s\nRAM : %d\nVRAM : %d\n\nInvalid input.\n>",name,ram,vram);
        scanf("%s", choice);
    }
    if(choice[0] == 'n')
    {
        return 2;
    }

    snprintf(command, sizeof(command), "bash %s %s %d %d >> %s 2>> %s", configuration.script_path, name, ram, vram, configuration.logs_file, configuration.errors_file);
    
    status = executecmd(command);
    if(status != 0)
    {
        printf("\n❌ Error while creating the virtual machine. Logs are in %s.\n",configuration.errors_file);
    }
    else
    {
        printf("\n✅ Virtual machine %s sucessfully created.\n");
    }
    
    printf("\nConfiguration initializing");
    for(i=0;i<3;i++)
    {
        sleep(1);
        printf(".");
        fflush(stdout);
    }

    system("clear");
    configure_vm("data/vmconfig.cfg");
    read_vm_config("data/vmconfig.cfg");
    
    snprintf(command, sizeof(command), "ssh -t alice@192.168.56.101 'sudo adduser %s'",configuration.vmname);
    printf("\nWaiting for the machine to boot up");
    for(i=0;i<3;i++)
    {
        sleep(3);
        printf(".");
        fflush(stdout);
    }
    printf("\n");
    executecmd(command);
    
    printf("User %s created. You can now connect to the machine with 'ssh %s@192.168.56.101'.\n",configuration.vmname, configuration.vmname);
    return 0;
}

void launcher() 
{
    int status = 0;
    char line[COMMAND_SIZE];
    char choice[COMMAND_SIZE];
    char modifiedLine[COMMAND_SIZE];

    FILE *fp = fopen(configuration.commands_file, "r");
    if (fp == NULL) 
    {
        perror("Error opening commands file.");
        return;
    }

    while (fgets(line, sizeof(line), fp) != NULL) 
    {
        unsigned int len = my_strlen(line);
        if (len > 0 && line[len - 1] == '\n') 
        {
            line[len - 1] = '\0';
        }

        printf("\n[%s] Do you want to execute the command? (y/n):",line);
        scanf("%s", choice);
        while(choice[0] != 'y' && choice[0] != 'n' || my_strlen(choice) != 1) 
        {
            printf("Invalid input. Please enter 'y' to execute or 'n' to cancel: ");
            scanf("%s", choice);
        }

        if(choice[0] == 'n')
        {
            continue;
        }

        if(configuration.mode == 0)
        {
            snprintf(modifiedLine, sizeof(modifiedLine), "ssh %s@192.168.56.101 '%s >> %s 2>> %s'",configuration.vmname, line, configuration.output_file, configuration.errors_file);
        }
        else
        {
            snprintf(modifiedLine, sizeof(modifiedLine), "%s >> %s 2>> %s", line, configuration.output_file, configuration.errors_file);
        }

        status = executecmd(modifiedLine);
        if(status != 0)
        {
            printf("❌ Error while executing %s. Logs are in %s.\n",line,configuration.errors_file);
        }
        else
        {
            printf("✅ command %s sucessfully executed\n",line);
        }

        sleep(configuration.wait_time);
    }

    fclose(fp);
}

int menu()
{
    int i = 0;
    int loop = 0;
    char choice[COMMAND_SIZE];

    system("clear");
    printf("\n\n\t Automaton - VM \n\n[1] Configuration\n[2] VM Configuration\n[3] Launch\n\n[q] Quit\n\n>");
    scanf("%s", choice);
    while(choice[0] != '1' && choice[0] != '2' && choice[0] != '3' && choice[0] != 'q' || my_strlen(choice) != 1) 
    {
        system("clear");
        printf("\n\n\t Automaton - VM \n\n[1] Configuration\n[2] VM Configuration\n[3] Launch\n\n[q] Quit\n\n>");
        scanf("%s", choice);
    }

    switch(choice[0])
    {
        case '1':
            system("clear");
            printf("\nConfiguration selected.\n\n");
            configure("data/config.cfg");
            printf("\nReturning to menu");
            for(i=0;i<3;i++)
            {
                sleep(1);
                printf(".");
                fflush(stdout);
            }
            sleep(1);
            menu();
            break;

        case '2':
            system("clear");
            printf("\nVM Configuration selected.\n\n");
            read_config("data/config.cfg");
            loop = vmconfig("data/vmconfig.cfg");
            if(loop == 2)
                vmconfig("data/vmconfig.cfg");
            printf("\nReturning to menu");
            for(i=0;i<3;i++)
            {
                sleep(1);
                printf(".");
                fflush(stdout);
            }
            sleep(1);
            menu();
            break;
        
        case '3':
            system("clear");
            printf("\nLauncher selected.\n");
            read_config("data/config.cfg");   
            read_vm_config("data/vmconfig.cfg");
            preparefiles();
            initialize();
            launcher();
            printf("\nReturning to menu");
            for(i=0;i<3;i++)
            {
                sleep(1);
                printf(".");
                fflush(stdout);
            }
            sleep(1);
            menu();
            break;
        
        case 'q':
            printf("\nQuitting program.");
            return EXIT_SUCCESS;
    }
    
}
