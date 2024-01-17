#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

// Function to generate a random number between min and max
int getRandomNumber(int min, int max) {
    static const double fraction = 1.0 / (RAND_MAX + 1.0);
    return min + static_cast<int>((max - min + 1) * (rand() * fraction));
}

// Function to get the value of a card
int getCardValue(int card) {
    switch(card) {
        case 1: // Ace
            return 11;
        case 11: // Jack, Queen, King
        case 12:
        case 13:
            return 10;
        default:
            return card;
    }
}

// Function to display the cards in hand
void displayHand(const int* hand, int numCards) {
    cout << "Cards in hand: ";
    for (int i = 0; i < numCards; ++i) {
        cout << hand[i] << " ";
    }
    cout << endl;
}

// Function to calculate the total value of cards in hand
int calculateTotal(const int* hand, int numCards) {
    int total = 0;
    int numAces = 0;

    for (int i = 0; i < numCards; ++i) {
        total += getCardValue(hand[i]);

        if (hand[i] == 1) {
            numAces++;
        }
    }

    // Adjust for Aces if needed
    while (total > 21 && numAces) {
        total -= 10;
        numAces--;
    }

    return total;
}

int main() {
    srand(static_cast<unsigned int>(time(0)));

    const int deckSize = 52;
    int deck[deckSize];

    for (int i = 0; i < deckSize; ++i) {
        deck[i] = i % 13 + 1;
    }

    // Shuffle the deck
    for (int i = 0; i < deckSize; ++i) {
        int swapIndex = getRandomNumber(0, deckSize - 1);
        swap(deck[i], deck[swapIndex]);
    }

    int playerHand[10];
    int dealerHand[10];

    int playerNumCards = 0;
    int dealerNumCards = 0;

    // Initial deal
    playerHand[playerNumCards++] = deck[--deckSize];
    dealerHand[dealerNumCards++] = deck[--deckSize];
    playerHand[playerNumCards++] = deck[--deckSize];
    dealerHand[dealerNumCards++] = deck[--deckSize];

    // Display initial cards
    cout << "Welcome to Blackjack!" << endl;
    displayHand(playerHand, playerNumCards);
    cout << "Total: " << calculateTotal(playerHand, playerNumCards) << endl;

    // Player's turn
    while (true) {
        char choice;
        cout << "Do you want to hit (h) or stand (s)? ";
        cin >> choice;

        if (choice == 'h') {
            playerHand[playerNumCards++] = deck[--deckSize];
            displayHand(playerHand, playerNumCards);
            cout << "Total: " << calculateTotal(playerHand, playerNumCards) << endl;

            if (calculateTotal(playerHand, playerNumCards) > 21) {
                cout << "Bust! You lose." << endl;
                return 0;
            }
        } else if (choice == 's') {
            break;
        }
    }

    // Dealer's turn
    while (calculateTotal(dealerHand, dealerNumCards) < 17) {
        dealerHand[dealerNumCards++] = deck[--deckSize];
    }

    // Display final hands
    cout << "\nFinal hands:" << endl;
    cout << "Your hand: ";
    displayHand(playerHand, playerNumCards);
    cout << "Total: " << calculateTotal(playerHand, playerNumCards) << endl;

    cout << "Dealer's hand: ";
    displayHand(dealerHand, dealerNumCards);
    cout << "Total: " << calculateTotal(dealerHand, dealerNumCards) << endl;

    // Determine the winner
    int playerTotal = calculateTotal(playerHand, playerNumCards);
    int dealerTotal = calculateTotal(dealerHand, dealerNumCards);

    if (playerTotal > dealerTotal || dealerTotal > 21) {
        cout << "You win!" << endl;
    } else if (playerTotal < dealerTotal) {
        cout << "You lose." << endl;
    } else {
        cout << "It's a tie!" << endl;
    }

    return 0;
}
