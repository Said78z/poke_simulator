#ifndef POKEMON_EAU_HPP
#define POKEMON_EAU_HPP

#include "Pokemon.hpp"

class PokemonEau : public Pokemon {
public:
    PokemonEau(const std::string& nom, int hp, const std::string& attaque, int puissance,
              const std::string& typeSecondaire = "");
    std::string getType() const override;
    float getMultiplicateurContre(const std::string& typeAdverse) const override;
    void interagir() const override;
};

#endif
