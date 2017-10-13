#include "pathFinder/pathFinder.h"

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>

int main(int argc , char * argv[]){

    //read data from nodes.txt and weights.txt
    vector<double> nodeX;
    vector<double> nodeY;
    vector< vector<int> > weights;
    
    std::ifstream nodefile;
    nodefile.open("data/nodes.txt");//data file

    int i,x,y;

    if(nodefile.is_open()){
        while(nodefile >> i >> x >> y){
            nodeX.push_back(x);
            nodeY.push_back(y);
            //std::cout<< i << " "<< x << " " << y << std::endl;
        }
        //std::cout<<"node file read done.\n";
        nodefile.close();
    }
    else{
        std::cout<<"node file unable to be opened\n";
        return 0;
    }

    vector<int> weight(nodeX.size(),0);
    weights.resize(nodeX.size(), weight);

    std::string line;
    vector<std::string> lines;
    int node1,node2;
    std::ifstream weightfile("data/weights.txt");//data file
    if(weightfile.is_open()){
        while(std::getline(weightfile ,line)){
            std::istringstream nodes;
            nodes.str(line);
            nodes >> node1;
            while(nodes >> node2){
                weights[node1][node2] = 1;
            }
        }
        //std::cout<<"weight file read done.\n";
        weightfile.close();
    }else{
        std::cout<<"weight file unable to be opened\n";
        return 0;
    }

    //read args from args
    if (argc < 3){
        printf("there should be at least two arguments \n");
        return 0;
    }
    int srcNode = atoi(argv[1]);
    int targetNode = atoi(argv[2]);

    vector<int> paths;
    paths = xuechong::aStar(weights , srcNode, targetNode, nodeX, nodeY);

    for(int j = 0; j< paths.size() - 1 ; j++){
        std::cout<< paths[j] << "->";
    }
    if(paths.size() > 0){
        std::cout << paths[paths.size() - 1];
    }
    std::cout<<"\n";

    return 1;
}
