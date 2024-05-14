// MultiMediaTechnology / FHS | MultiMediaProjekt 1  | van Renen Nicolas

using SFML.Graphics;
using SFML.System;
using SFML.Window;

namespace Shiftee;

public class FloorCollision
{
    public enum Direction
    {
        Left = 0,
        Right = 1,
        Top = 2,
        Bottom = 3,
        None = 4
    }
    private readonly List<FloatRect> floors;
    private readonly List<Sprite> playerSprites;
    private readonly List<Rigidbody> playerRigidbodies = new();
    private readonly List<Sprite> moveables = new();
    private Vector2f _positionCorrection = new();
    public FloorCollision(List<Sprite> playerSprites, List<Rigidbody> playerRigidbodies, List<FloatRect> floors, List<Sprite> moveables)
    {
        this.playerSprites = playerSprites;
        this.playerRigidbodies = playerRigidbodies;
        this.floors = floors;
        this.moveables = moveables;
    }

    public void Update()
    {
        for (int i = 0; i < playerSprites.Count; i++)
        {
            Sprite sprite = playerSprites[i];
            Rigidbody rigidbody = playerRigidbodies[i];

            foreach (var floor in floors)
            {
                _positionCorrection = sprite.Position;

                if (floor.Intersects(sprite.GetGlobalBounds()))
                {
                    Manifold m = GenerateManifold(sprite.GetGlobalBounds(), floor);
                    Direction d = GetDirection(m, sprite, floor);
                    if (d == Direction.Top)
                    {
                        _positionCorrection.Y = floor.Top - sprite.GetGlobalBounds().Height;
                        sprite.Position = _positionCorrection;
                        if (rigidbody._object_velocity.Y > 0)
                        {
                            rigidbody._object_velocity.Y = 0f;
                        }
                        rigidbody.SetGrounded(true);
                    }
                    else if (d == Direction.Bottom)
                    {
                        _positionCorrection.Y = floor.Top + floor.Height;
                        sprite.Position = _positionCorrection;
                        rigidbody._object_velocity.Y = 0f;
                        rigidbody.SetGrounded(false);
                    }
                    else if (d == Direction.Left)
                    {
                        _positionCorrection.X = floor.Left + floor.Width;
                        sprite.Position = _positionCorrection;
                    }
                    else if (d == Direction.Right)
                    {
                        _positionCorrection.X = floor.Left - sprite.GetGlobalBounds().Width;
                        sprite.Position = _positionCorrection;
                    }
                }
            }
            foreach (Sprite moveable in moveables)
            {
                FloatRect moveableBounds = moveable.GetGlobalBounds();
                const float reductionAmount = 15f; // Specify the amount by which you want to reduce the size

                // Calculate the new bounds dimensions
                float newWidth = moveableBounds.Width - reductionAmount;
                float newHeight = moveableBounds.Height - reductionAmount;

                // Calculate the offset to keep the center of the bounds the same
                float offsetX = (moveableBounds.Width - newWidth) / 2f;
                float offsetY = (moveableBounds.Height - newHeight) / 2f;

                // Update the bounds with the new dimensions and offset
                moveableBounds.Left += offsetX;
                moveableBounds.Top += offsetY;
                moveableBounds.Width = newWidth;
                moveableBounds.Height = newHeight;

                if (moveableBounds.Intersects(sprite.GetGlobalBounds()))
                {
                    Manifold m = GenerateManifold(sprite.GetGlobalBounds(), moveableBounds);
                    Direction d = GetDirection2(m, sprite, moveable);
                    if (d == Direction.Top)
                    {
                        _positionCorrection.Y = moveableBounds.Top - sprite.GetGlobalBounds().Height;
                        sprite.Position = _positionCorrection;
                        if (rigidbody._object_velocity.Y > 0)
                        {
                            rigidbody._object_velocity.Y = 0f;
                        }
                        rigidbody.SetGrounded(true);
                    }
                    else if (d == Direction.Bottom)
                    {
                        _positionCorrection.Y = moveableBounds.Top + moveableBounds.Height;
                        sprite.Position = _positionCorrection;
                        rigidbody._object_velocity.Y = 0f;
                        rigidbody.SetGrounded(false);
                    }
                    else if (d == Direction.Left)
                    {
                        _positionCorrection.X = moveableBounds.Left + moveableBounds.Width;
                        sprite.Position = _positionCorrection;
                    }
                    else if (d == Direction.Right)
                    {
                        _positionCorrection.X = moveableBounds.Left - sprite.GetGlobalBounds().Width;
                        sprite.Position = _positionCorrection;
                    }
                }
            }
        }
    }

    public static Direction GetDirection(Manifold m, Sprite sprite, FloatRect floor)
    {
        //Corrects collision normal if the AABB is a Rectangle, does nothing if its a square
        float scaleY = (sprite.GetGlobalBounds().Width) / (sprite.GetGlobalBounds().Height);
        m._normal.Y *= scaleY;

        scaleY = (floor.Width) / (floor.Height);
        m._normal.Y *= scaleY;

        float angle = MathF.Atan2(m._normal.Y, m._normal.X);
        float degrees = angle * (180 / MathF.PI);

        // Adjust the angle to be positive and within 360 degrees
        if (degrees <= 0)
            degrees += 360;
        // Determine the collision direction based on the angle
        if (degrees > 40 && degrees <= 135)
            return Direction.Bottom;
        if (degrees > 135 && degrees <= 208)
            return Direction.Right;
        if (degrees > 208 && degrees <= 315)
            return Direction.Top;
        if (degrees > 315 && degrees <= 360)
            return Direction.Left;
        return Direction.Left;
    }
    public static Direction GetDirection2(Manifold m, Sprite sprite, Sprite moveable)
    {
        //Corrects collision normal if the AABB is a Rectangle, does nothing if its a square
        float scaleY = (sprite.GetGlobalBounds().Width) / (sprite.GetGlobalBounds().Height);
        m._normal.Y *= scaleY;

        scaleY = moveable.GetGlobalBounds().Width / (moveable.GetGlobalBounds().Height);
        m._normal.Y *= scaleY;

        float angle = MathF.Atan2(m._normal.Y, m._normal.X);
        float degrees = angle * (180 / MathF.PI);

        // Adjust the angle to be positive and within 360 degrees
        if (degrees <= 0)
            degrees += 360;
        // Determine the collision direction based on the angle
        if (degrees > 40 && degrees <= 135)
            return Direction.Bottom;
        if (degrees > 135 && degrees <= 208)
            return Direction.Right;
        if (degrees > 208 && degrees <= 315)
            return Direction.Top;
        if (degrees > 315 && degrees <= 360)
            return Direction.Left;
        return Direction.Left;
    }
    public static Manifold GenerateManifold(FloatRect Collider1, FloatRect Collider2)
    {
        Manifold manifold = new();
        manifold._depth.X = Math.Min((Collider1.Left + Collider1.Width) - Collider2.Left,
            (Collider2.Left + Collider2.Width) - Collider1.Left);
        manifold._depth.Y = Math.Min((Collider1.Top + Collider1.Height) - Collider2.Top,
            (Collider2.Top + Collider2.Height) - Collider1.Top);

        manifold._normal = (new Vector2f(Collider1.Left + (Collider1.Width / 2), Collider1.Top + (Collider1.Height / 2)) -
                            new Vector2f(Collider2.Left + (Collider2.Width / 2), Collider2.Top + (Collider2.Height / 2)))
            .Normalize();
        return manifold;
    }
    public struct Manifold
    {
        public Vector2f _normal;
        public Vector2f _depth;
    }
}