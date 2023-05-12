#include <fstream>
#include <iostream>
#include <sstream>
#include <sys/time.h>
#include <ctime>
#include <sys/stat.h>
#include <stdio.h>
#include <string>
#include <sys/io.h>
#include <chrono>

using namespace std;
using std::cout;
using std::endl;

class GPM_LOG
{
  public:
  string foldername;
  string folderPath;
  string LOGPath;
  string GPMFolderPath;
  string txtName;
  string msec;

void CreateFolder()
{
  time_t now = time(0);
  tm*ltm = localtime(&now);

  std::stringstream tt;
  tt << ltm->tm_hour << ":" << ltm->tm_min << ":" << ltm->tm_sec;
  txtName = tt.str();

  std::stringstream foldertime; //Load systime to string
  foldertime << 1900 + ltm->tm_year << "-" << 1 + ltm->tm_mon << "-" 
  << ltm->tm_mday;

  foldername = foldertime.str();

  folderPath = "/home/gpm/catkin_ws/GPM_LOG/";
  GPMFolderPath = folderPath + foldername + "/" + txtName + " LOG.txt";
  string command;
  command = "mkdir -p " + folderPath + foldername;

  LOGPath = folderPath + foldername;
  const char* filename = LOGPath.c_str();

  if(access(filename,0)==-1)  //Check folder existed or not
  {
    system(command.c_str());
  }
  else{
    printf("Folder already exists!\n");
  }

}

void RemoveFolder()
{
  time_t now = time(0);
  tm*ltm = localtime(&now);
  int MonNow = 1 + ltm->tm_mon;
  int YearNow = 1900 + ltm->tm_year;
  int DeleteMon;
  int DeleteYear;
  string DeleteFolder;

  if(MonNow - 3 >= 1) //Get Delete Year & Mon
  {
    DeleteYear = YearNow;
    DeleteMon = MonNow - 3;
  }
  else
  {
    DeleteYear = YearNow -1;
    DeleteMon = MonNow + 9;
  }

  std::stringstream DS;
  DS << "rm -r " << folderPath << DeleteYear << "-" << DeleteMon << "*";
  DeleteFolder = DS.str();
  system(DeleteFolder.c_str());

}

void systime(string LOG_data)
{
  time_t now = time(0);
  tm*ltm = localtime(&now); //Load system time

  ofstream newFile;  //Create new file
  newFile.open(GPMFolderPath.c_str() ,ios::app);  //Open new file

  struct timeval time_now{};
  gettimeofday(&time_now,nullptr);
  time_t msecs_time = (time_now.tv_usec/1000); //Get minisec
  std::stringstream ms;
  ms << msecs_time;
  msec = ms.str();

  newFile << "\n" << "\nBarcodeReader_State: " << 1900 + ltm->tm_year << "/" << 1 + ltm->tm_mon << "/" << ltm->tm_mday << " " 
  << ltm->tm_hour << ":" << ltm->tm_min << ":" << ltm->tm_sec << "." << msec << "==>" << LOG_data; //Write into file

  newFile.close();

}

};