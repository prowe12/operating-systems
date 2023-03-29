#include <limits.h>
#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "ts_hashmap.h"

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

  for (int i = 0; i < mymap->capacity; i++)
    mymap->table[i] = NULL;

  // Malloc all the starting entries the table points to onto the heap
  // and initialze them to entry structs?
  // for (int i = 0; i < mymap->capacity; i++)
  //   mymap->table[i] = malloc(sizeof(ts_entry_t));

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
  unsigned int arrind = hash(key, map->capacity);

  // Make sure there is something at this index
  ts_entry_t *entry = map->table[arrind];
  while (entry != NULL)
  {
    if (entry->key == key)
      return entry->value;
    entry = entry->next;
  }

  // Note: INT_MAX is a macro that specifies that an integer variable cannot store
  // any value beyond this limit.
  return INT_MAX;
}

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

/**
 * Associates a value associated with a given key.
 * @param map a pointer to the map
 * @param key a key
 * @param value a value
 * @return old associated value, or INT_MAX if the key was new
 */
int put(ts_hashmap_t *map, int key, int value)
{

  // TODO implement this: return old associated value, or INT_MAX if the key was new

  // Get the array index: cast the key into an unsigned int, assuming the int is positive
  // then modulo key by the size of the array.
  // unsigned int arrind = key % map->capacity;
  unsigned int arrind = hash(key, map->capacity);

  // Because the array element points to the head of the entry list (or NULL),
  // you can then walk the list of entries to search for a key.
  ts_entry_t *entry = map->table[arrind]; // head node

  if (entry == NULL)
  {
    addtohead(map, key, value, arrind);
    return INT_MAX;
  }

  else
  {
    // Trawl through the linked list
    int keepgoing = 1;
    while (keepgoing)
    {
      if (entry->key == key)
      {
        int oldval = entry->value;
        entry->value = value;
        // Do not increment the size (number of entries), b/c we replaced an entry
        return oldval;
      }
      // If the next entry is null, then we need to stop at this entry
      // because we will need to have it to link it to the next entry
      if (entry->next == NULL)
      {
        keepgoing = 0; // stop here
      }
      else
        entry = entry->next; // Get the next entry and keep going
    }
  }

  addtoend(map, key, value, entry);

  return INT_MAX;

  // if (entry == NULL)
  // {
  //   // First value in list; add entry
  //   printf("Adding the new key/value to the head\n");
  //   // Create the new entry and add the key, value, and next
  //   ts_entry_t *myentry = getentry(key, value);
  //   // Put the entry at the head of this item of the table
  //   map->table[arrind] = myentry;
  //   // Increment the size (number of entries)
  //   map->size += 1;
  //   return INT_MAX;
  // }
  // else
  // {
  //   printf("Trawl through the linked list\n");
  //   // Trawl through the linked list
  //   int keepgoing = 1;
  //   while (keepgoing)
  //   {
  //     if (entry->key == key)
  //     {
  //       printf("I found a matching key\n");
  //       int oldval = entry->value;
  //       entry->value = value;
  //       printf("Got it!  It was %d, and is now %d\n", oldval, entry->value);

  //       // Do not increment the size (number of entries), b/c we replaced an entry
  //       return oldval;
  //     }
  //     // If the next entry is null, then we need to stop at this entry
  //     // because we will need to have it to link it to the next entry
  //     if (entry->next == NULL)
  //     {
  //       printf("The next entry is null, so stopping\n");
  //       keepgoing = 0; // stop here
  //     }
  //     else
  //       entry = entry->next; // Get the next entry and keep going
  //   }
  // }

  // // Replace the new entry and add the key, value, and next
  // ts_entry_t *myentry = getentry(key, value);
  // // Link this up to the previous entry
  // entry->next = myentry;
  // // Increment the size (number of entries)
  // map->size += 1;

  // return INT_MAX;
}

/**
 * Removes an entry in the map
 * @param map a pointer to the map
 * @param key a key to search
 * @return the value associated with the given key, or INT_MAX if key not found
 */
int del(ts_hashmap_t *map, int key)
{
  // Get the hash for this key
  unsigned int arrind = hash(key, map->capacity);

  // Get the head and test its key
  ts_entry_t *entry = map->table[arrind];

  if (entry == NULL)
    return INT_MAX;

  if (entry->key == key)
  {
    // The key is the head node
    printf("Got the key: %d\n", key);
    int val = entry->value;
    if (entry->next == NULL)
    {
      // There is nothing after the head node, so just replace it with null
      map->table[arrind] = NULL;
      free(entry);
      return val;
    }
    printf("Replacing head with next\n");
    map->table[arrind] = entry->next;
    free(entry);
    return val;
  }

  // Trawl through the linked list
  while (entry->next != NULL)
  {
    if (entry->next->key == key)
    {
      // TODO: link up the next entry to the one after this one, or null

      ts_entry_t *tmp = entry->next;
      entry->next = entry->next->next;

      int oldval = entry->value;

      // TODO: free it
      free(tmp);
      return oldval;
    }
    entry = entry->next;
  }

  return INT_MAX;
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
  printf("In printmap with capacity %d\n", map->capacity);
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
  }

  // Free the table
  free(map->table);

  // Free the hashmap
  free(map);
}
