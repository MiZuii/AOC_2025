#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <filesystem>
#include <algorithm>
#include <numeric>
#include <unordered_map>

using num_t = long long;

num_t dfs(int v, const std::vector<std::vector<int>> &graph, std::vector<bool> &visited, int out, std::vector<int> boundary)
{
    if( v == out )
    {
        return 1;
    }

    if( std::find(boundary.begin(), boundary.end(), v) != boundary.end() )
    {
        return 0;
    }
    
    if( visited[v] )
    {
        return 0;
    }

    visited[v] = true;
    num_t res = 0;

    for( auto u : graph[v] )
    {
        res += dfs(u, graph, visited, out, boundary);
    }

    visited[v] = false;
    return res;
}

num_t dfs_ws(int v, const std::vector<std::vector<int>> &graph, std::vector<bool> &visited, int out, std::vector<int> shortcut, std::vector<num_t> shortcut_values)
{
    for( size_t i=0; i<shortcut.size(); i++ )
    {
        if( v == shortcut[i] )
        {
            return shortcut_values[i];
        }
    }
    
    if( visited[v] )
    {
        return 0;
    }

    visited[v] = true;
    num_t res = 0;

    for( auto u : graph[v] )
    {
        res += dfs_ws(u, graph, visited, out, shortcut, shortcut_values);
    }

    visited[v] = false;
    return res;
}

unsigned long long solution(std::vector<std::string> &input)
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

    std::vector<int> shortcut_vs{name_to_idx["rpn"], name_to_idx["lpz"], name_to_idx["apc"]};
    std::vector<num_t> shortcut_values;
    for( auto sv : shortcut_vs )
    {
        shortcut_values.push_back(dfs(sv, graph, visited, name_to_idx["dac"], {name_to_idx["qdo"], name_to_idx["sdo"], name_to_idx["ire"], name_to_idx["you"]}));
    }

    unsigned long long svrTOfft = dfs(name_to_idx["svr"], graph, visited, name_to_idx["fft"], {name_to_idx["kqn"], name_to_idx["vht"], name_to_idx["vjh"], name_to_idx["ehw"], name_to_idx["edr"]});
    unsigned long long fftTOdac = dfs_ws(name_to_idx["fft"], graph, visited, name_to_idx["dac"], shortcut_vs, shortcut_values);
    unsigned long long dacTOout = dfs(name_to_idx["dac"], graph, visited, name_to_idx["out"], {});
    
    return svrTOfft * fftTOdac * dacTOout;
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
