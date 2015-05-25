# Drone-Sim
Quadricoptere Simulation + arduino controller

Permet le contrôle d'un quadricoptère en se basant sur une simulation Unity et 2 cartes Arduino MEGA 2560.

# Getting started
1. Clone.
2. Unity > Edit > Project Settings > Player > API Compatibility (Net 2.0 et non 2.0subset)

## Architecture du projet
* Joystick -> Unity3d (interprétation des commandes)
* (Optionnel) Transformation en utilisant le protocole du joystick Pelco
* Unity3d -> Carte Arduino 1 (Parsing du bytecode, application des paramètres)
* Carte Arduino 1 -> Carte Arduino 2 (envoi wifi, Armement / initialisation, puis passage des commandes avec le protocole Proxy)
* Carte Arduino 2 : Filtrage des mesures, calcul algorithme d'asservissement, checksum
* Carte Arduino 2 -> Unity3d (envoi des commandes)
* Unity3d : réception des commandes et application au modèle numérique

## Paramètres

### Asservissement
* Tilt (°)
* Vitesse verticale (mm/s)
* Vitesse lacet (°/s)
* Altitude limite
* Touche urgence (désarmement, stabilisation et éventuellement atterissage)
* Etalonnage (flat trim)

### Confort
* Sensibilité
* Orientation du drone
* Etat de la batterie
* (Optionnel) Mode Headless
