#ifndef SCOREMANAGER_H_INCLUDED
#define SCOREMANAGER_H_INCLUDED

// ScoreManager.h

#include <vector>
#include <string>
#include <fstream>
#include <algorithm>

struct ScoreEntry {
    std::string playerName;
    int score;
};

bool compareScores(const ScoreEntry& a, const ScoreEntry& b) {
    return a.score > b.score; // Tri décroissant
}

void sauvegarderMeilleursScores(const std::vector<ScoreEntry>& scores, const std::string& nomFichier) {
    std::ofstream fichier(nomFichier);
    if (fichier.is_open()) {
        for (const auto& entry : scores) {
            fichier << entry.playerName << " " << entry.score << std::endl;
        }
        fichier.close();
    }
    else {
        std::cerr << "Impossible d'ouvrir le fichier pour sauvegarder les meilleurs scores." << std::endl;
    }
}

void ajouterScore(std::vector<ScoreEntry>& scores, const ScoreEntry& newScore) {
    scores.push_back(newScore);
    std::sort(scores.begin(), scores.end(), compareScores);
    if (scores.size() > 10) {
        scores.resize(10); // Gardez seulement les 10 meilleurs scores
    }
}


#endif // SCOREMANAGER_H_INCLUDED
