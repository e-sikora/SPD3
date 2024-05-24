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
    std::vector<int> end_time(machine_amount, 0);
    std::vector<int> previous_end_time(machine_amount, 0);

    for(size_t i = 0; i < list_size; i++){
        for(int j = 0; j < machine_amount; j++){
            if(j != 0){
                end_time[j] = main_list[i].getOneWorkTime(j) + std::max(previous_end_time[j], end_time[j-1]);
            }
            else{
                end_time[j] = main_list[i].getOneWorkTime(j) + previous_end_time[j];
            }
        }
    previous_end_time = end_time;
    }

    return end_time.back();
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

template<class Item>
void Problem<Item>::permutationSort(){
    std::vector<Item> orginal = main_list;
    int perm_work_time = 0;
    int best_time;
    std::vector<Item> best_order;
    bool first_iteration = true;

    do {
        perm_work_time = this->workTime();
        if (first_iteration == true) {
            best_time = perm_work_time;
            best_order.assign(main_list.begin(), main_list.end());
            first_iteration = false;
        }
        if (perm_work_time < best_time) {
            best_time = perm_work_time;
            best_order.assign(main_list.begin(), main_list.end());
        }

    } while (std::next_permutation(main_list.begin(), main_list.end()));

    std::cout << "-------------------------Full reviev-------------------------" << std::endl;
    displayResult(best_order, best_time);

    main_list = orginal;
}

template<class Item>
void Problem<Item>::johnsonAlgorithm(){
    std::vector<Item> orginal = main_list;
    std::vector<Item> first_less, second_less;

    while(!main_list.empty()){
        if(main_list.front().getOneWorkTime(0) < main_list.front().getOneWorkTime(1)){
            first_less.push_back(main_list.front());
        }
        else{
            second_less.push_back(main_list.front());
        }
        main_list.erase(main_list.begin());
    }

    std::sort(first_less.begin(), first_less.end(), [](const Item &a, const Item &b) { return a.compareByFirstWorkTime(b); });
    std::sort(second_less.begin(), second_less.end(), [](const Item &a, const Item &b) { return b.compareBySecondWorkTime(a); });

    first_less.insert(first_less.end(), second_less.begin(), second_less.end());

    main_list = first_less;

    std::cout << "----------------------Johanson Algorithm---------------------" << std::endl;
    displayResult(main_list, this->workTime());

    main_list = orginal;
}


template<class Item>
void Problem<Item>::NEHAlorithm(){
    std::vector<Item> inside_helper, best_combination;
    std::vector<Item> orginal = main_list;
    std::vector<Item> helper = main_list;
    Item temporary_item;

    std::sort(helper.begin(), helper.end(), [](const Item &a, const Item &b) { return b.compareByAllWorkTime(a); });

    main_list.clear();
    main_list.push_back(helper.front());
    helper.erase(helper.begin());
    best_combination = main_list;

    for(size_t i = 1; i < list_size; i++){
        temporary_item = helper.front();
        helper.erase(helper.begin());
        inside_helper = main_list;
        main_list = best_combination;
        int previous_work_time = 0;
        for(size_t j = 0; j < main_list.size(); j++){
            int work_time = 0;
            main_list = inside_helper;
            main_list.insert(main_list.begin() + j, temporary_item);
            work_time = this->workTime();
            if(previous_work_time == 0){ previous_work_time = work_time; }
            if(work_time <= previous_work_time){
                best_combination = main_list;
                previous_work_time = work_time;
            }
        }
    }

    main_list = best_combination;

    std::cout << "-------------------------NEH Algorithm-----------------------" << std::endl;
    displayResult(main_list, this->workTime());

    main_list = orginal;
}

template class Problem<Item<int>>;