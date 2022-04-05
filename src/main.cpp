#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <GL/glut.h>

#define MAXVERTEXS 30
#define PHI 3.141572
#define ZERO 0.00001;

GLenum doubleBuffer;

struct polygon {
	float v[3];
} pvertex[MAXVERTEXS];

int windW, windH;
int cc;
int gOpera = 0;
int tipoPoligono;
int gVert = -1;
float gCen[3];
float gAng = 0.0f;

int nVertices = 0;
int jaPoligono = 0;

int matrizReflexaoX[2][2] = { { 1, 0 }, { 0, -1 } };
int matrizReflexaoY[2][2] = { { -1, 0 }, { 0, 1 } };
int matrizReflexaoOrigem[2][2] = { { 0, 1 }, { 1, 0 } };
int matrizReflexaoZ[2][2] = { { -1, 0 }, { 0, -1 } };

void circulo(float r, float ang, float pp[3])
{
	pp[0] = (float)(r * cos(ang));
	pp[1] = (float)(r * sin(ang));
	pp[2] = (float)0.0;
}

int clipVertex(int x, int y)
{
	int i;
	float d;
	gVert = -1;
	for (i = 0; i < nVertices; i++) {
		d = sqrt(pow((pvertex[i].v[0] - x), 2.0) + pow((pvertex[i].v[1] - y), 2.0));
		if (d < 3.0) {
			gVert = i;
			break;
		}
	}
	return gVert;
}

void inicializar(void)
{
	int i;
	//	float ang;
	cc = 1;
	jaPoligono = 0;
	nVertices = 0; // zero pontos
	tipoPoligono = GL_POINTS;
	// tipoPoligono = GL_LINE;

	for (i = 0; i < MAXVERTEXS; i++) {
		pvertex[i].v[0] = 0.0f;
		pvertex[i].v[1] = 0.0f;
		pvertex[i].v[2] = 0.0f;
	}

	// calcula o angulo básico de rotacao 
	gAng = (2.0f * PHI) / 180.0f;
}

static void Reshape(int width, int height)
{
	windW = width / 2;
	windH = height / 2;

	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	//    gluPerspective(60.0, 1.0, 0.1, 1000.0);
	gluOrtho2D(-windW, windW, -windH, windH);

	glMatrixMode(GL_MODELVIEW);
}

static void Key(unsigned char key, int x, int y)
{
	switch (key) {
	case 27:
		exit(0);
	}
}

void desenhaEixos(void)
{
	glLineWidth(1);

	glColor3f(1.0, 0.0, 0.0);

	// vertical line

	glBegin(GL_LINE_STRIP);
	glVertex2f(-windW, 0);
	glVertex2f(windW, 0);
	glEnd();

	// horizontal line

	glBegin(GL_LINE_STRIP);
	glVertex2f(0, -windH);
	glVertex2f(0, windH);
	glEnd();
}

void desenhaPoligno(void)
{
	int i;

	glColor3f(0.0, 0.0, 0.0);

	glPolygonMode(GL_FRONT_AND_BACK, tipoPoligono);

	glBegin(tipoPoligono);
	for (i = 0; i < nVertices; i++) {
		glVertex2fv(pvertex[i].v);
	}
	glEnd();
}

static void desenhaTela(void)
{
	glClearColor(1.0, 1.0, 1.0, 0.0);
	glClear(GL_COLOR_BUFFER_BIT);

	desenhaEixos();

	desenhaPoligno();

	if (gVert > -1) {
		glColor3f(1.0, 0.0, 0.0);
		glPointSize(3);
		glBegin(GL_POINTS);
		glVertex2fv(pvertex[gVert].v);
		glEnd();
	}

	if (doubleBuffer) {
		glutSwapBuffers();
	}
	else {
		glFlush();
	}
}

static void Args(int argc, char** argv)
{
	GLint i;

	doubleBuffer = GL_FALSE;

	for (i = 1; i < argc; i++) {
		if (strcmp(argv[i], "-sb") == 0) {
			doubleBuffer = GL_FALSE;
		}
		else if (strcmp(argv[i], "-db") == 0) {
			doubleBuffer = GL_TRUE;
		}
	}
}

/////////////// MENU //////////////////

void selecionaOpcaoMenu(int option)
{
	switch (option) {
	case 1:
		tipoPoligono = tipoPoligono == GL_POINTS ? GL_FILL : GL_LINE;
		break;
	case 2:
		inicializar();
		break;
	case 3:
		tipoPoligono = GL_LINE_LOOP;
		jaPoligono = 1;
		break;
	case 4 ... 10:
		gOpera = option;
		break;
	}
	glutPostRedisplay();
}

void criaMenu()
{
	int menu;

	menu = glutCreateMenu(selecionaOpcaoMenu);
	glutAddMenuEntry("Pontos", 1);
	glutAddMenuEntry("Limpar", 2);
	glutAddMenuEntry("Gerar poligno", 3);
	glutAddMenuEntry("Translacao", 4);
	glutAddMenuEntry("Rotacao", 5);
	glutAddMenuEntry("Escalar", 6);
	glutAddMenuEntry("Cisalha", 7);
	glutAddMenuEntry("EspelhoX", 8);
	glutAddMenuEntry("EspelhoY", 9);
	glutAddMenuEntry("EspelhoOrigem", 10);

	glutAttachMenu(GLUT_RIGHT_BUTTON);
}



///////////// OPERAÇÕES /////////////////

void calCentro(void)
{
	int i;
	// computando o centroide
	gCen[0] = gCen[1] = 0.0f;
	for (i = 0; i < nVertices; i++) {
		gCen[0] += pvertex[i].v[0];
		gCen[1] += pvertex[i].v[1];
	}
	gCen[0] /= nVertices;
	gCen[1] /= nVertices;
}

void translaCentro(int t)
{
	int i;
	// translada para centro
	for (i = 0; i < nVertices; i++) {
		pvertex[i].v[0] += (t * gCen[0]);
		pvertex[i].v[1] += (t * gCen[1]);
	}
}

////////////// TRANSFORMAÇÕES //////////////

void translacao(float dx, float dy)
{
	int i;
	for (i = 0; i < nVertices; i++) {
		pvertex[i].v[0] += dx;
		pvertex[i].v[1] += dy;
	}
}

void rotacao(float dx, float dy)
{
	int i;
	float oo, teta, xy[3];

	// calculo do angulo
	// seja vetor do centro para o vertice: vv
	// dd = (dx, dy) ? o vetor deslocalmento do mouse
	// o = vv x dd  (produto vetorial)
	// se o positivo ==> rota antihorario;
	// se o negativo ==> rota horario

	calCentro();
	translaCentro(-1);

	// determinando o angulo
	oo = pvertex[gVert].v[1] * dx - pvertex[gVert].v[0] * dy;

	teta = gAng;
	if (oo > 0.0f)
		teta = -1.0f * gAng;

	// rota em teta para lado oo
	for (i = 0; i < nVertices; i++) {
		xy[0] = pvertex[i].v[0];
		xy[1] = pvertex[i].v[1];
		pvertex[i].v[0] = xy[0] * cos(teta) - xy[1] * sin(teta);
		pvertex[i].v[1] = xy[0] * sin(teta) + xy[1] * cos(teta);
	}
	translaCentro(1);
}

void  espelho(int matrizReflexao[2][2])
{
	int i;
	float xy[3];

	// calculo do angulo
	// seja vetor do centro para o vertice: vv
	// dd = (dx, dy) ? o vetor deslocalmento do mouse
	// o = vv x dd  (produto vetorial)
	// se o positivo ==> rota antihorario;
	// se o negativo ==> rota horario

	calCentro();
	translaCentro(-1);

	// determinando o angulo


	// rota em teta para lado oo
	for (i = 0; i < nVertices; i++) {
		xy[0] = pvertex[i].v[0];
		xy[1] = pvertex[i].v[1];
		pvertex[i].v[0] = (xy[0] * matrizReflexao[0][0]) + (xy[1] * matrizReflexao[0][1]);
		pvertex[i].v[1] = (xy[0] * matrizReflexao[1][0]) + (xy[1] * matrizReflexao[1][1]);
	}
	translaCentro(1);
}

void escala(float dx, float dy)
{
	int i;
	float sx, sy;

	calCentro();
	translaCentro(-1);
	// scalando...

	sx = sy = 1.0f;
	if (fabs(pvertex[gVert].v[0]) > 0.01f)
		sx = 1.0f + dx / pvertex[gVert].v[0];
	if (fabs(pvertex[gVert].v[1]) > 0.01f)
		sy = 1.0f + dy / pvertex[gVert].v[1];

	for (i = 0; i < nVertices; i++) {
		pvertex[i].v[0] *= sx;
		pvertex[i].v[1] *= sy;
	}

	translaCentro(1);
}

void cisalha(float dx, float dy)
{
	int i;
	float sx, sy, xy[3];

	sx = 0.00000001f * dx;
	sy = 0.00000001f * dy;
	if (fabs(pvertex[gVert].v[0]) > 0.1f)
		sx = dx / pvertex[gVert].v[0];
	if (fabs(pvertex[gVert].v[1]) > 0.1f)
		sy = dy / pvertex[gVert].v[1];

	calCentro();
	translaCentro(-1);

	// rota em teta para lado oo
	for (i = 0; i < nVertices; i++) {
		xy[0] = pvertex[i].v[0];
		xy[1] = pvertex[i].v[1];
		pvertex[i].v[0] = xy[0] + (xy[1] / 2) * sx;
		pvertex[i].v[1] = xy[1] + (xy[0] / 2) * sy;
	}

	translaCentro(1);
}

void motion(int x, int y)
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
				gOpera == 9 ? matrizReflexaoY : matrizReflexaoOrigem));
			break;
		}
		desenhaTela();
	}
}

void mouse(int button, int state, int x, int y)
{

	if (state == GLUT_UP) {
		printf("\n jaPoligono %d ", jaPoligono);
		if (button == GLUT_LEFT_BUTTON) {

			if (jaPoligono == 0) {
				x = x - windW;
				y = windH - y;
				glPointSize(3);
				pvertex[nVertices].v[0] = (float)x;
				pvertex[nVertices].v[1] = (float)y;
				nVertices++;
				gVert = clipVertex(x, y); // mostrar o ponto vermelho
			}
		}

		else if (button == GLUT_RIGHT_BUTTON) {
			if (nVertices > 0) {
				jaPoligono = 1;
				tipoPoligono = GL_LINE;
			}
		}
	}
	glutPostRedisplay();
}

int main(int argc, char** argv)
{
	GLenum type;

	glutinicializar(&argc, argv);
	Args(argc, argv);

	type = GLUT_RGB;
	type |= (doubleBuffer) ? GLUT_DOUBLE : GLUT_SINGLE;

	glutinicializarDisplayMode(type);
	glutinicializarWindowSize(600, 500);
	glutCreateWindow("Basic Program Using Glut and Gl");

	inicializar();

	glutReshapeFunc(Reshape);
	glutKeyboardFunc(Key);
	glutDisplayFunc(desenhaTela);

	glutMotionFunc(motion);
	glutMouseFunc(mouse);
	//	glutIdleFunc(idle);

	criaMenu();

	glutMainLoop();

	return (0);
}
