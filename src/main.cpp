#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include "niveau.h"
#include "acteur.h"

#include "joueur.h"
#include "chargeurNiveau.h"
#include "TextureManager.h"
#include "BufferManager.h"

#include "GestionnaireNiveau.h"

#include <sstream>
#include <fstream>

#include "menu.h"

// Charger les textures
void chargerTextures();

// Charge les sons 
void chargerSons();

// Charge les différentes tuiles du jeu
void chargerTuiles(std::map<int, tuile> &list);

// Lit un fichier texte pour charger une liste de niveau
bool chargerNiveaux(std::string fichier, std::map<int, tuile> comparaison);

int main (int argc, const char * argv[])
{
    // Creation de la fenetre
    sf::RenderWindow window(sf::VideoMode(800, 600), "Like A Sir");
    window.setFramerateLimit(60);
    
    sf::View view = sf::View(sf::FloatRect(0,0,160,120)); 
    
    bool pause = false;
    bool easterEgg = false;
    
    sf::Shader shader;
    std::string shaderStr = "uniform sampler2D texture;void main() {vec4 texel = texture2D(texture,gl_TexCoord[0].st);vec4 pixel = texel * gl_Color;vec4 pink = vec4(1.0, 0.62, 0.96, pixel.a);float gray = pixel.r * 0.39 + pixel.g * 0.50 + pixel.b * 0.11;gl_FragColor = vec4(gray*2.0,gray*2.0,gray*2.0,pixel.a) * pink;}";
    
    shader.setParameter("texture", sf::Shader::CurrentTexture);
    shader.loadFromMemory(shaderStr, sf::Shader::Fragment);
    
    // On charge les musiques
    sf::Music backMusic_01, backMusic_02;
    backMusic_01.openFromFile("sons/warhead_storage.ogg");
    backMusic_01.play();
    backMusic_01.setLoop(true);
    backMusic_01.setVolume(75);
    
    sf::Music alertMusic;
    alertMusic.openFromFile("sons/escape.ogg");
    
    // On charge les différentes textures
    chargerTextures();
        
    // On charge les différents sons
    chargerSons();
    
    // Création du joueur
    joueur hommeAuChapeau;
    hommeAuChapeau.setTexture(*TextureManager::getInstance()->getTexture("hero"));
    
    // Les différentes tuiles utilisable et la couleur qui leurs sont assignés
    std::map<int, tuile> comparaison;
    chargerTuiles(comparaison);
    
    // On informe le gestionnaire de l'existence du joueur
    gestionnaireNiveau::getInstance()->setJoueur(&hommeAuChapeau);
  
    // On charge les différents niveaux depuis un fichier texte
    chargerNiveaux("niveaux.sir", comparaison);
    
    // On change le niveau pour le premier
    gestionnaireNiveau::getInstance()->changerNiveau(0);
    
    sf::Clock _deltaCompteur;
    
    float delta;
    int tempsAncien = 0;
    
    // La clef affichée
    sf::Sprite uiClef;
    uiClef.setTexture(*TextureManager::getInstance()->getTexture("clef"));
    uiClef.setPosition(750, 560);
    uiClef.scale(5, 5);
    
    // La police 
    sf::Font font;
    font.loadFromFile("Police.ttf");
    
    // Le texte du timer de fuite
    sf::Text _timerJoueur;
    _timerJoueur.setFont(font);
    _timerJoueur.setPosition(50, 30);
    _timerJoueur.setCharacterSize(48);
    
    bool cheatActivated = false;
    
    if(menu(window) == false)
        return EXIT_SUCCESS;
    
    
    // Début de la boucle principale
    while (window.isOpen())
    {
        int tempsDepuisDebut = _deltaCompteur.getElapsedTime().asMilliseconds();
        delta = tempsDepuisDebut - tempsAncien;
        tempsAncien = tempsDepuisDebut;
        
        
        // Gestion de la caméra (Qu'elle ne dépasse pas les bordures de l'écran)
        view.setCenter(hommeAuChapeau.getPosition());
        
        if(view.getCenter().x - view.getSize().x/2 < 0) {
            view.setCenter(view.getSize().x/2, view.getCenter().y);
        }
        
        if(view.getCenter().x + view.getSize().x/2 > gestionnaireNiveau::getInstance()->getNiveauActuel()->getLargeur() * 8) {
            view.setCenter(gestionnaireNiveau::getInstance()->getNiveauActuel()->getLargeur() * 8 - view.getSize().x/2, view.getCenter().y);
        }
        
        if(view.getCenter().y + view.getSize().y/2 > gestionnaireNiveau::getInstance()->getNiveauActuel()->getHauteur() * 8) {
            view.setCenter(view.getCenter().x, gestionnaireNiveau::getInstance()->getNiveauActuel()->getHauteur() * 8 - view.getSize().y/2);
        }
        
        if(view.getCenter().y - view.getSize().y/2 < 0) {
            view.setCenter(view.getCenter().x, view.getSize().y/2);
        }
        
        window.setView(view);
            
        // Récupération des évènements de la fenêtre
        sf::Event event;
        while (window.pollEvent(event))
        {
            // Close window : exit
            if (event.type == sf::Event::Closed)
                window.close();
            
            // Escape pressed : exit
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
                window.close();
            
            if(event.type == sf::Event::KeyPressed) {
                // Avec la touche R, on recharge le niveau
                if(event.key.code == sf::Keyboard::R)
                    gestionnaireNiveau::getInstance()->rechargerNiveauActuel();
                else {
                    // Petite gestion de "cheat codes" pour tester les niveaux rapidement
                    if(event.key.code >= sf::Keyboard::Num0 && event.key.code <= sf::Keyboard::Num9) {
                        int id = event.key.code - sf::Keyboard::Num0;
                        
                        if(cheatActivated)
                            gestionnaireNiveau::getInstance()->changerNiveau(id);
                    } 
                    
                    else if(event.key.code == sf::Keyboard::J) {
                        if(cheatActivated) {
                            hommeAuChapeau.setIndetectable(!hommeAuChapeau.getIndetectable());
                            cheatActivated = false;
                        }
                    } else if(event.key.code == sf::Keyboard::I && easterEgg == false) {
                        backMusic_01.openFromFile("sons/dingDongSong.ogg");
                        backMusic_01.play();
                        
                        easterEgg = true;
                    }
                }
            }
        }
        
        cheatActivated = false;
        
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::LShift) && sf::Keyboard::isKeyPressed(sf::Keyboard::RShift)) {
            cheatActivated = true;
        }
        
        // Gestion de la musique d'Alerte
        if(hommeAuChapeau.getDetecte() && alertMusic.getStatus() != sf::Music::Playing) {
            alertMusic.play();
            alertMusic.setVolume(1.0f);
            
            if(backMusic_01.getVolume() > 1.0f)
                backMusic_01.setVolume(backMusic_01.getVolume() - 1.0f);
        } else if(hommeAuChapeau.getDetecte() == false && alertMusic.getStatus() == sf::Music::Playing) {
            
            
            if(backMusic_01.getVolume() < 75.0f)
                backMusic_01.setVolume(backMusic_01.getVolume() + 1.0f);
        }
        
        if(alertMusic.getStatus() == sf::Music::Playing) {
            if(alertMusic.getVolume() < 75.0f && hommeAuChapeau.getDetecte())
                alertMusic.setVolume(alertMusic.getVolume() + 1.0f);
            else if(alertMusic.getVolume() > 1.0f && hommeAuChapeau.getDetecte() == false) {
                alertMusic.setVolume(alertMusic.getVolume() - 1.0f);
                
                if(alertMusic.getVolume() <= 1.0f)
                    alertMusic.stop();
            }
        }
        

        // Si le jeu est en pause, on ne fait pas de simulation 
        if(!pause)
            gestionnaireNiveau::getInstance()->getNiveauActuel()->rafraichir(delta);
        
        // Efface le contenu de l'écran
        window.clear(sf::Color(100, 100, 100));

        if(easterEgg)
            sf::Shader::bind(&shader);
        
        // On n'affiche que les tuiles visibles à la caméra
        int y1, y2, x1, x2;
        
        x1 = view.getCenter().x - view.getSize().x / 2;
        x1 /= 8;
        
        x1--;
        
        x2 = view.getCenter().x + view.getSize().x / 2;
        x2 /= 8;
        
        x2++;
        
        y1 = view.getCenter().y - view.getSize().y / 2;
        y1 /= 8;
        
        y1--;
        
        y2 = view.getCenter().y + view.getSize().y / 2;
        y2 /= 8;
        
        y2++;
        
        if(x1 < 0)
            x1 = 0;
        
        if(x2 > gestionnaireNiveau::getInstance()->getNiveauActuel()->getLargeur())
            x2 = gestionnaireNiveau::getInstance()->getNiveauActuel()->getLargeur();
        
        if(y1 < 0)
            y1 = 0;
        
        if(y2 > gestionnaireNiveau::getInstance()->getNiveauActuel()->getHauteur())
            y2 = gestionnaireNiveau::getInstance()->getNiveauActuel()->getHauteur();
    
        for(int i = y1 ; i < y2; i++) {
            for(int j = x1 ; j < x2; j++) {
                
                if(gestionnaireNiveau::getInstance()->getNiveauActuel()->getTuile(j, i)->identifiant != 0)
                    window.draw(gestionnaireNiveau::getInstance()->getNiveauActuel()->getTuile(j, i)->_sprite);
            }
        }
        
        gestionnaireNiveau::getInstance()->getNiveauActuel()->afficherActeur(window);
        
        // Affichage de l'interface utilisateur
        window.setView(window.getDefaultView());
        
        if(hommeAuChapeau.getClef())
            window.draw(uiClef);
        
        
        // Si le joueur est détecté, on affiche un petit timer en haut à gauche
        if(hommeAuChapeau.getDetecte()) {
            long timerTimer = hommeAuChapeau.getTempsDetection();
            
            std::stringstream stream;
            stream << timerTimer;
            
            _timerJoueur.setString(stream.str());
            
            if(timerTimer <= 1000) {
                _timerJoueur.setColor(sf::Color(255, 0, 0));
            } else {
                _timerJoueur.setColor(sf::Color(255, 255, 255));
            }
            
            if(timerTimer <= 0) {
                _timerJoueur.setString("Trop Tard!");
            }
            
            if(timerTimer <= -500) {
                gestionnaireNiveau::getInstance()->rechargerNiveauActuel();
            }
            
            if(easterEgg)
                sf::Shader::bind(NULL);
            
            window.draw(_timerJoueur);
        }
        // Rafraichit l'écran
        window.display();
        
        //_deltaCompteur.restart();
    }

    return EXIT_SUCCESS;
}


/**
 * Fonctions de chargement
 */

void chargerTextures() {
    TextureManager::getInstance()->addTexture("tuiles");
    TextureManager::getInstance()->loadTexture("tuiles", "textures/tuiles.png");
    
    TextureManager::getInstance()->addTexture("porte_01");
    TextureManager::getInstance()->loadTexture("porte_01", "textures/porte.png");
    
    TextureManager::getInstance()->addTexture("hero");
    TextureManager::getInstance()->loadTexture("hero", "textures/heroSkin.png");
    
    TextureManager::getInstance()->addTexture("clef");
    TextureManager::getInstance()->loadTexture("clef", "textures/clef.png");
    
    TextureManager::getInstance()->addTexture("mechant");
    TextureManager::getInstance()->loadTexture("mechant", "textures/mechant.png");
    
    TextureManager::getInstance()->addTexture("baril");
    TextureManager::getInstance()->loadTexture("baril", "textures/baril.png");
    
    TextureManager::getInstance()->addTexture("actionIcon");
    TextureManager::getInstance()->loadTexture("actionIcon", "textures/actionPossible.png");
    
    TextureManager::getInstance()->addTexture("levier");
    TextureManager::getInstance()->loadTexture("levier", "textures/levier.png");
}

void chargerSons() {
    BufferManager::getInstance()->addBuffer("jump");
    BufferManager::getInstance()->loadBuffer("jump", "sons/saut.wav");
    
    BufferManager::getInstance()->addBuffer("clef");
    BufferManager::getInstance()->loadBuffer("clef", "sons/clef.wav");
    
    BufferManager::getInstance()->addBuffer("hurt");
    BufferManager::getInstance()->loadBuffer("hurt", "sons/fermee.wav");
    
    BufferManager::getInstance()->addBuffer("fermee");
    BufferManager::getInstance()->loadBuffer("fermee", "sons/fermee.wav");
    
    BufferManager::getInstance()->addBuffer("levier");
    BufferManager::getInstance()->loadBuffer("levier", "sons/levier.wav");
}

void chargerTuiles(std::map<int, tuile> &list) {
    sf::Color col(255,255,255);
    tuile Tuile;
    
    // Air
    Tuile.identifiant = 0;
    Tuile.mur = false;
    Tuile._sprite.setTexture(*TextureManager::getInstance()->getTexture("tuiles"));
    list[convertirCouleurEnInt(col)] = Tuile;
    
    // Métal/Pierre
    col = sf::Color(0,0,0);
    Tuile.identifiant = 1;
    Tuile.mur = true;
    Tuile._sprite.setTexture(*TextureManager::getInstance()->getTexture("tuiles"));
    list[convertirCouleurEnInt(col)] = Tuile;
    
    // Métal/Pierre
    col = sf::Color(0,100,100);
    Tuile.identifiant = 5;
    Tuile.mur = true;
    Tuile._sprite.setTexture(*TextureManager::getInstance()->getTexture("tuiles"));
    list[convertirCouleurEnInt(col)] = Tuile;
    
    // Métal/Pierre
    col = sf::Color(0,100,200);
    Tuile.identifiant = 6;
    Tuile.mur = true;
    Tuile._sprite.setTexture(*TextureManager::getInstance()->getTexture("tuiles"));
    list[convertirCouleurEnInt(col)] = Tuile;
    
    // Métal/Pierre
    col = sf::Color(0,100,255);
    Tuile.identifiant = 10;
    Tuile.mur = true;
    Tuile._sprite.setTexture(*TextureManager::getInstance()->getTexture("tuiles"));
    list[convertirCouleurEnInt(col)] = Tuile;
    
    // Métal/Pierre Mur
    col = sf::Color(0,200,0);
    Tuile.identifiant = 7;
    Tuile.mur = false;
    Tuile._sprite.setTexture(*TextureManager::getInstance()->getTexture("tuiles"));
    list[convertirCouleurEnInt(col)] = Tuile;
    
    // Métal/Pierre Mur
    col = sf::Color(0,200,100);
    Tuile.identifiant = 8;
    Tuile.mur = false;
    Tuile._sprite.setTexture(*TextureManager::getInstance()->getTexture("tuiles"));
    list[convertirCouleurEnInt(col)] = Tuile;
    
    // Gazon
    col = sf::Color(255,0,255);
    Tuile.identifiant = 2;
    Tuile.mur = true;
    Tuile._sprite.setTexture(*TextureManager::getInstance()->getTexture("tuiles"));
    list[convertirCouleurEnInt(col)] = Tuile;
    
    // Terre
    col = sf::Color(0,255,0);
    Tuile.identifiant = 3;
    Tuile.mur = true;
    Tuile._sprite.setTexture(*TextureManager::getInstance()->getTexture("tuiles"));
    list[convertirCouleurEnInt(col)] = Tuile;
    
    // Tronc
    col = sf::Color(10,24,30);
    Tuile.identifiant = 9;
    Tuile.mur = false;
    Tuile._sprite.setTexture(*TextureManager::getInstance()->getTexture("tuiles"));
    list[convertirCouleurEnInt(col)] = Tuile;
    
    // Tronc-centre
    col = sf::Color(10,24,53);
    Tuile.identifiant = 4;
    Tuile.mur = false;
    Tuile._sprite.setTexture(*TextureManager::getInstance()->getTexture("tuiles"));
    list[convertirCouleurEnInt(col)] = Tuile;
    
    // Tronc-centre_branche
    col = sf::Color(10,24,100);
    Tuile.identifiant = 14;
    Tuile.mur = false;
    Tuile._sprite.setTexture(*TextureManager::getInstance()->getTexture("tuiles"));
    list[convertirCouleurEnInt(col)] = Tuile;
    
    // Touffe
    col = sf::Color(10,24,200);
    Tuile.identifiant = 19;
    Tuile.mur = false;
    Tuile._sprite.setTexture(*TextureManager::getInstance()->getTexture("tuiles"));
    list[convertirCouleurEnInt(col)] = Tuile;
    
    // Touffe
    col = sf::Color(60,60,0);
    Tuile.identifiant = 11;
    Tuile.mur = false;
    Tuile._sprite.setTexture(*TextureManager::getInstance()->getTexture("tuiles"));
    list[convertirCouleurEnInt(col)] = Tuile;
    
    col = sf::Color(60,60,100);
    Tuile.identifiant = 12;
    Tuile.mur = false;
    Tuile._sprite.setTexture(*TextureManager::getInstance()->getTexture("tuiles"));
    list[convertirCouleurEnInt(col)] = Tuile;
}

bool chargerNiveaux(std::string fichier, std::map<int, tuile> comparaison) {
    std::ifstream entree;
    // On ouvre le fichier
    entree.open(fichier.c_str());
    
    // On retourne faux si le fichier n'est pas ouvert
    if(entree.is_open() == false)
        return false;
    
    std::string line;
    sf::Image image;
    niveau niv;
    
    // Sinon on lit toutes les lignes pour trouver les images des niveaux
    while(entree.good()) {
        getline(entree, line);
        
        image.loadFromFile("niveaux/" + line);
        niv = chargeurNiveau::chargerNiveauDeImage(image, comparaison);
        gestionnaireNiveau::getInstance()->ajouterNiveau(niv);
    }
    
    return true;
}
