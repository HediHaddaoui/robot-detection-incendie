# 🔥 Robot Intelligent de Détection d'Incendie

**Projet embarqué basé sur ESP32 — Firmware PlatformIO + simulation Wokwi**

## 📌 Présentation du projet

Ce projet consiste à concevoir et simuler un robot mobile intelligent capable de détecter un départ de feu, de surveiller son environnement et de réagir en fonction des informations fournies par ses capteurs.

Le système utilise un ESP32 comme unité de commande. Il combine des capteurs de détection de flamme, un capteur de distance ultrasonique, un capteur de température et d'humidité, ainsi qu'un servomoteur et une interface LCD.

Le dépôt contient deux volets complémentaires :

- **`robot/`** — le firmware du robot réel, développé avec **PlatformIO** pour une carte ESP32-S3 DevKit (cible `4d_systems_esp32s3_gen4_r8n16`), prêt à être compilé et flashé sur le prototype.
- **la racine du dépôt** — la **simulation Wokwi** (fichiers `sketch.ino`, `diagram.json`, `libraries.txt`) permettant de reproduire le comportement du robot sans matériel.

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
- PlatformIO
- Wokwi
- Git et GitHub

## 📁 Structure du projet

```text
robot-detection-incendie/
├── robot/                     # Firmware PlatformIO (robot réel)
│   ├── src/main.cpp           # Code source principal
│   ├── platformio.ini         # Configuration PlatformIO (carte, libs)
│   ├── include/               # En-têtes additionnels
│   ├── lib/                   # Bibliothèques locales
│   ├── test/                  # Tests unitaires PlatformIO
│   └── .vscode/               # Recommandations d'extensions
├── docs/
│   └── robot_pompier.pptx     # Présentation de soutenance du projet
├── photo-de-robot.jpeg        # Photo du prototype assemblé
├── sketch.ino                 # Sketch Wokwi (simulation)
├── diagram.json               # Schéma de câblage de la simulation
├── libraries.txt              # Bibliothèques Wokwi
├── wokwi-project.txt          # Lien vers le projet Wokwi en ligne
└── README.md
```

## 🔌 Brochage (câblage réel)

| Fonction | Broche ESP32 |
|---|---|
| Relais pompe (TX2) | GPIO 17 |
| Capteurs IR — FC / FL / FR / BL / BR | GPIO 32 / 33 / 34 / 35 / 23 |
| HC-SR04 — TRIG / ECHO | GPIO 5 / 18 |
| Servomoteur SG90 | GPIO 19 |
| DHT22 | GPIO 15 |
| Pont en H L298N — IN1/IN2/IN3/IN4 | GPIO 25 / 26 / 27 / 14 |
| Pont en H L298N — ENA / ENB (PWM) | GPIO 12 / 13 |
| LCD I2C 16×2 (adresse 0x27) | GPIO 21 (SDA) / 22 (SCL) |

## 🛠️ Compiler et flasher le firmware (PlatformIO)

1. Installer [PlatformIO Core](https://platformio.org/install) ou l'extension **PlatformIO IDE** pour VS Code.
2. Se placer dans le dossier `robot/`.
3. Compiler le firmware :

   ```bash
   pio run
   ```

4. Brancher l'ESP32-S3 puis flasher la carte :

   ```bash
   pio run --target upload
   ```

5. Ouvrir le moniteur série (115200 bauds) pour visualiser les logs :

   ```bash
   pio device monitor
   ```

Les dépendances déclarées dans `platformio.ini` sont automatiquement téléchargées par PlatformIO (`ESP32Servo`, `LiquidCrystal_I2C`, `DHT sensor library`).

## 🚀 Lancer la simulation

1. Ouvrir le projet dans Wokwi.
2. Vérifier les connexions et les bibliothèques requises.
3. Démarrer la simulation.
4. Modifier les interrupteurs simulant les capteurs de flamme pour tester les différents scénarios.
5. Observer les messages sur l'écran LCD et le comportement du servomoteur.

## 📊 Présentation

La présentation de soutenance du projet est disponible dans [`docs/robot_pompier.pptx`](docs/robot_pompier.pptx). Elle couvre le contexte, le cahier des charges, l'architecture matérielle et logicielle, l'implémentation, les tests de validation et les perspectives d'évolution.

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
