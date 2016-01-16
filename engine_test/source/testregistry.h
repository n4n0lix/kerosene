#pragma once

#include <memory>
        using std::shared_ptr;

#include <vector>
        using std::vector;

#include <iostream>
        using std::cout;
        using std::endl;

class TestRegistry
{
public:
    void reg(TestClass* instance)
    {
        _tests.push_back(instance);
    }

    void reg(PerfClass* instance)
    {
        _perfs.push_back(instance);
    }

    void runBehaviourTests() {

        cout << "START BEHAVIOUR TESTS ..." << endl;
        cout << "-------------------------" << endl << endl;

        int numTests     = _tests.size();
        int passedTests  = 0;
        int skippedTests = 0;
        int failedTests  = 0;

        for (auto instance : _tests) {
            int result = instance->exec();
            switch (result) {
                case 0:
                    passedTests++;
                    cout << "\tPASSED: " << instance->name() << endl;
                    break;
                case -1:
                    failedTests++;
                    cout << "\tFAILED: " << instance->name() << endl;
                    break;
                case 1:
                    skippedTests++;
                    cout << "\tSKIPPED: " << instance->name() << endl;
                    break;
            }
        }

        cout << endl << "----------------------------------------------------------------------------" << endl;
        cout << "Behaviour tests finished: " << passedTests << " passed, " << skippedTests << " skipped, " << failedTests << " failed" << endl;
        cout << "============================================================================" << endl << endl << endl;
    }

    void runPerformanceTests() {

        cout << "START PERFORMANCE TESTS ..." << endl;
        cout << "---------------------------" << endl << endl;

        for (auto instance : _perfs) {
            instance->exec();
        }

        cout << endl << "----------------------------------------------------------------------------" << endl;
        cout << "Performance tests finished!" << endl;
        cout << "============================================================================" << endl << endl << endl;
    }
private:
    vector<TestClass*> _tests;
    vector<PerfClass*> _perfs;
} registry;