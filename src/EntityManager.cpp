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

const std::vector<std::shared_ptr<Entity>>& EntityManager::GetEntities() {
    return entities_;
}