#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#include <queue>

/*
Найдите минимальное вершинное покрытие в двудольном графе.

На вход подается описание двудольного графа, в котором доли уже выделены явно. 
Первая строка содержит три натуральных числа: 
v1<100 — число вершин первой доли, 
v2<100 — число вершин второй доли, 
e≤v1<=v2 — число рёбер. Подразумевается, что первая доля состоит из вершин с 
номерами от 0 до v1−1, вторая — из вершин с номерами от v1 до v1+v2−1. 
Следующие e строк описывают рёбра: каждая из этих строк содержит 
два числа: 0≤ui<v1 и v1≤wi<v1+v2, что означает, что между вершинами ui и wi есть ребро.

Скопируйте описание графа из входа на выход и выведите единственную 
дополнительную строку — список номеров вершин, составляющих минимальное вершинное покрытие. 
Если таких покрытий несколько, выведите любое.
*/
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

void bfs(int vertex, std::vector<uint8_t>& visited, std::vector<std::vector<int>>const& graph)
{
    int v;
    std::queue<int> queue;
    queue.push(vertex);
    while(!queue.empty())
    {
        v = queue.front();
        queue.pop();
        visited[v] = 1;
        for(auto const& v_ : graph[v])
        {
            if(visited[v_] == 0)
            {
                queue.push(v_);
            }
        }
    }
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

    std::vector<std::vector<int>> new_graph(v);
    std::vector<uint8_t> left_free(v1);
    left_free.assign(v1, 1);
    int left, right;
    for (auto i = 0; i < e; ++i)
    {
        left = edges[i].first;
        right = edges[i].second;
        if(matching[right - v1] == edges[i].first)
        {
            new_graph[right].push_back(left);
            left_free[left] = 0;
        }
        else
        {
            new_graph[left].push_back(right);
        }
    }

    std::vector<uint8_t> visited(v);
    visited.assign(v, 0);

    for (int i = 0; i < v1; ++i)
    {
        if (left_free[i] == 0 && !visited[i]) continue;

        bfs(i, visited, new_graph);
    }

    int in_cover;
    for (int i = 0; i < v; ++i)
    {
        if(i < v1 && visited[i] == 0)
        {
            std::cout << i << " ";
        }
        if (i >= v1 && visited[i] == 1)
        {
            std::cout << i << " ";
        }
    }

    std::cout << std::endl;
}