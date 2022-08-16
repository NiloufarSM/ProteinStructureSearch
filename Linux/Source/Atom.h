//
//  Atom.h
//  atomParser
//
//  Created by saman on 7/10/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#ifndef ATOM_H_
#define ATOM_H_

#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <vector>
#include <iostream>
using namespace std;


class Atom{
public:
    
    //----ATOM_SECTION----
    
    // atom serial number
    int serial;
    
    // atom name
    string name;
    
    // residue name
    string residue;
    
    // chain identifier
    char chainID;
    
    // residue sequence number
    int resSeq;
    
    // code for insertion of residues
    char iCode;
    
    // orthogonal coordinates for X in Angstroms
    float X;
    
    // orthogonal coordinates for Y in Angstroms
    float Y;
    
    // orthogonal coordinates for Z in Angstroms
    float Z;
    
    // occupancy
    float occupancy;
    
    // temperature factor
    float tempFactor;
    
    //----HETATM_SECTION---- 
    
    Atom( );
    ~Atom( );
    
};


#endif