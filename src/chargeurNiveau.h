/*
 * FICHIER: chargerNiveau.h
 * PROJET:  LikeASir
 *
 * AUTHEUR: Nathan
 * DATE:    2013-04-25
 *
 *
 * Classe permettant le chargement d'un niveau à partir d'un bitmap
 */

#ifndef __LikeASir__chargerNiveau__
#define __LikeASir__chargerNiveau__

#include <iostream>
#include "niveau.h"

#include <map>

struct pixelToTile {
    sf::Color _couleur;
    tuile _tuile;
};

int convertirCouleurEnInt(sf::Color &color);

class chargeurNiveau {
public:
    static niveau chargerNiveauDeImage(sf::Image &img, std::map<int, tuile> &map);  
};

#endif /* defined(__LikeASir__chargerNiveau__) */
