#include <stdio.h>
#include <string.h>


int main() {
	char s[22];
	strcpy(s, "dsdsdsdso");

	char *str = strtok(s, ".");
	puts(str);
}
