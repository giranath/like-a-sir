/*
 * FICHIER: TextureManager.h
 * PROJET:  Unicorn
 *
 * AUTHEUR: Nathan
 * DATE:    2013-04-28
 *
 * Il s'agit d'un gestionnaire de texture (pris d'un projet personnel) Permettant de simplifier l'utilisation de texture.
 * Une seule instanciation est possible (Singleton)
 */

#ifndef __Amanita__TextureManager__
#define __Amanita__TextureManager__

#include <iostream>
#include <SFML/Graphics.hpp>

#include <map>
#include "Singleton.h"

class TextureManager : public Singleton<TextureManager> {
    friend class Singleton<TextureManager>;
public:
    bool addTexture(std::string name);
    bool removeTexture(std::string name);
    
    bool loadTexture(std::string name, std::string path);
    sf::Texture *getTexture(std::string name);
    
private:
    TextureManager();
    ~TextureManager();
    std::map<std::string, sf::Texture*> _textures;
};

#endif /* defined(__Amanita__TextureManager__) */
