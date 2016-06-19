# D::Luz
OSC Remote for D::Light lighting console (www.getdlight.com)



# Installation sur iOS depuis un Mac

Les versions modernes d'iOS et Xcode proposent une technique appelée Sideloading qui vous permet d'installer des apps et software sur vos iPhone, iPad ou iPod touch directement depuis Xcode sur un Mac, sans devoir passer par l'App Store. Nous utiliserons cette méthode pour installer Diluz sur votre iOS device.

Le code de Diluz a été crée sur QT Creator. Il vous faudra télécharger ce software afin de générer un projet Xcode.


Pour ce faire il vous faudra :

- la dernière version de Qt Creator (www.qt.io/developers/)
- la dernière version de Xcode sur Mac (à télécharger sur l'App Store)
- un Apple ID 
- un cable USB pour connecter votre iDevice et votre Mac
- au minimum iOS 9
- cloner ou télécharger le contenu du Git Diluz



La marche à suivre pourrait se résumer à :

1. ouvrir le fichier oscosc.pro avec QT Creator
2. générer un nouveau projet Xcode et son fichier DiLuz.xcodeproj
3. ouvrir le fichier DiLuz.xcodeproj dans Xcode
4. compiler le fichier, soit créer l'app Diluz
5. sideloader l'app Diluz sur votre iDevice

# Marche à suivre pas à pas


1. Télécharger QT Creator et l'installer : http://www.qt.io/download-open-source/
2. Télécharger Xcode dans l'AppleStore et l'installer
3. Ouvrir Xcode et dans Préférence / Account, cliquer sur le bouton + pour y ajouter votre Apple ID
4. Dans QT Creator, faire Nouveau projet / Import projet / Git clone
5.  Dans repository, entrer l'adresse : https://github.com/Pancho63/Diluz. Vous pouvez choisir dans le path: l'endroit où les fichiers seront téléchargés. 
6. Dans la fenêtre Configure Project : sélectionner "iphoneos-clang Qt 5.6.0 for iOS" uniquement et cliquer sur "Configure project"
7. Cliquer sur l'icone "Marteau" soit "Build Project" tout en bas de la colone de gauche
8. QT Creator aura alors créé un dossier contenant le fichier Xcode DiLuz.xcodeproj. Ce dossier est par defaut généré dans le dossier précédent dans l'arborescence de vos fichiers.
9. Double cliquez sur le fichier DiLuz.xcodeproj (Il s'ouvre dans XCode)
10. Sélectionner le projet Xcode à sideloader dans la barre latérale de gauche
11. Allez dans General / Identity et changer le Bundle Identfier. Vous pouvez simplement ajouter "123" à la fin du nom.
12. Sous Team, sélectionner votre Apple ID
13. Dans Deployement/Info/device orientation, décocher les 2 landscapes (D::Luz n'est pas encore très bien visuellement
    en orientation paysage..)
14. Connecter votre iDevice via USB
15. Dans Xcode, allez dans le menu Product et sélectionner votre iDevice dans Destination
16. Déloquer votre iDevice et aller dans Settings / General / Profile et cliquer sur l'account developer et choisir Trust
17. De retour dans Xcode, cliquer sur le bouton Run ou Play (ou raccourcis Command + R) pour compiler l'app D::Luz sur votre iDevice
18. Attendez une minute ou deux que Xcode sideload l'app sur votre iOS
19. Une fois terminé vous pouvez démarer D::Luz sur votre iDevice

enjoy
(merci à Aroom pour ce howto)
