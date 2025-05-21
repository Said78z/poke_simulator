#include "PokemonEau.hpp"
#include <iostream>

PokemonEau::PokemonEau(const std::string& nom, int hp, const std::string& attaque, int puissance,
                     const std::string& typeSecondaire)
    : Pokemon(nom, hp, attaque, puissance, "Eau", typeSecondaire) {}

std::string PokemonEau::getType() const { return "Eau"; }

float PokemonEau::getMultiplicateurContre(const std::string& typeAdverse) const {
    if (typeAdverse == "Feu") return 2.0;
    if (typeAdverse == "Plante") return 0.5;
    return 1.0;
}

void PokemonEau::interagir() const {
    if (typeSecondaire.empty()) {
        std::cout << "Le Pokémon " << nom << " vous éclabousse joyeusement !" << std::endl;
        std::cout << "Il crée quelques bulles qui flottent doucement dans l'air." << std::endl;
    } else {
        Pokemon::interagir(); // Appel à la méthode de la classe parente pour les types doubles
    }
}
