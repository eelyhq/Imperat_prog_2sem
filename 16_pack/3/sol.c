#include <stdlib.h>
#include "sol.h"

typedef struct Node_s {
    Edge edge;
    struct Node_s* next_edge;
}Node;

static Node** graph = NULL; // make static var for matrix
static int total_vertices = 0; // static var for num vertices

void push(Node** new_graph, Edge* new_edge, int vertice) {

    if (new_graph[vertice] == NULL) { // there is no one edge in matrix -> make first edge
        new_graph[vertice] = (Node*)malloc(sizeof(Node) * 1); // create node for new edge

        new_graph[vertice] -> edge = *new_edge; // add edge
        new_graph[vertice] -> next_edge = NULL; // reset to NULL next edge
    }
    else { // there is at least one edge
        Node* pointer_next_edge =  new_graph[vertice]; // we add edges at the beginning, because order doesen't matter

        new_graph[vertice] = (Node*)malloc(sizeof(Node) * 1); // create node for new edge

        new_graph[vertice] -> edge = *new_edge; // add edge
        new_graph[vertice] -> next_edge = pointer_next_edge; // return pointer
    }

}
//==============================================
//call these functions to get the graph data:
//returns N –- the number of vertices in the graph
// int getVerticesCount() {
//     printf("write num og vertices\n");
//     int a;
//     scanf("%d", &a);
//     return a;
// }
//reads the next edge from the edge list
//if there is next edge, returns 1 and stores that edge to *oEdge
//if there is no next edge, returns 0 without touching pointer
// int readEdge (Edge* oEdge) {
//     int from, to, mass;
//
//     if (scanf("%d %d %d", &from, &to, &mass) < 3) {
//         return 0;
//     }
//
//     oEdge->from = from;
//     oEdge->to = to;
//     oEdge->weight = mass;
//
//     return 1;
// }
//==============================================
//implement these functions in your solution:
//this function is called first to initialize graph
//you are expected to read graph here and fill internal data structures
void init() {
    int n = getVerticesCount(); // get graph size(num of vertices)

    total_vertices = n; // remember num of vertices

    graph = (Node**)calloc(n, sizeof(Node*)); // make Node list for incident matrix

    Edge new_edge;
    int f = readEdge(&new_edge);

    while (f) {
        push(graph, &new_edge,(&new_edge) -> from); // add edges to matrix twice
        int fr = new_edge.from; // swap from and to
        new_edge.from = new_edge.to;
        new_edge.to = fr;
        push(graph, &new_edge, (&new_edge) -> from);

        f = readEdge(&new_edge); // read next edge
    }

}

//this function is called whet the graph is no more needed
//you are expected to cleanup the used resources
void destroy() {
    for (int i = 0; i < total_vertices; i++) {
        Node* edge = graph[i];

        if (edge != NULL) {
            while (edge -> next_edge != NULL) {
                Node* tmp = edge -> next_edge; // remember pointer

                free(edge); // delete curr node
                edge = tmp; // next edge make current
            }
            free(edge); // free last edge
        }
    }
    free(graph); // free all matrix
}

//returns number of edges indicent to vertex iVertex
int getEdgesCount(int iVertex) {
    Node* tmp = graph[iVertex]; // var for moving on nodes

    if (tmp == NULL) { // there is no edges
        return 0;
    }

    int res = 1; // there is at least one edge

    while (tmp -> next_edge != NULL) {
        res++;
        tmp = tmp -> next_edge;
    }

    return res;
}
//returns iIndex-th edge incident to the vertex iVertex
//it must have .from == Vertex and .to denoting the other end
Edge getIncidentEdge (int iVertex , int iIndex ) {
    Node* tmp = graph[iVertex];

    for (int i = 0; i < iIndex; i++) {
        tmp = tmp -> next_edge;
    }

    return tmp -> edge;
}