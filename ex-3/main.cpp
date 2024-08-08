#include <iostream>
#include <fstream>
#include <string>

int main(){
    
    std::string fish;
    std::cout << "Какую рыбу хотите поймать?" << std::endl;
    std::cin >> fish;

    std::ifstream riverStream(".\\river.txt");

    std::ofstream tempRiverStream(".\\tempRiver.txt"); // копия списка рыб в реке без пойманной рыбы
    
    
    bool didFishCaught = false;

    while(!riverStream.eof()){
        std::string currentFish;
        riverStream >> currentFish;

        if (!didFishCaught && currentFish == fish){
            std::cout << "Вы поймали " << fish << "!" << std::endl;

            std::ofstream basketStream(".\\basket.txt", std::ios::app);
            basketStream << fish << std::endl;
            basketStream.close();
            didFishCaught = true;
            continue;
        }
        tempRiverStream << currentFish << std::endl;

    }

    riverStream.close();
    tempRiverStream.close();

    //переписать river.txt если рыба была поймана
    if (didFishCaught){
        std::ofstream outRiverStream(".\\river.txt");
        std::ifstream inTempRiverStream(".\\tempRiver.txt");

        while(!inTempRiverStream.eof()){
            std::string currentFish;
            inTempRiverStream >> currentFish;
            outRiverStream << currentFish << std::endl;
        }

        outRiverStream.close();
        inTempRiverStream.close();
    }

    
}