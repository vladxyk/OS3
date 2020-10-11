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

using namespace std;


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
}
