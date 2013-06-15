//
//  utils.c
//  A2
//
//  Created by Alex Egg on 6/13/13.
//  Copyright (c) 2013 Alex Egg. All rights reserved.
//

#include <stdio.h>



unsigned * read_page_file()
{
    //pretend read file
    unsigned page_file [] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
    
    //unsigned (*ptr) [10] = &page_file;
    
    return page_file;
}