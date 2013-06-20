#ifndef A2_lru_h
#define A2_lru_h


void display(int page_frames[],int frame_size);
void lru(unsigned reference[], unsigned length, const int frame_size);
unsigned lru_simulate(unsigned pages[], unsigned pages_len, unsigned table_len);

#endif