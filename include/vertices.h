int clipVertex(int x, int y) {
  printf("%d %d\n", x, y);
  int i;
  float d;
  gVert = -1;
  for (i = 0; i < nVertices; i++) {
    d = sqrt(pow((pvertex[i].v[0] - x), 2.0) + pow((pvertex[i].v[1] - y), 2.0));
    if (d < 3.0) {
      gVert = i;
      break;
    }
  }
  return gVert;
}

void CriaVertices(int button, int state, int x, int y)
{
  gVert = -1;

  if (button == GLUT_LEFT_BUTTON) {
    if (state == GLUT_DOWN) {
      x = x - windW;
      y = windH - y;
      if (jaPoligono == 0) {
        glPointSize(3);
        pvertex[nVertices].v[0] = (float)x;
        pvertex[nVertices].v[1] = (float)y;
        nVertices++;
      }
      gVert = clipVertex(x, y);
    }
  }
  glutPostRedisplay();
}