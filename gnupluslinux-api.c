/*
 * https://gnupluslinux.com/anime Api
 * Copyright © 2021 Leonardo Zamboni
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

#include "gnupluslinux-api.h" 
#include "web-scraping/scraping.h"

int lines(char *str) {
  	if (*str == '\0') return 0;
	if (*str++ == '\n') return 1 + lines(str); 
	return lines(str); 
}

char *get_anime_file(char *fol, size_t i) {
	WSCONF cnfg;
  	cnfg.start_block = "alt=\"[IMG]\"> <a href=";
  	cnfg.end_block = "\">";
  	cnfg.enable_print = 0;

  	char *fol_url = malloc(strlen(URL) + (strlen(fol)) * sizeof(char));
  	strcpy(fol_url,URL);
  	strcat(fol_url,fol);
  	if (fol[(strlen(fol)-1)] != '/') strcat(fol_url,"/");

  	get_file(fol_url);

  	char *src_str = get_source(cnfg);
  	if (!src_str) return NULL;

  	int size_str = lines(src_str);
  	if (i > size_str) return NULL;

  	size_t cnt = 0;
  	while (cnt != i) if (*src_str++ == '\n') cnt++;

  	Queue *fl_url = create_queue();
  	while (*src_str != '\n') push_queue(fl_url,*src_str++);

  	char *str = get_str(fl_url->f); 
  	char *url = (char *) malloc((strlen(fol_url) + strlen(str)) * sizeof(char));
  	strcat(url,fol_url);

  	free(fol_url);

  	strcat(url,str);

  	return url;
}
