#ifndef BGG_H
#define BGG_H

#ifdef __cplusplus
extern "C" {
#endif

void modify(int);
int query(int);
void report(int, int);
int check(int);

void explore(int, int);

#ifdef __cplusplus
}
#endif

#endif
