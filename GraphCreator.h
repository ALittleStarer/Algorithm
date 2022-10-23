#pragma once

#include"Graph.h"
#include<time.h>
class GraphCreator
{
private:
    Graph graph;
    GraphType type;
    int Random_getNum(int range);//指定范围随机取数
    int Random_getNum(int left, int right);//指定边界随机取数
    void procedure();
public:
    GraphCreator(){srand(time(NULL));};
    GraphCreator(int size, GraphType t): graph(Graph(size)), type(t) {srand(time(NULL));};
    int Random_getNum(); //默认随机取数，范围为1-1000
    bool Random_IsNeighbour();//随机确定两个节点是否邻接
    void Random_SetDistance(int src, int dest);//随机确定两个邻接节点直接的距离
    Graph& getGraph()
    {
        procedure();
        return graph;
    }
};

int GraphCreator::Random_getNum()
{
    int random = rand();
    return random%1000 + 1;
}

bool GraphCreator::Random_IsNeighbour()
{
    int flag = Random_getNum();
    return flag < 400;
}

void GraphCreator::Random_SetDistance(int src, int dest)
{
    if(Random_IsNeighbour()){
        graph.setDistance(src, dest, Random_getNum());
    }else{
        graph.setDistance(src,dest, -1);
    }
}

void GraphCreator::procedure()
{
    int size = graph.size();
    if(type == DIRECTED){
        for(int i=0; i < size; i++){
            for(int j=0; j < size; j++){
                if(i==j){
                    graph.setDistance(i, j, 0);
                }else{
                    Random_SetDistance(i,j);
                }
            }
        }
    }else{
        for(int i=0;i<size;i++){
            for(int j=i;j<size;j++){
                if(i==j){
                    graph.setDistance(i, j ,0);
                }else{
                    Random_SetDistance(i,j);
                    graph.setDistance(j, i, graph.getDistance(i, j ));
                }
            }
        }
    }
}