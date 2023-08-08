/**
 * @Title      	: Terminal Module
 * @Filename   	: terminal.c
 * @Author     	: Mahmoud Mowafey
 * @Origin Date	: Mar 29, 2023
 * @Version		: 1.0.0
 * @Compiler	: MinGW
 * @Target     	: General Purpose Processor / PCs
 * @Notes		: The code is written with ANSI_C Standard.
 *
 * THIS SOFTWARE IS PROVIDED BY HACKER KERMIT- TEAM_1 at Sprints_Automotiv_BC_W11.
 *
 *
 */

/* ********************** Includes Section Start ********************** */

/* Terminal Module */
#include"terminal.h"

/* ********************** Includes Section End   ********************** */



/* ********************** Main Terminal Functions Start ******************************************** */

 /*
 * @author         : Tarek Gohry
 * @brief          : Get transaction date and store it in terminal data
 * Description     :
    - This function takes a reference to a structure or terminal data
    - Get transaction date
 * Return          :
    - WRONG_DATE ERROR if transaction date is NULL or < 10 characters or Wrong format
    - TERMINAL_OK otherwise
 */

 EN_terminalError_t getTransactionDate(ST_terminalData_t *termData)
 {
    uint8_t day;
    uint8_t month;
    uint16_t year;

    time_t t = time(NULL);
    struct tm tm = *localtime(&t);

    sprintf((char *) termData->transactionDate, "%02d/%02d/%04d", tm.tm_mday, tm.tm_mon + 1, tm.tm_year + 1900);

    printf(" Current date:\t\t%s\n", termData->transactionDate);

    /* Validate Date Length*/
    if(strlen((char *)termData->transactionDate) != 10)
    {
        return WRONG_DATE;
    }

    /* Validate Date Format */
    if(termData->transactionDate[2] != '/' || termData->transactionDate[5] != '/')
    {
        return WRONG_DATE;
    }

    /* Validate Day */
    day = termData->transactionDate[0] - '0';
    day = (day*10) + (termData->transactionDate[1] - '0');

    if(day<1 || day>31)
    {
        return WRONG_DATE;
    }

    /* Validate Month */
    month = termData->transactionDate[3] - '0';
    month = (month*10) + (termData->transactionDate[4] - '0');

    if(month<1 || month>12)
    {
        return WRONG_DATE;
    }

    if(month==2 && day>29)
    {
        return WRONG_DATE;
    }

    /* Validate Year */
    year = termData->transactionDate[6] - '0';
    year = (year*10) + (termData->transactionDate[7] - '0');
    year = (year*10) + (termData->transactionDate[8] - '0');
    year = (year*10) + (termData->transactionDate[9] - '0');

    if(year<1900 || year>2100)
    {
        return WRONG_DATE;
    }

    return TERMINAL_OK;
 }


/**
 * @author Hossam Elwahsh
 * This function takes the maximum allowed amount and stores it into terminal data
 * Note:
 * - Transaction max amount is a float number 
 * 
 * @param termData [in,out] terminal data
 * @param maxAmount [in] max transaction amount
 * 
 * @return INVALID_MAX_AMOUNT if max amount is less than or equal zero
 * @return TERMINAL_OK otherwise
 */
EN_terminalError_t setMaxAmount(ST_terminalData_t *termData, float maxAmount)
{
    if (maxAmount > 0) {
        termData->maxTransAmount = maxAmount;
        return TERMINAL_OK;
    } else {
        return INVALID_MAX_AMOUNT;
	}
}


/************************************************************************************************************
 * Function : getTransactionAmount()
 *//**
 * Description:
 * @Author     	: Mahmoud Mowafey
 * This function is used to test the getTransactionAmount(ST_terminalData_t *termData) function, to validate the terminal data.
 *
 *
 * @param [in]		termData is a pointer to the ST_terminalData_t structure that holding data
 * 					about the terminal such as transAmount, maxTransAmount, transactionGate.
 *
 * @return 			EN_terminalError_t is a enumeration that contains terminal module errors.
 *
 * \b Example:
 * @code
 *
 * EN_terminalError_t getTransactionAmount(ST_terminalData_t *termData);
 *
 * @endcode
 *
 * @see getCardHolderNameTest()
 *
 *************************************************************************************************************************************/
EN_terminalError_t getTransactionAmount(ST_terminalData_t *termData)
{
    printf("\nEnter the amount for transaction: \t");
    fflush(stdin);
    fflush(stdout);

    float number;
    char *endptr;
    char input[20] = {'\0'};
    fgets(input, sizeof(input), stdin);
    // remove trailing newline from string
    char* ptr = strchr(input, '\n');
    if (ptr) *ptr = '\0';

    number = strtof(input, &endptr);
    if (endptr == input || *endptr != '\n') {
        if (number <= 0.0) {
            return INVALID_AMOUNT;
        } else {
            termData->transAmount = number;
            return TERMINAL_OK;
        }
    } else {
        return TERMINAL_OK;
    }
}

 /**
 * @author Abdelrahman Walaa
 * Name: isCardExpired
 * @param Card user card to check
 * @param termData ATM terminal data
 *
 * @return EN_terminalError_t Error or No Error
 * Description: 1. This function compares the card expiry date with the transaction date.
			    2. If the card expiration date is before the transaction date will return EXPIRED_CARD,
				 else return TERMINAL_OK.
*/
EN_terminalError_t isCardExpired(ST_cardData_t *cardData, ST_terminalData_t *termData)
{
	/* Define local variable to set the error state, No Error */
	EN_terminalError_t Loc_ErrorState = TERMINAL_OK;
	/* Define local variable to store month on Card */
	uint8_t Loc_CardMonth = ((cardData->cardExpirationDate[0] - '0') * 10) + (cardData->cardExpirationDate[1] - '0');
	/* Define local variable to store year on Card */
	uint8_t Loc_CardYear  = ((cardData->cardExpirationDate[3] - '0') * 10) + (cardData->cardExpirationDate[4] - '0');
	/* Define local variable to store month of transaction */
	uint8_t Loc_TransMonth = ((termData->transactionDate[3] - '0') * 10) + (termData->transactionDate[4] - '0');
	/* Define local variable to store year of transaction */
	uint8_t Loc_TransYear  = ((termData->transactionDate[8] - '0') * 10) + (termData->transactionDate[9] - '0');

	/* Check 1: cardYear < transYear */
	if (Loc_CardYear < Loc_TransYear)
	{
		/* Update error state, Expired Card! */
		Loc_ErrorState = EXPIRED_CARD;
	}
	/* Check 2: cardYear >= transYear */
	else
	{
		/* Check 2.1: cardMonth < TransMonth */
		if (Loc_CardYear == Loc_TransYear && Loc_CardMonth < Loc_TransMonth)
		{
			/* Update error state, Expired Card! */
			Loc_ErrorState = EXPIRED_CARD;
		}
	}

	return Loc_ErrorState;
}

/**
 * This function will check if the PAN is a Luhn number or not
 * @param cardData user credit card data
 * @return INVALID_CARD if not Luhn number
 * @return TERMINAL_OK otherwise
 */
EN_terminalError_t isValidCardPAN(ST_cardData_t *cardData)
{
    int sum = 0;
    int len = sizeof(cardData->primaryAccountNumber);
    int is_second = 0;

    for (int i = len - 1; i >= 0; i--) {
        int digit = cardData->primaryAccountNumber[i];
        if(digit == 0) continue; // card number is less than 20
        digit -= '0'; // convert number from char to integer

        // double every second digit
        if (is_second) {
            digit *= 2;

            // if result is 2 digits, sum the 2 digits into one
            while (digit > 9) {
                digit -= 9;
            }
        }

        // add digit to total sum
        sum += digit;

        // flip is_second number flag
        is_second = !is_second;
    }

    // check if sum of the digits is divisible by 10, therefore it is a valid Luhn number
    // checksum is the last digit
    return ((sum % 10 == 0) ? TERMINAL_OK : INVALID_CARD);

}

/* ********************** Main Terminal Functions End ********************************************** */


 /*****************************************************************************************/
 /*    Function Description    : This function compares the transaction amount with the terminal max allowed amount. */
 /*    Parameter in            : ST_terminalData_t* termData */
 /*    Parameter inout         : None */
 /*    Parameter out           : None */
 /*    Return value            : return EXCEED_MAX_AMOUNT If the transaction amount is larger than the terminal max allowed amount
 *                               return TERMINAL_OK otherwise;
 *    Requirment              : None */
 /*****************************************************************************************/
 EN_terminalError_t isBelowMaxAmount(ST_terminalData_t* termData)
 {
     if (termData->transAmount > termData->maxTransAmount)
         return EXCEED_MAX_AMOUNT;
     return TERMINAL_OK;
 }