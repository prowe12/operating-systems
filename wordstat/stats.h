/*
 * histo.h
 */

#ifndef STATS_H_
#define STATS_H_

// constants
#define ALPHABET_SIZE 26

// TODO: functions declarations go below
void initializeHistogram(int hist[], int histlen);
void incrementHistogram(char newstr[], int hist[], int histlen);
void printStats(int opt, int hist[], int histLen);
void printSimpleHistogram(int hist[], int histLen);
void printFrequencies(int hist[], int histLen);

#endif /* STATS_H_ */
