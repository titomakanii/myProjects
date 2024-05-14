// MultiMediaTechnology / FHS | MultiMediaProjekt 1  | van Renen Nicolas

using SFML.Graphics;
using SFML.System;
using SFML.Window;
using SFML.Audio;
using System.Collections.Generic;

namespace Shiftee
{
    public class Moveables : GameObject
    {
        public List<Sprite> moveables = new();
        public Sprite? purplePlatform;
        private Sprite? purpleButton;

        private Sprite? greenPlatform;
        private Sprite? greenButton;

        private readonly Player player;
        private readonly float platformSpeed = 100f; // Adjust the speed as needed
        private bool isButtonPressed = false;
        private bool isButtonPressed2 = false;

        private FloatRect buttonCollider;
        private FloatRect buttonCollider2;

        public Moveables(Player player)
        {
            this.player = player;
        }

        public override void Initialize()
        {
            // Setup Moveables
            AssetManager.LoadTexture("PurpleP", "./Assets/purplePlatform.png");
            purplePlatform = new Sprite(AssetManager.Textures["PurpleP"])
            {
                Scale = new Vector2f(0.25f, 0.28f),
                Position = new Vector2f(50, 0)
            };
            purplePlatform.TextureRect = new IntRect(0, 0, purplePlatform.TextureRect.Width, purplePlatform.TextureRect.Height);

            AssetManager.LoadTexture("PurpleB", "./Assets/purpleButton.png");
            purpleButton = new Sprite(AssetManager.Textures["PurpleB"])
            {
                Scale = new Vector2f(1.3f, 1.3f),
                Position = new Vector2f(512, 190)
            };
            purpleButton.TextureRect = new IntRect(0, 0, purpleButton.TextureRect.Width, purpleButton.TextureRect.Height);

            AssetManager.LoadTexture("GreenP", "./Assets/greenPlatform.png");
            greenPlatform = new Sprite(AssetManager.Textures["GreenP"])
            {
                Scale = new Vector2f(2.5f, 2.4f),
                Position = new Vector2f(562, 220)
            };
            greenPlatform.TextureRect = new IntRect(0, 0, greenPlatform.TextureRect.Width, greenPlatform.TextureRect.Height);

            AssetManager.LoadTexture("GreenB", "./Assets/greenButton.png");
            greenButton = new Sprite(AssetManager.Textures["GreenB"])
            {
                Scale = new Vector2f(1.3f, 1.3f),
                Position = new Vector2f(320, 65)
            };
            greenButton.TextureRect = new IntRect(0, 0, greenButton.TextureRect.Width, greenButton.TextureRect.Height);

            moveables.Add(purplePlatform);
            moveables.Add(greenPlatform);

            // Set the button collider based on the position and size of the button sprite
            buttonCollider = new FloatRect(purpleButton.Position.X, purpleButton.Position.Y, purpleButton.TextureRect.Width * purpleButton.Scale.X, purpleButton.TextureRect.Height * purpleButton.Scale.Y);
            buttonCollider2 = new FloatRect(greenButton.Position.X, greenButton.Position.Y, greenButton.TextureRect.Width * greenButton.Scale.X, greenButton.TextureRect.Height * greenButton.Scale.Y);
        }

        public override void Update(float deltaTime)
        {
            // Check collision between player and button
            isButtonPressed = player.GetBounds().Intersects(buttonCollider) || player.GetBounds2().Intersects(buttonCollider);

            // Move the platform down if the button is pressed
            if (isButtonPressed && purplePlatform!.Position.Y < 60) // Adjust the maximum distance as needed
            {
                purplePlatform.Position += new Vector2f(0, platformSpeed * deltaTime);
            }
            else if (!isButtonPressed && purplePlatform!.Position.Y > 0) // Move the platform back up to its original position
            {
                purplePlatform.Position -= new Vector2f(0, platformSpeed * deltaTime);
            }
            // Check collision between player and button
            isButtonPressed2 = player.GetBounds().Intersects(buttonCollider2) || player.GetBounds2().Intersects(buttonCollider2);

            // Move the platform down if the button is pressed
            if (isButtonPressed2 && greenPlatform!.Position.Y < 290) // Adjust the maximum distance as needed
            {
                greenPlatform.Position += new Vector2f(0, platformSpeed * deltaTime);
            }
            else if (!isButtonPressed2 && greenPlatform!.Position.Y > 220) // Move the platform back up to its original position
            {
                greenPlatform.Position -= new Vector2f(0, platformSpeed * deltaTime);
            }
        }

        public override void Draw(RenderWindow window)
        {
            foreach (Sprite moveable in moveables)
            {
                window.Draw(moveable);
            }
            window.Draw(greenButton);
            window.Draw(purpleButton);
        }
    }
}