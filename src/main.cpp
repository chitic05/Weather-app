// Weather app.cpp : Defines the entry point for the application.
//

#include <nlohmann/json.hpp>
#include <SFML/Window.hpp>
#include <TGUI/TGUI.hpp>
#include <TGUI/Backend/SFML-Graphics.hpp>
#include "textbox.h"
#include "api.h"
using namespace std;

int scene = 0;
std::string API_KEY = "22e0e7bff53d4cd4bd8140117250902";
std::string city;
nlohmann::json city_stats;
int main()
{
    

	sf::RenderWindow window(sf::VideoMode(600, 600), "Weather App", sf::Style::Close | sf::Style::Titlebar);
    tgui::Gui search_window(window);
    tgui::Gui stats_window(window);
    
    //Stats window

    auto panel = tgui::Panel::create({ 200, 50 });
    panel->getRenderer()->setBorders({ 2, 2, 2, 2 });  // Border thickness
    panel->getRenderer()->setBorderColor(tgui::Color::Black);
    panel->setPosition(200, 100);
    stats_window.add(panel);

    auto city_name = tgui::Label::create();
    city_name->setSize(200, 50);
    city_name->setTextSize(30);
    city_name->setPosition(300-100, 100);
    city_name->getRenderer()->setBorderColor(tgui::Color::Black);
    city_name->setVerticalAlignment(tgui::VerticalAlignment::Center);
    city_name->setHorizontalAlignment(tgui::HorizontalAlignment::Center);
    stats_window.add(city_name);

    auto grid = tgui::Grid::create();
    stats_window.add(grid);

    // Set the grid's position
    grid->setPosition(200, 150);

    auto back_button = tgui::Button::create("BACK");
    back_button->setSize(100, 25);
    back_button->setTextSize(30);
    back_button->setPosition(0, 0);
    back_button->onClick([&]() {
        scene = 0;
        });
    stats_window.add(back_button);

    //Search Window
    auto textBox = tgui::TextArea::create();
    textBox->setSize(200, 50);
    textBox->setTextSize(30);
    textBox->setPosition(300 - 100, 300 - 50 - 150);
    textBox->getRenderer()->setBackgroundColor(tgui::Color::Blue);
    textBox->getRenderer()->setTextColor(tgui::Color::White);
    search_window.add(textBox);

    auto button = tgui::Button::create("Hit me");
    button->setSize(100, 100);
    button->setPosition(300 - 50, 300 - 50);
    button->onClick([&](){
        city_stats = search_city(API_KEY, textBox->getText().toStdString()); 
        if (city_stats.contains("location") && city_stats.contains("current")){
            scene = 1;
            city_name->setText(city_stats["location"]["name"].get<std::string>());

            float temp = city_stats["current"]["temp_c"].get<float>();
            std::ostringstream temp_stream;
            temp_stream << std::fixed << std::setprecision(1) << temp;

            grid->addWidget(tgui::Label::create("Temperature"), 0, 0);
            grid->addWidget(tgui::Label::create(temp_stream.str() + "C"), 0, 1);
        }

        textBox->setText("");
        });
    search_window.add(button);

    


    while (window.isOpen())
    {
        std::cout << "Scene: " << scene << std::endl;

        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

            if (scene == 0)
                search_window.handleEvent(event);
            else if (scene == 1)
                stats_window.handleEvent(event);
        }

        window.clear(sf::Color::White);

        switch (scene)
        {
        case 0:
            search_window.draw();
            break;

        case 1:
            stats_window.draw();
            break;
        }

        window.display();
    }

	return 0;
}