// MultiMediaTechnology / FHS | MultiMediaProjekt 1  | van Renen Nicolas

using SFML.Graphics;
using SFML.System;
using SFML.Window;

namespace Shiftee;

public class Background : GameObject
{
    public Sprite background = null!;

    public override void Initialize()
    {
        AssetManager.LoadTexture("Background", "./Assets/background2.png");
        background = new Sprite(AssetManager.Textures["Background"]);

        Vector2f windowSize = new(SceneHandler.WIDTH, SceneHandler.HEIGHT);
        Vector2f backgroundSize = new(background.Texture.Size.X, background.Texture.Size.Y);
        Vector2f scale = new(windowSize.X / backgroundSize.X, windowSize.Y / backgroundSize.Y);
        background.Scale = scale;
    }

    public override void Draw(RenderWindow window)
    {
        window.Draw(background);
    }

    public override void Update(float deltaTime)
    {
    }
}