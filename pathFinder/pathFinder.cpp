/*************************************************
  Copyright (C), 2017.10.10-2017.10.13, Trunk Tech.
  File name:    pathFinder.h
  Author:  薛崇     Version: １.0       Date:2017.10.11
  Description:    path finder with A* algorithm
                  leader function is aStar()
                  check input using judge
                  check other input and generate nodeMap, using initNodeMap
                  init and generate paths, using initPaths
                  call aStep recursively, complete the search
  Others:         // 其它内容的说明
  Function List:  // 主要函数列表，每条记录应包括函数名及功能简要说明
    1. ....
  History:        // 修改历史记录列表，每条修改记录应包括修改日期、修改
                  // 者及修改内容简述  
    1. Date:2017.10.11
       Author:XueChong
       Modification:build up the framework
    2. Date:2017.10.12
       Author:XueChong
       Modification:fix the bugs
    3. Date:2017.10.13
       Author:XueChong
       Modification:add detailed comments
    4. ...
*************************************************/

#include "pathFinder.h"

#include <iostream>
#include <vector>
#include <limits>
#include <cmath>
#include <math.h>

using std::vector;
using std::abs;

namespace xuechong{

vector<int> aStar(const vector< vector<int> > &weights ,const int srcNode, const int targetNode,const  vector<double> &nodeX, vector<double> &nodeY){
    //define it firstly, if input is wrong, return the empty path
    vector<int> path;
    //if there is no path from srcNode to targetNode,return NULL
    if( !judge(weights, srcNode, targetNode)){
        std::cout<< "input is fault, please check!\n";
        path.resize(1,-2);
        return path;
    }

    // init nodeMap
    vector< vector<double> > nodeMap;
    //there should check if nodeX and nodeY is correct,false lead to empty path return
    if( !initNodeMap(weights, nodeX, nodeY, nodeMap)){
        std::cout<< "input is fault, please check!\n";
        path.resize(1,-2);
        return path;
    }

    //init paths
    vector<double> paths;
    initPaths(nodeMap, srcNode, targetNode, paths);

    //define parents and visited
    vector<int> parents(nodeX.size(),-1);
    vector<int> visited;

    // start calling main algorithm aStep recursively
    int result = aStep(srcNode, targetNode, nodeMap, paths, parents, visited);

    path.push_back(targetNode);
    int tempNode = targetNode;

    int step = 0;
    while((tempNode = parents[tempNode]) != srcNode && tempNode >= 0){
        path.push_back(tempNode);
        step ++;
        //path doesn't exist
        if(step > nodeMap.size()){
            path.resize(1);
            path[0] = -1;
            std::cout << "doesn't exist! \n";
            return path;
        }
    }

    //path doesn't exist
    if(tempNode < 0){
        std::cout << "doesn't exist! \n";
        path.resize(1);
        path[0] = -1;
        return path;
    }

    path.push_back(srcNode);

    //reverse the path, make it start from srcNode and end with targetNode
    int temp = 0;
    for (int i=0; i< path.size()/2 ; i++){
        temp = path[i];
        path[i] = path[path.size() - 1 - i];
        path[path.size() - 1 - i] = temp;
    }

    return path;
}


bool judge(const vector< vector<int> > &weights, const int srcNode, const int targetNode){
    if(weights.size() <=0){
        return false;
    }

    if(srcNode >= weights.size() || targetNode >= weights.size()){
        return false;
    }

    for(int i=0; i<weights.size(); i++){
        if(weights[i].size() != weights.size()){
            return false;
        }
    }

    return true;
}


int aStep(int srcNode, const int targetNode,const vector< vector<double> > &nodeMap, vector<double> &paths, vector<int> &parents, vector<int> &visited){

    //std::cout << srcNode << "-->";

    if( srcNode == targetNode){
        return 0;
    }
    if( visited.size() == nodeMap.size() ){
        return 0;
    }

    //update paths, g_cost
    for(int i=0;i<nodeMap.size();i++){
        if (nodeMap[srcNode][i] > 0  && nodeMap[srcNode][i] + paths[srcNode] <= paths[i] ){
            paths[i] = paths[srcNode] + nodeMap[srcNode][i];
            parents[i] = srcNode;
        }
    }

    visited.push_back(srcNode);

    //compute h_cost
    double distance = std::numeric_limits<double>::max();
    for(int i=0; i< nodeMap.size(); i++){
        if(!isContain(visited, i)  && paths[i] + abs(nodeMap[i][targetNode]) < distance ){
            srcNode = i;
            distance = paths[i] + abs(nodeMap[i][targetNode]) ;
        }
    }

    return aStep(srcNode, targetNode,  nodeMap, paths, parents, visited);
}

bool isContain(const vector<int> &visited, int node){
    for(int i=0; i< visited.size(); i++){
        if( node == visited[i]){
            return true;
        }
    }
    return false;
}

bool initNodeMap(const vector< vector<int> > &weights, const vector<double> &nodeX, const vector<double> &nodeY, vector< vector<double> > &nodeMap){
    //check the nodeX and nodeY firstly
    if(nodeX.size() != weights.size() || nodeY.size() != weights.size() || nodeX.size()==0){
        return false;
    }
    
    vector<double> nodeRow(nodeX.size(), 0.0);
    nodeMap.resize(nodeX.size(), nodeRow);

    for(int i=0; i< nodeX.size(); i++){
        for(int j = 0; j< nodeY.size(); j++){
            if(weights[i][j] == 1){
                nodeMap[i][j] = sqrt( pow(nodeX[i] - nodeX[j] ,2 ) + pow( nodeY[i]-nodeY[j] , 2) );
            }else{
                nodeMap[i][j] = 0 - sqrt( pow(nodeX[i] - nodeX[j] ,2 ) + pow( nodeY[i]-nodeY[j] , 2) );
            }
        }
    }

    return true;
}

void initPaths(const vector< vector<double> > &nodeMap, const int srcNode, const int targetNode, vector<double> &paths){
    paths.resize(nodeMap.size(), std::numeric_limits<double>::max());
    for(int i=0; i< nodeMap.size(); i++){
        if(nodeMap[srcNode][i] > 0){
            paths[i] = nodeMap[srcNode][i];
        }
    }
    paths[srcNode] = 0.0;
}
}
