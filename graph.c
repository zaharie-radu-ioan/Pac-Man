#include <stdlib.h>
#include "graph.h"
#include "map.h"

Node *nodes[HEIGHT][WIDTH];

Node *get_node(int x, int y)
{
    if (x < 0 || x >= WIDTH || y < 0 || y >= HEIGHT)
        return NULL;
    return nodes[y][x];
}

void build_graph()
{
    for (int y = 0; y < HEIGHT; y++)
    {
        for (int x = 0; x < WIDTH; x++)
        {
            if (get_tile(x, y) != '#')
            {
                Node *n = malloc(sizeof(Node));
                n->x = x;
                n->y = y;
                n->visited = 0;
                n->distance = -1;
                for (int i = 0; i < 4; i++)
                    n->neighbors[i] = NULL;
                nodes[y][x] = n;
            }
            else
            {
                nodes[y][x] = NULL;
            }
        }
    }

    for (int y = 0; y < HEIGHT; y++)
    {
        for (int x = 0; x < WIDTH; x++)
        {
            Node *n = get_node(x, y);
            if (!n)
                continue;
            if (get_node(x, y - 1))
                n->neighbors[0] = get_node(x, y - 1);
            if (get_node(x, y + 1))
                n->neighbors[1] = get_node(x, y + 1);
            if (get_node(x - 1, y))
                n->neighbors[2] = get_node(x - 1, y);
            if (get_node(x + 1, y))
                n->neighbors[3] = get_node(x + 1, y);
        }
    }
}
Path shortest_path(int sx, int sy, int dx, int dy) {
    Path path = {0};

    // Reset noduri
    for (int y = 0; y < HEIGHT; y++)
        for (int x = 0; x < WIDTH; x++) {
            Node* n = get_node(x, y);
            if (n) {
                n->visited = 0;
                n->distance = -1;
                n->parent = NULL;
            }
        }

    Node* start = get_node(sx, sy);
    Node* dest = get_node(dx, dy);
    if (!start || !dest) return path;

    Node* queue[WIDTH * HEIGHT];
    int front = 0, rear = 0;

    queue[rear++] = start;
    start->visited = 1;
    start->distance = 0;

    while (front < rear) {
        Node* curr = queue[front++];
        if (curr == dest) break;

        for (int i = 0; i < 4; i++) {
            Node* n = curr->neighbors[i];
            if (n && !n->visited) {
                n->visited = 1;
                n->distance = curr->distance + 1;
                n->parent = curr;
                queue[rear++] = n;
            }
        }
    }

    Node* step = dest;
    while (step && step != start) {
        path.steps[path.length++] = step;
        step = step->parent;
    }

    // Inversare drum
    for (int i = 0; i < path.length / 2; i++) {
        Node* tmp = path.steps[i];
        path.steps[i] = path.steps[path.length - 1 - i];
        path.steps[path.length - 1 - i] = tmp;
    }

    return path;
}
