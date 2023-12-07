#include "EntityManager.hpp"
#include "Entity.hpp"

#include <vector>
#include <memory>

std::vector<std::shared_ptr<Entity>> EntityManager::entities_;

void EntityManager::addEntity(std::shared_ptr<Entity> entity) {
    entities_.push_back(entity);
}

void EntityManager::removeEntity(std::shared_ptr<Entity> entity) {
    auto it = std::find(entities_.begin(), entities_.end(), entity);
    if (it != entities_.end()) {
        entities_.erase(it);
    }
}

void EntityManager::clearEntities() {
    entities_.clear();
}

void EntityManager::removeDead() {
    entities_.erase(std::remove_if(
        entities_.begin(), entities_.end(),
        [](const std::shared_ptr<Entity>& x) { 
            return x->IsDead(); 
        }), entities_.end());
}

const std::vector<std::shared_ptr<Entity>>& EntityManager::getEntities() {
    return entities_;
}