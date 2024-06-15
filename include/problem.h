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
    int machine_amount;             /**< The number of machines. */
    std::vector<Item> main_list;    /**< The main list of items. */

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

    /**
     * @brief Display all items in the list.
     */
    void displayAll() const;

    /**
     * @brief Perform permutation sort on the list of items.
     */
    void permutationSort();

    /**
     * @brief Apply Johnson's algorithm to the list of items.
     */
    void johnsonAlgorithm();

    /**
     * @brief Apply NEH algorithm to the list of items.
     */
    void NEHAlgorithm();

    /**
     * @brief Apply QNEH algorithm to the list of items.
     */
    void QNEHAlorithm();

    /**
     * @brief Generate a random double within a specified range.
     * @param min The minimum value.
     * @param max The maximum value.
     * @return A random double within the specified range.
     */
    double randomDouble(double min, double max);

    /**
     * @brief Calculate the objective function for a given order of items.
     * @param order The order of items.
     * @return The value of the objective function.
     */
    int objectiveFunction(const std::vector<Item>& order);

    /**
     * @brief Generate a neighbor of the given order of items.
     * @param order The current order of items.
     * @return A new order of items representing a neighbor.
     */
    std::vector<Item> generateNeighbor(const std::vector<Item>& order);

    /**
     * @brief Apply simulated annealing algorithm to the list of items.
     */
    void simulatedAnnealing();

    /**
     * @brief Check if a given order of items is in the tabu list.
     * @param order The order of items.
     * @param tabu_list The tabu list.
     * @return true If the order is in the tabu list.
     * @return false Otherwise.
     */
    bool isTabu(const std::vector<Item>& order, const std::list<std::vector<Item>>& tabu_list);

    /**
     * @brief Apply tabu search algorithm to the list of items.
     */
    void tabuSearch();
};

/**
 * @brief Overloaded equality operator for comparing vectors of items.
 *
 * @param lhs The left-hand side vector.
 * @param rhs The right-hand side vector.
 * @return true If the vectors are equal.
 * @return false Otherwise.
 */
bool operator==(const std::vector<Item<int>>& lhs, const std::vector<Item<int>>& rhs);
