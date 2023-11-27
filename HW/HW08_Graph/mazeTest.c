#include "graph.h"
#include <stdio.h>


int match(const void *key1, const void *key2);
void (*destroy)(void *data);


int main() {
    Graph maze1, maze2;
    char vertices[] = {'A', 'B', 'C', 'D', 'E', 'F', 'G'};
    int i;

    /* Initialize both mazes. */
    graph_init(&maze1, match, *destroy);
    graph_init(&maze2, match, *destroy);

    /* Insert vertices for both mazes. */
    for (i = 0; i < sizeof(vertices) / sizeof(char); i++) {
        graph_ins_vertex(&maze1, &vertices[i]);
        graph_ins_vertex(&maze2, &vertices[i]);
    }

    /* Insert edges for Maze #1. */
    graph_ins_edge(&maze1, &vertices[0], &vertices[2]); // A-C
    graph_ins_edge(&maze1, &vertices[0], &vertices[3]); // A-D
    graph_ins_edge(&maze1, &vertices[3], &vertices[1]); // D-B
    graph_ins_edge(&maze1, &vertices[2], &vertices[5]); // C-F
    graph_ins_edge(&maze1, &vertices[5], &vertices[6]); // F-G
    graph_ins_edge(&maze1, &vertices[3], &vertices[6]); // D-G
    graph_ins_edge(&maze1, &vertices[3], &vertices[4]); // D-E
    graph_ins_edge(&maze1, &vertices[4], &vertices[6]); // E-G


    /* Insert edges for Maze #2. */
    graph_ins_edge(&maze2, &vertices[0], &vertices[2]); // A-C
    graph_ins_edge(&maze2, &vertices[0], &vertices[3]); // A-D
    graph_ins_edge(&maze2, &vertices[3], &vertices[1]); // D-B
    graph_ins_edge(&maze2, &vertices[2], &vertices[5]); // C-F
    graph_ins_edge(&maze2, &vertices[4], &vertices[6]); // E-G
    

    /* Test the mazes. */
    int result1 = isExitReachable(&maze1, 'A', 'G');
    int result2 = isExitReachable(&maze2, 'A', 'G');

    printf("Result for Maze #1 (should be reachable, expect 1): %d\n", result1);
    printf("Result for Maze #2 (should NOT be reachable, expect 0): %d\n", result2);

    /* Destroy both mazes. */
    graph_destroy(&maze1);
    graph_destroy(&maze2);

    return 0;
}
