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
#include "opt.h"
#include "lru.h"
#define PAGE_T_LEN 3

void ui_loop()
{
    printf("Assignment 2\n");
    int page_table_len=PAGE_T_LEN;
    printf("\nEnter page file length:");
    scanf("%d",&page_table_len);
    
    unsigned _pages[100];
    int len = read_page_file(&_pages);


    
    printf("pages: ");
    for(int j=0;j<len;j++)
    {
        printf("%d ", _pages[j]);
    }
    
    clock_simulate(_pages, len, page_table_len);

    lru_simulate(_pages, len, page_table_len);

    opt_simulate(_pages, len, page_table_len);

}

