#include <stdio.h>

#include "gnupluslinux-api.h"

int main(int argc, char *argv[]) 
{
	printf("%s", get_anime_file(argv[1], atoi(argv[2])));
	return 0;
}
