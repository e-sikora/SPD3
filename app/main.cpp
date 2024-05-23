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
    std::cout << "Błędne wywołanie programu! Program kończy działanie!" << std::endl;
    exit(EXIT_FAILURE);
  }

  Problem<Item<int>> problem;
  problem.loadFromFile(argv[1]);


  problem.displayAll();
  //Instance<Problem<Item<int>>> instance(problem.getMachines());

  //instance.timeMeasure([&]() { instance.LSA(problem); });
  //instance.timeMeasure([&]() { instance.LPT(problem); });
  //instance.timeMeasure([&]() { instance.fullReview(problem, true); });
  //instance.timeMeasure([&]() { instance.algorithmWrongPTAS(problem); });
  // instance.timeMeasure([&]() { instance.algorithmPTAS(problem); });
  // if(problem.getMachines()==2) {
  //   instance.timeMeasure([&]() { instance.dynamicProgramingTwoMachines(problem, true, false); });
  //   instance.timeMeasure([&]() { instance.algorithmFPTAS(problem); });
  // }
  
  return 0;
}
