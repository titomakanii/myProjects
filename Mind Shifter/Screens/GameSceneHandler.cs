// MultiMediaTechnology / FHS | MultiMediaProjekt 1  | van Renen Nicolas

using SFML.Graphics;
using SFML.System;
using SFML.Window;
using SFML.Audio;
using System.Collections.Generic;

namespace Shiftee
{
    public class SceneHandler
    {
        public enum Scene
        {
            Start,
            Menu,
            MainGame,
            GameOverA,
            GameOverB,
            Win
        }

        private readonly Dictionary<Scene, GameObject> scenes;
        private readonly RenderWindow window;
        private Scene currentScene;

        public const int WIDTH = 640;
        public const int HEIGHT = 480;
        private const string TITLE = "Mind Shifter";

        public SceneHandler()
        {
            // Window info
            VideoMode videoMode = new(WIDTH, HEIGHT);
            window = new RenderWindow(videoMode, TITLE);

            // Close & resize
            window.KeyPressed += OnWindowClose;
            window.Closed += (sender, args) => window.Close();

            // Scenes
            scenes = new Dictionary<Scene, GameObject>
            {
                { Scene.Start, new Start(window) },
                { Scene.Menu, new Menu(window) },
                { Scene.MainGame, new MainGame(window) },
                { Scene.GameOverA, new GameOverA(window) },
                { Scene.GameOverB, new GameOverB(window) },
                { Scene.Win, new Win(window) }
            };

            currentScene = Scene.Start;

            DebugDraw.ActiveWindow = window;
            window.SetFramerateLimit(480);
        }

        private void OnWindowClose(object? sender, KeyEventArgs e)
        {
            if (e.Code == Keyboard.Key.Escape)
            {
                window?.Close();
            }
        }

        public void Run()
        {
            Initialize();
            Clock clock = new();

            while (window.IsOpen)
            {
                float deltaTime = clock.Restart().AsSeconds();
                HandleEvents();
                Update(deltaTime);
                Draw();
            }
        }

        private void Initialize()
        {
            InputManager.Instance.Initialize(window);

            foreach (GameObject scene in scenes.Values)
            {
                scene.Initialize();
            }

            AssetManager.LoadMusic("SoundTrack", @".\Assets\soundtrack.wav");
            AssetManager.Music["SoundTrack"].Play();
            AssetManager.Music["SoundTrack"].Volume = 10;
        }

        private void Update(float deltaTime)
        {
            scenes[currentScene].Update(deltaTime);

            if (scenes[currentScene] is Start startScene && startScene.MenuRequested)
            {
                currentScene = Scene.Menu;
            }
            else if (scenes[currentScene] is Menu menuScene && menuScene.MainGameRequested)
            {
                currentScene = Scene.MainGame;
            }
            else if (scenes[currentScene] is MainGame mainGameScene)
            {
                if (mainGameScene.GameOverARequested)
                {
                    currentScene = Scene.GameOverA;
                }
                else if (mainGameScene.GameOverBRequested)
                {
                    currentScene = Scene.GameOverB;
                }
                else if (mainGameScene.WinRequested)
                {
                    currentScene = Scene.Win;
                }
            }
        }

        private void Draw()
        {
            window.Clear();
            scenes[currentScene].Draw(window);
            window.Display();
        }

        private void HandleEvents()
        {
            window.DispatchEvents();
        }
    }
}
