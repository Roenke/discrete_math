#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
int v1, v2, e;
std::vector<int> used;
std::vector<int> matching;
bool dfs(std::vector<std::vector<int>> const& graph, int v)
{
    if (used[v] == 1)
    {
        return false;
    }

    used[v] = 1;
    int to;
    for (auto i = 0; i < graph[v].size(); ++i)
    {
        to = graph[v][i];
        if (matching[to] == -1 || dfs(graph, matching[to]))
        {
            matching[to] = v;
            return true;
        }
    }

    return false;
}

int main()
{
    std::cin >> v1 >> v2 >> e;
    int v = v1 + v2;
    std::vector <std::vector < int > > graph(v1);
    matching.resize(v2);
    matching.assign(v2, -1);
    used.resize(v);
    used.assign(v, 0);
    std::vector<std::pair<int, int>> edges;
    if (e == 0)
    {
        std::cout << 0 << std::endl;
        return 1;
    }
    int begin, end;
    for (int i = 0; i < e; ++i)
    {
        std::cin >> begin >> end;
        edges.push_back(std::pair<int, int>(begin, end));
        graph[begin].push_back(end - v1);
    }

    for (int i = 0; i < v1; ++i)
    {
        used.assign(v, 0);
        dfs(graph, i);
    }

    std::cout << v1 << " " << v2 << " " << e << std::endl;

    for (int i = 0; i < edges.size(); ++i)
    {
        std::cout << edges[i].first << " " << edges[i].second << std::endl;
    }

    int in_cover;
    for (auto i = 0; i < matching.size(); ++i)
    {
        if(matching[i] != -1)
        {
            auto left = matching[i];
            auto added = false;
            for(auto const& r_vertex: graph[left])
            {
                if(matching[r_vertex] == -1)
                {
                    in_cover = left;
                    added = true;
                    break;
                }
            }

            if(!added)
            {
                in_cover = i + v1;
            }
            std::cout << in_cover << " ";
        }
    }

    std::cout << std::endl;
}