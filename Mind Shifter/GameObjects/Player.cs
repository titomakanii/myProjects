// MultiMediaTechnology / FHS | MultiMediaProjekt 1  | van Renen Nicolas

using SFML.Graphics;
using SFML.System;
using SFML.Window;

namespace Shiftee
{
    public class Player : GameObject
    {
        public enum AnimationType
        {
            IdleLeft,
            IdleRight,
            RunRight,
            RunLeft,
            Jump
        }
        private const int sprite_TILING_X = 14;
        private const int sprite_TILING_Y = 5;

        public float MOVE_SPEED = 150.0f;

        private readonly float animationSpeed = 8;

        private readonly int[] animationTypeFramesCount =
        {
            4,
            4,
            14,
            14,
            9
        };

        private float animationTimeIndex;

        private AnimationType currentAnimation = AnimationType.IdleRight;

        public Sprite? sprite1;
        public Sprite? sprite2;
        public float impulse = 2200.0f;
        private bool isTimerStarted = false;
        private RectangleShape? healthBar1;
        private RectangleShape? healthBar2;
        private Text? healthBarText1;
        private Text? healthBarText2;
        private float healthBarWidth;
        private readonly float healthBarHeight = 10f;
        private readonly float maxHealth = 20f;
        private readonly Clock healthTimer1 = new();
        public float currentHealth1 = 20f;
        private readonly Clock healthTimer2 = new();
        public float currentHealth2 = 20f;
        private Font? font;
        private const string healthBarLabelText = "O2";

        public Rigidbody? _playerRigidbody1;
        public Rigidbody? _playerRigidbody2;
        private bool isPlayer1Active = true;

        FloatRect bounds = new();
        FloatRect bounds2 = new();

        private bool isStandingOnFloor;
        private bool isStandingOnFloor2;

        private readonly List<FloatRect> floors = new();
        private readonly List<Sprite> o2Tanks = new();
        public List<Sprite> playerSprites = new();
        public List<Rigidbody> playerRigidbodies = new();

        private const float MAX_JUMP_HEIGHT = 310.0f;
        private bool isJumping;
        private float initialJumpY;

        public Player(List<FloatRect> floors, List<Sprite> o2Tanks)
        {
            this.floors = floors;
            this.o2Tanks = o2Tanks;
        }

        public override void Initialize()
        {
            AssetManager.LoadTexture("Character", "./Assets/player1.png");
            AssetManager.LoadTexture("Character2", "./Assets/player2.png");
            font = new Font("Assets/ARCADECLASSIC.ttf");

            sprite1 = new Sprite(AssetManager.Textures["Character"])
            {
                Position = new Vector2f(10, 420),
                Scale = new Vector2f(2.5f, 2.5f)
            };
            sprite1.TextureRect = new IntRect(0, 0, sprite1.TextureRect.Width / sprite_TILING_X,
                sprite1.TextureRect.Height / sprite_TILING_Y);
            _playerRigidbody1 = new Rigidbody(ref sprite1);

            sprite2 = new Sprite(AssetManager.Textures["Character2"])
            {
                Position = new Vector2f(590, 0),
                Scale = new Vector2f(2.5f, 2.5f)
            };
            sprite2.TextureRect = new IntRect(0, 0, sprite2.TextureRect.Width / sprite_TILING_X,
                                            sprite2.TextureRect.Height / sprite_TILING_Y);
            _playerRigidbody2 = new Rigidbody(ref sprite2);

            playerSprites.Add(sprite1);
            playerSprites.Add(sprite2);
            playerRigidbodies.Add(_playerRigidbody1);
            playerRigidbodies.Add(_playerRigidbody2);

            healthBarWidth = sprite1.GetGlobalBounds().Width;
            healthBar1 = new RectangleShape(new Vector2f(healthBarWidth, healthBarHeight))
            {
                Origin = new Vector2f(healthBarWidth / 2f, healthBarHeight / 2f),
                FillColor = Color.Red
            };

            healthBarText1 = new Text(healthBarLabelText, font, 12)
            {
                FillColor = Color.White
            };

            healthBar2 = new RectangleShape(new Vector2f(healthBarWidth, healthBarHeight))
            {
                Origin = new Vector2f(healthBarWidth / 2f, healthBarHeight / 2f),
                FillColor = Color.Red
            };

            healthBarText2 = new Text(healthBarLabelText, font, 12)
            {
                FillColor = Color.White
            };

            AssetManager.LoadSound("Jump", "./Assets/jump.wav");
            AssetManager.LoadSound("Oxygen", "./Assets/oxygen.wav");
        }

        public override void Update(float deltaTime)
        {
            OrientationAwareRunToIdle();
            SpriteMovement(deltaTime);
            UpdatePhysics();
            KeepInScreen();
            DoSpriteAnimation();
            HandleAudio();
            _playerRigidbody1!.Update(deltaTime);
            _playerRigidbody2!.Update(deltaTime);
            isStandingOnFloor = IsStandingOnFloor();
            isStandingOnFloor2 = IsStandingOnFloor2();
            animationTimeIndex += deltaTime * animationSpeed;
            UpdateHealthBar();
        }

        private void OrientationAwareRunToIdle()
        {
            switch (currentAnimation)
            {
                case AnimationType.RunLeft:
                    currentAnimation = AnimationType.IdleLeft;
                    break;

                case AnimationType.RunRight:
                    currentAnimation = AnimationType.IdleRight;
                    break;

                case AnimationType.Jump:
                    currentAnimation = AnimationType.IdleRight;
                    break;

                default:
                    // Handle default case, if needed
                    break;
            }
        }

        public FloatRect GetBounds()
        {
            bounds = sprite1!.GetGlobalBounds();
            bounds.Left += 8;
            bounds.Width -= 16;
            return bounds;
        }
        public FloatRect GetBounds2()
        {
            bounds2 = sprite2!.GetGlobalBounds();
            bounds2.Left += 8;
            bounds2.Width -= 16;
            return bounds2;
        }
        private void SpriteMovement(float deltaTime)
        {
            if (InputManager.Instance.GetKeyDown(Keyboard.Key.S))
            {
                SwitchPlayer();
            }
            if (isPlayer1Active)
            {
                if (InputManager.Instance.GetKeyPressed(Keyboard.Key.A))
                {
                    currentAnimation = AnimationType.RunLeft;
                    sprite1!.Position -= new Vector2f(1, 0) * MOVE_SPEED * deltaTime;
                }

                if (InputManager.Instance.GetKeyPressed(Keyboard.Key.D))
                {
                    currentAnimation = AnimationType.RunRight;
                    sprite1!.Position += new Vector2f(1, 0) * MOVE_SPEED * deltaTime;
                }

                if (InputManager.Instance.GetKeyDown(Keyboard.Key.Space) && isStandingOnFloor)
                {
                    currentAnimation = AnimationType.Jump;
                    isJumping = true;
                    initialJumpY = sprite1!.Position.Y;
                    _playerRigidbody1!._object_velocity += new Vector2f(0, -1) * impulse * deltaTime;
                }
            }
            else
            {
                if (InputManager.Instance.GetKeyPressed(Keyboard.Key.A))
                {
                    currentAnimation = AnimationType.RunLeft;
                    sprite2!.Position -= new Vector2f(1, 0) * MOVE_SPEED * deltaTime;
                }

                if (InputManager.Instance.GetKeyPressed(Keyboard.Key.D))
                {
                    currentAnimation = AnimationType.RunRight;
                    sprite2!.Position += new Vector2f(1, 0) * MOVE_SPEED * deltaTime;
                }

                if (InputManager.Instance.GetKeyDown(Keyboard.Key.Space) && isStandingOnFloor2)
                {
                    currentAnimation = AnimationType.Jump;
                    isJumping = true;
                    initialJumpY = sprite2!.Position.Y;
                    _playerRigidbody2!._object_velocity += new Vector2f(0, -1) * impulse * deltaTime;
                }
            }
        }
        private void SwitchPlayer()
        {
            isPlayer1Active = !isPlayer1Active;
            if (isPlayer1Active)
            {
                currentAnimation = AnimationType.IdleRight;
            }
            else
            {
                currentAnimation = AnimationType.IdleLeft;
            }
        }

        private void UpdatePhysics()
        {
            if (isJumping && sprite1!.Position.Y <= initialJumpY - MAX_JUMP_HEIGHT)
            {
                _playerRigidbody1!._object_velocity.Y = 0.0f;
                isJumping = false;
            }
        }

        private bool IsStandingOnFloor()
        {
            bounds = GetBounds();
            foreach (FloatRect floor in floors)
            {
                if (bounds.Top + bounds.Height >= floor.Top &&
                    bounds.Top + bounds.Height <= floor.Top + 1f &&
                    bounds.Left + bounds.Width > floor.Left &&
                    bounds.Left < floor.Left + floor.Width)
                {
                    return true;
                }
            }

            return false;
        }
        private bool IsStandingOnFloor2()
        {
            bounds2 = GetBounds2();
            foreach (FloatRect floor in floors)
            {
                if (bounds2.Top + bounds2.Height >= floor.Top &&
                    bounds2.Top + bounds2.Height <= floor.Top + 1f &&
                    bounds2.Left + bounds2.Width > floor.Left &&
                    bounds2.Left < floor.Left + floor.Width)
                {
                    return true;
                }
            }

            return false;
        }
        public void KeepInScreen()
        {
            foreach (Sprite sprite in playerSprites)
            {
                if (sprite.Position.X < 0)
                {
                    sprite.Position = new Vector2f(0, sprite.Position.Y);
                }
                else if (sprite.Position.X > SceneHandler.WIDTH - sprite.GetGlobalBounds().Width)
                {
                    sprite.Position = new Vector2f(SceneHandler.WIDTH - sprite.GetGlobalBounds().Width, sprite.Position.Y);
                }

                if (sprite.Position.Y < 0)
                {
                    sprite.Position = new Vector2f(sprite.Position.X, 0);
                }
                else if (sprite.Position.Y > SceneHandler.HEIGHT - sprite.GetGlobalBounds().Height)
                {
                    sprite.Position = new Vector2f(sprite.Position.X, SceneHandler.HEIGHT - sprite.GetGlobalBounds().Height);
                }
            }
        }

        private void UpdateHealthBar()
        {
            float elapsedTime1 = healthTimer1.ElapsedTime.AsSeconds();
            if (elapsedTime1 >= 20f)
            {
                currentHealth1 = 0f;
            }
            else
            {
                float remainingTime = 20f - elapsedTime1;
                currentHealth1 = remainingTime / 20f * maxHealth;
            }

            healthBar1!.Size = new Vector2f(healthBarWidth * (currentHealth1 / maxHealth), healthBarHeight);
            healthBar1.Position = sprite1!.Position + new Vector2f(25, -5);

            healthBarText1!.Position = healthBar1.Position + new Vector2f(-healthBarWidth + healthBarText1.GetGlobalBounds().Width + 6f, -healthBarText1.GetGlobalBounds().Height - 1f);

            float elapsedTime2 = healthTimer2.ElapsedTime.AsSeconds();
            if (elapsedTime2 >= 20f)
            {
                currentHealth2 = 0f;
            }
            else
            {
                float remainingTime = 20f - elapsedTime2;
                currentHealth2 = remainingTime / 20f * maxHealth;
            }
            healthBar2!.Size = new Vector2f(healthBarWidth * (currentHealth2 / maxHealth), healthBarHeight);
            healthBar2.Position = sprite2!.Position + new Vector2f(25, -5);

            healthBarText2!.Position = healthBar2.Position + new Vector2f(-healthBarWidth + healthBarText2.GetGlobalBounds().Width + 6f, -healthBarText2.GetGlobalBounds().Height - 1f);

            List<Sprite> o2TanksToRemove = new();

            foreach (Sprite o2Tank in o2Tanks)
            {
                if (bounds.Intersects(o2Tank.GetGlobalBounds()) || bounds2.Intersects(o2Tank.GetGlobalBounds()))
                {
                    AssetManager.Sounds["Oxygen"].Play();

                    if (isPlayer1Active)
                    {
                        healthTimer1.Restart();
                    }
                    else
                    {
                        healthTimer2.Restart();
                    }

                    o2TanksToRemove.Add(o2Tank);
                }
            }
            foreach (Sprite o2TankToRemove in o2TanksToRemove)
            {
                AssetManager.Sounds["Oxygen"].Play();
                o2Tanks.Remove(o2TankToRemove);
            }
        }

        private void DoSpriteAnimation()
        {
            Sprite? activeSprite = isPlayer1Active ? sprite1 : sprite2;

            var animationFrame = (int)animationTimeIndex % animationTypeFramesCount[(int)currentAnimation];
            activeSprite!.TextureRect = new IntRect(animationFrame * activeSprite.TextureRect.Width,
                (int)currentAnimation * activeSprite.TextureRect.Height, activeSprite.TextureRect.Width, activeSprite.TextureRect.Height);
        }

        private static void HandleAudio()
        {
            if (InputManager.Instance.GetKeyDown(Keyboard.Key.Space))
            {
                AssetManager.Sounds["Jump"].Play();
                AssetManager.Sounds["Jump"].Volume = 45;
            }
        }

        public override void Draw(RenderWindow window)
        {
            window.Draw(sprite1);
            window.Draw(sprite2);

            Sprite? activeSprite = isPlayer1Active ? sprite1 : sprite2;
            if (activeSprite != null)
            {
                float triangleSize = 10.0f; // Adjust the size as needed
                ConvexShape triangleMarker = new ConvexShape(3)
                {
                    Origin = new Vector2f(triangleSize / 2, triangleSize / 2),
                    FillColor = Color.Yellow // Adjust the color as needed
                };

                // Define the vertices of the triangle
                triangleMarker.SetPoint(0, new Vector2f(-triangleSize / 2, -triangleSize / 2));
                triangleMarker.SetPoint(1, new Vector2f(triangleSize / 2, -triangleSize / 2));
                triangleMarker.SetPoint(2, new Vector2f(0, triangleSize / 2));

                // Position the triangle above the active player sprite
                FloatRect bounds = activeSprite.GetGlobalBounds();
                triangleMarker.Position = new Vector2f(bounds.Left+5 + (bounds.Width / 2), bounds.Top-5 - triangleSize);

                window.Draw(triangleMarker);
            }
            if (!isTimerStarted)
            {
                healthTimer1.Restart();
                healthTimer2.Restart();
                isTimerStarted = true;
            }
            window.Draw(healthBar1);
            window.Draw(healthBarText1);
            window.Draw(healthBar2);
            window.Draw(healthBarText2);
        }
    }
}