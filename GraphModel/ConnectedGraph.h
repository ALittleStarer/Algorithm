#pragma once

#include"GraphSplit.h"
class ConnectedGraph : public Graph
{
private:
    GraphSplit split;
public:
    ConnectedGraph(vector<vector<int>> mapInfo): Graph(mapInfo)
    {
        split = GraphSplit(Graph(mapInfo));
        letConnected();
    }

    void letConnected()
    {
        if(!isConnected())
        {
            auto allBlock = split.getAllBlock();
            vector<int> blockDeputy;
            for(auto val : allBlock){
                blockDeputy.push_back(val[0]);
            }

            srand(time(NULL));
            for(int i=0; i < blockDeputy.size()-1; i++){
                setDistance(blockDeputy[i], blockDeputy[i+1], rand()%1000 + 1);
                setDistance(blockDeputy[i+1], blockDeputy[i], 
                    getDistance(blockDeputy[i], blockDeputy[i+1]));
            }
        }

    }
};