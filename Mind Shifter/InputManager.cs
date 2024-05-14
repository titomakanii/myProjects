// MultiMediaTechnology / FHS | MultiMediaProjekt 1  | van Renen Nicolas

using SFML.Window;
using System.Collections.Generic;

namespace Shiftee
{
    public class InputManager
    {
        private static InputManager instance = null!;
        private readonly Dictionary<Keyboard.Key, bool> isKeyDown = new();
        private readonly Dictionary<Keyboard.Key, bool> isKeyPressed = new();
        private readonly Dictionary<Keyboard.Key, bool> isKeyUp = new();

        private readonly Dictionary<Mouse.Button, bool> isMouseDown = new();
        private readonly Dictionary<Mouse.Button, bool> isMousePressed = new();
        private readonly Dictionary<Mouse.Button, bool> isMouseUp = new();

        // Simplified version of a Singleton
        public static InputManager Instance
        {
            get { return instance ??= new InputManager(); }
        }

        public void Initialize(Window window)
        {
            window.SetKeyRepeatEnabled(false);
            window.KeyPressed += OnKeyPressed;
            window.KeyReleased += OnKeyReleased;

            window.MouseButtonPressed += OnMouseButtonPressed;
            window.MouseButtonReleased += OnMouseButtonReleased;

            InitKeyboardMap();
            InitMouseMap();
        }

        private void InitKeyboardMap()
        {
            isKeyDown.Add(Keyboard.Key.W, false);
            isKeyDown.Add(Keyboard.Key.A, false);
            isKeyDown.Add(Keyboard.Key.S, false);
            isKeyDown.Add(Keyboard.Key.D, false);
            isKeyDown.Add(Keyboard.Key.Space, false);
            isKeyDown.Add(Keyboard.Key.R, false);

            isKeyUp.Add(Keyboard.Key.W, false);
            isKeyUp.Add(Keyboard.Key.A, false);
            isKeyUp.Add(Keyboard.Key.S, false);
            isKeyUp.Add(Keyboard.Key.D, false);
            isKeyUp.Add(Keyboard.Key.Space, false);
            isKeyUp.Add(Keyboard.Key.R, false);

            isKeyPressed.Add(Keyboard.Key.W, false);
            isKeyPressed.Add(Keyboard.Key.A, false);
            isKeyPressed.Add(Keyboard.Key.S, false);
            isKeyPressed.Add(Keyboard.Key.D, false);
            isKeyPressed.Add(Keyboard.Key.Space, false);
            isKeyPressed.Add(Keyboard.Key.R, false);
        }

        private void InitMouseMap()
        {
            isMouseDown.Add(Mouse.Button.Left, false);
            isMouseDown.Add(Mouse.Button.Right, false);
            isMouseDown.Add(Mouse.Button.Middle, false);

            isMouseUp.Add(Mouse.Button.Left, false);
            isMouseUp.Add(Mouse.Button.Right, false);
            isMouseUp.Add(Mouse.Button.Middle, false);

            isMousePressed.Add(Mouse.Button.Left, false);
            isMousePressed.Add(Mouse.Button.Right, false);
            isMousePressed.Add(Mouse.Button.Middle, false);
        }

        public void Update(float deltaTime)
        {
            // Reset keyboard input states
            foreach (var kvp in isKeyDown)
                isKeyDown[kvp.Key] = false;

            foreach (var kvp in isKeyUp)
                isKeyUp[kvp.Key] = false;

            // Reset mouse input states
            foreach (var kvp in isMouseDown)
                isMouseDown[kvp.Key] = false;

            foreach (var kvp in isMouseUp)
                isMouseUp[kvp.Key] = false;
        }

        public bool GetKeyPressed(Keyboard.Key key)
        {
            return isKeyPressed.ContainsKey(key) && isKeyPressed[key];
        }

        public bool GetKeyDown(Keyboard.Key key)
        {
            return isKeyDown.ContainsKey(key) && isKeyDown[key];
        }

        public bool GetKeyUp(Keyboard.Key key)
        {
            return isKeyUp.ContainsKey(key) && isKeyUp[key];
        }

        public bool GetMousePressed(Mouse.Button button)
        {
            return isMousePressed.ContainsKey(button) && isMousePressed[button];
        }

        public bool GetMouseDown(Mouse.Button button)
        {
            return isMouseDown.ContainsKey(button) && isMouseDown[button];
        }

        public bool GetMouseUp(Mouse.Button button)
        {
            return isMouseUp.ContainsKey(button) && isMouseUp[button];
        }

        private void OnKeyPressed(object? sender, KeyEventArgs e)
        {
            if (isKeyPressed.ContainsKey(e.Code))
            {
                isKeyDown[e.Code] = true;
                isKeyPressed[e.Code] = true;
            }
        }

        private void OnKeyReleased(object? sender, KeyEventArgs e)
        {
            if (isKeyPressed.ContainsKey(e.Code))
            {
                isKeyUp[e.Code] = true;
                isKeyPressed[e.Code] = false;
            }
        }

        private void OnMouseButtonPressed(object? sender, MouseButtonEventArgs e)
        {
            if (isMousePressed.ContainsKey(e.Button))
            {
                isMouseDown[e.Button] = true;
                isMousePressed[e.Button] = true;
            }
        }

        private void OnMouseButtonReleased(object? sender, MouseButtonEventArgs e)
        {
            if (isMousePressed.ContainsKey(e.Button))
            {
                isMouseUp[e.Button] = true;
                isMousePressed[e.Button] = false;
            }
        }
    }
}
