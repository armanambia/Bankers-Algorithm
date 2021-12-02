#include <vector>
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <algorithm>

class Bank{
    public:
        Bank(std::string input);
        void showAvailable();
        void showAlloc();
        void showMax();
        void showNeed();
        std::string getSafeSequence();
    private:
        void parseFile();
        void parseNeed();
        int cur_customer_;
        int MAX_RESOURCES;
        int MAX_CUSTOMERS;

        std::string fileName;

        std::vector<int> available;
        std::vector< std::vector<int> > max;
        std::vector< std::vector<int> > allocation;
        std::vector< std::vector<int> > need;


};