void iPassiveMouseMove(int mx, int my);
void mousePassiveMoveHandlerFF(int mx, int my);

void mousePassiveMoveHandlerFF(int mx, int my){

    iPassiveMouseMove(mx,iScreenHeight - my);
    glFlush();
}

void dxFilledPolygon(double x[], double y[], int n,int r, int g, int b)
{
    int i;
    if(n<3)return;
    glBegin(GL_POLYGON);
    for(i = 0; i < n; i++){
        if(i==2) iSetColor(r,g,b);
        glVertex2f(x[i], y[i]);
    }
    glEnd();
}



void dxFilledRectangle(double left, double bottom, double dx, double dy,int r, int g, int b)
{
    double xx[4], yy[4];
    double x1, y1, x2, y2;

    x1 = left;
    y1 = bottom;
    x2=x1+dx;
    y2=y1+dy;

    xx[0]=x1;
    yy[0]=y1;
    xx[1]=x2;
    yy[1]=y1;
    xx[2]=x2;
    yy[2]=y2;
    xx[3]=x1;
    yy[3]=y2;

    dxFilledPolygon(xx, yy, 4, r,g,b);
}



void iInitializeNew(int width=500, int height=500, char *title="iGraphics")
{
    iScreenHeight = height;
    iScreenWidth = width;

    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_ALPHA) ;
    glutInitWindowSize(width , height ) ;
    glutInitWindowPosition( 10 , 10 ) ;
    glutCreateWindow(title) ;
    glClearColor( 0.0 , 0.0 , 0.0 , 0.0 ) ;
    glMatrixMode( GL_PROJECTION) ;
    glLoadIdentity() ;
    glOrtho(0.0 , width , 0.0 , height , -1.0 , 1.0) ;
    //glOrtho(-100.0 , 100.0 , -100.0 , 100.0 , -1.0 , 1.0) ;
    //SetTimer(0, 0, 10, timer_proc);

    iClear();

    glutDisplayFunc(displayFF) ;
    glutKeyboardFunc(keyboardHandler1FF); //normal
    glutSpecialFunc(keyboardHandler2FF); //special keys
    glutMouseFunc(mouseHandlerFF);
    glutMotionFunc(mouseMoveHandlerFF);
    glutPassiveMotionFunc(mousePassiveMoveHandlerFF);
    glutIdleFunc(animFF) ;

    //
    // Setup Alpha channel testing.
    // If alpha value is greater than 0, then those
    // pixels will be rendered. Otherwise, they would not be rendered
    //
    glAlphaFunc(GL_GREATER,0.0f);
    glEnable(GL_ALPHA_TEST);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glutFullScreen();
    glutMainLoop();
}


