/*
** struct.h for struct in /home/chen_c/rendu/AUSP_strace
** 
** Made by Billy CHEN
** Login   <chen_c@epitech.net>
** 
** Started on  Mon May  5 21:02:05 2014 Billy CHEN
** Last update Sun May 18 20:39:32 2014 eliot bardet
*/

#ifndef STRUCT_H
# define STRUCT_H

# include <sys/types.h>
# include <sys/user.h>
# include <sys/time.h>
# include <sys/resource.h>

# define INT (5)
# define POINTER (1)
# define STRING (2)
# define VOID (3)
# define INT_POINTER (4)
# define VOID_POINTER (6)
# define PTR_POINTER (7)
# define DOUBLE (8)
# define DOUBLE_POINTER (9)
# define CHAR (10)
# define FLOAT (11)

typedef struct	s_name
{
  int		pos;
  char		name[25];
}		t_name;

typedef struct	s_prot
{
  int		pos;
  int		rdi;
  int		rsi;
  int		rdx;
  int		r10;
  int		ret;
}		t_prot;

extern t_name	sys[];
extern t_prot	arg[];

int	trace_prog(int, char **);
void	set_signal();
int	start_tracee(int);
int	kill(pid_t, int);
void	perror(const char *);
void	return_value(struct user_regs_struct *, int);
void	syscall_name(struct user_regs_struct *, int);
pid_t	wait4(pid_t, int *, int, struct rusage *);
int	check_wait_status(int, int);
void	check_and_print(int, long int, int, int);

#endif /* !STRUCT_H */
