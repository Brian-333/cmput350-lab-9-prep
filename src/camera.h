#ifndef CAMERA_H
#define CAMERA_H

#include "vector_util.h"
#include <SFML/System.hpp>

class Camera {
public:
    Camera(const sf::Vector2f& windowSize, const sf::Vector2f& viewCenterWorld,
           float worldUnitsPerPixel = 1.f)
        : mWindowSize{windowSize},
          mViewCenterWorld{viewCenterWorld},
          mWorldUnitsPerPixel{worldUnitsPerPixel} {}

    // TODO: all of these:

    sf::Vector2f windowToWorld(const sf::Vector2f& pWindow) {
        return {
            (pWindow.x - mWindowSize.x / 2) * mWorldUnitsPerPixel + mViewCenterWorld.x,
            (pWindow.y - mWindowSize.y / 2) * mWorldUnitsPerPixel + mViewCenterWorld.y
        };
    };

    sf::Vector2f worldToWindow(const sf::Vector2f& pWorld) { 
        return {
            (pWorld.x - mViewCenterWorld.x) / mWorldUnitsPerPixel + mWindowSize.x / 2,
            (pWorld.y - mViewCenterWorld.y) / mWorldUnitsPerPixel + mWindowSize.y / 2
        };
     };

    sf::Vector2f windowPercentToWorld(const sf::Vector2f& pWindowPercent) { 
        return windowToWorld(sf::Vector2<float>(pWindowPercent) * sf::Vector2<float>(mWindowSize)); 
    };

    sf::Vector2f worldToWindowPercent(const sf::Vector2f& pWorld) { return worldToWindow(pWorld) / sf::Vector2<float>(mWindowSize); };

    void translateWorld(const sf::Vector2f& deltaWorld) { mViewCenterWorld += deltaWorld; };

    void translateWindow(const sf::Vector2f& deltaScreen) { mViewCenterWorld += {deltaScreen.x * mWorldUnitsPerPixel, deltaScreen.y * mWorldUnitsPerPixel}; };

    void translateWindowPercent(const sf::Vector2f& deltaScreenPercent) { translateWindow({deltaScreenPercent.x * mWindowSize.x, deltaScreenPercent.y * mWindowSize.y}); };

    void setCamera(const sf::Vector2f& pWorld, const sf::Vector2f& pWindow) {
        sf::Vector2f windowCenterInWorld = {
            (mWindowSize.x / 2 - pWindow.x) * mWorldUnitsPerPixel, 
            (mWindowSize.y / 2 - pWindow.y) * mWorldUnitsPerPixel
        };
        mViewCenterWorld = windowCenterInWorld + pWorld;
    };

    void setCameraPercent(const sf::Vector2f& pWorld, const sf::Vector2f& pWindowPercent) {
        setCamera(pWorld, sf::Vector2<float>(pWindowPercent) * sf::Vector2<float>(mWindowSize));
    };

    void setCameraCenter(const sf::Vector2f& pWorld) { mViewCenterWorld = pWorld; };

    sf::Vector2f getCameraCenter() const { return mViewCenterWorld; };

private:
    sf::Vector2f mWindowSize;       // size of the window in screen pixels (i.e. window coords)
    sf::Vector2f mViewCenterWorld;  // world coords point corresponding to the center of our window.
    float mWorldUnitsPerPixel;      // distance in world coords covered by one pixel
};

#endif  // CAMERA_H
