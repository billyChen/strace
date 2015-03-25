/*
** print.c for print in /home/chen_c/rendu/AUSP_strace
** 
** Made by Billy CHEN
** Login   <chen_c@epitech.net>
** 
** Started on  Thu May 15 17:24:34 2014 Billy CHEN
** Last update Tue May 20 11:39:59 2014 Billy CHEN
*/

#include <sys/user.h>
#include <stdio.h>
#include "struct.h"

void				print_argument(struct user_regs_struct *reg, int c, int pid)
{
  check_and_print(arg[reg->rax].rdi, reg->rdi, 0, pid);
  if (arg[reg->rax].rsi != 0 && c != -1)
    {
      check_and_print(arg[reg->rax].rsi, reg->rsi, 1, pid);
      if (arg[reg->rax].rdx != 0)
	{
	  check_and_print(arg[reg->rax].rdx, reg->rdx, 1, pid);
	  if (arg[reg->rax].r10 != 0)
	    {
	      check_and_print(arg[reg->rax].r10, reg->r10, 1, pid);
	    }
	}
    }
}

void				return_value(struct user_regs_struct *reg, int pid)
{
  if (arg[reg->orig_rax].ret != 0)
    {
      printf(" = ");
      check_and_print(arg[reg->orig_rax].ret, reg->rax, 0, pid);
      printf("\n");
    }
}

void				syscall_name(struct user_regs_struct *reg, int pid)
{
  printf("%s(", sys[reg->rax].name);
  if (arg[reg->rax].rdi != 0)
    {
      print_argument(reg, 0, pid);
    }
  printf(")");
}
