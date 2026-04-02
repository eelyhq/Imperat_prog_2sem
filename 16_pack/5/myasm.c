#include <stdio.h>
#include <string.h>
#include <dlfcn.h>

typedef struct State {
    char* regs [256];
} State;

State state = {0};

int main()
{
    char buffer[1001];
    char* f = fgets(buffer, 1001, stdin);

    while (f != NULL)
    {
        buffer[strcspn(buffer, "\r\n")] = '\0'; // delete \n
        char plugin_name[37] = "./"; // names
        char func_name[37];
        char* core_name_plugin = "core"; // for case, when name of plugin missed

        char* args[3]; // create array for args
        char arg0[1001];
        char arg1[1001];
        char arg2[1001];
        args[0] = arg0;
        args[1] = arg1;
        args[2] = arg2;

        char* separator = " "; // frist, separate plugin + func or just func

        char* token; // var for strtok

        token = strtok(buffer, separator); // now in token separate plugin + func or just func

        if (token == NULL)
        {
            break;
        }
        int num_args = 0;
        char* token_for_args = strtok(NULL, separator); // separate args

        while (token_for_args)
        {
            strcpy(args[num_args], token_for_args);
            num_args++;
            token_for_args = strtok(NULL, separator);
        }

        separator = ":"; // second, try to separate plugin and func

        char* token2;
        char* token3;

        token2 = strtok(token, separator);

        token3 = strtok(NULL, separator); // if there is NULL, then there is no plugin name

        if (token3 == NULL) // missed name of plugin -> plugin - core
        {
            strcat(plugin_name, core_name_plugin);
            strcpy(func_name, token2);
        }
        else
        {
            strcat(plugin_name, token2);
            strcpy(func_name, token3);
        }

        char num_args_str[4]; // convert int num_args to string num_args for making func name
        sprintf(num_args_str, "%d", num_args);

        separator = "_"; // use this var for underscore

        strcat(func_name, separator); // concat to name func underscore and num of args
        strcat(func_name, num_args_str);

        char* extension = ".so";
        strcat(plugin_name, extension); // add extension to plugin name

        void* hDll = dlopen(plugin_name, RTLD_LAZY);
        if (hDll == NULL)
        {
            f = fgets(buffer, 1001, stdin);
            memmove(plugin_name, plugin_name + 2, strlen(plugin_name) + 1); // skip ./
            plugin_name[strlen(plugin_name) - 3] = '\0'; // delete .so
            printf("Missing plugin %s\n", plugin_name);
            continue;
        }

        if (num_args == 0)
        {
            typedef void (*func_t)(State*);
            func_t func = (func_t)dlsym(hDll, func_name);
            if (func == NULL)
            {
                dlclose(hDll);
                f = fgets(buffer, 1001, stdin);
                memmove(plugin_name, plugin_name + 2, strlen(plugin_name) + 1); // skip ./
                plugin_name[strlen(plugin_name) - 3] = '\0'; // delete .so
                printf("Missing function %s in plugin %s\n", func_name, plugin_name);
                continue;
            }
            func(&state);
        }
        else  if (num_args == 1)
        {
            typedef void (*func_t)(State*, char*);
            func_t func = (func_t)dlsym(hDll, func_name);
            if (func == NULL)
            {
                dlclose(hDll);
                f = fgets(buffer, 1001, stdin);
                memmove(plugin_name, plugin_name + 2, strlen(plugin_name) + 1); // skip ./
                plugin_name[strlen(plugin_name) - 3] = '\0'; // delete .so
                printf("Missing function %s in plugin %s\n", func_name, plugin_name);
                continue;
            }
            func(&state, args[0]);
        }
        else  if (num_args == 2)
        {
            typedef void (*func_t)(State*, char*, char*);
            func_t func = (func_t)dlsym(hDll, func_name);
            if (func == NULL)
            {
                dlclose(hDll);
                f = fgets(buffer, 1001, stdin);
                memmove(plugin_name, plugin_name + 2, strlen(plugin_name) + 1); // skip ./
                plugin_name[strlen(plugin_name) - 3] = '\0'; // delete .so
                printf("Missing function %s in plugin %s\n", func_name, plugin_name);
                continue;
            }
            func(&state, args[0], args[1]);
        }
        else
        {
            typedef void (*func_t)(State*, char*, char*, char*);
            func_t func = (func_t)dlsym(hDll, func_name);
            if (func == NULL)
            {
                dlclose(hDll);
                f = fgets(buffer, 1001, stdin);
                memmove(plugin_name, plugin_name + 2, strlen(plugin_name) + 1); // skip ./
                plugin_name[strlen(plugin_name) - 3] = '\0'; // delete .so
                printf("Missing function %s in plugin %s\n", func_name, plugin_name);
                continue;
            }
            func(&state, args[0], args[1], args[2]);
        }
        dlclose(hDll);
        f = fgets(buffer, 1001, stdin);
    }
    return 0;
}