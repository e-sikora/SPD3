#include "problem.h"

template<class Item>
Problem<Item>::Problem() : list_size(0), machine_amount(0) {}

template<class Item>
size_t Problem<Item>::getSize() { return list_size; }

template<class Item>
size_t Problem<Item>::getMachines() { return machine_amount; }

template<class Item>
void Problem<Item>::loadFromFile(const std::string &file_name) {
    std::ifstream input_file(file_name);

    if (!input_file.is_open()) {
        std::cerr << "Nie udało się otworzyć pliku: " << file_name << "!\n";
        exit(EXIT_FAILURE);
    }

    // std::string temp;

    // if (!std::getline(input_file, temp)) {
    //     std::cerr << "Plik " << file_name << " jest pusty!\n";
    //     exit(EXIT_FAILURE);
    // } else {
    //     std::istringstream divide(temp);
    //     if(!(divide >> list_size >> machine_amount)) {
    //         std::cerr << "Dane zostały źle podzielone!\n";
    //         exit(EXIT_FAILURE);
    //     }
    // }

    // Item new_item;
    // int counter = 0, o_time, w_time, i_time;
    // while (std::getline(input_file, temp)) {
    //     counter++;
    //     std::istringstream divide(temp);
    //     if (divide >> o_time >> w_time >> i_time) {
    //         new_item = Item(counter, o_time, w_time, i_time);
    //     } else {
    //         std::cerr << "Dane zostały źle podzielone!\n";
    //         exit(EXIT_FAILURE);
    //     }
    //     main_list.push_back(new_item);
    // }
    // if (counter != list_size) {
    //     std::cerr << "Liczba wczytanych zadań nie zgadza się z zadeklarowaną ilośćią!\n";
    //     exit(EXIT_FAILURE);
    // }
    input_file.close();
}

template<class Item>
int Problem<Item>::workTime() {
    int total_work_time = 0;

    return total_work_time;
}

template<class Item>
void Problem<Item>::displayResult(std::vector<Item> order, int time){
    std::cout << "Optymalna kolejność wykonywania powyższych zadań jest dla ułożenia: ";
    for (Item &item: order) {
        std::cout << item.getId() << " ";
    }
    std::cout << std::endl << "Czas potrzebny na wykonanie zadania w powyższej kolejności to: " << time
              << std::endl;
}

template<class Item>
void Problem<Item>::timeMeasure(std::function<void()> callback) {
    auto start = std::chrono::high_resolution_clock::now();

    callback();

    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);

    std::cout << "Powyższy algorytm wykonywał się: " << duration.count() << "ms" 
              << std::endl << std::endl;
}

template class Problem<Item<int>>;