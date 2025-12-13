#include "../../include/application/AppState.hpp"

std::vector<std::shared_ptr<NPC>>& AppState::getCharacters() {
    return this->characters_;
}

const std::vector<std::shared_ptr<NPC>>& AppState::getCharacters() const {
    return this->characters_;
}

void AppState::setCharacters(const std::vector<std::shared_ptr<NPC>>& chars) {
    this->characters_ = chars;
}

bool AppState::hasCharacters() const {
    return !this->characters_.empty();
}

void AppState::clear() {
    this->characters_.clear();
}
