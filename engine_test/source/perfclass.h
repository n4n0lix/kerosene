#pragma once

#include <string>
        using std::string;

#include <chrono>
        using namespace std::chrono;
        using std::chrono::high_resolution_clock;

#include <iostream>
        using std::cout;
        using std::endl;

#pragma optimize( "", off )
int64_t measureRawForLoop(int64_t iterations) {
    // 1# Preparations
    time_point<high_resolution_clock> loop_start;
    time_point<high_resolution_clock> loop_end;

    // 2# Measuring
    loop_start = high_resolution_clock::now();
    for (int64_t i = 0; i < iterations; i++) {}
    loop_end = high_resolution_clock::now();

    // 3# Calculation
    auto duration = duration_cast<nanoseconds>(loop_end - loop_start);
    return duration.count();
}
#pragma optimize( "", on )

class PerfClass
{
public:
    virtual void    run() = 0;
    //virtual void    overheadRun() = 0;
    virtual string  name() = 0;
    virtual int64_t iterations() = 0;
    void   exec() {

        int64_t _iterations = iterations();
        
        // 1# Measure time the raw loop takes
        int64_t time_forloop = measureRawForLoop(_iterations);
        
        //// 2# Measure overhead
        //time_point<high_resolution_clock> overhead_start;
        //time_point<high_resolution_clock> overhead_end;

        //overhead_start = high_resolution_clock::now();
        //for (int64_t i = 0; i < _iterations; i++) { overheadRun(); } // This becomes inlined
        //overhead_end = high_resolution_clock::now();
        //int64_t time_overhead = duration_cast<nanoseconds>(overhead_end - overhead_start).count();

        // 3# Measure performance
        time_point<high_resolution_clock> loop_start;
        time_point<high_resolution_clock> loop_end;

        loop_start = high_resolution_clock::now();
        for (int64_t i = 0; i < _iterations; i++) { run(); } // This becomes inlined
        loop_end = high_resolution_clock::now();

        // 3# Calculate result
        int64_t time_func = duration_cast<nanoseconds>(loop_end - loop_start).count();
        //cout << "TIME:\t\t" << time_func << endl;
        //cout << "FOR:\t\t" << time_forloop << endl;
        //cout << "OVERHEAD:\t" << time_overhead << endl;

        time_func = time_func /*- time_overhead*/ - time_forloop;
        cout << "\t" << name() << " took " << (time_func / _iterations) << " ns per iteration." << endl;
    }
};

#define PERFORMANCE( NAME, ITERATIONS )                 \
  class NAME : public PerfClass                         \
  {                                                     \
    public:                                             \
      NAME##() { registry.reg(this); }                  \
      virtual void run() override;                      \
      virtual string name() override;                   \
      virtual int64_t iterations() override;            \
  } NAME##Instance;                                     \
  string NAME##::name() { return #NAME##; }             \
  int64_t NAME##::iterations() { return ITERATIONS##; } \
  __forceinline void NAME##::run()

//virtual void overheadRun() override;              


//#define PERFORMANCE_OVERHEAD( NAME )
//  __forceinline void NAME##::overheadRun()