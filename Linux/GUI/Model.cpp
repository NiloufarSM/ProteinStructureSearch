//
//  Model.cpp
//  atomParser
//
//  Created by saman on 7/21/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#include "Model.h"

Model::Model( ){
    
    numberOfChains = 0;
    
}

Model::~Model(){
    
    
}

void Model::createNewChain(){
    
    Chain newChain;
    chains.push_back( newChain );
    numberOfChains++;
    
}
