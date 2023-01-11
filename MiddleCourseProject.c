
#include <stdio.h>
#include <conio.h>
#include <time.h>
#include <stdlib.h>
#include <stdbool.h>

#define STOP_PLAYING 'n'
#define CONTINUE_PLAYING 'y'
#define HIGHEST_DIGIT 6
#define LOWEST_DIGIT 1
#define HIGEST_RANDOM_NUMBER_POSSIBLE 6543
#define lOWEST_RANDOM_NUMBER_POSSIBLE 1234
#define EASY_ROUNDS 20
#define MODERATE_ROUNDS 15
#define HARD_ROUNDS 10
#define HIGHEST_ROUNDS_FOR_CRAZY 25
#define LOWEST_ROUNDS_FOR_CRAZY 5

typedef enum {Easy = 1 , Moderate ,  Hard , Crazy}gameLevel;

bool isAllFourDigitsValid(int number);
bool isDigitNotRepeatedInNumber(int number);
int randomCreditCardNumber(void);
gameLevel getDifficultyChoice(void);
int crazyDifficultyRounds(void);
int digitCharToInt(void);
int getNumberFromUserWithoutEnter(void);
void askUserForInput(gameLevel choice , int rounds);
void hitsAndMissesInUserNumber(int userNumber , int creditNumber);
void welcome(void);
void rules(void);
void difficultyOptions(void);
void loseMessage(void);

int main()
{
    int creditNumber = 0;
    int rounds = 0;
    int userNumber = 0;
    int roundsTaken = 0;
    bool isWon = 0;
    char play = CONTINUE_PLAYING;
    printf("Welcome to my Midldle C course project\n");
    printf("Made by : Shon Gutman\n");
    while(STOP_PLAYING != play) //player will play until he enters 'n' at the end of the game
    {
        creditNumber = randomCreditCardNumber(); //generating the random credit card for the game
        welcome();
        rules();
        difficultyOptions();
        gameLevel userDifficultyChoice = getDifficultyChoice();
        if(userDifficultyChoice == Crazy)
        {
            rounds = crazyDifficultyRounds();
        }
        else
        {
            switch(userDifficultyChoice)
            {
                case Easy:
                    rounds = EASY_ROUNDS;
                    break;
                case Moderate:
                    rounds = MODERATE_ROUNDS;
                    break;
                case Hard:
                    rounds = HARD_ROUNDS;
                    break;
                default:
                    printf("Something went wront\n");
                    break;
            }
        }
    
        while(rounds != 0) //we begin the game
        {
            roundsTaken++;
            askUserForInput(userDifficultyChoice , rounds);
            userNumber = getNumberFromUserWithoutEnter();
            while(isAllFourDigitsValid(userNumber) == 0) //while user number isn't with all digits between 1 - 6
            {
                printf("Only 1-6 are allowed, try again!\n");
                askUserForInput(userDifficultyChoice , rounds);
                userNumber = getNumberFromUserWithoutEnter();
            }
            //second bonus , if user enter number with repeated dont tell him the problem , just don't take round from him
            while(isDigitNotRepeatedInNumber(userNumber) == 0) 
            {
                askUserForInput(userDifficultyChoice , rounds);
                userNumber = getNumberFromUserWithoutEnter();
                while(isAllFourDigitsValid(userNumber) == 0) //while user number isn't with all digits between 1 - 6
                {
                    printf("Only 1-6 are allowed, try again!\n");
                    askUserForInput(userDifficultyChoice , rounds);
                    userNumber = getNumberFromUserWithoutEnter();
                }
            }
            if(userNumber == creditNumber)
            {
                printf("   4 HITS YOU WON!!!\n\n");
                printf("It took you only %d guesses, you are a professional code breaker!\n" , roundsTaken);
                isWon = 1;
                rounds = 0;
            }
            else
            {
            hitsAndMissesInUserNumber(userNumber , creditNumber);
            rounds--;
            }
            
        }
        if(isWon == 0) 
        {
            loseMessage();
            printf("The secret password was %d\n" , creditNumber);
        }
        do
        {
            printf("\nWould you like to play again? (y/n): ");
            play = getche();
        }
        while(play != STOP_PLAYING && play != CONTINUE_PLAYING);
        roundsTaken = 0;
        isWon = 0;
    }
    
    printf("\nBye Bye!\n");
    

    return 0;
}

/*function will check if all digits in number are between 1 - 6
input - number
output - 1 - if all between 1 - 6 and 0 if not
*/

bool isAllFourDigitsValid(int number)
{
    bool fourLettersOk = 1;
    int countDigits = 0;
    while(number > 0)
    {
        if((number % 10) < LOWEST_DIGIT || (number % 10) > HIGHEST_DIGIT)
        {
            fourLettersOk = 0;
        }
        number /= 10;
        countDigits++;
    }
    if(countDigits != 4) //we need only 4 digits number in this project
    {
        fourLettersOk = 0;
    }
    return fourLettersOk;
}

/*function will check if digit in number are not repeated 
input - number
output - 1 - if it is not repeated and 0 if it does
*/

bool isDigitNotRepeatedInNumber(int number)
{
    bool isDigitNotRepeated = 1;
    int digit = 0;
    while(number > 0) //runnig on all digits of number
    {
        digit = number % 10; 
        int temp = number / 10; //temp is equal to number / 10 because we want to run on all remaining digits
        while(temp > 0) //runing on all remaining digits
        {
            if(digit == temp % 10) //comparing the taken digit to all remaining digits of number
            {
                isDigitNotRepeated = 0;
            }
            temp /= 10;
        }
        number /= 10;
    }
    return isDigitNotRepeated;
}

/*function will get random number and will check until all its digits are between 1 - 6 and not repeated 
input - NONE
output - the random number
*/

int randomCreditCardNumber()
{
    srand(time(NULL));
    bool isRandomNumberFine = 0;
    int random = 0;
    while(isRandomNumberFine == 0)
    {
        //number should be with all digits between 1 - 6 and none reapeted , for example : 1436
        int temp = rand() % (HIGEST_RANDOM_NUMBER_POSSIBLE - lOWEST_RANDOM_NUMBER_POSSIBLE + 1) + lOWEST_RANDOM_NUMBER_POSSIBLE;
        random = temp;
        if(isAllFourDigitsValid(temp) == 1 && isDigitNotRepeatedInNumber(temp) == 1)
        {
            isRandomNumberFine = 1;
        }
    }
    return random;
}

/*function will get the user choice about difficulty until its valid
input - NONE
output - the choice
*/

gameLevel getDifficultyChoice()
{
    gameLevel choice = 0;
    do
    {
    printf("Make a choice: ");
    scanf("%d" , &choice);
    }
    while(choice < Easy || choice > Crazy);
    getchar(); //clear buffer
    return choice;
}

/*function will roll the rounds for crazy difficulty
input - NONE
output - amount of rounds for crazy difficulty
*/

int crazyDifficultyRounds()
{
    srand(time(NULL));
    int rounds = rand() % (HIGHEST_ROUNDS_FOR_CRAZY - LOWEST_ROUNDS_FOR_CRAZY + 1) + LOWEST_ROUNDS_FOR_CRAZY;
    return rounds;
}

/*function will turn digit char to digit for example char '7' will turn to int 7
input - NONE
output - the digit as int
*/

int digitCharToInt()
{
   char digitChar = getche();
   int digit = (int)(digitChar - 48);
   return digit;
}

/*function will get four digits of four digits number and than build the number
input - NONE
output - the number
*/

int getNumberFromUserWithoutEnter()
{
    int thousends = digitCharToInt();
    int hundreds = digitCharToInt();
    int tens = digitCharToInt();
    int units = digitCharToInt();
    printf("\n");
    int number = thousends * 1000 + hundreds * 100 + tens * 10 + units;
    return number;
}

/*function will print and ask for input from user
input - the gameLevel of the player and the amount of round he has left
output - NONE
*/

void askUserForInput(gameLevel choice , int rounds)
{
        printf("\nWrite your guess (only 1-6, no ENTER is needed)\n");
        if(choice == Crazy)
        {
            printf("CRAZY MODE!!!\n");
        }
        else
        {
            printf("%d guesses left\n" , rounds);
        }
}

/*function will print the amount of hits and misses of userNumber in the creditCard number
input - userNumber and the creditCard number
output - NONE
*/

void hitsAndMissesInUserNumber(int userNumber , int creditNumber)
{
    int hits = 0;
    int misses = 0;
    int digit = 0;
    int temp = 0;
    int i = 1;
    int j = 1;
    for(i = 1; i<=4; i++) // i is for the place of digit in user number
    {
        digit = userNumber % 10;
        temp = creditNumber;
        for(j = 1; j <= 4; j++) // j is for the place of digit in credit number
        {
            if(digit == (temp % 10) && i == j) //it's a hit. same digit at same place
            {
                hits++;
            }
            else if(digit == (temp % 10))//it's a miss. digit apears but not in right spot
            {
                misses++;
            }
            temp /= 10;
        }
        userNumber /=10;
    }
        printf("You got    %d HITS    %d MISSES.\n" , hits , misses);
    }

/*function will print a welcome and quick instruction of the game
input - NONE
output - NONE
*/

void welcome()
{
    printf("\nWelcome to \"MAGSHIMIM CODE-BREAKER\"!!!\n\n");
    printf("A secret password was chosen to protect the credit card of Pancratius,\n");
    printf("the descendant of Antiochus.\n");
    printf("Your mission is to stop Pancratius by revealing his secret password.\n\n");
}

/*function will print all the rules of the game
input - NONE
output - NONE
*/

void rules()
{
    printf("The rules are as follows:\n");
    printf("1. In each round you try to guess the secret password (4 distinct digits)\n");
    printf("2. After every guess you'll receive two hints about the password\n");
    printf("   HITS:   The number of digits in your guess which were exactly right.\n");
    printf("   MISSES: The number of digits in your guess which belongs to\n");
    printf("           the password but were miss-placed.\n");
    printf("3. If you'll fail to guess the password after a certain number of rounds\n");
    printf("   Pancratius will buy all the gifts for Hanukkah!!!\n");
}

/*function will print all the difficulty options to the player
input - NONE
output - NONE
*/

void difficultyOptions()
{
    printf("\nPlease choose the game level:\n");
    printf("1 - Easy (20 rounds)\n");
    printf("2 - Moderate (15 rounds)\n");
    printf("3 - Hard (10 rounds)\n");
    printf("4 - Crazy (random number of rounds 5-25)\n");
}

/*function will print losing message
input - NONE
output - NONE
*/

void loseMessage()
{
    printf("\n\nOOOOHHHH!!! Pancratius won and bought all of Hanukkah's gifts.\n");
    printf("Nothing left for you...\n");
    //printing lion - first bonus
    printf("               .,  ,.                       ,.\n");
    printf("              ,((')/))).                    (()\n");
    printf("             '(.(()( )\")),                ((())\n");
    printf("          \"___/,  \"/)))/).'               .))\n");
    printf("           '.-.   \"(()(()()/^             ( (\n");
    printf(" >> ROAR << ' _)   /)()())(()'______.---._.' )\n");
    printf("            '.   _  (()(()))..            ,'\n");
    printf("               (() \  ()) ())(             )\n");
    printf("                   ((                .     /_\n");
    printf("                  /       \,     .-(     (_ )\n");
    printf("               .'   \/    )___.'   \      )\n");
    printf("              /    \-    /        _/'.-'  /\n");
    printf("              (,(,.'     ))       (_ /    /\n");
    printf("                  (,(,(,_)mrf      (,(,(,_)\n");
}