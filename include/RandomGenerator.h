#ifndef RANDOMGENERATOR_H_
#define RANDOMGENERATOR_H_

#include <iostream>
#include <vector>
#include <random>
#include <exception>
#include <typeinfo>
#include <string>

using namespace std;

template<typename T>
class RandomGenerator
{
private:
    vector<T> randoms;
public:
    explicit RandomGenerator<T>(uint32_t size, T rangeLeft, T rangeRight)
    {
        std::default_random_engine dr(time(NULL));
        if (typeid(T).name() == typeid(int).name()) {
            std::uniform_int_distribution<T> uniRand(rangeLeft, rangeRight);
            this->randoms.clear();
            for (uint32_t i = 0u; i < size; i++) {
                this->randoms.push_back(uniRand(dr));
            }
        }
        else if (typeid(T).name() == typeid(float).name() or typeid(T).name() == typeid(double).name()) {
            std::uniform_real_distribution<> realRand(rangeLeft, rangeRight);
            this->randoms.clear();
            for (uint32_t i = 0u; i < size; i++) {
                this->randoms.push_back(realRand(dr));
            }
        }
        else {
            // throw std::bad_typeid("unkown type for random engine!");
            throw std::string("unkown type for random engine!");
        }
    }
    virtual ~RandomGenerator<T>() {}
public:
    const vector<T>& getRandoms() const
    {
        return this->randoms;
    }
    void showRandoms() const
    {
        for (auto &item : this->randoms) {
            std::cout<<item<<" ";
        }
        std::endl(std::cout);
    }
};

#endif // RandomGenerator.h
