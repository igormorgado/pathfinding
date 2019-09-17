#include "main.h"

gint
main(gint   argc,
     gchar *argv[])
{
    struct graph *G = graph_new();
    struct node *a = graph_node_add(G, "a", 10);
    struct node *b = graph_node_add(G, "b", 20);
    struct node *c = graph_node_add(G, "c", 30);
    graph_edge_add(G, a, b, 2);
    graph_edge_add_by_label(G, "a", "c", 4);
    graph_edge_add(G, b, c, 6);
    graph_print(G);
    graph_free(G);
    return 0;
}
