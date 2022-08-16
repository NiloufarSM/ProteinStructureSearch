//
//  Model.h
//  atomParser
//
//  Created by saman on 7/21/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#ifndef MODEL_H_
#define MODEL_H_

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "Chain.h"
using namespace std;

class Model{
public:
    
    vector<Chain> chains;
    int numberOfChains;
    
    Model( );
    ~Model( );
    void createNewChain( );
    
};

#endif