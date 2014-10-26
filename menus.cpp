/*
 * menus.c
 *
 * Ficheiro de implementacao do modulo MENUS.
 *
 */


/* Incluir os ficheiros cabecalhos necessarios */

#include <stdlib.h>
#define GLEW_STATIC /* Necessario se houver problemas com a lib */
#include <GL/glew.h>
#include <GL/freeglut.h>
#include "consoleIO.h"
#include "globals.h"
#include "init.h"
#include "menus.h"
#include "models.h"

#include <string>
using namespace std;


/* ----------------------------------------------------------------------- */

/* Definicao dos menus e sub-menus usando um tipo auxiliar e arrays */

/* Ref.: "OpenGL: A Primer" - p. 219-220 */

typedef struct menuItemStruct
{
	string item; /* O texto do item */
	char  val;  /* O valor retornado */
} menuItemStruct;

/* Menu 1 - Botao Esquerdo */

static menuItemStruct menu1[] =
{

	{"Angulo Rota��o XX",     'x'},
	{"Angulo Rota��o YY",     'y'},
	{"Angulo Rota��o ZZ",     'z'},
	{"Translacao",            't'},
	{"Mudanca de Escala",     's'},
	{"-------------------",   '-'},
	{"Posicao ORIGINAL",      'o'},
	{"-------------------",   '-'},
	{"Proj. Paralela",        'O'},
	{"Proj. Perspectiva",     'P'},
	{"-------------------",   '-'},
	{"Anima��o ON / OFF",     'A'},
	{"-------------------",   '-'},
	{"BF Culling ON / OFF",   'B'}
};

int numItensMenu1 = sizeof(menu1) / sizeof(menuItemStruct);

/* Menu 2 - Botao Direito */

static menuItemStruct menu2[] =
{

	{"Ler Ficheiro",        'L'},
	{"-----------------",   '-'},
	{"Faces",               'F'},
	{"Arestas",             'A'},
	{"Vertices",            'V'},
	{"-----------------",   '-'},
	{"Sair",                '9'}
};

int numItensMenu2 = sizeof(menu2) / sizeof(menuItemStruct);


/* ----------------------------------------------------------------------- */

/* Callback function para o MENU 2 - Botao Direito */

static void myMenuEsq(int i)
{
	switch (menu1[i].val)
	{
	case 'x' :
		glutPostRedisplay();
		break;
	case 'y' :
		glutPostRedisplay();
		break;
	case 'z' :
		glutPostRedisplay();
		break;
	case 't' :
		parametrosTransl3D(&deslX, &deslY, &deslZ);
		glutPostRedisplay();
		break;
	case 's' :
		glutPostRedisplay();
		break;
	case 'o' :
		deslX = 0;
		deslY = 0;
		deslZ = -0.5;
		anguloRotXX = 0;
		anguloRotYY = 0;
		anguloRotZZ = 0;
		factorEscX = 0.25;
		factorEscY = 0.25;
		factorEscZ = 0.25;
		animacaoON = 0;
		glutPostRedisplay();
		break;
	case 'O' :
		matrizProj = IDENTITY_MATRIX;
		glutPostRedisplay();
		break;
	case 'P' :
		matrizProj = CreateProjectionMatrix(60, 1, 1, 50);
		/* Posicionar no interior do View Volome */
		Translate(&matrizProj, 0, 0, -5);
		glutPostRedisplay();
		break;
	case 'A' :
		if (animacaoON)
		{
			animacaoON = 0;
		}
		else
		{
			animacaoON = 1;
		}
		glutPostRedisplay();
		break;
	case 'B' :
		if (glIsEnabled(GL_CULL_FACE))
		{
			fprintf(stdout, "\n ** Back-Face Culling DISABLED ** \n");
			glDisable(GL_CULL_FACE);
		}
		else
		{
			fprintf(stdout, "\n ** Back-Face Culling ENABLED ** \n");
			glEnable(GL_CULL_FACE);
		}
		glutPostRedisplay();
		break;
	}
}

static void myMenuDir(int i)
{
	char nomeF[40];
	switch (menu2[i].val)
	{
	case 'L' :
		libertarArraysGlobais();
		nomeFicheiro(nomeF);
		lerVerticesDeFicheiro(nomeF, &numVertices, &arrayVertices);
		/* Determinar as normais unitarias a cada triangulo */
		arrayNormais = calcularNormaisTriangulos(numVertices, arrayVertices);
		/* Array vazio para guardar a cor atribuida a cada vertice */
		arrayCores = (GLfloat *) calloc(3 * numVertices, sizeof(GLfloat));
		/* COMPLETAR */
		/* Estabelecer propriedades do material iniciais */
		/* Parametros das transformacoes */
		deslX = 0;
		deslY = 0;
		deslZ = -0.5;
		anguloRotXX = 0;
		anguloRotYY = 0;
		anguloRotZZ = 0;
		factorEscX = 0.25;
		factorEscY = 0.25;
		factorEscZ = 0.25;
		glutPostRedisplay();
		break;
	case 'F' :
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		glutPostRedisplay();
		break;
	case 'A' :
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		glutPostRedisplay();
		break;
	case 'V' :
		glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);
		glutPostRedisplay();
		break;
	case '9' :
		exit(EXIT_SUCCESS);
		break;
	}
}

/* Criar os menus */

void criarMenus(void)
{
	int i;
	/* MENU 1 */
	glutCreateMenu(myMenuEsq);
	for (i = 0; i < numItensMenu1; i++)
	{
		/* Os itens do menu e os valores devolvidos a funcao callback */
		glutAddMenuEntry(menu1[i].item.c_str(), i);
	}
	/* O botao do rato associado */
	glutAttachMenu(GLUT_LEFT_BUTTON);
	/* MENU 2 */
	glutCreateMenu(myMenuDir);
	for (i = 0; i < numItensMenu2; i++)
	{
		/* Os itens do menu e os valores devolvidos a funcao callback */
		glutAddMenuEntry(menu2[i].item.c_str(), i);
	}
	/* O botao do rato associado */
	glutAttachMenu(GLUT_RIGHT_BUTTON);
}

