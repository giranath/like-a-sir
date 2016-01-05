/*
 * FICHIER: Niveau.cpp
 * PROJET:  ProtoNinja
 *
 * AUTHEUR: Nathan
 * DATE:    2013-04-22
 *
*/

#include "niveau.h"
#include <cmath>
#include "mechant.h"
#include "levier.h"
#include "trap.h"

float distanceEntrePosition(sf::Vector2f a, sf::Vector2f b) {
    return sqrtf(((b.x - a.x) * (b.x - a.x)) + ((b.y - a.y) * (b.y - a.y)));
}

niveau::niveau() {
    _largeur = 0;
    _hauteur = 0;
}

niveau::niveau(niveau const&copy) {
    _largeur = copy._largeur;
    _hauteur = copy._hauteur;
    
    _acteurs = copy._acteurs;
    
    for(std::list<acteur*>::iterator it = _acteurs.begin(); it != _acteurs.end(); it++) {
        (*it)->devoiler();
    }
    
    _tuiles = copy._tuiles;
    
    _entree = copy._entree;
    _sortie = copy._sortie;
}

niveau::~niveau(){
}

bool niveau::init(int largeur, int hauteur) {
    // Si les dimensions entrées sont invalides...
    if(largeur < 0 || hauteur < 0) {
        // On stoppe l'initialisation
        return false;
    }
    
    _largeur = largeur;
    _hauteur = hauteur;
    
    _tuiles.resize(_hauteur);
    
    for(int i = 0; i < _hauteur; i++)
        _tuiles[i].resize(_largeur);
    
    return true;
}

tuile* niveau::getTuile(int x, int y) {
    // SI on veut acceder à une case hors du tableau, on renvoie un pointeur null
    if(x < 0 || y < 0 || x >= _largeur || y >= _hauteur)
        return NULL;
    
    // Sinon on retourne un pointeur vers la tuile demandée
    return &_tuiles[y][x];
}

bool niveau::setTuile(int x, int y, tuile iTuile) {
    if(x < 0 || y < 0 || x >= _largeur || y >= _hauteur)
        return false;
    
    _tuiles[y][x] = iTuile;
    
    _tuiles[y][x]._sprite.setPosition(x * 8, y * 8);
    
    _tuiles[y][x]._sprite.setTextureRect(sf::IntRect((int)(_tuiles[y][x].identifiant % 5) * 8, (int)(_tuiles[y][x].identifiant/5) * 8,8,8));
    
    return true;
}

void niveau::ajouterActeur(acteur *_acteur) {
    _acteurs.push_back(_acteur);
}

void niveau::rafraichir(float delta) {
    std::list<acteur*>::iterator it;
    
    // On parcourt la liste des acteurs...
    ///for(it = _acteurs.begin(); it != _acteurs.end(); ++it) {
        it = _acteurs.begin(); 
        while(it != _acteurs.end()) {
        
        // On effectue sa mise à jours
        (*it)->rafraichir(delta);
        
        // On détecte quel type d'acteur il s'agit pour adapter les prochaines instructions...
        switch((*it)->getType()) {
            // Si c'est un personnage,
            case acteur::PERSONNAGE: 
            {
                // On convertie l'acteur en personnage pour manipuler les propriétés qui lui sont propre
                personnage *ActuelPersonnage = dynamic_cast<personnage*>(*it);
            
                if(ActuelPersonnage->getAuSol() == false) {
                    ActuelPersonnage->setVelocite(ActuelPersonnage->getVelocite().x, ActuelPersonnage->getVelocite().y + 0.055f);
                }
                
                sf::Vector2f a1, a2;    // Les antennes
                
                a1 = (ActuelPersonnage->getPosition() + ActuelPersonnage->getAntenne1());
                a2 = (ActuelPersonnage->getPosition() + ActuelPersonnage->getAntenne2());
                
                // On détecte dans quel bloc les antennes touchent
                int x1, y1, x2, y2;
                
                x1 = a1.x / 8;
                x2 = a2.x / 8;
                
                y1 = a1.y / 8;
                y2 = a2.y / 8;
                
                // Si c'est le joueur
                if(ActuelPersonnage->getTypePersonnage() == personnage::JOUEUR) {
                    
                    joueur *actualJoueur = dynamic_cast<joueur*>(*it);
                    
                    // Si les deux antennes touches le sol, alors le personnage est considéré comme sur le sol
                    // (Avec un ou ici = wall jumps) (Avec un false = seulement s'accrocher)
                    if(_tuiles[y1][x1].mur == true || _tuiles[y2][x2].mur == true) {
                        actualJoueur->setAuSol(true);
                        actualJoueur->setWatchOut(false);
                    }// Si les antennes ne détectent rien le personnage est dans les airs
                    else {
                        actualJoueur->setAuSol(false);
                        actualJoueur->setWatchOut(false);
                    }
                    
                    if((_tuiles[y1][x1].mur == true && _tuiles[y2][x2].mur == false)) {
                        actualJoueur->setWatchOut(true);
                    } else if(_tuiles[y1][x1].mur == false && _tuiles[y2][x2].mur == true) {
                        actualJoueur->setWatchOut(true);
                    }
                }
                
            }
                break;
                
            default:
                break;
        }
        
        // On décompose le mouvement
        
        float dx, dy;
        
        // On récupère la vélocité en entier
        dx = (*it)->getVelocite().x ;
        dy = (*it)->getVelocite().y ;
        
        // On récupère la direction (gauche/droite, bas/haut)
        int depy = 1, depx = 1;
        
        if(dx < 0)
            depx = -1;
        if(dy < 0)
            depy = -1;
        
        
        for(int x = 0; x <= abs(dx); x++) {
            bool collision = false;
            
            int px;
            
            if(depx >= 0) {
                px = (*it)->getPosition().x + (*it)->getLargeur() - 1;
            } else {    // Sinon c'est la tête
                px = (*it)->getPosition().x;
            }
            
            // On récupère les x des cases de l'entite
            int maxY, minY;
            minY = (*it)->getPosition().y / 8;
            maxY = ((*it)->getPosition().y + (*it)->getHauteur() - 1) / 8;
            
            for(int y = minY; y <= maxY; y++) {
                if(_tuiles[y][(px + depx * x)/8].mur == true) {
                    collision = true;
                    break;
                }
            }
            
            // Si collision durant test on quitte la boucle
            if(collision == true) {
                (*it)->subitUneCollision();
                (*it)->setVelocite(0, (*it)->getVelocite().y);
                break;
            }
        }
        
        // On essais unité par unité le déplacement y pour vérifier s'il y a collision
        for(int y = 0; y <= abs(dy); y++) {
            bool collision = false;
            
            int py; // Le point y qui pourrait possiblement entrer en collision
            
            // S'il descend, ce sont les pieds
            if(depy >= 0) {
                py = (*it)->getPosition().y + (*it)->getHauteur() ;
            } else {    // Sinon c'est la tête
                py = (*it)->getPosition().y;
            }
            
            // On récupère les x des cases de l'entite
            int maxX, minX;
            minX = (*it)->getPosition().x / 8;
            maxX = ((*it)->getPosition().x + (*it)->getLargeur() - 1) / 8;
            
            for(int x = minX; x <= maxX; x++) {
                if(_tuiles[(py + depy * y)/8][x].mur == true) {
                    collision = true;
                    break;
                }
            }
            
            // Si collision durant test on quitte la boucle
            if(collision == true) {
                (*it)->subitUneCollision();
                (*it)->setVelocite((*it)->getVelocite().x, 0);
                break;
            }
        }
        
        
        // On déplace l'acteur en fonction de sa vélocité.
        (*it)->setPosition((*it)->getPosition().x + (*it)->getVelocite().x,(*it)->getPosition().y + (*it)->getVelocite().y );
        
        std::list<acteur*>::iterator it2;
            
        // On récupère la hitbox du premier itérareur
        sf::FloatRect rect1;
        rect1.left = (*it)->getPosition().x;
        rect1.top = (*it)->getPosition().y;
        rect1.width = (*it)->getLargeur();
        rect1.height = (*it)->getHauteur();
            
        // On parcourt tous les autres acteurs de la scène
        for(it2 = _acteurs.begin(); it2 != _acteurs.end(); it2++) {
            // Si les deux itérateurs ne pointent pas vers le même acteur
            if((*it2)->getId() != (*it)->getId()) {
                
                // On récupère la hitbox du deuxième acteur
                sf::FloatRect rect2;
                rect2.left = (*it2)->getPosition().x;
                rect2.top = (*it2)->getPosition().y;
                rect2.width = (*it2)->getLargeur();
                rect2.height = (*it2)->getHauteur();
                
                // Test de collision entre deux acteurs
                if(rect1.intersects(rect2))
                    (*it2)->enCollisionAvecActeur(*it);
                
                //Si l'acteur est un méchant, on testera sa vision
                if((*it2)->getType() == acteur::PERSONNAGE) {
                    personnage *p = dynamic_cast<personnage*>((*it2));
                    if(p->getTypePersonnage() == personnage::MECHANT) {
                        mechant *m = dynamic_cast<mechant*>(p);
                        float d = distanceEntrePosition(m->getPosition(), (*it)->getPosition());
                        
                        if(d <= m->getDistanceVision() * 8) {
                            m->acteurDansChampsDeVision((*it));
                        }
                    }
                }
                
            }
        }
            
        if((*it)->getVivant() == false) {
            it = _acteurs.erase(it);
        } else {
            it++;
        }
    }
}

void niveau::afficherActeur(sf::RenderTarget &target) {
    std::list<acteur*>::iterator it;
    
    for(it = _acteurs.begin(); it != _acteurs.end(); ++it) {
        if((*it)->getVisible())
            (*it)->afficher(&target);
    }
}

int niveau::getLargeur() const {
    return _largeur;
}

int niveau::getHauteur() const {
    return _hauteur;
}

void niveau::setEntree(int x, int y) {
    setEntree(sf::Vector2i(x,y));
}

void niveau::setEntree(sf::Vector2i pos) {
    _entree = pos;
}

void niveau::setSortie(int x, int y) {
    setSortie(sf::Vector2i(x,y));
}

void niveau::setSortie(sf::Vector2i pos) {
    _sortie = pos;
}

sf::Vector2i niveau::getEntree() {
    return _entree;
}

sf::Vector2i niveau::getSortie() {
    return _sortie;
}

void niveau::recharger() {
    // On parcourt tous les acteurs de la scène
    for(std::list<acteur*>::iterator it = _acteurs.begin(); it != _acteurs.end(); it++) {
        // On réaffiche tous les acteurs
        (*it)->devoiler();
        
        // Si c'est un personnage
        if((*it)->getType() == acteur::PERSONNAGE) {
            // On récupère le personnage
            personnage *p = dynamic_cast<personnage*>((*it));
            
            // Si le personnage est un joueur...
            if(p->getTypePersonnage() == personnage::JOUEUR) {
                // On récupère le joueur
                joueur *j = dynamic_cast<joueur*>(p);
                
                // On place le joueur au spawn
                j->setPosition(sf::Vector2f(_entree.x * 8, _entree.y * 8));
                // On lui retire sa clef
                j->enleverClef();
                
                // On le rend non-detecté
                j->nonDetecte();
            }
        } 
        
        // Si c'est un objet d'interaction...
        else if((*it)->getType() == acteur::INTERACTIONNABLE) {
            // On récupère l'interactionnable
            interaction *i = dynamic_cast<interaction*>((*it));
            
            // Si c'est un levier...
            if(i->getTypeInterraction() == interaction::LEVIER) {
                // On récupère le levier
                levier *l = dynamic_cast<levier*>(i);
                
                // On le rend non-utilisé
                l->setUtiliser(false);
            } 
            
        }
    }
}

std::vector<interaction*> niveau::getInteractions() {
    std::vector<interaction*> interactions;
    
    for(std::list<acteur*>::iterator it = _acteurs.begin(); it != _acteurs.end(); it++) {
        if((*it)->getType() == acteur::INTERACTIONNABLE) {
            interaction *i = dynamic_cast<interaction*>((*it));
            interactions.push_back(i);
        }
    }
    
    return interactions;
}

void niveau::setBackColor(int r, int g, int b) {
    _backColor.r = r;
    _backColor.g = g;
    _backColor.b = b;
}

sf::Color niveau::getBackColor() {
    return _backColor;
}