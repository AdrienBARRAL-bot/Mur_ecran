// Convertir la direction de rotation en code correspondant
int rotationCode;
if (rotationDirection == "clockwise") {
	rotationCode = -1;
} else if (rotationDirection == "counter-clockwise") {
	rotationCode = 1;
} else {
	rotationCode = 0;
}
 
// Déterminer le centre de rotation en fonction de l'axe spécifié
Point2f rotationCenter;
if (rotationAxis == "center") {
	rotationCenter = Point2f(image.cols / 2.0, image.rows / 2.0);
} else if (rotationAxis == "top") {
	rotationCenter = Point2f(image.cols / 2.0, 0);
} else if (rotationAxis == "bottom") {
	rotationCenter = Point2f(image.cols / 2.0, image.rows);
} else if (rotationAxis == "left") {
	rotationCenter = Point2f(0, image.rows / 2.0);
} else if (rotationAxis == "right") {
	rotationCenter = Point2f(image.cols, image.rows / 2.0);
} else if (rotationAxis == "top left") {
	rotationCenter = Point2f(0, 0);
} else if (rotationAxis == "top right") {
	rotationCenter = Point2f(image.cols, 0);
} else if (rotationAxis == "bottom left") {
	rotationCenter = Point2f(0, image.rows);
} else if (rotationAxis == "bottom right") {
	rotationCenter = Point2f(image.cols, image.rows);
} else {
	rotationCenter = Point2f(0, 0);
}
 
// Déterminer l'angle de rotation en fonction de la vitesse spécifiée
double rotationAngle;
if (rotationSpeed == "fast") {
	rotationAngle = 10.0;
} else if (rotationSpeed == "medium") {
	rotationAngle = 5.0;
} else if (rotationSpeed == "slow") {
	rotationAngle = 2.0;
} else {
	rotationAngle = 0.0;
}
 
// Boucle principale pour l'animation
while (true) {
	// Appliquer la rotation à l'image
	Mat rotationMatrix = getRotationMatrix2D(rotationCenter, rotationAngleTotal, 1.0);
	warpAffine(rotatedImage, rotatedImage, rotationMatrix, image.size());
 
	// Afficher l'image animée dans la fenêtre
	imshow("Animation", rotatedImage);
 
	// Mettre à jour l'angle de rotation
	rotationAngleTotal += rotation
