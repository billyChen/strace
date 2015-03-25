/*
** check_and_print.c for check_and_print in /home/chen_c/rendu/AUSP_strace
** 
** Made by Billy CHEN
** Login   <chen_c@epitech.net>
** 
** Started on  Thu May 15 17:24:57 2014 Billy CHEN
** Last update Sun May 18 20:22:09 2014 eliot bardet
*/

#include <sys/ptrace.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "struct.h"

void				put_string(long int val, int pid)
{
  char				buf[4];
  long				result;
  void				*ptr;
  int				printed;

  printf("\"");
  ptr = (void *) val;
  printed = 1;
  while (printed)
    {
      result = ptrace(PTRACE_PEEKTEXT, pid, ptr, NULL);
      if (result == -1)
	{
	  perror("ptrace_peektext");
	  exit(EXIT_FAILURE);
	}
      memmove(buf, &result, sizeof(result));
      buf[4] = 0;
      printed = printf("%s", buf);
      ptr = (char *)ptr + 4;
    }
    printf("\"");
}

void				check_and_print(int args, long int val, int bol, int pid)
{
  if (bol == 1)
    printf(", ");
  if (args == INT)
    printf("%d", (int)val);
  else if (args == VOID_POINTER)
    printf("%p", (void *)val);
  else
    {
      if (args == STRING)
	put_string(val, pid);
      else if (args == PTR_POINTER)
	printf("%p", (void *)&val);
      else
	{
	  if (args == CHAR)
	    printf("%c", (char)val);
	  else if (args == FLOAT || args == DOUBLE)
	    printf("%f", (float)val);
	  else
	    printf("?");
	}
    }
}
