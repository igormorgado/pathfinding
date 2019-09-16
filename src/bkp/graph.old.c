#include <glib.h>
#include <glib/gprintf.h>

/*
 * TODO: 
 * Write helper functions to retrieve a node pointer by index
 * Write helper functions to retrieve a node pointer by label
 * Write helper functions to retrieve a pointer to node edges
 * Correctly count the number of edges, incoming edges and outgoing edges
 *  both in graph itself as in each vertex.
 */


struct graph
{
    GSList * nodes;         // A list of nodes in graph
    gsize n;                // Number of nodes
    gsize m;                // Number of edges
};

struct node
{
    GSList *neighbors;      // A list of all adjacent nodes
    gint weight;            // Node weight
    gsize r;                // Number of outbounding edges
    gsize s;                // Number of inbounding edges
    GString * label;        // Node label
};

struct neighbor
{
    struct node * dst;      // The node that is pointed too
    gint weight;            // Edge SRC->DST weight
};


struct graph * graph_new(void);
struct node * graph_node_add(struct graph *graph, const gchar * label, gint weight);
void graph_edge_add(struct graph *graph, struct node *src, struct node *dst, gint weight);

void graph_free(struct graph *graph);
void graph_nodes_free(struct node *node);
void graph_neighbors_free(struct neighbor *neighbor);

void graph_neighbors_print(struct neighbor *n, gpointer user_data);
void graph_node_print(struct node *n, gpointer user_data);
void graph_print(struct graph *graph);

void graph_print_debug(struct graph *G, struct node *n);

/*
 * Creates a new graph structure
 */
struct graph * graph_new(void)
{
    struct graph * g = g_malloc0_n(1, sizeof *g);
    g->nodes = NULL;        // List of nodes
    g->n = 0;               // Number of nodes
    g->m = 0;               // Number of edges

    return g;
}

struct node * graph_node_add(struct graph *graph, const gchar * label, gint weight)
{
    /* Create the node */
    struct node * n = g_malloc0_n(1, sizeof *n);
    n->neighbors = NULL;
    n->weight = weight;
    n->r = 0;
    n->label = g_string_new(label);

    /* Add node to the graph */
    graph->nodes = g_slist_append(graph->nodes, n);
    graph->n++;
    
    return n;
}

void graph_edge_add(struct graph *graph, struct node *src, struct node *dst, gint weight)
{
    /* Create the edge to neighbor */
    struct neighbor * n = g_malloc0_n(1, sizeof *n);
    n->dst = dst;
    n->weight = weight;

    /* Add the dst as a neighboor of src */
    src->neighbors = g_slist_append(src->neighbors, n);
    src->r++;

    /* Add edge count in graph */
    graph->m++;
}

void graph_neighbors_free(struct neighbor *neighbor)
{
    if (neighbor)
        g_free(neighbor);
}

void graph_nodes_free(struct node *node)
{
    if (node->label)
        g_string_free(node->label, TRUE);
    if (node->neighbors)
        g_slist_free_full(node->neighbors, (GDestroyNotify)&graph_neighbors_free);
    g_free(node);
}

void graph_free(struct graph *graph) {

    if(graph->nodes)
        g_slist_free_full(graph->nodes, (GDestroyNotify)&graph_nodes_free);
    g_free(graph);
}


void graph_neighbors_print(struct neighbor *n, gpointer user_data)
{
    g_printf("%s(%d), ", n->dst->label->str, n->weight); // how to find edge weight?
}

void graph_node_print(struct node *n, gpointer user_data)
{
    g_printf("%s(%d) -> ", n->label->str, n->weight);
    g_slist_foreach(n->neighbors, (GFunc)graph_neighbors_print, NULL);
    g_printf("\n");
}

void graph_print(struct graph *graph)
{
    g_slist_foreach(graph->nodes, (GFunc)graph_node_print, NULL);
}

void graph_print_debug(struct graph *G, struct node *n)
{
    if (G)
        g_printf("Number of nodes %ld\n", G->n);
    if (n && n->label && n->label->str) {
            g_printf("Number of neighbors of node %s: %ld\n", n->label->str, n->r);
            g_printf(" Node '%s' address (%p)\n", n->label->str, (gpointer)n);
    }
    if(G->nodes)
        g_printf("GNode '%s' address (%p)\n",
            ((struct node *)g_slist_nth_data(G->nodes, 1))->label->str,
            (gpointer)g_slist_nth_data(G->nodes, 1));
}


int main(void)
{
    /* Generic pointers */
    struct graph *G;
    struct node  *n;

    /*
     * Individual nodes
     */
    g_printf("\nIndividual\n");
    struct graph *graph1 = graph_new();
    G = graph1;

    struct node * u = graph_node_add(G, "u", 10);
    struct node * v = graph_node_add(G, "v", 20);
    struct node * w = graph_node_add(G, "w", 15);
    n = v;

    graph_edge_add(G, u, v, 3);
    graph_edge_add(G, u, w, 2);
    graph_edge_add(G, v, w, 1);

    graph_print(G);
    graph_print_debug(G, n);
    graph_free(G);

    /*
     *  Using array of pointers to nodes
     */
    g_printf("\nArray of pointers\n");
    struct graph *graph2 = graph_new();
    G = graph2;

    struct node *node[3];
    node[0] = graph_node_add(G, "u", 10);
    node[1] = graph_node_add(G, "v", 20);
    node[2] = graph_node_add(G, "w", 15);
    n = node[1];

    graph_edge_add(G, node[0], node[1], 3);
    graph_edge_add(G, node[0], node[2], 2);
    graph_edge_add(G, node[1], node[2], 1);

    graph_print(G);
    graph_print_debug(G, n);
    graph_free(G);

    // /*
    //  * Nodes on the stack
    //  */
    // g_printf("\nStack\n");
    // struct graph *graph3 = graph_new();
    // G = graph3;

    // struct node nd[3];
    // nd[0] = *(graph_node_add(G, "u", 10));
    // nd[1] = *(graph_node_add(G, "v", 20));
    // nd[2] = *(graph_node_add(G, "w", 15));
    // n = &nd[1];

    // graph_edge_add(G, &nd[0], &nd[1], 3);
    // graph_edge_add(G, &nd[0], &nd[2], 2);
    // graph_edge_add(G, &nd[1], &nd[2], 1);

    // graph_print(G);
    // graph_print_debug(G, n);
    // graph_free(G);

    // /*
    //  * Nodes on the heap 
    //  */
    // g_printf("\nHeap\n");
    // struct graph *graph4 = graph_new();
    // G = graph4;

    // // struct node *ptr, *vertex = g_malloc0_n(3, sizeof * vertex);
    // // ptr = vertex;
    // // ptr++ = graph_node_add(I, "u", 10);
    // // ptr++ = graph_node_add(I, "v", 20);
    // // ptr   = graph_node_add(I, "w", 15);
    // // graph_edge_add(I, vertex[0], node[1], 3);
    // // graph_edge_add(I, vertex[0], node[2], 2);
    // // graph_edge_add(I, vertex[1], node[2], 1);

    // graph_print(G);
    // graph_print_debug(G, n);
    // graph_free(G);
    //
    return(0);
}

