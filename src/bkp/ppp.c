#include <glib.h>
#include <glib/gprintf.h>

struct graph
{
    GArray * nodes;
};

struct node
{
    GArray * neighbors;
    gint weight;
    GString * label;
};

struct neighbor
{
    struct node * dst;
    gint weight;
};

struct graph * graph_new(void);
void graph_node_add(struct graph * graph, const gchar * label, gint weight);
void graph_edge_add(struct graph * graph, struct node * src, struct node * dst, gint weight);

struct graph * graph_new(void)
{
    struct graph * g = g_new(struct graph, 1);
    g->nodes = g_array_new (FALSE, FALSE, sizeof (struct node));
    return g;
}

void graph_node_add(struct graph * graph, const gchar * label, gint weight)
{
    struct node * node = g_new(struct node, 1);
    node->neighbors = g_array_new(FALSE, FALSE, sizeof (struct neighbor));
    node->label = g_string_new(label);
    node->weight = weight;
    graph->nodes = g_array_append_val(graph->nodes, node);
}

void graph_edge_add(struct graph *graph, struct node *src, struct node *dst, gint weight)
{
    struct neighbor * neighbor = g_new(struct neighbor, 1);
    neighbor->dst = dst;
    neighbor->weight = weight;
    src->neighbors = g_array_append_val(src->neighbors, neighbor);
}


int main(void)
{
    struct graph * G = graph_new();
    graph_node_add(G, "u", 10);
    graph_node_add(G, "v", 20);
    graph_node_add(G, "w", 15);

    struct node * n = &g_array_index(G->nodes, struct node, 0);
    g_printf("segfaulting here\n");
    char * s = n->label->str;
    g_printf("LABEL %s\n", s);

    return(0);
}

