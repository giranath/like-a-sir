/*
 * FICHIER: clef.cpp
 * PROJET:  LikeASir_fonctionnel
 *
 * AUTHEUR: Nathan
 * DATE:    2013-05-06
 *
*/

#include "clef.h"
#include "TextureManager.h"
#include "personnage.h"
#include "joueur.h"

clef::clef() {
    this->setTexture(*TextureManager::getInstance()->getTexture("clef"));
    this->setLargeur(8);
    this->setHauteur(8);
}

clef::~clef() {
    
}

void clef::rafraichir(float delta) {
    
}

void clef::enCollisionAvecActeur(acteur *autre) {
    if(autre->getType() == acteur::PERSONNAGE && _visible == true) {
        personnage *person = dynamic_cast<personnage*>(autre);
        
        // Si la clef entre en collision 
        if(person->getTypePersonnage() == personnage::JOUEUR) {
            joueur *j = dynamic_cast<joueur*>(person);
        
            j->trouverClef();
            
            //tuer();
            cacher();
        }
    }
}

void clef::subitUneCollision() {
    
}