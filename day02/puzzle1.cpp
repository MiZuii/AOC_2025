#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <filesystem>
#include <algorithm>
#include <numeric>
#include <cmath>

using num_t=long;

num_t num_cnt(num_t num)
{
    num_t c = 0;
    while(num)
    {
        num /= 10;
        c++;
    }
    return c;
}

bool check_num(num_t num)
{
    num_t ncnt = num_cnt(num);
    if( ncnt % 2 != 0 ) return false;

    if( (num % num_t(pow(10, ncnt/2))) == (num / num_t(pow(10, ncnt/2))) )
    {
        return true;
    }
    return false;
}

num_t solution(std::vector<std::string> &input)
{
    std::stringstream sinput(input[0]);
    std::string ipair;
    std::vector<std::pair<num_t, num_t>> pinput;

    while(std::getline(sinput, ipair, ','))
    {
        auto split = ipair.find('-');
        std::string num1(ipair.begin(), ipair.begin() + split);
        std::string num2(ipair.begin() + split + 1, ipair.end());
        pinput.push_back(std::pair<num_t, num_t>(std::stol(num1), std::stol(num2)));
    }

    num_t res = 0;
    for( const std::pair<num_t, num_t> &range : pinput )
    {
        for( num_t i=range.first; i<=range.second; i++ )
        {
            if( check_num(i) )
            {
                res += i;
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
