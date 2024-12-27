#include "game_state.hpp"

std::string GameState::getHash(const std::string& data) {
    std::hash<std::string> hash_fn;
    size_t hash = hash_fn(data);

    std::stringstream ss;
    ss << std::hex << hash;
    return ss.str();
}

Wrapper& operator<<(Wrapper& fileWrapper, GameState& state) {
    nlohmann::json j;
    nlohmann::json data;
    Serialization seri(data);
    
    seri.to_json(state.getPlayer().getShipManager(), "playerShipManager");
    seri.to_json(state.getPlayer().getField(), "playerField");
    seri.to_json(state.getPlayer().getAbilityManager(), "playerAbilityManager");
    seri.to_json(state.getEnemy().getShipManager(), "enemyShipManager");
    seri.to_json(state.getEnemy().getField(), "enemyField");
    
    std::string jsonString = data.dump();

    j["data"] = data;
    j["hashValue"] = state.getHash(jsonString);

    try {
        fileWrapper.write(j);
    }
    catch (UnableToOpenFileException& e){
        std::cerr << e.what() << std::endl;
    }
    
    return fileWrapper;
}

Wrapper& operator>>(Wrapper& fileWrapper, GameState& state) {
    nlohmann::json j;

    try {
        fileWrapper.read(j);
    }
    catch (UnableToOpenFileException& e) {
        std::cerr << e.what() << std::endl;
        return fileWrapper;
    }


    nlohmann::json data = j.at("data");
    std::string savedHashValue = j.at("hashValue");

    std::string jsonString = data.dump();

    if (savedHashValue != state.getHash(jsonString)) {
        throw HashMismatchException();
    }

    Deserialization deseri(data);
    ShipManager shipManager;
    GameField field;
    AbilityManager abilityManager;

    ShipManager enemyShipManager;
    GameField enemyField;

    deseri.from_json(abilityManager, "playerAbilityManager");
    deseri.from_json(shipManager, "playerShipManager");
    deseri.from_json(field, "playerField");

    deseri.from_json(enemyShipManager, "enemyShipManager");
    deseri.from_json(enemyField, "enemyField");

    state.getPlayer().getShipManager() = shipManager;
    state.getPlayer().getField() = field;
    state.getPlayer().getAbilityManager() = abilityManager;

    state.getEnemy().getShipManager() = enemyShipManager;
    state.getEnemy().getField() = enemyField;
    
    state.placeShips(state.getPlayer().getShipManager(), state.getPlayer().getField());
    state.placeShips(state.getEnemy().getShipManager(), state.getEnemy().getField());

    return fileWrapper;
}

void GameState::placeShips(ShipManager& shipManager, GameField& field) {
    for (int y = 0; y < field.getHeight(); y++) {
        for (int x = 0; x < field.getWidth(); x++) {
            auto& cell = field.getCell(x, y);
            if (cell.getStatus() == GameField::Cell::CellStatus::occupied) {
                cell.setShip(shipManager.getShip(cell.getShipIndex()));
            }
        }
    }
}

void GameState::loadGame(const std::string& file) {
    Wrapper fileWrapper(file);
    fileWrapper >> *this;
}

void GameState::saveGame(const std::string& file) {
    std::ofstream ofs(file, std::ofstream::out | std::ofstream::trunc);
    Wrapper fileWrapper(file);
    fileWrapper << *this;
}