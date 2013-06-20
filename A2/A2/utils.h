//
//  utils.h
//  A2
//
//  Created by Alex Egg on 6/13/13.
//  Copyright (c) 2013 Alex Egg. All rights reserved.
//

#ifndef A2_utils_h
#define A2_utils_h


int * read_page_file();
int exists(int frame_size,int page_frames[],int page_num);
void print_frame(int * frames, int * r, int len);
void display(int page_frames[],int frame_size);

#endif
