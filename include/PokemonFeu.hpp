#ifndef POKEMON_FEU_HPP
#define POKEMON_FEU_HPP

#include "Pokemon.hpp"

class PokemonFeu : public Pokemon {
public:
    PokemonFeu(const std::string& nom, int hp, const std::string& attaque, int puissance,
              const std::string& typeSecondaire = "");
    std::string getType() const override;
    float getMultiplicateurContre(const std::string& typeAdverse) const override;
    void interagir() const override;
};

#endif
