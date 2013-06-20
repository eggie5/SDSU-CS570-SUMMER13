//
//  ui.c
//  A2
//
//  Created by Alex Egg on 6/13/13.
//  Copyright (c) 2013 Alex Egg. All rights reserved.
//

#include <stdio.h>
#include "clock.h"
#include "utils.h"
#define PAGE_TABLE_LEN 3

void ui_loop()
{
    printf("Assignment 2\n");
    
    unsigned _pages[100];
    int len = read_page_file(&_pages);
    int page_table_len=PAGE_TABLE_LEN;
    page_table_len=6;
    
    printf("pages: ");
    for(int j=0;j<len;j++)
    {
        printf("%d ", _pages[j]);
    }
    
    clock_simulate(_pages, len, page_table_len);
//    opt_simulate(_pages);
//    lru_simulate(_pages);
    
    
}

