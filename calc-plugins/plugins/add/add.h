#ifndef ADD_LIB_H_
#define ADD_LIB_H_

struct lib_info {
	char description[255];
	char func_name[255];
};

struct lib_info *get_lib_info(void);

int add(int a, int b);

#endif