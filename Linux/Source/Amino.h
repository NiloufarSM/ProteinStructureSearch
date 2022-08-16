//
//  Amino.h
//  atomParser
//
//  Created by saman on 7/21/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#ifndef AMINO_H_
#define AMINO_H_

#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include "Atom.h"

class Amino{
public:
    
    vector<Atom> atoms;
    int numberOfAtoms;
    
    Amino( );
    ~Amino( );
    void addNewAtom( );
    
    
};

#endif