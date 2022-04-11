#include <iostream>
#include <algorithm>
#include <vector>
#include <map>
#include <fstream>
#include <utility>

template<typename T>
class Tests{
public:
    Tests(std::string s) {
        std::fstream file;
        file.open(s);
        if (file.is_open()) {
            int kol_elem;
            file >> kol_elem;
            arr_not_sorted.resize(kol_elem);
            for (size_t i = 0; i < kol_elem; i++) {
                file >> arr_not_sorted[i];
            }
        } else {
            std::cerr << "error of open file\n";
            return;
        }
        file.close();
    }

    void all_algorithms() {
        std::map<double, std::string> time;

        time.insert(std::make_pair(sort_standard(arr_not_sorted), "sort_standard"));
        std::cout<<"sort_standard_done\n";
        time.insert(std::make_pair(heap_sort(arr_not_sorted), "heap_sort"));
        std::cout<<"heap_sort_done\n";
        time.insert(std::make_pair(insert_sort(arr_not_sorted), "insert_sort"));
        std::cout<<"insert_sort_done\n";
        time.insert(std::make_pair(selection_sort(arr_not_sorted), "selection_sort"));
        std::cout<<"selection_sort_done\n";
        time.insert(std::make_pair(shell_sort(arr_not_sorted), "shell_sort"));
        std::cout<<"shell_sort_done\n";
         time.insert(std::make_pair(bubble_sort(arr_not_sorted), "bubble_sort"));
        std::cout<<"bubble_sort_done\n";
        std::ofstream file;
        file.open("file.txt");
        for (const auto cur: time) {
            file<<cur.first << ' ' << cur.second << '\n';
            std::cout << cur.first << ' ' << cur.second << '\n';
        }
        file.close();
    }

private:
    std::vector<T> arr_not_sorted;
    double bubble_sort(std::vector<T> arr) {
        const clock_t start = clock();
        bool is_sorted = false;
        while (!is_sorted) {
            is_sorted = true;
            for (int i = 0; i < arr.size() - 1; i++)
                if (arr[i] > arr[i + 1]) {
                    is_sorted = false;
                    std::swap(arr[i], arr[i + 1]);
                }
        }
        return static_cast<double>(clock() - start) / CLOCKS_PER_SEC;
    }
    double insert_sort(std::vector<T> arr) {
        const clock_t start = clock();
        for (int i = 1; i < arr.size(); i++) {
            bool sorted = false;
            for (int j = i; (j > 0) && (!sorted); j--)
                if (arr[j] < arr[j - 1])
                    std::swap(arr[j], arr[j - 1]);
                else
                    sorted = true;
        }
        return static_cast<double>(clock() - start) / CLOCKS_PER_SEC;
    }
    double selection_sort(std::vector<T> arr) {
        const clock_t start = clock();
        for (int i = 0; i < arr.size(); i++) {
            int j = i;
            int min = j;
            bool checked = false;
            for (j = j + 1; j < arr.size(); j++)
                if (arr[j] < arr[min]) {
                    min = j;
                    checked = true;
                }
            if (checked) {
                checked = false;
                std::swap(arr[min], arr[i]);
            }
        }
        return static_cast<double>(clock() - start) / CLOCKS_PER_SEC;
    }
    double sort_standard(std::vector<T> arr) {
        const clock_t start = clock();
        sort(arr.begin(), arr.end());
        return static_cast<double>(clock() - start) / CLOCKS_PER_SEC;
    }
    double shell_sort(std::vector<T> arr){
        const clock_t start = clock();
        int t= arr.size()/2;
        bool sorted=false;
        while(!sorted)
        {
            sorted=true;
            for(size_t i=0; i<arr.size(); i++)
                if (i + t < arr.size()) {
                    if (arr[i] > arr[i + t]) {
                        std::swap(arr[i], arr[i + t]);
                        sorted = false;
                    } else if (t != 1) {
                        t--;
                        sorted = false;
                    }
                }
        }
        return static_cast<double>(clock() - start) / CLOCKS_PER_SEC;
    }
    double heap_sort(std::vector<T> arr) {
        const clock_t start = clock();
        std::make_heap(arr.begin(), arr.end());
        for (auto i = arr.end(); i != arr.begin(); --i) {
            std::pop_heap(arr.begin(), i);
        }
        return static_cast<double>(clock() - start) / CLOCKS_PER_SEC;
    }

};


int main()
{
    Tests<int> g("1000000.10.100.txt");
    g.all_algorithms();
};