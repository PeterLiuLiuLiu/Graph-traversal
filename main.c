// Compile this assignment with: gcc -Wall main.c -o main
//
// Include parts of the C Standard Library
// These have been written by some other really
// smart engineers.
#include <stdio.h>  // For IO operations
#include <stdlib.h> // for malloc/free

// Our library that we have written.
// Also, by a really smart engineer!
#include "my_graph.h"


// Note that we are locating this file
// within the same directory, so we use quotations
// and provide the path to this file which is within
// our current directory.

int main(int argc, const char * argv[]) {


    graph_t * graph = create_graph();

    graph_add_node(graph, 1);
    graph_add_node(graph, 1);
    graph_add_node(graph, 2);
    graph_add_node(graph, 2);
    graph_add_node(graph, 3);
    graph_add_node(graph, 4);
    graph_add_node(graph, 5);
    graph_add_node(graph, 6);
    printf("total nodes: 6==%d\n", graph_num_nodes(graph));

    graph_add_edge(graph, 1, 2);
    graph_add_edge(graph, 2, 3);
    graph_add_edge(graph, 3, 4);
    graph_add_edge(graph, 4, 2); 
    graph_add_edge(graph, 1, 5); 
    graph_add_edge(graph, 5, 6); 

    printf("graph_has_cycle(g): %d\n", graph_has_cycle(graph));
    printf("graph_is_reachable(g, 1, 6): %d\n", graph_is_reachable(graph, 1, 6));
    printf("graph_print_path(graph, 1, 6): %d", graph_print_path(graph, 1, 6));

    /*
    graph_add_edge(graph, 1, 2);
    graph_add_edge(graph, 2, 3);
    graph_add_edge(graph, 3, 1);
    graph_add_edge(graph, 2, 5);
    graph_remove_edge(graph, 1, 5);
    graph_remove_edge(graph, 3, 5);
    printf("contains_edge(graph, 3, 5): %d\n", contains_edge(graph, 3, 5));
    printf("contains_edge(graph, 5, 3): %d\n", contains_edge(graph, 5, 3));
    
    graph_remove_node(graph, 5);
    graph_remove_node(graph, 1);

    printf("node 2's inNeighbor: ");
    print_dll(getInNeighbors(graph, 2));
    printf("node 2's outNeighbor: ");
    print_dll(getOutNeighbors(graph, 2));
    printf("\n");

    printf("node 3's inNeighbor: ");
    print_dll(getInNeighbors(graph, 3));
    printf("node 3's outNeighbor: ");
    print_dll(getOutNeighbors(graph, 3));
    printf("\n");

    printf("contains_edge(graph, 1, 2) = 0: %d\n", contains_edge(graph, 1, 2));
    printf("contains_edge(graph, 2, 1) = 0: %d\n", contains_edge(graph, 2, 1));
    printf("contains_edge(graph, 2, 3) = 1: %d\n", contains_edge(graph, 2, 3));
    printf("contains_edge(graph, 3, 2) = 0: %d\n", contains_edge(graph, 3, 2));
    printf("contains_edge(graph, 1, 3) = 0: %d\n", contains_edge(graph, 1, 3));
    printf("contains_edge(graph, 3, 1) = 0: %d\n", contains_edge(graph, 3, 1));
    printf("contains_edge(graph, 1, 4) = 0: %d\n", contains_edge(graph, 1, 4));
    printf("contains_edge(graph, 4, 1) = 0: %d\n", contains_edge(graph, 4, 1));
    printf("contains_edge(graph, 3, 5) = 0: %d\n", contains_edge(graph, 3, 5));
    printf("contains_edge(graph, 5, 3) = 0: %d\n", contains_edge(graph, 5, 3));

    graph_remove_node(graph, 2);
    graph_remove_node(graph, 3);
    graph_remove_node(graph, 4);

    printf("%d\n", graph_num_nodes(graph));
    printf("%d\n", graph_num_edges(graph));

	printf("graph_is_reachable(graph, 1, 5) = 1: %d", graph_is_reachable(graph, 1, 5));
	printf("graph_has_cycle(graph) = 1: %d", graph_has_cycle(graph));
    */

	free_graph(graph);

    return 0;
}
