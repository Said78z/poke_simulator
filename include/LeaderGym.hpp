#ifndef LEADERGYM_HPP
#define LEADERGYM_HPP

#include "Entraineur.hpp"

class LeaderGym : public Entraineur {
private:
    std::string badge;
    std::string gymnase;

public:
    LeaderGym(const std::string& nom, const std::string& badge, const std::string& gymnase);
    
    // Méthodes d'accès
    std::string getBadge() const;
    std::string getGymnase() const;
    
    // Surcharge de la méthode interagir
    void interagir() const override;
};

#endif 