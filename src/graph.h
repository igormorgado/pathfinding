#ifndef __GRAPH_H__
#define __GRAPH_H__

#include <glib.h>
#include <glib/gprintf.h>

struct graph
{
    GHashTable  *nodes;         // A list of nodes in graph
    gsize n;                    // number of nodes;
};

struct node
{
    GPtrArray   *neighbors;     // A list of all adjacent nodes
    gint         weight;        // Node weight
    GString     *label;         // Node label
};

struct neighbor
{
    struct node *dst;           // The node that is pointed too
    gint         weight;        // Edge SRC->DST weight
};


/* Creation functions */
struct graph     *graph_new                     (void);
struct node      *graph_node_add                (struct graph       *graph, 
                                                 gchar              *label, 
                                                 gint                weight);

void              graph_edge_add                (struct graph       *graph, 
                                                 struct node        *src,
                                                 struct node        *dst,
                                                 gint                weight);

void              graph_edge_add_by_label       (struct graph       *graph, 
                                                 gchar              *src, 
                                                 gchar              *dst, 
                                                 gint                weight);

/* Manipulation functions */
struct node      *graph_node                    (struct graph       *graph, 
                                                 gchar              *label);

/* Print functions */
void              graph_print                   (struct graph       *graph);

void              graph_node_print              (gpointer            key, 
                                                 struct node        *value,
                                                 gpointer            user_data);

void              graph_neighbors_print         (struct neighbor    *n,
                                                 gpointer            user_data);

/* Free functions */
void              graph_free                    (struct graph       *g);

void              graph_node_neighbor_destroyed (gpointer            n);

void              graph_node_value_destroyed    (gpointer            value);

#endif /* __GRAPH_H__ */
