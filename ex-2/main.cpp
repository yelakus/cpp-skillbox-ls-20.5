#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>

int main(){
    std::srand(std::time(nullptr));
    int height, width;
    
    std::cout << "Введите высоту и ширину:" << std::endl;
    std::cin >> height >> width;

    std::ofstream file(".\\pic.txt");
    for (int i = 0; i < height; ++i){
        for (int j = 0; j < width; ++j){
            file << std::rand() % 2;
        }
        file << std::endl;
    }
    file.close();
}