/*
** main.c for  in /home/daelomin/rendu/CPE/CPE_2015_bsq
**
** Made by Arnould Jean-Michel
** Login   <daelomin@epitech.net>
**
** Started on  Thu Dec  3 15:34:18 2015 Arnould Jean-Michel
** Last update Sun Dec 20 12:23:32 2015 jean-michel arnould
*/

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include "my.h"

void	display(char **map, int lines)
{
  int	i;

  i = 0;
  while (i < lines)
    {
      write(1, map[i], strlen(map[i]));
      i++;
    }
}

void	name(char *tmp, int size, int lines)
{
  int	**map;
  char	**map_char;
  int	size2;
  int	i;

  i = 0;
  size2 = size / lines - 1;
  map = malloc(sizeof (int *) * lines);
  map_char = malloc(sizeof (char *) * lines);
  while (i < lines)
    {
      map_char[i] = malloc(sizeof (char) * (size2 + 2));
      map[i++] = malloc(sizeof (int) * (size2 + 2));
    }
  fill(tmp, map, map_char);
  display(map_char, lines);
  i = 0;
  while (i < lines)
    {
      free(map[i]);
      free(map_char[i++]);
    }
  free(map_char);
  free(map);
}

int	bsq(char *path, int size)
{
  int	nb;
  int	ret;
  int	lines;
  char	*buf;

  buf = malloc(sizeof (char) * size + 1);
  nb = open(path, O_RDONLY);
  ret = read(nb, buf, size);
  if (nb == -1 || ret == -1)
    {
      free(buf);
      close(nb);
      return (1);
    }
  buf[size] = 0;
  lines =  atoi(buf);
  if (lines <= 0)
    {
        free(buf);
	close(nb);
	return (3);
    }
  name(buf, size, lines);
  free(buf);
  close(nb);
  return (0);
}

int	main(int ac, char **av)
{
  struct stat	map;

  if (ac == 2)
    {
      stat(av[1], &map);
      return (bsq(av[1], map.st_size));
    }
  else
    return (-1);
  return (0);
}
