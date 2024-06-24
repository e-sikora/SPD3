// Executables must have the following defined if the library contains
// doctest definitions. For builds with this disabled, e.g. code shipped to
// users, this can be left out.
#ifdef ENABLE_DOCTEST_IN_LIBRARY
#define DOCTEST_CONFIG_IMPLEMENT
#include "doctest/doctest.h"
#endif

#include <iostream>

#include "problem.h"


/**
 * @brief Main function of the program.
 *
 * @param argc Number of command-line arguments.
 * @param argv Array of command-line arguments.
 * @return int Return status of the program.
 */
int main(int argc, char *argv[])
{
  if (argc != 2)
  {
    std::cout << "Incorrect program invocation! The program terminates!" << std::endl;
    exit(EXIT_FAILURE);
  }

  Problem<Item<int>> problem;
  problem.loadFromFile(argv[1]);


  //problem.displayAll();

  //problem.timeMeasure([&]() { problem.permutationSort(); });
  problem.timeMeasure([&]() { problem.NEHAlgorithm(); });
  problem.timeMeasure([&]() { problem.QNEHAlorithm(); });
  problem.timeMeasure([&]() { problem.simulatedAnnealing(); });
  problem.timeMeasure([&]() { problem.tabuSearch(); });
  if(problem.getMachines() == 2) {
    problem.timeMeasure([&]() { problem.johnsonAlgorithm(); });
  }
  
  return 0;
}
