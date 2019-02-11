#include <GL/glu.h>
#include <GL/glut.h>
#include <iostream>
#include <stdlib.h>
#include <math.h>
#include<iostream>
#include<sstream>
#include <string>
#include<string.h>

#include<windows.h>
#include<mmsystem.h>


using namespace std;

static float xp=-.55;
int static bdspeed = 60;
float bodymove = 4;
float static y11= -3.3;
float static zp= 2;
float static tpx= .15;
int static bodypos= 0;
float view = 10.0;
int static score= 0;
int static totalMeter = 0;
char quote[6][80];
int numberOfQuotes = 0, i;
int static bodyspeed= 45;


void sprint( float x, float y, string st)
{
    int l,i;
    glColor3f(0.0,0.0,0.0);

    glRasterPos2f( x, y); // location to start printing text
    for( i=0; i <  st.length(); i++) // loop until i is greater then l
    {
       glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, st[i]);

    }


}

void keyboardown(int key, int x, int y)
{
	switch (key){

	case GLUT_KEY_RIGHT:
	    xp=.55;
	    bodypos=1;
      break;



	case GLUT_KEY_LEFT:
	    xp=-.55;
	    bodypos=0;
	    break;


    case GLUT_KEY_UP:
        if (bdspeed>5){
        bdspeed-=5;
        bodyspeed+=5;
        }

        else
            bdspeed=bdspeed;
        break;


    case GLUT_KEY_DOWN:
       if (bdspeed<60){
        bdspeed+=5;
        bodyspeed-=5;
        }

        else
            bdspeed=bdspeed;
        break;


	default:
		break;

	}
}

//Extra Display Function
void reshape(int w, int h)
{
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60, 1.0, 1.0, 3200);
	glMatrixMode(GL_MODELVIEW);
}

GLfloat UpwardsScrollVelocity = -1.0;

void timeTick(void)
{
	if (UpwardsScrollVelocity< -1)
		view -= 0.0011;
	if (view < 0) { view = 2; UpwardsScrollVelocity = -1.0; }
	//  exit(0);
	UpwardsScrollVelocity -= 0.2;
	glutPostRedisplay();
}


void RenderToDisplay()
{
	int l, lenghOfQuote, i;

	glTranslatef(0.0, 0.0, 0.0);
	glRotatef(-20, 1.0, 0.0, 0.0);
	glScalef(0.05, 0.05, 0.05);

	for (l = 0; l<numberOfQuotes; l++)
	{
		lenghOfQuote = (int)strlen(quote[l]);
		glPushMatrix();
		glTranslatef(-(lenghOfQuote * 37), (l * 200), 0.0);
		for (i = 0; i < lenghOfQuote; i++)
		{
			glColor3f((UpwardsScrollVelocity / 10) + 400 + (l * 10), (UpwardsScrollVelocity / 10) + 300 + (l * 10), 0.0);

			glutStrokeCharacter(GLUT_STROKE_ROMAN, quote[l][i]);
		}
		glPopMatrix();
	}
}




void myDisplayFunction(void)
{
	glClear(GL_COLOR_BUFFER_BIT);
	glLoadIdentity();
	gluLookAt(0.0, 30.0, 100.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
	RenderToDisplay();
	glutSwapBuffers();


}

int winner(char a)
{


	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(800, 500);
	glutCreateWindow("GAME OVER");
	glClearColor(0.0, 0.0, 0.0, 1.0);
	glLineWidth(3);
	char c=char(score);


	strcpy(quote[1], "Game Over");

	numberOfQuotes = 5;
	glutDisplayFunc(myDisplayFunction);
	glutReshapeFunc(reshape);
	glutIdleFunc(timeTick);
	glutMainLoop();

	return 0;
}



bool collision()
{

	if (0 > (bodymove-y11)&& -1 < (bodymove-y11)&& bodypos==1 )
	{
		return true;
	}

	else if (0 > (bodymove-(y11-10))&& -1 < (bodymove-(y11-10))&& bodypos==0 )
	{
	    return true;
	}

    else if (0 > (bodymove-(y11-20))&& -1 < (bodymove-(y11-20))&& bodypos==0 )
	{
	    return true;
	}

	 else if (0 > (bodymove-(y11-30))&& -1 < (bodymove-(y11-30))&& bodypos==1 )
	{
	    return true;
	}


	 else if (0 > (bodymove-(y11-30))&& -1 < (bodymove-(y11-30))&& bodypos==0 )
	{
	    y11-=40;
	    return false;
	}

	else
    {
        return false;
	}
}

    bool GameScore()
    {
    if (0 > (bodymove-y11)&& -1 < (bodymove-y11)&& bodypos==0 )
	{
	    score++;
	}

	else if (0 > (bodymove-(y11-10))&& -1 < (bodymove-(y11-10))&& bodypos==1 )
	{
	     score++;
	}

    else if (0 > (bodymove-(y11-20))&& -1 < (bodymove-(y11-20))&& bodypos==1 )
	{

	     score++;
	}

	 else if (0 > (bodymove-(y11-30))&& -1 < (bodymove-(y11-30))&& bodypos==0 )
	{

	     score+=10;
	}

	else if (0 > (bodymove-(y11-35))&& -1 < (bodymove-(y11-35))&& bodypos==0 )
	{
        return true;
	     score+=10;
	}



    }


//Initializes 3D rendering
void initRendering() {
	glEnable(GL_DEPTH_TEST);
}

//Called when the window is resized
void handleResize(int w, int h) {
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0, (double)w / (double)h, 1.0, 200.0);
}

float _angle = 0.0;
float _cameraAngle = 0.0;
float _ang_tri = 0.0;



//////////////HUMAN BODY///////////////////////

void playerbody()
    {

        /////////belly///////////
        glPushMatrix();
            glTranslatef(xp, -.7, 3.5);

            glPushMatrix();
            glRotatef(-10 , -1.0, 0.0, 0.0);
            glScalef(1, 1.5, 1);
			glColor3f(1, 1, 1);
            glutSolidCube(.2);
            glPopMatrix();

            /////////head///////////
            glPushMatrix();
            glTranslatef(0.0, tpx+.1, 0.0);
            glRotatef(-10 , -1.0, 0.0, 0.0);
            glColor3f(0, 0, 0);
            glutSolidSphere(.09,20,10);
            glPopMatrix();


////////////////left leg///////////
            glPushMatrix();
            glTranslatef(-0.05, -0.25, 0.10);
            glRotatef(80 , 0.0, 1.2, 0.0);
            glScalef(.4, .9, .07);
			glColor3f(1, 0, 0);
            glutSolidCube(.2);
            glPopMatrix();


           /////////////Right Leg///////////

            glPushMatrix();
            glTranslatef(0.05, -0.25, 0.10);
            glRotatef(80 , 0.0, 1.2, 0.0);
            glScalef(.44 , .9, .07);
			glColor3f(1, 0, 0);
            glutSolidCube(.2);
            glPopMatrix();


     glPopMatrix();




    }


void roadside()
    {


     for (float z = -38; z < 400; z +=4)
	{
          ///grass///
          glBegin(GL_QUADS);
            glColor3ub(0, 94, 48);
			glVertex3f(-5.0, -10, 0);
			glVertex3f(-1.0, -10, 0);
			glVertex3f(-1.0, 400, 0);
			glVertex3f(-5.0, 400, 0);
		  glEnd();

		glBegin(GL_QUADS);
            glColor3ub(0, 94, 48);
			glVertex3f(1.0, -10, 0);
			glVertex3f(5.0, -10, 0);
			glVertex3f(5.0, 400, 0);
			glVertex3f(1.0, 400, 0);
		glEnd();


    }
 }

void house(){

     for (float z = -40; z < 400; z +=4.8)
	{
		glPushMatrix();
		glScalef(1.0, 1.0, 1.0);
		    glPushMatrix();
			glColor3ub(149, 149,149);
			glTranslatef(-1.70, z, .30);
            glutSolidCube(1);//2ND FLOOR
		    glPopMatrix();

		glPushMatrix();
		glScalef(1.0, 1.0, 1.0);
		glPushMatrix();
        glColor3ub(255,255,255);
        glTranslatef(-1.70, z, 1.30);
        glutSolidCube(1);//1st floor
		glPopMatrix();



		glPushMatrix();//WINDOW RIGHT
			glColor3ub(106, 106, 255);
			glTranslatef(-1.10, z, .50);
            glutSolidCube(.2);
		glPopMatrix();

		//////////////////




		glPushMatrix();//2ND FLOOR WINDOW RIGHT
			glColor3ub(106, 106, 255);
			glTranslatef(-1.10, z, 1.50);
            glutSolidCube(.2);
		glPopMatrix();


		glPushMatrix(); //WINDOW LEFT
			glColor3ub(106, 106, 255);
			glTranslatef(-1.10, z-.5, .50);
            glutSolidCube(.2);
		glPopMatrix();

		glPushMatrix(); //2ND FLOOR WINDOW LEFT
			glColor3ub(106, 106, 255);
			glTranslatef(-1.10, z-.5, 1.50);
            glutSolidCube(.2);
		glPopMatrix();





		glPushMatrix(); // DOOR
			glColor3ub(106, 106, 255);
			glTranslatef(-1.60, z-.5, .2);
            glScalef(.6, .2, 1);
            glutSolidCube(.5);
		glPopMatrix();

		glPushMatrix(); // 2ND FLOOR DOOR
			glColor3ub(106, 106, 255);
			glTranslatef(-1.60, z-.5, 1.10);
            glScalef(.6, .2, 1);
            glutSolidCube(.5);
		glPopMatrix();
		glPopMatrix();

		//right side

		glPushMatrix();
		glPushMatrix();//2nd floor
			glColor3f(1, 1, 1);
			glTranslatef(1.70, z, 1.30);
            glutSolidCube(1);
		glPopMatrix();



		glPushMatrix();
			glColor3ub(166, 166, 83);//window
			glTranslatef(1.20, z, .40);
            glutSolidCube(.2);
		glPopMatrix();

		glPushMatrix();
			glColor3ub(166, 166, 83);//2nd floor window
			glTranslatef(1.20, z, 1.40);
            glutSolidCube(.2);
		glPopMatrix();



		glPushMatrix();
			glColor3ub(166, 166, 83);//door
			glTranslatef(1.69, z-.5, .2);
			glScalef(.6, .2, 1);
            glutSolidCube(.5);
		glPopMatrix();

		glPushMatrix();
			glColor3ub(166, 166, 83);//2nd floor door
			glTranslatef(1.69, z-.5, 1.2);
			glScalef(.6, .2, 1);
            glutSolidCube(.5);
		glPopMatrix();

		glPushMatrix();//1st floor
			glColor3f(1, 0, 0);
			glTranslatef(1.70, z, .30);
            glutSolidCube(1);


		glPopMatrix();



		 ///Left back side tree///

		glPushMatrix();
		glColor3f(0, 1, 0);
			glTranslatef(-3.0, z, .60);
            glutSolidCone(.4, .6, 20, 10);

		glPopMatrix();



		glPushMatrix();
		glColor3f(0, 1, 0);

			glTranslatef(-3.0, z, .80);
            glutSolidCone(.4, .6, 20, 10);

		glPopMatrix();



		glPushMatrix();
		glColor3f(0,1,0);
			//glTranslatef(-1.20, z, .45);
			glTranslatef(-3.0, z, .99);
            glutSolidCone(.4, .6, 20, 10);

		glPopMatrix();


		//left tree bottom  stone
		glPushMatrix();
			glColor3f(164, 82, 0);
			glTranslatef(-3.0, z, .01);
            glutSolidSphere(.14, 7, 4);
		glPopMatrix();



            glColor3ub(102, 51, 0);
		glTranslatef(-3.0, z, .30);
			glScalef(.071, .071, 1);
            glutSolidCube(.8);
		glPopMatrix();



//right back side tree

		glPushMatrix();
		glColor3f(0, 1, 0);
			glTranslatef(3.0, z, .50);
            glutSolidCone(.4, .6, 20, 10);

		glPopMatrix();

		glPushMatrix();
		glColor3f(0, 1, 0);
			glTranslatef(3.0, z, .70);
            glutSolidCone(.4, .6, 20, 10);

		glPopMatrix();



		glPushMatrix();
		glColor3f(0,1,0);
			glTranslatef(3.0, z, .90);
            glutSolidCone(.4, .6, 20, 10);

		glPopMatrix();




		glPushMatrix();
            glColor3ub(102, 51, 0);
		glTranslatef(3.0, z, .30);
			glScalef(.071, .071, 1);
            glutSolidCube(.8);
		glPopMatrix();

//right tree bottom  stone
		glPushMatrix();
			glColor3f(164, 82, 0);
			glTranslatef(3.0, z, .01);
            glutSolidSphere(.14, 7, 4);
		glPopMatrix();


		glPopMatrix();

	}
    }


    void tree(){
        for (float z = -40; z < 400; z +=4)
	{
		glPushMatrix();

		///front side tree///
		glPushMatrix();
			glColor3f(0, 1, 0);
			glTranslatef(-1.40, z, .35);
            glutSolidCone(.2, .4, 20, 10);
		glPopMatrix();
            glColor3ub(102, 51, 0);
		glTranslatef(-1.40, z, .15);
			glScalef(.2, .2, 2);
            glutSolidCube(.2);
		glPopMatrix();


glPushMatrix();

		glPushMatrix();
			glColor3ub(255, 156,108);
            glTranslatef(-1.40, z, .008);
            glutSolidSphere(.12, 7, 4);
		glPopMatrix();





		//right

		glPushMatrix();
		glPushMatrix();
			glColor3f(0, 1, 0);
			glTranslatef(1.40, z, .37);
            glutSolidCone(.2, .4, 20, 10);
		glPopMatrix();
            glColor3ub(102, 51, 0);
			glTranslatef(1.40, z, .17);
			glScalef(.2, .2, 2);
            glutSolidCube(.2);
		glPopMatrix();


///right tree vast///

glPushMatrix();

		glPushMatrix();
			glColor3ub(128, 128,128);
            glTranslatef(1.40, z, .008);

            glutSolidSphere(.12, 7, 4);
		glPopMatrix();


	}

    }




void roadline(){
    for (float z = -4; z < 6; z +=1)
	{
		glPushMatrix();

			glColor3f(1, 1, 0);
				glBegin(GL_QUADS);
				glVertex3f(-.03, z, 0);
				glVertex3f(.03, z, 0);
				glVertex3f(.03, z+.5, 0);
				glVertex3f(-.03, z+.5, 0);
			glEnd();
		glPopMatrix();
	}
    }

void manhole()
{

 for (float z = -60; z < 400; z +=50)
	{

	    ///manhole///

		glPushMatrix();
			glColor3ub(0,0,0);
            glTranslatef(-1.0, z, -.21);

            glutSolidTorus(.09, 0.122, 5,5);
		glPopMatrix();


	}
}



    void objectcube()
    {
         for (float zp = -20; zp < 400; zp+=40)
	{

		glPushMatrix();
			glColor3ub(255,255, 0);
			glTranslatef(-.30, zp, -.1);
           // glutSolidCube(.4);
           glutWireSphere(.4,10,10);
	glPopMatrix();

///cng/////////////////////

		glPushMatrix();
			glColor3ub(0,128,128);//down
			 glScalef(1.6, 1.0, .8);
			glTranslatef(.30, zp+10, -.1);
           glutSolidCube(.4);
		glPopMatrix();
		glPushMatrix();//up
			glColor3ub(255,255,0);
			glScalef(1.6, 1.0, 1);
			glTranslatef(.30, zp+10, .3);
           glutSolidCube(.4);
           glPopMatrix();

           glPushMatrix();
			glColor3ub(0,0,0);//low
			 glScalef(1.6, 1.0, .2);
			glTranslatef(.30, zp+10, -1.50);
           glutSolidCube(.4);
		glPopMatrix();

           glPushMatrix();
          glTranslatef(.30, zp+9.5, .01);
            glScalef(.1, .1, .1);
			glColor3f(1, 0, 0);
            glutSolidCube(1);
            glPopMatrix();
            glPushMatrix();
          glTranslatef(.65, zp+9.5, .01);
            glScalef(.1, .1, .1);
			glColor3f(1, 0, 0);
            glutSolidCube(1);
            glPopMatrix();

            glPushMatrix();//up window
			glColor3ub(0,0,0);
			glScalef(2.50, 1.0, 1);
			glTranslatef(.19, zp+9.5, .33);
           glutSolidCube(.1);
           glPopMatrix();


           glPushMatrix();
            glTranslatef(0.15, zp+10, -0.10);
            glRotatef(80 , 0.0, 1.2, 0.0);
            glScalef(.07, .14, .07);
			glColor3f(0, 0, 0);
            glutWireTorus(.3, .4, 20, 15);
            glPopMatrix();

      glPopMatrix();

///cng end///////////////
		glPushMatrix();
			glColor3ub(95,158,160);
			glTranslatef(.30, zp+20, -.1);
          glutWireSphere(.2,10,10);
		glPopMatrix();

		glPushMatrix();
		     glColor3ub(106,90,205);
			glTranslatef(-.30, zp+30, -.1);
           glutSolidCube(.4);


		glPopMatrix();

   }
    }


    void road(){


	glPushMatrix();

		glColor3f(.68, .34, 0);
		glTranslatef(0.0, 0.0, -.50);
		glBegin(GL_QUADS);
			glVertex3f(-1.5, -10, 0); //1.5
			glVertex3f(1.5, -10, 0);
			glVertex3f(1.5, 400, 0);
			glVertex3f(-1.5, 400, 0);
		glEnd();


	glPopMatrix();


    }
//Draws the 3D scene
void drawScene() {

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW); //Switch to the drawing perspective
	glLoadIdentity(); //Reset the drawing perspective
	glRotatef(-_cameraAngle, 0.0, 1.0, 0.0); //Rotate the camera
	glTranslatef(0.0, 0.0, -7.0); //Move forward 5 units
    playerbody();

    glPushMatrix(); //Save the current state of transformations
	glTranslatef(0.0, 0.0, 0.0); //Move to the center of the triangle
	glRotatef(80 , -1.0, 0.0, 0.0);

	glPushMatrix();
	glTranslatef(0.0, bodymove, 0.0);
	glClearColor(0.0, 185, 185, 1.0);
    road();
    glPopMatrix();
    glPushMatrix();
	glTranslatef(0.0, bodymove, 0.0);
    tree();
    house();
    roadside();
   objectcube();
   manhole();
    GameScore();

    cout<<score<<endl;
    cout<<bodymove<<endl;
    cout<<y11<<endl;
    glPopMatrix();

    glPushMatrix();
    glColor3ub(0,0,0);
     glTranslatef(3.66, 0.0, 2.0);


     ostringstream cnvrt;
     cnvrt << score;
     sprint(-4,-2.3,"Score: "+cnvrt.str());

     glPopMatrix();

    glPopMatrix();


    if(collision())
    {
        winner('a');
    }


	glutSwapBuffers();
}

void update(int value) {
   bodymove-= 0.1f;
	_angle += 2.0f;
	if (_angle > 360) {
		_angle -= 360;

	}
	_ang_tri += 0.7f;
	if (_ang_tri > 80) {
            _ang_tri=0;

	}

	glutPostRedisplay(); //Tell GLUT that the display has changed

	//Tell GLUT to call update again in 25 milliseconds
	glutTimerFunc(bdspeed, update, 0);
}




int main(int argc, char** argv) {

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(800, 500);
	glutInitWindowPosition(100,100);
	glutCreateWindow("SUBWAY SURFERS");
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable( GL_BLEND );
	glClearColor(0, 185, 185, 0);
	initRendering();
//	Set handler functions
	glutDisplayFunc(drawScene);
	glutReshapeFunc(handleResize);

	 sndPlaySound("F:\\c drive\\Desktop\\COMPUTER GRAPHICS\\SUBWAY SURFERS\\sound.wav", SND_ASYNC | SND_LOOP );


	glutTimerFunc(25, update, 0); //Add a timer

	glutSpecialFunc(keyboardown);

glutMainLoop();
	return 0;
}



