#include <stdio.h>

int main() {

    int appleQuantity =23;
    double applePrice = 1.49;
    int appleReviewDisplay =82.5;
    const char appleLocation ='F';
    // Put all your code above this and if you declare your variables using the given names and types there is no need to change any of the code below.
    printf("An apple costs: $%.2f, there are %d in inventory found in section: %c and your customers gave it an average review of %d%%!", applePrice, appleQuantity, appleLocation, appleReviewDisplay);

}