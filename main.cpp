#include <iostream>
#include <algorithm>
#include <vector>
#include <map>
#include <fstream>
#include <utility>
#include <iomanip>
#include <chrono>


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
        }
        else {
            std::cerr << "error of open file\n";
            return;
        }
        file.close();
        line_plus_time="time_" + s;
    }

    void all_algorithms() {
        std::multimap<double, std::string> time;
        time.insert(std::make_pair(sort_standard(arr_not_sorted), "sort_standard"));
        time.insert(std::make_pair(selection_sort(arr_not_sorted), "selection_sort"));
        time.insert(std::make_pair(shell_sort(arr_not_sorted), "shell_sort"));
        time.insert(std::make_pair(heap_sort(arr_not_sorted), "heap_sort"));
        time.insert(std::make_pair(insert_sort(arr_not_sorted), "insert_sort"));
        time.insert(std::make_pair(bubble_sort(arr_not_sorted), "bubble_sort"));

        std::ofstream file;
        std::cout << time.size() << '\n';

        file.open(line_plus_time);
        for (const auto cur: time) {
            file<<std::fixed<<std::setprecision(1)<<cur.first << ' ' << cur.second << '\n';
            std::cout<<std::fixed <<std::setprecision(1)<< cur.first << ' ' << cur.second << '\n';
        }
        file.close();
    }

private:
    std::vector<T> arr_not_sorted;
    std::string line_plus_time;
    using time_=std::chrono::microseconds;
    double bubble_sort(std::vector<T> arr) {
        auto begin =std::chrono::steady_clock::now();
        bool is_sorted = false;
        while (!is_sorted) {
            is_sorted = true;
            for (int i = 0; i < arr.size() - 1; i++)
                if (arr[i] > arr[i + 1]) {
                    is_sorted = false;
                    std::swap(arr[i], arr[i + 1]);
                }
        }
        auto end = std::chrono::steady_clock::now();
        return duration_cast<time_>(end - begin).count();

    }
    double insert_sort(std::vector<T> arr) {
        auto begin =std::chrono::steady_clock::now();
        for (int i = 1; i < arr.size(); i++) {
            bool sorted = false;
            for (int j = i; (j > 0) && (!sorted); j--)
                if (arr[j] < arr[j - 1])
                    std::swap(arr[j], arr[j - 1]);
                else
                    sorted = true;
        }
        auto end = std::chrono::steady_clock::now();
        return duration_cast<time_>(end - begin).count();
    }
    double selection_sort(std::vector<T> arr) {
        auto begin =std::chrono::steady_clock::now();
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
        auto end = std::chrono::steady_clock::now();
        return duration_cast<time_>(end - begin).count();
    }
    double sort_standard(std::vector<T> arr) {
        auto begin =std::chrono::steady_clock::now();
        sort(arr.begin(), arr.end());
        auto end = std::chrono::steady_clock::now();
        return duration_cast<time_>(end - begin).count();
    }
    double shell_sort(std::vector<T> arr){
        auto begin =std::chrono::steady_clock::now();
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
        auto end = std::chrono::steady_clock::now();
        return duration_cast<time_>(end - begin).count();
    }
    double heap_sort(std::vector<T> arr) {
        auto begin =std::chrono::steady_clock::now();
        std::make_heap(arr.begin(), arr.end());
        for (auto i = arr.end(); i != arr.begin(); --i) {
            std::pop_heap(arr.begin(), i);
        }
        auto end = std::chrono::steady_clock::now();
        return duration_cast<time_>(end - begin).count();
    }
    bool check(std::vector<T>arr){
        for(size_t i=0; i+1<arr.size(); i++){
            if(arr[i]>arr[i+1]){
                return false;
            }
        }
        return true;
    }
};


int main()
{


    std::string line="1000.1000.10000.txt";
    std::string line1="10000.1000.10000.txt";
    std::string line2="100000.1000.10000.txt";

    Tests<int> g(line);
    Tests<int> g1(line1);
    Tests<int> g2(line2);
    g.all_algorithms();
    g1.all_algorithms();
    g2.all_algorithms();

    std::string line01="1000.1000.1.9999.9.txt";
    std::string line11="10000.1000.1.9999.9.txt";
    std::string line21="100000.1000.1.9999.9.txt";

    Tests<double> g01(line01);
    Tests<double> g11(line11);
    Tests<double> g21(line21);
    g01.all_algorithms();
    g11.all_algorithms();
    g21.all_algorithms();

};