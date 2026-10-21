# 🔥 Robot Intelligent de Détection d'Incendie

**Projet embarqué basé sur ESP32 — Simulation avec Wokwi**

## 📌 Présentation du projet

Ce projet consiste à concevoir et simuler un robot mobile intelligent capable de détecter un départ de feu, de surveiller son environnement et de réagir en fonction des informations fournies par ses capteurs.

Le système utilise un ESP32 comme unité de commande. Il combine des capteurs de détection de flamme, un capteur de distance ultrasonique, un capteur de température et d'humidité, ainsi qu'un servomoteur et une interface LCD.

## 🎯 Objectifs

- Détecter la présence d'un feu à l'aide de capteurs.
- Surveiller la température et l'humidité ambiantes.
- Détecter les obstacles et déclencher une manœuvre d'évitement.
- Commander les mouvements du robot.
- Simuler l'orientation d'un dispositif de lutte contre l'incendie.
- Afficher les informations importantes sur un écran LCD.

## 🧰 Matériel et composants

| Composant | Fonction |
|---|---|
| ESP32 DevKit | Unité de commande principale |
| Capteurs de flamme | Détection du feu |
| HC-SR04 | Mesure de distance et détection d'obstacles |
| DHT22 | Mesure de température et d'humidité |
| Servomoteur | Orientation du dispositif de visée |
| Écran LCD 16×2 I2C | Affichage des informations |
| Pilote de moteurs | Commande des moteurs du robot |
| Relais et pompe | Commande du dispositif d'extinction |

*Remarque : certains composants sont représentés de manière simplifiée dans la simulation Wokwi. Le montage réel doit être vérifié avant toute utilisation.*

## ⚙️ Fonctionnement

1. **Patrouille :** le robot avance lorsque les conditions le permettent.
2. **Évitement d'obstacles :** si un obstacle est détecté à proximité, le robot recule puis tourne.
3. **Recherche du feu :** les capteurs latéraux permettent d'orienter le robot vers la zone détectée.
4. **Détection frontale :** si un feu est détecté devant le robot et que la distance est inférieure à 50 cm, le robot s'arrête.
5. **Orientation :** le servomoteur effectue un balayage pour orienter le dispositif de visée.
6. **Surveillance climatique :** le DHT22 mesure la température et l'humidité, affichées sur l'écran LCD.

## 💻 Technologies utilisées

- C++ / Arduino
- ESP32
- Wokwi
- Git et GitHub

## 📁 Structure du projet

```text
robot-detection-incendie/
├── sketch.ino
├── diagram.json
├── libraries.txt
└── README.md
```

## 🚀 Lancer la simulation

1. Ouvrir le projet dans Wokwi.
2. Vérifier les connexions et les bibliothèques requises.
3. Démarrer la simulation.
4. Modifier les interrupteurs simulant les capteurs de flamme pour tester les différents scénarios.
5. Observer les messages sur l'écran LCD et le comportement du servomoteur.

## 🔧 Améliorations possibles

- Ajouter une navigation autonome plus avancée.
- Améliorer la détection et la localisation du feu.
- Intégrer une télémétrie Wi-Fi.
- Ajouter un système de journalisation des mesures.
- Réaliser des tests sur un prototype physique.

## ⚠️ Sécurité

Ce projet est un prototype pédagogique. Une simulation ou un prototype expérimental ne remplace pas un système certifié de détection ou d'extinction d'incendie. Toute pompe, batterie, motorisation ou installation réelle doit être testée et protégée de manière appropriée.

## 👨‍💻 Auteur

**Hedi Haddaoui**

Projet de robotique embarquée et de simulation électronique.
