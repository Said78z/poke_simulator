#ifndef POKEMON_PLANTE_HPP
#define POKEMON_PLANTE_HPP

#include "Pokemon.hpp"

class PokemonPlante : public Pokemon {
public:
    PokemonPlante(const std::string& nom, int hp, const std::string& attaque, int puissance,
                 const std::string& typeSecondaire = "");
    std::string getType() const override;
    float getMultiplicateurContre(const std::string& typeAdverse) const override;
    void interagir() const override;
};

#endif
