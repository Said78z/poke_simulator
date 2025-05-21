#ifndef COMBAT_HPP
#define COMBAT_HPP

#include <memory>
#include <vector>
#include "Pokemon.hpp"

class Entraineur; // Déclaration anticipée

class Combat {
private:
    std::shared_ptr<Entraineur> entraineur1;
    std::shared_ptr<Entraineur> entraineur2;
    int indexPokemon1;
    int indexPokemon2;

public:
    Combat(std::shared_ptr<Entraineur> entraineur1, std::shared_ptr<Entraineur> entraineur2);
    
    // Lance le combat entre les deux entraîneurs
    void demarrer();
    
    // Effectue un tour de combat
    bool effectuerTour();
    
    // Calcule les dégâts en appliquant les multiplicateurs
    int calculerDegats(std::shared_ptr<Pokemon> attaquant, std::shared_ptr<Pokemon> defenseur);
    
    // Affiche le résultat du combat
    void afficherResultat(bool victoire);
};

#endif 