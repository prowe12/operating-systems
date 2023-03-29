#include <limits.h>
#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "ts_hashmap.h"

// shared lock
pthread_mutex_t **lock;

// One lock for every element in the linked list

/**
 * Creates a new thread-safe hashmap.
 *
 * @param capacity initial capacity of the hashmap.
 * @return a pointer to a new thread-safe hashmap.
 */
ts_hashmap_t *initmap(int capacity)
{
  // malloc the hashmap on the heap
  ts_hashmap_t *mymap = malloc(sizeof(ts_hashmap_t));
  mymap->capacity = capacity;
  mymap->size = 0;

  // malloc the table based on capacity so that it's on the heap
  mymap->table = malloc(sizeof(ts_entry_t *) * capacity);

  // Set up the lock and initialize it to unlocked
  lock = (pthread_mutex_t **)malloc(sizeof(pthread_mutex_t) * capacity);

  for (int i = 0; i < mymap->capacity; i++)
  {
    mymap->table[i] = NULL;
    lock[i] = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t));
    pthread_mutex_init(lock[i], NULL); // sets it to "unlocked" state
  }

  return mymap;
}

/**
 * Obtains the value associated with the given key.
 * @param map a pointer to the map
 * @param key a key to search
 * @return the value associated with the given key, or INT_MAX if key not found
 */
int get(ts_hashmap_t *map, int key)
{
  int val = INT_MAX;
  unsigned int arrind = hash(key, map->capacity);

  pthread_mutex_lock(lock[arrind]); // try to acquire the lock

  /////////////////////////////////////////
  // << critical section >>
  // Make sure there is something at this index
  ts_entry_t *entry = map->table[arrind];
  int notdone = 1;
  while (entry != NULL && notdone == 1)
  {
    if (entry->key == key)
    {
      val = entry->value;
      notdone = 0;
    }
    else
      entry = entry->next;
  }

  // Note: INT_MAX is a macro that specifies that an integer variable cannot store
  // any value beyond this limit.
  /////////////////////////////////////////

  pthread_mutex_unlock(lock[arrind]); // release

  return val;
}

/**
 * Associates a value associated with a given key.
 * @param map a pointer to the map
 * @param key a key
 * @param value a value
 * @return old associated value, or INT_MAX if the key was new
 */
int put(ts_hashmap_t *map, int key, int value)
{

  int val = INT_MAX;

  // Get the array index: cast the key into an unsigned int, assuming the int is positive
  // then modulo key by the size of the array.
  // unsigned int arrind = key % map->capacity;
  unsigned int arrind = hash(key, map->capacity);

  pthread_mutex_lock(lock[arrind]); // try to acquire the lock

  /////////////////////////////////////////
  // << critical section >>

  // Because the array element points to the head of the entry list (or NULL),
  // you can then walk the list of entries to search for a key.
  ts_entry_t *entry = map->table[arrind]; // head node

  if (entry == NULL)
  {
    addtohead(map, key, value, arrind);
    val = INT_MAX;
  }

  else
  {
    // Trawl through the linked list
    int keepgoing = 1;
    while (keepgoing)
    {
      if (entry->key == key)
      {
        val = entry->value;
        entry->value = value;
        keepgoing = 0; // Break out of this while loop
        // Do not increment the size (number of entries), b/c we replaced an entry
      }
      // If the next entry is null, then we need to stop at this entry
      // because we will need to have it to link it to the next entry
      else if (entry->next == NULL)
      {
        addtoend(map, key, value, entry);
        keepgoing = 0; // stop here
      }
      else
        entry = entry->next; // Get the next entry and keep going
    }
  }

  /////////////////////////////////////////

  pthread_mutex_unlock(lock[arrind]); // release

  return val;
}

/**
 * Removes an entry in the map
 * @param map a pointer to the map
 * @param key a key to search
 * @return the value associated with the given key, or INT_MAX if key not found
 */
int del(ts_hashmap_t *map, int key)
{

  int val;
  unsigned int arrind = hash(key, map->capacity);

  pthread_mutex_lock(lock[arrind]); // try to acquire the lock

  /////////////////////////////////////////
  // << critical section >>
  // Get the head and test its key
  ts_entry_t *entry = map->table[arrind];

  if (entry == NULL)
    val = INT_MAX;

  else if (entry->key == key)
  {
    // The key is the head node
    val = entry->value;
    if (entry->next == NULL)
    {
      // There is nothing after the head node, so just replace it with null
      map->table[arrind] = NULL;
      free(entry);
    }
    else
    {
      map->table[arrind] = entry->next;
      free(entry);
    }
  }
  else
  {
    // Trawl through the linked list
    while (entry->next != NULL)
    {
      if (entry->next->key == key)
      {
        // TODO: link up the next entry to the one after this one, or null

        ts_entry_t *tmp = entry->next;
        entry->next = entry->next->next;

        val = entry->value;

        // TODO: free it
        free(tmp);
      }
      else
        entry = entry->next;
    }
  }

  /////////////////////////////////////////
  pthread_mutex_unlock(lock[arrind]); // release
  return val;
}

/**
 * @return the load factor of the given map
 */
double lf(ts_hashmap_t *map)
{
  return (double)map->size / map->capacity;
}

/**
 * Prints the contents of the map
 */
void printmap(ts_hashmap_t *map)
{
  for (int i = 0; i < map->capacity; i++)
  {
    printf("[%d] -> ", i);
    ts_entry_t *entry = map->table[i];
    while (entry != NULL)
    {
      printf("(%d,%d)", entry->key, entry->value);
      if (entry->next != NULL)
        printf(" -> ");
      entry = entry->next;
    }
    printf("\n");
  }
}

/**
 * Clears the map out of memory
 */
void freemap(ts_hashmap_t *map)
{
  ts_entry_t *next;

  // Free up the entries one by one
  for (int i = 0; i < map->capacity; i++)
  {
    ts_entry_t *entry = map->table[i];
    while (entry != NULL)
    {
      next = entry->next;
      free(entry);
      entry = next;
    }

    // Destroy the locks
    pthread_mutex_destroy(lock[i]);

    // Free the mallocd space for the locks
    free(lock[i]);
  }

  // Free the table
  free(map->table);

  // Free the hashmap
  free(map);

  // Free the lock
  free(lock);
}

// Helper functions

/**
 * Get a new entry
 */
ts_entry_t *getentry(int key, int value)
{

  // First create the new entry and add the key, value, and next
  ts_entry_t *myentry = malloc(sizeof(ts_entry_t));
  myentry->key = key;
  myentry->value = value;
  myentry->next = NULL;

  return myentry;
}

/**
 * Add a new entry to the head
 * @param map a pointer to the map
 * @param key a key
 * @param value a value
 * @param arrind  the index to the array
 * @return old associated value, or INT_MAX if the key was new
 */
void addtohead(ts_hashmap_t *map, int key, int value, unsigned int arrind)
{
  // Create and add an entry
  ts_entry_t *myentry = getentry(key, value);
  // Put the entry at the head of this item of the table
  map->table[arrind] = myentry;
  // Increment the size (number of entries)
  map->size += 1;
  return;
}

/**
 * Add an entry to the end of a linked list
 * @param map a pointer to the map
 * @param key a key
 * @param value a value
 * @param entry  the entry
 * @return old associated value, or INT_MAX if the key was new
 */
void addtoend(ts_hashmap_t *map, int key, int value, ts_entry_t *entry)
{
  // Replace the new entry and add the key, value, and next
  ts_entry_t *myentry = getentry(key, value);
  // Link this up to the previous entry
  entry->next = myentry;
  // Increment the size (number of entries)
  map->size += 1;
  return;
}

/**
 * Our hash function
 * @param key  a key
 * @param capacity  number of elements in the map table
 * @returns the hash key
 */
unsigned int hash(int key, int capacity)
{
  unsigned int arrind = key % capacity;
  return arrind;
}
