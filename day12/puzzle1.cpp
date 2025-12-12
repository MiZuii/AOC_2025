#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <filesystem>
#include <algorithm>
#include <numeric>

int solution(std::vector<std::string> &input)
{
    int res = 0;

    for( auto &line : input )
    {
        int dx = std::stoi(std::string(line.begin(), line.begin() + line.find('x')));
        int dy = std::stoi(std::string(line.begin() + line.find('x') + 1, line.begin() + line.find(':')));
        
        std::stringstream sstream(std::string(line.begin() + line.find(':') + 2, line.end()));
        std::string token;
        int sum = 0;
        while( std::getline(sstream, token, ' '))
        {
            int quant = std::stoi(token);
            sum += 9*quant;
        }

        if( sum <= dx*dy)
        {
            res++;
        }
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
