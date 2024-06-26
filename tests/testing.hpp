#ifndef TESTING
#define TESTING

#include <iostream>
#include <string>
#include <sstream>
#include <functional>
#include <chrono>


#define START_TEST { std::cout << "Running " << __FUNCTION__ << "... "; }
#define PASS(dur) { std::cout << "and passed!" << " Took " << ((std::chrono::duration<double, std::milli>)(dur)).count() << " milliseconds. B-)" << std::endl; return true; }
#define AFAIL(x, y) { std::cerr << __FUNCTION__ << " failed... expected " << x << " but got " << y << ". :-(" << std::endl; return false; }
#define TFAIL(x, y) { std::cerr << "but failed... took " << x << " milliseconds but should take at most " << y << " milliseconds. :-(" << std::endl; return false; }


#endif