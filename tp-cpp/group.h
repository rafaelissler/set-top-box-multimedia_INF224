#ifndef GROUP_H
#define GROUP_H

#include <list>

/**
 * @brief Class for a group of pointers to Multimedia objects
 */
class Group: public std::list<std::shared_ptr<Multimedia>>{
    private:
    std::string name;

    public:
    /**
     * @brief Construct a new Group object
     * 
     * @param name Name of the group
     */
    Group(std::string name);

    /**
     * @brief Sends the values of every object in the group
     * 
     * @param out Stream to be outputted to
     */
    void printValues(std::ostream &out) const;
    void erase(std::string name);
    
    std::string getName() const;
    void setName(std::string name);
};

#endif