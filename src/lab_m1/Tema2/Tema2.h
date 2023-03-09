#pragma once

#include "components/simple_scene.h"
#include "lab_m1/Tema2/lab_camera.h"

namespace m1
{
    class Tema2 : public gfxc::SimpleScene
    {
     public:
        struct ViewportArea
        {
            ViewportArea() : x(0), y(0), width(1), height(1) {}
            ViewportArea(int x, int y, int width, int height)
                : x(x), y(y), width(width), height(height) {}
            int x;
            int y;
            int width;
            int height;
        };

        Tema2();
        ~Tema2();

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
        void RenderMesh1(Mesh * mesh, Shader * shader, const glm::mat4 & modelMatrix);
        void RenderSimpleMesh(Mesh *mesh, Shader *shader, const glm::mat4 & modelMatrix);

        void RenderScene();
        void RenderSimpleScene();
     protected:
        implemented::Camera1 *camera;
        glm::mat4 modelMatrix;
        float translateX, translateY, translateZ;
        float scaleX, scaleY, scaleZ;
        float angularStepOX, angularStepOY, angularStepOZ;
        GLenum polygonMode;
        ViewportArea miniViewportArea;
        glm::vec3 playercar = glm::vec3(-6.5, 0, 1);
        glm::vec3 helpercoliz;
        glm::vec3 carOrientation;
        float carAngle = 0.0;
        int flagdir;
        std::vector<glm::vec3> combinate;
        glm::vec3 centernpc1 = glm::vec3(0,0,0);
        int densitatepct = 100;
        int nrpct = 15;


        //pt npcccc
        std::vector<float> unghinpc1;
        std::vector<glm::vec3> traseunpc1;
        int npc1cont =  0;

        std::vector<float> unghinpc2;
        std::vector<glm::vec3> traseunpc2;
        int npc2cont =  300;

        std::vector<float> unghinpc3;
        std::vector<glm::vec3> traseunpc3;
        int npc3cont =  800;

        std::vector<glm::vec3> copacisus;
        std::vector<glm::vec3> copacijos;
        glm::mat4 projectionMatrix;
        glm::mat4 projectionMatrix1;
        int location;
        float fscalare = 0.02;
        std::vector<glm::vec3> npcsus;
        std::vector<glm::vec3> npcjos;

        
    };
}   // namespace m1

