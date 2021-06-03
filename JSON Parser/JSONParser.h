//
//  JSONParser.h
//  JSON Parser
//
//  Created by Panagiotis Giotis on 6/3/21.
//  Copyright © 2021 Panagiotis Giotis. All rights reserved.
//

#ifndef JSONParser_h
#define JSONParser_h

#define DEBUG 0

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

struct Node
{
    string Name;
    string Type; // 'S' for Single, 'M' for Multi
    vector<string> Key;
    vector<string> Value;
};

class JSONParser
{
    
public:
    // Constr/Destr
    JSONParser(){};
    ~JSONParser(){};
    
    // Main functions
    void getJSONfile(std::string filename);
    void process();
    void printAllNodes ();

private:
    // AUX functions
    string ltrim(std::string s);
    string strip(std::string s);
    
    // Var
    fstream inputFile;
    vector<Node> myNodes;
};

#endif /* JSONParser_h */


