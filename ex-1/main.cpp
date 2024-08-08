#include <iostream>
#include <fstream>
#include <string>

bool isPositiveNumber(std::string sum){
    if (sum[0] == '-'){
        std::cout << "Нужно ввести целое положительное число." << std::endl;
        return false;
    }

    for(int i = 0; i < sum.length(); ++i){
        if(!(isdigit(sum[i]))){
            std::cout << "Нужно ввести целое положительное число." << std::endl;
            return false;
        }
    }    
    return true;
}

std::string getSumInput(){
    std::string sum;

    while(true){
        std::cout << "Введите сумму:" << std::endl;
        std::cin >> sum;
        if (isPositiveNumber(sum)) break;
    }

    return sum;
}

bool isDateInputCorrect(std::string date){
    if (date.length() != 10 || date[2] != '.' || date[5] != '.') {
        std::cout << "Неправильный ввод!" << std::endl;
        return false;
    }

    std::string day, month, year;
    day = date.substr(0, 2);
    month = date.substr(3, 2);
    year = date.substr(6, 4);
    
    if(isPositiveNumber(day) && isPositiveNumber(month) && isPositiveNumber(year)) return true;
    
    std::cout << "Неправильный ввод!" << std::endl;
    return false;
}

std::string getDateInput(){
    std::string date;

    while(true){
        std::cout << "Введите дату в формате ДД.ММ.ГГГГ: " << std::endl;
        std::cin >> date;
        if (isDateInputCorrect(date)) break;
    }

    return date;
}

int main()
{
    std::string firstName, lastName, sum, date;

    std::cout << "Введите Имя: " << std::endl;
    std::cin >> firstName;
    std::cout << "Введите Фамилию: " << std::endl;
    std::cin >> lastName;

    date = getDateInput();
    sum = getSumInput();
    
    std::ofstream file(".\\dataBase.txt", std::ios::app);
    file << firstName << " " << lastName << " "  << date << " " << sum << "p." << std::endl;
    file.close();
}