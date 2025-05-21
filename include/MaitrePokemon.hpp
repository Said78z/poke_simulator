#ifndef MAITREPOKEMON_HPP
#define MAITREPOKEMON_HPP

#include "Entraineur.hpp"

class MaitrePokemon : public Entraineur {
private:
    // Capacité spéciale qui augmente les dégâts de 25%
    const float BONUS_DEGATS = 1.25f;

public:
    MaitrePokemon(const std::string& nom);
    
    // Méthode pour appliquer le bonus de dégâts
    float getBonusDegats() const;
    
    // Surcharge de la méthode interagir
    void interagir() const override;
};

#endif 