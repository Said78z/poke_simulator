#include "PokemonFeu.hpp"
#include <iostream>

PokemonFeu::PokemonFeu(const std::string& nom, int hp, const std::string& attaque, int puissance,
                     const std::string& typeSecondaire)
    : Pokemon(nom, hp, attaque, puissance, "Feu", typeSecondaire) {}

std::string PokemonFeu::getType() const { return "Feu"; }

float PokemonFeu::getMultiplicateurContre(const std::string& typeAdverse) const {
    if (typeAdverse == "Plante") return 2.0;
    if (typeAdverse == "Eau") return 0.5;
    return 1.0;
}

void PokemonFeu::interagir() const {
    if (typeSecondaire.empty()) {
        std::cout << "Le Pokémon " << nom << " crache des flammes ardentes !" << std::endl;
        std::cout << "Sa queue s'embrase avec une intensité impressionnante !" << std::endl;
    } else {
        Pokemon::interagir(); // Appel à la méthode de la classe parente pour les types doubles
    }
}
