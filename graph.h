#ifndef GRAPH_H
#define GRAPH_H

#define WIDTH 30
#define HEIGHT 15
typedef struct Node
{
    int x, y;
    struct Node *neighbors[4];
    int visited;
    int distance;
    struct Node* parent;
} Node;

typedef struct Path {
    int length;
    Node* steps[WIDTH * HEIGHT];
} Path;

Node* get_node(int x, int y);
void build_graph();
Path shortest_path(int sx, int sy, int dx, int dy);

#endif