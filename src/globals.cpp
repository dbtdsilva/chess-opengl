#include "globals.hpp"

using namespace std;

/* Variaveis GLOBAIS !! */
projCoord proj;
int windowHandle;
/* O identificador do programa em GLSL combinando os SHADERS */
GLuint programaGLSL;
/* Os identificadores dos SHADERS */
GLuint vs;
GLuint fs;
/* Para passar coordenadas, cores a a matriz de transformacao ao Vertex-Shader */
GLint attribute_coord3d;
GLint attribute_normal3d;
/* Matriz de projeccao */
mat4x4 matrizProj;
/* Matriz global de transformacao */
mat4x4 matrizModelView;

string projectPath = "../src/";
Chess * chess;
LightModel * lights;
int selectedModel;
vector<GraphicModelChess> previewPositions;
vector<GraphicModelChess> secondaryModels;
vector<GraphicModelChess> pieceModels;