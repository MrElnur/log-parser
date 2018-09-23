/*
Parsing functions here
There we are sorting lines by the last element of our lines (durations in ms)
*/

//function to find duration
bool sort_by_duration (std::string& a,std::string& b)
{
    std::size_t found1 = a.find_last_of(" ");
    std::size_t found2 = b.find_last_of(" ");
    int aValue = std::stoi(a.substr(found1+1));
    int bValue = std::stoi(b.substr(found2+1));
    return (aValue > bValue);
}

//sort function
void parser(std::string str[], int x,int result)
{
 
 std::sort (str, str+result, sort_by_duration);

 for (auto it = str; it != str + x; ++it)
     std::cout << *it<<std::endl;
}