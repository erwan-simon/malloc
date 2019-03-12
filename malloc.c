/*
** malloc.c for malloc in /home/erwan/Code/teck/PSU_2016_malloc
** 
** Made by erwan
** Login   <erwan.simon@epitech.eu>
** 
** Started on  Thu Jan 26 14:08:12 2017 erwan
** Last update Sat Feb 11 16:09:33 2017 Antoine
*/

#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/mman.h>
#include <pthread.h>
#include "linked_list.h"

void		my_put_nbr(int);
pthread_mutex_t	g_mutex = PTHREAD_MUTEX_INITIALIZER;

void		*malloc(size_t size)
{
  void		*ptr;

  if (size % 8)
    size = ((size / 8) * 8) + 8;
  pthread_mutex_lock(&g_mutex);
  ptr = searchSlot(size);
  pthread_mutex_unlock(&g_mutex);
  return (ptr);
}

void    free(void *ptr)
{
  pthread_mutex_lock(&g_mutex);
  free_elem(ptr);
  pthread_mutex_unlock(&g_mutex);
}

void		*realloc(void *ptr, size_t size)
{
  char		*res;
  char		*src;
  t_block	*scroll;

  if (ptr == NULL)
    return (malloc(size));
  scroll = g_start;
  while (scroll && scroll->_end != ptr)
    scroll = scroll->_next;
  if (scroll != NULL && scroll->_blockSize >= size)
    {
      pthread_mutex_lock(&g_mutex);
      scroll->_effSize = size;
      pthread_mutex_unlock(&g_mutex);
      return (ptr);
    }
  src = ptr;
  if ((res = malloc(size)) == NULL)
    return (NULL);
  pthread_mutex_lock(&g_mutex);
  res = memcpy(res, src, size);
  pthread_mutex_unlock(&g_mutex);
  free(ptr);
  return (res);
}

void		show_alloc_mem()
{
  t_block	*scroll;

  printf("break : %p\n", sbrk(0));
  scroll = g_start;
  while (scroll)
    {
      if (scroll->_effSize > 0)
	printf("%p - %p : %d\n", scroll->_end,
	       scroll->_end + scroll->_effSize, (int) scroll->_effSize);
      scroll = scroll->_next;
    }
}
