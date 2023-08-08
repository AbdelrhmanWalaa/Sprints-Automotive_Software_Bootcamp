/**
 * @Title      	: Card Module
 * @Filename   	: card.c
 * @Authors     : Mahmoud Mowafey, Hossam Elwahsh
 * @Origin Date	: Mar 28, 2023
 * @Version		: 1.0.0
 * @Compiler	: MinGW
 * @Target     	: General Purpose Processor / PCs
 * @Notes		: The code is written with ANSI_C Standard.
 *
 * THIS SOFTWARE IS PROVIDED BY HACKER KERMIT- TEAM_1 at Sprints_Automotiv_BC_W11.
 *
 *
 */

/* Application */
#include "app.h"

/*
 Name: appStart
 Input: void
 Output: void
 Description: This function will be called by main to start the program.
*/
void appStart(void)
{
    /* Variables to be used */
    ST_cardData_t     cardData;
    ST_terminalData_t terminalData;
    ST_transaction_t  currentTransaction;

    uint8_t Loc_UserInput;

    /* Set Terminal max Amount */
    setMaxAmount(&terminalData, 4000.0f);

    /* Start of program */

    /* Print out message: Starting the program */
    systemPrintOut((uint8_t *)" Starting the program....");
    /* Print out message: Welcome */
    systemPrintOut((uint8_t *)"\t\tWelcome!");

    while (1)
    {   
        /* Initialize Arrays with NULL character */
        memset(cardData.cardHolderName, '\0', 25);
        memset(cardData.primaryAccountNumber, '\0', 20);
        memset(cardData.cardExpirationDate, '\0', 6);
        memset(terminalData.transactionDate, '\0', 11);

        /* Clear Buffer */
        fflush(stdin);

        printf("\n\n");
        printf("\t\t  -VBS-\n\t Virtual Banking System");
        printf("\n\n");

        /* Get Card Data */
        printf("\n\n");
        printf(" Insert Card Data");
        printf("\n\n");

        /* Loop: Until user enters correct Name */
        while (getCardHolderName(&cardData) == WRONG_NAME)
        {
            systemDeleteLine((uint8_t *)" Error! Wrong Name!");
        }

        /* Loop: Until user enters correct Expiration Date */
        while (getCardExpiryDate(&cardData) == WRONG_EXP_DATE)
        {
            systemDeleteLine((uint8_t *)" Error! Wrong Expiration Date!");
        }

        /* Loop: Until user enters correct PAN */
        while (getCardPAN(&cardData) == WRONG_PAN)
        {
            systemDeleteLine((uint8_t *)" Error! Wrong PAN!");
        }

        /* Print out message: Processing */
        systemPrintOut((uint8_t *)" Processing....");

        printf("\n\n");
        printf("\t\t  -VBS-\n\t Virtual Banking System");
        printf("\n\n");

        printf("\n\n");
        printf(" Welcome %s", cardData.cardHolderName);
        printf("\n\n");

        /* Loop: Until user enters correct Transaction Date */
        while (getTransactionDate(&terminalData) == WRONG_DATE)
        {
            systemDeleteLine((uint8_t *)" Error! Wrong Transaction Date!");
        }

        printf(" Max withdrawal amount:\t%0.2f\n", terminalData.maxTransAmount);

        /* Get Terminal Data */

        /* Check 1: Card is Expired */
        if (isCardExpired(&cardData, &terminalData) == EXPIRED_CARD)
        {
            /* Print out error: Expired Card */
            systemPrintOut((uint8_t *)" Error! Expired card, Transaction Declined.");
        }
        /* Check 2: Card is not Expired */
        else
        {
            /* Loop: Until user enters valid Amount */
            while (getTransactionAmount(&terminalData) == INVALID_AMOUNT)
            {
                systemDeleteLine((uint8_t *)" Error! Wrong Amount!");
            }

            /* Check 2.1: User enters Amount exceeds Terminal Max Amount */
            if (isBelowMaxAmount(&terminalData) == EXCEED_MAX_AMOUNT)
            {
                /* Print out error: Exceed Max Amount */
                systemPrintOut((uint8_t *)" Error! Exceed Max Amount!");
            }
            /* Check 2.2: User enters Amount does not exceed Max Amount */
            else
            {
                /* Print out message: Processing */
                systemPrintOut((uint8_t *)" Processing....");

                /* Save the current card data in the current Transaction structure */
                currentTransaction.cardHolderData = cardData;
                /* Save the current terminal data in the current Transaction structure */
                currentTransaction.terminalData = terminalData;

                uint8_t currentState = recieveTransactionData(&currentTransaction);

                /* Check 2.2.1: Current state of Transaction  */
                /*if(currentState == FRAUD_CARD || currentState == DECLINED_STOLEN_CARD
                || currentState == DECLINED_INSUFFECIENT_FUND)
                {
                    currentTransaction.transState = currentState;
                    saveTransaction(&currentTransaction);
                }*/
                sleep(2);
                switch (currentState)
                {
                    case FRAUD_CARD:
                        /* Print out message: Declined Invalid Account */
                        systemPrintOut((uint8_t *)" Declined Invalid Account!");
                        break;
                    case DECLINED_STOLEN_CARD:
                        /* Print out message: Declined Blocked Account */
                        systemPrintOut((uint8_t *)" Declined Blocked Account!");
                        break;
                    case DECLINED_INSUFFECIENT_FUND:
                        /* Print out message: Declined Insufficient Funds */
                        systemPrintOut((uint8_t *)" Declined Insufficient Funds!");
                        break;
                    case APPROVED:
                        /* Print out message: Approved */
                        systemPrintOut((uint8_t *)" Approved!");
//                        printf("\n Your new balance is %.2f \n", accountsDB[Glb_AccountsDBIndex].balance);
                        break;
                    default:
                    case INTERNAL_SERVER_ERROR:
                        /* Print out message: Internal Server Error */
                        systemPrintOut((uint8_t *)" Internal Server Error!");
                        break;
                }                
            }
        }

        /* Clear Buffer */
        fflush(stdin);

        /* Confirm continue or exit */
        printf("\n\n");
        printf(" Press ANY KEY to continue or X to exit....  ");
        scanf("%c", &Loc_UserInput);

        /* Check 3: User pressed X */
        if (Loc_UserInput == 'X' || Loc_UserInput == 'x')
        {
            /* break while(1) */
            break;
        }

        /* Print out message: Processing */
        systemPrintOut((uint8_t *)" Processing....");
    }

    /* Print out message: Goodbye */
    systemPrintOut((uint8_t *)"\t\tGoodbye!");
    /* Print out message: Exiting the program */
    systemPrintOut((uint8_t *)" Exiting the program....");

    /* End of program */
}

int main()
{
    appStart();
}