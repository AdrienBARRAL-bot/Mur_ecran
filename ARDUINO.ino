import serial
import datetime

chemin_fichier = '/chemin/vers/fichier.txt'  # Spécifiez le chemin vers le fichier de destination

ser = serial.Serial('/dev/ttyACM0', 9600)

with open(chemin_fichier, 'w') as fichier:
    while True:
        donnees = ser.readline().decode().strip()  # Lecture des données de consommation depuis l'Arduino
        horodatage = datetime.datetime.now().strftime('%Y-%m-%d %H:%M:%S')
        message = f'{horodatage}: {donnees}'
        print(message)
        fichier.write(message + '\n')  # Écriture des données dans le fichier
        fichier.flush()  # Vidage du tampon pour s'assurer que les données sont écrites immédiatement
