// MultiMediaTechnology / FHS | MultiMediaProjekt 1  | van Renen Nicolas

using SFML.Graphics;
using SFML.System;
using SFML.Window;
using SFML.Audio;
using System.Collections.Generic;

namespace Shiftee
{
    public class Cage : GameObject
    {
        public Sprite? cage;
        private Vector2f _positionCorrection = new();
        public int score;
        public int score2;
        private readonly List<Sprite> playerSprites = new();
        public Cage(ref int score, ref int score2, List<Sprite> playerSprites)
        {
            this.score = score;
            this.score2 = score2;
            this.playerSprites = playerSprites;
        }
        public override void Initialize()
        {
            AssetManager.LoadTexture("cage", "./Assets/cage.png");
            cage = new Sprite(AssetManager.Textures["cage"])
            {
                Scale = new Vector2f(0.25f, 0.25f),
                Position = new Vector2f(69, 272)
            };
            cage.TextureRect = new IntRect(0, 0, cage.TextureRect.Width, cage.TextureRect.Height);
        }

        public override void Update(float deltaTime)
        {
            foreach (Sprite sprite in playerSprites)
            {
                _positionCorrection = sprite.Position;

                if (cage!.GetGlobalBounds().Intersects(sprite.GetGlobalBounds()))
                {
                    _positionCorrection.X = cage.GetGlobalBounds().Left + cage.GetGlobalBounds().Width;
                    sprite.Position = _positionCorrection;
                }
            }
        }

        public override void Draw(RenderWindow window)
        {
            window.Draw(cage);
        }
    }
}