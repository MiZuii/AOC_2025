#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <filesystem>
#include <algorithm>
#include <numeric>

void vec_add(std::vector<unsigned int> &base, const std::vector<bool> &app)
{
    for( size_t i=0; i<base.size(); i++ )
    {
        if( app[i] ) base[i]++;
    }
}

void vec_sub(std::vector<unsigned int> &base, const std::vector<bool> &app)
{
    for( size_t i=0; i<base.size(); i++ )
    {
        if( app[i] ) base[i]--;
    }
}

void search(
    std::vector<unsigned int> &state,
    const std::vector<std::vector<bool>> &machine,
    const std::vector<unsigned int> &target,
    int current, int &min)
{
    bool check = true;

    for( size_t i=0; i<state.size(); i++ )
    {
        if( state[i] != target[i] )
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

    for( const auto &button : machine )
    {
        vec_add(state, button);
        search(state, machine, target, current+1, min);
        vec_sub(state, button);
    }
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
    std::vector<std::vector<unsigned int>> machines_targets;

    for( auto &str_machine : split_input )
    {
        machines.push_back({});
        size_t machine_len = str_machine[0].size();
        
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
        
        machines_targets.push_back({});
            
        std::stringstream machinestream(*(str_machine.end()-1));
        std::string token;
        
        while( std::getline(machinestream, token, ',') )
        {
            machines_targets.back().push_back(std::stoi(token));
        }
    }

    int res = 0;

    for( size_t i=0; i<machines.size(); i++ )
    {
        auto &machine = machines[i];
        auto &machine_target = machines_targets[i];

        int local_res = 10000;
        size_t machine_len = machine[0].size();
        std::vector<unsigned int> state(machine_len, 0);

        search(state, machine, machine_target, 0, local_res);
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
