#include <SFML/Graphics.hpp>
#include <complex>
#include <iostream>

using namespace sf;

int video_x=300,video_y=300;
RenderWindow window(VideoMode(video_x, video_y), "Maldenbrod");
double iter = 20;
double zoom = 1;
double x_start = -2,x_end = 1;
double y_start = -1,y_end = 1;
bool draw;

void Malder()
{
    for(double x = 0.0; x< video_x;x++)
    {
      for(double y = 0.0; y < video_y;y++)
      {
          double size_x = x_end - x_start;
          double size_y = y_end - y_start;
          draw = true;
          std::complex<double> c( (x_start+(x/video_x)*size_x)/zoom, (y_start+(y/video_y)*size_y)/zoom);
          std::complex<double> z1( 0, 0);
          std::complex<double> z2( 0, 0);
          std::complex<double> z( 0, 0);
          for(int n = 0; n < iter;n++)
          {
            z = z2;
            z2 = (-(z2*z2) + z1*z1  + c);
            z1 = z;
            if(std::abs(z2) >= 2)
            {
                sf::Vertex point(sf::Vector2f(x, y), sf::Color(250-n*12,250-n*10,n*3));
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
int main()
{
    while (window.isOpen())
    {
        window.clear(Color(250,250,250,0));
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
                window.close();
            if(Keyboard::isKeyPressed(Keyboard::Up))
            {
                y_start -= 0.1;
                y_end -= 0.1;
            }
            if(Keyboard::isKeyPressed(Keyboard::Down))
            {
                y_start += 0.1;
                y_end += 0.1;
            }
            if(Keyboard::isKeyPressed(Keyboard::Left))
            {
                x_start -= 0.1;
                x_end -= 0.1;
            }
            if(Keyboard::isKeyPressed(Keyboard::Right))
            {
                x_start += 0.1;
                x_end += 0.1;
            }
            if(Keyboard::isKeyPressed(Keyboard::Z))
            {
                zoom += 0.1;
            }
            if(Keyboard::isKeyPressed(Keyboard::X))
            {
                zoom -= 0.1;
            }
            if(Keyboard::isKeyPressed(Keyboard::C))
            {
                Malder();
            }
        }
    }

    return 0;
}
