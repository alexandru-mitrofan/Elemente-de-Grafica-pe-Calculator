#pragma once

#include "components/simple_scene.h"
#include "components/text_renderer.h"

namespace m1
{
    class Tema1 : public gfxc::SimpleScene
    {
     public:
        Tema1();
        ~Tema1();

        void Init() override;

     private:
        void FrameStart() override;
        void Update(float deltaTimeSeconds) override;
        void FrameEnd() override;

        void OnInputUpdate(float deltaTime, int mods) override;
        void OnKeyPress(int key, int mods) override;
        void OnKeyRelease(int key, int mods) override;
        void OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY) override;
        void OnMouseBtnPress(int mouseX, int mouseY, int button, int mods) override;
        void OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods) override;
        void OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY) override;
        void OnWindowResize(int width, int height) override;

     protected:
        float cx, cy;
        glm::mat3 modelMatrix;
        float translateX, translateY;
        float scaleX, scaleY;
        float angularStep;
        float x1,y1;
        int flagx;
        int flagy;
        int flag3;
        float x3,y3;
        float prex1,prey1;
        float vitezax,vitezay;
        int semnaripa;
        int onMouse;
        int incx,incy;
        float incdelta;
        float unghix,unghiy;
        float secBirdOnScreen;
        int nlives;
        int i;
        int nbullets;
        int points;
        int moarte;
        float vitezatotala;
        int nivel;
        float acceleratie;
        gfxc::TextRenderer* tr;
        float timp;
        int flagnivel;


    };
}   // namespace m1
