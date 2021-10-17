/* Input Format:    Number of Vertices
 *                  Number of Edges
 *                  u v weight
 */
#include <stdio.h>
#include <stdlib.h>

typedef struct node Node;
struct node{
    int rank;
    Node * p;
};

Node * MakeSet(){
    Node * node = (Node*)malloc(sizeof(Node));
    node->p=node;
    node->rank=0;
    return node;
}
Node * FindSet(Node * x){
    if (x->p != x)
        x->p = FindSet(x->p);
    return x->p;
}
void Link(Node * x, Node * y){
    if(x->rank > y->rank){
        y->p = x;
    }else{
        x->p = y;
        if(x->rank==y->rank)
            y->rank++;
    }

}
void Union(Node * x, Node * y){
    if(FindSet(x) != FindSet(y))
        Link(FindSet(x),FindSet(y));

}

typedef struct _LinkedList LinkedList;
struct _LinkedList{
    LinkedList * next;
    int u;
    int v;
    double weight;
};
LinkedList * LinkedList_Create(int u, int v, double weight){
    LinkedList * l = (LinkedList*)malloc(sizeof(LinkedList));
    l->next = NULL;
    l->u = u;
    l->v = v;
    l->weight = weight;
    return l;
}
void LinkedList_Insert(LinkedList * root, LinkedList * new){
    LinkedList * temp = root->next;
    root->next = new;
    new->next = temp;
}
void LinkedList_InsertSort(LinkedList * root, LinkedList * new){
    if(root->next == NULL){
        root->next = new;
    }else if(root->next->weight>new->weight){
        LinkedList * temp = root->next;
        root->next = new;
        new->next = temp;
    }else{
        LinkedList_InsertSort(root->next,new);
    }
}
void LinkedList_RemoveFirst(LinkedList * root){
    if(root->next == NULL)return;
    LinkedList * temp = root->next;
    root->next = root->next->next;
    free(temp);
}
int LinkedList_isEmpty(LinkedList * root){
    return root->next == NULL;
}
void LinkedList_Print(LinkedList * root){
    LinkedList * node = root->next;
    while(node != NULL){
        printf("(%d,%d) = %.2f\n",node->u,node->v,node->weight);
        node = node->next;
    }
}
int main(){
    char buffer[1000];
    int NumberOfVertices = 10;
    fgets(buffer,1000,stdin);
    sscanf(buffer,"%d",&NumberOfVertices);
    printf("NumberOfVertices = %d\n", NumberOfVertices);
    Node ** UnionArray = (Node**)malloc(NumberOfVertices * sizeof(Node*));
    int i;
    for(i=0;i<NumberOfVertices;i++){
        UnionArray[i] = MakeSet();
    }

    int NumberOfEdges = 5;
    fgets(buffer,1000,stdin);
    sscanf(buffer,"%d",&NumberOfEdges);
    printf("NumberOfEdges = %d\n", NumberOfEdges);
    LinkedList * GEdges = LinkedList_Create(0,0,0);
    for(i=0;i<NumberOfEdges;i++){
        int u,v;
        double w;

        fgets(buffer,1000,stdin);
        sscanf(buffer,"%d %d %lf",&u,&v,&w);
        printf("Read %d %d %lf\n",u,v,w);
        LinkedList_InsertSort(GEdges, LinkedList_Create(u,v,w));
        printf("Inserted:\n");
        LinkedList_Print(GEdges);
    }
    LinkedList * FEdges = LinkedList_Create(0,0,0);
    while(!LinkedList_isEmpty(GEdges)){
        int u = GEdges->next->u;
        int v = GEdges->next->v;
        int w = GEdges->next->weight;
        if(FindSet(UnionArray[u]) != FindSet(UnionArray[v])){
            LinkedList_Insert(FEdges, LinkedList_Create(u,v,w));
            Union(UnionArray[u],UnionArray[v]);
        }
        LinkedList_RemoveFirst(GEdges);
    }
    printf("Minimum Spanning Tree:\n");
    LinkedList_Print(FEdges);
}
//int main(){
//    int N;
//    int K;
//    scanf("%d %d", &N,&K);
//    int i;
//    Node ** banks = (Node**)malloc(N*sizeof(Node*));
//    int t;
//    for(i=0;i<N;i++){
//        scanf("%d",&t);
//        banks[i] = MakeSet();
//    }
//    int A,B;
//    char O;
//    char buffer[100];
//    for(i=0;i<K;i++){
//        fgets(buffer,100,stdin);
//        sscanf(buffer,"%c %d %d", &O, &A,&B);
//        //printf("O = %c, A = %d, B = %d\n",O,A,B);
//
//        A--;
//        B--;
//        if(O=='F'){
//            Union(banks[A],banks[B]);
//        }else if(O=='C'){
//            if(FindSet(banks[A])==FindSet(banks[B]))printf("S\n");
//            else printf("N\n");
//        }
//
//    }
//    for(i=0;i<N;i++){
//        free(banks[i]);
//    }
//    free(banks);
//    return 0;
//}
