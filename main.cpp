/*
Code written by Elnur Mammadov. 
More information you can find in README file

First deployment 09/16/2018 00:16
Last deployment 09/16/2018 04:45

*/
#include <iostream>
#include <cstring>
#include <map>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <time.h>
#include "parser.cpp"

using namespace std;

int getFileContentAndSize(std::string fileName, std::vector<std::string> & vecOfStrs, int count, std::map<std::string, int> & myMap)
{
    count=0;
	std::ifstream in(fileName.c_str());
	if (!in.is_open()) {
		 cout << "Failed to open file..";
		return -1;      
    }
 else {
	std::string str;
	
	while (std::getline(in, str))
	{
		if(str.size() > 0)
			count++;
			vecOfStrs.push_back(str);
			std::size_t found1 = str.find("");
            myMap[ str.substr(found1+0,13) ] += 1;
	}
 }
	in.close();
	return count;
}
 
int main(int argc, char *argv[])
{
    clock_t t1,t2;
    t1=clock();
    //check if arguments count is correct
	if(argc>3 || argc<2)
	{
		cout<<"Error"<<endl;
		cout<<"Please use 'program name' -h for more information"<<endl;
		cout<<argc<<endl;
		return -4;
	}
	//help argument (example: func.exe -h)
	if(argc == 2 && strcmp(argv[1], "-h")==0)
        {
			cout<<""<<endl;
			cout<<"To run the program you need to use 3 arguments:"<<endl;
			cout<<""<<endl;
			cout<<"First argument is program name"<<endl;
			cout<<"Second argument is log file name, please be sure that file in the same directory or put full path name"<<endl;
			cout<<"The last third argument is out top n value (top n hightest results by duration)"<<endl;
			cout<<""<<endl;
			cout<<"Below you can find example of usage program:"<<endl;
			cout<<"a.exe log.txt 50"<<endl;
			cout<<"Where a.exe is program name, log.txt file name and 50 is our top value"<<endl;
			cout<<""<<endl;
	return 0;
	}
	errno = 0;
    char *endptr;
	long int x;
	//get our "top n" value from command line
	if(argc==3)
	{
    x = strtol(argv[2], &endptr, 10);
    if (endptr == argv[2]) {
     std::cout << "Invalid number: " << argv[2] << '\n';
     return -1;
    } 
    else if (*endptr) {
     std::cout << "Trailing characters after number: " << argv[2] << '\n';
     return -2;
    }
    else if (errno == ERANGE) {
     std::cout << "Number out of range: " << argv[2] << '\n';
     return -3;
    }
	}
	//vector used for sortinf, map used for count lines per hour
	std::vector<std::string> vecOfStr;
	std::map<std::string, int> myMap;
    int count;
	//result is count of total lines if file
	//also below getFileContentAndSize function reads lines from file
	int result = getFileContentAndSize(argv[1], vecOfStr,count, myMap);
	if(result==-1)
	{
		return -1;
	}
    		string* str =new string[result];
 	       	for (int i = 0; i < result; i++)
              {    
                  str[i]=vecOfStr[i];
              } 
  //you can find more information from parser.cpp
  parser(str,x,result);

  //Count of requests per hour
  cout<<""<<endl;
  cout<<"Requests per hour:"<<endl;
  for(auto it = myMap.cbegin(); it != myMap.cend(); ++it)
    {
        std::cout <<"At this date and hour "<< it->first<< " | " << it->second<<" requests" << "\n";
    }
	
  delete[] str;
    //Run time our program
	t2=clock();
    float diff ((float)t2-(float)t1);
    
	float seconds = diff / CLOCKS_PER_SEC;
	cout<<""<<endl;
	cout<<"Run time of the program: "<<seconds<<" seconds"<<endl;
    
	return 0;	
}