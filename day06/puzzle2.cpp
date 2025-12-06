#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <filesystem>
#include <algorithm>
#include <numeric>

using num_t = long long;

#define CTI(x) ((int)(x - '0'))

num_t solution(std::vector<std::string> &input)
{
    num_t res = 0;
    num_t base = 0;
    char last_sign = ' ';

    for( size_t c=0; c<input[0].size(); c++)
    {
        if( input.back()[c] != ' ' )
        {
            res += base;
            last_sign = input.back()[c];

            if( last_sign == '*' )
            {
                base = 1;
            }
            else
            {
                base = 0;
            }
        }
        
        num_t num = 0;
        num_t mult = 1;
        bool empty = true;
        for( int r=input.size()-2; r>=0; r--)
        {
            if( input[r][c] != ' ' )
            {
                empty = false;
                num += mult * CTI(input[r][c]);
                mult *= 10;
            }
        }

        if( !empty )
        {
            if( last_sign == '*' )
            {
                base *= num;
            }
            else
            {
                base += num;
            }
        }
    }

    res += base;

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
