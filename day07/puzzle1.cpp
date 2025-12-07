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

    for( size_t i=1; i<input.size(); i++ )
    {
        for( size_t j=0; j<input[0].size(); j++ )
        {
            if( input[i][j] == '.' )
            {
                if( input[i-1][j] == '|' || input[i-1][j] == 'S' )
                {
                    input[i][j] = '|';
                }
            }
            else if( input[i][j] == '^' )
            {
                if( input[i-1][j] == '|' )
                {
                    res++;
                    input[i][j-1] = '|';
                    input[i][j+1] = '|';
                }
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
