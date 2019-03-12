/*
** linked_list.c for malloc in /home/erwan/Code/teck/PSU_2017_malloc
** 
** Made by erwan
** Login   <erwan.simon@epitech.eu>
** 
** Started on  Thu Jan 26 11:16:09 2017 erwan
** Last update Sat Feb 11 16:11:32 2017 Antoine
*/

#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include "linked_list.h"

t_block         *add(t_block *block, size_t size)
{
  t_block	*new;

  if ((new = sbrk(getpagesize() *
		  ((size / getpagesize()) + 1) + sizeof(t_block))) == NULL)
    return (NULL);
  new->_blockSize = (getpagesize() * ((size / getpagesize()) + 1));
  new->_effSize = size;
  new->_prev = block;
  new->_next = NULL;
  if (block == NULL)
    g_start = new;
  else
    block->_next = new;
  return (new);
}

t_block		*split(t_block *block, size_t size)
{
  t_block	*new;

  new = (void *) (block->_end + block->_effSize);
  new->_effSize = size;
  new->_blockSize = block->_blockSize - sizeof(t_block) - block->_effSize;
  new->_prev = block;
  new->_next = block->_next;
  block->_blockSize = block->_blockSize - (new->_blockSize + sizeof(t_block));
  block->_next = new;
  return (new);
}

void		*searchSlot(size_t size)
{
  t_block	*scroll;

  if (g_start == NULL)
    return (add(NULL, size)->_end);
  scroll = g_start;
  while (scroll)
    {
      if (scroll->_effSize == 0 && scroll->_blockSize >= size)
      	{
      	  scroll->_effSize = size;
      	  return (scroll->_end);
      	}
      if (scroll->_effSize > 0 && scroll->_blockSize
	  - scroll->_effSize >= sizeof(t_block) + size)
      	return (split(scroll, size)->_end);
      scroll = scroll->_next;
    }
  return (add(scroll, size)->_end);
}

t_block		*merge(t_block *block)
{
  if (block->_next != NULL && block->_next->_effSize == 0)
    {
      block->_blockSize += block->_next->_blockSize + sizeof(t_block);
      block->_next = block->_next->_next;
    }
  if (block->_prev != NULL && block->_prev->_effSize == 0)
    {
      block->_prev->_blockSize += block->_blockSize;
      block->_prev->_next = block->_next;
      return (block->_prev);
    }
  return (block);
}

void		free_elem(void *ptr)
{
  t_block	*scroll;

  scroll = g_start;
  while (scroll)
    {
      if (scroll->_end == ptr)
	{
	  scroll = merge(scroll);
	  scroll->_effSize = 0;
	  return ;
	}
      scroll = scroll->_next;
    }
}
