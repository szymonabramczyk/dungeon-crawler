#include "EntityManager.hpp"

#include <memory>
#include <vector>

#include "Entity.hpp"

std::vector<std::shared_ptr<Entity>> EntityManager::entities_;

void EntityManager::AddEntity(std::shared_ptr<Entity> entity) {
    entities_.push_back(entity);
}

void EntityManager::RemoveEntity(std::shared_ptr<Entity> entity) {
    auto it = std::find(entities_.begin(), entities_.end(), entity);
    if (it != entities_.end()) {
        entities_.erase(it);
    }
}

void EntityManager::RemoveEntity(std::vector<std::shared_ptr<Entity>>::iterator it) {
    if (it != entities_.end()) {
        entities_.erase(it);
    }
}

void EntityManager::ClearEntities() {
    entities_.clear();
}

void EntityManager::RemoveDead() {
    entities_.erase(std::remove_if(
                        entities_.begin(), entities_.end(),
                        [](const std::shared_ptr<Entity>& x) {
                            return x->IsDead();
                        }),
                    entities_.end());
}

std::vector<std::shared_ptr<Entity>>::iterator EntityManager::begin() {
    return entities_.begin();
}

std::vector<std::shared_ptr<Entity>>::iterator EntityManager::end() {
    return entities_.end();
}

std::vector<std::shared_ptr<Entity>>::const_iterator EntityManager::cbegin() {
    return entities_.cbegin();
}

std::vector<std::shared_ptr<Entity>>::const_iterator EntityManager::cend() {
    return entities_.cend();
}