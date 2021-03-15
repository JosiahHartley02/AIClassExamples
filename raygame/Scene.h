#pragma once
#include "Actor.h"

class Player;
class Scene
{
public:
    Scene();

    bool getStarted() { return m_started; }

    MathLibrary::Matrix3* getWorld();

    void addActor(Actor* actor);
    bool removeActor(int index);

    MathLibrary::Vector2 getCameraPosition() { return m_cameraPosition; };
    void setCameraPosition(MathLibrary::Vector2 position) { m_cameraPosition = position; };

    bool removeActor(Actor* actor);

    virtual void start();

    virtual void checkCollision();

    virtual void update(float deltaTime);

    virtual void draw();

    virtual void debug();

    virtual void end();

    static void destroy(Actor* actor);

    Scene* getThisScene() { return m_thisScene; }
    void setThisScene(Scene* scene) { m_thisScene = scene; }

private:
    Actor** m_actors;
    MathLibrary::Matrix3* m_world;
    bool m_started;
    int m_actorCount;
    MathLibrary::Vector2 m_cameraPosition;
    Scene* m_thisScene;
};

