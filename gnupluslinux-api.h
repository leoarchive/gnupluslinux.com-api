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
#ifndef GNUPLUSLINUX_API_H
#define GNUPLUSLINUX_API_H

#include <stdlib.h>

#define URL "https://gnupluslinux.com/anime/"

char *get_anime_file(char *folder, size_t index);

#endif
