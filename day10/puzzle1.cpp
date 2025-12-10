#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <filesystem>
#include <algorithm>
#include <numeric>

void vec_xor(std::vector<bool> &base, const std::vector<bool> &app)
{
    for( size_t i=0; i<base.size(); i++ )
    {
        base[i] = base[i] ^ app[i];
    }
}

void search(std::vector<bool> &state, const std::vector<std::vector<bool>> &machine, size_t depth, int current, int &min)
{
    bool check = true;

    for( size_t i=0; i<state.size(); i++ )
    {
        if( state[i] != machine[0][i] )
        {
            check = false;
            break;
        }
    }

    if( check )
    {
        min = std::min(min, current);
        return;
    }

    // cutof if better solution is impossible
    if( current >= min )
    {
        return;
    }

    // cutof if too big depth
    if( depth + 1 >= machine.size() )
    {
        return;
    }

    // split search
    // button clicked
    vec_xor(state, machine[depth+1]);
    search(state, machine, depth+1, current+1, min);
    vec_xor(state, machine[depth+1]);

    // button not clicked
    search(state, machine, depth+1, current, min);
}

int solution(std::vector<std::string> &input)
{
    std::vector<std::vector<std::string>> split_input;
    for( std::string &line : input )
    {
        std::stringstream sline(line);
        std::string token;

        split_input.push_back({});

        while( std::getline(sline, token, ' ') )
        {
            split_input.back().push_back(std::string(token.begin()+1, token.end()-1));
        }
    }

    std::vector<std::vector<std::vector<bool>>> machines;
    for( auto &str_machine : split_input )
    {
        machines.push_back({});
        size_t machine_len = str_machine[0].size();
        
        machines.back().push_back(std::vector<bool>(machine_len, false));
        for( size_t i=0; i<machine_len; i++ )
        {
            if( str_machine.front()[i] == '#' )
            {
                machines.back().back()[i] = true;
            }
        }

        for( auto it = str_machine.begin()+1; it != str_machine.end()-1; it++ )
        {
            // convert equation line to bool vector
            machines.back().push_back(std::vector<bool>(machine_len, false));

            std::stringstream machinestream(*it);
            std::string token;

            while( std::getline(machinestream, token, ',') )
            {
                machines.back().back()[std::stoi(token)] = true;
            }
        }
    }

    int res = 0;
    for( auto &machine : machines )
    {
        int local_res = 10000;
        size_t machine_len = machine[0].size();
        std::vector<bool> state(machine_len, false);

        search(state, machine, 0, 0, local_res);
        res += local_res;
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
