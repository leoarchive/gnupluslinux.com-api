/*
 * https://gnupluslinux.com/anime Api
 * Copyright © 2021 Leonardo Zamboni 🌎 leozamboni.dev
 *
 * this program is free software: you can redistribute it and/or modify
 * it under the terms of the gnu general public license as published by
 * the free software foundation, either version 3 of the license, or
 * (at your option) any later version.
 * 
 * this program is distributed in the hope that it will be useful,
 * but without any warranty; without even the implied warranty of
 * merchantability or fitness for a particular purpose.  see the
 * gnu general public license for more details.
 * 
 * you should have received a copy of the gnu general public license
 * along with this program.  if not, see <http://www.gnu.org/licenses/>.
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "web-scraping/scraping.h"

#define URL "https://gnupluslinux.com/anime/"

#define CURL_CMD "curl --output source.png "

int count_str_lines(char *str) {
  	if (*str == '\0') return 0;
	if(*str == '\n') { *str++; return 1 + count_str_lines(str); }
  	else { *str++; return count_str_lines(str); }
}

int get_img(WSCONF cnfg, char *url, size_t i) {
  	get_file(url);

  	char *srcstr = get_source(cnfg);
  	if (!srcstr) return 1;

  	int sizestr = count_str_lines(srcstr);
  	if (i > sizestr) return 2;

  	size_t cnt = 0;
  	while (cnt != i) if (*srcstr++ == '\n') cnt++;

  	Queue *flurl = create_queue();
  	while (*srcstr != '\n') push_queue(flurl,*srcstr++);

  	char *str = get_str(flurl->f); 
  	char *cmd;
  	cmd = (char *) malloc((
    		strlen(CURL_CMD) +
    		strlen(url) + 
    		strlen(str)) * sizeof(char));
  	strcpy(cmd,CURL_CMD);
  	strcat(cmd,url);
  	strcat(cmd,str);

  	printf("%s\n", cmd);
  	system(cmd);

  	free(cmd);
  	free(flurl);
  	return 0;
}

int main(int argc, char *argv[]) {
  	WSCONF cnfg;

  	cnfg.string_init = "alt=\"[IMG]\"> <a href=";
  	cnfg.string_end = "\">";
  	cnfg.enable_print = false;

  	char *url = malloc((strlen(argv[2]) + strlen(URL) + 1) * sizeof(char));
  	strcpy(url,URL);
  	strcat(url,argv[2]);
  	if (argv[2][(strlen(argv[2]) - 1)] != '/') 
    		strcat(url,"/");

  	int i = strtol(argv[1],NULL,10);
  	int rgetimg = get_img(cnfg,url,i);
  	if (rgetimg == 1) printf("Error in get source\n");
  	else if (rgetimg == 2) printf("Invalid index\n");

  	free(url);
  	return 0;
}
