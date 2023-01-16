#include <string>
#include "engine.h"

nlohmann::json parseInput(){
    std::string input;
    std::cin >> input;
    nlohmann::json json = nlohmann::json::parse(input);
    return json;
}

int main(int argc, char* argv[]){
    nlohmann::json input = parseInput();

    Engine engine;
    engine.CalculateMove(input);

    // MLEngine smartEngine;
    // smartEngine.CalculateMove(input);
}
