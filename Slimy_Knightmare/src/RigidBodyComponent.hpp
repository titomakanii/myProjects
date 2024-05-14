#pragma once

#include "IComponent.hpp"

#include <Box2D/box2d.h>

namespace mmt_gd
{


class RigidBodyComponent : public IComponent
{
public:
    RigidBodyComponent(GameObject& gameObject, b2BodyType type);
    ~RigidBodyComponent() override;


    void addVelocity(const sf::Vector2f& velocity) const;
    sf::Vector2f getVelocity() const;

    sf::Vector2f getPosition() const;
    void         setPosition(const sf::Vector2f& position);

    bool init() override
    {
        return true;
    }

    void update(float deltaTime) override{};

    void physicsUpdate(float deltaTime);


    b2Body* getB2Body() const;


private:
    b2Body* m_body;
};
} // namespace mmt_gd
