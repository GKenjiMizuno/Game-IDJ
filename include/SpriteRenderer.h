#ifndef SPRITE_RENDERER_H
#define SPRITE_RENDERER_H
#include "Component.h"
#include "Sprite.h"
using namespace std;

class SpriteRenderer : public Component {
    private:
        Sprite sprite;
        bool cameraFollower = false;
    public:
        SpriteRenderer(GameObject& associated);
        SpriteRenderer(GameObject& associated, string file, int frameCountW = 1, int frameCountH = 1);
    
        void Open(string file);
        void SetFrameCount(int frameCountW, int frameCountH);
        void SetFrame(int frame);
        void SetCameraFollower(bool enabled);
        bool IsCameraFollower();  
        void Update(float dt) override;
        void Render() override;
        bool Is(string type) override;
        bool IsOpen();
};

#endif