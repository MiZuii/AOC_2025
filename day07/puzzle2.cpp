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
    for( auto &line : input )
    {
        pinput.push_back({});
        for( auto c : line )
        {
            if( c == 'S' )
            {
                pinput.back().push_back(1);
            }
            else if( c == '^' )
            {
                pinput.back().push_back(-1);
            }
            else
            {
                pinput.back().push_back(0);
            }
        }
    }


    for( size_t i=1; i<pinput.size(); i++ )
    {
        for( size_t j=0; j<pinput[0].size(); j++ )
        {
            if( pinput[i][j] == -1 && pinput[i-1][j] > 0 )
            {
                // spliter
                pinput[i][j-1] += pinput[i-1][j];
                pinput[i][j+1] += pinput[i-1][j];
            }
            else if( pinput[i-1][j] > 0 )
            {
                pinput[i][j] += pinput[i-1][j];
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
