#include <glib.h>
#include <glib/gprintf.h>

struct graph
{
    GHashTable * nodes;         // A list of nodes in graph
};

struct node
{
    GPtrArray * neighbors;      // A list of all adjacent nodes
    gint weight;            // Node weight
    GString * label;        // Node label
};

struct neighbor
{
    struct node * dst;      // The node that is pointed too
    gint weight;            // Edge SRC->DST weight
};


struct graph * graph_new(void);
struct node * graph_node_add(struct graph *graph, gchar * label, gint weight);
void graph_edge_add(struct graph *graph, struct node *src, struct node *dst, gint weight);


struct graph * graph_new(void)
{
    struct graph * g = g_new(struct graph, 1);
    g->nodes = g_hash_table_new(g_str_hash, g_str_equal);
    return g;
}

struct node * graph_node_add(struct graph *graph, gchar * label, gint weight)
{
    struct node * n = g_new(struct node, 1);
    n->neighbors = g_ptr_array_new();
    n->weight = weight;
    n->label = g_string_new(label);
    g_hash_table_insert(graph->nodes, label, n);
    return n;
}

void graph_edge_add(struct graph *graph, struct node *src, struct node *dst, gint weight)
{
    struct neighbor * n = g_new(struct neighbor, 1);
    n->dst = dst;
    n->weight = weight;
    g_ptr_array_add(src->neighbors, dst);   // Add dst as neiggbor
}


int main(void)
{
    struct graph *G = graph_new();
    graph_node_add(G, "A", 10);
    graph_edge_add(G, "A", "B", 4);
}


// void graph_neighbors_free(struct neighbor *neighbor)
// {
//     g_printf("Freeing edge");
//     if (neighbor->weight) {
//         g_printf(" with weight %d", neighbor->weight);
//     }
// 
//     if (neighbor->dst) {
//         g_printf(" destination %s", neighbor->dst->label->str);
//     }
//     
//     if (neighbor)
//         g_free(neighbor);
// 
//     g_printf("\n");
// }
// 
// void graph_nodes_free(struct node *node)
// {
//     g_printf("Freeing node");
//     if (node->label) {
//         g_printf(" %s", node->label->str);
//         g_string_free(node->label, TRUE);
//     }
//     g_printf("\n");
// 
//     if (node->neighbors) {
//         g_slist_free_full(node->neighbors, (GDestroyNotify)&graph_neighbors_free);
//     }
// 
//     g_free(node);
// }
// 
// void graph_free(struct graph *graph) {
// 
//     if(graph->nodes) {
//         g_slist_free_full(graph->nodes, (GDestroyNotify)&graph_nodes_free);
//     }
//     g_free(graph);
// }
// 
// 
// void graph_neighbors_print(struct neighbor *n, gpointer user_data)
// {
//     g_printf("%s(%d), ", n->dst->label->str, n->weight); // how to find edge weight?
// }
// 
// void graph_node_print(struct node *n, gpointer user_data)
// {
//     g_printf("%s(%d) -> ", n->label->str, n->weight);
//     g_slist_foreach(n->neighbors, (GFunc)graph_neighbors_print, NULL);
//     g_printf("\n");
// }
// 
// void graph_print(struct graph *graph)
// {
//     g_slist_foreach(graph->nodes, (GFunc)graph_node_print, NULL);
// }














    /*
     * Individual declaration
     */
    // g_printf("\nIndividual\n");
//     struct graph *G = graph_new();
//     // struct graph *G, *graph1  = graph_new();
//     // G = graph1;
// 
//     struct node * u = graph_node_add(G, "u", 10);
//     struct node * v = graph_node_add(G, "v", 20);
//     struct node * w = graph_node_add(G, "w", 15);
//     graph_edge_add(G, u, v, 3);
//     graph_edge_add(G, u, w, 2);
//     graph_edge_add(G, v, w, 1);
//     // g_printf("Number of nodes %ld\n", G->n);
//     // g_printf("Number of neighbors of node %s: %ld\n", u->label->str, u->r);
//     graph_print(G);
// 
//     /* Comparing pointing to same object */
//     // g_print(" Node '%s' address (%p)\n", v->label->str, (gpointer)v);
//     // g_print("GNode '%s' address (%p)\n",
//     //         ((struct node *)g_slist_nth_data(G->nodes, 1))->label->str,
//     //         (gpointer)g_slist_nth_data(G->nodes, 1));
//     graph_free(G);

    //
// void graph_free(struct graph *graph);
// void graph_nodes_free(struct node *node);
// void graph_neighbors_free(struct neighbor *neighbor);
// 
// void graph_neighbors_print(struct neighbor *n, gpointer user_data);
// void graph_node_print(struct node *n, gpointer user_data);
// void graph_print(struct graph *graph);
    /*
     *  Using array  of pointers
     */
    // g_printf("\nArray of pointers\n");
    // struct graph * H = graph_new();
    // struct node *node[3];
    // node[0] = graph_node_add(H, "u", 10);
    // node[1] = graph_node_add(H, "v", 20);
    // node[2] = graph_node_add(H, "w", 15);
    // graph_edge_add(H, node[0], node[1], 3);
    // graph_edge_add(H, node[0], node[2], 2);
    // graph_edge_add(H, node[1], node[2], 1);

    // g_printf("Number of nodes %ld\n", H->n);
    // g_printf("Number of neighbors of node %s: %ld\n", node[0]->label->str, node[0]->r);
    // graph_print(H);
    // graph_free(H);

    // /*
    //  * On stack
    //  */
    // g_printf("\nStack\n");
    // struct graph * J = graph_new();
    // struct node nd[3];
    // nd[0] = *(graph_node_add(J, "u", 10));
    // nd[1] = *(graph_node_add(J, "v", 20));
    // nd[2] = *(graph_node_add(J, "w", 15));
    // /* Why those didn't work */
    // graph_edge_add(J, &nd[0], &nd[1], 3);
    // graph_edge_add(J, &nd[0], &nd[2], 2);
    // graph_edge_add(J, &nd[1], &nd[2], 1);

    // g_printf("Number of nodes %ld\n", H->n);
    // g_printf("Number of neighbors of node %s: %ld\n", nd[0].label->str, nd[0].r);
    // graph_print(J);
    // graph_free(J);


    /*
     * On the heap 
     */
    // g_printf("\nHeap\n");
    // struct graph * I = graph_new();
    // struct node *ptr, *vertex = g_malloc_n(3, sizeof * vertex);
    // ptr = vertex;
    // ptr++ = graph_node_add(I, "u", 10);
    // ptr++ = graph_node_add(I, "v", 20);
    // ptr   = graph_node_add(I, "w", 15);
    // graph_edge_add(I, vertex[0], node[1], 3);
    // graph_edge_add(I, vertex[0], node[2], 2);
    // graph_edge_add(I, vertex[1], node[2], 1);

    // g_printf("Number of nodes %ld\n", I->n);
    // g_printf("Number of neighbors of node %s: %ld\n", vertex[0]->label->str, vertex[0]->r);
    // graph_print(I);
    // graph_free(I);

