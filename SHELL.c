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
  
