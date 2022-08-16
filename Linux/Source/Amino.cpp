//
//  Amino.cpp
//  atomParser
//
//  Created by saman on 7/21/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#include "Amino.h"

Amino::Amino( ){
    
    numberOfAtoms = 0;
    
}

Amino::~Amino(){
    
}

void Amino::addNewAtom(){
    
    Atom newAtom;
    atoms.push_back( newAtom );
    numberOfAtoms++;
    
}

