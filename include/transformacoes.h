
void translacao(float distanciaVerticeEixoX, float distanciaVerticeEixoY)
{
  int i;
  criarMatrizIndentidade(3, 3);

  Matriz[0][2] = distanciaVerticeEixoX;
  Matriz[1][2] = distanciaVerticeEixoY;

  for (i = 0; i < quantidadeVertices; i++)
  {
    // multipla os vertices pela matriz de translacao
    multiplicaMatrizVetor(poligno[i].v);
  }
}

void rotacao(float distanciaVerticeEixoX, float distanciaVerticeEixoY)
{
  int i;
  float oo, teta, xy[3];

  calculaCentro(xy);
  translacao(-1 * xy[0], -1 * xy[1]); // desloca o centro para o centro

  // determinando o angulo
  oo = poligno[verticeSelecionado].v[1] * distanciaVerticeEixoX - poligno[verticeSelecionado].v[0] * distanciaVerticeEixoY;

  teta = angulo;

  // mudar o sentido da rotacao
  if (oo > 0.0f)
    teta = -1.0f * angulo;

  criarMatrizIndentidade(3, 3);
  Matriz[0][0] = cos(teta);
  Matriz[0][1] = -sin(teta);
  Matriz[1][0] = sin(teta);
  Matriz[1][1] = cos(teta);

  for (i = 0; i < quantidadeVertices; i++)
  {
    multiplicaMatrizVetor(poligno[i].v);
  }
  translacao(xy[0], xy[1]); // desloca para o centro do poligno de volta

  // rota em teta para lado oo
}

void espelho(int matrizReflexao[2][2], float distanciaVerticeEixoX, float distanciaVerticeEixoY)
{
  int i;
  float xy[3];

  criarMatrizIndentidade(3, 3);

  Matriz[0][0] = matrizReflexao[0][0];
  Matriz[0][1] = matrizReflexao[0][1];
  Matriz[1][0] = matrizReflexao[1][0];
  Matriz[1][1] = matrizReflexao[1][1];

  calculaCentro(xy);
  // transladaCentro(-1);

  for (i = 0; i < quantidadeVertices; i++)
  {
    multiplicaMatrizVetor(poligno[i].v);
  }
}

void escala(float distanciaVerticeEixoX, float distanciaVerticeEixoY)
{
  int i;
  float sx, sy, xy[3];

  calculaCentro(xy);
  transladaCentro(-1); // desloca o centro para o centro
  // scalando...

  sx = sy = 1.0f;
  if (fabs(poligno[verticeSelecionado].v[0]) > 0.01f) // se o eixo x for maior que 0.01
    sx += distanciaVerticeEixoX / poligno[verticeSelecionado].v[0];
  if (fabs(poligno[verticeSelecionado].v[1]) > 0.01f) // se o eixo y for maior que 0.01
    sy += distanciaVerticeEixoY / poligno[verticeSelecionado].v[1];

  // criarMatrizIndentidade(3, 3);
  Matriz[0][0] = sx;
  Matriz[1][1] = sy;

  for (i = 0; i < quantidadeVertices; i++)
  {
    multiplicaMatrizVetor(poligno[i].v);
  }
  translacao(xy[0], xy[1]);
}

void cisalha(float distanciaVerticeEixoX, float distanciaVerticeEixoY)
{
  int i;
  float sx, sy, xy[3];

  transladaCentro(-1);
  sx = 0.00000001f * distanciaVerticeEixoX; // sensibilidade de cisalhamento
  sy = 0.00000001f * distanciaVerticeEixoY; // sensibilidade de cisalhamento
  if (distanciaVerticeEixoX > distanciaVerticeEixoY)
  {
    if (fabs(poligno[verticeSelecionado].v[0]) > 0.1f)
      sx += distanciaVerticeEixoX / poligno[verticeSelecionado].v[0];
  }
  else
  {
    if (fabs(poligno[verticeSelecionado].v[1]) > 0.1f)
      sy += distanciaVerticeEixoY / poligno[verticeSelecionado].v[1];
  }

  calculaCentro(xy);
  translacao(-1 * xy[0], -1 * xy[1]); // desloca o centro para o centro

  criarMatrizIndentidade(3, 3);
  Matriz[1][0] = sx;
  Matriz[0][1] = sy;

  for (i = 0; i < quantidadeVertices; i++)
  {
    multiplicaMatrizVetor(poligno[i].v);
  }

  translacao(xy[0], xy[1]); // desloca para o centro do poligno de volta
}
