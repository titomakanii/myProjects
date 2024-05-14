// MultiMediaTechnology / FHS | MultiMediaProjekt 1  | van Renen Nicolas

using System;
using System.Collections.Generic;
using System.IO;
using SFML.Graphics;
using SFML.System;
using SFML.Window;
using System;
using SFML.Audio;

namespace Shiftee
{
    public class MainGame : GameObject
    {
        private bool gameOverARequested;
        public bool GameOverARequested => gameOverARequested;

        private bool gameOverBRequested;
        public bool GameOverBRequested => gameOverBRequested;

        private bool winRequested;
        public bool WinRequested => winRequested;
        private readonly RenderWindow window;

        public static readonly List<GameObject> gameObjects = new();
        public static readonly Dictionary<Type, GameObject> gameObjectMap = new();
        public int score;
        public int score2;
        private readonly Text scoreText;
        private readonly Text scoreText2;
        private FloorCollision? collider;
        private FloatRect rocket;
        private FloatRect jumpBooost;
        public FloatRect abyss;

        public MainGame(RenderWindow window)
        {
            this.window = window;
            Font font = new("Assets/ARCADECLASSIC.ttf");
            score = 6;
            scoreText = new Text("0", font, 40)
            {
                Position = new Vector2f(610, 400),
                FillColor = Color.Blue,
                DisplayedString = $"{score}"
            };

            score2 = 6;
            scoreText2 = new Text("0", font, 40)
            {
                Position = new Vector2f(610, 430),
                FillColor = Color.Red,
                DisplayedString = $"{score}"
            };

            window.SetVerticalSyncEnabled(true);

            DebugDraw.ActiveWindow = window;
        }

        public override void Initialize()
        {
            AssetManager.LoadSound("GameOverA", @".\Assets\gameovera.wav");
            AssetManager.LoadSound("Win", @".\Assets\win.wav");
            AssetManager.LoadSound("GameOverB", @".\Assets\gameoverb.wav");
            AssetManager.LoadSound("Cage", @".\Assets\cage.wav");

            Oxygen o2Tank = new();
            Floor floor = new();
            Player player = new(floor.floors, o2Tank.o2Tanks);
            Moveables moveable = new(player);
            collider = new FloorCollision(player.playerSprites, player.playerRigidbodies, floor.floors, moveable.moveables);

            Background background = new();
            gameObjects.Add(background);
            gameObjectMap.Add(typeof(Background), background);

            gameObjects.Add(player);
            gameObjectMap.Add(typeof(Player), player);

            Crystal crystal = new();
            gameObjects.Add(crystal);
            gameObjectMap.Add(typeof(Crystal), crystal);

            gameObjects.Add(floor);
            gameObjectMap.Add(typeof(Floor), floor);

            gameObjects.Add(o2Tank);
            gameObjectMap.Add(typeof(Oxygen), o2Tank);

            gameObjects.Add(moveable);
            gameObjectMap.Add(typeof(Moveables), moveable);

            Cage cage = new(ref score, ref score2, player.playerSprites);
            gameObjects.Add(cage);
            gameObjectMap.Add(typeof(Cage), cage);

            rocket = new FloatRect(72, 310, 60, 80);
            jumpBooost = new FloatRect(0, 330, 50, 120);
            abyss = new FloatRect(152, 462, 312, 16);

            foreach (GameObject gameObject in gameObjects)
            {
                gameObject.Initialize();
            }
        }

        public override void Update(float deltaTime)
        {
            Player player = (Player)gameObjectMap[typeof(Player)];
            Crystal crystal = (Crystal)gameObjectMap[typeof(Crystal)];
            Cage? rokcetCage = (Cage)gameObjectMap[typeof(Cage)];

            Collision.CheckCrystalCollisions(player, crystal.crystalsBlue, crystal.crystalsRed, ref score, ref score2);

            collider!.Update();

            scoreText.DisplayedString = score.ToString();
            scoreText2.DisplayedString = score2.ToString();

            foreach (GameObject gameObject in gameObjects)
            {
                gameObject.Update(deltaTime);
            }

            InputManager.Instance.Update(deltaTime);
            if (player.sprite1!.GetGlobalBounds().Intersects(jumpBooost))
            {
                player.impulse = 4250;
            }
            else
            {
                player.impulse = 2200;
            }
            if (abyss.Intersects(player.sprite1.GetGlobalBounds()) || abyss.Intersects(player.sprite2!.GetGlobalBounds()))
            {
                gameOverARequested = true;
            }
            else if (player.currentHealth1 == 0 || player.currentHealth2 == 0)
            {
                gameOverBRequested = true;
            }
            else if (rocket.Intersects(player.sprite1.GetGlobalBounds()) && rocket.Intersects(player.sprite2.GetGlobalBounds()))
            {
                winRequested = true;
            }

            if (gameOverARequested || gameOverBRequested || winRequested)
            {
                AssetManager.Music["SoundTrack"].Stop();

                if (gameOverARequested)
                {
                    AssetManager.Sounds["GameOverA"].Play();
                }
                else if (gameOverBRequested)
                {
                    AssetManager.Sounds["GameOverB"].Play();
                }
                else if (winRequested)
                {
                    AssetManager.Sounds["Win"].Play();
                }
            }

            if (score == 0 && score2 == 0)
            {
                rokcetCage!.cage!.Position = new Vector2f(1000, 1000);
                AssetManager.Sounds["Cage"].Play();
            }
        }

        public override void Draw(RenderWindow window)
        {
            window.Clear();

            foreach (GameObject gameObject in gameObjects)
            {
                gameObject.Draw(window);
            }

            window.Draw(scoreText);
            window.Draw(scoreText2);
        }
    }
}
