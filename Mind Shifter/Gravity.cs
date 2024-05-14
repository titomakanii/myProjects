// MultiMediaTechnology / FHS | MultiMediaProjekt 1  | van Renen Nicolas

using SFML.Graphics;
using SFML.System;

namespace Shiftee
{
    public class Rigidbody
    {
        public Vector2f _object_velocity = new(0, 0);
        public float _appliedGravity = 72f;
        private readonly Sprite _objectSprite;
        private readonly float _physicUpdatesPerSecond = 120;
        private float _frameTimeCounter = 0;

        public bool IsGrounded { get; private set; }

        public Rigidbody(ref Sprite objectSprite)
        {
            _objectSprite = objectSprite;
            IsGrounded = false;
        }

        public void Update(float deltaTime)
        {
            _frameTimeCounter += deltaTime;
            if (_frameTimeCounter >= 1 / _physicUpdatesPerSecond)
            {
                _object_velocity.Y += deltaTime * _appliedGravity;

                _objectSprite.Position += _object_velocity;

                _frameTimeCounter = 0;
            }
        }

        public void SetGrounded(bool grounded)
        {
            IsGrounded = grounded;
        }
    }
}