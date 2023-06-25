# Mur_ecran
Voici la partie affichage du Mur d'écran

INSTALLATION OPENCV : 
Commande à effectuer sur la raspberry : 
1) Vérifier la version de la raspberry : 
sudo apt update 
sudo apt upgrade 

2) Installation OPENCV : 
Voici l’ordre des commandes à entrer : 
1. sudo apt install libopencv-dev // Installer les dépendances. 
2. mkdir opencv_build // Créer un répertoire de compilation. 3. cd opencv_build 
4. git clone https://github.com/opencv/opencv.git // Télécharger le code source d’OpenCV à l’aide de GIT. 
5. cd opencv // Accédez au répertoire opencv. 
6. mkdir build // Créez un répertoire de compilation. 7. cd build // Accédez au répertoire build. 
8. cmake -D CMAKE_BUILD_TYPE=RELEASE -D 
CMAKE_INSTALL_PREFIX=/usr/local .. // Configurer la compilation 
9. sudo make install // Installer et compiler opencv. 
10. #include <opencv2/opencv.hpp> // Mettre en tête d’un fichier source c++ pour que opencv fonctionne. 
11. g++ votre_code.cpp -o votre_code `pkg-config --cflags --libs opencv4` // Remplacer votre_code par le nom du fichier à compiler. 
