#include <iostream>
#include <cstdlib>
#include <SDL.h>
#include <string>

#if defined(__linux__) || defined(WIN32)
    #include <GL/gl.h>
    #include <GL/glu.h>
#endif

#ifdef __APPLE__
    #include <OpenGL/gl.h>
    #include <OpenGL/glu.h>
#endif

void SDLErrorExit(const std::string &_msg);
void setupCamera();
void drawScene();
int main()
{
    std::cout<<"Hello OpenGL\n";

    if(SDL_Init(SDL_INIT_EVERYTHING) < 0)
    {
        SDLErrorExit("Unable to init SDL:");
    }

    SDL_Window *window = SDL_CreateWindow("OpenGL", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1024, 720, SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);

    if(!window)
    {
        SDLErrorExit("can't create window");
    }

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION,2);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION,1);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_COMPATIBILITY);

    SDL_GL_CreateContext(window);

    SDL_Event event;
    bool quit=false;
    glClearColor(0.4, 0.4, 0.4, 1);
    setupCamera();
    while(!quit)
    {
        while (SDL_PollEvent(&event))
        {
            switch (event.type)
            {
                case SDL_QUIT : quit=true; break;
            }
        }
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    drawScene();
    SDL_GL_SwapWindow(window);
    } //end game loop

    //while(1);

    return EXIT_SUCCESS;
}

void SDLErrorExit(const std::string &_msg)
{
    std::cerr<<_msg<<'\n';
    std::cerr<<SDL_GetError()<<'\n';
    SDL_Quit();
    exit(EXIT_FAILURE);
}

void setupCamera()
{
    glMatrixMode(GL_PROJECTION);
    gluPerspective(45.0, 1.0, 0.5f, 100.0f);
    glMatrixMode(GL_MODELVIEW);
    gluLookAt(2, 2, 2, 0, 0, 0, 0, 1, 0);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_NORMALIZE);
}

static int rot;
void drawScene()
{
    glPushMatrix();
    glRotatef(++rot, 0, 1, 0);
        glBegin(GL_TRIANGLES);
            glColor3f(1, 0, 0);
            glVertex3f(0, 1, 0);
            glColor3f(0, 1, 0);
            glVertex3f(1, -1, 0);
            glColor3f(0, 0, 1);
            glVertex3f(-1, -1, 0);

            glVertex3f(0, 1, 1);
            glVertex3f(1, -1, 1);
            glVertex3f(-1, -1, 1);
        glEnd();
    glPopMatrix();
}
