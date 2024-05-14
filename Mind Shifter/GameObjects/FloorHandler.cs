// MultiMediaTechnology / FHS | MultiMediaProjekt 1  | van Renen Nicolas

using System.Collections.Generic;
using SFML.Graphics;
using SFML.System;
using SFML.Window;

namespace Shiftee
{
    public class Floor : GameObject
    {
        public List<FloatRect> floors = new();

        private readonly FloatRect[] floorRects = new FloatRect[]
        {
            new FloatRect(0, 468, 100, 488),
            new FloatRect(491, 85, 160, 13),
            new FloatRect(212, 418, 55, 15),
            new FloatRect(351, 436, 55, 15),
            new FloatRect(52, 180, 16, 235),
            new FloatRect(70, 395, 42, 20),
            new FloatRect(102, 395, 48, 100),
            new FloatRect(60, 170, 180, 15),
            new FloatRect(237, 138, 13, 38),
            new FloatRect(240, 136, 60, 13),
            new FloatRect(288, 105, 12, 40),
            new FloatRect(288, 104, 81, 13),
            new FloatRect(68, 90, 58, 13),
            new FloatRect(0, 55, 58, 13),
            new FloatRect(385, 181, 40, 13),
            new FloatRect(419, 0, 13, 342),
            new FloatRect(419, 330, 132, 13),
            new FloatRect(313, 220, 56, 13),
            new FloatRect(205, 279, 79, 13),
            new FloatRect(204, 170, 13, 115),
            new FloatRect(466, 433, 90, 60),
            new FloatRect(550, 428, 30, 50),
            new FloatRect(556, 425, 30, 50),
            new FloatRect(562, 421, 30, 50),
            new FloatRect(565, 416, 30, 50),
            new FloatRect(585, 413, 30, 50),
            new FloatRect(590, 409, 30, 50),
            new FloatRect(601, 366, 50, 50),
            new FloatRect(584, 282, 60, 13),
            new FloatRect(495, 227, 71, 13),
            new FloatRect(491, 85, 13, 145)
        };

        public override void Initialize()
        {
            floors.AddRange(floorRects);
        }

        public override void Draw(RenderWindow window)
        {
            // Implement drawing logic here
        }

        public override void Update(float deltaTime)
        {
            // Implement update logic here
        }
    }
}
