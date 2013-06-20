//
//  clock.h
//  A2
//
//  Created by Alex Egg on 6/13/13.
//  Copyright (c) 2013 Alex Egg. All rights reserved.
//

#ifndef A2_clock_h
#define A2_clock_h


void print_frame(int * frames, int * r, int len);
void clock(unsigned * pg, unsigned pages_len, int page_file_len);
unsigned clock_simulate(unsigned pages[], unsigned pages_len, unsigned table_len);
int find(int *hit_p, int* frames, int page, const int frame_len);

#endif
