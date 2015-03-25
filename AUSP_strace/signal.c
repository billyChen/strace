/*
** signal.c for signal in /home/chen_c/rendu/AUSP_strace
** 
** Made by Billy CHEN
** Login   <chen_c@epitech.net>
** 
** Started on  Thu May 15 17:15:08 2014 Billy CHEN
** Last update Sun May 18 19:58:05 2014 eliot bardet
*/

#include <signal.h>
#include <stdio.h>
#include <sys/ptrace.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include "struct.h"

void				sig_handler(int sig)
{
  signal(sig, NULL);
  kill(getpid(), sig);
}

void				set_signal()
{
  signal(SIGINT, &sig_handler);
}

int				check_wait_status(int status, int pid)
{
  if (WIFEXITED(status))
    {
      printf(" = ?\n");
      return (-1);
    }
  else if (WIFSIGNALED(status))
    return (-1);
  else
    {
      if (WSTOPSIG(status) == SIGINT)
	{
	  ptrace(PTRACE_KILL, pid, NULL, NULL);
	  return (0);
	}
    }
  return (0);
}
