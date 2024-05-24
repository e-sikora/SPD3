#pragma once

#include <iostream>
#include <cmath>
#include <vector>
#include <numeric>

/**
 * @brief A class representing an item with attributes like ID, occurrence time,
 * work time, and idle time.
 *
 * @tparam T The type of the item (currently unused).
 */
template <class T>
class Item
{
private:
    int id;         ///< The unique identifier of the item.
    std::vector<int> work_time;

public:
    /**
     * @brief Default constructor initializing all attributes to zero.
     */
    Item() : id(0), work_time() {}

    /**
     * @brief Parameterized constructor to initialize the item with provided values.
     *
     * @param id_s The ID of the item.
     * @param occur_time_s The occurrence time of the item.
     * @param work_time_s The work time required for the item.
     * @param idle_time_s The idle time associated with the item.
     */
    Item(int id_s, std::vector<int> work_time_s)
    {
        id = id_s;
        work_time = work_time_s;
    }

    /**
     * @brief Getter method for the ID of the item.
     *
     * @return int The ID of the item.
     */
    int getId() const { return id; }

    /**
     * @brief Getter method for the work time required for the item.
     *
     * @return int The work time required for the item.
     */
    std::vector<int> getWorkTime() const { return work_time; }

    int getSumWorkTime() const { return std::accumulate(work_time.begin(), work_time.end(), 0); }

    int getOneWorkTime(int index) const { return work_time[index]; }

    /**
     * @brief Getter method for the idle time associated with the item.
     *
     * @return int The idle time associated with the item.
     */
    void setWorkTime(std::vector<int> work_time_s) { work_time = work_time_s; }

    /**
     * @brief Overloaded less than operator for comparing items based on their IDs.
     *
     * @param other The other item to compare with.
     * @return true If this item's ID is less than the other item's ID.
     * @return false Otherwise.
     */
    bool operator<(const Item &other) const { return id < other.id; }

    bool compareByFirstWorkTime(const Item &other) const;

    bool compareBySecondWorkTime(const Item &other) const;

    bool compareByAllWorkTime(const Item &other) const;
};

#ifdef ENABLE_DOCTEST_IN_LIBRARY

#include "doctest/doctest.h"

TEST_CASE("Item class")
{
    // // Default constructor
    // Item<int> defaultItem;
    // CHECK(defaultItem.getId() == 0);
    // CHECK(defaultItem.getOccurTime() == 0);
    // CHECK(defaultItem.getWorkTime() == 0);
    // CHECK(defaultItem.getIdleTime() == 0);

    // // Parameterized constructor
    // Item<int> item1(1, 10, 5, 2);
    // CHECK(item1.getId() == 1);
    // CHECK(item1.getOccurTime() == 10);
    // CHECK(item1.getWorkTime() == 5);
    // CHECK(item1.getIdleTime() == 2);

    // // Comparison operators
    // Item<int> item2(2, 15, 3, 7);
    // CHECK(item1 < item2);
    // CHECK(item1.compareByOccurTime(item2));
    // CHECK(item1.compareByIdleTime(item2));
}

#endif