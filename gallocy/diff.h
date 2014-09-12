#ifndef _DIFF_H
#define _DIFF_H


#include <cstdio>
#include <cstdlib>


int diff(
  const char* mem1, size_t mem1_len, char*& output_mem1,
  const char* mem2, size_t mem2_len, char*& output_mem2);


void print_diff(
  const char* mem1, size_t mem1_len,
  const char* mem2, size_t mem2_len);


#endif
