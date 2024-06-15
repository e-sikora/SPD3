#pragma once

#include <vector>
#include <fstream>
#include <string>
#include <sstream>
#include <algorithm>
#include <queue>
#include <chrono>
#include <functional>
#include <list>

#include "item.h"

/**
 * @brief A class representing a problem with a list of items.
 *
 * This class provides methods to manipulate a list of items,
 * including loading items from a file, performing various sorting
 * algorithms, calculating work time, and saving results to a file.
 *
 * @tparam Item The type of items in the problem.
 */
template <class Item>
class Problem
{
private:
    size_t list_size;               /**< The size of the list. */
    int machine_amount;
    std::vector<Item> main_list;

public:
    /**
     * @brief Default constructor for Problem class.
     */
    Problem();

    /**
     * @brief Get the size of the list.
     * @return The size of the list.
     */
    size_t getSize();

    /**
     * @brief Get the number of machines.
     * @return The number of machines.
     */
    size_t getMachines();

    /**
     * @brief Load items from a file into the list.
     * @param file_name The name of the file to load from.
     */
    void loadFromFile(const std::string &file_name);

    /**
     * @brief Calculate the total work time for the list of items.
     * @return The total work time.
     */
    int workTime();

    /**
     * @brief Display the result.
     * @param order The order of items.
     * @param time The total time.
     */
    void displayResult(const std::vector<Item> order, const int time);

    /**
     * @brief Measure time for a given function.
     * @param callback The function to measure time for.
     */
    void timeMeasure(std::function<void()> callback);

    /**
     * @brief Increments the size of the main list.
     */
    void listSizeIncrement() { this->list_size++; }
    /**
     * @brief Decrements the size of the main list.
     */
    void listSizeDecrement() { this->list_size--; }

    void displayAll() const;

    void permutationSort();

    void johnsonAlgorithm();

    void NEHAlorithm();

    void FNEHAlorithm();

    double randomDouble(double, double);

    int objectiveFunction(const std::vector<Item>&);

    std::vector<Item> generateNeighbor(const std::vector<Item>&);

    void simulatedAnnealing();

    bool isTabu(const std::vector<Item>&, const std::list<std::vector<Item>>&);

    void tabuSearch();
};

bool operator==(const std::vector<Item<int>>&, const std::vector<Item<int>>&);
