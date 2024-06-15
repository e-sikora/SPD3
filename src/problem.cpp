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

template<class Item>
void Problem<Item>::FNEHAlorithm() {
    std::vector<Item> orginal = main_list;
    std::vector<Item> helper = main_list;

    int front_value;
    int back_value;

    std::sort(helper.begin(), helper.end(), [](const Item &a, const Item &b) { return b.compareByAllWorkTime(a); });

    main_list.clear();
    main_list.push_back(helper.front());
    helper.erase(helper.begin());

    while(!helper.empty()){
        std::vector<std::vector<int>> front(this->getMachines(), std::vector<int>(main_list.size()));
        for (size_t i = 0; i < main_list.size(); i++) {
            for (size_t j = 0; j < this->getMachines(); j++) {

                if (j == 0 && i == 0) {
                    front_value = main_list[i].getOneWorkTime(j);
                } else if (j != 0 && i == 0) {
                    front_value = main_list[i].getOneWorkTime(j) + front[j - 1][i];
                } else if (j == 0 && i != 0) {
                    front_value = main_list[i].getOneWorkTime(j) + front[j][i - 1];
                } else {
                    front_value = std::max(front[j][i - 1], front[j - 1][i]) + main_list[i].getOneWorkTime(j);
                }

                front[j][i] = front_value;
            }
        }

        std::vector<std::vector<int>> back(this->getMachines(), std::vector<int>(main_list.size()));
        for (int i = int(main_list.size()) - 1; i >= 0; i--) {
            for (int j = int(this->getMachines()) - 1; j >= 0; j--) {
                if (j == int(this->getMachines()) - 1 && i == int(main_list.size()) - 1) {
                    back_value = main_list[i].getOneWorkTime(j);
                } else if (j != int(this->getMachines()) - 1 && i == int(main_list.size()) - 1) {
                    back_value = main_list[i].getOneWorkTime(j) + back[j + 1][i];
                } else if (j == int(this->getMachines()) - 1 && i != int(main_list.size()) - 1) {
                    back_value = main_list[i].getOneWorkTime(j) + back[j][i + 1];
                } else {
                    back_value = std::max(back[j][i + 1], back[j + 1][i]) + main_list[i].getOneWorkTime(j);
                }
                
                back[j][i] = back_value;
            }
        }

        std::vector<int> temp (this->getMachines());
        std::vector<int> ans (this->getMachines());
        std::vector<int> ans_tab;
        Item top_item = helper.front();
        helper.erase(helper.begin());

        for(size_t i = 1; i <= main_list.size() + 1; i++){
            for(size_t j = 0; j < temp.size(); j++){
                if (j == 0 && i == 0) {
                    temp[j] = top_item.getOneWorkTime(j);
                } else if (j != 0 && i == 0) {
                    temp[j] = top_item.getOneWorkTime(j) + temp[j - 1];
                } else if (j == 0 && i != 0) {
                    temp[j] = top_item.getOneWorkTime(j) + front[j][i - 1];
                } else {
                    temp[j] = std::max(front[j][i - 1], temp[j-1]) + top_item.getOneWorkTime(j);
                } 
            
                ans[j] = temp[j] + back[j][i];
            }

            ans_tab.push_back(*std::max_element(ans.begin(), ans.end()));
        }

        auto min_iter = std::min_element(ans_tab.begin(), ans_tab.end());
        int min_index = std::distance(ans_tab.begin(), min_iter);

        main_list.insert(main_list.begin() + min_index, top_item);
    }

    std::cout << "------------------------FNEH Algorithm-----------------------" << std::endl;
    displayResult(main_list, this->workTime());

    main_list = orginal;
}

template<class Item>
double Problem<Item>::randomDouble(double min, double max) {
    return min + (double)rand() / RAND_MAX * (max - min);
}

template<class Item>
int Problem<Item>::objectiveFunction(const std::vector<Item>& solution) {
    std::vector<int> end_time(machine_amount, 0);
    std::vector<int> previous_end_time(machine_amount, 0);

    for(size_t i = 0; i < solution.size(); i++){
        for(int j = 0; j < machine_amount; j++){
            if(j != 0){
                end_time[j] = solution[i].getOneWorkTime(j) + std::max(previous_end_time[j], end_time[j-1]);
            }
            else{
                end_time[j] = solution[i].getOneWorkTime(j) + previous_end_time[j];
            }
        }
    previous_end_time = end_time;
    }

    return end_time.back();
}

template<class Item>
std::vector<Item> Problem<Item>::generateNeighbor(const std::vector<Item>& current_solution) {
    std::vector<Item> new_solution = current_solution;
    int i = rand() % new_solution.size();
    int j = rand() % new_solution.size();
    std::swap(new_solution[i], new_solution[j]);
    return new_solution;
}

template<class Item>
void Problem<Item>::simulatedAnnealing() {
    std::vector<Item> orginal = main_list;
    srand(time(NULL));
    double temperature = 1000.0;
    double cooling_rate = 0.003;
    std::vector<Item> current_solution = main_list;
    std::vector<Item> best_solution = current_solution;
    
    while (temperature > 1) {
        std::vector<Item> new_solution = generateNeighbor(current_solution);
        double current_energy = objectiveFunction(current_solution);
        double neighbor_energy = objectiveFunction(new_solution);
        
        if (neighbor_energy < current_energy || exp((current_energy - neighbor_energy) / temperature) > randomDouble(0, 1)) {
            current_solution = new_solution;
        }
        
        if (objectiveFunction(current_solution) < objectiveFunction(best_solution)) {
            best_solution = current_solution;
        }
        
        temperature *= 1 - cooling_rate;
    }
    
    main_list = best_solution;

    std::cout << "----------------------Simulated Annealing--------------------" << std::endl;
    displayResult(main_list, this->workTime());

    main_list = orginal;
}

template<class Item>
bool Problem<Item>::isTabu(const std::vector<Item>& solution, const std::list<std::vector<Item>>& tabu_list) {
    for (const auto& tabu_solution : tabu_list) {
        if (solution == tabu_solution) {
            return true;
        }
    }
    return false;
}

bool operator==(const std::vector<Item<int>>& lhs, const std::vector<Item<int>>& rhs) {
    if (lhs.size() != rhs.size()) {
        return false;
    }
    for (size_t i = 0; i < lhs.size(); ++i) {
        if (!(lhs[i] == rhs[i])) {
            return false;
        }
    }
    return true;
}

template<class Item>
void Problem<Item>::tabuSearch() {
    std::vector<Item> orginal = main_list;
    srand(time(NULL));
    size_t tabu_tenure = 5;
    std::list<std::vector<Item>> tabu_list;
    std::vector<Item> current_solution = main_list;
    std::vector<Item> best_solution = current_solution;
    int iteration = 0;
    int max_iterations = 100;

    while (iteration < max_iterations) {
        std::vector<Item> best_neighbor;
        double best_neighbor_cost = std::numeric_limits<double>::max();

        for (size_t i = 0; i < current_solution.size(); ++i) {
            for (size_t j = i + 1; j < current_solution.size(); ++j) {
                std::vector<Item> neighbor = current_solution;
                std::swap(neighbor[i], neighbor[j]);
                double neighbor_cost = objectiveFunction(neighbor);

                if (!isTabu(neighbor, tabu_list) && neighbor_cost < best_neighbor_cost) {
                    best_neighbor = neighbor;
                    best_neighbor_cost = neighbor_cost;
                }
            }
        }

        current_solution = best_neighbor;

        if (objectiveFunction(current_solution) < objectiveFunction(best_solution)) {
            best_solution = current_solution;
        }

        tabu_list.push_back(current_solution);
        if (tabu_list.size() > tabu_tenure) {
            tabu_list.pop_front();
        }

        ++iteration;
    }

    main_list = best_solution;

    std::cout << "--------------------------Tabu Search------------------------" << std::endl;
    displayResult(main_list, this->workTime());

    main_list = orginal;
}



template class Problem<Item<int>>;