#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <filesystem>
#include <algorithm>
#include <numeric>
#include <array>
#include <utility>

constexpr std::array<std::pair<int, int>, 8> shifts = {{
    {1, 0}, {-1, 0}, {0, 1}, {0, -1},
    {1, 1}, {-1, 1}, {-1, -1}, {1, -1}
}};

int solution(std::vector<std::string> &input)
{
    int res = 0;
    int iter_res = 1;
    while( iter_res )
    {
        iter_res = 0;
        for( size_t y=0; y<input.size(); y++ )
        {
            for( size_t x=0; x<input[0].size(); x++ )
            {
                if( input[y][x] == '@' )
                {
                    int rolls_around = 0;
                    
                    for( std::pair<int, int> shift : shifts )
                    {
                        if( y + shift.second >= 0 && y + shift.second < input.size() &&
                            x + shift.first  >= 0 && x + shift.first  < input[0].size() &&
                            input[y + shift.second][x + shift.first] == '@')
                        {
                            rolls_around++;
                        }
                    }

                    if( rolls_around < 4 )
                    {
                        res++;
                        iter_res++;
                        input[y][x] = '.';
                    }
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
