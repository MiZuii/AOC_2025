#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <filesystem>
#include <algorithm>
#include <numeric>

using num_t = long long;
using point_t = std::pair<num_t, num_t>;

num_t solution(std::vector<std::string> &input)
{
    std::vector<point_t> points;
    for( auto &line : input )
    {
        std::stringstream sline(line);
        std::string token;
        std::getline(sline, token, ',');
        num_t x = std::stol(token);
        std::getline(sline, token, ',');
        num_t y = std::stol(token);
        points.push_back({x, y});
    }

    num_t maxarea = 0;
    for( size_t i=0; i<points.size()-1; i++ )
    {
        for( size_t j=i+1; j<points.size(); j++ )
        {
            num_t dx = std::abs(points[i].first - points[j].first) + 1;
            num_t dy = std::abs(points[i].second - points[j].second) + 1;

            maxarea = std::max(maxarea, dx*dy);
        }
    }

    return maxarea;
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
