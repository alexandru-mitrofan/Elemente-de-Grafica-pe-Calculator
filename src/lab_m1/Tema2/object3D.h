#pragma once

#include <string>

#include "core/gpu/mesh.h"
#include "utils/glm_utils.h"
#include "core/engine.h"
#include "utils/gl_utils.h"


namespace object3D
{

   Mesh* CreateRectangle(const std::string &name, glm::vec3 center, float height, float width,float depth, glm::vec3 color);
   Mesh* CreateMap(const std::string &name, glm::vec3 corner, float len, glm::vec3 color);
   Mesh* CreateLap(const std::string &name, glm::vec3 color);
   Mesh* CreateLine(const std::string &name, glm::vec3 color);
   glm::vec3 punctsus(glm::vec3 punct1, glm::vec3 punct2, float dist);
   glm::vec3 punctjos(glm::vec3 punct1, glm::vec3 punct2, float dist);
   Mesh* CreateLap1(const std::string &name,std::vector<glm::vec3>punctesus,std::vector<glm::vec3>punctejos, glm::vec3 color);
   int vercoliziune(std::vector<glm::vec3>combinate,glm::vec3 pozacum);
   float arietriunghi(glm::vec3 A,glm::vec3 B,glm::vec3 C);
   float unghivectori(glm::vec3 A1, glm::vec3 A2,glm::vec3 B1 ,glm::vec3 B2);
   std::vector<glm::vec3> impartetraseupuncte(std::vector<glm::vec3> traseunpc,int densitatepct,int nrpct);
   std::vector<float> unghiurinpc(std::vector<glm::vec3> traseunpc,int nrpct);
   Mesh* CreatetrTree(const std::string &name, glm::vec3 center, float height, float width ,float depth ,glm::vec3 colortrunchi,glm::vec3 colorsus) ;
   Mesh* CreateLap2(const std::string &name,std::vector<glm::vec3>punctesus,std::vector<glm::vec3>punctejos,int densitatepct,int nrpct, glm::vec3 color);
   int bummasina(glm::vec3 masina1,glm::vec3 masina2);
}
