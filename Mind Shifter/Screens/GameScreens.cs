// MultiMediaTechnology / FHS | MultiMediaProjekt 1  | van Renen Nicolas

using SFML.Graphics;
using SFML.System;
using SFML.Window;
using SFML.Audio;

namespace Shiftee
{
    public class GameScreen : GameObject
    {
        protected RenderWindow window;
        protected Sprite? background;

        public GameScreen(RenderWindow window)
        {
            this.window = window;
        }

        public override void Initialize()
        {
            // Implement initialization logic in the derived classes
        }

        public override void Update(float deltaTime)
        {
            // Implement update logic in the derived classes
        }

        public override void Draw(RenderWindow window)
        {
            window.Clear();
            if (background != null)
            {
                window.Draw(background);
            }
        }
    }

    public class GameOverA : GameScreen
    {
        public GameOverA(RenderWindow window) : base(window)
        {
        }

        public override void Initialize()
        {
            AssetManager.LoadTexture("GameOverA", "./Assets/Over_Abyss.png");
            background = new Sprite(AssetManager.Textures["GameOverA"]);

            Vector2f windowSize = new(SceneHandler.WIDTH, SceneHandler.HEIGHT);
            Vector2f backgroundSize = new(background.Texture.Size.X, background.Texture.Size.Y);
            Vector2f scale = new(windowSize.X / backgroundSize.X, windowSize.Y / backgroundSize.Y);
            background.Scale = scale;
        }

        public override void Update(float deltaTime)
        {
            // Implement update logic specific to GameOverA
        }
    }

    public class GameOverB : GameScreen
    {
        public GameOverB(RenderWindow window) : base(window)
        {
        }

        public override void Initialize()
        {
            AssetManager.LoadTexture("GameOverB", "./Assets/Over_O2.png");
            background = new Sprite(AssetManager.Textures["GameOverB"]);

            Vector2f windowSize = new(SceneHandler.WIDTH, SceneHandler.HEIGHT);
            Vector2f backgroundSize = new(background.Texture.Size.X, background.Texture.Size.Y);
            Vector2f scale = new(windowSize.X / backgroundSize.X, windowSize.Y / backgroundSize.Y);
            background.Scale = scale;
        }

        public override void Update(float deltaTime)
        {
            // Implement update logic specific to GameOverB
        }
    }

    public class Menu : GameScreen
    {
        private bool mainGameRequested;

        public bool MainGameRequested => mainGameRequested;

        public Menu(RenderWindow window) : base(window)
        {
        }

        public override void Initialize()
        {
            AssetManager.LoadTexture("Menu", "./Assets/menu.png");
            background = new Sprite(AssetManager.Textures["Menu"]);

            Vector2f windowSize = new(SceneHandler.WIDTH, SceneHandler.HEIGHT);
            Vector2f backgroundSize = new(background.Texture.Size.X, background.Texture.Size.Y);
            Vector2f scale = new(windowSize.X / backgroundSize.X, windowSize.Y / backgroundSize.Y);
            background.Scale = scale;
        }

        public override void Update(float deltaTime)
        {
            if (InputManager.Instance.GetKeyPressed(Keyboard.Key.Space))
            {
                mainGameRequested = true;
            }
        }
    }

    public class Start : GameScreen
    {
        private bool menuRequested = false;

        public bool MenuRequested => menuRequested;

        public Start(RenderWindow window) : base(window)
        {
        }

        public override void Initialize()
        {
            AssetManager.LoadTexture("Start", "./Assets/start.png");
            background = new Sprite(AssetManager.Textures["Start"]);

            Vector2f windowSize = new(SceneHandler.WIDTH, SceneHandler.HEIGHT);
            Vector2f backgroundSize = new(background.Texture.Size.X, background.Texture.Size.Y);
            Vector2f scale = new(windowSize.X / backgroundSize.X, windowSize.Y / backgroundSize.Y);
            background.Scale = scale;
        }

        public override void Update(float deltaTime)
        {
            if (InputManager.Instance.GetMousePressed(Mouse.Button.Left))
            {
                menuRequested = true;
            }
        }
    }

    public class Win : GameScreen
    {
        public Win(RenderWindow window) : base(window)
        {
        }

        public override void Initialize()
        {
            AssetManager.LoadTexture("Win", "./Assets/EndingWin.png");
            background = new Sprite(AssetManager.Textures["Win"]);

            Vector2f windowSize = new(SceneHandler.WIDTH, SceneHandler.HEIGHT);
            Vector2f backgroundSize = new(background.Texture.Size.X, background.Texture.Size.Y);
            Vector2f scale = new(windowSize.X / backgroundSize.X, windowSize.Y / backgroundSize.Y);
            background.Scale = scale;
        }

        public override void Update(float deltaTime)
        {
            // Implement update logic specific to Win screen
        }
    }
}
