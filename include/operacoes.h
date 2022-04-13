void calculaCentro(float cc[])
{
  int i;

  // pega os pontos dos vertices e divide pela quantidade de vertices para calcular o centro

  cc[0] = cc[1] = cc[2] = 0.0f;
  for (i = 0; i < quantidadeVertices; i++)
  {
    cc[0] += poligno[i].v[0];
    cc[1] += poligno[i].v[1];
    cc[2] += poligno[i].v[2];
  }
  cc[0] /= quantidadeVertices;
  cc[1] /= quantidadeVertices;
  cc[2] /= quantidadeVertices;
}

void transladaCentro(int t)
{
  int i;
  // Move o poligono para o centro e depois move para a posição original
  // mover para o centro quando t => -1
  // move devolta quando t => 1

  // translada para centro
  for (i = 0; i < quantidadeVertices; i++)
  {                                               // percorre todos os vertices do poligno
    poligno[i].v[0] += (t * centroDoPoligono[0]); // translada o x do vertice para o centro do poligno
    poligno[i].v[1] += (t * centroDoPoligono[1]); // translada o y do vertice para o centro do poligno
  }
}

void multiplicaMatrizVetor(float v[])
{
  float temp[3];
  int i, j;
  // temp = Matriz x vetor
  for (i = 0; i < 3; i++)
  {
    temp[i] = 0.0f;
    for (j = 0; j < 3; j++)
    {
      temp[i] += v[j] * Matriz[i][j];
    }
  }

  for (i = 0; i < 3; i++)
  {
    v[i] = temp[i];
  }

  // copia vetor resultando no vetor original
}
