/*
Code written by Elnur Mammadov.
More information you can find in README file

Last Modified 09/25/2018 01:49

*/
#include <iostream>
#include <cstring>
#include <map>
#include <fstream>
#include <string>
#include <algorithm>
#include <cstdlib>
#include <time.h>

int getFileContentAndSize(std::string fileName,std::map<std::string, int> &SumOfDurations,std::map<std::string, int> &CountOfEachRequests,std::map<std::string, int> &HoursOfHistogram) 
{
int count = 0;
std::ifstream in(fileName.c_str());
if (!in.is_open()) {
  std::cout << "Failed to open file..";
  return -1;
} else {
std::string str;
std::string a;
unsigned last_delim_pos;
unsigned first_delim_pos = str.find("] ");
unsigned end_pos_of_first_delim = first_delim_pos + 2;
char str2[1][64];
while (std::getline(in, str)) {
  count++;
  last_delim_pos;
  first_delim_pos = str.find("] ");
  end_pos_of_first_delim = first_delim_pos + 2;
  a = str.substr(first_delim_pos + 2);
  sscanf(a.c_str(), "%[^ ?]", str2[0]);
  std::size_t found1 = str.find("]");
  std::size_t found2 = str.find_last_of(" ");
  std::size_t found3 = str.find_first_of(" ");
  CountOfEachRequests[str2[0]] += 1;
  HoursOfHistogram[str.substr(found3 + 1, 2)] += 1;
  SumOfDurations[str2[0]] += std::stoi(str.substr(found2 + 1));
  }
}
in.close();
return count;
}
//Sorting our requests by top durations
void Parser(int x,std::map<std::string, int> &SumOfDurations,std::map<std::string, int> &CountOfEachRequests, std::map<int,std::string> &SortedRequestsByAverageDuration)
{
int div, div2;
std::cout << ""
          << "\n";
std::cout << "Top requests:"
          << "\n";
for (auto it = SumOfDurations.begin(), it2 = CountOfEachRequests.begin();
  it != SumOfDurations.end() && it2 != CountOfEachRequests.end(); ++it, ++it2) {
  div = it2->second;
  div2 = it->second;
  it->second = (it->second) / div;
  SortedRequestsByAverageDuration[it->second] = it->first;
}
std::map<int, std::string>::iterator iter;
iter = SortedRequestsByAverageDuration.end();
int lastValues = x;
while (lastValues != 0) {
  iter--;
  lastValues--;
  std::cout << iter->first << ", " << iter->second << "\n";
}
}
//Draw Histogram
void Histogram(int result,std::map<std::string, int> &HoursOfHistogram)
{
double div3;
for (auto it3 = HoursOfHistogram.begin(); it3 != HoursOfHistogram.end(); ++it3) {
  div3 = (it3->second) * 100 / result;
  std::cout << it3->first << " | ";
  //max of '*' is 20
  for (int i = 0; i < div3 / 5; i++) {
    std::cout << "*";
  }
  std::cout << "\n";
}
}
int main(int argc, char *argv[]) 
{
clock_t t1, t2;
t1 = clock();
// check if arguments count is correct
if (argc > 3 || argc < 2) {
  std::cout << "Error"
            << "\n";
  std::cout << "Please use 'program name' -h for more information"
            << "\n";
  std::cout << argc << "\n";
  return -4;
}
// help argument (example: func.exe -h)
if (argc == 2 && strcmp(argv[1], "-h") == 0) {
  std::cout << ""
            << "\n";
  std::cout << "To run the program you need to use 3 arguments:"
            << "\n";
  std::cout << ""
            << "\n";
  std::cout << "First argument is program name"
            << "\n";
  std::cout << "Second argument is log file name, please be sure that file "
               "in the same directory or put full path name"
            << "\n";
  std::cout << "The last third argument is out top n value (top n hightest "
               "results by duration)"
            << "\n";
  std::cout << ""
            << "\n";
  std::cout << "Below you can find example of usage program:"
            << "\n";
  std::cout << "a.exe log.txt 50"
            << "\n";
  std::cout << "Where a.exe is program name, log.txt file name and 50 is our "
               "top value"
            << "\n";
  std::cout << ""
            << "\n";
  return 0;
}
errno = 0;
char *endptr;
long int x;
// get our "top n" value from command line
if (argc == 3) {
  x = strtol(argv[2], &endptr, 10);
  if (endptr == argv[2]) {
    std::cout << "Invalid number: " << argv[2] << '\n';
    return -1;
  } else if (*endptr) {
    std::cout << "Trailing characters after number: " << argv[2] << '\n';
    return -2;
  } else if (errno == ERANGE) {
    std::cout << "Number out of range: " << argv[2] << '\n';
    return -3;
  }
}
std::map<std::string, int> SumOfDurations;
std::map<std::string, int> CountOfEachRequests;
std::map<int, std::string> SortedRequestsByAverageDuration;
std::map<std::string, int> HoursOfHistogram;
int count;
// result is count of total lines if file
// also below getFileContentAndSize function reads lines from file
int result = getFileContentAndSize(argv[1], SumOfDurations, CountOfEachRequests, HoursOfHistogram);
if (result == 0) {
  return -1;
}
std::cout<<"Histogram:"<<"\n";
Histogram(result,HoursOfHistogram);
std::cout<<"\n";
Parser(x,SumOfDurations, CountOfEachRequests,SortedRequestsByAverageDuration);
// Run time our program
t2 = clock();
float diff((float)t2 - (float)t1);

float seconds = diff / CLOCKS_PER_SEC;
std::cout << ""
          << "\n";
std::cout << "Run time of the program: " << seconds << " seconds"
          << "\n";

return 0;
}
