// MultiMediaTechnology / FHS | MultiMediaProjekt 1  | van Renen Nicolas

using SFML.Graphics;
using SFML.System;
using SFML.Window;

namespace Shiftee;

public abstract class GameObject : Transformable
{
    public abstract void Initialize();
    public abstract void Update(float deltaTime);
    public abstract void Draw(RenderWindow window);
}