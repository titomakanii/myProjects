// MultiMediaTechnology / FHS | MultiMediaProjekt 1  | van Renen Nicolas

using SFML.Audio;
using SFML.Graphics;
using System;

namespace Shiftee;

internal static class AssetManager
{
    public static readonly Dictionary<string, Texture> Textures = new();
    public static readonly Dictionary<string, Sound> Sounds = new();
    public static readonly Dictionary<string, Music> Music = new();
    public static readonly Dictionary<string, Font> Fonts = new();

    public static void LoadTexture(string name, string fileName)
    {
        if (Textures.ContainsKey(name))
            return;

        var texture = new Texture(fileName);
        Textures.Add(name, texture);
    }

    public static void LoadSound(string name, string fileName)
    {
        if (Sounds.ContainsKey(name))
            return;

        var sound = new SoundBuffer(fileName);
        Sounds.Add(name, new Sound(sound));
    }

    public static void LoadMusic(string name, string fileName)
    {
        if (Music.ContainsKey(name))
            return;

        var music = new Music(fileName);
        Music.Add(name, music);
    }

    public static void LoadFont(string name, string fileName)
    {
        if (Fonts.ContainsKey(name))
            return;

        var font = new Font(fileName);
        Fonts.Add(name, font);
    }
}