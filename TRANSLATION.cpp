// Initialiser les variables de translation et de rotation
int translationX = 0;
int translationY = 0;
 
// Boucle principale pour l'animation
while (true) {
	// Appliquer la translation initiale à l'image
	Mat rotatedImage;
	Mat translationMatrix = Mat::eye(2, 3, CV_32F);
    translationMatrix.at<float>(0, 2) = translationX;
    translationMatrix.at<float>(1, 2) = translationY;
	warpAffine(image, rotatedImage, translationMatrix, image.size());
 
	// Afficher l'image animée dans la fenêtre
	imshow("Animation", rotatedImage);
 
	// Mettre à jour les valeurs de translation
	translationX = (translationX + translationStep) % nbPixel;
	translationY = (translationY + translationStep) % nbPixel;
}
