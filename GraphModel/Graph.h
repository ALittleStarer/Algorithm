#pragma once

#include<iostream>
#include<vector>
#include"Line.h"
using namespace std;

enum GraphType
{
    UNDIRECTED,DIRECTED,CONNECTED_UND
};

class Graph
{
protected:
    vector<vector<int>> innerMap;
    int nodeSize;
public:
    Graph(): nodeSize(0){}
    Graph(int size): nodeSize(size), innerMap(vector<vector<int>>(size, vector<int>(size,0))) {}
    Graph(vector<vector<int>> mapInfo): nodeSize(mapInfo.size()), innerMap(mapInfo) {}
    Graph(const Graph& graph)
    {
        nodeSize = graph.nodeSize;
        innerMap = vector<vector<int>>(graph.innerMap);
    }

    int size()
    {
        return nodeSize;
    }

    vector<vector<int>> map()
    {
        return innerMap;
    }

    bool isLegal(int id) const
    {
        return id>=0&&id<nodeSize;
    }

    int getDistance(int src, int dest) const
    {
        if(isLegal(src)&&isLegal(dest))
        {
            return innerMap[src][dest];
        }
        return -1;
    }

    bool isNeighbour(int src, int dest) const
    {
        return getDistance(src, dest) != -1;
    }
    
    bool setDistance(int src, int dest, int distance)
    {
        if(isLegal(src)&&isLegal(dest))
        {
            innerMap[src][dest] = distance;
            return true;
        }
        return false;
    }

    void getBlock(int startId, vector<int>& block, vector<bool>& find)
    {
        for(int i=0; i<nodeSize;i++)
        {
            if(isNeighbour(startId, i)){
                if(!find[i]){
                    find[i] = 1;
                    block.push_back(i);
                    getBlock(i, block, find);
                }
            }
        }
    }
    bool isConnected()
    {
        vector<bool> find(nodeSize, 0);
        vector<int> block;
        getBlock(0, block, find);
        return block.size() == nodeSize;
    }

    vector<Line> getAllLine() //默认无向图
    {
        vector<Line> allLines;
        for(int i=0; i < nodeSize; i++){
            for(int j=i+1; j < nodeSize; j++){
                if(isNeighbour(i, j+1)){
                    allLines.push_back(Line(i, j+1, getDistance(i, j+1)));
                }
            }
        }

        return allLines;
    }

    vector<Line> getLineContain(int node)
    {
        vector<Line> lines;
        for(int i=0; i < nodeSize; i++){
            if(i != node){
                if(isNeighbour(node, i)){
                    lines.push_back(Line(node, i, getDistance(node, i)));
                }
            }
        }
        
        return lines;
    }

    void print() const
    {
        for(int i=0;i<nodeSize;i++){
            for(int j=0;j<nodeSize;j++){
                cout<<innerMap[i][j]<<" ";
            }
            cout<<endl;
        }
    }

};