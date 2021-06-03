//
//  JSONParser.cpp
//  JSON Parser
//
//  Created by Panagiotis Giotis on 6/3/21.
//  Copyright © 2021 Panagiotis Giotis. All rights reserved.
//

#include "JSONParser.h"

// Open and store JSON file
void JSONParser::getJSONfile(std::string filename) {
    JSONParser::inputFile.open(filename.c_str());
    
    if (JSONParser::inputFile.is_open()) { /* ok, proceed with output */
        std::cout <<  ("\n-> File " + filename + " found, reading in...\n");
    }
    else
    {
        std::cout <<  ("\n-> Error! File " + filename + " not found, exiting...\n\n");
        exit(0);
    }
}

// Trim initial whitespace
string JSONParser::ltrim(std::string s) {
    long firstCharIdx = s.find_first_not_of(" ");
    if (firstCharIdx>0) {
        s.erase(0, firstCharIdx);
    }
    return s;
}

// Strip redundant " and , symbols before storing nodees
string JSONParser::strip(std::string s) {
    char tmp = s.back();
    while ((tmp == '"' or tmp == ','))
    {
        s.pop_back();
        tmp = s.back();
    }
    return s;
}

// Do a full printout of node structure
void JSONParser::printAllNodes () {
    
    long Len = JSONParser::myNodes.size();
    cout << "\n************************************\n\nFinal JSON Printout\nNumber of Primary Nodes: " << Len;
    for (int i=0; i< Len; i++){
        cout << "\n\n* Node #" << i+1 << " | Type: " << JSONParser::myNodes[i].Type;
        for (int j = 0; j<JSONParser::myNodes[i].Key.size(); j++) {
            cout << "\nKey: " <<  JSONParser::myNodes[i].Key[j] << " | Value: " << JSONParser::myNodes[i].Value[j] << " | Parent Node: "<< JSONParser::myNodes[i].Name;
        }
    }
}

// Main process function
void JSONParser::process() {
    
    std::cout <<  ("\n-> Processing...\n");
    string line;
    bool multinode = false;
    
    // Vector to contain the Node collection
    vector<Node> myNodes;
    
    int i = 0;
    while ( getline (JSONParser::inputFile, line) )
    {
        string myLine = line;
        
        // Check for initial/endind brackets and skip
        if (( line == "{" ) or (line == "}")) {
            if (DEBUG) cout << "\nSkipping initial/ending brackets...";
            continue;
        }
        
        // Remove initial whitespace
        line = ltrim(line);
        
        // Check if current line is multinode start
        if (line[line.length()-1] == '{') {
            multinode = true;
        }
        
        // Check if current line is multinode end
        if ( line == "}," ) {
            multinode = false;
            continue;
        }
        
        // Check if Node is singular
        if (!multinode) {
            if (DEBUG) cout << "\n*****************************\nSingular Node Found! Node #" << i+1 << "\n";
            
            // Remove initial whitespace
            myLine = ltrim(myLine);
            
            // Find separator
            long idx = myLine.find(':');
            
            // Create Node
            myNodes.push_back(Node());
            myNodes[i].Type.push_back('S');
            myNodes[i].Name = strip(myLine.substr(1,idx-1));
//            myNodes[i].Key.push_back(strip(myLine.substr(0,idx-1)));
//            myNodes[i].Value.push_back(strip(myLine.substr(idx+2, myLine.length()-3)));
            myNodes[i].Key.push_back(strip(myLine.substr(1,idx-1)));
            myNodes[i].Value.push_back(strip(myLine.substr(idx+2)));
            
            if (DEBUG) cout << "\nKey: " <<  myNodes[i].Key.back() << " Value: " << myNodes[i].Value.back() << " in Parent Node: "<< myNodes[i].Name<< endl;
        }
        
        // Multinode
        else {
            if (DEBUG) cout << "\n*****************************\nMulti Node Found! Node #" << i+1 << "\n";
            multinode = true;
            // Create Node
            myNodes.push_back(Node());
            
            while (line != "}," ) {
                line = ltrim(line);
                myLine = line;
                
                // Find separator
                long idx = myLine.find(':');
                
                myNodes[i].Type = ('M');
                
                if (myNodes[i].Name.empty()) {
                    myNodes[i].Name = strip(myLine.substr(1,idx-1));
                }
                
                myNodes[i].Key.push_back(strip(myLine.substr(1,idx-1)));
                myNodes[i].Value.push_back(strip(myLine.substr(idx+3)));
//                myNodes[i].Key.push_back(strip(myLine));
//                myNodes[i].Value.push_back(strip(myLine));
                
                if (DEBUG) cout << "\nKey: " <<  myNodes[i].Key.back() << " Value: " << myNodes[i].Value.back() << " in Parent Node: "<< myNodes[i].Name<< endl;
                
                getline (JSONParser::inputFile, line);
                line = ltrim(line);
            }
            multinode = false;
        }
        i++;
    }
    
    // Export to class var
    JSONParser::myNodes = myNodes;
    
    // Close file
    JSONParser::inputFile.close();
}
