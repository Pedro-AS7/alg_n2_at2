#ifndef ALG_N2_AT2_GLOBALS_H
#define ALG_N2_AT2_GLOBALS_H

#include "types.h"

extern struct User *currentUser;
extern struct User users[MAX_CLIENTS];
extern int users_count;
extern struct Restaurant restaurants[10];
extern int restaurants_count;
extern struct Bag bags[MAX_CLIENTS];
extern struct Order orders[MAX_CLIENTS];
extern int bags_count;
extern int orders_count;
extern struct Favorite favorites[100];
extern int favorites_count;


#endif
