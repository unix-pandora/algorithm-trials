#include "../../headers/refer.h"

/* adjacency list: undirect graph */

#define MAX 100

class ListUDG {
private:
    class EdgeNode {
    public:
        int vertex; // this edge pointing to which one vertex
        EdgeNode *nextEdge;
    };

    class VertexNode {
    public:
        char data;
        EdgeNode *firstEdge; // the first edge of pointing to this vertex
    };

private:
    int vertexNum;
    int edgeNum;
    VertexNode vertexs[MAX];

public:
    ListUDG();

    // create a undirect graph(modality of adjancency list)
    ListUDG(char vertexArr[], int vertexLen, char edgeArr[][2], int edgeLen);

    ~ListUDG();

    void ergodicList();

private:
    char readAnChar();

    int getCharPosition(char ch);

    void insertNode2ListLast(EdgeNode *list, EdgeNode *node);
};

int ListUDG::getCharPosition(char ch) {
    int i;
    for (i = 0; i < vertexNum; i++) {
        if (vertexs[i].data == ch) {
            return i;
        }
    }
    return -1;
}

void ListUDG::ergodicList() {
    EdgeNode *node;

    for (int i = 0; i < vertexNum; i++) {
        cout << i << "( " << vertexs[i].data << " ) ";
        node = vertexs[i].firstEdge;

        while (node != NULL) {
            cout << node->vertex << "( " << vertexs[node->vertex].data << " ) ";
            node = node->nextEdge;
        }
        cout << endl;
    }
}

void ListUDG::insertNode2ListLast(EdgeNode *list, EdgeNode *node) {
    EdgeNode *p = list;
    while (p->nextEdge) {
        p = p->nextEdge;
    }
    p->nextEdge = node;
}

ListUDG::ListUDG(char vertexArr[], int vertexLen, char edgeArr[][2], int edgeLen) {
    int i;
    char c1, c2;
    int pos, pos2;

    EdgeNode *node, *node2;

    vertexNum = vertexLen;
    edgeNum = edgeLen;

    //set up the vertexs in graph
    for (i = 0; i < vertexNum; i++) {
        vertexs[i].data = vertexArr[i];
        vertexs[i].firstEdge = NULL;
    }

    //use edge connect the vertexs
    for (i = 0; i < edgeNum; i++) {
        c1 = edgeArr[i][0];
        c2 = edgeArr[i][1];

        pos = getCharPosition(c1);
        pos2 = getCharPosition(c2);

        node = new EdgeNode();
        node->vertex = pos2;

        // initialize node
        if (vertexs[pos].firstEdge == NULL) {
            vertexs[pos].firstEdge = node;
        } else {
            insertNode2ListLast(vertexs[pos].firstEdge, node);
        }

        // initialize node2
        node2 = new EdgeNode();
        node2->vertex = pos;

        if (vertexs[pos2].firstEdge == NULL) {
            vertexs[pos2].firstEdge = node2;
        } else {
            insertNode2ListLast(vertexs[pos2].firstEdge, node2);
        }
    }
}

void generateUDG() {
    char vertexDatas[] = {'A', 'B', 'C', 'D', 'E', 'F', 'G'};

    char edgeDatas[][2] = {
            {'A', 'C'},
            {'A', 'D'},
            {'A', 'F'},
            {'B', 'C'},
            {'C', 'D'},
            {'E', 'G'},
            {'F', 'G'}};

    int vertexLength = sizeof(vertexDatas) / sizeof(vertexDatas[0]);
    int edgeLength = sizeof(edgeDatas) / sizeof(edgeDatas[0]);

    ListUDG *g;
    g = new ListUDG(vertexDatas, vertexLength, edgeDatas, edgeLength);

    g->ergodicList();
}

void executeCase1() {
    generateUDG();
}