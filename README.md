IMUViewer
=========

Lorsque l'utilisateur choisit un fichier, le logiciel réalise les pré-traitements nécessaires pour l'affichage de la centrale et de la classification du mouvement de l'opérateur.
Une fois ces traitements réalisés, MainWindow crée un timer qui va permettre de lancer à une
fréquence régulière :
- l'évolution de la centrale dans le temps
- la mise à jour de la fenêtre d'évolution de la centrale
- la mise à jour des fenêtres des capteurs
- la mise à jour des fenêtres de visualisation des signaux
- la mise à jour de l'affichage de la classe de mouvement
 la mise à jour de l'écran LCD (affichant le temps), barre de défilement

![snapshot de l'application](https://github.com/mohamedamjad/IMUViewer/blob/master/images/application_snapshot.png)

La partie de gauche permet de visualiser l'évolution de la centrale en 3D ou en mode projeté sur
les trois plans (classe PrincipalCapteurGL). L'utilsiateur peut également activer le mode suivi en
appuyant sur la touche 's' du clavier. La partie supérieure représente les données de
l'accéléromètre et du gyroscope (classe CapteurGL). L'image en haut à droite représente le type
courant du mouvement. Il est possible d'afficher trois signaux différents via les listes déroulantes
(classe gyrograph).
Le fichier se lit avec les boutons classiques d'un lecteur multimédia.

Voir répértoire ![doc](https://github.com/mohamedamjad/IMUViewer/doc) pour télécharger la doc développeur et le rapport du projet

Développeurs:
![Régis](https://github.com/cwamgis) - ![Ferdaousse](https://github.com/ferdaousse) - ![Amjad](https://github.com/mohamedamjad)
