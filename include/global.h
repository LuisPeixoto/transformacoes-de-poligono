#define MAXVERTEXS 30
#define PHI 3.141572
#define ZERO 0.00001;

GLenum doubleBuffer;

struct polygon {
  float v[3];
} poligno[MAXVERTEXS];

int windW, windH;
int transformacaoEscolhida = 0;
int tipoPoligono;
int verticeSelecionado = -1;
float centroDoPoligono[3];
float angulo = 0.0f;
float Matriz[3][3];

int quantidadeVertices = 0;
int jaPoligono = 0;

int matrizReflexaoX[2][2] = { { 1, 0 }, { 0, -1 } };
int matrizReflexaoY[2][2] = { { -1, 0 }, { 0, 1 } };
int matrizReflexaoOrigem[2][2] = { { 0, 1 }, { 1, 0 } };
int matrizReflexaoZ[2][2] = { { -1, 0 }, { 0, -1 } };

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

static void Key(unsigned char key, int x, int y)
{
  switch (key) {
  case 27:
    exit(0);
  }
}
