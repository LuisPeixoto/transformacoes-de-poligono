void criarMatrizIndentidade(int QuantidadeDeLinhas, int QuantidadeDeColunas) {
  for (int i = 0; i < QuantidadeDeLinhas; i++) {
    for (int j = 0; j < QuantidadeDeColunas; j++) {
      if (i == j)
        Matriz[i][j] = 1;
      else
        Matriz[i][j] = 0;
    }
  }
}