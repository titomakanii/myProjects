#pragma once

#include "IComponent.hpp"

namespace mmt_gd
{

class PointsComponent : public IComponent
{
public:
    PointsComponent(GameObject& gameObject, int m_points);

    void addPoints(int points);

    int getPoints() const;

    bool init();

    void update(float deltaTime);

private:
    int m_points;
};

} // namespace mmt_gd
