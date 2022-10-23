#include<iostream>
#include<vector>
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