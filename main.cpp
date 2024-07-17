#include <SFML/Graphics.hpp>
#include<SFML/Audio.hpp>
#include <iostream>
#include <ctime>
#include <string>
#include <fstream>
#include <vector>
#include <algorithm>
#define NBmax_piece 15
#include "Plateau.h" // Supposons que Plateau.h contient la définition de la classe Plateau et des pièces
#include "ScoreManager.h"

/// Variable globale pour suivre si le jeu a commencé.
bool isGameStarted = false;

/// Déclaration des fonctions pour afficher le menu et démarrer le jeu.
void displayMenu(sf::RenderWindow& window);
void startGame(sf::RenderWindow& window);

/// Fonction pour afficher les règles du jeu dans une nouvelle fenêtre.
void afficherRegleGame(){
    // Créer la fenêtre avec une taille spécifique et un titre.
    sf::RenderWindow window(sf::VideoMode(800, 600), "Régle de jeux");

    // Charger la texture pour l'arrière-plan. Si le chargement échoue, afficher un message d'erreur.
    sf::Texture texture;
    if (!texture.loadFromFile("Game_Regle.png")) {
       std::cout << "image non afficher\n";
    }

    // Créer le sprite pour l'arrière-plan et lui attribuer la texture chargée.
    sf::Sprite background(texture);

    // Boucle de jeu pour gérer les événements et afficher le contenu.
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // Effacer l'écran, dessiner l'arrière-plan, puis afficher le contenu.
        window.clear();
        window.draw(background);
        window.display();
    }
}

/// Fonction pour afficher l'écran de fin de jeu (game over).
void afficherGameOver() {
    // Charger la texture pour l'arrière-plan. Si le chargement échoue, afficher un message d'erreur.
    sf::Texture backgroundTexture;
    if (!backgroundTexture.loadFromFile("Imgame_over.gif")) {
        std::cout << "Erreur de chargement de l'image de fond" << std::endl;
        return;
    }
    sf::Sprite background(backgroundTexture);

    // Créer une nouvelle fenêtre avec une taille spécifique et un titre.
    sf::RenderWindow window(sf::VideoMode(500, 300), "Game Over");

    // Créer un sprite animé à partir de plusieurs images.
    AnimatedSprite sprite;
    for (int i = 1; i <= 16; ++i) {
        sf::Texture texture;
        texture.loadFromFile("frame" + std::to_string(i) + ".png");
        sprite.addFrame(texture);
    }

    // Boucle principale de la fenêtre pour gérer les événements et afficher le contenu.
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        // Mettre à jour le sprite animé.
        sprite.update();

        // Effacer l'écran, dessiner l'image de fond et le sprite, puis afficher le tout.
        window.clear();
        window.draw(background);
        window.draw(sprite);
        window.display();
    }
}




int main() {
    sf::RenderWindow window(sf::VideoMode(920, 520), "Game Menu");

    // Initialisation du menu
    displayMenu(window);

    return 0;
}

void displayMenu(sf::RenderWindow& window) {
    sf::Font font;
    if (!font.loadFromFile("geo_1.ttf")) {
        std::cout << "Erreur de chargement de la police" << std::endl;
        return;
    }

    sf::Texture backgroundTexture;
    if (!backgroundTexture.loadFromFile("imageBk.png")) {
        std::cout << "Erreur de chargement de l'image de fond" << std::endl;
        return;
    }

    sf::Sprite background(backgroundTexture);

    sf::RectangleShape frame(sf::Vector2f(300.f, 370.f));
    frame.setPosition(window.getSize().x / 2 - frame.getSize().x / 2, 150.f);
    frame.setFillColor(sf::Color::Transparent);
    frame.setOutlineThickness(5.f);
    frame.setOutlineColor(sf::Color::Black);

    sf::RectangleShape button1(sf::Vector2f(200.f, 50.f));
    button1.setPosition(window.getSize().x / 2 - button1.getSize().x / 2, 200.f);
    button1.setFillColor(sf::Color(255, 255, 255, 128)); // Blanc semi-transparent

    sf::Text menu1("Start Game", font);
    menu1.setCharacterSize(24);
    menu1.setStyle(sf::Text::Bold);
    menu1.setPosition(button1.getPosition().x + button1.getSize().x / 2 - menu1.getGlobalBounds().width / 2,
                      button1.getPosition().y + button1.getSize().y / 2 - menu1.getGlobalBounds().height / 1.5);
    menu1.setFillColor(sf::Color::Black);

    sf::RectangleShape button2(sf::Vector2f(200.f, 50.f));
    button2.setPosition(window.getSize().x / 2 - button2.getSize().x / 2, 280.f); // Position ajustée
    button2.setFillColor(sf::Color(255, 255, 255, 128));

    sf::Text menu2("Régle de jeux", font);
    menu2.setCharacterSize(24);
    menu2.setStyle(sf::Text::Bold);
    menu2.setPosition(button2.getPosition().x + button2.getSize().x / 2 - menu2.getGlobalBounds().width / 2,
                      button2.getPosition().y + button2.getSize().y / 2 - menu2.getGlobalBounds().height / 1.5);
    menu2.setFillColor(sf::Color::Black);

    sf::RectangleShape button3(sf::Vector2f(200.f, 50.f));
    button3.setPosition(window.getSize().x / 2 - button3.getSize().x / 2, 360.f); // Position ajustée
    button3.setFillColor(sf::Color(255, 255, 255, 128));

    sf::Text menu3("Exit", font);
    menu3.setCharacterSize(24);
    menu3.setStyle(sf::Text::Bold);
    menu3.setPosition(button3.getPosition().x + button3.getSize().x / 2 - menu3.getGlobalBounds().width / 2,
                      button3.getPosition().y + button3.getSize().y / 2 - menu3.getGlobalBounds().height / 1.5);
    menu3.setFillColor(sf::Color::Black);


    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::MouseButtonPressed) {
                if (event.mouseButton.button == sf::Mouse::Left) {
                    if (!isGameStarted && button1.getGlobalBounds().contains(window.mapPixelToCoords(sf::Mouse::getPosition(window)))) {
                        isGameStarted = true;
                        window.clear();
                        startGame(window);
                    }
                    // Ajoutez ici la gestion des clics sur les autres boutons du menu...
                    else if
                        (button3.getGlobalBounds().contains(window.mapPixelToCoords(sf::Mouse::getPosition(window)))) {

                        window.close();

                    }else if (button2.getGlobalBounds().contains(window.mapPixelToCoords(sf::Mouse::getPosition(window)))){
                        afficherRegleGame();
                    }
                }
            }
        }


        if (event.type == sf::Event::MouseMoved) {
            // Changement de couleur des boutons lorsque la souris se déplace
           if (event.type == sf::Event::MouseMoved)
            {
                if (button1.getGlobalBounds().contains(window.mapPixelToCoords(sf::Mouse::getPosition(window))))
                {
                    button1.setFillColor(sf::Color::Yellow);
                }
                else
                {
                    button1.setFillColor(sf::Color(255, 255, 255, 128));
                }

                if (button2.getGlobalBounds().contains(window.mapPixelToCoords(sf::Mouse::getPosition(window))))
                {
                    button2.setFillColor(sf::Color::Green);
                }
                else
                {
                    button2.setFillColor(sf::Color(255, 255, 255, 128));
                }

                if (button3.getGlobalBounds().contains(window.mapPixelToCoords(sf::Mouse::getPosition(window))))
                {
                    button3.setFillColor(sf::Color::Blue);
                }
                else
                {
                    button3.setFillColor(sf::Color(255, 255, 255, 128));
                }
            }
        }


         window.clear();
        window.draw(background);
        window.draw(frame);
        window.draw(button1);
        window.draw(menu1);
        window.draw(button2);
        window.draw(menu2);
        window.draw(button3);
        window.draw(menu3);
        window.display();
    }
}

void startGame(sf::RenderWindow& window) {

      Plateau plateau; // Création du plateau de jeu
     std::string nomJoueur = plateau.demanderNomJoueur();
    std::string nomFichier = "savegame.txt";
   // sauvegarderEtatJeu(etatJeu);

    srand(static_cast<unsigned int>(time(0)));

    sf::Clock clock; // Créez une horloge pour suivre le temps



    sf::Color couleurs[4] = { sf::Color::Red, sf::Color::Green, sf::Color::Blue, sf::Color::Yellow };
    std::string formes[4] = { "Carre", "Losange", "Circle", "Triangle" };
    for (int i = 0; i < 4; ++i) {
        sf::Color color = couleurs[i];
        string forme = formes[i];
        Piece* newPiece = new Piece(color, forme);
        plateau.insererDroite(newPiece);
    }

    sf::RenderWindow gameWindow(sf::VideoMode(800, 600), "Tetris", sf::Style::Resize | sf::Style::Titlebar | sf::Style::Close);


         Piece* newPiece = new Piece(couleurs[rand() % 4], formes[rand() % 4]);
        plateau.afficherPieceAInserer(gameWindow, newPiece, gameWindow.getSize().x / 2 - 25); // Affichage au centre de la fenêtre


    while (gameWindow.isOpen()) {
        sf::Event event;
        while (gameWindow.pollEvent(event)) {
            switch (event.type) {
                case sf::Event::Closed:
                    gameWindow.close();
                    break;
                case sf::Event::Resized:
                    gameWindow.setView(sf::View(sf::FloatRect(0, 0, event.size.width, event.size.height)));
                    break;
                case sf::Event::KeyPressed:

                  if(newPiece==nullptr)
{
    newPiece = new Piece(couleurs[rand() % 4], formes[rand() % 4]);
    plateau.afficherPieceAInserer(gameWindow, newPiece, gameWindow.getSize().x / 2 - 25); // Affichage au centre de la fenêtre
}


         if (event.key.code == sf::Keyboard::G) {
                    // Insérer la pièce à gauche
                    plateau.insererGauche(newPiece);
                    newPiece = nullptr;
                     // Créer et afficher une nouvelle pièce
    newPiece = new Piece(couleurs[rand() % 4], formes[rand() % 4]);
    plateau.afficherPieceAInserer(gameWindow, newPiece, gameWindow.getSize().x / 2 - 25); // Affichage au centre de la fenêtr

                }

        else if (event.key.code == sf::Keyboard::D) {
            // Insérer la pièce à droite
            plateau.insererDroite(newPiece);
            newPiece = nullptr; //
             // Créer et afficher une nouvelle pièce
    newPiece = new Piece(couleurs[rand() % 4], formes[rand() % 4]);
    plateau.afficherPieceAInserer(gameWindow, newPiece, gameWindow.getSize().x / 2 - 25); // Affichage au centre de la fenêtr


    }else if (event.key.code == sf::Keyboard::V) {
           // Décalage circulaire pour les pièces vertes
            plateau.decalerParCouleur(sf::Color::Green);

        }
        else if (event.key.code == sf::Keyboard::R) {
            // Décalage à gauche par forme
            plateau.decalerParCouleur(sf::Color::Red);

    }else if(event.key.code == sf::Keyboard::J){
        // Décalage à gauche par forme
            plateau.decalerParCouleur(sf::Color::Yellow);
    }else if(event.key.code == sf::Keyboard::B){
        // Décalage à gauche par forme
            plateau.decalerParCouleur(sf::Color::Blue);
    }else if(event.key.code == sf::Keyboard::C){
         // Décalage à gauche par forme
            plateau.decalerParForme("Circle");
    }else if(event.key.code == sf::Keyboard::T){
        // Décalage à gauche par forme
            plateau.decalerParForme("Triangle");
    }else if(event.key.code == sf::Keyboard::L){
          // Décalage à gauche par forme
            plateau.decalerParForme("Losange");
    }else if(event.key.code == sf::Keyboard::A){

        // Décalage à gauche par forme
            plateau.decalerParForme("Carre");
    }
                    break;
                default:
                    break;
            }
        }
          // Vérifiez l'état du jeu ici
    if (plateau.estVide() || plateau.nombreDePieces() > NBmax_piece) {
        afficherGameOver();
        break; // Sortez de la boucle de jeu
    }




        plateau.supprimerTriplets_memeCouleur();
        plateau.supprimerTriplets_memeForme();
sf::Font font;

    if (!font.loadFromFile("Sunny Spells Basic.ttf")) {
        std::cout << "Erreur de chargement de la police" << std::endl;
        return;
    }
        gameWindow.clear();

        plateau.afficherPieceAInserer(gameWindow, newPiece, gameWindow.getSize().x / 2 - 25); // Affichage au centre de la fenêtre
        plateau.afficherPieces(gameWindow, 50, 200);
        plateau.score_Afficher(gameWindow, font);
          // Mettez à jour timeElapsed à chaque tour de boucle
        plateau.timeElapsed = clock.getElapsedTime();
            plateau.afficherTemps(gameWindow,font);
    // Réinitialisez l'horloge après avoir obtenu le temps écoulé
    clock.restart();


        plateau.Level_Afficher(gameWindow,font);
        plateau.afficherInformations(gameWindow,font);
        sauvegarderEtatJeu(etatJeu);

        gameWindow.display();
    }

}
