#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <filesystem>
#include <algorithm>
#include <numeric>

using num_t = long long;

num_t solution(std::vector<std::string> &input)
{
    std::vector<std::vector<num_t>> pinput;
    std::vector<char> signs;
    for( size_t i=0; i<input.size()-1; i++ )
    {
        std::stringstream line_input(input[i]);
        std::string token;
        pinput.push_back({});

        while( std::getline(line_input, token, ' '))
        {
            if( !token.empty() )
            {
                pinput.back().push_back(static_cast<num_t>(std::stoi(token)));
            }
        }
    }

    std::stringstream line_input(input.back());
    std::string token;
    while( std::getline(line_input, token, ' '))
    {
        if( !token.empty() )
        {
            signs.push_back(token[0]);
        }
    }

    for( size_t c=0; c< pinput[0].size(); c++ )
    {
        for( size_t r=1; r<pinput.size(); r++ )
        {
            if( signs[c] == '*' )
            {
                pinput[r][c] *= pinput[r-1][c];
            }
            else
            {
                pinput[r][c] += pinput[r-1][c];
            }
        }
    }

    return std::accumulate(pinput.back().begin(), pinput.back().end(), 0LL);
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
