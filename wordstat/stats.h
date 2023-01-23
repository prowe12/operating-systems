/*
 * histo.h
 */

#ifndef STATS_H_
#define STATS_H_

// constants
#define ALPHABET_SIZE 26

// TODO: functions declarations go below
void incrementHistogram(char newstr[], int hist[]);
void printStats(int opt, int hist[], int histLen);

#endif /* STATS_H_ */
