void inicializar(void)
{
  int i;
  jaPoligono = 0;
  quantidadeVertices = 0; // zero pontos
  tipoPoligono = GL_POINTS;

  for (i = 0; i < MAXVERTEXS; i++) {
    poligno[i].v[0] = 0.0f;
    poligno[i].v[1] = 0.0f;
    poligno[i].v[2] = 1;
  }

  // calcula o angulo básico de rotacao 
  angulo = (2.0f * PHI) / 180.0f;
}