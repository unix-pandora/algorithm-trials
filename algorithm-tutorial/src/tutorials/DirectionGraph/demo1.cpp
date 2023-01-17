#include "../../headers/refer.h"

#define NodesLimit 20

typedef struct Arc_Nodes {
    int vexIndex;
    struct Arc_Nodes *nextArc;
} *arcNodes;

typedef struct Vertex_Nodes {
    char vertexName;
    arcNodes firstArc;
} VertexNodes, *vertexsNodes;

typedef struct Direct_Graph {
    int vertexQuantity;
    int arcQuantity;
    vertexsNodes vexEleArr[NodesLimit];
} *DirectGraphPtr, DirectGraph;

void ergodicTheGraph(DirectGraphPtr g);

DirectGraphPtr InitializationGraph(char vex_arr[], char vexLength, char arc_arr[][2], int arcLength);

int getNodePosition(DirectGraphPtr g, char name);

DirectGraphPtr InitializationGraph(char vex_arr[], char vexLength, char arc_arr[][2], int arcLength) {
    char startNodeName, endNodeName;
    int startNodePosition, endNodePosition;

    arcNodes a1;
    arcNodes tempArcNode;

    DirectGraphPtr g = new Direct_Graph();
    g->vertexQuantity = vexLength;
    g->arcQuantity = arcLength;

    //vertex
    for (int i = 0; i < g->vertexQuantity; i++) {
        g->vexEleArr[i] = new VertexNodes();
        g->vexEleArr[i]->firstArc = NULL;
        g->vexEleArr[i]->vertexName = vex_arr[i];
    }

    for (int i = 0; i < g->arcQuantity; i++) {
        startNodeName = arc_arr[i][0];
        endNodeName = arc_arr[i][1];

        startNodePosition = getNodePosition(g, startNodeName);
        endNodePosition = getNodePosition(g, endNodeName);

        a1 = new Arc_Nodes();
        a1->vexIndex = endNodePosition;
        a1->nextArc = NULL;

        if (g->vexEleArr[startNodePosition]->firstArc == NULL) {
            g->vexEleArr[startNodePosition]->firstArc = a1;
        } else {
            tempArcNode = g->vexEleArr[startNodePosition]->firstArc;

            while (tempArcNode->nextArc != NULL) {
                tempArcNode = tempArcNode->nextArc;
            }
            tempArcNode->nextArc = a1;
        }
    }

    return g;
}

int getNodePosition(DirectGraphPtr g, char name) {
    for (int i = 0; i < g->vertexQuantity; i++) {
        if (g->vexEleArr[i]->vertexName == name) {
            return i;
        }
    }

    return -1;
}

void ergodicTheGraph(DirectGraphPtr g) {
    arcNodes t1;
    for (int i = 0; i < g->vertexQuantity; i++) {
        t1 = g->vexEleArr[i]->firstArc;
        cout << g->vexEleArr[i]->vertexName << " -> ";

        while (t1) {
            cout << "[";
            cout << t1->vexIndex << "_" << g->vexEleArr[t1->vexIndex]->vertexName;
            cout << "]";
            t1 = t1->nextArc;
        }
        cout << endl;
    }
}

void executeDemo1() {
    DirectGraphPtr g;
    char vexsArray[] = {'A', 'B', 'C', 'D'};

    // algorithm-tutorial/images/strongly-connect-component-1.png
    char arcsArray[][2] = {
            {'A', 'B'},
            {'B', 'C'},
            {'C', 'A'},
            {'D', 'B'},
            {'D', 'C'}
    };

    int vertexSize = sizeof(vexsArray) / sizeof(vexsArray[0]);
    int arcSize = sizeof(arcsArray) / sizeof((arcsArray[0]));

    g = InitializationGraph(vexsArray, vertexSize, arcsArray, arcSize);
    ergodicTheGraph(g);
}