#include<iostream>

int main() {
    const double terrestrial_planets[4] = {88,225,365,687};
    const double outer_planets[4] = {12,29.5,84,165};
    

    for (int i=0; i<4;i++){
        
        std::cout<< terrestrial_planets[i]<<"\n";
        std::cout<< outer_planets[i]<<"\n";
        
    }

}