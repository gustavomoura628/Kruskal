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
void LinkedList_GetDataOfFirst(LinkedList * ll, int * u,int * v,double * w){
        *u = ll->next->u;
        *v = ll->next->v;
        *w = ll->next->weight;
}

int main(){
    char buffer[1000];
    int NumberOfVertices;
    printf("Insira o número de vértices: ");
    fgets(buffer,1000,stdin);
    sscanf(buffer,"%d",&NumberOfVertices);
    //printf("NumberOfVertices = %d\n", NumberOfVertices);
    
    //Inicializa os vertices do grafo com MakeSet
    Node ** UnionArray = (Node**)malloc(NumberOfVertices * sizeof(Node*));
    int i;
    for(i=0;i<NumberOfVertices;i++){
        UnionArray[i] = MakeSet();
    }

    int NumberOfEdges;
    printf("Insira o número de arestas: ");
    fgets(buffer,1000,stdin);
    sscanf(buffer,"%d",&NumberOfEdges);
    //printf("NumberOfEdges = %d\n", NumberOfEdges);

    //Cria a linked list que recebe as arestas
    LinkedList * GEdges = LinkedList_Create(0,0,0);
    printf("Insira as arestas no formato 'u v peso': \n");
    for(i=0;i<NumberOfEdges;i++){
        int u,v;
        double w;
        
        fgets(buffer,1000,stdin);
        sscanf(buffer,"%d %d %lf",&u,&v,&w);
        //printf("Read %d %d %lf\n",u,v,w);
        //Insere cada aresta ordenando por weight
        LinkedList_InsertSort(GEdges, LinkedList_Create(u,v,w));
        //printf("Inserted:\n");
        //LinkedList_Print(GEdges);
    }
    //Cria o conjunto de arestas F
    LinkedList * FEdges = LinkedList_Create(0,0,0);

    //Executa o algoritimo de Kruskal
    int u,v;
    double w;
    while(!LinkedList_isEmpty(GEdges)){
        LinkedList_GetDataOfFirst(GEdges,&u,&v,&w);
        if(FindSet(UnionArray[u]) != FindSet(UnionArray[v])){
            LinkedList_Insert(FEdges, LinkedList_Create(u,v,w));
            Union(UnionArray[u],UnionArray[v]);
        }
        LinkedList_RemoveFirst(GEdges);
    }

    printf("Árvore de extensão mínima:\n");
    LinkedList_Print(FEdges);
}
