/*
This is the test base class. Each test, will have a number assigned to it, it will have a result 
and it will have a name. The test base class will be used to run the tests and print the results.

There will be a test handler class  
*/

#ifndef TEST_BASE_H
#define TEST_BASE_H
#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <stdexcept>

struct functionPtr{
    std::string name;
    std::string file;
    void* result;
    bool (*function)(std::string, std::string&);
    functionPtr(std::string n, std::string f, void* r, bool (*func)(std::string, std::string&))
        : name(n), file(f), result(r), function(func) {}
    bool run(){
        return function(name, file);
    }
};

class TestBase {
private:
    std::string testName;
    int testNumber;
    bool testResult;
    std::string testOutput;
    std::string expectedOutput;
public:
    TestBase(std::string name, int number)
        : testName(name), testNumber(number), testResult(false) {};

    void setTestResult(bool result) {
        testResult = result;
    }
    void setTestOutput(std::string output) {
        testOutput = output;
    }
    void setExpectedOutput(std::string output) {
        expectedOutput = output;
    }
    std::string getTestName() const {
        return testName;
    }
    int getTestNumber() const {
        return testNumber;
    }
    bool getTestResult() const {
        return testResult;
    }
    std::string getTestOutput() const {
        return testOutput;
    }
    std::string getExpectedOutput() const {
        return expectedOutput;
    }
    void setTestName(std::string name) {
        testName = name;
    }
    void setTestNumber(int number) {
        testNumber = number;
    }
    virtual void run()=0;
};

/* 
A unit test can internal pointer to a function when initialized this pointer 
is set to the function that will be run. The function will be run and the result will be compared to the expected result. 
Each function will output a bool, and will have a reference string for any errors or results to be logged. 
*/
class Unittest : public TestBase {

private:
    functionPtr testFunction;
    std:: string result_output;
public:
    Unittest(std::string name, int number, functionPtr function)
        : TestBase(name, number),  testFunction(function) {}

    void run() override {
        bool result = testFunction.run();
        setTestResult(result);
        setTestOutput(result_output);
    }

};


class IntegrationTest : public TestBase {

};

class TestHandler {
private:
    std::unordered_map<int, std::shared_ptr<TestBase>> tests;
public:
    void addTest(std::shared_ptr<TestBase> test) {
        tests[test->getTestNumber()] = test;
    }

    void runTests() {
        for (auto& test : tests) {
            test.second->run();
            std::cout << "Test " << test.first << ": " << (test.second->getTestResult() ? "Passed" : "Failed") << std::endl;
        }
    }
};
#endif // TEST_BASE_H
