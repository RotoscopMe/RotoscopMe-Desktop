# RotoscopMe-Desktop

RotoscopMe-Desktop est une application de rotoscopie pour desktop.

## Compatibilités

Cette application a été développée sous Qt 5.3.2. Elle est donc assuré de fonctionner avec cette version. Il y a des chances qu'elle fonctionne sur des versions proches (5.x).

Pour interagir avec le système, l'application utilise des commandes système de Unix (cp, rm) ainsi que la commande avconv. Il faut donc avoir ces commandes installées sur le système.

## Build

Cette application a un sous-module github lié, il y a donc plus de commandes nécessaires que d'habitude pour récupérer la totalité du dépo :

`git clone https://github.com/RotoscopeMe/RotoscopeMe-Desktop.git`

`git submodule init`

`git submodule update --checkout`

Puis ouvrir, compiler et lancer l'application comme n'importe quel projet Qt.

## Update

En cas d'update de la partie core, il faut travailler sur le dépo RotoscopMe-core (dans la même organisation). Il faut ensuite pusher les changements, puis faire un git pull depuis le dossier core du dépo de travail de la version desktop.
