#include "../../headers/public_invoke.h"

const int MaxVertexNum = 10;

typedef struct AdjacencyNode
{
  int vertexIndex;
  struct AdjacencyNode *nextAdjNode;
} AdjNode;

typedef struct VertexNode
{
  char data;
  AdjNode *firstAdjNode;
} VxNode;

typedef struct
{
  VxNode VexArray[MaxVertexNum];
  int vertexNum, edgeNum;
} AdjacencyListGraph;

int getVertexIndex(AdjacencyListGraph g, char x)
{
  int i;
  for (i = 0; i < g.vertexNum; i++)
  {
    if (x == g.VexArray[i].data)
    {
      return i;
    }
  }
  return -1;
}

void insertEdge(AdjacencyListGraph &g, int firstIndex, int secondIndex)
{
  AdjNode *aj;
  aj = new AdjNode;
  aj->vertexIndex = firstIndex;
  aj->nextAdjNode = g.VexArray[secondIndex].firstAdjNode;
  g.VexArray[secondIndex].firstAdjNode = aj;
}

void displayGraph(AdjacencyListGraph g, char *vertex_arr)
{
  for (int i = 0; i < g.vertexNum; i++)
  {
    AdjNode *tmp = g.VexArray[i].firstAdjNode;
    cout << g.VexArray[i].data << " -> ";

    while (tmp != NULL)
    {
      cout << "[" << tmp->vertexIndex << "]";
      cout << "(" << vertex_arr[tmp->vertexIndex] << ") ";
      tmp = tmp->nextAdjNode;
    }
    cout << endl;
  }
}

void generatesAdjList(AdjacencyListGraph &g, char *vertex_arr, char (*edge_arr)[2])
{
  int index, index2;
  char vex_ch, vex_ch2;

  for (int i = 0; i < g.vertexNum; i++)
  {
    g.VexArray[i].data = vertex_arr[i];
    g.VexArray[i].firstAdjNode = NULL;
  }

  for (int i = 0; i < g.edgeNum; ++i)
  {
    vex_ch = edge_arr[i][0];
    vex_ch2 = edge_arr[i][1];

    index = getVertexIndex(g, vex_ch);
    index2 = getVertexIndex(g, vex_ch2);

    if (index != -1 && index2 != -1)
    {
      insertEdge(g, index, index2);
    }
  }
}

int main()
{
  AdjacencyListGraph g;
  char vertex_arr[] = {'a', 'b', 'c', 'd'};

  char edge_arr[][2]{
      {'a', 'd'},
      {'a', 'b'},
      {'b', 'd'},
      {'b', 'c'},
      {'b', 'a'},
      {'c', 'd'},
      {'c', 'b'},
      {'d', 'c'},
      {'d', 'b'},
      {'d', 'a'}};

  g.vertexNum = sizeof(vertex_arr) / sizeof(vertex_arr[0]);
  g.edgeNum = sizeof(edge_arr) / sizeof(edge_arr[0]);

  generatesAdjList(g, vertex_arr, edge_arr);
  displayGraph(g, vertex_arr);

  return 0;
}
