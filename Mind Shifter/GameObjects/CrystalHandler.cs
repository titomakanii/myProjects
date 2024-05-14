// MultiMediaTechnology / FHS | MultiMediaProjekt 1  | van Renen Nicolas

using SFML.Graphics;
using SFML.System;
using SFML.Window;
using SFML.Audio;

namespace Shiftee;

public class Crystal : GameObject
{
    public List<Sprite> crystalsBlue = new();
    public List<Sprite> crystalsRed = new();

    private readonly float pulsatingSpeed = 3f; // Adjust the pulsating speed
    private float elapsedTime = 0f;
    private readonly float minScale = 0.22f; // Minimum scale of the crystals
    private readonly float maxScale = 0.23f; // Maximum scale of the crystals

    public IntRect CollisionRect { get; private set; }

    public override void Initialize()
    {
        AssetManager.LoadTexture("Crystal", "./Assets/crystal1.png");
        AssetManager.LoadTexture("crystalRed", "./Assets/crystal2.png");

        for (int i = 0; i < 6; i++)
        {
            Sprite crystalBlue = new(AssetManager.Textures["Crystal"])
            {
                Scale = new Vector2f(0.22f, 0.22f)
            };
            crystalBlue.TextureRect = new IntRect(0, 0, crystalBlue.TextureRect.Width, crystalBlue.TextureRect.Height);

            switch (i)
            {
                case 0:
                    crystalBlue.Position = new Vector2f(25, 300);
                    break;
                case 1:
                    crystalBlue.Position = new Vector2f(360, 420);
                    break;
                case 2:
                    crystalBlue.Position = new Vector2f(258, 262);
                    break;
                case 3:
                    crystalBlue.Position = new Vector2f(30, 40);
                    break;
                case 4:
                    crystalBlue.Position = new Vector2f(246, 402);
                    break;
                case 5:
                    crystalBlue.Position = new Vector2f(95, 72);
                    break;
                default:
                    // Handle additional cases if needed
                    break;
            }

            crystalsBlue.Add(crystalBlue);
        }
        for (int i = 0; i < 6; i++)
        {
            Sprite crystalRed = new(AssetManager.Textures["crystalRed"])
            {
                Scale = new Vector2f(0.22f, 0.22f)
            };
            crystalRed.TextureRect = new IntRect(0, 0, crystalRed.TextureRect.Width, crystalRed.TextureRect.Height);

            switch (i)
            {
                case 0:
                    crystalRed.Position = new Vector2f(480, 414);
                    break;
                case 1:
                    crystalRed.Position = new Vector2f(610, 265);
                    break;
                case 2:
                    crystalRed.Position = new Vector2f(300, 330);
                    break;
                case 3:
                    crystalRed.Position = new Vector2f(394, 420);
                    break;
                case 4:
                    crystalRed.Position = new Vector2f(460, 130);
                    break;
                case 5:
                    crystalRed.Position = new Vector2f(535, 118);
                    break;
                default:
                    // Handle additional cases if needed
                    break;
            }

            crystalsRed.Add(crystalRed);
        }
    }
    public override void Update(float deltaTime)
{
    elapsedTime += deltaTime;

    // Calculate the scale factor based on the pulsating effect
    float scale = minScale + ((maxScale - minScale) * (float)Math.Sin(pulsatingSpeed * elapsedTime));

    // Apply the scale factor to each crystalBlue sprite
    foreach (Sprite crystalBlue in crystalsBlue)
    {
        // Set the origin of the sprite to its center
        Vector2f center = new(crystalBlue.GetLocalBounds().Width / 2, crystalBlue.GetLocalBounds().Height / 2);
        crystalBlue.Origin = center;

        // Set the scale of the sprite
        crystalBlue.Scale = new Vector2f(scale, scale);
    }

    // Apply the scale factor to each crystalRed sprite
    foreach (Sprite crystalRed in crystalsRed)
    {
        // Set the origin of the sprite to its center
        Vector2f center = new(crystalRed.GetLocalBounds().Width / 2, crystalRed.GetLocalBounds().Height / 2);
        crystalRed.Origin = center;

        // Set the scale of the sprite
        crystalRed.Scale = new Vector2f(scale, scale);
    }
}

    public override void Draw(RenderWindow window)
    {
        foreach (Sprite crystalBlue in crystalsBlue)
        {
            window.Draw(crystalBlue);
        }
        foreach (Sprite crystalRed in crystalsRed)
        {
            window.Draw(crystalRed);
        }
    }
}