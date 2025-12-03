#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <filesystem>
#include <algorithm>
#include <numeric>

int solution(std::vector<std::string> &input)
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

    int res = 0;
    for( auto &battery_line : parsed_in )
    {
        int prev_max = battery_line[0];
        int line_max = 0;
        for( size_t i=1; i<battery_line.size(); i++)
        {
            if( prev_max*10 + battery_line[i] > line_max )
            {
                line_max = prev_max*10 + battery_line[i];
            }
            prev_max = std::max(prev_max, battery_line[i]);
        }

        res += line_max;
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
