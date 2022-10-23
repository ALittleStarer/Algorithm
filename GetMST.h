#pragma once

#include<iostream>
#include"GraphCreator.h"
#include"UFset.h"
#include<queue>
#include"Line.h"

class MST_Algorithm
{
protected:
    Graph graph;
    priority_queue<Line, vector<Line>, greater<Line>> manager;
    vector<Line> lineChoose;
    UFset treeNodeSet;
    int treeValue = 0;
public:
    MST_Algorithm(){}
    MST_Algorithm(Graph inputMap):graph(inputMap){}
    virtual void initial() = 0;
    bool noCircle(Line line);
    virtual void solution() = 0;
    void print();
    int getValue() const {return treeValue;}
};

bool MST_Algorithm::noCircle(Line line)
{
    return treeNodeSet.Union(line.getSource(), line.getDest());
}

void MST_Algorithm::print()
{
    graph.print();
    for(auto val : lineChoose){
        val.print();
    }
}

class Kruskal : public MST_Algorithm
{
public:
    Kruskal(){}
    Kruskal(Graph graph) : MST_Algorithm(graph) {}
    void initial();
    void solution();
};

void Kruskal::initial()
{
    for(int i = 0 ; i < graph.size(); i++){
        for(int j = i+1; j< graph.size(); j++){
            if(graph.isNeighbour(i, j)){
                Line newline(i, j, graph.getDistance(i, j));
                manager.push(newline);
            }
        }
    }
}

void Kruskal::solution()
{
    initial();

    while(lineChoose.size() < graph.size()-1){
        Line candidate = manager.top();
        if(noCircle(candidate)){
            lineChoose.push_back(candidate);
            treeValue += candidate.getDistance();
        }
        manager.pop();
    }
}

class Prim : public MST_Algorithm
{
public:
    Prim(){}
    Prim(Graph graph) : MST_Algorithm(graph) {}
    void initial();
    void solution();
};

void Prim::initial()
{
    Line shortest(-1,-1,INT_MAX);
    for(int i = 0 ; i < graph.size(); i++){
        for(int j = i+1; j< graph.size(); j++){
            if(graph.isNeighbour(i, j)){
                Line newline(i, j, graph.getDistance(i, j));
                shortest = min(shortest, newline);
            }
        }
    }

    lineChoose.push_back(shortest);
    treeValue += shortest.getDistance();
    treeNodeSet.Union(shortest.getSource(), shortest.getDest());
    for(int i = 0; i< graph.size(); i++){
        if(i != shortest.getDest()){
            if(graph.isNeighbour(shortest.getSource(), i)){
                manager.push(Line(shortest.getSource(), i, graph.getDistance(shortest.getSource(), i)));
            }
        }
    }

    for(int i = 0; i < graph.size(); i++){
        if(i != shortest.getSource()&&graph.isNeighbour(shortest.getDest(), i)){
            manager.push(Line(shortest.getDest(), i, graph.getDistance(shortest.getDest(), i)));
        }
    }
}
void Prim::solution()
{
    initial();
    while(lineChoose.size() < graph.size()-1){
        Line candidate = manager.top();
        int newAdd = -1;
        if(!treeNodeSet.contain(candidate.getSource())){
            newAdd = candidate.getSource();
        }

        if(!treeNodeSet.contain((candidate.getDest()))){
            newAdd = candidate.getDest();
        }

        if(noCircle(candidate)){
            lineChoose.push_back(candidate);
            treeValue += candidate.getDistance();
            if(newAdd != -1){
                for(int i=0; i< graph.size(); i++){
                    if(graph.isNeighbour(newAdd, i)){
                        manager.push(Line(newAdd, i, graph.getDistance(newAdd, i)));
                    }
                }
            }
        }

        manager.pop();
    }
}