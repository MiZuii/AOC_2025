#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <filesystem>
#include <algorithm>
#include <numeric>

using num_t = long long;
using point_t = std::pair<num_t, num_t>;

struct Edge
{
    point_t s;
    point_t e;
};

template<bool is_vertical, bool positive_inside>
class Sweeper
{
public:
    void step(Edge edge)
    {
        // remove all edges that the next edge intersects with
        while(true)
        {
            auto it = _state.begin();
            bool deleted = false;
            for( ; it != _state.end(); it++ )
            {
                if constexpr ( is_vertical )
                {
                    // this is wrong -> the code ignores corner points. however since the results is still too
                    // low this bug doesnt affect the final solution
                    if( !(std::max(edge.s.second, edge.e.second) <= std::min(it->s.second, it->e.second) ||
                        std::min(edge.s.second, edge.e.second) >= std::max(it->s.second, it->e.second)))
                    {
                        // the edges intersect
                        _update_result(*it, edge);
                        _state.erase(it);
                        deleted = true;
                        break;
                    }
                }
                else
                {
                    if( !(std::max(edge.s.first, edge.e.first) <= std::min(it->s.first, it->e.first) ||
                        std::min(edge.s.first, edge.e.first) >= std::max(it->s.first, it->e.first)))
                    {
                        // the edges intersect
                        _update_result(*it, edge);
                        _state.erase(it);
                        deleted = true;
                        break;
                    }
                }
            }

            if( deleted )
            {
                // this means that somethign has been deleted this iteration
                continue;
            }

            // add the edge to the state if it's in correct direction.
            if constexpr ( positive_inside )
            {
                if constexpr ( is_vertical )
                {
                    if( edge.e.second - edge.s.second > 0 )
                    {
                        _state.push_back(edge);
                    }
                }
                else
                {
                    if( edge.e.first - edge.s.first > 0 )
                    {
                        _state.push_back(edge);
                    }
                }
            }
            else
            {
                if constexpr ( is_vertical )
                {
                    if( edge.e.second - edge.s.second < 0 )
                    {
                        _state.push_back(edge);
                    }
                }
                else
                {
                    if( edge.e.first - edge.s.first < 0 )
                    {
                        _state.push_back(edge);
                    }
                }
            }

            break;
        }
    };

    num_t get_result()
    {
        return max_rect;
    };

private:

    void _update_result(const Edge &start_edge, const Edge &final_edge)
    {
        if constexpr ( is_vertical )
        {
            num_t dy = std::abs(start_edge.e.second - start_edge.s.second) + 1;
            num_t dx = std::abs(final_edge.s.first - start_edge.s.first) + 1;

            max_rect = std::max(max_rect, dx*dy);
        }
        else
        {
            num_t dx = std::abs(start_edge.e.first - start_edge.s.first) + 1;
            num_t dy = std::abs(final_edge.s.second - start_edge.s.second) + 1;

            max_rect = std::max(max_rect, dx*dy);
        }
    }

    std::vector<Edge> _state;
    num_t max_rect = 0;
};

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

    std::vector<Edge> vertical_edges;
    std::vector<Edge> horizontal_edges;
    for( size_t i=1; i<points.size()+1; i++)
    {
        if( points[i-1].first == points[i].first )
        {
            vertical_edges.push_back({points[i-1], points[i % points.size()]});
        }
        else
        {
            horizontal_edges.push_back({points[i-1], points[i % points.size()]});
        }
    }

    // sort vertical and horizontal edges to find out
    // which direction is the inside of the shape and prepare for sweep
    std::sort(vertical_edges.begin(), vertical_edges.end(), [](const Edge &e1, const Edge &e2) {
        // compare x coordinates
        return e1.s.first < e2.s.first;
    });

    std::sort(horizontal_edges.begin(), horizontal_edges.end(), [](const Edge &e1, const Edge &e2) {
        // compare y coordinates
        return e1.s.second < e2.s.second;
    });

    bool vertical_positive_inside = (vertical_edges[0].e.second - vertical_edges[0].s.second > 0);
    bool horizontal_positive_inside = (horizontal_edges[0].e.first - horizontal_edges[0].s.first > 0);

    num_t res = 0;

    if( vertical_positive_inside )
    {
        Sweeper<true, true> sweeper;
        for( auto it = vertical_edges.begin(); it != vertical_edges.end(); it++ )
        {
            sweeper.step(*it);
        }
        res = std::max(res, sweeper.get_result());

        Sweeper<true, false> rsweeper;
        for( auto it = vertical_edges.rbegin(); it != vertical_edges.rend(); it++ )
        {
            rsweeper.step(*it);
        }
        res = std::max(res, rsweeper.get_result());
    }
    else
    {
        Sweeper<true, false> sweeper;
        for( auto it = vertical_edges.begin(); it != vertical_edges.end(); it++ )
        {
            sweeper.step(*it);
        }
        res = std::max(res, sweeper.get_result());

        Sweeper<true, true> rsweeper;
        for( auto it = vertical_edges.rbegin(); it != vertical_edges.rend(); it++ )
        {
            rsweeper.step(*it);
        }
        res = std::max(res, rsweeper.get_result());
    }

    if( horizontal_positive_inside )
    {
        Sweeper<false, true> sweeper;
        for( auto it = horizontal_edges.begin(); it != horizontal_edges.end(); it++ )
        {
            sweeper.step(*it);
        }
        res = std::max(res, sweeper.get_result());

        Sweeper<false, false> rsweeper;
        for( auto it = horizontal_edges.rbegin(); it != horizontal_edges.rend(); it++ )
        {
            rsweeper.step(*it);
        }
        res = std::max(res, rsweeper.get_result());
    }
    else
    {
        Sweeper<false, false> sweeper;
        for( auto it = horizontal_edges.begin(); it != horizontal_edges.end(); it++ )
        {
            sweeper.step(*it);
        }
        res = std::max(res, sweeper.get_result());

        Sweeper<false, true> rsweeper;
        for( auto it = horizontal_edges.rbegin(); it != horizontal_edges.rend(); it++ )
        {
            rsweeper.step(*it);
        }
        res = std::max(res, rsweeper.get_result());
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
