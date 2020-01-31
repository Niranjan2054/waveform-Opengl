#include<windows.h>
#include<GL/glut.h>
#include<iostream>
#include<math.h>
#define pi 3.1415
struct point{
    GLfloat x;
    GLfloat y;
};

point p[1000];
void initpoints()
{
    for(int i=0;i<1000;i++)
    {
        p[i].x=i;
    }
}
void displaypoints()
{
    for(int i=0;i<1000;i++){
        glColor3f(p[i].x/210,p[i].y/210,0.7);
        glBegin(GL_POINTS);
            glVertex2f(p[i].x+230,p[i].y);
        glEnd();
    }
}
void addpoint(GLfloat newy)
{
    for(int i=998;i>=0;i--){
        p[i+1].y=p[i].y;
    }
    p[0].y=newy;
}
void init()
{
    // For displaying the window color
    glClearColor(0, 0, 0, 0);
    glColor3f(1,1,1);
    glPointSize(3);
    initpoints();
    // Choosing the type of projection
    glMatrixMode(GL_PROJECTION);
    // for setting the transformation which here is 2D
    gluOrtho2D(-240, 1000, -360,360);
}
void circle(int r, int xc, int yc)
{
    GLfloat x,y;
    for(float i=0;i<2*pi;i+=0.005)
    {
        x = r*cos(i);
        y = r*sin(i);
        glColor3f(x/r,y/r,0.3);
        glBegin(GL_POINTS);
            glVertex2f(x+xc,y+yc);
        glEnd();
    }
}


void display()
{
    int counter=0;
    GLfloat x,y;
    GLfloat x1,y1;
    GLfloat x2,y2;

    for(float i=0;i<2*pi;i+=0.001)
    {
        for(float j=0;j<200;j+=.01)
        {
            for(float k =0;k<2*pi;k+=.005){
                glClear(GL_COLOR_BUFFER_BIT);
                circle(150,0,0);
                x = 150*cos(j);
                y = 150*sin(j);
                circle(40,x,y);
                x1 = 40*cos(k);
                y1 = 40*sin(k);
                circle(20,x1+x,y1+y);
                x2 = 20*cos(k)+x1+x;
                y2 = 20*sin(k)+y1+y;
                glBegin(GL_LINES);
                    glVertex2f(x2,y2);
                    glVertex2d(230,y2);
                glEnd();
                if(counter%15==0){
                        addpoint(y2);
                }
                displaypoints();
                counter++;

                glFlush();
                j+=0.0006;
            }
        }
    }
}

int main(int agrc, char ** argv)
{
    // Initialize GLUT
    glutInit(&agrc, argv);
    // Set display mode
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    // Set top - left display window position.
    glutInitWindowPosition(100, 100);
    // Set display window width and height
    glutInitWindowSize(1240, 720);
    // Create display window with the given title
    glutCreateWindow("Curve Generation");
    // Execute initialization procedure
    init();
    // Send graphics to display window
    glutDisplayFunc(display);
    // Display everything and wait.
    glutMainLoop();
}
