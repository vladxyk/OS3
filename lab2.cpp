#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <dirent.h>
#include <iomanip>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <experimental/filesystem>


using namespace std;

void help(){
  cout << "AUTHORS:" << endl << "Goriunova" << endl << "Eremin" << endl << "Dultseva" << endl << endl;
  cout << "AVAILABLE OPTIONS: " << endl;
  cout << "-mf: move a file" << endl;
  cout << "-cf: copy a file" << endl;
  cout << "-rmf: remove a file" << endl;
  cout << "-ssf: show size of file" << endl;
  cout << "-saf: show all files in directory" << endl;
  cout << "-sap: show all processes" << endl << endl;
  cout << "PROJECT DESCRIPTION: " << endl << "Working with the file system" << endl << endl;
  cout << "EXAMPLES OF STARTING: " << endl << "./oslab2 -cf from_file to_file" << endl;
}

void show_all_files(const char *path){
  DIR *dir = opendir(path);
  dirent *entry;
  if (dir == NULL){
    return;
  }

  while ((entry = readdir(dir)) != NULL){
    cout << entry->d_name << endl;
  }
  closedir(dir);
}

int showsize(string filesize){
	int allsize = 0;
	
  struct stat fileinfo;
  if(stat(filesize.c_str(), &fileinfo) != 0){
    return -1;
  }
  if(S_ISDIR(fileinfo.st_mode)){
    DIR *dir = opendir(filesize.c_str());
    dirent *entry;
    while((entry = readdir(dir)) != nullptr){
      if((strcmp(entry->d_name, ".") != 0) && (strcmp(entry->d_name, "..") != 0)){
        string next = filesize + "/" + entry->d_name;
        allsize += showsize(next);
      }
    }
    closedir(dir);
    return allsize;
  }
  else{
    return fileinfo.st_size;
  }
}

streampos size(const char *s_path){
  ifstream size(s_path);
  size.seekg(0, ios::end);
  int file_size = size.tellg();
  cout<<"Size of the file is"<<" "<< file_size<<" "<<"bytes" << endl;
  cout << "help" << endl;
  return 0;
}

bool copyFile(const char *copyfromfile, const char *copytofile){
  ifstream cff(copyfromfile);
  ofstream ctf(copytofile);
 
  char sym;
  // цикл посимвольного чтения
  while (cff)
  {
    cff.get(sym);
    if (cff) {
      ctf.put(sym);
    }
  }
  cff.close();
  ctf.close();
  return 0;
}

int showp()
{
  DIR *dir = opendir("/proc/");
  if (dir == nullptr){
        return -1;
  }
  dirent *entry;

  while ((entry = readdir(dir)) != NULL){
    cout << entry->d_name << endl;
  }
  closedir(dir);
}