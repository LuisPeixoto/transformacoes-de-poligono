int selecionaVertice(int posicaoX, int posicaoY) {
  int i;
  float distancia; // distancia do clique do mouse ao vertice do poligno
  verticeSelecionado = -1;
  for (i = 0; i < quantidadeVertices; i++) { // percorre todos os vertices do poligno
    // calcula a distancia do clique do mouse ao vertice do poligno
    distancia = sqrt(pow((poligno[i].v[0] - posicaoX), 2.0) + pow((poligno[i].v[1] - posicaoY), 2.0));
    if (distancia < 3.0) { // se a distancia for menor que 3 pixels, o vertice eh selecionado
      verticeSelecionado = i; // seleciona o vertice
      break;
    }
  }
  return verticeSelecionado;
}

void CriaVertices(int botaoSelecionado, int estadoBotao, int posicaoX, int posicaoY)
{
  verticeSelecionado = -1;

  if (botaoSelecionado == GLUT_LEFT_BUTTON) {
    if (estadoBotao == GLUT_DOWN) {
      // Move referencia do mouse para o meio da tela
      posicaoX = posicaoX - windW;
      posicaoY = windH - posicaoY;

      if (jaPoligono == 0) {
        // cria um um vertice quando clica
        glPointSize(5); // define o tamanho do ponto
        poligno[quantidadeVertices].v[0] = (float)posicaoX; // define o x do ponto
        poligno[quantidadeVertices].v[1] = (float)posicaoY; // define o y do ponto
        quantidadeVertices++; // incrementa o numero de vertices
      }
      verticeSelecionado = selecionaVertice(posicaoX, posicaoY);
    }
  }
  glutPostRedisplay(); // redesenha a tela
}