#include "PokemonPlante.hpp"
#include <iostream>

PokemonPlante::PokemonPlante(const std::string& nom, int hp, const std::string& attaque, int puissance,
                           const std::string& typeSecondaire)
    : Pokemon(nom, hp, attaque, puissance, "Plante", typeSecondaire) {}

std::string PokemonPlante::getType() const { return "Plante"; }

float PokemonPlante::getMultiplicateurContre(const std::string& typeAdverse) const {
    if (typeAdverse == "Eau") return 2.0;
    if (typeAdverse == "Feu") return 0.5;
    return 1.0;
}

void PokemonPlante::interagir() const {
    if (typeSecondaire.empty()) {
        std::cout << "Le Pokémon " << nom << " fait pousser quelques feuilles autour de lui !" << std::endl;
        std::cout << "Une douce odeur de nature émane de sa plante." << std::endl;
    } else {
        Pokemon::interagir(); // Appel à la méthode de la classe parente pour les types doubles
    }
}
