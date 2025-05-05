#include <stdlib.h>
#include "graph.h"
#include "map.h"

#define WIDTH 20
#define HEIGHT 10

Node* nodes[HEIGHT][WIDTH];

Node* get_node(int x, int y) {
    if (x < 0 || x >= WIDTH || y < 0 || y >= HEIGHT) return NULL;
    return nodes[y][x];
}

void build_graph() {
    for (int y = 0; y < HEIGHT; y++) {
        for (int x = 0; x < WIDTH; x++) {
            if (get_tile(x, y) != '#') {
                Node* n = malloc(sizeof(Node));
                n->x = x;
                n->y = y;
                n->visited = 0;
                n->distance = -1;
                for (int i = 0; i < 4; i++) n->neighbors[i] = NULL;
                nodes[y][x] = n;
            } else {
                nodes[y][x] = NULL;
            }
        }
    }

    for (int y = 0; y < HEIGHT; y++) {
        for (int x = 0; x < WIDTH; x++) {
            Node* n = get_node(x, y);
            if (!n) continue;
            if (get_node(x, y - 1)) n->neighbors[0] = get_node(x, y - 1);
            if (get_node(x, y + 1)) n->neighbors[1] = get_node(x, y + 1);
            if (get_node(x - 1, y)) n->neighbors[2] = get_node(x - 1, y);
            if (get_node(x + 1, y)) n->neighbors[3] = get_node(x + 1, y);
        }
    }
}

int shortest_path(int sx, int sy, int dx, int dy) {
    Node* start = get_node(sx, sy);
    Node* end = get_node(dx, dy);
    if (!start || !end) return -1;

    for (int y = 0; y < HEIGHT; y++)
        for (int x = 0; x < WIDTH; x++)
            if (nodes[y][x]) {
                nodes[y][x]->visited = 0;
                nodes[y][x]->distance = -1;
            }

    Node* queue[WIDTH * HEIGHT];
    int front = 0, rear = 0;
    queue[rear++] = start;
    start->visited = 1;
    start->distance = 0;

    while (front < rear) {
        Node* current = queue[front++];
        if (current == end) return current->distance;

        for (int i = 0; i < 4; i++) {
            Node* n = current->neighbors[i];
            if (n && !n->visited) {
                n->visited = 1;
                n->distance = current->distance + 1;
                queue[rear++] = n;
            }
        }
    }

    return -1;
}