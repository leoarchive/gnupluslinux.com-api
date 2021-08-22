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
#include <stdint.h>

#include "gnupluslinux-api.h" 
#include "web-scraping/scraping.h"

uint8_t lines(char *str) 
{
  	if (*str == '\0') return 0;

	if (*str++ == '\n') return 1 + lines(str); 

	return lines(str); 
}

void set_config(WSCONF *cnfg)
{
  	cnfg->start_block = "alt=\"[IMG]\"> <a href=";
  	cnfg->end_block = "\">";
  	cnfg->enable_print = 0;
}

uint8_t address_bar(char c)
{
	return (c == '/' ? 1 : 0); 
}

char *get_anime_file(char *fol, size_t i) 
{
	WSCONF cnfg;

	set_config(&cnfg);

	uint16_t size = strlen(URL) + strlen(fol);

	if (!address_bar(fol[(strlen(fol)) - 1]))
	{
		size++;
	}	

  	char *fol_url = malloc(size * sizeof(char));

  	strcpy(fol_url, URL);
  	strcat(fol_url, fol);

	if (!address_bar(fol[(strlen(fol)) - 1]))
	{
		fol_url[strlen(fol_url)] = '/';
	}	

  	get_file(fol_url);

  	char *src_str = get_source(cnfg);
  	if (!src_str) return NULL;

  	uint16_t size_str = lines(src_str);
  	if (i > size_str) return NULL;

	size_t cnt = 0;
	do
	{
		if (*src_str++ == '\n') 
		{
			cnt++;
		}
	}
	while (cnt != i);


  	Queue *fl_url = create_queue();

	do
  	{
		push_queue(fl_url, *src_str);
		*src_str++;
	} 
	while (*src_str != '\n');

	push_queue(fl_url, '\n');
	push_queue(fl_url, '\0');

	char *str = (char *) malloc((count_nodes(fl_url->f) + strlen(fol_url)) * sizeof(char));

	strcpy(str, fol_url);
  	strcat(str, get_str(fl_url->f));

	free(fol_url);
	free(fl_url);
	
  	return str;
}
