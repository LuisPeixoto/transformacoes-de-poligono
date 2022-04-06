static void Reshape(int width, int height)
{
  windW = width / 2;
  windH = height / 2;

  glViewport(0, 0, width, height);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  //    gluPerspective(60.0, 1.0, 0.1, 1000.0);
  gluOrtho2D(-windW, windW, -windH, windH);

  glMatrixMode(GL_MODELVIEW);
}

void desenhaEixos(void)
{
  glLineWidth(1);

  glColor3f(1.0, 0.0, 0.0);

  // vertical line

  glBegin(GL_LINE_STRIP);
  glVertex2f(-windW, 0);
  glVertex2f(windW, 0);
  glEnd();

  // horizontal line

  glBegin(GL_LINE_STRIP);
  glVertex2f(0, -windH);
  glVertex2f(0, windH);
  glEnd();
}

void desenhaPoligno(void)
{
  int i;

  glColor3f(0.0, 0.0, 0.0);

  glPolygonMode(GL_FRONT_AND_BACK, tipoPoligono);

  glBegin(tipoPoligono);
  for (i = 0; i < nVertices; i++) {
    glVertex2fv(pvertex[i].v);
  }
  glEnd();
}

static void desenhaTela(void)
{
  glClearColor(1.0, 1.0, 1.0, 0.0);
  glClear(GL_COLOR_BUFFER_BIT);

  desenhaEixos();

  desenhaPoligno();

  if (gVert > -1) {
    glColor3f(1.0, 0.0, 0.0);
    glPointSize(3);
    glBegin(GL_POINTS);
    glVertex2fv(pvertex[gVert].v);
    glEnd();
  }

  if (doubleBuffer) {
    glutSwapBuffers();
  }
  else {
    glFlush();
  }
}