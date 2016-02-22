#include <stdio.h>
#include <malloc.h>
#include <stdarg.h>
#include "dfs.h"

#define isEmpty(node) (node == NULL)
#define NUM_VERTEX  26

// Use the linked list to store the path through DFS
t_list* g_path;

t_node* createNode(char vertex)
{
    t_node* pNode = NULL;

    pNode = (t_node*)malloc(sizeof(t_node));
    if (pNode) {
        pNode->vertex = vertex;
        pNode->next = NULL;
    }

    return pNode;
}

t_list* addList(t_list* list, t_node* node)
{
    t_list* pTmp;

    if (isEmpty(list))
        return node;

    pTmp = list;
    while (pTmp->next) 
        pTmp = pTmp->next;

    pTmp->next = node;

    return list;
}

void destroyList(t_list** list)
{
    t_node* pDel;

    while (*list) {
        pDel = *list;
        *list = (*list)->next;
        free(pDel);
        pDel = NULL;
    }
}

// Create empty adjacent list
t_adjlist* createAdjList()
{
    t_adjlist* pAdjList = NULL;

    pAdjList = (t_adjlist*)malloc(sizeof(t_adjlist));

    if (!isEmpty(pAdjList)) {
        pAdjList->size = NUM_VERTEX;
        pAdjList->list = (t_list**)malloc(sizeof(t_list*) * NUM_VERTEX);
        if (!isEmpty(pAdjList->list)) {
            int i;
            for (i = 0; i < NUM_VERTEX; i++) {
                pAdjList->list[i] = NULL;
            }
        }
    }

    return pAdjList;
}

// Add edge between 2 vertex
void addEdge(t_adjlist* pAdjList, char V, char E)
{
    int index;

    index = V - 'A';

    pAdjList->list[index] = addList(pAdjList->list[index], createNode(E));
}

// Check if the vertex is exist in the linkded list
int isVertexExist(t_list* list, char vertex)
{
    while (list) {
        if (list->vertex == vertex)
            return 1;
        list = list->next;
    }

    return 0;
}

/*
 * Variable arguments meaning:
 * 1. One argument: meaning DFS from this vertex
 * 2. Two arguments: meaning find the path from argument 1 to argument 2.
 */
#if 0
dfs(t_adjlist* pAdjList, char V)
{
    t_list* pSearchedList;

    g_path = addList(g_path, createNode(V));

    pSearchedList = pAdjList->list[V - 'A'];
    pSearchedList = pSearchedList->next;

    while (!isEmpty(pSearchedList)) {
        if (!isVertixExist(g_path, pSearchedList->data))
            dfs(pAdjList, pSearchedList->data);
        
        pSearchedList = pSearchedList->next;
    }
}
#endif
int dfs(t_adjlist* pAdjList, int numV, ...)
{
    t_list* pSearchedList;
    va_list valist;
    char startV, endV;

    if (numV > 2 || numV < 1) {
        printf("Incorrect number of arguments for the function \"dfs\"\n");
        return 0;
    }

    va_start(valist, numV);
    if (numV == 1) {
        startV = va_arg(valist, char);
    }
    else {
        startV = va_arg(valist, char);
        endV = va_arg(valist, char);
        if (startV == endV) {
            return 1;
        }
    }
    va_end(valist);

    g_path = addList(g_path, createNode(startV));

    pSearchedList = pAdjList->list[startV - 'A'];
    pSearchedList = pSearchedList->next;

    while (!isEmpty(pSearchedList)) {
        if (!isVertexExist(g_path, pSearchedList->vertex)) {
            if (numV == 1) {
                dfs(pAdjList, 1, pSearchedList->vertex);
            }
            else {
                if (dfs(pAdjList, 2, pSearchedList->vertex, endV))
                    return 1;
            }
        }
        
        pSearchedList = pSearchedList->next;
    }

    if (numV == 2) 
        return 0;
}

// The other way to check if there is path between 2 vertices
int dfs_path(t_adjlist* pAdjList, char vStart, char vEnd)
{
    t_list* pSearchedList;

    g_path = addList(g_path, createNode(vStart));

    if (vStart == vEnd) {
        return 1;
    }

    pSearchedList = pAdjList->list[vStart - 'A'];
    pSearchedList = pSearchedList->next;

    while (!isEmpty(pSearchedList)) {
        if (!isVertexExist(g_path, pSearchedList->vertex))
            if (dfs_path(pAdjList, pSearchedList->vertex, vEnd))
                return 1;
        pSearchedList = pSearchedList->next;
    }

    return 0;
}

void print(t_list* list)
{
    while (list) {
        printf("%c ", list->vertex);
        list = list->next;
    }
    printf("\n");
}

int main() {
    t_adjlist* pAdjList;
    t_list* pPath = NULL;
    int iRet;
    int i;

    pAdjList = createAdjList();
    pAdjList->list[0]= addList(pAdjList->list[0], createNode('A'));
    pAdjList->list[1]= addList(pAdjList->list[1], createNode('B')); 
    pAdjList->list[2]= addList(pAdjList->list[2], createNode('C'));
    pAdjList->list[3]= addList(pAdjList->list[3], createNode('D'));
    pAdjList->list[4]= addList(pAdjList->list[4], createNode('E'));
    pAdjList->list[5]= addList(pAdjList->list[5], createNode('F'));
    pAdjList->list[6]= addList(pAdjList->list[6], createNode('G'));
    pAdjList->list[7]= addList(pAdjList->list[7], createNode('H'));

    addEdge(pAdjList, 'A', 'B');
    addEdge(pAdjList, 'B', 'C');
    addEdge(pAdjList, 'B', 'E');
    addEdge(pAdjList, 'B', 'F');
    addEdge(pAdjList, 'B', 'H');
    addEdge(pAdjList, 'C', 'E');
    addEdge(pAdjList, 'D', 'C');
    addEdge(pAdjList, 'E', 'B');
    addEdge(pAdjList, 'E', 'D');
    addEdge(pAdjList, 'F', 'G');

    printf("The adjacent list of the directed graph is: \n");
    for (i = 0; i < 8; i++) {
        print(pAdjList->list[i]);
    }
    printf("\n\n");

    iRet = dfs(pAdjList, 1, 'A');
    if (iRet) {
        printf("The path from vertex 'A' of the directed graph is: ");
        print(g_path);
    }

    destroyList(&g_path);
    //iRet = dfs_path(pAdjList, 'A', 'G');
    iRet = dfs(pAdjList, 2, 'A', 'G');
    if (iRet) {
        printf("The path from 'A' to 'G' is: ");
        print(g_path);
    }
    else {
        printf("No path from 'A' to 'G'\n");
    }
    
    destroyList(&g_path);
    //iRet = dfs_path(pAdjList, 'C', 'H');
    iRet = dfs(pAdjList, 2, 'C', 'H');
    if (iRet) {
        printf("The path from 'C' to 'H' is: ");
        print(g_path);
    }
    else {
        printf("No path from 'C' to 'H'\n");
    }

    destroyList(&g_path);
    //iRet = dfs_path(pAdjList, 'F', 'H');
    iRet = dfs(pAdjList, 2, 'F', 'H');
    if (iRet) {
        printf("The path from 'F' to 'H' is: ");
        print(g_path);
    }
    else {
        printf("No path from 'F' to 'H'\n");
    }

    return 0;
}