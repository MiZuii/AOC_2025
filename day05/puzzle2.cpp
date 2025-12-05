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

    // reduce ranges

    num_t res = 0;
    size_t i = 0;
    while( i < db_ranges.size() )
    {
        range_t range = db_ranges[i];

        // find if range overlaps with any other range
        auto overlaping = db_ranges.end();
        for( size_t j=i+1; j<db_ranges.size(); j++ )
        {
            if(!(range.second < (db_ranges.begin() + j)->first || range.first > (db_ranges.begin() + j)->second))
            {
                overlaping = db_ranges.begin() + j;
                break;
            }
        }

        if(overlaping != db_ranges.end())
        {
            // merge range into overlaped
            overlaping->first = std::min(overlaping->first, range.first);
            overlaping->second = std::max(overlaping->second, range.second);

            // remove range from the list
            db_ranges.erase(db_ranges.begin()+i);
        }
        else
        {
            i++;
        }
    }

    for( range_t& range : db_ranges )
    {
        res += range.second - range.first + 1;
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
