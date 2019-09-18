#include "graph.h"

void
graph_free (struct graph *g)
{
    g_hash_table_remove_all(g->nodes);
    g_hash_table_destroy(g->nodes);
    g_free(g);
}


void
graph_node_value_destroyed (gpointer value)
{
    if (((struct node*)value)->edges) 
        g_ptr_array_unref (((struct node*)value)->edges);
    g_string_free (((struct node*)value)->label, TRUE);
    g_free ((struct node*)value);
}


void 
graph_node_edge_destroyed(gpointer n)
{
    g_free(n);
}


struct graph *
graph_new(void)
{
    struct graph * g = g_new(struct graph, 1);
    g->nodes = g_hash_table_new_full(
            g_str_hash, g_str_equal,
            NULL, (GDestroyNotify)graph_node_value_destroyed);
    return g;
}


struct node *
graph_node_add(struct graph *graph,
               gchar        *label,
               gint          weight)
{
    struct node * n = g_new(struct node, 1);
    n->edges = g_ptr_array_new_full(1, (GDestroyNotify)graph_node_edge_destroyed);
    n->weight = weight;
    n->label = g_string_new(label);
    g_hash_table_insert(graph->nodes, label, n);
    return n;
}


void
graph_edge_add(struct graph *graph, 
               struct node  *src,
               struct node  *dst, 
               gint          weight)
{
    struct edge * n = g_new(struct edge, 1);
    n->dst = dst;
    n->weight = weight;
    g_ptr_array_add(src->edges, n);
}


struct node *
graph_node(struct graph *graph,
           gchar        *label)
{
    return g_hash_table_lookup(graph->nodes, label);
}


void 
graph_edge_add_by_label(struct graph *graph,
                        gchar        *lsrc, 
                        gchar        *ldst, 
                        gint          weight)
{
    graph_edge_add(graph, 
                   graph_node(graph, lsrc), 
                   graph_node(graph, ldst), 
                   weight);
}


void 
graph_edges_print(struct edge  *n, 
                      gpointer          user_data)
{
    g_printf("%s(%d), ", n->dst->label->str, n->weight);
}


void
graph_node_print(gpointer       key,
                 struct node   *value, 
                 gpointer       user_data)
{
    g_printf("%s(%d) -> ", (gchar*)key, value->weight);
    g_ptr_array_foreach(value->edges, (GFunc)graph_edges_print, NULL);
    g_printf("\n");
}


void graph_print(struct graph *graph)
{
    g_hash_table_foreach(graph->nodes, (GHFunc)graph_node_print, NULL);
}

