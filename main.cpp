#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <GL/glut.h>

#include "./include/global.h"
#include "./include/grafico.h"
#include "./include/inicializa.h"
#include "./include/menu.h"
#include "./include/operacoes.h"
#include "./include/transformacoes.h"
#include "./include/vertices.h"

void EscolheTransformacoes(int x, int y)
{
	int i;
	float dx, dy;
	if (gVert > -1) {
		x = x - windW;
		y = windH - y;
		dx = x - pvertex[gVert].v[0];
		dy = y - pvertex[gVert].v[1];
		switch (gOpera) {
		case 4:
			translacao(dx, dy);
			break;
		case 5:
			rotacao(dx, dy);
			break;
		case 6:
			escala(dx, dy);
			break;
		case 7:
			cisalha(dx, dy);
			break;
		case 8 ... 10:
			espelho(gOpera == 8 ? matrizReflexaoX : (
				gOpera == 9 ? matrizReflexaoY : matrizReflexaoOrigem), dx, dy);
			break;
		}
		desenhaTela();
	}
}

int main(int argc, char** argv)
{
	GLenum type;

	glutInit(&argc, argv);
	Args(argc, argv);

	type = GLUT_RGB;
	type |= (doubleBuffer) ? GLUT_DOUBLE : GLUT_SINGLE;

	glutInitDisplayMode(type);
	glutInitWindowSize(600, 500);
	glutCreateWindow("Transformacoes");

	inicializar();

	glutReshapeFunc(Reshape);
	glutKeyboardFunc(Key);
	glutDisplayFunc(desenhaTela);

	glutMotionFunc(EscolheTransformacoes);
	glutMouseFunc(CriaVertices);

	criaMenu();

	glutMainLoop();

	return (0);
}
