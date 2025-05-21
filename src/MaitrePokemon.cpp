#include "MaitrePokemon.hpp"
#include <iostream>

MaitrePokemon::MaitrePokemon(const std::string& nom)
    : Entraineur(nom) {}

float MaitrePokemon::getBonusDegats() const {
    return BONUS_DEGATS;
}

void MaitrePokemon::interagir() const {
    std::cout << "Je suis " << nom << ", Maître Pokémon ! Peu nombreux sont ceux qui ont pu me défier." << std::endl;
    std::cout << "Mes Pokémon sont plus puissants que tous les autres, avec un bonus de dégâts de 25% !" << std::endl;
    std::cout << "Seuls les dresseurs ayant obtenu tous les badges peuvent espérer me vaincre !" << std::endl;
} 