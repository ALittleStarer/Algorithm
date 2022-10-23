#pragma once

#include"GraphCreator.h"

class GraphSplit
{
private:
    Graph mapAll;
    vector<Graph> graphs;
    vector<int> blockID;
public:
    GraphSplit(){}
    GraphSplit(Graph input):mapAll(input)
    {
        blockID = vector<int>(mapAll.size(), -1);
    }
    vector<vector<int>> getAllBlock();
    void getBlock(int id, int startId, vector<int>& block);
    void setGraphs();
    vector<Graph> getGraphs() const{return graphs;}

};

void GraphSplit::getBlock(int id, int startId, vector<int>& block)
{
    for(int i=0; i<mapAll.size(); i++){
        if(mapAll.isNeighbour(startId, i)){
            if(blockID[i] == -1){
                block.push_back(i);
                blockID[i] = id;
                getBlock(id, i, block);
            }
        }
    }
}

vector<vector<int>> GraphSplit::getAllBlock()
{
    vector<vector<int>> allBlock;
    int id = 0;
    for(int i=0; i<mapAll.size();i++){
        if(blockID[i] == -1){
            vector<int> block;
            getBlock(id, i, block);
            id++;
            allBlock.push_back(block);
        }
    }

    return allBlock;
}

void GraphSplit::setGraphs()
{
    auto allBlock = getAllBlock();

    for(auto val : allBlock){
        vector<vector<int>> newgraph(val.size(), vector<int>(val.size()));
        for(int i=0; i<val.size();i++){
            for(int j=0;j<val.size();j++){
                newgraph[i][j] = mapAll.getDistance(val[i], val[j]);
            }
        }
        graphs.push_back(Graph(newgraph));
    }

}