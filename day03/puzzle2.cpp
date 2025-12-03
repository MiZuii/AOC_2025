#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <filesystem>
#include <algorithm>
#include <numeric>
#include <cmath>

long solution(std::vector<std::string> &input)
{
    std::vector<std::vector<int>> parsed_in;
    for( auto line : input )
    {
        parsed_in.push_back({});
        for( auto c : line )
        {
            parsed_in.back().push_back(std::stoi(std::string(1, c)));
        }
    }

    long res = 0;
    for( auto &battery_line : parsed_in )
    {
        size_t search_i = 0;
        long local_res = 0;

        for( size_t i=0; i<12; i++ )
        {
            long max = 0;
            for( size_t j=search_i; j<battery_line.size()-11+i; j++)
            {
                if( battery_line[j] > max )
                {
                    max = battery_line[j];
                    search_i = j+1;
                }
            }
            local_res += pow(10, 11-i)*max;
        }

        res += local_res;
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
