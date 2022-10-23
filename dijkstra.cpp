/*  
    复现Dijkstra 算法
    算法目标：计算一个节点到其他节点的最短路径（单源最短路）
    算法思想关键词：分治 | 动态规划 | 迭代

    时间复杂度: O(n^2) 路径长更新不可避免, 准确为n + n-1 + n-2 + ... + 1
*/
#include"GraphCreator.h"
#include"load.h"
#include"unordered_set"
/*Solution Code Below */
class Dijkstra
{
private:
    vector<vector<int>> Map;
    vector<int> distance;
    unordered_set<int> findOver;
    unordered_set<int> waitForFind;
    vector<Load> loads;
    int nodeSize;
    int source;
public:
    Dijkstra()
    {
        source = 0;
    }
    Dijkstra(vector<vector<int>>& mapInput):Map(mapInput)
    {
        nodeSize = Map.size();
        distance = vector<int>(nodeSize, INT_MAX);
        loads = vector<Load>(nodeSize);
        source = 0;
    };

    bool setSource(int sourceInput)
    {
        if(sourceInput < nodeSize){
            source =sourceInput;
            return true;
        }else{
            return false;
        }
    }

    bool initial(int sourceInput)
    {
        if(!setSource(sourceInput)){
            return false;
        }

        distance[sourceInput] = 0;
        loads[sourceInput] = Load(sourceInput, sourceInput);
        findOver.insert(sourceInput);
        for(int i=0; i < nodeSize; i++){
            if(i!=sourceInput){
                waitForFind.insert(i);
                distance[i]=Map[sourceInput][i];
                if(distance[i] != INT_MAX){
                    loads[i] = Load(sourceInput, i);
                }
            }
        }
        return true;
    }

    void solution()
    {
        cout<<"please input the source ID:";
        int sourceInput;
        cin>>sourceInput;
        if(!initial(sourceInput)){
            cout<<"source ID is illegal"<<endl;
            return;
        };
        // waitForFind 是未确定最短路径集合， findOver 是已确定最短路径集合
        while(!waitForFind.empty()){
            int minDistance = INT_MAX;
            int minID = -1;
            for(auto val : waitForFind){
                if(distance[val] <= minDistance){
                    minDistance = distance[val];
                    minID = val;
                }
            }
            waitForFind.erase(minID);
            findOver.insert(minID);

            for(auto val : waitForFind){
                if(Map[minID][val] != INT_MAX){
                    int newdistance = distance[minID] + Map[minID][val];
                    if(newdistance < distance[val]){
                        distance[val] = newdistance;
                        Load newLoad = Load(minID, val);
                        loads[val] = loads[minID] + newLoad;
                    }
                }
            }
        }     
    }

    void print()
    {
        cout<<"the source ID is:"<<source<<endl;
        for(int i=0;i<nodeSize;i++){
            cout<<distance[i]<<endl;
            loads[i].printLoad();
        }
    }
};

int main()
{
    int size;
    cin>>size;
    GraphCreator creator(size, UNDIRECTED);
    vector<vector<int>> map = creator.getGraph().map();

    for(int i=0;i<map.size();i++){
        for(int j=0;j<map[i].size();j++){
            if(map[i][j] == -1){
                map[i][j] = INT_MAX;
            }
        }
    }

    Dijkstra myDijkstra(map);
    myDijkstra.solution();
    myDijkstra.print();
    return 0;
}