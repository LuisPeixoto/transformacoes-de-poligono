
void translacao(float dx, float dy) {
  int i;
  for (i = 0; i < nVertices; i++) {
    pvertex[i].v[0] += dx;
    pvertex[i].v[1] += dy;
  }
}

void rotacao(float dx, float dy) {
  int i;
  float oo, teta, xy[3];

  // calculo do angulo
  // seja vetor do centro para o vertice: vv
  // dd = (dx, dy) ? o vetor deslocalmento do mouse
  // se o negativo ==> rota horario
  // o = vv x dd  (produto vetorial)
  // se o positivo ==> rota antihorario;

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

void  espelho(int matrizReflexao[2][2]) {
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

void escala(float dx, float dy) {
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
