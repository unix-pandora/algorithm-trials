#include "../../headers/refer.h"

/* create one adjacenency martix */

#define MAX_VERTEX_LIMIT 100
#define DISCONTINUE 999
#define NEGATIVE_NUMBER -1

typedef struct EDGE_DATA {
    char vex, vex2;
    int weightValue;
} edgeDatas, edgeDataArr[];

typedef struct {
    char *vertexs;
    int martixArray[MAX_VERTEX_LIMIT][MAX_VERTEX_LIMIT];
    int vexNum, edgeNum;
    edgeDatas *edges;
} AdjacencyMartixGraphs;

void displays_paths(AdjacencyMartixGraphs g, int dists[], int marks[], int previous_set[], int start);

void print_mid_paths(AdjacencyMartixGraphs g, int previous_set[], int i, int start);

void dijkstra_model(AdjacencyMartixGraphs g, int startIndex);

void printMartix(AdjacencyMartixGraphs g);

int getVexIndex(AdjacencyMartixGraphs &g, int vertex);

int getVexIndex(AdjacencyMartixGraphs &g, int vertex) {
    for (int i = 0; i < g.vexNum; ++i) {
        if (g.vertexs[i] == vertex) {
            return i;
        }
    }
    return NEGATIVE_NUMBER;
}

void printMartix(AdjacencyMartixGraphs g) {
    for (int n = 0; n < g.vexNum; ++n) {
        cout << "   " << g.vertexs[n];
    }
    cout << endl;

    for (int i = 0; i < g.vexNum; ++i) {
        cout << g.vertexs[i] << "  ";

        for (int j = 0; j < g.vexNum; ++j) {
            if (g.martixArray[i][j] == DISCONTINUE) {
                cout << DISCONTINUE << " ";
            } else {
                cout << g.martixArray[i][j] << "   ";
            }
        }
        cout << endl;
    }
}

void buildAdjacencyMartix(AdjacencyMartixGraphs &g) {
    int pos, pos2;
    int v, v2, weight;

    for (int i = 0; i < g.vexNum; ++i) {
        for (int j = 0; j < g.vexNum; ++j) {
            g.martixArray[i][j] = DISCONTINUE;
        }
    }

    for (int k = 0; k < g.edgeNum; ++k) {
        v = g.edges[k].vex;
        v2 = g.edges[k].vex2;
        weight = g.edges[k].weightValue;

        pos = getVexIndex(g, v);
        pos2 = getVexIndex(g, v2);

        if (pos != NEGATIVE_NUMBER && pos2 != NEGATIVE_NUMBER) {
            // "g.e[x][y] = g.e[y][x]" means un-directs, if just "g.e[x][y]" that mean had directs
            g.martixArray[pos][pos2] = g.martixArray[pos2][pos] = weight;
        }
    }
}

void dijkstra_model(AdjacencyMartixGraphs g, int startIndex) {
    int min_dist, t;

    //marks[i]=0表示顶点i未加入最短路线,marks[i]=1表示已经加入
    int marks[MAX_VERTEX_LIMIT];

    //起点 至 顶点i 的距离
    int dists[MAX_VERTEX_LIMIT];

    // 表示 顶点i 的前驱节点
    int previous_set[MAX_VERTEX_LIMIT];

    for (int i = 0; i < g.vexNum; i++) {
        marks[i] = 0;
        dists[i] = g.martixArray[startIndex][i];

        if (g.martixArray[startIndex][i] < DISCONTINUE) {
            previous_set[i] = startIndex;
        } else {
            previous_set[i] = NEGATIVE_NUMBER;
        }
    }

    marks[startIndex] = 1;
    previous_set[startIndex] = 0;

    for (int i = 0; i < g.vexNum; i++) {
        min_dist = DISCONTINUE;

        for (int j = 0; j < g.vexNum; j++) {//选取不在marks中,且具有最短路径的顶点t
            if (marks[j] == 0 && dists[j] < min_dist) {
                min_dist = dists[j];
                t = j;
            }
        }

        marks[t] = 1;

        for (int j = 0; j < g.vexNum; j++) {
            if (marks[j] == 0) {
                if (g.martixArray[t][j] < DISCONTINUE && dists[t] + g.martixArray[t][j] < dists[j]) {
                    dists[j] = dists[t] + g.martixArray[t][j];
                    previous_set[j] = t;
                }
            }
        }
    }

    displays_paths(g, dists, marks, previous_set, startIndex);
}

void displays_paths(AdjacencyMartixGraphs g, int dists[], int marks[], int previous_set[], int start) {
    for (int i; i < g.vexNum; i++) {
        if (marks[i] == 1) {
            cout << endl;
            cout << "shortest path design: " << g.vertexs[start] << "-->" << g.vertexs[i] << " : " << dists[i] << endl;
            cout << "start node: " << g.vertexs[start] << endl;
            cout << "destination: " << g.vertexs[i] << endl;

            //输出路径上的中间点
            print_mid_paths(g, previous_set, i, start);
        } else {
            cout << g.vertexs[start] << " to " << g.vertexs[i] << " path not exist" << endl;
        }
    }
}

/**
 * 向前递归寻找路径上的顶点,但不包含起点和终点的权值
 * @param g
 * @param previous_set
 * @param i
 * @param start
 */
void print_mid_paths(AdjacencyMartixGraphs g, int previous_set[], int i, int start) {
    int k = previous_set[i];

    if (k == start) {//无中间节点,退出
        return;
    }

    cout << " " << g.vertexs[k];
    print_mid_paths(g, previous_set, i, start);
}


void revovled() {
    AdjacencyMartixGraphs g;
    char vex_arr[] = {'a', 'b', 'c', 'd', 'e'};

    //algorithm-tutorial/images/plat-1.png
    edgeDataArr edges_data_arr = {
            {vex:'a', vex2: 'b', weightValue:5},
            {vex:'a', vex2: 'c', weightValue: 6},
            {vex:'a', vex2: 'd', weightValue: 2},
            {vex:'b', vex2: 'e', weightValue: 3},
            {vex:'c', vex2: 'e', weightValue: 4},
            {vex:'d', vex2: 'e', weightValue: 5}};

    g.vexNum = sizeof(vex_arr) / sizeof(vex_arr[0]);
    g.edgeNum = sizeof(edges_data_arr) / sizeof(edges_data_arr[0]);

    g.edges = edges_data_arr;
    g.vertexs = vex_arr;

    buildAdjacencyMartix(g);
    printMartix(g);

    dijkstra_model(g, 0);
}
