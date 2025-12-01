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

        // eliminates full rotations
        if( num > 100 )
        {
            res += num / 100;
            num %= 100;
        }

        int prevdial = dial;
        if( line[0] == 'L' )
        {
            dial -= num;
            dial = (dial + 100) % 100;

            // if full rotations are eleminated
            // if we went through 0 the dial number
            // will be higher than the previous dial number
            if( dial != 0 && prevdial != 0 && dial >= prevdial )
            {
                res += 1;
            }
        }
        else
        {
            dial += num;
            dial %= 100;

            // same as above but in different direction
            if( dial != 0 && prevdial != 0  && dial <= prevdial )
            {
                res += 1;
            }
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
