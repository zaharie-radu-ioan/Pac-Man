#ifndef GRAPH_H
#define GRAPH_H

typedef struct Node
{
    int x, y;
    struct Node *neighbors[4];
    int visited;
    int distance;
} Node;

void build_graph();
int shortest_path(int sx, int sy, int dx, int dy);

#endif