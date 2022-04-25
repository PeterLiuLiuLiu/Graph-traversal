// =================== Support Code =================
// Graph.
//
// - Implement each of the functions to create a working graph.
// - Do not change any of the function declarations
//   - (i.e. graph_t* create_graph() should not have additional arguments)
// - You should not have any 'printf' statements in your graph functions.
//   - (You may consider using these printf statements to debug, but they 
//      should be removed from your final version)
// ==================================================
#ifndef MYGRAPH_H
#define MYGRAPH_H

#include "my_dll.h"
#include <stdlib.h>
#include <assert.h>
// Create a graph data structure
typedef struct graph{
    int numNodes;
    int numEdges;
    dll_t* nodes;     //an array of nodes storing all of our nodes.
} graph_t;

typedef struct graph_node{
    int data;
    dll_t* inNeighbors;
    dll_t* outNeighbors;
} graph_node_t;

// -----------------------------helper function---------------------------------

// Check a general dll to see if the val is present
// -1 means l is NULL
// -9999 means not found
int dll_contains_graph_node(dll_t* l, int value){
    int pos = 0;
    if(l == NULL) return -1;
    node_t *curr_node = l->head;
    while(curr_node != NULL){
        if((int)curr_node->data == value){
            return pos;
        }
        curr_node = curr_node->next;
        pos++;
    }
    return -9999;
}

// Returns the node pointer if the node exists.
// Returns NULL if the node doesn't exist or the graph is -1
int find_node_in_graph_dll( graph_t * g, int value){
    if ( g == NULL ) return -1;

    int pos = 0;
    node_t *curr_node = g->nodes->head;
    while(curr_node != NULL){
        // data of the head of g->node contains a graph node
        graph_node_t* curr_g_node = (graph_node_t*)curr_node->data;
        if((int)curr_g_node->data == value){
            return pos;
        }
        pos++;
        curr_node = curr_node->next;
    }
    return -1;
}

// Check the neighor dll to see if the src or dest is present
// -1 means l is NULL
// -9999 means not found
int neighbor_dll_contains_graph_node(dll_t* l, int value){
    int pos = 0;

    if(l == NULL) return -1;
    node_t *curr_node = l->head;
    while(curr_node != NULL){
        graph_node_t *temp_g_node = curr_node->data;
        if(temp_g_node->data == value){
            return pos;
        }
        curr_node = curr_node->next;
        pos++;
    }
    return -9999;
}
// -----------------------------------------------------------------------------


// Creates a graph
// Returns a pointer to a newly created graph.
// The graph should be initialized with data on the heap.
// The graph fields should also be initialized to default values.
// Returns NULL if we cannot allocate memory.
graph_t* create_graph(){
    // Modify the body of this function as needed.
    graph_t* myGraph= (graph_t*)malloc(sizeof(graph_t));
    
    if ( myGraph == NULL ) return NULL;

    myGraph->nodes = create_dll();
    myGraph->numEdges = 0;
    myGraph->numNodes = 0;
    return myGraph;
}

// Returns the node pointer if the node exists.
// Returns NULL if the node doesn't exist or the graph is NULL
graph_node_t* find_node( graph_t * g, int value){
    if ( g == NULL ) return NULL;

    int pos = 0;
    node_t *curr_node = g->nodes->head;
    while(curr_node != NULL){
        // data of the head of g->node contains a graph node
        graph_node_t* curr_g_node = (graph_node_t*) curr_node->data;
        if((int)curr_g_node->data == value){
            return curr_g_node;
        }
        pos++;
        curr_node = curr_node->next;
    }
    return NULL;
}

// Creates a graph node
// Note: This relies on your dll implementation.
graph_node_t * create_graph_node(int value){
    graph_node_t* graph_node = (graph_node_t*)malloc(sizeof(graph_node_t));
    
    if ( graph_node == NULL ) return NULL;
    
    graph_node->data = value;
    graph_node->inNeighbors = create_dll();
    graph_node->outNeighbors = create_dll();
    
    return graph_node;
}

// Returns 1 on success
// Returns 0 on failure ( or if the node already exists )
// Returns -1 if the graph is NULL.
int graph_add_node(graph_t* g, int value){
    if ( g == NULL ) return -1;
    
    // if the value exists in any graph nodes
    if (find_node_in_graph_dll(g, value) != -1) return 0;

    // if value does not exist in any graph node's data, create and insert into dll
    graph_node_t* newNode = create_graph_node(value);
    if ( newNode == NULL ) return -1;
    assert(g->nodes);
    dll_push_back(g->nodes, newNode);
    g->numNodes++;
    
    return 1;
}

// Returns 1 on success
// Returns 0 on failure ( or if the source or destination nodes don't exist, or the edge doesn't exists )
// Returns -1 if the graph is NULL.
int graph_remove_edge(graph_t * g, int source, int destination){
    // TODO: Implement me!
    //The function removes an edge from source to destination but not the other way.
    //Make sure you remove destination from the out neighbors of source.
    //Make sure you remove source from the in neighbors of destination.
    if ( g == NULL ) return -1;

    int src_pos = find_node_in_graph_dll(g, source);
    int dest_pos = find_node_in_graph_dll(g, destination);
    if(src_pos == -1 || dest_pos == -1) return 0;

    graph_node_t *src = dll_get(g->nodes, src_pos);
    graph_node_t *dest = dll_get(g->nodes, dest_pos);

    int src_neighbor_pos = neighbor_dll_contains_graph_node(src->outNeighbors, destination);
    int dest_neighbor_pos = neighbor_dll_contains_graph_node(dest->inNeighbors, source);

    if(src_neighbor_pos < 0 || dest_neighbor_pos < 0) return 0;
    dll_remove(src->outNeighbors, src_neighbor_pos);
    dll_remove(dest->inNeighbors, dest_neighbor_pos);

    g->numEdges--;
    return 1;
}

// Returns 1 on success
// Returns 0 on failure ( or if the node doesn't exist )
// Returns -1 if the graph is NULL.
int graph_remove_node(graph_t* g, int value){
    // TODO: Implement me!
    // The function removes the node from the graph along with any edges associated with it.
    // That is, this node would have to be removed from all the in and out neighbor's lists that countain it.
    if ( g == NULL ) return -1;

    int pos = find_node_in_graph_dll(g, value);
    // the node does not exist
    if(pos == -1) return 0;

    graph_node_t *node = dll_get(g->nodes, pos);
    node_t *inNode = node->inNeighbors->head;
    node_t *outNode = node->outNeighbors->head;

    // Remove edges related to all inNeighbors of value node, 
    // i.e. (1 -> 5), (2 -> 5), (1, 2) would be the inNeighbors of 5
    while(inNode != NULL){
        graph_node_t *curr_in_node = inNode->data;
        node_t *nextNode = inNode->next;
        int res = graph_remove_edge(g, curr_in_node->data, value);
        if(res != 1) return 0;
        inNode = nextNode;
    }

    // Remove edges related to all inNeighbors of value node, 
    // i.e. (5 -> 1), (5 -> 2), (1, 2) would be the outNeighbors of 5
    while(outNode != NULL){
        graph_node_t *curr_out_node = outNode->data;
        node_t *nextNode = outNode->next;
        int res = graph_remove_edge(g, value, curr_out_node->data);
        if(res != 1) return 0;
        outNode = nextNode;
    }

    // freeing the graph_node_t's 2 dlls and the graph_node_t itself
    free_dll(node->inNeighbors);
    free_dll(node->outNeighbors);
    free(node);
    
    // freeing the node_t in g->nodes
    dll_remove(g->nodes, pos);
    g->numNodes--;

    return 1;
}

// Returns 1 on success
// Returns 0 on failure ( or if the source or destination nodes don't exist, or the edge already exists )
// Returns -1 if the graph is NULL.
int graph_add_edge(graph_t * g, int source, int destination){
    // TODO: Implement me!
    // The function adds an edge from source to destination but not the other way.
    // Make sure you are not adding the same edge multiple times.
    // Make sure you modify the in and out neighbors appropriatelly. destination will be an out neighbor of source.
    // Source will be an in neighbor of destination.
    if ( g == NULL ) return -1;

    // Working on out neighor (source -> destination)
    int src_pos = find_node_in_graph_dll(g, source);
    // if graph node dest cannot be found
    if(src_pos == -1) return 0;
    graph_node_t *src = dll_get(g->nodes, src_pos);

    // Working on in neighor (source -> destination)
    int dest_pos = find_node_in_graph_dll(g, destination);
    // if graph node dest cannot be found 
    if(dest_pos == -1) return 0;
    graph_node_t *dest = dll_get(g->nodes, dest_pos);


    // if src's outNeighors contains source (0 means src->outNeighors exists but without destination value)
    if(neighbor_dll_contains_graph_node(src->outNeighbors, destination) >= 0) return 0;
    int res = dll_push_back(src->outNeighbors, dest);
    if(res != 1) return 0;

    // if dest's inNeighors contains source (0 means dest->inNeighors exists but without source value)
    if(neighbor_dll_contains_graph_node(dest->inNeighbors, source) >= 0) return 0;
    res = dll_push_back(dest->inNeighbors, src);
    if(res != 1) return 0;

    g->numEdges++;

    return 1;
}

// Returns 1 on success
// Returns 0 on failure ( or if the source or destination nodes don't exist )
// Returns -1 if the graph is NULL.
int contains_edge( graph_t * g, int source, int destintaion){
    // TODO: Implement me!
    if ( g == NULL ) return -1;

    int src_pos = find_node_in_graph_dll(g, source);
    int dest_pos = find_node_in_graph_dll(g, destintaion);
    if(src_pos == -1 || dest_pos == -1) return 0;

    graph_node_t *src = dll_get(g->nodes, src_pos);
    graph_node_t *dest = dll_get(g->nodes, dest_pos);

    if(neighbor_dll_contains_graph_node(src->outNeighbors, destintaion) >=0 && neighbor_dll_contains_graph_node(dest->inNeighbors, source) >= 0)
        return 1;
    return 0;
}

// Returns dll_t* of all the in neighbors of this node.
// Returns NULL if thte node doesn't exist or if the graph is NULL.
dll_t* getInNeighbors( graph_t * g, int value ){
    // TODO: Implement me!
    if ( g == NULL ) return NULL;

    // Working on out neighor (source -> destination)
    int node_pos = find_node_in_graph_dll(g, value);
    // if graph node dest cannot be found or 
    // src's outNeighors contains source (0 means src->outNeighors exists but without destination value)
    if(node_pos == -1) return NULL;
    graph_node_t *node = dll_get(g->nodes, node_pos);
    return node->inNeighbors;
}

// Returns the number of in neighbors of this node.
// Returns -1 if the graph is NULL or the node doesn't exist.
int getNumInNeighbors( graph_t * g, int value){
    // TODO: Implement me!
    if ( g == NULL ) return -1;

    dll_t * l = getInNeighbors(g, value);
    if (l == NULL) return -1;
    int length = dll_size(l);
    if (length == -1) return -1;

    return length;
}

// Returns dll_t* of all the out neighbors of this node.
// Returns NULL if thte node doesn't exist or if the graph is NULL.
dll_t* getOutNeighbors( graph_t * g, int value ){
    // TODO: Implement me!
    if ( g == NULL ) return NULL;

    // Working on out neighor (source -> destination)
    int node_pos = find_node_in_graph_dll(g, value);
    // if graph node dest cannot be found or 
    // src's outNeighors contains source (0 means src->outNeighors exists but without destination value)
    if(node_pos == -1) return NULL;
    graph_node_t *node = dll_get(g->nodes, node_pos);
    return node->outNeighbors;
}

// Returns the number of out neighbors of this node.
// Returns -1 if the graph is NULL or the node doesn't exist.
int getNumOutNeighbors( graph_t * g, int value){
    // TODO: Implement me!
    if ( g == NULL ) return -1;

    dll_t * l = getOutNeighbors(g, value);
    if (l == NULL) return -1;
    int length = dll_size(l);
    if (length == -1) return -1;

    return length;
}

// Returns the number of nodes in the graph
// Returns -1 if the graph is NULL.
int graph_num_nodes(graph_t* g){
    // TODO: Implement me!
    if ( g == NULL ) return -1;
    return g->numNodes;
}

// Returns the number of edges in the graph,
// Returns -1 on if the graph is NULL
int graph_num_edges(graph_t* g){
    // TODO: Implement me!
    if ( g == NULL ) return -1;
    return g->numEdges;
}

// Free graph
// Removes a graph and ALL of its elements from memory.
// This should be called before the program terminates.
// Make sure you free all the dll's too.
void free_graph(graph_t* g){
    // TODO: Implement me!
    if (g == NULL) return;
    node_t* curr_node = g->nodes->head;
    while(curr_node != NULL){
        // Freeing graph_node_t inside g->node dll
        graph_node_t* curr_g_node = curr_node->data;
        free_dll(curr_g_node->inNeighbors);
        free_dll(curr_g_node->outNeighbors);
        free(curr_g_node);
        curr_node = curr_node->next;
    }
    // freed all graph_node_t, now free g->node itself
    free_dll(g->nodes);
    free(g);
}

// ------------------------------------------------------------
// IMPLEMENT THESE AFTER ALL THE FUNCTIONS ABOVE ARE --TESTED--
// AND CONFIRMED TO WORK

// returns 1 if we can reach the destination from source
// returns 0 if it is not reachable
// returns -1 if the graph is NULL (using BFS)
// Using BFS over DFS prevents getting stuck in the cycle
int graph_is_reachable(graph_t * g, int source, int dest){
    if (g == NULL) return -1;

    int src_pos = find_node_in_graph_dll(g, source);
    int dest_pos = find_node_in_graph_dll(g, dest);
    if(src_pos < 0 || dest_pos < 0){
        return 0;
    } 

    // initialize dll which contains the nodes visited
    dll_t *visited = create_dll();

    // dll queue for bfs initialized, only push_back and pop_front would be used for queue
    dll_t *queue = create_dll();
    dll_push_back(queue, source);

    while(dll_size(queue) > 0){
        int explore = dll_pop_front(queue);
        dll_push_back(visited, explore);
        node_t *outNeighbors_node = getOutNeighbors(g, explore)->head;
        while(outNeighbors_node != NULL){
            // Add the node data to visited dll if it is not visited before for queue operations
            graph_node_t *curr_g_node = outNeighbors_node->data;
            int value = curr_g_node->data;
            if(value == dest){
                free_dll(visited);
                free_dll(queue);
                return 1;
            }
            
            // The second part of this equality evluation would prevent a cycle from happening
            if(dll_contains_graph_node(queue, value) == -9999 && dll_contains_graph_node(visited, value) == -9999){
                dll_push_back(queue, value);
            }

            outNeighbors_node = outNeighbors_node->next;
        }
    }
    free_dll(visited);
    free_dll(queue);
    return 0;
}


// helper function for graph_has_cycles
int dfs_helper_graph_has_cycles(graph_t* g, dll_t* stack, int val){

    if(dll_contains_graph_node(stack, val) >= 0) return 1;

    dll_push_back(stack, val);

    node_t *outNeighbors_node = getOutNeighbors(g, val)->head;
    while(outNeighbors_node != NULL){
        graph_node_t *curr_g_node = outNeighbors_node->data;
        int value = curr_g_node->data;
        if(dfs_helper_graph_has_cycles(g, stack, value) == 1) return 1;
        outNeighbors_node = outNeighbors_node->next;
    }
    // if the node is a dead end and not dest
    dll_pop_back(stack);
    return 0;
}

// returns 1 if there is a cycle in the graph
// returns 0 if no cycles exist in the graph
// returns -1 if the graph is NULL 
// You may use either BFS or DFS to complete this task.
// Using dfs to check for cycles recurrsively
int graph_has_cycle(graph_t * g){
    if (g == NULL) return -1;

    // start with first value in g->nodes->head and traversal with it's outNeighbors for dfs
    graph_node_t *node = g->nodes->head->data;
    
    // dll stack for dfs initialized, only dll_push_back and dll_pop_back would be used for stack
    dll_t *stack = create_dll();

    int res = dfs_helper_graph_has_cycles(g, stack, node->data);
    free_dll(stack);
    return res;
}


// helper function for graph_print_path
int dfs_helper_graph_print_path(graph_t* g, dll_t* stack, int val, int dest){
    // TODO: Cant a graph with cycle still have a path from src to dest?
    if(dll_contains_graph_node(stack, val) >= 0) return 0;

    dll_push_back(stack, val);

    // base case if dest is found
    if(val == dest) return 1;

    node_t *outNeighbors_node = getOutNeighbors(g, val)->head;
    while(outNeighbors_node != NULL){
        graph_node_t *curr_g_node = outNeighbors_node->data;
        int value = curr_g_node->data;
        if(dfs_helper_graph_print_path(g, stack, value, dest) == 1) return 1;
        outNeighbors_node = outNeighbors_node->next;
    }
    // if the node is a dead end and not dest
    dll_pop_back(stack);
    return 0;
}

// prints any path from source to destination if there exists a path from the source to the destination.
// exists a path from the source to the destination.
// Note: Consider using one of the other functions to help you
//       determine if a path exists first
// (Choose either BFS or DFS, typically DFS is much simpler)
//
// Returns 1 if there is a path from source to destination
// Returns 0 if there is not a path from a source to destination
// Returns -1 if the graph is NULL
int graph_print_path(graph_t * g, int source, int dest){
    if (g == NULL) return -1;

    int src_pos = find_node_in_graph_dll(g, source);
    int dest_pos = find_node_in_graph_dll(g, dest);
    if(src_pos < 0 || dest_pos < 0){
        return 0;
    }

    // Path found if src and dest is the same
    if(source == dest) return 1;

    // print graph using DFS only if it has no cycles and the source to destination is reachable
    if(graph_is_reachable(g, source, dest) == 0) return 0;

    // dll stack for dfs initialized, only dll_push_back and dll_pop_back would be used for stack
    dll_t *stack = create_dll();

    // run df populate stack
    dfs_helper_graph_print_path(g, stack, source, dest);

    print_dll(stack);
    free_dll(stack);
    return 1;
}

#endif
