// MMP2 Project made by: Nicolas van Renen, Andrè Linder
#include "stdafx.h"
#include "PointsComponent.hpp"

namespace mmt_gd
{

PointsComponent::PointsComponent(GameObject& gameObject, int points) : IComponent(gameObject), m_points(points)
{
}

void PointsComponent::addPoints(int points)
{
    m_points += points;
}

int PointsComponent::getPoints() const
{
    return m_points;
}

bool PointsComponent::init()
{
    // Any initialization logic goes here
    return true;
}

void PointsComponent::update(float deltaTime)
{
    //physicsmanager is observer, in objectfactory abfangen
}
} // namespace mmt_gd
