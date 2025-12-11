#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <filesystem>
#include <algorithm>
#include <numeric>
#include <unordered_map>

int dfs(int v, const std::vector<std::vector<int>> &graph, std::vector<bool> &visited)
{
    if( v == -1 )
    {
        return 1;
    }
    
    if( visited[v] )
    {
        return 0;
    }

    visited[v] = true;
    int res = 0;

    for( auto u : graph[v] )
    {
        res += dfs(u, graph, visited);
    }

    visited[v] = false;
    return res;
}

int solution(std::vector<std::string> &input)
{
    std::unordered_map<std::string, int> name_to_idx;
    name_to_idx["out"] = -1;
    int idx = 0;

    for( auto &line : input )
    {
        name_to_idx[std::string(line.begin(), line.begin()+3)] = idx++;
    }

    std::vector<std::vector<int>> graph(static_cast<size_t>(idx));

    for( auto &line : input )
    {
        size_t gidx = name_to_idx[std::string(line.begin(), line.begin()+3)];

        std::stringstream sline(std::string(line.begin()+5, line.end()));
        std::string token;
        while( std::getline(sline, token, ' '))
        {
            graph[gidx].push_back(name_to_idx[token]);
        }
    }

    std::vector<bool> visited(graph.size(), false);
    return dfs(name_to_idx["you"], graph, visited);
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
