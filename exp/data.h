#ifndef DATA_H
#define DATA_H
#include "point.h"
#include "edge.h"
#include "undiredge.h"

class Data
{
public:
    Data();
    Point p[100];
    QVector <Edge> E[100];
    UndirEdge UndirE[100];
    int une_num;
    int pnum;
    int par[100];
    int rootnum;
    int root[20];
    int type;
    int etype;
    int level;
    int start;
    bool ifpaint;
    int xulie1[100];
    int xulie2[100];
    void addedge(int u,int v,int w);
    void addundiredge(int u,int v,int w);
    int judgeMST();
    int judge();
    void callevel(int x);
    void initxulie();
    void clear();
};

#endif // DATA_H
