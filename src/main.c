#include "main.h"

gint
main(gint   argc,
     gchar *argv[])
{
    gchar alabel[]= "a";
    gchar cclabel[4];

    sprintf(cclabel, "%c%c%c", 99,99,99);

    struct graph *G = graph_new();
    struct node *a = graph_node_add(G, alabel, 10);
    struct node *b = graph_node_add(G, "b", 20);
    struct node *c = graph_node_add(G, "c", 30);
    struct node *ccc = graph_node_add(G, cclabel, 40);
    graph_edge_add(G, a, b, 2);
    graph_edge_add(G, b, c, 6);
    graph_edge_add_by_label(G, alabel, "c", 4);
    graph_edge_add_by_label(G, alabel, cclabel, 1);
    graph_edge_add_by_label(G, cclabel,alabel, 13);
    graph_print(G);
    graph_free(G);
    return 0;
}
