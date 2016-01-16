#pragma once

#include "testclass.h"
#include "perfclass.h"
#include "testregistry.h"

float randFloat() {
    return static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
}

#define SKIP return 1;
#define FAIL return -1;
#define PASS return 0;

#define IS_TRUE( BOOL ) \
  if (!(##BOOL##)) {                                            \
    cout << "@" << __FILE__ << " - " << __LINE__ << endl;       \
    return -1;                                                  \
  }



#define IS_FALSE( BOOL )                                        \
  if (##BOOL##) {                                               \
    cout << "@" << __FILE__ << " - " << __LINE__ << endl;       \
    return -1;                                                  \
  }

#define IS_EQUALS( VAL1, VAL2 )                                 \
  if ((##VAL1##)!=(##VAL2##)) {                                     \
    cout << "@" << __FILE__ << " - " << __LINE__                \
            << ": expected '" << VAL1                           \
            << "' but was '" << VAL2                            \
            << "'"<< endl;                                      \
    return -1;                                                  \
  }

#define IS_EQUALD( VAL1, VAL2, DELTA )                          \
  if ((##VAL1##)-(##VAL2##) > DELTA || (##VAL1##)-(##VAL2##) < -DELTA) {\
    cout << "@" << __FILE__ << " - " << __LINE__                \
            << ": expected '" << VAL1                           \
            << "' but was '" << VAL2                            \
            << "'"<< endl;                                      \
    return -1;                                                  \
  }

#define RUN_BEHAVIOUR_TESTS() registry.runBehaviourTests()
#define RUN_PERFORMANCE_TESTS() registry.runPerformanceTests()

#include "testdefs.h"