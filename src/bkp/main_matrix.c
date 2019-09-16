#include <stdio.h>
#include <stdlib.h>
#include <glib.h>
#include <glib/gprintf.h>
#include <gsl/gsl_errno.h>
#include <gsl/gsl_math.h>
#include <gsl/gsl_matrix.h>

#include "defs.h"
#include "io.h"


gsl_matrix *matrix_from_vector(double *vector, size_t n);

gsl_matrix *matrix_from_vector(double *vector, size_t n)
{
    gsl_matrix *M = gsl_matrix_alloc(n, n);
    for(size_t i=0; i < n; i++)
        for (size_t j=0; j < n; j++)
            gsl_matrix_set(M, i, j, vector[i*n+j]);

    return M;
}

struct graph
{
    GSList * nodes;
    gsize n;
    gsize m;
};

struct node
{
    GSList *neighbors;
    gint weight;
    gsize r;
    GString * label;
};

struct edge
{
    struct node * src;
    struct node * dst;
    gint weight;
};

struct graph * graph_new(void);
void graph_free(struct graph *graph);
void graph_print_neighbors(struct node *n);
void graph_print_node(struct node *n);
void graph_print(struct graph *graph);
struct node * graph_node_add(struct graph *graph, const gchar * label, gint weight);
struct edge * graph_edge_add(struct graph *graph, struct node *src, struct node *dst, gint weight);


struct graph * graph_new(void)
{
    struct graph * g = g_malloc_n(1, sizeof *g);
    g->nodes = NULL;
    g->m = 0;
    g->n = 0;

    return g;
}

void graph_free(struct graph *graph) {
    // Need remove all neigbors from all nodes
    g_slist_free(graph->nodes);
    g_free(graph);
}

struct node * graph_node_add(struct graph *graph, const gchar * label, gint weight)
{
    /* Create the node */
    struct node * n = g_malloc_n(1, sizeof *n);
    n->neighbors = NULL;
    n->weight = weight;
    n->r = 0;
    n->label = g_string_new(label);

    /* Add node to the graph */
    graph->nodes = g_slist_append(graph->nodes, n);
    graph->n++;
    
    return n;
}

struct edge * graph_edge_add(struct graph *graph, struct node *src, struct node *dst, gint weight)
{
    /* Create the edge */
    struct edge * e = g_malloc_n(1, sizeof *e);
    e->src = src;
    e->dst = dst;
    e->weight = weight;

    /* Add the dst as a neighboor of src */
    src->neighbors = g_slist_append(src->neighbors, dst);
    src->r++;

    /* Add edge count in graph */
    graph->m++;

    return e;
}

void graph_print_neighbors(struct node *n)
{
    g_printf("%s(%ld), ", n->label->str, 0L); // how to find edge weight?
}

void graph_print_node(struct node *n)
{
    g_printf("%s(%d) -> ", n->label->str, n->weight);
    g_slist_foreach(n->neighbors, (GFunc)graph_print_neighbors, NULL);
    g_printf("\n");
}

void graph_print(struct graph *graph)
{
    g_slist_foreach(graph->nodes, (GFunc)graph_print_node, NULL);
}


int main(int argc, char *argv[])
{

    if (argc != 2) {
        fprintf(stderr, "Usage: %s <FILENAME>\n", argv[0]);
        exit(1);
    } 

    char *fname = argv[1];
    double *vector = NULL; //malloc(sizeof * vector);
    size_t n = read_matrix_file(fname, &vector);
    gsl_matrix *M = matrix_from_vector(vector, n);
    free(vector);

    printf("Max V: %d  E: %d\n", MAX_VERTICES, MAX_EDGES);

    gsl_matrix_fprintf(stdout, M, "%.2f");
    gsl_matrix_free(M);

    printf("GGRAPHS\n");

    struct graph * G = graph_new();
    struct node * u = graph_node_add(G, "rj", 10);
    struct node * v = graph_node_add(G, "sp", 20);
    struct node * w = graph_node_add(G, "mg", 15);
    struct edge * e_0 = graph_edge_add(G, u, v, 30);
    struct edge * e_1 = graph_edge_add(G, u, w, 20);
    struct edge * e_2 = graph_edge_add(G, v, w, 20);

    printf("Number of nodes %ld\n", G->n);
    g_printf("Number of neighbors of node %s: %ld\n", u->label->str, u->r);

    graph_print(G);

    // ADD NODES
    graph_free(G);



    return 0;
}
