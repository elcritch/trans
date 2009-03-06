#ifndef __TERMINALS_H
#define __TERMINALS_H 1



typedef struct TreeId {
  char *id;
} *TreeId;

typedef struct TreeNum {
  char *num;
} *TreeNum;

typedef struct TreeReal {
  char *real;
} *TreeReal;



extern TreeId p_id();
extern TreeNum p_num();
extern TreeReal p_real();

#endif



