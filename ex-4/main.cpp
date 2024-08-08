#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cstdlib>
#include <ctime>

std::vector<int> actualBillsAmount(){//функция считает и возвращает количество каждой и всех купюр
    std::vector<int> allBillsInAtm = {0,0,0,0,0,0,0}; //количество купюр номиналов соответсвенно 100, 200, 500, 1 000, 2 000, 5 000 рублей и колчество всех купюр.
    std::string temp;

    char buffer[25];
    std::ifstream inFile(".\\billsInAtm.bin", std::ios::binary);
    inFile.read(buffer, sizeof(buffer));
    int index = 0;

    for (int i = 0; i < 25; i++){
        if(buffer[i] == ' '){
            allBillsInAtm[6] += std::stoi(temp);
            allBillsInAtm[index] += std::stoi(temp);
            index++;
            temp = "";
            continue;
        }
        temp += buffer[i];
    }

    inFile.close();

    return allBillsInAtm;
}

void fillAtmAndStatus(){ // функция заполняет автомат и выводит общий статус
    std::vector<int> billsAmount = actualBillsAmount();
    if (billsAmount[6] < 1000){
        for(int i = 0; i < 1000 - billsAmount[6]; ++i){
        billsAmount[std::rand() % 6]++;
    }

    std::ofstream file(".\\billsInAtm.bin", std::ios::binary);
    for(int i = 0; i < 6; ++i){
        file << billsAmount[i] << ' ';
    }
    file.close();
    billsAmount = actualBillsAmount(); // считаем еще раз после пополнения
    } 

    int sum = billsAmount[0] * 100 + billsAmount[1] * 200 + billsAmount[2] * 500 + billsAmount[3] * 1000 + billsAmount[4] * 2000 + billsAmount[5] * 5000;
    std::cout << "Количество 100р купюр: " << billsAmount[0] << std::endl;
    std::cout << "Количество 200р купюр: " << billsAmount[1] << std::endl;
    std::cout << "Количество 500р купюр: " << billsAmount[2] << std::endl;
    std::cout << "Количество 1 000р купюр: " << billsAmount[3] << std::endl;
    std::cout << "Количество 2 000р купюр: " << billsAmount[4] << std::endl;
    std::cout << "Количество 5 000р купюр: " << billsAmount[5] << std::endl;
    std::cout << "Общее количество купюр: " << billsAmount[6] << std::endl;
    std::cout << "Общее сумма денег: " << sum << std::endl;

}

int inputAndCheck(){ // проверяем делимость на 100 и не больше ли введенная сумма чем общая сумма денег в банкомате
    int userWithdrawal;
    while(true){
        std::cout << "How much money do you want to withdraw?(divisible by one hundred)" << std::endl;
        std::cin >> userWithdrawal; // тут можно сделать валидацию ввода цифр
        if (userWithdrawal % 100 != 0){
            std::cout << "Enter only divisible by one hundred sum" << std::endl;
            continue;
        } 
        // тут следует оптимизировать
        std::vector<int> billsAmount = actualBillsAmount();
        int sum = billsAmount[0] * 100 + billsAmount[1] * 200 + billsAmount[2] * 500 + billsAmount[3] * 1000 + billsAmount[4] * 2000 + billsAmount[5] * 5000;
        
        if (userWithdrawal > sum){ 
            std::cout << "There are not enough money in the ATM. Please enter a sum below " << sum << std::endl;
            continue;
        }

        break;
    }
    return userWithdrawal;
}

void withdrawal(){
    int userWithdrawal = inputAndCheck();

    std::vector<int> billsAmount = actualBillsAmount();
     while (userWithdrawal != 0){
        if (userWithdrawal / 5000 >= billsAmount[5]) {
            userWithdrawal -= billsAmount[5] * 5000;
            billsAmount[5] = 0;
        } else {
            billsAmount[5] -= userWithdrawal / 5000;
            userWithdrawal %= 5000;
        }

        if (userWithdrawal / 2000 >= billsAmount[4]) {
            userWithdrawal -= billsAmount[4] * 2000;
            billsAmount[4] = 0;
        } else {
            billsAmount[4] -= userWithdrawal / 2000;
            userWithdrawal %= 2000;
        }

        if (userWithdrawal / 1000 >= billsAmount[3]) {
            userWithdrawal -= billsAmount[3] * 1000;
            billsAmount[3] = 0;
        } else {
            billsAmount[3] -= userWithdrawal / 1000;
            userWithdrawal %= 1000;
        }

        if (userWithdrawal / 500 >= billsAmount[2]) {
            userWithdrawal -= billsAmount[2] * 500;
            billsAmount[2] = 0;
        } else {
            billsAmount[2] -= userWithdrawal / 500;
            userWithdrawal %= 500;
        }

        if (userWithdrawal / 200 >= billsAmount[1]) {
            userWithdrawal -= billsAmount[1] * 200;
            billsAmount[1] = 0;
        } else {
            billsAmount[1] -= userWithdrawal / 200;
            userWithdrawal %= 200;
        }

        if (userWithdrawal / 100 >= billsAmount[0]) {
            userWithdrawal -= billsAmount[0] * 100;
            billsAmount[0] = 0;
        } else {
            billsAmount[0] -= userWithdrawal / 100;
            userWithdrawal %= 100;
        }
     }

     /*for(int i : billsAmount){
        std::cout << i << std::endl;
     }*/

    std::ofstream file(".\\billsInAtm.bin", std::ios::binary); // переписать файл с учетом выведенных купюр
    for(int i = 0; i < 6; ++i){
        file << billsAmount[i] << ' ';
    }
    file.close();
}

int main(){

    std::srand(std::time(nullptr));
    std::string userInput;

    while(true){
        std::cout << "Type a command: \"+\" or \"-\" or \"exit\"" << std::endl;
        std::cin >> userInput;

        if (userInput == "exit") break;

        if (userInput == "+"){
            fillAtmAndStatus();
            continue;
        }

        if (userInput == "-"){
            withdrawal();
            continue;
        }

        std::cout << "Only \"+\" or \"-\" or \"exit\" commands. Try again." << std::endl;
    }

}