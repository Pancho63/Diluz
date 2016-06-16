# Diluz
OSC Remote control for D::Light lighting console

# Installation sur iOS depuis un Mac

Les versions moderne d'iOS et Xcode propose une technique appelée Sideloading qui vous permet d'installer des apps et software sur vos iPhone, iPad ou iPod touch directemment depuis Xcode sur un Mac, sans devoir passer par l'App Store. Nous utiliserons cette méthode pour installer Diluz sur votre iOS device.

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


1. Télécharger QT Creator et l'installer
2. Télécharger Xcode et l'installer
3. Ouvrir Xcode et dans Préférence / Account, cliquer sur le bouton + pour y ajouter votre Apple ID
4. Ouvrir le fichier oscosc.pro dans QT Creator
5. Dans la fenêtre Configure Project : sélectionner "iphoneos-clang Qt 5.6.0 for iOS "uniquement et cliquer sur "Configure project"
6. Cliquer sur l'icone "Marteau" soit "Build Project" tout en bas de la colone de gauche
7. QT Creator aura alors créé un dossier contenant le fichier Xcode DiLuz.xcodeproj. Ce dossier est par defaut généré dans le dossier précédent dans l'arborescence de vos fichier.
8. Ouvrir le fichier DiLuz.xcodeproj
9. Sélectionner le projet Xcode à sideloader dans la barre latérale de gauche
10. Allez dans General / Identity et changer le Bundle Identfier. Vous pouvez simplement ajouter "123" à la fin du nom.
11. Sous Team, sélectionner votre Apple ID
12. Connecter votre iDevice via USB
13. Dans Xcode, allez dans le menu Product et sélectionner votre iDevice dans Destination
14. Déloquer votre iDevice et aller dans Settings / General / Profile et cliquer sur l'account developer et choisir Trust
15. De retour dans Xcode, cliquer sur le bouton Run ou Play (ou raccourcis Command + R) pour compiler l'app Diluz sur votre iDevice
16. Attendez une minute ou deux que Xcode sideload l'app sur votre iOS
17. Une fois terminé vous pouvez démarer Diluz sur votre iDevice

enjoy
