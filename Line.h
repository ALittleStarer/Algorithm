#include<iostream>
using namespace std;

class Line
{
private:
    int src;
    int dest;
    int distance;
public:
    Line(){}
    Line(int s,int d, int dis): src(s), dest(d), distance(dis){}
    int getSource() const {return src;}
    int getDest() const {return dest;}
    int getDistance() const {return distance;}
    void print()
    {
        cout<<src<<"--"<<dest<<":"<<distance<<endl;
    }

    friend bool operator > (const Line& A, const Line& B)
    {
        return A.distance > B.distance;
    }

    friend bool operator < (const Line& A, const Line& B)
    {
        return A.distance < B.distance;
    }

    friend bool operator == (const Line& A, const Line& B)
    {
        return A.distance == B.distance;
    }

    friend ofstream& operator << (ofstream& out, Line& line){
        out<<src<<"--"<<dest<<":"<<distance;
        return out;
    } 

};