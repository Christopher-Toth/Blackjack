#include <iostream>
#include <vector>
#include <string>
#include <random>
#include <ctime>

enum class Rank {
    Ace = 1,
    Two, Three, Four, Five, Six, Seven, Eight, Nine, Ten,
    Jack, Queen, King
};

enum class Suit {
    Clubs, Diamonds, Hearts, Spades
};

struct Card {
    Rank rank;
    Suit suit;
};

// Get the value of a card
int getCardValue(const Card& card) {
    switch (card.rank) {
        case Rank::Ace:
            return 11;
        case Rank::Two:
            return 2;
        case Rank::Three:
            return 3;
        case Rank::Four:
            return 4;
        case Rank::Five:
            return 5;
        case Rank::Six:
            return 6;
        case Rank::Seven:
            return 7;
        case Rank::Eight:
            return 8;
        case Rank::Nine:
            return 9;
        case Rank::Ten:
        case Rank::Jack:
        case Rank::Queen:
        case Rank::King:
            return 10;
    }
    return 0;  // Should never happen
}

// Print a card
void printCard(const Card& card) {
    std::string rankString;
    switch (card.rank) {
        case Rank::Ace:
            rankString = "Ace";
            break;
        case Rank::Two:
            rankString = "2";
            break;
        case Rank::Three:
            rankString = "3";
            break;
        case Rank::Four:
            rankString = "4";
            break;
        case Rank::Five:
            rankString = "5";
            break;
        case Rank::Six:
            rankString = "6";
            break;
        case Rank::Seven:
            rankString = "7";
            break;
        case Rank::Eight:
            rankString = "8";
            break;
        case Rank::Nine:
            rankString = "9";
            break;
        case Rank::Ten:
            rankString = "10";
            break;
        case Rank::Jack:
            rankString = "Jack";
            break;
        case Rank::Queen:
            rankString = "Queen";
            break;
        case Rank::King:
            rankString = "King";
            break;
    }

    std::string suitString;
    switch (card.suit) {
        case Suit::Clubs:
            suitString = "Clubs";
            break;
        case Suit::Diamonds:
            suitString = "Diamonds";
            break;
        case Suit::Hearts:
            suitString = "Hearts";
            break;
        case Suit::Spades:
            suitString = "Spades";
            break;
    }

    std::cout << rankString << " of " << suitString;
}

// Print a hand
void printHand(const std::vector<Card>& hand) {
    for (const Card& card : hand) {
        printCard(card);
        std::cout << ", ";
    }
    std::cout << "\n";
}

// Deal a card to a hand from the deck
void dealCard(std::vector<Card>& hand, std::vector<Card>& deck) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dist(0, deck.size() - 1);
    int index = dist(gen);
    Card card = deck[index];
    hand.push_back(card);
    deck.erase(deck.begin() + index);
}

// Calculate the value of a hand
int calculateHandValue(const std::vector<Card>& hand) {
    int value = 0;
    int numAces = 0;

    for (const Card& card : hand) {
        value += getCardValue(card);
        if (card.rank == Rank::Ace) {
            numAces++;
        }
    }

    while (value > 21 && numAces > 0) {
        value -= 10;
        numAces--;
    }

    return value;
}

// Check if a hand is a soft 17 (Ace + 6)
bool isSoft17(const std::vector<Card>& hand) {
    if (hand.size() != 2) {
        return false;
    }

    int totalValue = calculateHandValue(hand);
    if (totalValue == 17) {
        int numAces = 0;
        for (const Card& card : hand) {
            if (card.rank == Rank::Ace) {
                numAces++;
            }
        }
        if (numAces == 1) {
            return true;
        }
    }

    return false;
}

int main() {
    std::vector<Card> deck;
    for (int rank = 1; rank <= 13; rank++) {
        for (int suit = 0; suit < 4; suit++) {
            deck.push_back({ static_cast<Rank>(rank), static_cast<Suit>(suit) });
        }
    }

    std::random_device rd;
    std::mt19937 gen(rd());

    while (true) {
        // Shuffle the deck
        std::shuffle(deck.begin(), deck.end(), gen);

        std::vector<Card> playerHand;
        std::vector<Card> dealerHand;

        // Deal initial cards
        dealCard(playerHand, deck);
        dealCard(dealerHand, deck);
        dealCard(playerHand, deck);
        dealCard(dealerHand, deck);

        // Print player's and dealer's hands
        std::cout << "Player's hand: ";
        printHand(playerHand);
        std::cout << "Dealer's hand: ";
        printCard(dealerHand[0]);
        std::cout << ", [Hidden]\n";

        bool playerBust = false;

        while (true) {
            // Ask player for action
            std::cout << "Choose an action: (1) Hit, (2) Stand: ";
            int choice;
            std::cin >> choice;

            if (choice == 1) {
                // Player chooses to hit
                dealCard(playerHand, deck);
                std::cout << "Player's hand: ";
                printHand(playerHand);

                // Check if player busts
                int playerValue = calculateHandValue(playerHand);
                if (playerValue > 21) {
                    std::cout << "Bust! You lose.\n";
                    playerBust = true;
                    break;
                }
            }
            else if (choice == 2) {
                // Player chooses to stand
                while (true) {
                    // Dealer hits until reaching a non-soft 17
                    std::cout << "Dealer's hand: ";
                    printHand(dealerHand);

                    int dealerValue = calculateHandValue(dealerHand);

                    if (dealerValue >= 17 && !isSoft17(dealerHand)) {
                        break;
                    }

                    std::cout << "Dealer hits.\n";
                    dealCard(dealerHand, deck);
                }

                std::cout << "Dealer's final hand: ";
                printHand(dealerHand);

                // Compare dealer's and player's hands to determine the winner
                int dealerValue = calculateHandValue(dealerHand);
                int playerValue = calculateHandValue(playerHand);

                if (dealerValue > 21 || dealerValue < playerValue) {
                    std::cout << "You win!\n";
                }
                else if (dealerValue > playerValue) {
                    std::cout << "You lose.\n";
                }
                else {
                    std::cout << "It's a draw.\n";
                }

                break;
            }
        }

        std::cout << "Do you want to play another hand? (y/n): ";
        char playAgain;
        std::cin >> playAgain;

        if (playAgain != 'y' && playAgain != 'Y') {
            break;
        }
    }

    return 0;
}