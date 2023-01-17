#include "../../headers/refer.h"

#define INFINITE 999
#define VEX_UP_LIMIT 100
#define MAX_COUNT 50
#define REGULAR_LENGTH 20
#define LOSE_OUT -1

typedef struct EdgeInformation {
    char vertex, vertex1;
    int weight;
} *edgeInfo, edge_structor;

typedef struct AML {
    char *vertexsArray;

    //origin edge-relationship data
    edgeInfo edgeGather;

    //edge-relationship after process
    int vertexMatrix[VEX_UP_LIMIT][VEX_UP_LIMIT];

    int vexQuanity, edgeQuanity;
} AdjacencyMartixList;

void displayAdjList(AdjacencyMartixList g);

int getElementIndex(AdjacencyMartixList g, char element);

void createAMList(AdjacencyMartixList &g);

void dijkstraFormer(AdjacencyMartixList g, int start);

void search_path(AdjacencyMartixList g, int *prePathsArr, int start, int destinationNode);

void previousFindPath(AdjacencyMartixList g, int index, int start);

void displayShortestPath(AdjacencyMartixList g, int start);

//是否已存入最短路线中(1:T,0:F)
int checkJoin[MAX_COUNT];

//起点至此顶点之距离
int dists[MAX_COUNT];

//表示此顶点的前驱顶点
int pathPrevious[MAX_COUNT];

void dijkstraFormer(AdjacencyMartixList g, int start) {
    int leastDistance, tmp;

    for (int i = 0; i < g.vexQuanity; i++) {
        checkJoin[i] = 0;
        dists[i] = g.vertexMatrix[start][i];

        if (g.vertexMatrix[start][i] < INFINITE) {
            pathPrevious[i] = start;
        } else {
            pathPrevious[i] = LOSE_OUT;
        }
    }

    checkJoin[start] = 1;
    pathPrevious[start] = 0;

    for (int i = 0; i < g.vexQuanity; i++) {
        leastDistance = INFINITE;

        for (int j = 0; j < g.vexQuanity; j++) {//选取不在 checkJoin 数组,且具有最短路径的邻接顶点tmp
            if ((checkJoin[j] == 0) && (dists[j] < leastDistance)) {
                leastDistance = dists[j];
                tmp = j;
            }
        }

        checkJoin[tmp] = 1;

        for (int j = 0; j < g.vexQuanity; j++) {
            if (checkJoin[j] == 0) {
                if ((g.vertexMatrix[tmp][j] < INFINITE) && (dists[tmp] + g.vertexMatrix[tmp][j] < dists[j])) {
                    dists[j] = dists[tmp] + g.vertexMatrix[tmp][j];
                    pathPrevious[j] = tmp;
                }
            }
        }
    }
//    displayShortestPath(g, start);
}

void displayShortestPath(AdjacencyMartixList g, int start) {
    for (int i = 0; i < g.vexQuanity; i++) {
        if (checkJoin[i] == 1) {
            cout << g.vertexsArray[start] << " To " << g.vertexsArray[i] << " shortest path is: " << dists[i] << endl;
            cout << "beginning node: " << g.vertexsArray[start] << endl;
            cout << "destination node: " << g.vertexsArray[i] << endl;

            cout << g.vertexsArray[start] << "--";
            previousFindPath(g, i, start);
            cout << "--" << g.vertexsArray[i] << endl;
            cout << endl;
        } else {
            cout << "between " << g.vertexsArray[start] << " to " << g.vertexsArray[i]
                 << " is not exist the connect path" << endl;
        }
    }
}

//向前递归查找路径上之顶点,但不包含起点与终点的路径值
void previousFindPath(AdjacencyMartixList g, int index, int start) {
    int k;
    k = pathPrevious[index];

    if (k == start) {
        return;
    }

    previousFindPath(g, k, start);

    cout << g.vertexsArray[k] << "--";
}

void search_path(AdjacencyMartixList g, int *prePathsArr, int start, int destinationNode) {
    int ques[MAX_COUNT];
    int tot = 1, siteIdx;
    int tmp = prePathsArr[destinationNode];
    char site;

    ques[tot] = destinationNode;
    tot++;

    while (tmp != start) {
        ques[tot] = tmp;
        tot++;
        tmp = prePathsArr[tmp];
    }

    ques[tot] = start;

    cout << "beginning: " << g.vertexsArray[start] << endl;
    cout << "destination: " << g.vertexsArray[destinationNode] << endl;
    cout << "shortest route length:  " << dists[destinationNode] << endl;
    cout << "the shortest route plan:  ";

    for (int i = tot; i >= 1; i--) {
        siteIdx = ques[i];
        site = g.vertexsArray[siteIdx];

        if (i != 1) {
            cout << site << "-->";
        } else {
            cout << site << endl;
        }
    }
}

int getElementIndex(AdjacencyMartixList g, char element) {
    for (int i = 0; i < g.vexQuanity; i++) {
        if (element == g.vertexsArray[i]) {
            return i;
        }
    }
    return LOSE_OUT;
}

void createAMList(AdjacencyMartixList &g) {
    char x, y;
    int index, index2, weight;

    for (int i = 0; i < g.vexQuanity; ++i) {
        for (int j = 0; j < g.vexQuanity; ++j) {
            g.vertexMatrix[i][j] = INFINITE;
        }
    }

    for (int i = 0; i < g.edgeQuanity; ++i) {
        x = g.edgeGather[i].vertex;
        y = g.edgeGather[i].vertex1;
        weight = g.edgeGather[i].weight;

        index = getElementIndex(g, x);
        index2 = getElementIndex(g, y);

        if (index != LOSE_OUT && index2 != LOSE_OUT) {
            g.vertexMatrix[index][index2] = g.vertexMatrix[index2][index] = weight;
        }
    }
}

void displayAdjList(AdjacencyMartixList g) {
    int position;
    for (int i = 0; i < g.vexQuanity; ++i) {
        cout << "   " << g.vertexsArray[i];
    }
    cout << endl;

    for (int i = 0; i < g.vexQuanity; ++i) {
        cout << g.vertexsArray[i] << ": ";

        for (int j = 0; j < g.vexQuanity; ++j) {
            position = g.vertexMatrix[i][j];

            if (position == INFINITE) {
                cout << position << " ";
            } else {
                cout << position << "   ";
            }
        }
        cout << endl;
    }
}

void executeTest4() {
    AdjacencyMartixList g;
    char vexs_chars[] = {'a', 'b', 'c', 'd', 'e', 'f'};

    // algorithm-tutorial/images/plat-2.png
    edge_structor edges[] = {
            {.vertex=vexs_chars[0], .vertex1=vexs_chars[1], .weight=7},
            {.vertex=vexs_chars[0], .vertex1=vexs_chars[2], .weight=5},
            {.vertex=vexs_chars[0], .vertex1=vexs_chars[3], .weight=1},
            {.vertex=vexs_chars[1], .vertex1=vexs_chars[2], .weight=1},
            {.vertex=vexs_chars[1], .vertex1=vexs_chars[5], .weight=2},
            {.vertex=vexs_chars[2], .vertex1=vexs_chars[4], .weight=1},
            {.vertex=vexs_chars[3], .vertex1=vexs_chars[4], .weight=3},
            {.vertex=vexs_chars[4], .vertex1=vexs_chars[5], .weight=1},
    };

    g.vexQuanity = sizeof(vexs_chars) / sizeof(vexs_chars[0]);
    g.edgeQuanity = sizeof(edges) / sizeof(edges[0]);

    g.vertexsArray = vexs_chars;
    g.edgeGather = edges;

    createAMList(g);
    displayAdjList(g);

    cout << endl;
    dijkstraFormer(g, 0);

    search_path(g, pathPrevious, 0, 4);
}
