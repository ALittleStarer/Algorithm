#include"ConnectedGraph.h"
#include"GetMST.h"
int main()
{
    GraphCreator creator(10, UNDIRECTED);
    Graph get;
    int connect = 0;
    for(int i=0; i < 10; i++){
        get =creator.getGraph();
        if(get.isConnected()){
            connect++;
        }
    }
    if(get.isConnected()){
        MST_Algorithm* mst = new Kruskal(get);
        MST_Algorithm* prim =new Prim(get);
        mst->solution();
        prim->solution();
        cout<<mst->getValue()<<" "<<prim->getValue()<<endl;
    }
}