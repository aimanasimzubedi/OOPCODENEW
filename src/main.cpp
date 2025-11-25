#include "game.hpp"

int main() {
    Game game(700, 600, "Piano Memory Challenge");
    game.run();
    return 0;
}





// ---------------- Run code below separately to test only the ResultScreen ----------------//

// #include <SFML/Graphics.hpp>
// #include "screens/ResultScreen.hpp"

// int main() {
//     sf::RenderWindow window(sf::VideoMode(700, 600), "Result Screen Test");

//     // Example values:
//     int score = 12345;
//     float accuracy = 92.4f;
//     int combo = 37;

//     ResultScreen result(score, accuracy, combo);

//     while (window.isOpen()) {
//         result.handleEvents(window);
//         result.update();

//         window.clear();
//         result.draw(window);
//         window.display();
//     }

//     return 0;
// }
