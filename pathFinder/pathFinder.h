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
#include <vector>
using std::vector;

namespace xuechong{

/*************************************************
  Function:       Astar for this file self
  Description:    main function of this file, 
  Called By:      //node_idxs_selected = aStar(pts, weight, start_idx, end_idx);
  Calls:          juge, initNodeMap, initPaths, aStep
  Input:          const src node
                  const target node
                  const node map
                  path of node list, renfrence arguments
  Return:         vector of path node, from srcNode to targetNode, if only contain -1,means there is not a path from srcNode to targetNode
*************************************************/
vector<int> aStar(const vector< vector<int> > &weights ,const int srcNode, const int targetNode,const  vector<double> &nodeX, vector<double> &nodeY);


/*************************************************
  Function:       Astar
  Description:    main function of this file, 
  Called By:      aStar
  Input:          const src node
  Output:         return itself until succeed, then return 0
*************************************************/
int aStep(int srcNode, const int targetNode,const vector< vector<double> > &nodeMap, vector<double> &paths, vector<int> &parents, vector<int> &visited);

/*************************************************
  Function:       judge
  Description:    check weather input is correct
  Called By:      aStar
  Calls:          isContain(visited, node)
  Input:          weights, srcNode, targetNode
  Return:         bool, if input is correct,return true, or return false
*************************************************/
bool judge(const vector< vector<int> > &weights, const int srcNode, const int targetNode);

/*************************************************
  Function:       initNodeMap
  Description:    check, and generate nodeMap
                  positive number is the edge weight, negative is the Euclidean distance * -1
  Called By:      aStar
  Input:          weights, nodeX, nodeY, nodeMap
  Return:         bool, if input is correct,return true, or return false
*************************************************/
bool initNodeMap(const vector< vector<int> > &weights, const vector<double> &nodeX, const vector<double> &nodeY, vector< vector<double> > &nodeMap);

/*************************************************
  Function:       initPaths
  Description:    initPaths
  Called By:      aStar
  Input:          nodeMap, srcNode, targetNode, paths
  Return:         bool, if input is correct,return true, or return false
*************************************************/
void initPaths(const vector< vector<double> > &nodeMap, const int srcNode, const int targetNode, vector<double> &paths);


/*************************************************
  Function:       isContain
  Description:    if visited contain node
  Called By:      aStep
  Input:          visited, node
  Return:         bool, if visited contains node,return true, or return false
*************************************************/
bool isContain(const vector<int> &visited, int node);

}
