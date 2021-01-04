#include <SFML/Graphics.hpp>
#include <complex>
#include <iostream>

using namespace sf;

int main()
{
    std::cout << "hello" << std::endl;
    double iter = 20;
    double zoom = 1;
    int video_x=1280,video_y=720;
    bool render = true;
    bool draw;
    RenderWindow window(VideoMode(video_x, video_y), "Maldenbrod");
    while (window.isOpen())
    {
        window.clear(Color(250,250,250,0));
        Event event;
        while (window.pollEvent(event))
        {
            // Пользователь нажал на «крестик» и хочет закрыть окно?
            if (event.type == Event::Closed)
                // тогда закрываем его
                window.close();
        }
        int i = 0;
        if(!render)
            continue;
        render = !render;
        for(double x = 0.0; x< video_x;x++)
        {
          for(double y = 0.0; y < video_y;y++)
          {
              draw = true;
              std::complex<double> c( (-2+(x/video_x)*3)/zoom, (-1+(y/video_y)*2)/zoom);
              std::complex<double> z( 0, 0);
              for(int n = 0; n < iter;n++)
              {
                z = ((z*z)+c);
                if(std::abs(z) >= 2)
                {
                    sf::Vertex point(sf::Vector2f(x, y), sf::Color(250-n*20,0,0));
                    window.draw(&point, 1, sf::Points);
                    draw = false;
                    break;
                }
              }
              if(!draw)
                  continue;
              sf::Vertex point(sf::Vector2f(x, y), sf::Color::Black);
              window.draw(&point, 1, sf::Points);

          }
        }
        window.display();
    }

    return 0;
}
