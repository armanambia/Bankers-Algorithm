#include "bank.h"


Bank::Bank(std::string input): 
    fileName(input){
        parseFile();
    }

std::string Bank::getSafeSequence(){
    std::vector<int> newly_Available(available);
    std::vector<bool> finish;
    for (int x = 0; x <  MAX_CUSTOMERS; x++){
        finish.push_back(false);
    }
    int i = 0;
    std::string sequence = "";
    while (std::find(finish.begin(), finish.end(), false) != finish.end()){
        
        std::vector<int> curNeed = need[i];
        std::vector<int> curAlloc = allocation[i];
        
        if (finish[i] == false){
            bool check = true;
            for(int j = 0; j < MAX_RESOURCES; j++){
                if (curNeed[j] > newly_Available[j]){
                    check = false;
                    break;
                }
            }
            if (check){
                std::transform (newly_Available.begin(), newly_Available.end(),
                                curAlloc.begin(), newly_Available.begin(), std::plus<int>());
                finish[i] = true;
                std::stringstream ss;
                ss << i;
                sequence += "Process "+  ss.str() + " has been allocated\n";
                sequence += "\tCurrent Work: ";
                for(int ind = 0; ind < MAX_RESOURCES; ind++){
                    std::stringstream as;
                    as << newly_Available[ind];
                    sequence+= as.str() + " ";
                }
                sequence += "\n";
            }
        }
        
        
        i++;
        i %= MAX_CUSTOMERS;
    }
    return sequence;
}

void Bank::parseFile(){
    std::ifstream inFile;
    inFile.open(fileName.c_str());
    if (inFile.is_open()){
        
        std::string line;
        std::getline(inFile,line);
        std::vector<std::string> result;
        std::stringstream s_stream(line); 
        while(s_stream.good()) {                        // this loop parses the available vectors
            std::string substr;
            std::getline(s_stream, substr, ','); //get first string delimited by comma
            substr.erase(remove_if(substr.begin(), substr.end(), isspace), substr.end());
            available.push_back(atoi( substr.c_str() ));
        }
        
        MAX_RESOURCES =  available.size();
        int row = 0;
        
        while( std::getline(inFile,line) ) // this loop will parse the max and allocation matricies
        {
            
            int col = 0;
            std::stringstream s_stream(line);
            std::vector<int> curAlloc;
            std::string substr;
            while(col < MAX_RESOURCES) {        // current row of the allocation matrix
                
                std::getline(s_stream, substr, ','); 
                substr.erase(remove_if(substr.begin(), substr.end(), isspace), substr.end());
                curAlloc.push_back(atoi( substr.c_str() ));
                col++;
                
            }
            allocation.push_back(curAlloc);
            std::vector<int> curMax;
            col = 0;
            while(col < MAX_RESOURCES){         // current row of the max matrix;
                std::getline(s_stream, substr, ',');
                substr.erase(remove_if(substr.begin(), substr.end(), isspace), substr.end());
                curMax.push_back(atoi( substr.c_str() ));
                col++;
            }
            max.push_back(curMax);
            row++;
            MAX_CUSTOMERS = row;
        }
    }

    parseNeed(); // create need matrix
    
    
}

void Bank::parseNeed(){
    std::vector<int> curNeed;
    for (int i = 0; i < MAX_CUSTOMERS; i++){   // this loop will create the need matrix;
        for(int j = 0; j < MAX_RESOURCES; j++){
            curNeed.push_back(max[i][j] - allocation[i][j]);
        }
        need.push_back(curNeed);
        curNeed.clear();
    }
}

void Bank::showAvailable(){
    std::cout << "--Available--\n";
    for(int i = 0; i < MAX_RESOURCES; i++) {    
        std::cout << available.at(i) << " ";
    }
    std::cout << "\n";
}

void Bank::showAlloc(){
    std::cout << "--ALLOCATION--\n";
    for (int i = 0; i < MAX_CUSTOMERS; i++){
        for(int j = 0; j < MAX_RESOURCES; j++){
            std::cout << allocation[i][j] << " ";
        }
        std::cout << "\n";
    }
}

void Bank::showMax(){
    std::cout << "--MAX--\n";
    for (int i = 0; i < MAX_CUSTOMERS; i++){
        for(int j = 0; j < MAX_RESOURCES; j++){
            std::cout << max[i][j] << " ";
        }
        std::cout << "\n";
    }
}

void Bank::showNeed(){
    std::cout << "--NEED--\n";
    for (int i = 0; i < MAX_CUSTOMERS; i++){
        for(int j = 0; j < MAX_RESOURCES; j++){
            std::cout << need[i][j] << " ";
        }
        std::cout << "\n";
    }
}