#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/OpenGL.hpp>

#include "specific.hpp"

#include <iostream>
#include <math.h>

#define GLM_ENABLE_EXPERIMENTAL
#include "glm/glm.hpp" 
#include "glm/gtx/transform.hpp"

void DrawCube(const float& size)
{
    glBegin(GL_QUADS);

    glTexCoord2f(0, 0); glVertex3f(-size, -size, -size);
    glTexCoord2f(0, 1); glVertex3f(-size,  size, -size);
    glTexCoord2f(1, 1); glVertex3f( size,  size, -size);
    glTexCoord2f(1, 0); glVertex3f( size, -size, -size);

    glTexCoord2f(0, 0); glVertex3f(-size, -size, size);
    glTexCoord2f(0, 1); glVertex3f(-size,  size, size);
    glTexCoord2f(1, 1); glVertex3f( size,  size, size);
    glTexCoord2f(1, 0); glVertex3f( size, -size, size);

    glTexCoord2f(0, 0); glVertex3f(-size, -size, -size);
    glTexCoord2f(0, 1); glVertex3f(-size,  size, -size);
    glTexCoord2f(1, 1); glVertex3f(-size,  size,  size);
    glTexCoord2f(1, 0); glVertex3f(-size, -size,  size);

    glTexCoord2f(0, 0); glVertex3f(size, -size, -size);
    glTexCoord2f(0, 1); glVertex3f(size,  size, -size);
    glTexCoord2f(1, 1); glVertex3f(size,  size,  size);
    glTexCoord2f(1, 0); glVertex3f(size, -size,  size);

    glTexCoord2f(0, 1); glVertex3f(-size, -size,  size);
    glTexCoord2f(0, 0); glVertex3f(-size, -size, -size);
    glTexCoord2f(1, 0); glVertex3f( size, -size, -size);
    glTexCoord2f(1, 1); glVertex3f( size, -size,  size);

    glTexCoord2f(0, 1); glVertex3f(-size, size,  size);
    glTexCoord2f(0, 0); glVertex3f(-size, size, -size);
    glTexCoord2f(1, 0); glVertex3f( size, size, -size);
    glTexCoord2f(1, 1); glVertex3f( size, size,  size);
 
    glEnd();
}

int main(int argc, char *argv[])
{
    sf::Clock clock;

    sf::ContextSettings settings; // window.getSettings();
    settings.depthBits = 24;
    settings.stencilBits = 8;
    settings.antialiasingLevel = 4;
    settings.sRgbCapable = true;
    settings.majorVersion = 2;
    settings.minorVersion = 1;
    sf::RenderWindow window(sf::VideoMode(800, 600), "SFML App", sf::Style::Default, settings);

    window.setVerticalSyncEnabled(true);
    window.setFramerateLimit(60);
    window.resetGLStates();

    std::cout << "depth bits:" << settings.depthBits << std::endl;
    std::cout << "stencil bits:" << settings.stencilBits << std::endl;
    std::cout << "antialiasing level:" << settings.antialiasingLevel << std::endl;
    std::cout << "version:" << settings.majorVersion << "." << settings.minorVersion << std::endl;

    sf::Font font;
    if (!font.loadFromFile("resources/sansation.ttf")) {
        std::cerr << "Error: Can't load font" << std::endl;
        return EXIT_FAILURE;
    }

	sf::Text text("SFML Demo", font);
	text.setFillColor(sf::Color(255, 255, 255, 170));
    text.setPosition(window.getSize().x*0.4, window.getSize().y - text.getGlobalBounds().height - text.getGlobalBounds().top - 50.f);


    GLfloat ratio = static_cast<float>(window.getSize().x) / window.getSize().y;
	glm::mat4 projection = glm::frustum(-ratio, ratio, -1.f, 1.f, 1.f, 500.0f);

    bool running = true;
    float x_angle = 0.0f;
    float y_angle = 0.0f;

    // Load a texture to apply to 3D cube
    sf::Texture texture;

    if(!texture.loadFromFile("resources/texture.jpg")) {
        std::cerr << "Error: Could not load texture" << std::endl;
        return EXIT_FAILURE;
    } else {
        // Attempt to generate a mipmap for 3D cube texture
        texture.generateMipmap();
    }

    while(running)
    {
        sf::Event event;
        sf::Time elapsed = clock.restart();

        while (window.pollEvent(event))
        {
            switch(event.type) {
                case sf::Event::KeyPressed:
                    if(event.key.code == sf::Keyboard::Escape) { 
                        running = false;
                        break;
                    }
                    if(event.key.code == sf::Keyboard::Left) { 
                        x_angle += 1.f; 
                        if(x_angle >= 360.f) x_angle = 0.0f;
                    }
                    if(event.key.code == sf::Keyboard::Right) { 
                        x_angle -= 1.f; 
                        if(x_angle <= 0.f) x_angle = 360.f;
                    }
                    if(event.key.code == sf::Keyboard::Up) { 
                        y_angle += 1.f; 
                        if(y_angle >= 360.f) y_angle = 0.0f;
                    }
                    if(event.key.code == sf::Keyboard::Down) { 
                        y_angle -= 1.f; 
                        if(y_angle <= 0.f) y_angle = 360.f;
                    }
                    break;
                case sf::Event::Closed:
                    running = false;
                    break;

                default:
                    break;
            }
        }

        window.setActive(true);

        glClearColor(0.3f, 0.3f, 0.3f, 1.f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glEnable(GL_DEPTH_TEST);
        glDepthMask(GL_TRUE);
        glClearDepth(1.f);

        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();

        sf::Vector2u wsize = window.getSize();
        glViewport(0, 0, wsize.x, wsize.y);
        glPerspective(60.f, (float)wsize.x / (float)wsize.y, 0.1f, 512.f);

        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();

        glPushMatrix();
        
        glTranslatef(0.f, 0.f, -5.f);
        glRotatef(x_angle, 0, 1, 0);
        glRotatef(y_angle, 1, 0, 0);

        glEnable(GL_TEXTURE_2D);
        sf::Texture::bind(&texture);

        DrawCube(1.f);

        sf::Texture::bind(NULL);

        glPopMatrix();

        window.pushGLStates();
		window.draw(text);
		window.popGLStates();

        window.display();
    }
    return EXIT_SUCCESS;
}
