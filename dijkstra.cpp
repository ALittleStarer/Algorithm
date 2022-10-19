/*  
    复现Dijkstra 算法
    算法目标：计算一个节点到其他节点的最短路径（单源最短路）
    算法思想关键词：分治 | 动态规划 | 迭代

    时间复杂度: O(n^2) 路径长更新不可避免, 准确为n + n-1 + n-2 + ... + 1
*/
#include<iostream>
#include<vector>
#include<unordered_set>
using namespace std;

class Load
{
private:
    vector<int> loadOrder;
public:
    Load(){}
    Load(const Load& copySource)
    {
        loadOrder = vector<int>(copySource.loadOrder);
    }
    Load(int source, int target)
    {
        loadOrder.push_back(source);
        loadOrder.push_back(target);
    }

    Load operator + (const Load& src)
    {
        Load copy(*this);
        if(copy.loadOrder[copy.loadOrder.size()-1] == src.loadOrder[0]){
            for(int i=1; i < src.loadOrder.size();i++){
                copy.loadOrder.push_back(src.loadOrder[i]);
            }
        }

        return copy;
    }

    void printLoad()
    {
        if(!loadOrder.empty()){
            cout<<loadOrder[0];
        }
        for(int i=1; i < loadOrder.size(); i++){
            cout<<"->"<<loadOrder[i];
        }

        cout<<endl;
    }
};
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

    void initial(int sourceInput)
    {
        setSource(sourceInput);
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
    }
    void solution()
    {
        cout<<"please input the source ID:";
        int sourceInput;
        cin>>sourceInput;
        initial(sourceInput);
        // waitForFind 是未确定最短路径集合， findOver 是已确定最短路径集合
        while(!waitForFind.empty()){
            print();
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
    vector<vector<int>> map = {
        {0, 1, -1 ,3},
        {1, 0, 2, -1},
        {-1, 2, 0, -1},
        {3, -1, -1, 0}
    };

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