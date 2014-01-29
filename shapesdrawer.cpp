#include "initshaders.h"
#include "vec.h"
using namespace std;
int counter = 0;

   GLfloat vertexarray[]={
	0.0f,0.5f,
	0.5f,0.5f,
	0.0f,0.0f,
	0.5f,0.0f,
	-0.5f,0.0f,
	-0.5f,0.5f
	-1.0f,0.5f
	};



void init(){
	glClear(GL_COLOR_BUFFER_BIT);//clears the screen

	//indices of triangle
	//GLubyte indices[3]={0,1,2};


	//initialize buffers
	GLuint vao, vbo;

	glGenVertexArrays(1, &vao);//generates object name for Vertex Array$
	glBindVertexArray(vao);//bind the object to the array

	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertexarray), vertexarray, GL_STATIC_DRAW);

	ShaderInfo shaders[]={//create the shader specified by my initshaders 
  	 { GL_VERTEX_SHADER , "vertexshader.glsl"} ,
	 { GL_FRAGMENT_SHADER , "fragmentshader.glsl"},
	 { GL_NONE , NULL} 
	 };

	initShaders(shaders);

	glEnableVertexAttribArray(0);//enables the vertex attribute index 
	glVertexAttribPointer(0,2,GL_FLOAT,GL_FALSE,0,(void*)0);
}


void triangle(){
  init();
  glDrawArrays(GL_TRIANGLES, 0, 3);
  glFlush();
}

void square(){
  init();
  glBegin(GL_QUADS);
  glVertex2f(0.0f,0.0f);
  glVertex2f(0.0f, 0.5f);
  glVertex2f(0.5f,0.5f);
  glVertex2f(0.5f,0.0f);
  glEnd();
  glFlush();
}

void lines(){
  init();
  glBegin(GL_LINES);
  glVertex2f(0.0f,0.5f);
  glVertex2f(0.0f,0.0f);
  glVertex2f(0.3f,0.7f);
  glVertex2f(0.4f,0.8f);
  glVertex2f(-0.5f,0.0f);
  glVertex2f(-0.3f,0.0f);
  glVertex2f(0.0f,-0.5f);
  glVertex2f(1.0f,1.5f);
  glVertex2f(-0.2f,-0.5f);
  glVertex2f(0.0f,0.0f);
  glVertex2f(-0.3f,-0.7f);
  glVertex2f(-0.4f,-0.8f);
  glEnd();
  glFlush();
}

void drawscene(){
 switch(counter%3){
        case 0:
          glutDisplayFunc(triangle);
          glutPostRedisplay();
          break;
        case 1:
          glutDisplayFunc(square);
          glutPostRedisplay();
          break;
        case 2:
          glutDisplayFunc(lines);
          glutPostRedisplay();
          break;
  }
}

//this function create the interaction with the mouse
void mousepress(int button, int state, int x, int y){
  if(button==GLUT_RIGHT_BUTTON && state==GLUT_DOWN)//right click closes$
    exit(0);
  else if(button==GLUT_LEFT_BUTTON && state==GLUT_DOWN){//left click ch$
    counter++;
    drawscene();
  }
}

void idle(void){
  glutPostRedisplay();
}

int main(int argc, char **argv){
       //Freeglut window and context management        
  glutInit(&argc, argv);
  glutCreateWindow("Shapes");//creates the window with the specified na$
  
  //initializes glew
  glewExperimental=GL_TRUE;
  if(glewInit()){
    fprintf(stderr, "Unable to initalize GLEW");
    exit(EXIT_FAILURE);
  }
  
  glutInitContextVersion(4, 3);//specifies the version of opengl
  glutInitContextProfile(GLUT_CORE_PROFILE|GLUT_COMPATIBILITY_PROFILE);


  //retruns what version of opengl and glsl your computer can use
  const GLubyte* version=glGetString(GL_SHADING_LANGUAGE_VERSION);
  fprintf(stderr,"Opengl glsl version %s\n", version);

  version=glGetString(GL_VERSION);
  fprintf(stderr,"Opengl version %s\n", version);

  glutDisplayFunc(drawscene);//displays callback draws the shapes
  glutMouseFunc(mousepress);//control callback specifies the mouse cont$
  glutMainLoop();//sets opengl state in a neverending loop
  return 0;
}
