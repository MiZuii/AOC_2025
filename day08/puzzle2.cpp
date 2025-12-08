#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <filesystem>
#include <algorithm>
#include <numeric>
#include <unordered_map>
#include <unordered_set>

/*
n*log(n) idea:
Create a 3dim KDTree from all points. Than create an array with
number of queries of each point, and a space for closest neighbors.
First step is to query each point for it's closes neighbor [n*log(n)].
Each point is put into a priority queue by it's distance [n*log(n)].
Than, initialize structures that will represent the connected junctions.
Now, in the task we get an arbitrary number of steps to perform m = 1000,
which is equal to n. Now we perform this steps. One step is:
 1. Get the smallest edge from priority queue [O(1)]
 2. Merge junction sets connected by this edge [with disjoint-set forest doable
    in amortized O(1)]
 3. Check which point from the list was the edge generated from. [O(1)]
 4. This, points closes neighbor is outdated soo we query for it's
    second closes neighbor. [log(n)]
 5. We add a new edge to the priority queue. [log(n)]
Since this steps are additive the final complexity is [n*log(n) + m*log(n)]
which is O(n*log(n)) with assumption that m=n

However for this size of the problem (n=1000) the bruteforce O(n^2) is probably
faster due to an extremaly better constant.
*/

using num_t = long long;
using dist_t = long long;
using point_t = std::tuple<num_t, num_t, num_t>;
using junction_t = std::tuple<size_t, size_t, dist_t>;

[[nodiscard]] dist_t dist(const point_t &p1, const point_t &p2)
{
    dist_t dx = static_cast<dist_t>(std::get<0>(p1) - std::get<0>(p2));
    dist_t dy = static_cast<dist_t>(std::get<1>(p1) - std::get<1>(p2));
    dist_t dz = static_cast<dist_t>(std::get<2>(p1) - std::get<2>(p2));
    
    return dx*dx + dy*dy + dz*dz;
}

struct DSFNode
{
    DSFNode(size_t i) : parent(nullptr), id(i), rank(1) {}
    DSFNode() : parent(nullptr), id(static_cast<size_t>(0) -1), rank(0) {}

    DSFNode *parent;
    size_t id;
    size_t rank;
};

class DSF
{
public:
    DSF() = default;

    void make_set(size_t i)
    {
        _nodes[i] = DSFNode(i);
        _roots.insert(i);
    }

    DSFNode* find(size_t i)
    {
        // add smoothing?

        auto nit = _nodes.find(i);
        if( nit != _nodes.end() )
        {
            DSFNode *node = &(nit->second);
            while( node->parent != nullptr )
            {
                node = node->parent;
            }
            return node;
        }

        return nullptr;
    }

    void merge(size_t i, size_t j)
    {
        DSFNode* r1 = find(i);
        DSFNode* r2 = find(j);

        if( r1 == nullptr || r2 == nullptr )
        {
            return;
        }

        if( r1 == r2 )
        {
            return;
        }

        if( r1->rank > r2->rank )
        {
            // merging r2 to r1
            r1->rank += r2->rank;
            r2->parent = r1;
            _roots.erase(_roots.find(r2->id));
        }
        else
        {
            r2->rank += r1->rank;
            r1->parent = r2;
            _roots.erase(_roots.find(r1->id));
        }
    }

    size_t number_of_roots()
    {
        return _roots.size();
    }

private:
    std::unordered_set<size_t> _roots;
    std::unordered_map<size_t, DSFNode> _nodes;

};

num_t solution(std::vector<std::string> &input)
{
    std::vector<point_t> points;
    for( auto &line : input )
    {
        std::stringstream sline(line);
        std::string token;

        std::getline(sline, token, ',');
        num_t x = std::stoll(token);

        std::getline(sline, token, ',');
        num_t y = std::stoll(token);

        std::getline(sline, token, ',');
        num_t z = std::stoll(token);

        points.push_back({x, y, z});
    }

    std::vector<junction_t> junctions;
    for( size_t i=0; i<points.size()-1; i++ )
    {
        for( size_t j=i+1; j<points.size(); j++ )
        {
            // unique i, j pairs.
            junctions.push_back({i, j, dist(points[i], points[j])});
        }
    }

    std::sort(junctions.begin(), junctions.end(), [](const junction_t &j1, const junction_t &j2) {
        return std::get<2>(j1) < std::get<2>(j2);
    });

    //join junctions
    DSF dsf;

    // add all junctions first
    for( size_t i=0; i<1000; i++ )
    {
        dsf.make_set(i);
    }

    size_t fi=0, fj=0;
    size_t c=0;
    while( dsf.number_of_roots() != 1 )
    {
        const size_t i = std::get<0>(junctions[c]);
        const size_t j = std::get<1>(junctions[c++]);

        dsf.merge(i, j);
        fi=i;
        fj=j;
    }

    return std::get<0>(points[fi]) * std::get<0>(points[fj]);
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
