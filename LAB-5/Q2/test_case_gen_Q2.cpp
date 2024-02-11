#include <iostream>
#include <fstream>
#include <vector>
#include <random>

void generateTestCases() {
    std::ofstream file("input_Q2.txt", std::ios_base::app);
    if (!file.is_open()) {
        std::cerr << "Error opening file for writing!" << std::endl;
        return;
    }

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(2, 5); // Number of ladders and snakes will be between 2 and 5
    int numLadders = dis(gen);
    int numSnakes = dis(gen);

    // Generate ladders
    file << numLadders << std::endl;
    std::uniform_int_distribution<> ladderDis(1, 30);
    std::vector<std::pair<int, int>> ladders;
    for (int i = 0; i < numLadders; ++i) {
        int start = ladderDis(gen);
        int end = ladderDis(gen);
        file << start << " " << end << std::endl;
        ladders.push_back(std::make_pair(start, end));
    }

    // Generate snakes
    file << numSnakes << std::endl;
    std::uniform_int_distribution<> snakeDis(1, 30);
    std::vector<std::pair<int, int>> snakes;
    for (int i = 0; i < numSnakes; ++i) {
        int start = snakeDis(gen);
        int end = snakeDis(gen);
        file << start << " " << end << std::endl;
        snakes.push_back(std::make_pair(start, end));
    }

    file.close();
    std::cout << "Test cases generated and appended successfully!" << std::endl;
}

int main() {
    generateTestCases();

    return 0;
}
