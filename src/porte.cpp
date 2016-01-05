/*
 * FICHIER: porte.cpp
 * PROJET:  LikeASir_fonctionnel
 *
 * AUTHEUR: Nathan
 * DATE:    2013-05-06
 *
*/

#include "porte.h"
#include "TextureManager.h"
#include "personnage.h"
#include "joueur.h"
#include "GestionnaireNiveau.h"
#include "BufferManager.h"

porte::porte() 
:interaction()
{
    this->setTexture(*TextureManager::getInstance()->getTexture("porte_01"));
    this->setLargeur(8);
    this->setHauteur(16);
    
    _sonVerouille.setBuffer(*BufferManager::getInstance()->getBuffer("fermee"));
}

porte::~porte() {
    
}

void porte::rafraichir(float delta) {
    _active = false;
}

void porte::enCollisionAvecActeur(acteur *autre) {
    if(autre->getType() == acteur::PERSONNAGE) {
        _active = true;
        personnage *person = dynamic_cast<personnage*>(autre);
        
        // Si la clef entre en collision 
        if(person->getTypePersonnage() == personnage::JOUEUR) {
            joueur *j = dynamic_cast<joueur*>(person);
   
            if(j->getClef() && j->getAction()) {
                j->enleverClef();
               // tuer();
                gestionnaireNiveau::getInstance()->changerNiveau(_prochainNiveau);
            } else if(j->getClef() == false && j->getAction()) {
                if(_sonVerouille.getStatus() != sf::Sound::Playing && _sonUnique == false)
                    _sonVerouille.play();
                _sonUnique = true;
            } else if(j->getAction() == false && _sonUnique) {
                _sonUnique = false;
            }
        }
    }

}


void porte::subitUneCollision() {
    
}

void porte::setProchainNiveau(int valeur) {
    _prochainNiveau = valeur;
}

int porte::getProchainNiveau() {
    return _prochainNiveau;
}