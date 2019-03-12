/*
** linked_list.h for malloc in /home/erwan/Code/teck/PSU_2017_malloc
** 
** Made by erwan
** Login   <erwan.simon@epitech.eu>
** 
** Started on  Thu Jan 26 11:16:50 2017 erwan
** Last update Sat Feb 11 16:10:48 2017 Antoine
*/

#ifndef LINKED_LIST_H_
# define LINKED_LIST_H_

typedef struct		s_block {
  size_t		_effSize;
  size_t		_blockSize;
  struct s_block	*_prev;
  struct s_block	*_next;
  char			_end[1];
}			t_block;

t_block			*add(t_block*, size_t);
t_block			*split(t_block*, size_t);
void			*searchSlot(size_t);
void			free_elem(void *);
void			show_alloc_mem(void);

void			*malloc(size_t);
void			free(void *);
void			*realloc(void *, size_t);

t_block			*g_start;

#endif /* !LINKED_LIST_H_ */
