#include "../../headers/refer.h"

#define MAX_CAPACITY 100
#define LONG_PATH 99

typedef struct EdgeInformation {
    char v1, v2;
    int weight;
} edgeInfo;

typedef struct {
    char *vexs_info;
    int adjacencyMartix[MAX_CAPACITY][MAX_CAPACITY];
    int vex_num, edge_num;
    edgeInfo *edges_info;
} AdjMGraph;

int LocateVex(AdjMGraph g, char vertex);

void GenerateUnDirectGraph(AdjMGraph &g);

void PrintsUnGraph(AdjMGraph g);

void dijkstraPattern(AdjMGraph g, int startVex);

void printingShortPath(AdjMGraph g, int begin, int destination);

void drawEveryShortest(AdjMGraph g, int startVex);

int previousNodes[MAX_CAPACITY];
int distsGather[MAX_CAPACITY];// store shortest distance that find at now
int paths_array[MAX_CAPACITY];// the last vertex node that in shortest distance
bool isChecking[MAX_CAPACITY];// mark they whether already get shortest or not

// input begin vertex and destination vertex,output shortest distance result
void printingShortPath(AdjMGraph g, int begin, int destination) {
    if (paths_array[destination] != -1) {
        printingShortPath(g, begin, paths_array[destination]);
        cout << g.vexs_info[paths_array[destination]] << "-->";
    }
}

void drawEveryShortest(AdjMGraph g, int startVex) {
    cout << "start: " << g.vexs_info[startVex] << endl;
    for (int i = 0; i < g.vex_num; ++i) {
        cout << g.vexs_info[startVex] << "-->" << g.vexs_info[i] << ": " << distsGather[i] << endl;
    }
}

void dijkstraPattern(AdjMGraph g, int startVex) {
    int vexQuant, temp, min, t;
    vexQuant = g.vex_num;

    int flags[MAX_CAPACITY];// flags[i]=1 表示起点至V_i的最短路径已经获取

    for (int i = 0; i < vexQuant; ++i) {
        flags[i] = 0;
        previousNodes[i] = 0;//顶点i 的前驱节点为0

        distsGather[i] = g.adjacencyMartix[startVex][i];
    }

    //初始化
    flags[startVex] = 1;
    distsGather[startVex] = 0;

    //遍历(vexQuant-1)次,每次找出一个顶点的最短路径
    for (int i = 1; i < vexQuant; ++i) {//寻找当前最短路径,即,在未获取最短路径的顶点中,找到与起点之间路径最短的相邻顶点
        min = LONG_PATH;
        for (int j = 0; j < vexQuant; ++j) {
            if ((flags[j] == 0) && (distsGather[j] < min)) {
                min = distsGather[j];
                temp = j;
            }
        }

        //标记 顶点temp 为已经取得最短路径的顶点
        flags[temp] = 1;

        //更新当前最短路径和前驱节点,即当已经标记 顶点temp 取得最短路径之后,更新未获取最短路径的顶点的最短路径及其前驱节点
        for (int j = 0; j < vexQuant; ++j) {
            //防止溢出
            t = (g.adjacencyMartix[temp][j] == LONG_PATH ? LONG_PATH : (min + g.adjacencyMartix[temp][j]));
            if ((flags[j] == 0) && (t < distsGather[j])) {
                distsGather[j] = t;
                previousNodes[j] = temp;
            }
        }
    }
}

int LocateVex(AdjMGraph g, char vertex) {
    int i;
    for (i = 0; i < g.vex_num; i++) {
        if (vertex == g.vexs_info[i]) {
            return i;
        }
    }
    return -1;
}

void GenerateUnDirectGraph(AdjMGraph &g) {
    int i, j, k;
    char vex1, vex2;
    int weight, position, position2;

    int vexAmount = g.vex_num;
    int edgeAmount = g.edge_num;

    for (i = 0; i < vexAmount; i++) {
        for (j = 0; j < vexAmount; j++) {
            g.adjacencyMartix[i][j] = LONG_PATH;
        }
    }

    for (k = 0; k < edgeAmount; k++) {
        vex1 = g.edges_info[k].v1;
        vex2 = g.edges_info[k].v2;
        weight = g.edges_info[k].weight;

        position = LocateVex(g, vex1);
        position2 = LocateVex(g, vex2);

        if (position != -1 && position2 != -1) {
            g.adjacencyMartix[position][position2] = g.adjacencyMartix[position2][position] = weight;
        }
    }
}

void PrintsUnGraph(AdjMGraph g) {
    int i, j;
    for (i = 0; i < g.vex_num; i++) {
        cout << i << ":" << g.vexs_info[i] << "  ";
    }
    cout << endl;

    for (i = 0; i < g.vex_num; i++) {
        for (j = 0; j < g.vex_num; j++) {
            cout << g.adjacencyMartix[i][j] << "  ";
        }
        cout << endl;
    }
}

void executeTest2() {
    AdjMGraph g;

    // algorithm-tutorial/images/UDN-1.3.png
    char vertex_array[] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i'};
    edgeInfo edgeArrs[] = {
            {v1:'a', v2:'b', weight:6},
            {v1:'a', v2:'c', weight:3},
            {v1:'b', v2:'c', weight:5},
            {v1:'b', v2:'d', weight:1},
            {v1:'b', v2:'e', weight:1},
            {v1:'c', v2:'e', weight:5},
            {v1:'c', v2:'f', weight:5},
            {v1:'d', v2:'e', weight:3},
            {v1:'d', v2:'g', weight:7},
            {v1:'e', v2:'f', weight:2},
            {v1:'e', v2:'g', weight:5},
            {v1:'e', v2:'h', weight:7},
            {v1:'e', v2:'i', weight:2},
            {v1:'f', v2:'i', weight:3},
            {v1:'g', v2:'h', weight:4},
            {v1:'h', v2:'i', weight:2}
    };

    g.vex_num = sizeof(vertex_array) / sizeof(vertex_array[0]);
    g.edge_num = sizeof(edgeArrs) / sizeof(edgeArrs[0]);

    g.vexs_info = vertex_array;
    g.edges_info = edgeArrs;

    GenerateUnDirectGraph(g);
    PrintsUnGraph(g);

    int startPos = LocateVex(g, vertex_array[0]);
    int endPos = LocateVex(g, vertex_array[g.vex_num - 1]);

    dijkstraPattern(g, startPos);

    // source vertex toward everywhere else
    drawEveryShortest(g, startPos);

    // vertex to other vertex
    printingShortPath(g, startPos, endPos);
}
