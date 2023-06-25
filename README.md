# Mur_ecran
Voici la partie affichage du Mur d'écran :
Nous avons mis au point deux serveurs pour ce projet. Le premier serveur, lui aussi écrit en C++, permet de recevoir les données des clients et de les enregistrer dans des fichiers selon leur extension. Il peut traiter les extensions JPEG, JSON et SO, et enregistre les données reçues dans les fichiers correspondants. Par ailleurs, il crée un fichier texte contenant le message "1" pour dire au premier serveur qu'une image doit être envoyée aux écrans.  
Le second serveur, basé sur le langage C++, est destiné à recevoir les requêtes des clients. Le serveur utilise des sockets pour communiquer avec les clients via Ethernet. Cependant, il faudrait rajouter qu’une fois que le serveur a finie d’envoyer les données à tous les contrôleurs, qu’il remplace le 1 pour mettre 0 dans le fichier texte afin qu’il sache qu’il ne faut plus envoyer les données automatiquement
Ces deux serveurs sont des éléments-clés de notre système, nous permettant de recevoir les demandes des clients, de traiter les données et d'afficher des images sur les écrans. Ils peuvent être mieux automatisés, le second serveur pourrait être mieux sécurisé en disposant d'un serveur DHCP pour donner aux clients une adresse IP statique. En revanche, pour notre temps et nos spécifications, les serveurs sont fonctionnels.

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
