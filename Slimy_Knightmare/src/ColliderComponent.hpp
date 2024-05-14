#pragma once
#include "IComponent.hpp"
#include "RigidBodyComponent.hpp"

#include <Box2D/Box2D.h>
#include <functional>
#include <list>

namespace mmt_gd
{


class ColliderComponent : public IComponent
{
public:
    /// \param collider1 the collider for which OnCollision was called.
    /// \param collider2 the collider with which the collision happened.
    using OnCollisionFunction = std::function<void(ColliderComponent&, ColliderComponent&)>;

    /// \param body the rigid body the collider is attached to.
    /// \param rect the size of the AABB in pixel
    ColliderComponent(GameObject& gameObject, RigidBodyComponent& body, b2FixtureDef& def);

    bool init() override
    {
        return true;
    }
    virtual void update(float fDeltaTime) override;
    /// Add delegate function to be executed when collision is detected.
    /// Signature: void func(ColliderComponent&)
    void registerOnCollisionFunction(const OnCollisionFunction& func);

    /// Method called when collision occured. Method calls all subscribed
    /// OnCollisionFunctions
    ///
    /// \param collider collision occured with this collider
    void                onCollision(ColliderComponent& collider);
    RigidBodyComponent& getBody() const
    {
        return m_body;
    }
    b2Fixture* getFixture()
    {
        return m_fixture; // Assuming m_fixture is a member variable of type b2Fixture*
    }

private:
    RigidBodyComponent&            m_body;
    b2Fixture*                     m_fixture;
    std::list<OnCollisionFunction> m_onCollisionFunctions;
};
} // namespace mmt_gd
