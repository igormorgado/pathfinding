#include <glib.h>
#include <glib/gprintf.h>


struct graph
{
    GArray * nodes;         // A list of nodes in graph
    gsize n;                // Number of nodes
    gsize m;                // Number of edges
};

struct node
{
    GArray *neighbors;      // A list of all adjacent nodes
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

// struct node * graph_node_idx(struct graph *graph, gint idx);

// void graph_free(struct graph *graph);
// void graph_nodes_free(struct node *node);
// void graph_neighbors_free(struct neighbor *neighbor);

// void graph_neighbors_print(struct neighbor *n, gpointer user_data);
// void graph_node_print(struct node *n, gpointer user_data);
void graph_print(struct graph *graph);
// 
// void graph_print_debug(struct graph *G, struct node *n);

/*
 * Creates a new graph structure
 */
struct graph * graph_new(void)
{
    struct graph * g = g_new(struct graph, 1);
    g->nodes = g_array_new (FALSE, FALSE, sizeof (struct node));        // List of nodes
    g->n = 0;               // Number of nodes
    g->m = 0;               // Number of edges

    return g;
}

struct node * graph_node_add(struct graph *graph, const gchar * label, gint weight)
{
    /* Create the node */
    struct node * n = g_new(struct node, 1);
    n->neighbors = g_array_new(FALSE, FALSE, sizeof (struct neighbor));
    n->weight = weight;
    n->r = 0;
    n->label = g_string_new(label);

    /* Add node to the graph */
    // graph->nodes = g_slist_append(graph->nodes, n);
    graph->nodes = g_array_append_val(graph->nodes, n);
    graph->n++;
    
    return n;
}

void graph_edge_add(struct graph *graph, struct node *src, struct node *dst, gint weight)
{
    /* Create the edge to neighbor */
    struct neighbor * n = g_new(struct neighbor, 1);
    n->dst = dst;
    n->weight = weight;

    /* Add the dst as a neighboor of src */
    //src->neighbors = g_slist_append(src->neighbors, n);
    src->neighbors = g_array_append_val(src->neighbors, n);
    src->r++;

    /* Add edge count in graph */
    graph->m++;
    g_printf("Adding %s -> %s (%d)\n",
            src->label->str,
            dst->label->str,
            weight);

}

// void graph_neighbors_free(struct neighbor *neighbor)
// {
//     if (neighbor)
//         g_free(neighbor);
// }
// 
// void graph_nodes_free(struct node *node)
// {
//     if (node->label)
//         g_string_free(node->label, TRUE);
//     if (node->neighbors)
//         g_slist_free_full(node->neighbors, (GDestroyNotify)&graph_neighbors_free);
//     g_free(node);
// }
// 
// void graph_free(struct graph *graph) {
// 
//     if(graph->nodes)
//         g_slist_free_full(graph->nodes, (GDestroyNotify)&graph_nodes_free);
//     g_free(graph);
// }


// void graph_neighbors_print(struct neighbor *n, gpointer user_data)
// {
//     if(n->dst && n->dst->label->str)
//         g_printf("%s(%d), ", n->dst->label->str, n->weight);
// }
// 
// void graph_node_print(struct node *n, gpointer user_data)
// {
//     if(n->label->str)
//         g_printf("%s(%d) -> ", n->label->str, n->weight);
//     g_slist_foreach(n->neighbors, (GFunc)graph_neighbors_print, NULL);
//     g_printf("\n");
// }
// 
// void graph_print(struct graph *graph)
// {
//     g_slist_foreach(graph->nodes, (GFunc)graph_node_print, NULL);
// }
// 
// void graph_print_debug(struct graph *G, struct node *n)
// {
//     if (G)
//         g_printf("Number of nodes %ld\n", G->n);
//     if (n && n->label && n->label->str) {
//             g_printf("Number of neighbors of node %s: %ld\n", n->label->str, n->r);
//             g_printf(" Node '%s' address (%p)\n", n->label->str, (gpointer)n);
//     }
//     if(G->nodes)
//         g_printf("GNode '%s' address (%p)\n",
//             ((struct node *)g_slist_nth_data(G->nodes, 1))->label->str,
//             (gpointer)g_slist_nth_data(G->nodes, 1));
// }


int main(void)
{
    /* Generic pointers */
    struct graph *G;
    struct node  *n;

    struct graph *graph1 = graph_new();
    G = graph1;

    struct node *node[3];
    node[0] = graph_node_add(G, "u", 10);
    node[1] = graph_node_add(G, "v", 20);
    node[2] = graph_node_add(G, "w", 15);
    n = node[1];

    graph_edge_add(G, node[0], node[1], 3);
    graph_edge_add(G, node[0], node[2], 2);
    graph_edge_add(G, node[1], node[2], 1);

    g_printf("%s %d\n",
            (G->nodes->data[0])->label->str,
            (G->nodes->data[0])->weight);
 

    // graph_print(G);
    // graph_print_debug(G, n);
    // graph_free(G);

    return(0);
}

