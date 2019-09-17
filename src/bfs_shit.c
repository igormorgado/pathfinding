#include <glib.h>
#include "graph.h"

#define ROWS 4
#define COLS 9

/*
 *    a  b  c  d  e  f  g  h  i
 * a aa ab ac ad ae af ag ah ai 
 * b ba bb bc bd be bf bg bh bi
 * c ca cb cc cd ce cf cg ch ci 
 * d da db dc dd de df dg dh di
 */

int 
main (int argc,
      char *argv[]) 
{

    gchar center[3], north[3], south[3], west[3], east[3];
    struct graph *map = graph_new();

    /* Create nodes */
    for(int i=0; i<ROWS; i++) {
        for(int j=0; j<COLS; j++) {
            sprintf(center, "%c%c", i+97, j+97);
            graph_node_add(map, center, COLS*i+j);
        }
    }

    /* Create edges */
    for(int i=1; i<3; i++) {
        for(int j=1; j<8; j++) {
            sprintf(center, "%c%c", i+97,   j+97);
            sprintf(north,  "%c%c", i+97-1, j+97);
            sprintf(south,  "%c%c", i+97+1, j+97);
            sprintf(west,   "%c%c", i+97,   j+97-1);
            sprintf(east,   "%c%c", i+97,   j+97+1);
            graph_edge_add_by_label(map, center, north, 1);
            graph_edge_add_by_label(map, center, south, 2);
            graph_edge_add_by_label(map, center, west,  3);
            graph_edge_add_by_label(map, center, east,  4);
            printf("N: %s->%s(%d) ", center, north, 1);
            printf("S: %s->%s(%d) ", center, south, 2);
            printf("W: %s->%s(%d) ", center, west,  3);
            printf("E: %s->%s(%d) ", center, east,  4);
            printf("\n");
        }
        printf("\n");
    }
    // graph_print(map);
    struct node *n = g_hash_table_lookup(map->nodes, center);
    printf("%s(%d)\n", n->label->str, n->weight);
    printf("Hash table size %d\n", g_hash_table_size(map->nodes));
    printf("Gptrarray len %d\n", n->neighbors->len);
    struct GPtrArray *p = g_ptr_array_index(n->neighbors, 1);
    struct neighbor *neigh = p->pdata;
    printf("%s(%d)\n", neigh->dst->label->str, neigh->weight);

    graph_free(map);
}
