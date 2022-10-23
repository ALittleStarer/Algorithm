#include<iostream>
#include<vector>
#include<unordered_map>
using namespace std;


class UFset
{
private:
    unordered_map<int,int> fatherMap;
    unordered_map<int,int> setSize;
public:
    UFset(){}
    bool contain(int target)
    {
        return fatherMap.find(target) != fatherMap.end();
    }
    
    int getSetId(int target)
    {
        if(contain(target)){
            while(fatherMap[target] !=-1){
                target = fatherMap[target];
            }
            return target;
        }
        
        return -1;
    }
    bool Union(int a, int b)
    {
        if(!contain(a)){
            fatherMap[a] = -1;
            setSize[a] = 1;
        }
        if(!contain(b)){
            fatherMap[b] = -1;
            setSize[b] = 1;
        }

        int A_Id = getSetId(a);
        int B_Id = getSetId(b);
        if(A_Id == B_Id){
            return false;
        }

        if(setSize[A_Id] >= setSize[B_Id]){
            setSize[A_Id] = setSize[A_Id] + setSize[B_Id];
            fatherMap[B_Id] = A_Id;
            setSize.erase(B_Id);
        }else{
            setSize[B_Id] = setSize[B_Id] + setSize[A_Id];
            fatherMap[A_Id] = B_Id;
            setSize.erase(A_Id);
        }

        return true;
    }
};