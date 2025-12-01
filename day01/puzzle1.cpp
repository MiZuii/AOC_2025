#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <filesystem>
#include <algorithm>
#include <numeric>

int solution(std::vector<std::string> &input)
{
    int dial = 50;
    int res = 0;
    for( std::string& line : input )
    {
        if( dial == 0 ) res++;

        auto strview = std::string(line.begin()+1, line.end());
        int num = std::stoi(strview);
        if( line[0] == 'L' )
        {
            dial -= num;
        }
        else
        {
            dial += num;
        }

        dial %= 100;
    }
    return res;
}

int main(int argc, char* argv[]) {
    std::string inputFilename = "input.txt";

    std::ifstream inputFile(inputFilename);
    if (!inputFile) {
        std::cerr << "Error opening input file" << std::endl;
        return 1;
    }

    std::vector<std::string> input;
    std::string line;
    while (std::getline(inputFile, line)) {
        input.push_back(line);
    }
    inputFile.close();

    std::cout << solution(input) << std::endl;
    return 0;
}
