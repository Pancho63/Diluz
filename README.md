# D::Luz
OSC Remote for D::Light lighting console (www.getdlight.com)

D::Luz is available on  the App store for IOS

an APK bundle for Android is available for download here : 
  http://www.getdlight.com/index.php/downloadfr/category/35-remote

Developer mode must be active on your device

///    ///     ///

D::Luz est disponible sur l'App store pour IOS

un executable APK pour Android est disponible ici : 
http://www.getdlight.com/index.php/downloadfr/category/35-remote

Le mode developpeur doit être actif sur votre appareil



# Installation sur Android sans passer par l'Android Market ni l'APK disponible sur le site de D::Light

Le code de Diluz a été crée sur QT Creator. Il vous faudra télécharger ce software afin d'installer D::Luz sur votre appareil.



1. Télécharger QT Creator et l'installer : http://www.qt.io/download-open-source/
2. Dans QT Creator, faire Nouveau projet / Import projet / Git clone
3. Dans repository, entrer l'adresse : https://github.com/Pancho63/Diluz. Vous pouvez choisir dans le path: l'endroit où les fichiers seront téléchargés. 
4. Dans la fenêtre Configure Project : sélectionner "android for armeabi-v7a Qt 5.6" uniquement 
5. Paramètrer votre appareil Android en mode developpeur
6. Le connecter par USB à votre ordinateur
7. Dans Qt creator, cliquer sur la flêche verte = Executer en bas de la colone de gauche
8. Selectionner votre appareil dans la fenêtre qui apparait
9. D::Luz devrait s'ouvrir sur votre appareil




# Installation sur iOS depuis un Mac sans passer par l'App Store

Le code de Diluz a été crée sur QT Creator. Il vous faudra télécharger ce software afin de générer un projet Xcode.

Pour ce faire il vous faudra :

- la dernière version de Qt Creator (www.qt.io/developers/)
- la dernière version de Xcode sur Mac (à télécharger sur l'App Store)
- un Apple ID 
- un cable USB pour connecter votre iDevice et votre Mac
- au minimum iOS 6


# Marche à suivre pas à pas


1. Télécharger QT Creator et l'installer : http://www.qt.io/download-open-source/
2. Télécharger Xcode dans l'AppleStore et l'installer
3. Ouvrir Xcode et dans Préférence / Account, cliquer sur le bouton + pour y ajouter votre Apple ID
4. Dans QT Creator, faire Nouveau projet / Import projet / Git clone
5. Dans repository, entrer l'adresse : https://github.com/Pancho63/Diluz. Vous pouvez choisir dans le path: l'endroit où les fichiers seront téléchargés. 
6. Dans la fenêtre Configure Project : sélectionner "iphoneos-clang Qt 5.6.0 for iOS" uniquement et cliquer sur "Configure project"
7. Cliquer sur l'icone "Marteau" soit "Build Project" tout en bas de la colone de gauche
8. QT Creator aura alors créé un dossier contenant le fichier Xcode DiLuz.xcodeproj. Ce dossier est par defaut généré dans le dossier précédent dans l'arborescence de vos fichiers.
9. Double cliquer sur le fichier DiLuz.xcodeproj (Il s'ouvre dans XCode)
10. Sélectionner le projet Xcode à sideloader dans la barre latérale de gauche
11. Aller dans General / Identity et changer le Bundle Identfier. Vous pouvez simplement ajouter "123" à la fin du nom.
12. Sous Team, sélectionner votre Apple ID
13. Connecter votre iDevice via USB
14. Dans Xcode, allez dans le menu Product et sélectionner votre iDevice dans Destination
15. Déloquer votre iDevice et aller dans Settings / General / Profile et cliquer sur l'account developer et choisir Trust
16. De retour dans Xcode, cliquer sur le bouton Run ou Play (ou raccourcis Command + R) pour compiler l'app D::Luz sur votre iDevice
17. Attendez une minute ou deux que Xcode sideload l'app sur votre iOS
18. Une fois terminé vous pouvez démarrer D::Luz sur votre iDevice

enjoy
(merci à Aroom pour le howto sur IOS)
