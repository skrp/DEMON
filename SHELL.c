//////////////////////////////////
// SHELL - standard DEMON skeleton
#include <stdio.h>
#include <syslog.h>
#include <fcntl.h>
#include <signal.h>
#include <sys/resource.h>
// FNS /////////////////////////
void daemonize(const char *code)
{
  int i, fd0, fd1, fd2;
  pid_t pid;
  struct rlimit rl;
  struct sigaction sa;
// 1 - clear file creation mask
  umask(0);
// 2 - orphan child
  if ((pid = fork()) < 0)
    { printf("%s: cant fork\n", code); exit(1); }
  else if (pid != 0)
    exit(0); // kill parent
// 3 - lose TTY
  setsid();
  sa.sa_handler = SIG_IGN;
  sigemptyset(&sa.sa_mask);
  sa.sa_flags = 0;
  if (sigaction(SIGHUP, &sa, NULL) < 0)
    { printf("%s: cant ignore SIGHUP", code); exit(1); }
  if ((pid = fork()) < 0)
    { printf("%s: cant fork", code); exit(1); }
  else if (pid != 0)
     exit(0); // kill parent
// 4 - chdir if need
/*
  if (chdir("/") < 0)
    { printf("%s: fail chdir", code); exit(1); }
*/
// 5 - purge FD
  if (getrlimit(RLIMIT_NOFILE, &rl) < 0)
    { printf("%s: cannt get file limit", code); exit(1); }
  if (rl.rlim_max == RLIM_INFINITY)
    rl.rlim_max = 1024;
  for (i = 0; i < rl.rlim_max; i++)
    close(i);
  fd0 = open("/dev/null", O_RDWR);
  fd1 = open("/dev/null", O_RDWR);
  fd2 = open("/dev/null", O_RDWR);
  if (fd0 != 0 || fd1 != 1 || fd2 != 2)
    { printf("%s: unexpected FD: %d %d %d", fd0, fd1, fd2); exit(1); }
}
