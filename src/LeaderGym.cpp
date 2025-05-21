#include "LeaderGym.hpp"
#include <iostream>

LeaderGym::LeaderGym(const std::string& nom, const std::string& badge, const std::string& gymnase)
    : Entraineur(nom), badge(badge), gymnase(gymnase) {}

std::string LeaderGym::getBadge() const {
    return badge;
}

std::string LeaderGym::getGymnase() const {
    return gymnase;
}

void LeaderGym::interagir() const {
    std::cout << "Bonjour, je suis " << nom << ", le Champion de l'Arène de " << gymnase << " !" << std::endl;
    std::cout << "Si tu parviens à me vaincre, tu obtiendras le Badge " << badge << "." << std::endl;
    std::cout << "Es-tu prêt à relever le défi ?" << std::endl;
} 