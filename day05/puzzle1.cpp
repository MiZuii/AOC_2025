#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <filesystem>
#include <algorithm>
#include <numeric>

using num_t = long;
using range_t = std::pair<num_t, num_t>;

num_t solution(std::vector<std::string> &input)
{
    std::vector<range_t> db_ranges;
    std::vector<num_t> db_nums;

    auto it = input.begin();
    while( it != input.end() && !it->empty() )
    {
        std::stringstream line(*it);
        std::string t1, t2;
        std::getline(line, t1, '-');
        std::getline(line, t2, '-');

        db_ranges.push_back(range_t(static_cast<num_t>(std::stol(t1)), 
                                    static_cast<num_t>(std::stol(t2))));
        it++;
    }
    it++;
    while( it != input.end())
    {
        db_nums.push_back(static_cast<num_t>(std::stol(*it)));
        it++;
    }

    int res = 0;
    for( num_t& num : db_nums )
    {
        for( range_t& range : db_ranges )
        {
            if( num >= range.first && num <= range.second )
            {
                res++;
                break;
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
