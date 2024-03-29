#include <pthread.h>

// globals (anything here would be shared with all threads) */
// pthread_mutex_t **lock; // global array of locks

// A hashmap entry stores the key, value
// and a pointer to the next entry
typedef struct ts_entry_t
{
   int key;
   int value;
   struct ts_entry_t *next; // pointer to next entry
} ts_entry_t;

// A hashmap contains an array of pointers to entries,
// the capacity of the array, and the size (number of entries stored)
typedef struct ts_hashmap_t
{
   ts_entry_t **table; // pointer to an array of entry pointers
   int capacity;       // size of the table (table[] array length)
   int size;           // number of entries currently stored
} ts_hashmap_t;

// /** struct to hold parameters to threads() **/
// typedef struct thread_args
// {
//    ts_hashmap_t *map; // The hahsmap
//    int randno;        // The integer for the random num
// } thread_args;

// function declarations
ts_hashmap_t *initmap(int capacity);
int get(ts_hashmap_t *map, int key);
int put(ts_hashmap_t *map, int key, int value);
int del(ts_hashmap_t *map, int key);
double lf(ts_hashmap_t *map);
void printmap(ts_hashmap_t *map);

void freemap(ts_hashmap_t *map);
ts_entry_t *getentry(int key, int value);
void addtohead(ts_hashmap_t *map, int key, int value, unsigned int arrind);
void addtoend(ts_hashmap_t *map, int key, int value, ts_entry_t *entry);
unsigned int hash(int key, int capacity);
