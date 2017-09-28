#include <stdio.h>
#include <stdlib.h>
#include <GL/glut.h>
#include <math.h>

#define WINDOW_X 500
#define WINDOW_Y 500
#define WINDOW_NAME "test1"

void init_GL(int argc, char *argv[]);
void init();
void set_callback_functions();

void glut_display();
void glut_keyboard(unsigned char key, int x, int y);

void draw_square1();
void draw_square2();
void draw_square3();
void draw_n(int n);

// グローバル変数
int g_display_mode = 1;
int npoly = 3;

int main(int argc, char *argv[]){
  /* OpenGLの初期化 */
  init_GL(argc, argv);

  /* このプログラム特有の初期化 */
  init();

  /* コールバック関数の登録 */
  set_callback_functions();

  /* メインループ */
  glutMainLoop();

  return 0;
}

void init_GL(int argc, char *argv[]){
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_RGBA);
  glutInitWindowSize(WINDOW_X, WINDOW_Y);
  glutCreateWindow(WINDOW_NAME);
}

void init(){
  glClearColor(0.0, 0.0, 0.0, 0.0);
}

void set_callback_functions(){
  glutDisplayFunc(glut_display);
  glutKeyboardFunc(glut_keyboard);
}

// キーボードに変化があった時に呼び出されるコールバック関数。
void glut_keyboard(unsigned char key, int x, int y){
  switch(key){

  case 'q':
  case 'Q':
  case '\033': // Escキーのこと
    exit(0);
  case '1':
    g_display_mode = 1;
    break;
  case '2':
    g_display_mode = 2;
    break;
  case '3':
    g_display_mode = 3;
    break;
  case '4':
    g_display_mode = 4;
  case 's':
    npoly++;
    break;
  case 'a':
    if(npoly >= 4){
      npoly--;
    }
    break;
  }

  glutPostRedisplay();
}

// ディスプレイに変化があった時に呼び出されるコールバック関数。
// 「ディスプレイに変化があった時」は、glutPostRedisplay() で指示する。
void glut_display(){
  glClear(GL_COLOR_BUFFER_BIT);

  switch(g_display_mode){
  case 1:
    draw_square1();
    break;
  case 2:
    draw_square2();
    break;
  case 3:
    draw_square3();
    break;
  case 4:
    draw_n(npoly);
  }

  glFlush();
}

void draw_square1(){
  glBegin(GL_LINE_LOOP);

  glColor3d(1.0, 0.0, 0.0);
  glVertex2d(-0.9,-0.9);
  glVertex2d(0.9, -0.9);
  glVertex2d(0.9,0.9);
  glVertex2d(-0.9,0.9);

  glEnd();
}

void draw_square2(){
  glBegin(GL_POLYGON);

  glColor3d(1.0, 0.0, 0.0);
  glVertex2d(-0.9,-0.9);
  glVertex2d(0.9, -0.9);
  glVertex2d(0.9,0.9);
  glVertex2d(-0.9,0.9);

  glEnd();
}

void draw_square3(){
  glBegin(GL_POLYGON);

  glColor3d(1.0, 0.0, 0.0);
  glVertex2d(-0.9,-0.9);
  glColor3d(1.0, 1.0, 0.0);
  glVertex2d(0.9, -0.9);
  glColor3d(0.0, 1.0, 1.0);
  glVertex2d(0.9,0.9);
  glColor3d(0.0, 0.0, 0.0);
  glVertex2d(-0.9,0.9);

  glEnd();
}
void draw_n(int n){
  glBegin(GL_POLYGON);
  int i;
  for(i = 0;i < n;i++){
    glVertex2d(cos(2.0*i/n*M_PI), sin(2.0 * i/n*M_PI));
  }

  glEnd();
}
