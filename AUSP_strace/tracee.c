/*
** tracee.c for tracee in /home/chen_c/rendu/AUSP_strace
** 
** Made by Billy CHEN
** Login   <chen_c@epitech.net>
** 
** Started on  Thu May 15 17:21:21 2014 Billy CHEN
** Last update Sun May 18 23:04:16 2014 eliot bardet
*/

#include <unistd.h>
#include <stdlib.h>
#include <sys/ptrace.h>
#include <sys/user.h>
#include <errno.h>
#include <sys/time.h>
#include <sys/resource.h>
#include <sys/wait.h>
#include "struct.h"

void				getregs(int pid, int *count)
{
  struct user_regs_struct	reg;
  short				opcode;

  if (ptrace(PTRACE_GETREGS, pid, NULL, &reg) == -1)
    {
      perror("PTRACE_GETREGS");
      return;
    }
  if (*count == 1)
    return_value(&reg, pid);
  else
    {
      if ((opcode = ptrace(PTRACE_PEEKTEXT, pid, reg.rip, NULL)) == -1)
	{
	  perror("PTRACE_PEEKTEXT");
	  return;
	}
      if (opcode == 0x050f)
	{
	  syscall_name(&reg, pid);
	  *count = 0;
	}
      else
	*count = 1;
    }
}

int				start_tracee(int pid)
{
  int				status;
  int   			count;

  count = 0;
  wait4(pid, &status, 0, NULL);
  if (check_wait_status(status, pid))
    return EXIT_FAILURE;
  while (42)
    {
      if (ptrace(PTRACE_SINGLESTEP, pid, NULL, NULL) == -1)
	{
	  perror("PTRACE_SINGLESTEP");
	  return (EXIT_FAILURE);
	}
      wait4(pid, &status, 0, NULL);
      if (check_wait_status(status, pid))
	return (EXIT_FAILURE);
      getregs(pid, &count);
      if (count == 0)
	count = 1;
      else
	count = 0;
    }
  return (EXIT_SUCCESS);
}

int				trace_prog(int argc, char **argv)
{
  int				pid;

  pid = fork();
  if (pid == 0)
    {
      if (ptrace(PTRACE_TRACEME, getpid(), NULL, NULL) == -1)
	{
	  perror("PTRACE_TRACEME");
	  return (-1);
	}
      if ((execvp(argv[1], &argv[1])) == -1)
	{
	  perror("EXECVP");
	  return (-1);
	}
    }
  return (pid);
}
