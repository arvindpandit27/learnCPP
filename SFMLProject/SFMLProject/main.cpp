#include <SFML/Graphics.hpp.>
using namespace sf;
int main(int argc, char** argv) {
    sf::RenderWindow renderWindow(sf::VideoMode(800, 800 ), "Chowka Bhaara");

    sf::Event event;

    sf::CircleShape square(100, 4);
    sf::RectangleShape sq(Vector2f{100,100});
    square.setRotation(45);
    //sf::vertex line[] =
    //{
    //   sf::vertex(sf::vector2f(10,160)),
    //   sf::vertex(sf::vector2f(100,250)),
    //    //sf::vertex(sf::vector2f(10,k))
    //};
  
    //sf::VertexArray lines(sf::LineStrip, 4);
    //lines[0].position = sf::Vector2f(100, 150);
    //lines[1].position = sf::Vector2f(200, 50);
    //lines[2].position = sf::Vector2f(300, 250);
    //lines[3].position = sf::Vector2f(400, 50);
    
    //sf::VertexArray lines(sf::LineStrip, 6);
    //for (int i = 0; i < 6; i++)
    //{
    //    if(i%2 == 0)
    //    { 
    //        lines[i].position = sf::Vector2f(i * 50 + 100, 150);
    //    }
    //    else
    //    {
    //        lines[i].position = sf::Vector2f(i * 50 + 100, 50);
    //    }

    //}


    //circleShape.setFillColor(sf::Color::Blue);

    while (renderWindow.isOpen()) {
        while (renderWindow.pollEvent(event)) {
            if (event.type == sf::Event::EventType::Closed)
                renderWindow.close();
        }
        renderWindow.clear();

        for (int i = 0; i < 5; i++) {
            for (int j = 0; j < 5; j++) {
                if (  ( (i % 2 == 0) && (j % 2 != 0) )  || ( (i % 2 != 0) && (j % 2 == 0) ) ){
                    sq.setFillColor(sf::Color(255,0,0));
                }
                else {
                    sq.setFillColor(sf::Color(0, 255, 255));
                }
               
               sq.setPosition({ (float) (100*i+100), (float)(100.0*j + 100)});
             renderWindow.draw(sq);

             // renderwindow.draw(line ,2, sf::lines);
            }
        }
       // line->a = 10;
      // renderWindow.draw(line, 2, sf::Lines); 
       // renderWindow.draw(lines);//Chetan
        //circleShape.setPosition({ 0,500 });
        //renderWindow.draw(circleShape);
        //rectShape.setPosition({ 0,100 });
        //renderWindow.draw(rectShape);
        //renderWindow.draw(triangle);
        //renderWindow.draw(square);
        renderWindow.display();
    }
}