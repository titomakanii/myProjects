// MultiMediaTechnology / FHS | MultiMediaProjekt 1  | van Renen Nicolas

using SFML.Graphics;
using SFML.System;

namespace Shiftee;

internal static class DebugDraw
{
    public static RenderWindow? ActiveWindow { get; set; }

    public static void DrawLine(Vector2f startPoint, Vector2f endPoint, Color color)
    {
        var line =
            new Vertex[]
            {
                new(startPoint, color),
                new(endPoint, color)
            };
        ActiveWindow!.Draw(line, 0, 2, PrimitiveType.Lines);
    }

    public static void DrawRectOutline(Vector2f position, int width, int height, Color color)
    {
        var bottomLeftPos = new Vector2f(position.X, position.Y + height);
        var topLeftPos = new Vector2f(position.X, position.Y);
        var topRightPos = new Vector2f(position.X + width, position.Y);
        var bottomRightPos =
            new Vector2f(position.X + width, position.Y + height);

        var line =
            new Vertex[]
            {
                new(bottomLeftPos, color),
                new(topLeftPos, color)
            };
        ActiveWindow!.Draw(line, 0, 2, PrimitiveType.Lines);

        line =
            new Vertex[]
            {
                new(topLeftPos, color),
                new(topRightPos, color)
            };
        ActiveWindow!.Draw(line, 0, 2, PrimitiveType.Lines);

        line =
            new Vertex[]
            {
                new(topRightPos, color),
                new(bottomRightPos, color)
            };
        ActiveWindow!.Draw(line, 0, 2, PrimitiveType.Lines);

        line =
            new Vertex[]
            {
                new(bottomRightPos, color),
                new(bottomLeftPos, color)
            };
        ActiveWindow!.Draw(line, 0, 2, PrimitiveType.Lines);
    }

    public static void DrawRectOutline(IntRect intRect, Color color)
    {
        var position = new Vector2f(intRect.Left, intRect.Top);
        var width = intRect.Width;
        var height = intRect.Height;

        var bottomLeftPos = new Vector2f(position.X, position.Y + height);
        var topLeftPos = new Vector2f(position.X, position.Y);
        var topRightPos = new Vector2f(position.X + width, position.Y);
        var bottomRightPos =
            new Vector2f(position.X + width, position.Y + height);

        var line =
            new Vertex[]
            {
                new(bottomLeftPos, color),
                new(topLeftPos, color)
            };
        ActiveWindow!.Draw(line, 0, 2, PrimitiveType.Lines);

        line =
            new Vertex[]
            {
                new(topLeftPos, color),
                new(topRightPos, color)
            };
        ActiveWindow!.Draw(line, 0, 2, PrimitiveType.Lines);

        line =
            new Vertex[]
            {
                new(topRightPos, color),
                new(bottomRightPos, color)
            };
        ActiveWindow!.Draw(line, 0, 2, PrimitiveType.Lines);

        line =
            new Vertex[]
            {
                new(bottomRightPos, color),
                new(bottomLeftPos, color)
            };
        ActiveWindow!.Draw(line, 0, 2, PrimitiveType.Lines);
    }

    public static void DrawRectangle(Vector2f position, int width, int height, Color color)
    {
        RectangleShape rectangle = new(new Vector2f(width, height))
        {
            Position = position,
            FillColor = color
        };
        ActiveWindow!.Draw(rectangle);
    }

    public static void DrawRectangle(IntRect rect, Color color)
    {
        RectangleShape rectangle = new(new Vector2f(rect.Width, rect.Height))
        {
            Position = new Vector2f(rect.Left, rect.Top),
            FillColor = color
        };
        ActiveWindow!.Draw(rectangle);
    }

    public static void DrawRectOutline(FloatRect rect, int width, int height, Color color)
    {
        Vertex[] lines = new Vertex[8];
        Vector2f[] corners = new Vector2f[4]
        {
            new Vector2f(rect.Left, rect.Top),
            new Vector2f(rect.Left + width, rect.Top),
            new Vector2f(rect.Left + width, rect.Top + height),
            new Vector2f(rect.Left, rect.Top + height)
        };

        // Set vertex positions and color for the top and bottom lines
        for (int i = 0; i < 4; i++)
        {
            lines[i * 2].Position = corners[i];
            lines[i * 2].Color = color;
            lines[(i * 2) + 1].Position = corners[(i + 1) % 4];
            lines[(i * 2) + 1].Color = color;
        }

        // Draw the lines
        ActiveWindow!.Draw(lines, PrimitiveType.Lines);
    }
}