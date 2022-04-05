
#include <stdio.h> 
#include <stdlib.h> 
#include <string.h>

#include "my_graph.h"

// Create a graph, populate with node and edges and check if the node, 
// edge connections are properly made
int unitTest1(int status) {
    int passed = 1;

    graph_t * g = create_graph();

    graph_add_node(g, 1);
    graph_add_node(g, 2);

	if(graph_num_nodes(g) != 2) passed = 0;

	graph_add_edge(g, 1, 2);
	graph_add_edge(g, 2, 1);

	if(contains_edge(g, 1, 2) != 1 || contains_edge(g, 2, 1) != 1) passed = 0;

	free_graph(g);

	return passed;
}

// Check for dupplicate add nodes and edges see if it will repeated add nodes and edges
int unitTest2(int status) {
	int passed = 1;

    graph_t * g = create_graph();

    graph_add_node(g, 1);
    if(graph_add_node(g, 1) != 0) passed = 0;
    graph_add_node(g, 2);

	if(graph_num_nodes(g) != 2) passed = 0;

	graph_add_edge(g, 1, 2);
	graph_add_edge(g, 2, 1);
    if(graph_add_edge(g, 2, 1) != 0) passed = 0;
	free_graph(g);

	return passed;
}


// Check if remove edge works
int unitTest3(int status) {
    int passed = 1;

    graph_t * g = create_graph();
    graph_add_node(g, 1);
    graph_add_node(g, 2);
    graph_add_node(g, 3);
    graph_add_node(g, 4);

	// try removing an edge that does not exist
	if(graph_remove_edge(g, 1, 2) != 0) passed = 0;

	graph_add_edge(g, 1, 2);
	graph_add_edge(g, 1, 3);
	graph_add_edge(g, 2, 3);
	graph_add_edge(g, 3, 4);
    
	if(contains_edge(g, 2, 1) == 1) passed = 0;
	if(contains_edge(g, 1, 2) != 1) passed = 0;
	if(contains_edge(g, 1, 3) != 1) passed = 0;
	if(contains_edge(g, 2, 3) != 1) passed = 0;
	if(contains_edge(g, 3, 4) != 1) passed = 0;
	if(graph_num_edges(g) != 4) passed = 0;

	graph_remove_edge(g, 1, 2);
	graph_remove_edge(g, 1, 3);
	graph_remove_edge(g, 2, 3);
	graph_remove_edge(g, 3, 4);

	if(contains_edge(g, 1, 2) == 1) passed = 0;
	if(contains_edge(g, 1, 3) == 1) passed = 0;
	if(contains_edge(g, 2, 3) == 1) passed = 0;
	if(contains_edge(g, 3, 4) == 1) passed = 0;
	if(graph_num_edges(g) != 0) passed = 0;

	free_graph(g);

	return passed;
}

// Check if graph_remove_node method works correctly
int unitTest4(int status) {
    int passed = 1;

    graph_t * g = create_graph();
    graph_add_node(g, 1);
    graph_add_node(g, 2);
    graph_add_node(g, 3);
    graph_add_node(g, 4);

	graph_add_edge(g, 1, 2);
	graph_add_edge(g, 1, 3);
	graph_add_edge(g, 2, 3);
	graph_add_edge(g, 3, 4);

	graph_remove_node(g, 1);
	// edges related to the deleted nodes should have been deleted
	if(contains_edge(g, 1, 2) == 1) passed = 0;
	if(contains_edge(g, 1, 3) == 1) passed = 0;
	if(graph_num_edges(g) != 2) passed = 0;

	graph_remove_node(g, 3);
	// edges related to the deleted nodes should have been deleted
	if(contains_edge(g, 2, 3) == 1) passed = 0;
	if(contains_edge(g, 3, 4) == 1) passed = 0;
	if(graph_num_edges(g) != 0) passed = 0;

	if(graph_num_nodes(g) != 2) passed = 0;

	free_graph(g);

	return passed;
}

// Check if the in and out Neighbors actuall contains the desired values
int unitTest5(int status) {
    int passed = 1;

    graph_t * g = create_graph();
    graph_add_node(g, 1);
    graph_add_node(g, 2);
    graph_add_node(g, 3);
    graph_add_node(g, 4);

	graph_add_edge(g, 1, 2);
	graph_add_edge(g, 1, 3);
	graph_add_edge(g, 2, 3);
	graph_add_edge(g, 3, 4);

	// 1 should have outNeighbors 2, 3 and no inNeighbors
	if(getNumInNeighbors(g, 1) != 0) passed = 0;

	dll_t *out_1 = getOutNeighbors(g, 1);
	if(getNumOutNeighbors(g, 1) != 2) passed = 0;
	// dll_contains_value returns the actual position, 
	// therefore should be non-negative
	if(dll_contains_value(out_1, 2) < 0) passed = 0;
	if(dll_contains_value(out_1, 3) < 0) passed = 0;
	if(dll_contains_value(out_1, 4) >= 0) passed = 0;

	// 2 should have outNeighbors 3 and inNeighbors 1
	dll_t *in_2 = getInNeighbors(g, 2);
	if(getNumInNeighbors(g, 2) != 1) passed = 0;
	if(dll_contains_value(in_2, 1) < 0) passed = 0;

	dll_t *out_2 = getOutNeighbors(g, 2);
	if(getNumOutNeighbors(g, 2) != 1) passed = 0;
	if(dll_contains_value(out_2, 3) < 0) passed = 0;
	if(dll_contains_value(out_2, 4) >= 0) passed = 0;
	
	// 3 should have outNeighbors 4 and inNeighbors 1, 2
	dll_t *in_3 = getInNeighbors(g, 3);
	if(getNumInNeighbors(g, 3) != 2) passed = 0;
	if(dll_contains_value(in_3, 1) < 0) passed = 0;
	if(dll_contains_value(in_3, 2) < 0) passed = 0;

	dll_t *out_3 = getOutNeighbors(g, 3);
	if(getNumOutNeighbors(g, 3) != 1) passed = 0;
	if(dll_contains_value(out_3, 4) < 0) passed = 0;
	
	// 4 should have no outNeighbors and inNeighbors 3
	dll_t *in_4 = getInNeighbors(g, 4);
	if(getNumInNeighbors(g, 4) != 1) passed = 0;
	if(dll_contains_value(in_4, 3) < 0) passed = 0;

	dll_t *out_4 = getOutNeighbors(g, 4);
	if(getNumOutNeighbors(g, 4) != 0) passed = 0;
	if(dll_contains_value(out_4, 1) >= 0) passed = 0;
	if(dll_contains_value(out_4, 2) >= 0) passed = 0;
	if(dll_contains_value(out_4, 3) >= 0) passed = 0;
	
	free_graph(g);

	return passed;
}

// Check after removing nodes, the inNeighbors and outNeighbors should have no value
int unitTest6(int status){
	int passed = 1;

	graph_t * g = create_graph();
	graph_add_node(g, 1);
	graph_add_node(g, 2);
	graph_add_node(g, 3);
	graph_add_node(g, 4);

	graph_add_edge(g, 1, 2);
	graph_add_edge(g, 1, 3);
	graph_add_edge(g, 2, 3);
	graph_add_edge(g, 3, 4);

	graph_remove_node(g, 1);
	graph_remove_node(g, 3);

	// removing the nodes 1, 3 should delete all connections 
	// since 2, 4 are not connected, all nodes have no connections
	// therefore size should return -1 for 1, 3
	// size of in out Neighbors should be 0 for 2, 4 since node are not null 
	// but does not connect to anything
	dll_t *in_1 = getInNeighbors(g, 1);
	dll_t *out_1 = getOutNeighbors(g, 1);
	
	if(dll_size(in_1) != -1) passed = 0;
	if(dll_size(out_1) != -1) passed = 0;
	if(getNumInNeighbors(g, 1) != -1) passed = 0;
	if(getNumOutNeighbors(g, 1) != -1) passed = 0;

	dll_t *in_2 = getInNeighbors(g, 2);
	dll_t *out_2 = getOutNeighbors(g, 2);
	if(dll_size(in_2) != 0) passed = 0;
	if(dll_size(out_2) != 0) passed = 0;
	if(getNumInNeighbors(g, 2) != 0) passed = 0;
	if(getNumOutNeighbors(g, 2) != 0) passed = 0;
	
	dll_t *in_3 = getInNeighbors(g, 3);
	dll_t *out_3 = getOutNeighbors(g, 3);
	if(dll_size(in_3) != -1) passed = 0;
	if(dll_size(out_3) != -1) passed = 0;
	if(getNumInNeighbors(g, 3) != -1) passed = 0;
	if(getNumOutNeighbors(g, 3) != -1) passed = 0;
	
	dll_t *in_4 = getInNeighbors(g, 4);
	dll_t *out_4 = getOutNeighbors(g, 4);
	if(dll_size(in_4) != 0) passed = 0;
	if(dll_size(out_4) != 0) passed = 0;
	if(getNumInNeighbors(g, 4) != 0) passed = 0;
	if(getNumOutNeighbors(g, 4) != 0) passed = 0;

	free_graph(g);

	return passed;
}

// Check if the graph has cycles in a simple one-node self-looping setting
int unitTest7(){
	int passed = 1;

	graph_t * g = create_graph();
	graph_add_node(g, 1);

	graph_add_edge(g, 1, 1);

	if(graph_has_cycle(g) != 1) passed = 0;

	free_graph(g);

	return passed;
}

// Check if a two-node bi-laterally connected contains cycle
int unitTest8(){
	int passed = 1;

	graph_t * g = create_graph();
	graph_add_node(g, 1);
	graph_add_node(g, 2);

	graph_add_edge(g, 1, 2);
	graph_add_edge(g, 2, 1);

	if(graph_has_cycle(g) != 0) passed = 0;

	free_graph(g);

	return passed;
}

// Check if a two-node bi-laterally connected contains cycle but with more complicated cases
int unitTest9(){
	int passed = 1;

	graph_t * g = create_graph();
	graph_add_node(g, 1);
	graph_add_node(g, 2);
	graph_add_node(g, 3);
	graph_add_node(g, 4);

	graph_add_edge(g, 1, 2);
	graph_add_edge(g, 2, 4);
	graph_add_edge(g, 2, 1);
	graph_add_edge(g, 1, 3);
	graph_add_edge(g, 3, 4);

	if(graph_has_cycle(g) != 0) passed = 0;

	// 1->2->4->1 forms a cycle
	graph_add_edge(g, 4, 1);
	if(graph_has_cycle(g) != 1) passed = 0;

	free_graph(g);

	return passed;
}


// Check if a undirected graph contains cycle
int unitTest10(){
	int passed = 1;

	graph_t * g = create_graph();
	graph_add_node(g, 1);
	graph_add_node(g, 2);
	graph_add_node(g, 3);

	graph_add_edge(g, 1, 2);
	graph_add_edge(g, 2, 1);
	graph_add_edge(g, 2, 3);
	graph_add_edge(g, 3, 2);
	graph_add_edge(g, 1, 3);
	graph_add_edge(g, 3, 1);
	
	if(graph_has_cycle(g) != 1) passed = 0;

	free_graph(g);
	return passed;
}


// Check if a directed graph contains cycle 
int unitTest11(){
	int passed = 1;

	graph_t * g = create_graph();
	graph_add_node(g, 1);
	graph_add_node(g, 2);
	graph_add_node(g, 3);
	graph_add_node(g, 4);
	graph_add_node(g, 5);
	graph_add_node(g, 6);

	graph_add_edge(g, 1, 2);
	graph_add_edge(g, 2, 3);
	graph_add_edge(g, 3, 4);
	graph_add_edge(g, 4, 2);
	graph_add_edge(g, 3, 6);
	graph_add_edge(g, 1, 5);
	graph_add_edge(g, 5, 6);
	
	if(graph_has_cycle(g) != 1) passed = 0;
	if(graph_is_reachable(g, 1, 2) != 1) passed = 0;
	if(graph_is_reachable(g, 3, 1) != 0) passed = 0;
	if(graph_is_reachable(g, 1, 6) != 1) passed = 0;
	if(graph_is_reachable(g, 4, 6) != 1) passed = 0;
	if(graph_is_reachable(g, 2, 5) != 0) passed = 0;
	if(graph_is_reachable(g, 5, 2) != 0) passed = 0;

	free_graph(g);
	return passed;
}

// Check for graph_is_reachable method with similar setting like test 11
int unitTest12(){
	int passed = 1;

	graph_t * g = create_graph();
	graph_add_node(g, 1);
	graph_add_node(g, 2);
	graph_add_node(g, 3);
	graph_add_node(g, 4);
	graph_add_node(g, 5);
	graph_add_node(g, 6);
	
	if(graph_is_reachable(g, 1, 2) != 0) passed = 0;
	if(graph_is_reachable(g, 3, 5) != 0) passed = 0;

	graph_add_edge(g, 1, 2);
	graph_add_edge(g, 2, 3);
	graph_add_edge(g, 3, 4);
	graph_add_edge(g, 4, 2);
	graph_add_edge(g, 3, 6);
	graph_add_edge(g, 1, 5);
	graph_add_edge(g, 5, 6);

	if(graph_is_reachable(g, 1, 2) != 1) passed = 0;
	if(graph_is_reachable(g, 3, 1) != 0) passed = 0;
	if(graph_is_reachable(g, 1, 6) != 1) passed = 0;
	if(graph_is_reachable(g, 4, 6) != 1) passed = 0;
	if(graph_is_reachable(g, 2, 5) != 0) passed = 0;
	if(graph_is_reachable(g, 5, 2) != 0) passed = 0;

	free_graph(g);
	return passed;
}


// Check for graph_is_reachable method with similar setting like test 11
int unitTest13(){
	int passed = 1;

	graph_t * g = create_graph();
	graph_add_node(g, 1);
	graph_add_node(g, 2);
	graph_add_node(g, 3);
	graph_add_node(g, 4);
	graph_add_node(g, 5);
	graph_add_node(g, 6);

	graph_add_edge(g, 1, 2);
	graph_add_edge(g, 2, 3);
	graph_add_edge(g, 3, 4);
	graph_add_edge(g, 4, 2);
	graph_add_edge(g, 3, 6);
	graph_add_edge(g, 1, 5);
	graph_add_edge(g, 5, 6);

	printf("Path from 4->6:\nExcepted:\t4  2  3  6\n");
	printf("Actual:\t\t");
	graph_print_path(g, 4, 6);

	free_graph(g);
	return passed;
}
	
// TODO: Add more tests here at your discretion
int (*unitTests[])(int)={
    unitTest1,
    unitTest2,
    unitTest3,
    unitTest4,
    unitTest5,
    unitTest6,
    unitTest7,
    unitTest8,
    unitTest9,
    unitTest10,
    unitTest11,
    unitTest12,
    unitTest13,
    NULL
};


// ====================================================
// ================== Program Entry ===================
// ====================================================
int main() {
    unsigned int testsPassed = 0;
    // List of Unit Tests to test your data structure
    int counter =0;
    while(unitTests[counter]!=NULL){
	printf("========unitTest %d========\n", counter);
        if(1==unitTests[counter](1)){
		printf("passed test\n");
		testsPassed++;	
	}else{
		printf("failed test, missing functionality, or incorrect test\n");
	}
        counter++;
    }

    printf("%d of %d tests passed\n", testsPassed, counter);

    return 0;
}
