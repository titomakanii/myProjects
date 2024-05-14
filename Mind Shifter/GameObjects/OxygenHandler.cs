// MultiMediaTechnology / FHS | MultiMediaProjekt 1  | van Renen Nicolas

using SFML.Graphics;
using SFML.System;
using SFML.Window;
using SFML.Audio;
using System.Collections.Generic;

namespace Shiftee
{
    public class Oxygen : GameObject
    {
        public List<Sprite> o2Tanks = new();
        public Sprite? o2Tank;
        public Sprite? o2Tank2;
        public Sprite? o2Tank3;
        public Sprite? o2Tank4;
        public Sprite? o2Tank5;

        private readonly float hoveringAmplitude = 0.04f; // Adjust the hovering effect amplitude
        private readonly float hoveringSpeed = 3.5f; // Adjust the hovering effect speed
        private float elapsedTime = 0f;

        public override void Initialize()
        {
            for (int i = 1; i <= 5; i++)
            {
                string textureName = "o2Tank" + i;
                const string texturePath = "./Assets/oxygentank.png";
                AssetManager.LoadTexture(textureName, texturePath);

                Sprite o2Tank = new(AssetManager.Textures[textureName])
                {
                    Scale = new Vector2f(0.25f, 0.25f)
                };

                switch (i)
                {
                    case 1:
                        o2Tank.Position = new Vector2f(200, 118);
                        break;
                    case 2:
                        o2Tank.Position = new Vector2f(210, 226);
                        break;
                    case 3:
                        o2Tank.Position = new Vector2f(203, 367);
                        break;
                    case 4:
                        o2Tank.Position = new Vector2f(426, 279);
                        break;
                    case 5:
                        o2Tank.Position = new Vector2f(520, 380);
                        break;
                }

                o2Tank.TextureRect = new IntRect(0, 0, o2Tank.TextureRect.Width, o2Tank.TextureRect.Height);
                o2Tanks.Add(o2Tank);
            }
        }

        public override void Update(float deltaTime)
        {
            elapsedTime += deltaTime;

            // Update the positions of the o2Tank sprites to create a hovering effect
            for (int i = 0; i < o2Tanks.Count; i++)
            {
                Sprite o2Tank = o2Tanks[i];

                // Calculate the vertical offset based on the hovering effect
                float yOffset = hoveringAmplitude * (float)Math.Sin(hoveringSpeed * elapsedTime);

                // Update the position of the sprite
                o2Tank.Position = new Vector2f(o2Tank.Position.X, o2Tank.Position.Y + yOffset);
            }
        }

        public override void Draw(RenderWindow window)
        {
            foreach (Sprite o2Tank in o2Tanks)
            {
                window.Draw(o2Tank);
            }
        }
    }
}