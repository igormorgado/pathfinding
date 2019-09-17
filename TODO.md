# TODO

## Conversion functions

    gint * graph_to_matrix(struct graph *graph);
    struct graph * matrix_to_graph(gint *matrix, gint order);

## Graph manipulation function
    gint * graph_node_weight(graph *graph, struct node *node);
    void graph_node_weight_set(graph *graph, struct node *node, gint weight);

    gint * graph_edge_weight(struct graph *graph, struct node *src, struct *dst);
    void graph_edge_weight_set(struct graph *graph, struct node *src, struct *dst, gint weight);

    graph_node_remove(struct graph* graph, struct node *node);
    graph_edge_remove(struct graph* graph, struct node *src, struct node *dst);

And respective `by_label` functions.

## Graph constructors

    Create a function to construct a graph from a adjacency structure as:

    '''
    struct graph *G = graph_new()
    graph_fill_edges(G, 
                     {
                       {"A", "B", 1}, 
                       {"A", "C", 5}, 
                       {"B", "D", 7}
                     }) 
    '''

    or maybe isn't that a good idea

