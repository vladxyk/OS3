#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <dirent.h>
#include <iomanip>
#include <sys/types.h>
#include "lab2.hpp"
#include <sys/wait.h>
#include <errno.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>
#include <stdio.h>

using namespace std;

int proc(char *name){
  int rv;
  char *path[] = {name, 0};
  switch (fork())
  {
  case -1:
    perror("fork");
    return 1;
  case 0:
    cout << "ppid: " << getppid() << endl;
    cout << "pid: " << getpid() << endl;
    execv(path[2], path);
  default:
    wait(&rv);
  }
  return 0;
}

int procFone(char *name){
  int rv;
  char *path[] = {name, 0};
  switch (fork()) 
  {
  case -1:
    perror("fork");
    return 1;
  case 0:
    setsid();
    cout << "ppid: " << getppid() << endl;
    cout << "pid: " << getpid() << endl;
    execv(path[2], path);
    _exit (EXIT_FAILURE);
    //kill(getppid(), SIGTERM);
  default:
    wait(&rv);
  }
  return 0;
}


void sighandler(int signum) 
{ 
    cout << "Signal received successfully" << endl; 
}

int recvsig() 
{
  int sigmun;
  cin >> sigmun;

  if (signal(sigmun, sighandler) == SIG_ERR);
    return 1; 
      
  return 0;
}

int sendsig(char *name){
  int signum;
  cout << "enter signum" << endl;
  cin >> signum;
  pid_t pid = getpid();
  if (kill(pid, signum) == -1)
    return 1;
  return 0;
}

int main(int argc, char *argv[]){
  if (string(argv[1]) == "-h"){
    help();
  } 
    
  if (string(argv[1]) == "--help"){
    help();
  }

  if (string(argv[1]) == "-mf"){
    rename(argv[2] , argv[3]);
  }

  if (string(argv[1]) == "-rmf"){
    remove(argv[2]);
  }

  if (string(argv[1]) == "-cf"){
    copyFile(argv[2], argv[3]);
  }

  if (string(argv[1]) == "-saf"){
    show_all_files(argv[2]);
  }

  if (string(argv[1]) == "-sap"){
    showp();
  }

  if (string(argv[1]) == "-ssf"){
    cout << "Size is " << showsize(argv[2]) << " bytes" << endl;
  }

  if (string(argv[1]) == "-p"){
    proc(argv[2]);
  }
  
  if (string(argv[1]) == "-pf"){
    procFone(argv[2]);
  }

  if (string(argv[1]) == "-rsig"){
    recvsig();
  }

  if (string(argv[1]) == "-ssig"){
    sendsig(argv[2]);
  }
}
