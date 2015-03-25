/*
** main.c for main in /home/chen_c/rendu/AUSP_strace
** 
** Made by Billy CHEN
** Login   <chen_c@epitech.net>
** 
** Started on  Sun May  4 17:56:03 2014 Billy CHEN
** Last update Sun May 18 19:57:13 2014 eliot bardet
*/

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <syscall.h>
#include <sys/ptrace.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/time.h>
#include <unistd.h>
#include <errno.h>
#include <sys/user.h>
#include "struct.h"
#include <sys/resource.h>
#include <stdlib.h>

int				option_p(int argc, char **argv)
{
  int				pid;

  if (argc < 3)
    {
      printf("[USAGE]: ./strace -p [trace]\n");
      exit(EXIT_FAILURE);
    }
  pid = atoi(argv[2]);
  if (ptrace(PTRACE_ATTACH, pid, NULL, NULL) == -1)
    {
      perror("PTRACE_ATTACH");
      return (-1);
    }
  return (pid);
}

int				main(int argc, char **argv)
{
  int				pid;

  if (argc >= 2)
    {
      if (!strcmp("-p", argv[1]))
	pid = option_p(argc, argv);
      else
	pid = trace_prog(argc, argv);
      if (pid == -1)
	exit(EXIT_FAILURE);
      set_signal();
      start_tracee(pid);
      if (!strcmp("-p", argv[1]))
	ptrace(PTRACE_DETACH, pid, NULL, NULL);
      else
	kill(pid, SIGKILL);
    }
  return (0);
}
