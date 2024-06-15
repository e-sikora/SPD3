#include "item.h"

template <class T>
bool Item<T>::compareByFirstWorkTime(const Item& other) const {
    return work_time[0] < other.work_time[0];
}

template <class T>
bool Item<T>::compareBySecondWorkTime(const Item& other) const {
    return work_time[1] < other.work_time[1];
}

template <class T>
bool Item<T>::compareByAllWorkTime(const Item& other) const {
    return this->getSumWorkTime() < other.getSumWorkTime();
}

template <class T>
bool Item<T>::operator==(const Item &other) const {
    return id == other.id && work_time == other.work_time;
}

template class Item<int>;