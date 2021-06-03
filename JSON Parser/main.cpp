//
//  JSON Parser for Loudly
//
//  Created by Panagiotis Giotis on 6/3/21.
//  Copyright © 2021 Panagiotis Giotis. All rights reserved.
//

#include <iostream>
#include "JSONParser.h"

using namespace std;

int main(int argc, const char * argv[]) {
    
    cout << "\n************************************ \
        \nJSON Parser, created for Loudly\nPanagiotis Giotis, June 3nd, 2021\n";
    cout << "\nUsage: Run with hardcoded input filename in main.cpp, or use JSON filename as argument.\n";
    
    // Hardcoded filename
    string filename = "sample2.json";
    
    // Check for user input filename and overwrite
    if (argc>1) {
        filename = std::string(argv[1]);
    }
    
    // Create JSONParser
    JSONParser myJSONParser;
    
    // Open file
    myJSONParser.getJSONfile(filename);
    
    // Run analysis
    myJSONParser.process();
    
    // Do a full printout of the nodes
    myJSONParser.printAllNodes();
    
    cout << "\n\n -> JSON Parser terminated succesfully!\n" << endl;
    
    return 0;
}
