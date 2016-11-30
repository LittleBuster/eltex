#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <dirent.h>
#include <unistd.h>
#include <stdbool.h>
#include <stdlib.h>
#include <dlfcn.h>

#include "plist.h"

struct lib_info {
	char description[255];
	char func_name[255];
};


bool check_is_lib(const char *filename)
{
	char *p_str = NULL;
	char fname[255];

	strncpy(fname, filename, 255);

	p_str = strtok(fname, ".");
	if (p_str == NULL)
		return false;

	p_str = strtok(NULL, ".");
	if (p_str == NULL)
		return false;

	if (!strcmp(p_str, "so"))
		return true;

	return false;
}

struct plugins_list *load_plugins(const char *path)
{
	DIR *dir;
	bool is_found = false;
	struct dirent *f_cur;
	struct plugins_list *plist = NULL;	    

    if ((dir = opendir(path)) == NULL) {
    	puts("Fail reading plugins folder.");
        return NULL;
    }

    while ((f_cur = readdir(dir)) != NULL) {
    	if (check_is_lib(f_cur->d_name)) {
    		char full_path[512];
    		struct lib_info* (*get_lib_info)(void);
    		struct lib_info *info;

    		strncpy(full_path, path, 255);
    		strncat(full_path, f_cur->d_name, 255);
    		is_found = true;

    		struct plugin *plugin = (struct plugin *)malloc(sizeof(struct plugin));
    		plugin->lib_id = dlopen(full_path, RTLD_NOW);
    		if (plugin->lib_id == NULL) {
    			printf("Fail loading %s plugin!\n", f_cur->d_name);
    			free(plugin);
    			continue;
    		}

    		*(void **)(&get_lib_info) = dlsym(plugin->lib_id, "get_lib_info");
    		if (get_lib_info == NULL) {
    			dlclose(plugin->lib_id);
    			free(plugin);
    			puts("Fail loading get_lib_info function.");
    			continue;
    		}

    		info = get_lib_info();
    		strncpy(plugin->description, info->description, 255);

    		*(void **)(&plugin->func) = dlsym(plugin->lib_id, info->func_name);
    		if (get_lib_info == NULL) {
    			printf("Fail loading %s function.\n", info->func_name);
    			dlclose(plugin->lib_id);
    			free(plugin);
    			continue;
    		}

    		plist = plugins_list_append(plist, plugin);
    		printf("Plugin %s loaded succesfully.\n", f_cur->d_name);
    	}
    }
    closedir(dir);

    if (!is_found)
    	puts("Plugins not found!");

	return plist;
}


int main(void)
{
	struct plugins_list *plist = load_plugins("./plugins/");

	if (plist == NULL)
		exit(-1);

	for (;;) {
		bool is_found = false;
		unsigned i = 0;	
		unsigned menu;
		int ret_val;
		int a = 0;
		int b = 0;

		puts("==========================");
		puts("     CALCULATOR MENU");
		puts("==========================");
		
		// Printing exists plugins
		for (struct plugins_list *l = plist; l != NULL; l = plugins_list_next(l)) {
			struct plugin *plugin = plugins_list_get_plugin(l);
			printf("[%u] %s\n", i, plugin->description);
			i++;
		}		
		printf("[-1] Exit.\n %s", ">");

		ret_val = scanf("%u", &menu);
		if (ret_val == 0) {
			puts("Wrong menu number.");
			continue;
		}

		// Exit program
		if (menu == -1)
			break;

		puts("\nPlease, enter nums:");
		printf("a=");
		ret_val = scanf("%d", &a);
		if (ret_val == 0) {
			puts("Wrong integer value.");
			continue;
		}

		printf("b=");
		ret_val = scanf("%d", &b);
		if (ret_val == 0) {
			puts("Wrong integer value.");
			continue;
		}

		i = 0;
		for (struct plugins_list *l = plist; l != NULL; l = plugins_list_next(l)) {
			if (menu == i) {
				is_found = true;
				struct plugin *plugin = plugins_list_get_plugin(l);
				printf("Result: %d\n", plugin->func(a, b));
				break;
			}
			i++;
		}
		if (!is_found)
			puts("Wring menu number!");
	}

	// Free all
	for (struct plugins_list *l = plist; l != NULL; l = plugins_list_next(l)) {
		struct plugin *plugin = plugins_list_get_plugin(l);
		dlclose(plugin->lib_id);
	}
	plugins_list_free_all(plist);
	puts("Goodbye.");
	return 0;
}