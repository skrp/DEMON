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
// 2 - session leader / lose TTY
  if ((pid = fork()) < 0)
    { printf("%s: cant fork\n", code); exit(1); }
  else if (pid != 0)
    exit(0); // kill parent
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
