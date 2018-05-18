
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\
 *                                                                             *
 *  Started by Ángel on march of 2014                                          *
 *                                                                             *
 *  This is free software released into the public domain.                     *
 *                                                                             *
 *  angel.rodriguez@esne.edu                                                   *
 *                                                                             *
\* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#include <cassert>
#include "View.hpp"
#include <SFML/Window.hpp>
#include <SFML/OpenGL.hpp>

#include <anim.h>

using namespace sf;
using namespace example;

int main ()
{
    Window window(VideoMode(800, 600), "OpenGL Examples: Texturing", Style::Default, ContextSettings(32));

    window.setVerticalSyncEnabled (true);

    // Una vez se ha creado el contexto de OpenGL ya se puede inicializar Glew:

    GLenum glew_initialization =  glewInit ();

    assert(glew_initialization == GLEW_OK);

    // Una vez se ha inicializado GLEW se puede crear una instancia de View:

    View view(800, 600);

    // Se ejecuta el bucle principal:

    bool running = true;

    do
    {
        Event event;

        while (window.pollEvent (event))
        {
            switch (event.type)
            {
                case Event::Closed:
                {
                    running = false;
                    break;
                }

                case Event::Resized:
                {
                    Vector2u window_size = window.getSize ();

                    view.resize (window_size.x, window_size.y);

                    break;
                }
            }
        }

        view.update ();
        view.render ();

        window.display ();
    }
    while (running);

    return (EXIT_SUCCESS);
}