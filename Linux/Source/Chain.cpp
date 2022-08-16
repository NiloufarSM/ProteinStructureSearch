//
//  Chain.cpp
//  atomParser
//
//  Created by saman on 7/21/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#include "Chain.h"


Chain::Chain( ){
    
    numberOfAminos = 0;
    
}

Chain::~Chain(){
    
    
    
}

void Chain::addNewAmino(){
    
    Amino newAmino;
    aminos.push_back( newAmino );
    numberOfAminos++;
    
}

