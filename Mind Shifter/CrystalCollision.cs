// MultiMediaTechnology / FHS | MultiMediaProjekt 1  | van Renen Nicolas

using SFML.Graphics;
using SFML.System;
using SFML.Window;
using SFML.Audio;
using System.Collections.Generic;

namespace Shiftee
{
    public static class Collision
    {
        public static void CheckCrystalCollisions(Player player, List<Sprite> crystalsRed, List<Sprite> crystalsBlue, ref int score, ref int score2)
        {
            List<Sprite> crystalsRedToRemove = new();
            List<Sprite> crystalsBlueToRemove = new();

            foreach (Sprite crystalRed in crystalsRed)
            {
                if (CheckPlayerCrystalCollision(player, crystalRed))
                {
                    HandleCrystalCollision(crystalRed);
                    crystalsRedToRemove.Add(crystalRed);
                    score--;
                }
            }

            foreach (Sprite crystalBlue in crystalsBlue)
            {
                if (CheckPlayer2CrystalCollision(player, crystalBlue))
                {
                    HandleCrystalCollision(crystalBlue);
                    crystalsBlueToRemove.Add(crystalBlue);
                    score2--;
                }
            }

            RemoveCrystals(crystalsRed, crystalsRedToRemove);
            RemoveCrystals(crystalsBlue, crystalsBlueToRemove);
        }

        private static bool CheckPlayerCrystalCollision(Player player, Sprite crystal)
        {
            return player.GetBounds().Intersects(crystal.GetGlobalBounds());
        }

        private static bool CheckPlayer2CrystalCollision(Player player2, Sprite crystal)
        {
            return player2.sprite2!.GetGlobalBounds().Intersects(crystal.GetGlobalBounds());
        }

        private static void HandleCrystalCollision(Sprite crystal)
        {
            AssetManager.LoadSound("crystal", @".\Assets\crystal.wav");
            AssetManager.Sounds["crystal"].Play();
        }

        private static void RemoveCrystals(List<Sprite> crystalList, List<Sprite> crystalsToRemove)
        {
            foreach (Sprite crystal in crystalsToRemove)
            {
                crystalList.Remove(crystal);
                HandleCrystalCollision(crystal);
            }
        }
    }
}
