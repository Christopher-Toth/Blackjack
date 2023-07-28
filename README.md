# Blackjack Game in C++

This is a command-line implementation of the popular casino card game Blackjack (also known as 21) in C++. The game follows Vegas-style rules and allows you to play multiple hands against the dealer.

## Getting Started

### Prerequisites

You need to have a C++ compiler installed on your system to compile and run this program.

### Compiling the Program

To compile the program, use the following command in your terminal or command prompt:

g++ main.cpp -o blackjack

This will create an executable file named `blackjack` in the current directory.

### Running the Game

After compiling the program, you can run the Blackjack game by executing the `blackjack` executable:

./blackjack

### Gameplay 

The game will display the player's hand and one of the dealer's cards. You'll then be asked to choose an action:

- Enter `1` to "hit" (draw another card) and try to improve your hand's total value.
- Enter `2` to "stand" (keep your current hand) and let the dealer play their hand.

### Winning Conditions

The dealer will draw cards until reaching a total value of at least 17. If the dealer goes over 21, they "bust," and you win. If neither the player nor the dealer busts, the one with the higher total value wins. If both have the same total value, it's a draw.

### Play Again

After each hand, you'll be asked if you want to play another hand. Enter `y` or `Y` to play again or any other key to exit the game.

### Vegas-style Rules

The game follows the standard Vegas-style rules for Blackjack, including:

- The dealer must hit on a soft 17 (a hand with an Ace counted as 11).
- Aces can be counted as either 1 or 11, depending on the player's hand value.
- The player wins if their hand value is closer to 21 than the dealer's hand, or if the dealer busts (goes over 21).

## Contributing

This project is for educational purposes, and contributions are not expected. However, if you find any issues or have suggestions for improvements, feel free to create an issue or submit a pull request.

## Acknowledgments

This Blackjack game is a simple implementation for educational purposes. It is based on the classic card game and follows the standard Vegas-style rules.

Happy gaming!
