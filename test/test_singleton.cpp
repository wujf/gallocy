#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "gtest/gtest.h"

#include "libgallocy.h"


class SingletonHeapTests: public ::testing::Test {
  protected:
    virtual void TearDown() {
      __reset_memory_allocator();
    }
};


TEST_F(SingletonHeapTests, ZeroMalloc) {
  void* ptr = NULL;
  ptr = local_internal_memory.malloc(0);
  ASSERT_NE(ptr, (void*) NULL);
}


TEST_F(SingletonHeapTests, SimpleMalloc) {
  char* ptr = (char*) local_internal_memory.malloc(sizeof(char) * 16);
  ASSERT_NE(ptr, (void *) NULL);
  memset(ptr, 'A', 15);
  ptr[15] = 0;
  ASSERT_EQ(strcmp(ptr, "AAAAAAAAAAAAAAA"), 0);
  local_internal_memory.free(ptr);
}


TEST_F(SingletonHeapTests, SmallMalloc) {
  char* ptr = (char*) local_internal_memory.malloc(1);
  ASSERT_TRUE(ptr != NULL);
  ptr[0] = 'A';
  ASSERT_EQ(*ptr, 'A');
}


TEST_F(SingletonHeapTests, MediumMalloc) {
  int sz = 4312;
  char* ptr = (char*) local_internal_memory.malloc(sz);
  ASSERT_TRUE(ptr != NULL);
  for (int i = 0; i < sz; i++)
    ptr[i] = 33 + (i % 126 - 33);
  for (int i = 0; i < sz; i++)
    ASSERT_EQ(ptr[i], 33 + (i % 126 - 33));
  local_internal_memory.free(ptr);
}


TEST_F(SingletonHeapTests, BigMalloc) {
  int sz =  4096 * 16;
  char* ptr = (char*) local_internal_memory.malloc(sz);
  ASSERT_TRUE(ptr != NULL);
  for (int i = 0; i < sz; i++)
    ptr[i] = 33 + (i % 126 - 33);
  for (int i = 0; i < sz; i++)
    ASSERT_EQ(ptr[i], 33 + (i % 126 - 33));
  local_internal_memory.free(ptr);
}


TEST_F(SingletonHeapTests, ManyMalloc) {
  char* ptr;
  for (int i = 0; i < 4096; i++) {
    ptr = (char*) local_internal_memory.malloc(32);
    ASSERT_TRUE(ptr != NULL);
    for (int j = 0; j < 32; j++)
      ptr[j] = 'A';
    for (int j = 0; j < 32; j++)
      ASSERT_EQ(ptr[j], 'A');
    local_internal_memory.free(ptr);
  }
}


TEST_F(SingletonHeapTests, ReuseAllocation) {
  char* ptr1 = NULL;
  char* ptr2 = NULL;

  ptr1 = (char*) local_internal_memory.malloc(64);
  memset(ptr1, 'A', 64);
  local_internal_memory.free(ptr1);

  ptr2 = (char*) local_internal_memory.malloc(16);
  memset(ptr2, 'B', 16);
  ASSERT_EQ(ptr1, ptr2);
}
