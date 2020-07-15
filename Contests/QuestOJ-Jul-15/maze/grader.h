#ifndef MAZE_H
#define MAZE_H

#ifdef __cplusplus
extern "C" {
#endif
	void findpath(int initialDeep, int T);
	bool move(int color);
	int query();
#ifdef __cplusplus
}
#endif

#endif
