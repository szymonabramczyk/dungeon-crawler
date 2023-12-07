#ifndef ENTITY_MANAGER_HPP_
#define ENTITY_MANAGER_HPP_

#include <vector>
#include <memory>

class Entity; // Forward declaration

class EntityManager {
public:
    static void addEntity(std::shared_ptr<Entity> entity);
    static void removeEntity(std::shared_ptr<Entity> entity);
    static void clearEntities();
    static void removeDead();
    static const std::vector<std::shared_ptr<Entity>>& getEntities();

private:
    static std::vector<std::shared_ptr<Entity>> entities_;
};

#endif // ENTITY_MANAGER_HPP_
