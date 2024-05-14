// MultiMediaTechnology / FHS | MultiMediaProjekt 1  | van Renen Nicolas

using SFML.System;

namespace Shiftee;

internal static class Utils
{
    /// <summary>
    ///     returns the squared magnitude of a vector (length before square root)
    /// </summary>
    /// <returns>Length of input vector</returns>
    public static float SqrMagnitude(this Vector2f input)
    {
        var sqrLenght = (input.X * input.X) + (input.Y * input.Y);
        return sqrLenght;
    }

    /// <summary>
    ///     Rotates a vector by a given angle counterclockwise
    /// </summary>
    /// <param name="v">input vector</param>
    /// <param name="angle">angle in radians</param>
    /// <returns></returns>
    public static Vector2f
        RotateVector(Vector2f v, float angle) //counterclockwise by the given angle (angle in radians)
    {
        return new Vector2f(
            (v.X * MathF.Cos(angle)) - (v.Y * MathF.Sin(angle)),
            (v.X * MathF.Sin(angle)) + (v.Y * MathF.Cos(angle)));
    }

    /// <summary>
    ///     Returns the angle between two vectors.
    /// </summary>
    /// <returns>angle in radians</returns>
    public static float AngleBetween(Vector2f v1, Vector2f v2)
    {
        return MathF.Atan2(v2.Y - v1.Y, v2.X - v1.X);
    }

    /// <summary>
    ///     convert from radians to degrees
    /// </summary>
    /// <returns>degrees</returns>
    public static float ToDegrees(this float val)
    {
        return 180 / MathF.PI * val;
    }

    /// <summary>
    ///     convert from degrees to radians
    /// </summary>
    /// <returns>radians</returns>
    public static float ToRadians(this float val)
    {
        return MathF.PI / 180 * val;
    }

    /// <summary>
    ///     Distance between two points.
    /// </summary>
    /// <returns>distance</returns>
    public static float Distance(Vector2f a, Vector2f b)
    {
        return MathF.Sqrt(((a.X - b.X) * (a.X - b.X)) + ((a.Y - b.Y) * (a.Y - b.Y)));
    }

    /// <summary>
    ///     normalizes a vector to a length of 1
    /// </summary>
    /// <returns>normalized vector</returns>
    public static Vector2f Normalize(this Vector2f source)
    {
        var length = MathF.Sqrt((source.X * source.X) + (source.Y * source.Y));

        if (length != 0)
            return new Vector2f(source.X / length, source.Y / length);

        return source;
    }

    /// <summary>
    ///     Linear interpolation between two floats.
    /// </summary>
    /// <param name="firstFloat">start value</param>
    /// <param name="secondFloat">end value</param>
    /// <param name="t">interpolation between [0,1]</param>
    /// <param name="clamped">clamp the interpolation between 0 and 1</param>
    /// <returns>interpolated value</returns>
    public static float Lerp(this float firstFloat, float secondFloat, float t, bool clamped = true)
    {
        if (clamped)
            t = t > 1.0f ? 1.0f : t;

        return (firstFloat * (1 - t)) + (secondFloat * t);
    }

    /// <summary>
    ///     Linear interpolation between two vectors.
    /// </summary>
    /// <param name="firstVector">start direction or point</param>
    /// <param name="secondVector">end direction or point</param>
    /// <param name="t">interpolation between [0,1]</param>
    /// <returns>interpolated vector</returns>
    public static Vector2f Lerp(Vector2f firstVector, Vector2f secondVector, float t)
    {
        var x = Lerp(firstVector.X, secondVector.X, t);
        var y = Lerp(firstVector.Y, secondVector.Y, t);
        return new Vector2f(x, y);
    }

    /// <summary>
    ///     Returns the Dot-Product of two vectors.
    /// </summary>
    /// <returns>Dot Product</returns>
    public static float Dot(Vector2f lhs, Vector2f rhs)
    {
        var dotProduct = (lhs.X * rhs.X) + (lhs.Y * rhs.Y);
        return dotProduct;
    }
}