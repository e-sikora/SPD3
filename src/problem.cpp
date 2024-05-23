#include "problem.h"

template<class Item>
Problem<Item>::Problem() : list_size(0), machine_amount(0) , main_list(){}

template<class Item>
size_t Problem<Item>::getSize() { return list_size; }

template<class Item>
size_t Problem<Item>::getMachines() { return machine_amount; }

template<class Item>
void Problem<Item>::loadFromFile(const std::string &file_name) {
    std::ifstream input_file(file_name);

    if (!input_file.is_open()) {
        std::cerr << "Can't open file: " << file_name << "!\n";
        exit(EXIT_FAILURE);
    }

    std::string temp;

    if (!std::getline(input_file, temp)) {
        std::cerr << "File " << file_name << " is empty!\n";
        exit(EXIT_FAILURE);
    } else {
        std::istringstream divide(temp);
        if(!(divide >> list_size >> machine_amount)) {
            std::cerr << "Data wasn't divided properly!\n";
            exit(EXIT_FAILURE);
        }
    }

    int id, time;
    std::vector<int> w_time(machine_amount);

    for (size_t i = 1; i <= list_size; ++i) {
        if (!std::getline(input_file, temp)) {
            std::cerr << "Failed to read sufficient data from the file!\n";
            exit(EXIT_FAILURE);
        }

        std::istringstream line_stream(temp);
        for (int j = 0; j < machine_amount; ++j) {
            if (!(line_stream >> id >> time)) {
                std::cerr << "Error in data format on line " << i + 1 << "!\n";
                exit(EXIT_FAILURE);
            }
            w_time[j] = time;
        }

        Item new_item(i, w_time);
        main_list.push_back(new_item);
    }
    
    if (main_list.size() != list_size) {
        std::cerr << "The number of tasks read does not match the declared amount!\n";
        exit(EXIT_FAILURE);
    }
    input_file.close();
}

template<class Item>
int Problem<Item>::workTime() {
    int total_work_time = 0;

    return total_work_time;
}

template<class Item>
void Problem<Item>::displayResult(std::vector<Item> order, int time){
    std::cout << "The optimal order for executing the above tasks is: ";
    for (Item &item: order) {
        std::cout << item.getId() << " ";
    }
    std::cout << std::endl << "The time needed to complete the tasks in the above order is: " << time
              << std::endl;
}

template<class Item>
void Problem<Item>::timeMeasure(std::function<void()> callback) {
    auto start = std::chrono::high_resolution_clock::now();

    callback();

    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);

    std::cout << "The above algorithm executed in: " << duration.count() << "ms" 
              << std::endl << std::endl;
}

template<class Item>
void Problem<Item>::displayAll() const {
    for (const auto &item : main_list) {
        std::cout << "ID: " << item.getId() << " Work Times: ";
        for (const auto &time : item.getWorkTime()) {
            std::cout << time << " ";
        }
        std::cout << std::endl;
    }
}

template class Problem<Item<int>>;