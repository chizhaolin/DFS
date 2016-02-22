#ifndef _bfs_h
#define _bfs_h

typedef struct node t_node;
struct node{
    char vertex;
    t_node* next;
};

typedef struct node t_list;

typedef struct adjlist{
    int size;
    t_list** list;
}t_adjlist;

#endif