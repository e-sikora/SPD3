#pragma once

#include <iostream>
#include <cmath>
#include <vector>
#include <numeric>

/**
 * @brief A class representing an item with attributes like ID and work time.
 *
 * @tparam T The type of the item (currently unused).
 */
template <class T>
class Item
{
private:
    int id;         ///< The unique identifier of the item.
    std::vector<int> work_time; ///< Vector containing work times.

public:
    /**
     * @brief Default constructor initializes the item with ID 0 and empty work time.
     */
    Item() : id(0), work_time() {}

    /**
     * @brief Parameterized constructor initializes the item with given ID and work time.
     *
     * @param id_s The ID of the item.
     * @param work_time_s The vector containing work times.
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
     * @brief Getter method for the work time of the item.
     *
     * @return std::vector<int> The work time of the item.
     */
    std::vector<int> getWorkTime() const { return work_time; }

    /**
     * @brief Calculates the sum of all work times.
     *
     * @return int The sum of all work times.
     */
    int getSumWorkTime() const { return std::accumulate(work_time.begin(), work_time.end(), 0); }

    /**
     * @brief Getter method for a specific work time by index.
     *
     * @param index The index of the work time to retrieve.
     * @return int The work time at the specified index.
     */
    int getOneWorkTime(int index) const { return work_time[index]; }

    /**
     * @brief Setter method for the work time of the item.
     *
     * @param work_time_s The new work time to set.
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

    /**
     * @brief Compares the first work time of this item with another item.
     *
     * @param other The other item to compare with.
     * @return true If this item's first work time is less than the other item's first work time.
     * @return false Otherwise.
     */
    bool compareByFirstWorkTime(const Item &other) const;

    /**
     * @brief Compares the second work time of this item with another item.
     *
     * @param other The other item to compare with.
     * @return true If this item's second work time is less than the other item's second work time.
     * @return false Otherwise.
     */
    bool compareBySecondWorkTime(const Item &other) const;

    /**
     * @brief Compares all work times of this item with another item.
     *
     * @param other The other item to compare with.
     * @return true If this item's work times are less than the other item's work times.
     * @return false Otherwise.
     */
    bool compareByAllWorkTime(const Item &other) const;

    /**
     * @brief Overloaded equality operator for comparing items based on their IDs.
     *
     * @param other The other item to compare with.
     * @return true If the items have the same ID.
     * @return false Otherwise.
     */
    bool operator==(const Item &other) const;
};
