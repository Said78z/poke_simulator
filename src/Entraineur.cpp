#include "Entraineur.hpp"
#include <iostream>

Entraineur::Entraineur(const std::string& nom) : nom(nom) {}

void Entraineur::ajouterPokemon(std::shared_ptr<Pokemon> pokemon) {
    if (equipe.size() < 6) {
        equipe.push_back(pokemon);
    } else {
        std::cout << "L'équipe est déjà complète (maximum 6 Pokémon)" << std::endl;
    }
}

std::shared_ptr<Pokemon> Entraineur::getPokemon(int index) const {
    if (index >= 0 && index < static_cast<int>(equipe.size())) {
        return equipe[index];
    }
    return nullptr;
}

size_t Entraineur::getNombrePokemon() const {
    return equipe.size();
}

bool Entraineur::aDesPokemonValides() const {
    for (const auto& pokemon : equipe) {
        if (pokemon->getHP() > 0) {
            return true;
        }
    }
    return false;
}

void Entraineur::interagir() const {
    std::cout << "Je suis " << nom << ", un entraîneur Pokémon !" << std::endl;
}

std::string Entraineur::getNom() const {
    return nom;
}

void Entraineur::afficherEquipe() const {
    std::cout << "Équipe de " << nom << " :" << std::endl;
    for (size_t i = 0; i < equipe.size(); ++i) {
        std::cout << i + 1 << ". ";
        equipe[i]->afficher();
        std::cout << std::endl;
    }
} 