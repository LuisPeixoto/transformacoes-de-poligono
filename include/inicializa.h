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