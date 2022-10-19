/*this model is to complete KMP algorithm
Tomorrow's work: KMP, essay
*/
#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

class KMP_Method{
private:
    string target;
    string model;
    vector<int> next;
public:
    KMP_Method(string t, string m): target(t), model(m)
    {
        next = vector<int>(t.size());
    }

    /* initial the next[]*/
    void getNext()
    {
        int length = model.size();
        int j=0, k=-1;
        next[0]=-1;
        while(j<length){
            if(k==-1 || model[j] == model[k]){
                j++;
                k++;
                next[j]=k;
            }else{
                k=next[k];
            }
        }
    }

    /* find if the model is in target 
            if true return the first index
            else return -1
    */
    int findFit()
    {
        getNext();
        int indexT = 0, indexM = 0;
        while(indexT < target.size() && indexM < model.size()){
            if(target[indexT] == model[indexM]){
                indexT++;
                indexM++;
            }else{
                if(next[indexM]== -1){
                    indexT++;
                }else{
                    indexM = next[indexM];
                }
            }
        }

        return indexM == model.size() ? indexT-indexM : -1;
    }
};

/*the function to judge its correction*/
bool Judge()
{
    string t,m;
    cin>>t>>m;
    KMP_Method kmp(t,m);
    int find = kmp.findFit();
    int real_find = t.find(m);
    cout<<find<<" "<<real_find<<endl;;
    return find == real_find;
}

int main()
{
    if(Judge()){
        cout<<"True"<<endl;
    }else{
        cout<<"False"<<endl;
    }
    
    return 0;
}