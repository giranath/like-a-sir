/*
 * FICHIER: chargerNiveau.cpp
 * PROJET:  LikeASir
 *
 * AUTHEUR: Nathan
 * DATE:    2013-04-25
 *
*/

#include "chargeurNiveau.h"
#include "porte.h"
#include "clef.h"
#include "mechant.h"
#include "baril.h"
#include "levier.h"
#include "trap.h"
#include "trapAuto.h"

//Cette méthode statique consiste à convertir chaque pixel en une case pour le niveau.
niveau chargeurNiveau::chargerNiveauDeImage(sf::Image &img, std::map<int, tuile> &map) {
    //On crée un niveau
    niveau niveau;
    //On l'initialise à la taille de l'image
    niveau.init(img.getSize().x, img.getSize().y);
    //On parcour l'image par chaque pixel et on vérifie sa couleur
    for(int i = 0 ; i < img.getSize().y; i++) {
        for(int j = 0; j < img.getSize().x; j++) {
            sf::Color color = img.getPixel(j, i);
            //Convertir une couleur en un entier
            int key = convertirCouleurEnInt(color);
            //Si la couleur est dans le tableau on set la tuile
            if(map.find(key) != map.end())
                niveau.setTuile(j, i, map[key]);
            
            // Sinon on regarde si la couleur correspond à une entrée de niveau
            else if(color == sf::Color(50,255,0)) {
                niveau.setEntree(j, i);
            }
            
            // Sinon, s'il s'agit d'un méchant
            else if(color == sf::Color(66,66,66)) {
                mechant *m = new mechant;
                m->setPosition(j * 8, i * 8);
                
                niveau.ajouterActeur(m);
            }
            
            // Sinon s'il s'agit d'une sortie
            else if(color.g == 110 && color.b == 50) {
                niveau.setSortie(j, i);
                porte *p = new porte;
                p->setPosition(j * 8, i * 8);
                p->setProchainNiveau(color.r);
                
                niveau.ajouterActeur(p);
            } 
            
            // Sinon s'il s'agit d'une clef
            else if(color == sf::Color(170,55,110)) {
                clef *c = new clef;
                c->setPosition(j * 8, i * 8);
                
                niveau.ajouterActeur(c);
            }
            
            // Sinon s'il s'agit d'une cachette
            else if(color == sf::Color(45,235,234)) {
                baril *b = new baril;
                b->setPosition(j * 8, i * 8);
                
                niveau.ajouterActeur(b);
            } 
            
            // Sinon s'il s'agit d'un levier
            else if(color.r == 64 && color.g == 87) {
                levier *l = new levier;
                l->setPosition(j * 8, i * 8);
                l->setLevierID(color.b);
                
                niveau.ajouterActeur(l);
            } 
            
            // Sinon s'il s'agit d'une trappe ouverte
            else if(color.r == 64 && color.b == 87) {
                trap *t = new trap;
                t->setPosition(j * 8, i * 8);
                t->setLevierID(color.g);
                t->fermer();
                t->setOuvertureDefaut(false);
                
                niveau.ajouterActeur(t);
            } 
            
            // Sinon s'il s'agit d'une trappe fermée
            else if(color.r == 87 && color.b == 64) {
                trap *t = new trap;
                t->setPosition(j * 8, i * 8);
                t->setLevierID(color.g);
                t->ouvrir();
                t->setOuvertureDefaut(true);
                
                niveau.ajouterActeur(t);
            }
            
            // Sinon s'il s'agit d'une trappe automatique
            else if(color.g == 12 && color.b == 52) {
                trapAuto *t = new trapAuto;
                t->setPosition(j * 8, i * 8);
                t->setDeltaTime(color.r);
                
                niveau.ajouterActeur(t);
            }
        }
    }
    
    return niveau;
}

int convertirCouleurEnInt(sf::Color &color) {
    return color.r * 10000 + color.g * 100 + color.b;
}