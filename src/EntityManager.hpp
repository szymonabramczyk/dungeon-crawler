#ifndef ENTITY_MANAGER_HPP_
#define ENTITY_MANAGER_HPP_

#include <memory>
#include <vector>

class Entity;  // Forward declaration

class EntityManager {
   public:
    static void AddEntity(std::shared_ptr<Entity> entity);
    static void RemoveEntity(std::shared_ptr<Entity> entity);
    static void ClearEntities();
    static void RemoveDead();
    static const std::vector<std::shared_ptr<Entity>>& GetEntities();

   private:
    static std::vector<std::shared_ptr<Entity>> entities_;
};

#endif  // ENTITY_MANAGER_HPP_
