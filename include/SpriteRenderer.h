#ifndef SPRITE_RENDERER_H
#define SPRITE_RENDERER_H
#include "Component.h"
#include "Sprite.h"
using namespace std;

class SpriteRenderer : public Component {
    private:
        Sprite sprite;

    public:
        SpriteRenderer(GameObject& associated);
        SpriteRenderer(GameObject& associated, string file, int frameCountW = 1, int frameCountH = 1);
    
        void Open(string file);
        void SetFrameCount(int frameCountW, int frameCountH);
        void SetFrame(int frame);
        void Update(float dt) override;
        void Render() override;
        bool Is(string type) override;
};

#endif