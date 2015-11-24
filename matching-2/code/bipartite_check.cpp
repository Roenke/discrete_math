#include <iostream>
#include <vector>
#include <set>

/* 
Проверить, является ли граф двудольным.

Формат входных данных:
В первой строке указаны два числа разделенных пробелом: 
v (число вершин) и e (число ребер). В следующих e 
строках указаны пары вершин, соединенных ребром. 
Выполняются ограничения: 0≤v≤1000,0≤e≤1000.

Формат выходных данных:
Одно слово: YES, если граф двудолен, или NO, в противном случае.
*/

using namespace std;

void dfs(int vertex, vector<vector<int>> const& graph, vector<uint8_t>& colors, uint8_t color)
{
    int to;
    colors[vertex] = color;
    for (int i = 0; i < graph[vertex].size(); ++i)
    {
        to = graph[vertex][i];
        if(colors[to] == 2)
        {
            dfs(to, graph, colors, !color);
        }
    }
}

int main()
{
    int v, e;
    cin >> v >> e;
    vector<vector<int>> graph(v);
    set<pair<int, int>> edges{};
    vector<uint8_t> colors(v);
    colors.assign(v, 2);

    int from, to;
    for (auto i = 0; i < e; ++i)
    {
        cin >> from >> to;
        --from;
        --to;
        edges.insert(pair<int, int>(from, to));
        graph[from].push_back(to);
        graph[to].push_back(from);
    }

    for (int i = 0; i < v; ++i)
    {
        if(colors[i] == 2)
        {
            dfs(i, graph, colors, 1);
        }
    }
    

    auto is_bapartite = true;
    for(auto const& edge : edges)
    {
        if(colors[edge.first] == colors[edge.second])
        {
            is_bapartite = false;
            break;
        }
    }

    cout << (is_bapartite ? "YES" : "NO") << endl;

    return 0;
}