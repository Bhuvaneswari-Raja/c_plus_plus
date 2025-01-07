#include <iostream>
#include <string>
#include <ctime>
#include <chrono>
#include <iomanip>
#include <array>
#include <map>
using namespace std;

void setTime(double);


int main() {

    cout << "Date check: ";

    auto time = chrono::system_clock::now();
    
    // Convert time_point to time_t
    time_t timeT = chrono::system_clock::to_time_t(time);

    // Convert time_t to tm for formatting
    tm* tm = localtime(&timeT);

    // Print the formatted time
    cout << put_time(tm, "%Y-%m-%d") << endl;    

    return 0;
}


