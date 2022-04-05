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