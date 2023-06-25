#include <Arduino.h>

const int compteur_pin = 2; // Broche du compteur à impulsions
volatile int impulsions = 0; // Variable pour stocker le nombre d'impulsions
const float conversion = 1600.0; // Constante pour convertir les impulsions en kWh (1600 impulsions par kWh)
unsigned long derniere_impulsion = 0; // Variable pour stocker le temps de la dernière impulsion
float consommation = 0.0; // Variable pour stocker la consommation

void compter_impulsion() {
  impulsions++;
}

void setup() {
  pinMode(compteur_pin, INPUT_PULLUP); // Configure la broche du compteur à impulsions en entrée avec résistance de pull-up
  attachInterrupt(digitalPinToInterrupt(compteur_pin), compter_impulsion, RISING); // Attache une interruption à la broche pour compter les impulsions

  Serial.begin(9600); // Ouvre la communication série avec la Raspberry Pi
  while (!Serial); // Attends que la connexion série soit établie
}

void loop() {
  unsigned long temps_actuel = millis(); // Stocke le temps actuel en millisecondes

  if (temps_actuel - derniere_impulsion >= 3600000) { // Vérifie si une heure s'est écoulée depuis la dernière impulsion
    detachInterrupt(digitalPinToInterrupt(compteur_pin)); // Détache l'interruption pour éviter de compter les impulsions pendant le calcul
    float imp_par_heure = (float)impulsions; // Nombre d'impulsions par heure
    consommation = imp_par_heure / conversion; // Calcule la consommation en kWh/heure et la stocke dans la variable "consommation"
    Serial.print("Consommation : ");
    Serial.print(consommation);
    Serial.println(" kWh/heure");
    impulsions = 0; // Réinitialise le compteur d'impulsions
    derniere_impulsion = temps_actuel; // Stocke le temps de la dernière impulsion pour le calcul suivant

    // Envoie les données de consommation à la Raspberry Pi
    String message = String(consommation);
    Serial.println(message);

    attachInterrupt(digitalPinToInterrupt(compteur_pin), compter_impulsion, RISING); // Réattache l'interruption pour compter les impulsions à nouveau
  }
}
