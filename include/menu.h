
void selecionaOpcaoMenu(int option)
{
  switch (option) {
  case 1: // desenha poligno
    tipoPoligono = tipoPoligono == GL_POINTS ? GL_FILL : GL_POINTS;
    jaPoligono = 0;
    break;
  case 2:
    inicializar();
    break;
  case 3:
    tipoPoligono = GL_LINE_LOOP;
    jaPoligono = 1;
    break;
  case 4 ... 10:
    transformacaoEscolhida = option;
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