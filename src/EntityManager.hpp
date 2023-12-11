#ifndef ENTITY_MANAGER_HPP_
#define ENTITY_MANAGER_HPP_

#include <memory>
#include <vector>

class Entity;  // Forward declaration

/*! \brief Class for Entity manipulation.

A class that is responsible for storing all the Entities in the game and 
performing operations on the container storing them. It stores Entities in 
the vector of shared pointers.
*/
class EntityManager {
   public:
    /*! a method to add Entity to the entities_ vector */
    static void AddEntity(std::shared_ptr<Entity> entity);
    /*! a method to remove Entity from the entities_ vector based on a pointer to the enemy */
    static void RemoveEntity(std::shared_ptr<Entity> entity);
    /*! a method to remove Entity from the entities_ vector based on an iterator */
    static void RemoveEntity(std::vector<std::shared_ptr<Entity>>::iterator it);
    /*! a method to remove all Entities from the entities_ vector */
    static void ClearEntities();
    /*! a method that iterates through the entities_ vector and removes the dead Entities from it */
    static void RemoveDead();

    /*! a method returning the begin iterator to the entities_ vector */
    static std::vector<std::shared_ptr<Entity>>::iterator begin();
    /*! a method returning the end iterator to the entities_ vector */
    static std::vector<std::shared_ptr<Entity>>::iterator end();
    /*! a method returning the const begin iterator to entities_ vector */
    static std::vector<std::shared_ptr<Entity>>::const_iterator cbegin();
    /*! a method returning the const end iterator to entities_ vector */
    static std::vector<std::shared_ptr<Entity>>::const_iterator cend();

   private:
    /*! a private vector that stores all the Entities in the game as the shared pointers to the Entities, 
    as they are also stored in Game class in monsters_ to differentiate between Monsters and the Player. 
    Shared pointers ensure correct memory deallocation.*/
    static std::vector<std::shared_ptr<Entity>> entities_;
};

#endif  // ENTITY_MANAGER_HPP_