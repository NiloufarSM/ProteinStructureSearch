//
//  Chain.h
//  atomParser
//
//  Created by saman on 7/21/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#ifndef CHAIN_H_
#define CHAIN_H_

#include <vector>
#include <iostream>
#include <fstream>
#include <string>
#include "Amino.h"
using namespace std;

class Chain{
public:
    
    vector<Amino> aminos;
    int numberOfAminos;
    
    Chain( );
    ~Chain( );
    void addNewAmino( );
    
    
};

#endif