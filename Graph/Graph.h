#ifndef GRAPH_GRAPH_H
#define GRAPH_GRAPH_H

#endif //GRAPH_GRAPH_H

const int MAXGRAPHSIZE = 25;

template <class T>
class Graph
{
private:
    // основные данные включают список вершин, матрицу смежности
    // и текущий размер (число вершин) графа
    SeqList<T> vertexList;
    int edge[MAXGRAPHSIZE];
    int graphsize;

    // методы для поиска вершины и указания ее позиции в списке
    int findVertex(SeqList<T> &L)
};