#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <filesystem>
#include <algorithm>
#include <numeric>

#include "absl/base/log_severity.h"
#include "absl/log/globals.h"
#include "ortools/base/init_google.h"
#include "ortools/linear_solver/linear_solver.h"

using namespace operations_research;

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
        auto &target = machines_targets[i];

        const size_t num_constraints = target.size();
        const size_t num_variables = machine.size();

        std::unique_ptr<MPSolver> solver(MPSolver::CreateSolver("SCIP"));
        const double infinity = solver->infinity();
        std::vector<MPVariable*> variables;
        
        for( size_t k=0; k<num_variables; k++ )
        {
            variables.push_back(solver->MakeIntVar(0.0, infinity, std::to_string(k)));
        }

        std::vector<MPConstraint*> constraints;
        for( size_t j=0; j<num_constraints; j++ )
        {
            constraints.push_back(solver->MakeRowConstraint(target[j], target[j], "c" + std::to_string(j)));

            for( size_t k=0; k<num_variables; k++ )
            {
                auto var = variables[k];
                if(machine[k][j])
                {
                    constraints.back()->SetCoefficient(var, 1);
                }
            }
        }

        //objective
        MPObjective* const objective = solver->MutableObjective();
        for( size_t k=0; k<num_variables; k++ )
        {
            auto var = variables[k];
            objective->SetCoefficient(var, 1);
        }

        const MPSolver::ResultStatus result_status = solver->Solve();
        
        res += objective->Value();
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
