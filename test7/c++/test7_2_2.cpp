#include <gl/glut.h>
#include <math.h>

#define QMeshSize 256
#define true 1
#define false 0
int width = 400, height = 600, vert[100][2],n = 0,
type = GL_LINE_STRIP,v;
bool rubberbanding = false,antialiasing = false;

float QMesh[100][QMeshSize+1][3];
GLfloat lightPosition[] = {-4.0,4.0,-6.0,1.0};
GLfloat amb[] = {0.3f,0.3f,0.3f,0.3f};
GLfloat frontDiffAmb[] = {0.95f,0.3f,0.1f,1.0};
GLfloat backDiffAmb[] = {0.1f,0.3f,0.95f,1.0};
GLfloat Spec[] = {0.45f,0.45f,0.45f,1.0};
GLfloat SpecExp = 15.0;
bool left_button_down = false, right_button_down = false;
int w = 600, h = 600,winid,
cx,cy,
dx=0,dy=0;
float zoom = 1.0;
typedef float Matrix[4][4];
Matrix RM,CRM;

void initQMesh(){
    float r;
    for(int i = 0; i<n; i++){
        r = vert[i][0]-width/2.0;
        for(int j = 0; j < QMeshSize;j++){
            QMesh[i][j][0]= r * cos(3.14159 * 2 * j /QMeshSize) / 100;
            QMesh[i][j][1]=(vert[i][1] - height/2.0) / 100;
            QMesh[i][j][2]=r * sin(3.14159 *2 *j /QMeshSize) / 100;
        }
        QMesh[i][QMeshSize][0]= QMesh[i][0][0];
        QMesh[i][QMeshSize][1]= QMesh[i][0][1];
        QMesh[i][QMeshSize][2]= QMesh[i][0][2];
    }
}

void display(){
    glClear(GL_COLOR_BUFFER_BIT);
    if(n == 1 &&  type ==GL_LINE_STRIP) {
        glBegin(GL_POINTS);
        glVertex2iv(vert[0]);
        glColor3f(0,0.5,0.5);
        glVertex2i(width-vert[0][0]-1,vert[0][1]);
        glEnd();
    }
    glColor3f(0,0.5,0.5);
    glBegin(GL_LINES);
    glVertex2i(width/2,0);
    glVertex2i(width/2,height-1);
    glEnd();
    glBegin(type);
    for(int i = 0;i<n;i++) glVertex2i(width-vert[i][0]-1,vert[i][1]);
    glEnd();
    glColor3f(1,1,0);
    glBegin(type);
    for(int j = 0;j<n;j++) glVertex2iv(vert[j]);
    glEnd();
    glutSwapBuffers();
    initQMesh();
    glutSetWindow(winid);
    glutPostRedisplay();
}

void keyboard(unsigned char key, int x,int y){
    switch(key){
        case 'a': antialiasing = ! antialiasing;
            if(antialiasing){
                glEnable(GL_BLEND);
                glEnable(GL_LINE_SMOOTH);
            }else{
                glDisable(GL_BLEND);
                glDisable(GL_LINE_SMOOTH);
            }
            break;
        case 'c': n = 0;break;
        case 'l': type = GL_LINE_STRIP;break;
        case 'v': type = GL_POINTS;break;
        case 'p': type = GL_LINE_LOOP; break;
    }
    glutPostRedisplay();
}

int findVertex(int x,int y){
    int dx,dy;
    for(int i = 0;i< n;i++){
        dx = vert[i][0]-x;
        dy = vert[i][1]-y;
        if(dx*dx + dy*dy < 16) return i;
    }
    return -1;
}

void mouse(int button, int state, int x ,int y){
    y = height - 1 - y;
    switch(button){
        case GLUT_LEFT_BUTTON:
            if(state == GLUT_DOWN && ! rubberbanding ){
                v = n++;
                vert[v][0] = (x < width/2) ? width/2: (x >= width) ? width - 1 : x;
                vert[v][1] = (y < 0) ? 0 : (y >= height) ? height -1 : y;
                rubberbanding = true;
                glutPostRedisplay();
            }
            else rubberbanding = false;
            break;
        case GLUT_RIGHT_BUTTON:
            if(state == GLUT_DOWN && ! rubberbanding && (v = findVertex(x,y)) != -1) {
                if(glutGetModifiers() == GLUT_ACTIVE_CTRL) {
                    for (int i = v; i< n-1; i++){
                        vert[v][0] = vert[i+1][0];
                        vert[i][1] = vert[i+1][1];
                    }
                    n--;
                }else{
                    vert[v][0] = (x < width/2) ? width/2 : (x >= width) ? width - 1 : x;
                    vert[v][1] = (y < 0) ? 0 : (y >= height) ? height -1 : y;
                    rubberbanding = true;
                }
                glutPostRedisplay();
            }
            else rubberbanding = false;
            break;
    }
}

void motion(int x, int y){
    if(rubberbanding){
        vert[v][0] =  (x < width/2) ? width/2 : (x >= width) ? width - 1 : x;
        y = height-1-y;
        vert[v][1] =(y < 0) ? 0 : (y >= height) ? height -1 : y;
        glutPostRedisplay();
    }
}

void normalize(float * v){
    float m = sqrt(v[0] * v[0] + v[1] * v[1] + v[2] * v[2]);
    for(int i = 0; i < 3; i++)
        v[i] = v[i] / m;
}
//矩阵运算
float vv(float * v1, float * v2){
    return v1[0] * v2[0] + v1[1] * v2[1] + v1[2] * v2[2];
}

void vxv(float * n, float * v1, float * v2){
    n[0] = v1[1] * v2[2] - v1[2] * v2[1];
    n[1] = v1[2] * v2[0] - v1[0] * v2[2];
    n[2] = v1[0] * v2[1] - v1[1] * v2[0];
}

void loadIdentity(Matrix m){
    Matrix identity = {{1.0,0.0,0.0,0.0},
        {0.0,1.0,0.0,0.0},
        {0.0,0.0,1.0,0.0},
        {0.0,0.0,0.0,1.0}};
    for(int i = 0;i < 4; i++)
        for(int j = 0;j < 4; j++)
            m[i][j] = identity[i][j];
}

void preMultiply(Matrix p, Matrix m){
    int i , j;
    Matrix t;
    for( i = 0; i < 4; i ++)
        for( j = 0; j < 4; j++)
            t[i][j] = p[i][0] * m[0][j] + p[i][1] * m[1][j] + p[i][2] * m[2][j] + p[i][3] * m[3][j];
    for( i = 0; i < 4; i ++)
        for( j = 0; j < 4; j ++)
            m[i][j] = t[i][j];
}

void rotate(float angle, float * axis){
    float v[3]= {axis[0],axis[1],0},
    i[3]={1,0,0},
    k[3]= {0,0,1};
    loadIdentity(RM);
    normalize(v);
    float r1= (v[1] < 0) ? acos(vv(v,i)) : -acos(vv(v,i));
    Matrix Rz = {{cos(r1), -sin(r1),0.0,0.0},
        {sin(r1),cos(r1),0.0,0.0},
        {0.0,0.0,1.0,0.0},
        {0.0,0.0,0.0,1.0}};
    preMultiply(Rz,RM);
    float r2 = -acos(vv(axis,k));
    Matrix Ry={{cos(r2),0.0,sin(r2),0.0},
        {0.0,1.0,0.0,0.0},
        {-sin(r2),0.0,cos(r2),0.0},
        {0.0,0.0,0.0,1.0}};
    preMultiply(Ry,RM);
    Matrix R={{cos(angle),-sin(angle),0.0,0.0},
        {sin(angle),cos(angle),0.0,0.0},
        {0.0,0.0,1.0,0.0},
        {0.0,0.0,0.0,1.0}};
    preMultiply(R,RM);
    Matrix R_y={{cos(-r2),0.0,sin(-r2),0.0},
        {0.0,1.0,0.0,0.0},
        {-sin(-r2),0.0,cos(-r2),0.0},
        {0.0,0.0,0.0,1.0}};
    preMultiply(R_y,RM);
    Matrix R_z={{cos(-r1),-sin(-r1),0.0,0.0},
        {sin(-r1),cos(-r1),0.0,0.0},
        {0.0,0.0,1.0,0.0},
        {0.0,0.0,0.0,1.0}};
    preMultiply(R_z,RM);
    preMultiply(RM,CRM);
}


void drawQMesh(){
    int i,j;
    float v1[3],v2[3],norm[3];
    glBegin(GL_QUADS);
    for(i = 0; i < n-1; i++)
        for(j=0;j<QMeshSize;j++){
            v1[0] = QMesh[i+1][j+1][0] - QMesh[i][j][0];
            v1[1] = QMesh[i+1][j+1][1] - QMesh[i][j][1];
            v1[2] = QMesh[i+1][j+1][2] - QMesh[i][j][2];
            v2[0] = QMesh[i+1][j][0] - QMesh[i][j+1][0];
            v2[1] = QMesh[i+1][j][1] - QMesh[i][j+1][1];
            v2[2] = QMesh[i+1][j][2] - QMesh[i][j+1][2];
            vxv(norm,v1,v2);
            glNormal3fv(norm);
            glVertex3fv(QMesh[i][j]);
            glVertex3fv(QMesh[i][j+1]);
            glVertex3fv(QMesh[i+1][j+1]);
            glVertex3fv(QMesh[i+1][j]);
        }
    glEnd();
}

void modelDisplay(){
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glPushMatrix();
    float M[16];
    for(int r = 0; r < 4; r++) for(int c = 0; c < 4; c++) M[4 * c + r] = CRM[r][c];
    glMultMatrixf(M);
    glScalef(zoom,zoom,zoom);
    drawQMesh();
    glPopMatrix();
    glPushMatrix();
    glLightfv(GL_LIGHT0,GL_AMBIENT,amb);
    glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);
    glPopMatrix();
    glutSwapBuffers();
}

void modelKeyboard(unsigned char key, int x, int y){
    switch (key) {
        case 'o':glMatrixMode(GL_PROJECTION);
            glLoadIdentity();
            glOrtho(-4,4,-4,4,6,14);
            glMatrixMode(GL_MODELVIEW);
            break;
        case 'p':glMatrixMode(GL_PROJECTION);
            glLoadIdentity();
            gluPerspective(45.0,1.0,6.0,14.0);
            glMatrixMode(GL_MODELVIEW);
            
    }
    glutPostRedisplay();
}

void modelMouse(int button,int state,int x,int y){
    switch (button){
        case GLUT_LEFT_BUTTON:
            if(state == GLUT_DOWN ){
                cx = x;
                cy = h - 1 - y;
                dx = dy = 0;
                left_button_down = true;
            }else
                left_button_down = false;
            break;
        case GLUT_RIGHT_BUTTON:
            if(state == GLUT_DOWN){
                cx = x;
                cy = h - 1 - y;
                right_button_down = true;
            }else
                right_button_down = false;
            break;
    }
}

void modelMotion(int x, int y){
    float v1[3],v2[3],axis[3],angle,dx,dy;
    y = h - 1 - y;
    if(left_button_down){
        dx = x - cx;
        dy = y - cy;
        if(dx != 0|| dy != 0){
            v1[0]= cx - w/2;
            v1[1]= cy - h/2;
            v1[2]= 300.0;
            v2[0]= x - w/2;
            v2[1]= y - h/2;
            v2[2]= 300.0;
            vxv(axis,v1,v2);
            angle = sqrt(dx * dx + dy * dy)/200;
            normalize(axis);
            rotate(angle,axis);
        }
    }
    if(right_button_down) zoom  = zoom - zoom * (y - cy) /250;
    cx = x;
    cy = y;
    glutPostRedisplay();
}
void modelIdle(void){
    if(dx * dx + dy * dy > 9) preMultiply(RM,CRM);
    glutPostRedisplay();
}

void main(int argc, char * * argv){
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB| GLUT_DOUBLE);
    glutInitWindowSize(width,height);
    glutInitWindowPosition(50,100);
    glutCreateWindow("Edit polygons");
    glClearColor(0.0,0.0,0.0,0.0);
    glColor3f(1,1,0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0,width,0,height);
    glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
    glutMouseFunc(mouse);
    glutMotionFunc(motion);
    
    glutInitDisplayMode(GLUT_RGB| GLUT_DEPTH | GLUT_DOUBLE);
    glutInitWindowSize(w,h);
    glutInitWindowPosition(50+width,100);
    winid = glutCreateWindow("Display object");
    glEnable(GL_DEPTH_TEST);
    glClearColor(0.0,0.0,0.0,0.0);
    
    glMaterialfv(GL_FRONT,GL_AMBIENT_AND_DIFFUSE,frontDiffAmb);
    glMaterialfv(GL_BACK,GL_AMBIENT_AND_DIFFUSE,backDiffAmb);
    glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,Spec);
    glMaterialf(GL_FRONT_AND_BACK,GL_SHININESS,SpecExp);
    
    glLightfv(GL_LIGHT0,GL_AMBIENT,amb);
    glLightfv(GL_LIGHT0,GL_POSITION,lightPosition);
    glLightModeli(GL_LIGHT_MODEL_TWO_SIDE,GL_TRUE);
    glEnable(GL_NORMALIZE);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0,1.0,6.0,14.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glTranslated(0,0,-10);
    glutDisplayFunc(modelDisplay);
    glutKeyboardFunc(modelKeyboard);
    glutMouseFunc(modelMouse);
    glutMotionFunc(modelMotion);
    glutIdleFunc(modelIdle);
    loadIdentity(CRM);
    loadIdentity(RM);
    
    glutMainLoop();
}

