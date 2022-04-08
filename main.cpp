#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <GL/glut.h>

#include "./include/global.h"
#include "./include/grafico.h"
#include "./include/matriz.h"
#include "./include/inicializa.h"
#include "./include/menu.h"
#include "./include/operacoes.h"
#include "./include/transformacoes.h"
#include "./include/vertices.h"

void EscolheTransformacoes(int posicaoX, int posicaoY)
// Funcao acionada quando o usuario escolhe um vertice para realizar a transformacao
{ // x e y posicao do mouse
	float distanciaVerticeEixoX, distanciaVerticeEixoY;

	if (verticeSelecionado > -1) {

		// Move referencia do mouse para o meio da tela
		posicaoX = posicaoX - windW;
		posicaoY = windH - posicaoY;

		// calcula a distancia do vertice selecionado do mouse no eixo X e Y
		distanciaVerticeEixoX = posicaoX - poligno[verticeSelecionado].v[0];
		distanciaVerticeEixoY = posicaoY - poligno[verticeSelecionado].v[1];

		// seleciona a transformacao a ser aplicada
		switch (transformacaoEscolhida) {
		case 4:
			translacao(distanciaVerticeEixoX, distanciaVerticeEixoY);
			break;
		case 5:
			rotacao(distanciaVerticeEixoX, distanciaVerticeEixoY);
			break;
		case 6:
			escala(distanciaVerticeEixoX, distanciaVerticeEixoY);
			break;
		case 7:
			cisalha(distanciaVerticeEixoX, distanciaVerticeEixoY);
			break;
		case 8 ... 10:
			espelho(transformacaoEscolhida == 8 ? matrizReflexaoX : (
				transformacaoEscolhida == 9 ? matrizReflexaoY : matrizReflexaoOrigem), distanciaVerticeEixoX, distanciaVerticeEixoY);
			break;
		}
		Desenha();
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

	// Defini o tamanho da janela
	glutInitWindowSize(600, 500);

	// inicializa a janela
	glutCreateWindow("Transformacoes");

	inicializar();

	glutReshapeFunc(Reshape);
	glutKeyboardFunc(Key);
	glutDisplayFunc(Desenha);

	// Funcao usada quando o usuario escolhe um vertice para realizar a transformacao
	glutMotionFunc(EscolheTransformacoes);

	glutMouseFunc(CriaVertices);

	criaMenu();

	glutMainLoop();

	return (0);
}
