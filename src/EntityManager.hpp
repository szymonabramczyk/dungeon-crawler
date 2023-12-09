#ifndef ENTITY_MANAGER_HPP_
#define ENTITY_MANAGER_HPP_

#include <memory>
#include <vector>

class Entity;  // Forward declaration

class EntityManager {
   public:
    static void AddEntity(std::shared_ptr<Entity> entity);
    static void RemoveEntity(std::shared_ptr<Entity> entity);
    static void RemoveEntity(std::vector<std::shared_ptr<Entity>>::iterator it);
    static void ClearEntities();
    static void RemoveDead();

    // iterator methods
    static std::vector<std::shared_ptr<Entity>>::iterator begin();
    static std::vector<std::shared_ptr<Entity>>::iterator end();
    static std::vector<std::shared_ptr<Entity>>::const_iterator cbegin();
    static std::vector<std::shared_ptr<Entity>>::const_iterator cend();

   private:
    static std::vector<std::shared_ptr<Entity>> entities_;
};

#endif  // ENTITY_MANAGER_HPP_