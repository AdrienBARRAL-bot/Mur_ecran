#include <iostream>
#include <string>
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <fstream>
#include <vector>
#include <unordered_map>
#include <sys/stat.h>
#include <thread>
#include <nlohmann/json.hpp>
#include <opencv2/opencv.hpp>


using json = nlohmann::json;


struct FileInfo {
    std::string cheminImage;
    std::string cheminJSON;
    time_t derniereModification;
};


// Fonction pour envoyer un fichier au client
void sendFile(const std::string& filePath, int socketClient) {
    std::ifstream file(filePath, std::ios::binary);
    if (!file) {
        std::cerr << "Erreur lors de l'ouverture du fichier : " << filePath << std::endl;
        return;
    }


    // Obtention de la taille du fichier
    file.seekg(0, std::ios::end);
    int fileSize = file.tellg();
    file.seekg(0, std::ios::beg);


    // Lecture du contenu du fichier
    std::vector<char> buffer(fileSize);
    file.read(buffer.data(), fileSize);


    // Envoi de la taille du fichier
    if (send(socketClient, &fileSize, sizeof(fileSize), 0) < 0) {
        std::cerr << "Erreur lors de l'envoi de la taille du fichier." << std::endl;
        return;
    }


    // Envoi du contenu du fichier
    if (send(socketClient, buffer.data(), fileSize, 0) < 0) {
        std::cerr << "Erreur lors de l'envoi du fichier." << std::endl;
        return;
    }


    std::cout << "Fichier envoyé : " << filePath << std::endl;
}


// Fonction pour envoyer les données JSON au client
void sendJSONData(const std::string& jsonData, int socketClient) {
    // Envoi de la taille des données JSON
    int dataSize = jsonData.size();
    if (send(socketClient, &dataSize, sizeof(dataSize), 0) < 0) {
        std::cerr << "Erreur lors de l'envoi de la taille des données JSON." << std::endl;
        return;
    }


    // Envoi des données JSON
    if (send(socketClient, jsonData.c_str(), dataSize, 0) < 0) {
        std::cerr << "Erreur lors de l'envoi des données JSON." << std::endl;
        return;
    }


    std::cout << "Données JSON envoyées." << std::endl;
}


void handleClient(int socketClient) {
    // Réception du message du client
    const int BUFFER_SIZE = 1024;
    char buffer[BUFFER_SIZE];
    int messageSize = recv(socketClient, buffer, BUFFER_SIZE - 1, 0);
    if (messageSize < 0) {
        std::cerr << "Erreur lors de la réception du message du client." << std::endl;
        close(socketClient);
        return;
    }


    buffer[messageSize] = '\0';
    std::string requestedFile(buffer);


    // Vérification du fichier demandé
    std::unordered_map<std::string, FileInfo> fileMap;
    fileMap["image1.jpg"] = { "image1.jpg", "image1.json", 0 }; // Exemple de fichier
    fileMap["image2.jpg"] = { "image2.jpg", "image2.json", 0 }; // Exemple de fichier


    if (fileMap.find(requestedFile) != fileMap.end()) {
        FileInfo& fileInfo = fileMap[requestedFile];


        // Vérification de la dernière modification du fichier
        struct stat fileAttributes;
        if (stat(fileInfo.cheminImage.c_str(), &fileAttributes) == 0) {
            if (fileAttributes.st_mtime > fileInfo.derniereModification) {
                // Le fichier a été modifié depuis la dernière vérification
                fileInfo.derniereModification = fileAttributes.st_mtime;
                sendFile(fileInfo.cheminImage, socketClient);


                // Lecture du contenu JSON à envoyer
                std::ifstream jsonFile(fileInfo.cheminJSON);
                if (!jsonFile) {
                    std::cerr << "Erreur lors de l'ouverture du fichier JSON : " << fileInfo.cheminJSON << std::endl;
                    return;
                }


                std::string jsonData((std::istreambuf_iterator<char>(jsonFile)), std::istreambuf_iterator<char>());
                jsonFile.close();


                // Envoi des données JSON
                sendJSONData(jsonData, socketClient);
            }
            else {
                std::cout << "Le fichier demandé est à jour : " << fileInfo.cheminImage << std::endl;
            }
        }
        else {
            std::cerr << "Erreur lors de la vérification des attributs du fichier." << std::endl;
        }
    }
    else {
        std::cerr << "Le fichier demandé n'existe pas." << std::endl;
    }


    close(socketClient);
}


int main() {
    int socketServeur = socket(AF_INET, SOCK_STREAM, 0);
    if (socketServeur == -1) {
        std::cerr << "Erreur lors de la création du socket." << std::endl;
        return 1;
    }


    sockaddr_in adresseServeur{};
    adresseServeur.sin_family = AF_INET;
    adresseServeur.sin_addr.s_addr = INADDR_ANY;
    adresseServeur.sin_port = htons(8080);


    if (bind(socketServeur, (struct sockaddr*)&adresseServeur, sizeof(adresseServeur)) < 0) {
        std::cerr << "Erreur lors du bind." << std::endl;
        return 1;
    }


    if (listen(socketServeur, 5) < 0) {
        std::cerr << "Erreur lors de l'écoute du socket." << std::endl;
        return 1;
    }


    std::cout << "Le serveur est prêt à recevoir des connexions." << std::endl;


    while (true) {
        sockaddr_in adresseClient{};
        socklen_t tailleAdresseClient = sizeof(adresseClient);


        int socketClient = accept(socketServeur, (struct sockaddr*)&adresseClient, &tailleAdresseClient);
        if (socketClient < 0) {
            std::cerr << "Erreur lors de l'acceptation de la connexion." << std::endl;
            return 1;
        }


        std::cout << "Nouvelle connexion acceptée." << std::endl;


        std::thread clientThread(handleClient, socketClient);
        clientThread.detach();
    }


    close(socketServeur);


    return 0;
}
