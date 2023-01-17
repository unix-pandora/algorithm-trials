#include "../../headers/refer.h"

#define MAX_SIZE 100
#define IMPOSSIBLE -1
#define LARGE_INT 1e7
#define ARRAY_LENGTH 50

//prevArray 前驱顶点数组,即:prev[i]的值是 起点 至 顶点i 的最短路径内,所经历的全部顶点中,位于 顶点i 之前的那个顶点
int prevArray[MAX_SIZE] = {};

//distanceArray 存放 起点 至 顶点i 的最短路径
int distanceArray[MAX_SIZE] = {};

//记录节点V_i 是否已经找到最短路径,true表示已经找到,false表示未找到
bool flag_signal[MAX_SIZE] = {};

typedef struct VertexRelation {
    string vertex, vertex2;
    int routeLength;
} edgesRelation;

typedef struct ADJACENCY_MATRIX_GRAPH {
    string *vexs;
    int adjacencyMatrix[MAX_SIZE][MAX_SIZE];
    int vertex_quantum, edge_quantum;
    edgesRelation *edges;
} graphStructor;

void string2charArray(string str, char *ch);

int getRegionPosition(graphStructor g, string venue);

void buildOneUnDirectGraph(graphStructor &g);

void showMartix(graphStructor g);

void dijkstraAlgorithm(graphStructor g, int srcVex);

void ergodicShortestPath(graphStructor g, int srcNode);

void buildOneUnDirectGraph(graphStructor &g) {
    int index, index2, weight;
    string vertex1, vertex2;

    for (int i = 0; i < g.vertex_quantum; ++i) {
        for (int j = 0; j < g.vertex_quantum; ++j) {
            g.adjacencyMatrix[i][j] = LARGE_INT;
        }
    }

    for (int k = 0; k < g.edge_quantum; ++k) {
        vertex1 = g.edges[k].vertex;
        vertex2 = g.edges[k].vertex2;
        weight = g.edges[k].routeLength;

        index = getRegionPosition(g, vertex1);
        index2 = getRegionPosition(g, vertex2);

        if (index != IMPOSSIBLE && index2 != IMPOSSIBLE) {
            g.adjacencyMatrix[index][index2] = g.adjacencyMatrix[index2][index] = weight;
        }
    }
}

void showMartix(graphStructor g) {
    for (int i = 0; i < g.vertex_quantum; ++i) {
        for (int j = 0; j < g.vertex_quantum; ++j) {
            cout << g.adjacencyMatrix[i][j] << " ";
        }
        cout << endl;
    }
}

int getRegionPosition(graphStructor g, string venue) {
    int i;
    for (i = 0; i < g.vertex_quantum; ++i) {
        if (venue == g.vexs[i]) {
            return i;
        }
    }

    return IMPOSSIBLE;
}

void dijkstraAlgorithm(graphStructor g, int src_node) {
    int vexQuantity = g.vertex_quantum;

    for (int i = 0; i < vexQuantity; ++i) {//初始化distance集合以及前驱节点集合
        distanceArray[i] = g.adjacencyMatrix[src_node][i];//初始化起点到其它各顶点的最短路径
        flag_signal[i] = false;

        if (distanceArray[i] == LARGE_INT) {
            prevArray[i] = IMPOSSIBLE;//起点到该顶点的距离无穷大,说明 顶点i 与 起点 不相邻
        } else {
            prevArray[i] = src_node;//说明 顶点i 与 起点 相邻,设置顶点i的前驱节点prev[i]为 起点
        }
    }

    distanceArray[src_node] = 0;
    flag_signal[src_node] = true;// 初始时,集合中只有起点元素

    for (int i = 0; i < vexQuantity; ++i) {//寻找起点到每个顶点的最短路径
        int temp = LARGE_INT, t = src_node;

        for (int j = 0; j < vexQuantity; ++j) {// 在集合中寻找离起点最近的 顶点t
            if ((!flag_signal[j]) && (distanceArray[j] < temp)) {
                t = j;
                temp = distanceArray[j];
            }
        }

        if (t == src_node) {
            return;//找不到距离起点最近的 顶点t, 跳出循环
        }

        flag_signal[t] = true;//否则,将 顶点t 加入集合

        for (int j = 0; j < vexQuantity; ++j) {//更新与 顶点t 相邻的顶点到起点的距离
            if ((!flag_signal[j]) && (g.adjacencyMatrix[t][j] < LARGE_INT)) {//flag_signal[j]=true 表示 j 在集合中
                if (distanceArray[j] > (distanceArray[t] + g.adjacencyMatrix[t][j])) {
                    distanceArray[j] = distanceArray[t] + g.adjacencyMatrix[t][j];
                    prevArray[j] = t;
                }
            }
        }
    }
}

void string2charArray(string str, char *ch) {
    int length = str.copy(ch, ARRAY_LENGTH - 1);
    ch[length] = '\0';
}

/**
 * 打印起点至其它每个顶点的最短路径
 * @param g
 * @param srcNode
 */
void ergodicShortestPath(graphStructor g, int srcNode) {
    int signal, x;
    string s1, s2;
    char ch1[ARRAY_LENGTH] = {}, ch2[ARRAY_LENGTH] = {};

    string src_place = *(g.vexs + srcNode);
    cout << "The source place is: " << src_place << endl;

    for (int i = 0; i < g.vertex_quantum; ++i) {
        x = prevArray[i];

        s1 = *(g.vexs + srcNode);
        s2 = *(g.vexs + i);

        cout << endl;
        cout << "base line: " << s1 << ",  destination: " << s2 << endl;

        string2charArray(s1, ch1);
        string2charArray(s2, ch2);

        signal = strcmp(ch1, ch2);

        if ((x == -1) && (signal != 0)) {
            cout << "source node to other vertex shortest path is: " << s1 << "==>>" << s2 << endl;
            continue;
        }

        cout << src_place << " to " << *(g.vexs + i) << " shortest distance is: " << distanceArray[i] << endl;
    }
}

void executeTest1() {
    graphStructor g;
    string region[] = {"spain", "france", "italy", "germany"};

    // algorithm-tutorial/images/west-europe.png
    edgesRelation edgesCollect[] = {
            {vertex:"spain", vertex2:"france", routeLength:116},
            {vertex:"spain", vertex2:"italy", routeLength:199},
            {vertex:"france", vertex2:"germany", routeLength:93},
            {vertex:"italy", vertex2:"germany", routeLength:150},
    };

    g.vexs = region;
    g.edges = edgesCollect;
    g.vertex_quantum = sizeof(region) / sizeof(region[0]);
    g.edge_quantum = sizeof(edgesCollect) / sizeof(edgesCollect[0]);

    buildOneUnDirectGraph(g);
    showMartix(g);

    int src_node = getRegionPosition(g, "spain");
    dijkstraAlgorithm(g, src_node);

    cout << endl;
    ergodicShortestPath(g, src_node);
}
