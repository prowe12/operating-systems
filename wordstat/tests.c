#include <stdio.h>
#include <assert.h>

#include "defs.h"
#include "stats.h"
#include "menu.h"

// Reminder of how to compile:
// gcc -Wall -g -o tests tests.c stats.c menu.c

int main(void)
{
    printf("Testing started\n");

    // Test of initializing the histogram
    int histlen = 26;
    int histogram[histlen];
    int expectedHist[] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    initializeHistogram(histogram, histlen);
    for (int i = 0; i < histlen; i++)
    {
        assert(histogram[i] == expectedHist[i]);
    }

    // Test increment histogram
    // int MAXSTRLEN = 128;
    char buf[] = "APPle caT\n";
    incrementHistogram(buf, histogram, ALPHABET_SIZE);
    //                     a  b  c  d  e  f  g  h  i  j  k  l  m  n  o  p  q  r  s  t  u  v  w  x  y  z
    int expectedHist1[] = {2, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 2, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0};
    for (int i = 0; i < histlen; i++)
    {
        assert(histogram[i] == expectedHist1[i]);
    }

    // Test increment histogram
    char buf2[] = "orangE goat\n";
    incrementHistogram(buf2, histogram, ALPHABET_SIZE);
    //                     a  b  c  d  e  f  g  h  i  j  k  l  m  n  o  p  q  r  s  t  u  v  w  x  y  z
    int expectedHist2[] = {4, 0, 1, 0, 2, 0, 2, 0, 0, 0, 0, 1, 0, 1, 2, 2, 0, 1, 0, 2, 0, 0, 0, 0, 0, 0};
    for (int i = 0; i < histlen; i++)
    {
        assert(histogram[i] == expectedHist2[i]);
    }

    // Test increment histogram
    char buf3[] = "greenish blue fish\n";
    incrementHistogram(buf3, histogram, ALPHABET_SIZE);
    //                     a  b  c  d  e  f  g  h  i  j  k  l  m  n  o  p  q  r  s  t  u  v  w  x  y  z
    int expectedHist3[] = {4, 1, 1, 0, 5, 1, 3, 2, 2, 0, 0, 2, 0, 2, 2, 2, 0, 2, 2, 2, 1, 0, 0, 0, 0, 0};
    for (int i = 0; i < histlen; i++)
    {
        assert(histogram[i] == expectedHist3[i]);
    }

    // Test vowel and consant frequencies
    // TODO: to test this, need to modify function so it returns a string
    int opt = 1;
    printStats(opt, histogram, ALPHABET_SIZE);

    // TODO: Test printing histogram
    // TODO: to test this, need to modify function so it returns a string

    // TODO: Test entering more strings
    // TODO: Remaining tests

    printf("Testing completed\n");

    return 0;
}