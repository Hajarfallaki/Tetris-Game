#ifndef PLATEAU_H_INCLUDED
#define PLATEAU_H_INCLUDED

/// Inclusion des bibliothèques standard et définitions
#include <iostream>
#include <vector>
#include <map>
#include <cstdlib>
#include <ctime>

/// Définition du nombre maximum de pièces
#define NBmax_piece 15
using namespace std;

/// Déclaration de la classe AnimatedSprite, qui hérite de sf::Sprite
class AnimatedSprite : public sf::Sprite {
public:
    // Ajoute une texture à la liste des frames
    void addFrame(sf::Texture texture) {
        frames.push_back(texture);
    }

    // Met à jour la frame actuelle en fonction du temps écoulé
    void update() {
        static sf::Clock clock; // Horloge pour mesurer le temps écoulé
        sf::Time elapsed = clock.getElapsedTime();

        // Change de frame toutes les 0.1 secondes
        if (elapsed.asSeconds() > 0.1) {
            currentFrame = (currentFrame + 1) % frames.size();
            setTexture(frames[currentFrame]);
            clock.restart();
        }
    }

private:
    std::vector<sf::Texture> frames; // Liste des textures pour l'animation
    int currentFrame = 0; // Index de la frame actuelle
};

/// Structure représentant l'état du jeu
struct EtatJeu {
    std::string nomJoueur; // Nom du joueur
    int score; // Score actuel
    int niveau; // Niveau actuel
    float temps; // Temps écoulé
};

/// Instance globale de EtatJeu
EtatJeu etatJeu;

///Déclaration anticipée de la classe Piece pour résoudre la dépendance circulaire
class Piece;

/// Déclaration de la classe PieceGraphique, qui associe une forme graphique à une pièce
class PieceGraphique {
public:
    sf::RectangleShape shape; // Forme rectangulaire par défaut
    Piece* piece; // Pointeur vers la pièce associée

    // Constructeur de PieceGraphique
    PieceGraphique(const sf::Vector2f& size, Piece* piece, const sf::Color& color, const sf::Vector2f& position)
        : piece(piece) {
        shape.setSize(size);
        shape.setFillColor(color);
        shape.setPosition(position);
    }

    // Dessine la forme graphique dans la fenêtre
    void draw(sf::RenderWindow& window) {
        window.draw(shape);
    }

    // Retourne le pointeur vers la pièce associée
    Piece* getPiece() { return piece; }
};

///Classe Piece : représente une pièce de jeu avec des attributs pour la couleur et la forme,
///ainsi que des pointeurs vers d'autres pièces dans une structure de liste chaînée.

class Piece {
private:
    sf::Color couleur; // Couleur de la pièce
    std::string forme; // Forme géométrique de la pièce
    // Pointeurs vers les pièces adjacentes dans la liste chaînée
    Piece* suivante; // Pièce suivante dans la liste
    Piece* precedente; // Pièce précédente dans la liste
    // Pointeurs vers les pièces de même forme, permettant de créer une sous-liste
    Piece* suivanteMemeForme; // Pièce suivante de même forme
    Piece* precedenteMemeForme; // Pièce précédente de même forme

public:
    // Constructeur de la classe Piece initialisant les attributs et les pointeurs à nullptr
    Piece(const sf::Color& color, const std::string& form)
        : couleur(color), forme(form), suivante(nullptr), precedente(nullptr),
        suivanteMemeForme(nullptr), precedenteMemeForme(nullptr) {}

    // Getters : fonctions pour obtenir les valeurs des attributs
    sf::Color getCouleur() const { return couleur; }
    std::string getForme() const { return forme; }
    Piece* getSuivante() { return suivante; }
    Piece* getPrecedente() { return precedente; }
    Piece* getSuivanteMemeForme() { return suivanteMemeForme; }
    Piece* getPrecedenteMemeForme() { return precedenteMemeForme; }

    // Setters : fonctions pour définir les valeurs des attributs
    void setSuivante(Piece* suiv) { suivante = suiv; }
    void setPrecedente(Piece* prec) { precedente = prec; }
    void setCouleur(const sf::Color& clr) { couleur = clr; }
    void setForme(const std::string& newForme) { forme = newForme;}
    void setSuivanteMemeForme(Piece* suiv) { suivanteMemeForme = suiv; }
    void setPrecedenteMemeForme(Piece* prec) { precedenteMemeForme = prec; }
    // Fonctions pour comparer les attributs avec une autre pièce
    bool aMemeForme(Piece* autrePiece) { return this->forme == autrePiece->forme; }
    bool aMemeCouleur(Piece* autrePiece) { return this->couleur == autrePiece->couleur; }
};

///Les classes suivantes définissent des formes géométriques spécifiques en héritant de sf::Shape.
///   Chaque classe initialise la forme avec un nombre de points et une couleur spécifiques.

///Classe Triangle : forme géométrique d'un triangle équilatéral
class Triangle : public sf::ConvexShape {
public:
    Triangle(float size, const sf::Color& color) {
        setPointCount(3); // Définit le nombre de points (sommets) du triangle
        // Définit les points du triangle pour former un triangle équilatéral
        setPoint(0, sf::Vector2f(0, 0));
        setPoint(1, sf::Vector2f(size, 0));
        setPoint(2, sf::Vector2f(size / 2, size * 0.866f)); // Hauteur d'un triangle équilatéral
        setFillColor(color); // Définit la couleur de remplissage du triangle
    }
};

/// Classe Carre : forme géométrique d'un carré
class Carre : public sf::RectangleShape {
public:
    Carre(float size, const sf::Color& color) {
        setSize(sf::Vector2f(size, size)); // Définit la taille du carré
        setFillColor(color); // Définit la couleur de remplissage du carré
    }
};

/// Classe Losange : forme géométrique d'un losange
class Losange : public sf::ConvexShape {
public:
    Losange(float size, const sf::Color& color) {
        setPointCount(4); // Définit le nombre de points (sommets) du losange
        // Définit les points du losange pour former la forme spécifique
        setPoint(0, sf::Vector2f(size / 2, 0));
        setPoint(1, sf::Vector2f(size, size / 2));
        setPoint(2, sf::Vector2f(size / 2, size));
        setPoint(3, sf::Vector2f(0, size / 2));
        setFillColor(color); // Définit la couleur de remplissage du losange
    }
};

/// Classe Circle : forme géométrique d'un cercle
class Circle : public sf::CircleShape {
public:
    Circle(float radius, const sf::Color& color) {
        setRadius(radius); // Définit le rayon du cercle
        setFillColor(color); // Définit la couleur de remplissage du cercle
    }
};



/// Déclaration de la classe Plateau qui gère un ensemble de pièces dans un jeu.
class Plateau {
public:
    // Pointeurs vers la première et la dernière pièce de la liste chaînée.
    Piece* debut;
    Piece* fin;
    // Score actuel du joueur.
    int score;
    // Indicateur de décalage effectué pour les opérations de jeu.
    bool decalageEffectue;
    // Buffer pour stocker les sons à jouer.
    sf::SoundBuffer buffer;
    // Objet son pour jouer des effets sonores.
    sf::Sound sound;

public:
    // Constructeur par défaut qui initialise les membres de la classe.
    Plateau() : debut(nullptr), fin(nullptr), score(0), decalageEffectue(false) {}

    // Destructeur qui libère la mémoire allouée pour les pièces.
    ~Plateau() {
        while (debut != nullptr) {
            Piece* temp = debut;
            debut = debut->getSuivante();
            delete temp;
        }
    }

    // Méthodes pour insérer des pièces à gauche ou à droite.
    void insererGauche(Piece* piece);
    void insererDroite(Piece* piece);

    // Méthode pour afficher les pièces sur le plateau.
    void afficherPieces(sf::RenderWindow& window, float x, float y);

    // Méthode pour afficher une pièce à insérer à une position donnée.
    void afficherPieceAInserer(sf::RenderWindow& window, Piece* piece, float positionX) {
        if (piece != nullptr) {
            sf::Shape* shape = nullptr;
            // Création d'une forme graphique selon la forme de la pièce.
            if (piece->getForme() == "Triangle") {
                shape = new Triangle(50, piece->getCouleur());
            } else if (piece->getForme() == "Carre") {
                shape = new Carre(50, piece->getCouleur());
            } else if (piece->getForme() == "Losange") {
                shape = new Losange(50, piece->getCouleur());
            } else if (piece->getForme() == "Circle") {
                shape = new Circle(25, piece->getCouleur());
            }

            // Si une forme a été créée, l'afficher puis la supprimer.
            if (shape != nullptr) {
                shape->setPosition(positionX, 50.0f);
                window.draw(*shape);
                delete shape;
            }
        }
    };

    // Méthode pour vérifier si le plateau est vide.
    bool estVide() const {
        return debut == nullptr;
    };

    /// Diverses méthodes pour gérer le score et les opérations de jeu.
    void score_jeux();
    void supprimer(Piece* piece);
    void supprimerTriplets_memeCouleur();
    void supprimerTriplets_memeForme();
    void decalerParForme(const std::string& forme);
    void decalerParCouleur(const sf::Color& couleur);
    void score_jeux1();
    void setDecalageEffectue(bool value);

    // Méthodes pour afficher le score, le temps, le niveau et d'autres informations.
    void score_Afficher(sf::RenderWindow& window, const sf::Font& font) const;
    int nombreDePieces() const;
    sf::Time timeElapsed;
    void afficherTemps(sf::RenderWindow& window, const sf::Font& font);
    void Level_Afficher(sf::RenderWindow& window, const sf::Font& font);
    void afficherInformations(sf::RenderWindow& window, const sf::Font& font);

    // Méthode pour demander le nom du joueur.
    std::string demanderNomJoueur();

    // Méthode pour afficher le plateau.
    void afficher() const;
};

/// Méthode pour insérer une pièce à l'extrémité Gauche  du plateau.
void Plateau::insererGauche(Piece* piece) {
    if (!debut) {
        debut = piece;
        fin = piece;
    }
    else {
        piece->setSuivante(debut);
        debut->setPrecedente(piece);
        debut = piece;

        // Mettre à jour les liens avec les pièces de même forme
        Piece* current = piece->getSuivante();
        while (current != nullptr && current != piece) {
            if (current->getForme() == piece->getForme()) {
                piece->setSuivanteMemeForme(current);
                current->setPrecedenteMemeForme(piece);
                break; // Ne cherchez que la première pièce de même forme à droite
            }
            current = current->getSuivante();
        }
    }
}

/// Méthode pour insérer une pièce à l'extrémité droite du plateau.
void Plateau::insererDroite(Piece* piece) {
    // Si le plateau est vide, initialisez-le avec la nouvelle pièce.
    if (!debut) {
        debut = piece;
        fin = piece;
    }
    else {
        // Sinon, liez la nouvelle pièce à la fin de la liste chaînée.
        piece->setPrecedente(fin);
        fin->setSuivante(piece);
        fin = piece;

        // Mettre à jour les liens avec les pièces de même forme.
        Piece* current = piece->getPrecedente();
        while (current != nullptr && current != piece) {
            if (current->getForme() == piece->getForme()) {
                piece->setPrecedenteMemeForme(current);
                current->setSuivanteMemeForme(piece);
                break; // Arrêtez la recherche après avoir trouvé la première correspondance.
            }
            current = current->getPrecedente();
        }
    }
}


/// Méthode pour afficher toutes les pièces présentes sur le plateau
void Plateau::afficherPieces(sf::RenderWindow& window, float x, float y) {
    float posX = x;
    float posY = y;
    Piece* current = debut;

     // Parcourez chaque pièce et créez une forme graphique correspondante.
    while (current != nullptr) {
        sf::Shape* shape = nullptr;
        // Créez une forme en fonction de la forme de la pièce
        if (current->getForme() == "Triangle") {
            shape = new Triangle(50, current->getCouleur()); // Triangle size
        }
        else if (current->getForme() == "Carre") {
            shape = new Carre(50, current->getCouleur()); // Square size
        }
        else if (current->getForme() == "Losange") {
            shape = new Losange(50, current->getCouleur()); // Losange size
        }
        else if (current->getForme() == "Circle") {
            shape = new Circle(25, current->getCouleur()); // Circle radius
        }
        // Add conditions for other piece shapes...

        if (shape != nullptr) {
            shape->setPosition(posX, posY);
            window.draw(*shape);
            delete shape; // Free dynamically allocated memory
        }
   // Déplacez la position X pour la prochaine pièce
        posX += 100.0f;
        current = current->getSuivante();
    }
}


/// Méthode pour supprimer une pièce spécifique du plateau.
void Plateau::supprimer(Piece* piece_supprimer) {
    // Si le plateau est vide, il n'y a rien à faire.
    if (!debut) {
        cout << "Le plateau est vide !!!\n";
        return;
    }
    // Gérez la suppression de la pièce en fonction de sa position.
    if (piece_supprimer == debut && piece_supprimer == fin) {
    // Si c'est la seule pièce, videz le plateau.
        debut = nullptr;
        fin = nullptr;
    }
    else if (piece_supprimer == debut) {
    // Si c'est la première pièce, mettez à jour le début.
        debut = debut->getSuivante();
        debut->setPrecedente(nullptr);
    }
    else if (piece_supprimer == fin) {
    // Si c'est la dernière pièce, mettez à jour la fin.
        fin = fin->getPrecedente();
        fin->setSuivante(nullptr);
    }
    else {
        // Sinon, reliez les pièces précédente et suivante entre elles.
        piece_supprimer->getPrecedente()->setSuivante(piece_supprimer->getSuivante());
        piece_supprimer->getSuivante()->setPrecedente(piece_supprimer->getPrecedente());
    }
    // Libérez la mémoire allouée pour la pièce supprimée.
    delete piece_supprimer;
}
/// Méthode pour supprimer les triplets de pièces de même couleur.
void Plateau::supprimerTriplets_memeCouleur() {
    // Vérifiez si le plateau est vide avant de commencer.
    if (!debut) {
        cout << "Le plateau est vide." << endl;
        return;
    }

    // Commencez par la première pièce.
    Piece* currentPiece = debut;
    // Continuez tant qu'il y a des pièces sur le plateau.
    while (currentPiece != nullptr) {
        // Obtenez la pièce suivante dans la liste.
        Piece* nextPiece = currentPiece->getSuivante();
        // Si la fin de la liste est atteinte, arrêtez la boucle.
        if (nextPiece == nullptr) break;
        // Obtenez la pièce après la suivante.
        Piece* nextNextPiece = nextPiece->getSuivante();

        // Si la fin de la liste est atteinte, arrêtez la boucle.
        if (nextNextPiece == nullptr) break;
        // Vérifiez si les trois pièces consécutives ont la même couleur.
        if (currentPiece->getCouleur() == nextPiece->getCouleur() && nextPiece->getCouleur() == nextNextPiece->getCouleur()) {
            // Si oui, supprimez ces trois pièces.
            supprimer(currentPiece);
            supprimer(nextPiece);
            supprimer(nextNextPiece);
            // Mettez à jour le score après la suppression.
            score_jeux();
            // Recommencez à partir du début de la liste.
            currentPiece = debut;
            continue;
        }

        // Passez à la pièce suivante dans la liste.
        currentPiece = currentPiece->getSuivante();
    }
}


/// Méthode pour supprimer les triplets de pièces de même forme.
void Plateau::supprimerTriplets_memeForme() {
    // Vérifiez si le plateau est vide avant de commencer.
    if (!debut) {
        cout << "Le plateau est vide." << endl;
        return;
    }

    // Commencez par la première pièce.
    Piece* currentPiece = debut;
    // Continuez tant qu'il y a des pièces sur le plateau.
    while (currentPiece != nullptr) {
        // Obtenez la pièce suivante dans la liste.
        Piece* nextPiece = currentPiece->getSuivante();
        // Si la fin de la liste est atteinte, arrêtez la boucle.
        if (nextPiece == nullptr) break;
        // Obtenez la pièce après la suivante.
        Piece* nextNextPiece = nextPiece->getSuivante();

        // Si la fin de la liste est atteinte, arrêtez la boucle.
        if (nextNextPiece == nullptr) break;
        // Vérifiez si les trois pièces consécutives ont la même forme.
        if (currentPiece->getForme() == nextPiece->getForme() && nextPiece->getForme() == nextNextPiece->getForme()) {
            // Si oui, supprimez ces trois pièces.
            supprimer(currentPiece);
            supprimer(nextPiece);
            supprimer(nextNextPiece);
            // Mettez à jour le score après la suppression.
            score_jeux();
            // Recommencez à partir du début de la liste.
            currentPiece = debut;
            continue;
        }

        // Passez à la pièce suivante dans la liste.
        currentPiece = currentPiece->getSuivante();
    }
}


///Fonction pour obtenir le nom d'une couleur SFML sous forme de chaîne de caractères.
std::string getColorName(const sf::Color& color) {
    // Compare la couleur passée en paramètre avec les couleurs prédéfinies de SFML.
    if (color == sf::Color::Red) {
        return "Red"; // Retourne "Red" si la couleur est rouge.
    }
    else if (color == sf::Color::Green) {
        return "Green"; // Retourne "Green" si la couleur est verte.
    }
    else if (color == sf::Color::Blue) {
        return "Blue"; // Retourne "Blue" si la couleur est bleue.
    }
    else if (color == sf::Color::Yellow) {
        return "Yellow"; // Retourne "Yellow" si la couleur est jaune.
    }
    else {
        return "Unknown"; // Retourne "Unknown" si la couleur ne correspond à aucune des couleurs prédéfinies.
    }
}





/// Méthode pour décaler les couleurs des pièces ayant une forme spécifique.
void Plateau::decalerParForme(const std::string& forme) {
    // Initialisation de l'indicateur de décalage à false.
    decalageEffectue = false;
    // Vérifiez si le plateau est vide avant de commencer.
    if (!debut) {
        cout << "Le plateau est vide." << endl;
        return;
    }

    // Commencez par la dernière pièce.
    Piece* curr = fin;
    int count = 0; // Compteur pour le nombre de décalages effectués.
    do {
        // Recherchez la première pièce de la forme spécifiée en remontant la liste.
        while ((curr->getForme() != forme) && curr->getPrecedente() != fin) {
            curr = curr->getPrecedente();
        }
        // Si une pièce de la forme spécifiée est trouvée, procédez au décalage.
        if (curr->getForme() == forme) {
            count++;
            // Sauvegardez la couleur de la pièce actuelle.
            sf::Color couleurTmp1 = curr->getCouleur();
            // Trouvez la pièce précédente de la même forme.
            Piece* first = curr->getPrecedente();
            while (first && first->getForme() != forme && first != fin) {
                first = first->getPrecedente();
            }
            // Si une telle pièce est trouvée, échangez les couleurs.
            if (first && first->getForme() == forme) {
                count++;
                sf::Color couleurTmp2 = first->getCouleur();
                first->setCouleur(couleurTmp1);
                // Trouvez la pièce encore précédente de la même forme.
                Piece* second = first->getPrecedente();
                while (second && second->getForme() != forme && second != fin) {
                    second = second->getPrecedente();
                }
                // Si une telle pièce est trouvée, échangez les couleurs.
                if (second && second->getForme() == forme) {
                    count++;
                    sf::Color couleurTmp3 = second->getCouleur();
                    second->setCouleur(couleurTmp2);
                    curr->setCouleur(couleurTmp3);
                    // Indiquez qu'un décalage a été effectué.
                    decalageEffectue = true;
                }
            }
        }
        else {
            // Si aucune pièce de la forme spécifiée n'est trouvée, terminez la fonction.
            return;
        }
    // Continuez tant que moins de trois décalages ont été effectués et que le début n'est pas atteint.
    } while (count < 3 && curr != debut);
}



/// Convertit une chaîne de caractères représentant une couleur en un objet sf::Color.
sf::Color stringToColor(const std::string& couleur) {
    if (couleur == "Green") {
        return sf::Color::Green; // Retourne la couleur verte.
    }
    else if (couleur == "Red") {
        return sf::Color::Red; // Retourne la couleur rouge.
    }
    else if (couleur == "Yellow") {
        return sf::Color::Yellow; // Retourne la couleur jaune.
    }
    else if (couleur == "Blue") {
        return sf::Color::Blue; // Retourne la couleur bleue.
    }
    // Si la chaîne ne correspond à aucune couleur connue, retourne noir par défaut.
    return sf::Color::Black;
}

/// Convertit un objet sf::Color en une chaîne de caractères représentant la couleur.
std::string colorToString(const sf::Color& color) {
    if (color == sf::Color::Green) {
        return "Green"; // Si la couleur est verte, retourne "Green".
    }
    else if (color == sf::Color::Red) {
        return "Red"; // Si la couleur est rouge, retourne "Red".
    }
    else if (color == sf::Color::Yellow) {
        return "Yellow"; // Si la couleur est jaune, retourne "Yellow".
    }
    else if (color == sf::Color::Blue) {
        return "Blue"; // Si la couleur est bleue, retourne "Blue".
    }
    else {
        return "Unknown"; // Si la couleur n'est pas reconnue, retourne "Unknown".
    }
}




/// Méthode pour décaler les formes des pièces ayant une couleur spécifique.
void Plateau::decalerParCouleur(const sf::Color& couleur) {
    // Initialisation de l'indicateur de décalage à false.
    decalageEffectue = false;
    // Vérifiez si le plateau est vide avant de commencer.
    if (!debut) {
        cout << "Le plateau est vide." << endl;
        return;
    }

    // Commencez par la dernière pièce.
    Piece* curr = fin;
    int count = 0; // Compteur pour le nombre de décalages effectués.
    do {
        // Recherchez la première pièce de la couleur spécifiée en remontant la liste.
        while ((curr->getCouleur() != couleur) && curr->getPrecedente() != fin) {
            curr = curr->getPrecedente();
        }
        // Si une pièce de la couleur spécifiée est trouvée, procédez au décalage.
        if (curr->getCouleur() == couleur) {
            count++;
            // Sauvegardez la forme de la pièce actuelle.
            std::string formeTmp1 = curr->getForme();
            // Trouvez la pièce précédente de la même couleur.
            Piece* first = curr->getPrecedente();
            while (first && first->getCouleur() != couleur && first != fin) {
                first = first->getPrecedente();
            }
            // Si une telle pièce est trouvée, échangez les formes.
            if (first && first->getCouleur() == couleur) {
                count++;
                std::string formeTmp2 = first->getForme();
                first->setForme(formeTmp1);
                // Trouvez la pièce encore précédente de la même couleur.
                Piece* second = first->getPrecedente();
                while (second && second->getCouleur() != couleur && second != fin) {
                    second = second->getPrecedente();
                }
                // Si une telle pièce est trouvée, échangez les formes.
                if (second && second->getCouleur() == couleur) {
                    count++;
                    std::string formeTmp3 = second->getForme();
                    second->setForme(formeTmp2);
                    curr->setForme(formeTmp3);
                    // Indiquez qu'un décalage a été effectué.
                    decalageEffectue = true;
                }
            }
        }
        else {
            // Si aucune pièce de la couleur spécifiée n'est trouvée, terminez la fonction.
            return;
        }
    // Continuez tant que moins de trois décalages ont été effectués et que le début n'est pas atteint.
    } while (count < 3 && curr != debut);
}






///Méthode pour mettre à jour le score du jeu et le niveau en fonction des actions effectuées.
void Plateau::score_jeux() {
    // Réinitialiser le niveau du jeu à 0.
    etatJeu.niveau = 0;

    // Charger le fichier sonore pour le score. Si le chargement échoue, afficher une erreur et quitter la méthode.
    if (!buffer.loadFromFile("sonScore.WAV")) {
        std::cerr << "Erreur lors du chargement du fichier son" << std::endl;
        return;
    }

    // Associer le buffer sonore à l'objet sound.
    sound.setBuffer(buffer);

    // Si le score est supérieur à 5, incrémenter le niveau du jeu.
    if (score > 5) {
        etatJeu.niveau++;
    }

    // Si un décalage a été effectué, ajouter 5 au score et réinitialiser l'indicateur de décalage.
    if (decalageEffectue) {
        score += 5;
        decalageEffectue = false;
    } else {
        // Sinon, incrémenter simplement le score.
        score++;
    }

    // Jouer le son du score.
    sound.play();
}

/// Méthode pour compter le nombre de pièces présentes sur le plateau.
int Plateau::nombreDePieces() const {
    int count = 0; // Initialiser le compteur de pièces à 0.
    Piece* current = debut; // Commencer par la première pièce.

    // Parcourir la liste chaînée de pièces et compter chaque pièce.
    while (current != nullptr) {
        count++;
        current = current->getSuivante();
    }

    // Retourner le nombre total de pièces.
    return count;
}



  /// Méthode pour afficher le score actuel dans la fenêtre de jeu.
void Plateau::score_Afficher(sf::RenderWindow& window, const sf::Font& font) const {
    // Création et configuration du texte à afficher.
    sf::Text scoreText("Score: " + std::to_string(score), font);
    scoreText.setCharacterSize(24); // Taille des caractères
    scoreText.setStyle(sf::Text::Bold); // Style du texte
    scoreText.setPosition(10, 10); // Position du texte dans la fenêtre
    scoreText.setFillColor(sf::Color::White); // Couleur du texte
    window.draw(scoreText); // Dessiner le texte dans la fenêtre

    etatJeu.score = score; // Mise à jour du score dans l'état du jeu
}

/// Méthode pour afficher le temps écoulé dans la fenêtre de jeu.
void Plateau::afficherTemps(sf::RenderWindow& window, const sf::Font& font) {
    // Création et configuration du texte à afficher.
    sf::Text timeText("Time: " + std::to_string(timeElapsed.asSeconds()), font);
    timeText.setCharacterSize(24); // Taille des caractères
    timeText.setStyle(sf::Text::Bold); // Style du texte
    timeText.setPosition(10, 40); // Position du texte dans la fenêtre
    timeText.setFillColor(sf::Color::White); // Couleur du texte
    window.draw(timeText); // Dessiner le texte dans la fenêtre

    etatJeu.temps = timeElapsed.asSeconds(); // Mise à jour du temps dans l'état du jeu
}

/// Méthode pour afficher le niveau actuel dans la fenêtre de jeu.
void Plateau::Level_Afficher(sf::RenderWindow& window, const sf::Font& font) {
    // Création et configuration du texte à afficher.
    sf::Text LevelText("Level: " + std::to_string(etatJeu.niveau), font);
    LevelText.setCharacterSize(24); // Taille des caractères
    LevelText.setStyle(sf::Text::Bold); // Style du texte
    LevelText.setPosition(10, 70); // Position du texte dans la fenêtre
    LevelText.setFillColor(sf::Color::White); // Couleur du texte
    window.draw(LevelText); // Dessiner le texte dans la fenêtre
}

/// Méthode pour demander et retourner le nom du joueur.
std::string Plateau::demanderNomJoueur() {
    std::cout << "Entrez votre nom: "; // Demande d'entrée à l'utilisateur
    std::cin >> etatJeu.nomJoueur; // Lecture du nom du joueur
    return etatJeu.nomJoueur; // Retour du nom du joueur
}


///Fonction pour afficher les informations du joueur dans la fenêtre de jeu.
void Plateau::afficherInformations(sf::RenderWindow& window, const sf::Font& font) {
    // Création et configuration du texte à afficher.
    sf::Text joueurText("Joueur: " + etatJeu.nomJoueur, font);
    joueurText.setCharacterSize(24); // Taille des caractères
    joueurText.setStyle(sf::Text::Bold); // Style du texte
    joueurText.setPosition(10, 100); // Position du texte dans la fenêtre
    joueurText.setFillColor(sf::Color::White); // Couleur du texte
    window.draw(joueurText); // Dessiner le texte dans la fenêtre
}

/// Fonction pour sauvegarder l'état du jeu dans un fichier texte.
void sauvegarderEtatJeu(const EtatJeu& etat) {
    // Ouvrir un fichier texte en mode ajout.
    std::ofstream fichier("etatJeu.txt", std::ios::app);
    if (fichier.is_open()) {
        // Écrire les informations du joueur dans le fichier.
        fichier << "Nom du Joueur: " << etat.nomJoueur << std::endl;
        fichier << "Score: " << etat.score << std::endl;
        fichier << "Temps: " << etat.temps << "s" << std::endl;
        fichier << "Niveau: " << etat.niveau << std::endl;
        fichier << "--------------------------" << std::endl;
        fichier.close(); // Fermer le fichier après l'écriture.
    } else {
        // Afficher une erreur si le fichier ne peut pas être ouvert.
        std::cerr << "Impossible d'ouvrir le fichier." << std::endl;
    }
}

/// Fonction pour charger l'état du jeu à partir d'un fichier texte.
EtatJeu chargerEtatJeu(const std::string& nomFichier) {
    // Ouvrir le fichier texte en mode lecture.
    std::ifstream fichier(nomFichier);
    EtatJeu etatJeu; // Créer une instance de EtatJeu pour stocker les informations.
    if (fichier.is_open()) {
        // Lire les informations du fichier et les stocker dans l'instance de EtatJeu.
        std::getline(fichier, etatJeu.nomJoueur);
        fichier >> etatJeu.score;
        fichier >> etatJeu.niveau;
        fichier >> etatJeu.temps;
        fichier.close(); // Fermer le fichier après la lecture.
    }
    return etatJeu; // Retourner l'instance de EtatJeu avec les informations chargées.
}


#endif // PLATEAU_H_INCLUDED

