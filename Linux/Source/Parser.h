//
//  Parser.h
//  atomParser
//
//  Created by saman on 7/11/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//


#ifndef PARSER_H_
#define PARSER_H_

#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <vector>
#include <fstream>
#include "Model.h"

class Parser{
public:    
    
    ifstream inFile;
    vector<Model> models;
    int numberOfModels;
    char HEADER[80];
    
    Parser( string );
    void printResult( );
    void get( char*, int, ifstream* );
    
};

#endif
