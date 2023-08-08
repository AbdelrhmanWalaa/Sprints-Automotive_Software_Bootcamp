
#include "test.h"

/************************************************************************************************************
* Function : getCardHolderNameTest()
*//**
 * Description:
 *
 * This function is used to test the getHolderName() function, to validate the card data.
 *
 * PRE-CONDITION:     the Card_Data exist and struct should be created, so that we can store/validate the card name.
 * POST-CONDITION:    the cardName passed the listed test cases.
 *
 * @param [in]		void
 *
 * @return 			void
 * \b Example:
 * @code
 * getCardHolderNameTest();
 * @endcode
 *
 * @see getCardHolderName()
 * Check the four cases:
 * 1- if the entered name is pure alphabetic and number of characters is >= 20 and <=24 or not.
 * 2- if the entered name contains an alphabetic characters or not.
 * 3- if the entered name is Null or not.
 * 4- if the entered name contains a non alphabetic characters or not.
 *
 ****************************************************************************************************************************************/

void getCardHolderNameTest(void)
{
    char *test_cases_filename = CONCAT(TEST_DIR, "getCardHolderName.csv");
    const char testCaseDelimiter[2] = ",";

    char testCase[256];

    ST_cardData_t *cardData = calloc(1, sizeof(ST_cardData_t));

    printf("==================================\n");
    printf("Tester Name:\tMahmoud Mowafey\n");
    printf("Function Name:\tgetCardHolderName\n");
    printf("==================================\n");

    FILE *fp_test_cases;
    int i = 0;


    // redirect test case inputData to stdin
    fp_test_cases = fopen(test_cases_filename, "r");

    // read test case inputData
//        fgets(testCase, sizeof(testCase), fp_test_cases);
    while (fgets(testCase, sizeof(testCase), fp_test_cases)) {
        // split test case into tokens of input data & expected result (which was delimited by comma)

        FILE *fp_fake_stdin;
        char *inputData;
        char *expectedResult;

        printf("\n-----------------------\n");
        printf("Test Case %d\n", i + 1);
        printf("-----------------------\n");

        inputData = strtok(testCase, testCaseDelimiter);
        expectedResult = strtok(NULL, testCaseDelimiter);

        printf("Input Data:\t%s\n", inputData);
        printf("Expected:\t%s\n", expectedResult);

        /************* push input data to stdin ***************/
        fp_fake_stdin = freopen(CONCAT(TEST_DIR, "temp_stdin.txt"), "w+", stdin);
        fprintf(fp_fake_stdin, "%s\n", inputData);
        rewind(fp_fake_stdin);

        /************* Execute test case ***************/
        EN_cardError_t ret = getCardHolderName(cardData);
        // turn on console logs

        printf("\nActual Result:\t");
        switch (ret) {
            case CARD_OK:
                printf("CARD_OK\n");
                break;
            case WRONG_NAME:
                printf("WRONG_NAME\n");
                break;
        }

        fclose(fp_fake_stdin);
        i++; // next test case
    }

    free(cardData);
    fclose(fp_test_cases);
}


/*****************************************************************************************/
/**    Function Description    : This function to test getCardExpiryDate
*								Check for the following cases
*								- if the entered date is NULL
*								- if the entered date containing numbers only
*								- if the entered month is valid (Not equal 0 or more than 12)
*								- if the entered date length is 5
*    Parameter in            : None
*    Parameter inout         : None
*    Parameter out           : None
*    Return value            : None
*    Requirment              : None
*
* Test cases @see "Test/TestCases/getCardExpireDate.csv"
*****************************************************************************************/
void getCardExpiryDateTest(void)
{
    // test cases init
    char *test_cases_filename = CONCAT(TEST_DIR, "getCardExpiryDate.csv");
    const char testCaseDelimiter[2] = ",";

    // test cases buffer
    char testCase[256];

    ST_cardData_t *cardData = calloc(1, sizeof(ST_cardData_t));

    // Print Test Header
    printf("===============================\n");
    printf("Tester Name:\tMatarawy\n");
    printf("Function Name:\tgetCardExpiryDate\n");
    printf("===============================\n");

    // running test cases
//    for (int i = 0; i < testCasesCount; ++i) {

    FILE *fp_test_cases;
    int i = 0;


    // redirect test case inputData to stdin
    fp_test_cases = fopen(test_cases_filename, "r");

    // read test case inputData
//        fgets(testCase, sizeof(testCase), fp_test_cases);
    while (fgets(testCase, sizeof(testCase), fp_test_cases)) {
        // split test case into tokens of input data & expected result (which was delimited by comma)

        FILE *fp_fake_stdin;
        char *inputData;
        char *expectedResult;

        printf("\n-------------------------------\n");
        printf("Test Case %d\n", i + 1);
        printf("-------------------------------\n");

        inputData = strtok(testCase, testCaseDelimiter);
        expectedResult = strtok(NULL, testCaseDelimiter);

        printf("Input Data:\t%s\n", inputData);
        printf("Expected:\t%s\n", expectedResult);

        /************* push input data to stdin ***************/
        fp_fake_stdin = freopen(CONCAT(TEST_DIR, "temp_stdin.txt"), "w+", stdin);
        fprintf(fp_fake_stdin, "%s\n", inputData);
        rewind(fp_fake_stdin);

        /************* Execute test case ***************/
        EN_cardError_t ret = getCardExpiryDate(cardData);
        // turn on console logs

        printf("\nActual Result:	");
        switch (ret) {
            case WRONG_EXP_DATE:
                printf("\tWRONG_EXP_DATE\n");
                break;
            case CARD_OK:
                printf("\tCARD_OK\n");
                break;
        }

        fclose(fp_fake_stdin);
        i++; // next test case
    }

    free(cardData);
    fclose(fp_test_cases);
}


/***
 * Runs test cases for getCardPan
 */
void getCardPANTest(void) {
    // test cases init
    char *test_cases_filename = CONCAT(TEST_DIR, "getCardPan.csv");
    const char testCaseDelimiter[2] = ",";

    // test cases buffer
    char testCase[256];

    ST_cardData_t *cardData = calloc(1, sizeof(ST_cardData_t));

    // Print Test Header
    printf("===============================\n");
    printf("Tester Name:\tHossam Elwahsh\n");
    printf("Function Name:\tgetCardPan\n");
    printf("===============================\n");

    // running test cases
//    for (int i = 0; i < testCasesCount; ++i) {

    FILE *fp_test_cases;
    int i = 0;


    // redirect test case inputData to stdin
    fp_test_cases = fopen(test_cases_filename, "r");

    // read test case inputData
//        fgets(testCase, sizeof(testCase), fp_test_cases);
    while (fgets(testCase, sizeof(testCase), fp_test_cases)) {
        // split test case into tokens of input data & expected result (which was delimited by comma)

        FILE *fp_fake_stdin;
        char *inputData;
        char *expectedResult;

        printf("\n------------------------------------------------------------------------\n");
        printf("Test Case %d\n", i + 1);
        printf("------------------------------------------------------------------------\n");

        inputData = strtok(testCase, testCaseDelimiter);
        expectedResult = strtok(NULL, testCaseDelimiter);

        printf("Input Data:\t%s\n", inputData);
        printf("Expected:\t%s\n", expectedResult);

        /************* push input data to stdin ***************/
        fp_fake_stdin = freopen(CONCAT(TEST_DIR, "temp_stdin.txt"), "w+", stdin);
        fprintf(fp_fake_stdin, "%s\n", inputData);
        rewind(fp_fake_stdin);

        /************* Execute test case ***************/
        EN_cardError_t ret = getCardPAN(cardData);
        // turn on console logs

        printf("\nActual Result:\t");
        switch (ret) {
            case CARD_OK:
                printf("CARD OK\n");
                break;
            case WRONG_PAN:
                printf("WRONG_PAN\n");
                break;
        }

        fclose(fp_fake_stdin);
        i++; // next test case
    }

    free(cardData);
    fclose(fp_test_cases);
}

//endregion

/** ***************************************************
******************* TERMINAL MODULE *******************
*******************************************************/

void getTransactionDateTest(void) {
    // Print Test Header
    printf("====================================\n");
    printf("Tester Name:\tTarek Gohary\n");
    printf("Function Name:\tgetTransactionDate()\n");
    printf("====================================\n");
    printf("Test Case 1\n");
    printf("Input Data:\tPC's current date programmatically\n");
    printf("Expected Result:\tTERMINAL_OK\n");

    // allocate memory for terminalData
    ST_terminalData_t * terminalData = calloc(1, sizeof(ST_terminalData_t));

    // fetch and validate PC date
    EN_terminalError_t ret = getTransactionDate(terminalData);

    switch (ret) {

        case TERMINAL_OK:
            printf("Actual Result:\tTERMINAL_OK\n");
            break;
        case WRONG_DATE:
            printf("Actual Result:\tWRONG_DATE\n");
            break;
    }

    // free terminalData
    free(terminalData);
}

        /************* push input data to stdin ***************//*
        fp_fake_stdin = freopen(CONCAT(TEST_DIR, "temp_stdin.txt"), "w+", stdin);
        fprintf(fp_fake_stdin, "%s\n", inputData);
        rewind(fp_fake_stdin);

        *//************* Execute test case ***************//*
        EN_terminalError_t ret = getTransactionDate(terminalData);
        // turn on console logs

        printf("Actual Result:	");
        switch (ret) {
            case WRONG_DATE:
                printf("WRONG_DATE OK\n");
                break;
            case TERMINAL_OK:
                printf("TERMINAL_OK\n");
                break;
        }

        fclose(fp_fake_stdin);
        i++; // next test case
    }

    free(terminalData);
    fclose(fp_test_cases);
}*/


void isCardExpiredTest(void) {
    // test cases init
    char *test_cases_filename = CONCAT(TEST_DIR, "isCardExpired.csv");
    const char testCaseDelimiter[2] = ",";

    // test cases buffer
    char testCase[256];

    ST_cardData_t *cardData = calloc(1, sizeof(ST_cardData_t));
    ST_terminalData_t *terminalData = calloc(1, sizeof(ST_terminalData_t));

    // sets transaction date to today's date
    getTransactionDate(terminalData);

    // Print Test Header
    printf("==================================\n");
    printf("Tester Name:\tAbdelrhman Walaa\n");
    printf("Function Name:\tisCardExpired\n");
    printf("==================================\n");

    FILE *fp_test_cases;
    int i = 0;

    // redirect test case inputData to stdin
    fp_test_cases = fopen(test_cases_filename, "r");

    // read test case inputData
//        fgets(testCase, sizeof(testCase), fp_test_cases);
    while (fgets(testCase, sizeof(testCase), fp_test_cases)) {
        // split test case into tokens of input data & expected result (which was delimited by comma)

        char *inputData;
        char *expectedResult;

        printf("\n------------------------------\n");
        printf("Test Case %d\n", i + 1);
        printf("------------------------------\n");

        inputData = strtok(testCase, testCaseDelimiter);
        expectedResult = strtok(NULL, testCaseDelimiter);

        printf("Input Data:\t%s\n", inputData);
        printf("Expected:\t%s\n", expectedResult);

        for (int j = 0; j < strlen(inputData); ++j) {
            cardData->cardExpirationDate[j] = inputData[j];
        }

        /************* Execute test case ***************/
        EN_terminalError_t ret = isCardExpired(cardData, terminalData);
        // turn on console logs

        printf("Actual Result:\t");
        switch (ret) {
            case TERMINAL_OK:
                printf("TERMINAL_OK\n");
                break;
            case EXPIRED_CARD:
                printf("EXPIRED_CARD\n");
                break;
        }

        i++; // next test case
    }

    free(cardData);
    free(terminalData);
    fclose(fp_test_cases);
}

void getTransactionAmountTest(void)
{
    // test cases init
    char *test_cases_filename = CONCAT(TEST_DIR, "getTransactionAmount.csv");
    const char testCaseDelimiter[2] = ",";

    // test cases buffer
    char testCase[256];

    ST_terminalData_t *terminalData = calloc(1, sizeof(ST_terminalData_t));
//    ST_cardData_t MyCard;

    // Print Test Header
    printf("==================================\n");
    printf("Tester Name:\tMahmoud Mowafey\n");
    printf("Function Name:\tgetTransactionAmount\n");
    printf("==================================\n");

    FILE *fp_test_cases;
    int i = 0;

    // redirect test case inputData to stdin
    fp_test_cases = fopen(test_cases_filename, "r");

    // read test case inputData
    while (fgets(testCase, sizeof(testCase), fp_test_cases)) {
        // split test case into tokens of input data & expected result (which was delimited by comma)

        FILE *fp_fake_stdin;
        char *inputData;
        char *expectedResult;

        printf("\n-----------------------\n");
        printf("Test Case %d\n", i + 1);
        printf("-----------------------\n");

        inputData = strtok(testCase, testCaseDelimiter);
        expectedResult = strtok(NULL, testCaseDelimiter);

        printf("Input Data:\t%s\n", inputData);
        printf("Expected:\t%s\n", expectedResult);

        /************* push input data to stdin ***************/
        fp_fake_stdin = freopen(CONCAT(TEST_DIR, "temp_stdin.txt"), "w+", stdin);
        fprintf(fp_fake_stdin, "%s\n", inputData);
        rewind(fp_fake_stdin);

        /************* Execute test case ***************/
        EN_terminalError_t ret = getTransactionAmount(terminalData);
        // turn on console logs

        printf("\nActual Result:\t");
        switch (ret) {
            case INVALID_AMOUNT:
                printf("INVALID_AMOUNT\n");
                break;
            case TERMINAL_OK:
                printf("TERMINAL_OK\n");
                break;
        }

        fclose(fp_fake_stdin);
        i++; // next test case
    }

    free(terminalData);
    fclose(fp_test_cases);

}

/*****************************************************************************************/
/*    Function Description    : test all possible scenarios, happy-case, and worst-case scenarios. on isBelowMaxAmount function*/
/*    Parameter in            : None */
/*    Parameter inout         : None */
/*    Parameter out           : None */
/*    Return value            : None */
/*    Requirement              : None */
/*
* Test casese 1000 , 1500 , 2000 , 2500 ,3000 , 3500 , 4000 , 4500 , 5000 , 5500 , 6000 , 6500 , 7000 , 7500 , 8000 , 8500 , 9000
*             9500 , 10000 , 10500
* max_amount set to 8000
*/
/*****************************************************************************************/
void isBelowMaxAmountTest(void)
{
    // test cases init
    char *test_cases_filename = CONCAT(TEST_DIR, "isBelowMaxAmount.csv");
    const char testCaseDelimiter[2] = ",";

    // test cases buffer
    char testCase[256];

    ST_terminalData_t *terminalData = calloc(1, sizeof(ST_terminalData_t));

    setMaxAmount(terminalData, 4000.0f);

    // Print Test Header
    printf("==================================\n");
    printf("Tester Name:\tMatarawy\n");
    printf("Function Name:\tisBelowMaxAmount\n");
    printf("==================================\n");

    FILE *fp_test_cases;
    int i = 0;

    // redirect test case inputData to stdin
    fp_test_cases = fopen(test_cases_filename, "r");

    // read test case inputData
    while (fgets(testCase, sizeof(testCase), fp_test_cases)) {

        // split test case into tokens of input data & expected result (which was delimited by comma)
        char *inputData;
        char *expectedResult;

        printf("\n-----------------------\n");
        printf("Test Case %d\n", i + 1);
        printf("-----------------------\n");

        inputData = strtok(testCase, testCaseDelimiter);
        expectedResult = strtok(NULL, testCaseDelimiter);

        printf("Input Data:\t%s\n", inputData);
        printf("Expected:\t%s\n", expectedResult);

        terminalData->transAmount = atof(inputData);

        /************* Execute test case ***************/
        EN_terminalError_t ret = isBelowMaxAmount(terminalData);

        // turn on console logs
        printf("\nActual Result:\t");
        switch (ret) {
            case EXCEED_MAX_AMOUNT:
                printf("EXCEED_MAX_AMOUNT\n");
                break;
            case TERMINAL_OK:
                printf("TERMINAL_OK\n");
                break;
        }

        i++; // next test case
    }

    free(terminalData);
    fclose(fp_test_cases);
}


/**
 * Runs test cases for setMaxAmount()
 */
void setMaxAmountTest(void) {
    // test cases init
    char* test_cases_filename = CONCAT(TEST_DIR, "setMaxAmount.csv");
    const char testCaseDelimiter[2] = ",";

    // test cases buffer
    char testCase[256];
    ST_terminalData_t* terminalData = calloc(1, sizeof(ST_terminalData_t));

    // Print Test Header
    printf("===============================\n");
    printf("Tester Name:\tHossam Elwahsh\n");
    printf("Function Name:\tsetMaxAmount\n");
    printf("===============================\n");

    // running test cases
//    for (int i = 0; i < testCasesCount; ++i) {

    FILE* fp_test_cases;
    int i = 0;


    // redirect test case inputData to stdin
    fp_test_cases = fopen(test_cases_filename, "r");

    // read test case inputData
//        fgets(testCase, sizeof(testCase), fp_test_cases);
    while (fgets(testCase, sizeof(testCase), fp_test_cases)) {
        // split test case into tokens of input data & expected result (which was delimited by comma)

        char* inputData;
        char* expectedResult;

        printf("\n-----------------------\n");
        printf("Test Case %d\n", i + 1);
        printf("-----------------------\n");

        inputData = strtok(testCase, testCaseDelimiter);
        expectedResult = strtok(NULL, testCaseDelimiter);

        printf("Input Data:\t%s\n", inputData);
        printf("Expected:\t%s\n", expectedResult);

        /************* Execute test case ***************/
        EN_terminalError_t ret = setMaxAmount(terminalData, atof(inputData));
        // turn on console logs

        printf("Actual Result:\t");
        switch (ret) {
            case TERMINAL_OK:
                printf("TERMINAL_OK\n");
                break;
            case INVALID_MAX_AMOUNT:
                printf("INVALID_MAX_AMOUNT\n");
                break;
        }

        i++; // next test case
    }

    free(terminalData);
    fclose(fp_test_cases);
}


/**
 * Runs test cases for isValidCardPAN()
 */
void isValidCardPANTest(void) {
    // test cases init
    char *test_cases_filename = CONCAT(TEST_DIR, "isValidCardPAN.csv");
    const char testCaseDelimiter[2] = ",";

    // test cases buffer
    ST_cardData_t *cardData = calloc(1, sizeof(ST_cardData_t));
    char testCase[256];

    // Print Test Header
    printf("===============================\n");
    printf("Tester Name:\tHossam Elwahsh\n");
    printf("Function Name:\tisValidCardPAN\n");
    printf("===============================\n");

    // running test cases
//    for (int i = 0; i < testCasesCount; ++i) {

    FILE *fp_test_cases;
    int i = 0;

    // redirect test case inputData to stdin
    fp_test_cases = fopen(test_cases_filename, "r");

    // read test case inputData
//        fgets(testCase, sizeof(testCase), fp_test_cases);
    while (fgets(testCase, sizeof(testCase), fp_test_cases)) {
        // split test case into tokens of input data & expected result (which was delimited by comma)

        char *inputData;
        char *expectedResult;

        printf("\n-----------------------\n");
        printf("Test Case %d\n", i + 1);
        printf("-----------------------\n");

        inputData = strtok(testCase, testCaseDelimiter);
        expectedResult = strtok(NULL, testCaseDelimiter);

        printf("Input Data:\t%s\n", inputData);
        printf("Expected:\t%s\n", expectedResult);

        // clear data
        for (int j = 0; j < sizeof (cardData->primaryAccountNumber); ++j) {
            cardData->primaryAccountNumber[j] = 0;
        }

        // set test case input
        for (int j = 0; j < strlen(inputData); ++j) {
            cardData->primaryAccountNumber[j] = inputData[j];
        }

        /************* Execute test case ***************/
        EN_terminalError_t ret = isValidCardPAN(cardData);

        printf("Actual Result:	");
        switch (ret) {
            case TERMINAL_OK:
                printf("TERMINAL_OK\n");
                break;
            case INVALID_CARD:
                printf("INVALID_CARD\n");
                break;
        }

        i++; // next test case
    }

    free(cardData);
    fclose(fp_test_cases);
}

/** ***************************************************
******************* SERVER MODULE *******************
*******************************************************/

    /**
     * Runs test cases for isBlockedAccount()
     */
void isBlockedAccountTest(void)
{
    // test cases init
    char* test_cases_filename = CONCAT(TEST_DIR, "isBlockedAccount.csv");
    const char testCaseDelimiter[2] = ",";

    // test cases buffer
    char testCase[256];

    ST_accountsDB_t* accountState = calloc(1, sizeof(ST_accountsDB_t));

    // Print Test Header
    printf("===============================\n");
    printf("Tester Name:\tMahmoud Mowafey\n");
    printf("Function Name:\tisBlokedAccount\n");
    printf("===============================\n");

    // running test cases
//    for (int i = 0; i < testCasesCount; ++i) {

    FILE* fp_test_cases;
    int i = 0;


    // redirect test case inputData to stdin
    fp_test_cases = fopen(test_cases_filename, "r");

    // read test case inputData
//        fgets(testCase, sizeof(testCase), fp_test_cases);
    while (fgets(testCase, sizeof(testCase), fp_test_cases)) {
        // split test case into tokens of input data & expected result (which was delimited by comma)

        FILE* fp_fake_stdin;
        char* inputData;
        char* expectedResult;

        printf("\n-----------------------\n");
        printf("Test Case %d\n", i + 1);
        printf("-----------------------\n");

        inputData = strtok(testCase, testCaseDelimiter);
        expectedResult = strtok(NULL, testCaseDelimiter);

        printf("Input Data:\t%s\n", inputData);
        printf("Expected:\t%s\n", expectedResult);

        if(!strcmp("RUNNING", inputData))
        {
            accountState->state = RUNNING;
        }else{
            accountState->state = BLOCKED;
        }

        /************* push input data to stdin ***************/
        fp_fake_stdin = freopen(CONCAT(TEST_DIR, "temp_stdin.txt"), "w+", stdin);
        fprintf(fp_fake_stdin, "%s\n", inputData);
        rewind(fp_fake_stdin);

        /************* Execute test case ***************/
        EN_serverError_t ret = isBlockedAccount(accountState);
        // turn on console logs

        printf("Actual Result:\t");
        switch (ret) {
        case SERVER_OK:
            printf("SERVER_OK\n");
            break;
        case BLOCKED_ACCOUNT:
            printf("BLOCKED_ACCOUNT\n");
            break;
        }

        fclose(fp_fake_stdin);
        i++; // next test case
    }

    free(accountState);
    fclose(fp_test_cases);

}

void isValidAccountTest(void)
{
    // test cases init
    char *test_cases_filename = CONCAT(TEST_DIR, "isValidAccount.csv");
    const char testCaseDelimiter[2] = ",";

    // test cases buffer
    ST_accountsDB_t * accountReference = calloc(1, sizeof(ST_accountsDB_t));
    ST_cardData_t *cardData = calloc(1, sizeof(ST_cardData_t));
    char testCase[256];

    // Print Test Header
    printf("===============================\n");
    printf("Tester Name:\tAbdelrhman Walaa\n");
    printf("Function Name:\tisValidAccount\n");
    printf("===============================\n");

    FILE *fp_test_cases;
    int i = 0;

    // redirect test case inputData to stdin
    fp_test_cases = fopen(test_cases_filename, "r");

    // read test case inputData
    while (fgets(testCase, sizeof(testCase), fp_test_cases)) {
        // split test case into tokens of input data & expected result (which was delimited by comma)

        char *inputData;
        char *expectedResult;

        printf("\n-----------------------\n");
        printf("Test Case %d\n", i + 1);
        printf("-----------------------\n");

        inputData = strtok(testCase, testCaseDelimiter);
        expectedResult = strtok(NULL, testCaseDelimiter);

        printf("Input Data:\t%s\n", inputData);
        printf("Expected:\t%s\n", expectedResult);

        // clear data
        for (int j = 0; j < sizeof (cardData->primaryAccountNumber); ++j) {
            cardData->primaryAccountNumber[j] = 0;
        }

        // set test case input
        for (int j = 0; j < strlen(inputData); ++j) {
            cardData->primaryAccountNumber[j] = inputData[j];
        }

        /************* Execute test case ***************/
        EN_serverError_t ret = isValidAccount(cardData, accountReference);

        printf("Actual Result:\t");
        switch (ret) {
            case ACCOUNT_NOT_FOUND:
                printf("ACCOUNT_NOT_FOUND\n");
                break;
            case SERVER_OK:
                printf("SERVER_OK\n");
                break;
        }

        i++; // next test case
    }

    free(cardData);
    free(accountReference);
    fclose(fp_test_cases);



}

void listSavedTransactionsTest(void)
{
    ST_transaction_t transactionsDB[4] = {
            {
                    {
                        "Mohamed Salah Mohamed",
                        "4728459258966333",
                        "05/25"
                    },
                    {
                            1000.0f,
                            4000.0f,
                            "03/10/2020"
                    },
                    APPROVED,
                    1
            },
            {
                    {
                        "Salah Abdo Hamed",
                        "4946084897338284",
                        "05/24"
                    },
                    {
                            3500.0f,
                            4000.0f,
                            "05/10/2020"
                    },
                    DECLINED_STOLEN_CARD,
                    2
            },
            {
                    {
                        "Aly Mamdouh Aly",
                        "4728451059691228",
                        "06/25"
                    },
                    {
                            3200.0f,
                            4000.0f,
                            "06/11/2020"
                    },
                    APPROVED,
                    3
            },
            {
                    {
                        "Mostafa Mohamed Mostafa",
                        "4573762093153876",
                        "07/26"
                    },
                    {
                            2500.0f,
                            4000.0f,
                            "07/10/2021"
                    },
                    DECLINED_STOLEN_CARD,
                    4
            }
    };

    printf("===============================\n");
    printf("Tester Name:\tAbdelrhman Walaa\n");
    printf("Function Name:\tlistSavedTransactions\n");
    printf("===============================\n");

    printf("----------------------------------\n");
    printf("Test Case 1:\n");
    printf("----------------------------------\n");
    printf("Input Data:\ttransaction entry\n");
    printf("Expected Result:\tlist of elements\n");
    printf("Actual Result:\n\t");

    for (int i = 0; i < (sizeof(transactionsDB)/ sizeof(transactionsDB[0])); i++) {

        /// Code snippet from server.c -> @listSavedTransactions()
        printf("\n");

        printf(" ##########################\n");
        printf(" Transaction Sequence Number: %d\n", transactionsDB[i].transactionSequenceNumber);
        printf(" Transaction Date: %s\n", transactionsDB[i].terminalData.transactionDate);
        printf(" Transaction Amount: %.3f\n", transactionsDB[i].terminalData.transAmount);
        printf(" Transaction State: %d\n", transactionsDB[i].transState);
        printf(" Terminal Max Amount: %.3f\n", transactionsDB[i].terminalData.maxTransAmount);
        printf(" Cardholder Name: %s\n", transactionsDB[i].cardHolderData.cardHolderName);
        printf(" PAN: %s\n", transactionsDB[i].cardHolderData.primaryAccountNumber);
        printf(" Card Expiration Date: %s\n", transactionsDB[i].cardHolderData.cardExpirationDate);
        printf(" ##########################\n");

        printf("\n");

    }
}


/*****************************************************************************************/
/*    Function Description    : test all possible scenarios, happy-case, and worst-case scenarios. on isAmountAvailable function*/
/*    Parameter in            : None */
/*    Parameter inout         : None */
/*    Parameter out           : None */
/*    Return value            : None */
/*    Requirment              : None */
/*
* Test casese 1000 , 1500 , 2000 , 2500 ,3000 , 3500 , 4000 , 4500 , 5000 , 5500 , 6000 , 6500 , 7000 , 7500 , 8000 , 8500 , 9000
*             9500 , 10000 , 10500
* balance set to 8000
*/
/*****************************************************************************************/
void isAmountAvailableTest(void) {
    // test cases init
    char* test_cases_filename = CONCAT(TEST_DIR, "isAmountAvailable.csv");
    const char testCaseDelimiter[2] = ",";

    // test cases buffer
    char testCase[256];

    ST_terminalData_t * terminalData = calloc(1, sizeof(ST_terminalData_t));
    ST_accountsDB_t * accountReference = calloc(1, sizeof(ST_accountsDB_t));
    accountReference->balance = 8000.0f;

    // Print Test Header
    printf("===============================\n");
    printf("Tester Name:\tMatarawy\n");
    printf("Function Name:\tisAmountAvailable\n");
    printf("===============================\n");

    FILE* fp_test_cases;
    int i = 0;

    // redirect test case inputData to stdin
    fp_test_cases = fopen(test_cases_filename, "r");

    // read test case inputData
    while (fgets(testCase, sizeof(testCase), fp_test_cases)) {

        // split test case into tokens of input data & expected result (which was delimited by comma)
        char* inputData;
        char* expectedResult;

        printf("\n-----------------------\n");
        printf("Test Case %d\n", i + 1);
        printf("-----------------------\n");

        inputData = strtok(testCase, testCaseDelimiter);
        expectedResult = strtok(NULL, testCaseDelimiter);

        printf("Acc Balance:\t%.2f\n", accountReference->balance);
        printf("Input Data:\t%s\n", inputData);
        printf("Expected:\t%s\n", expectedResult);

        terminalData->transAmount = atof(inputData);

        /************* Execute test case ***************/
        EN_serverError_t ret = isAmountAvailable(terminalData, accountReference);
        // turn on console logs

        printf("Actual Result:\t");
        switch (ret) {
            case SERVER_OK:
                printf("SERVER_OK\n");
                break;
            case LOW_BALANCE:
                printf("LOW_BALANCE\n");
                break;
        }

        i++; // next test case
    }

    fclose(fp_test_cases);
}

/**
 * Runs test cases for recieveTransactionDataTest()
 */

void receiveTransactionDataTest(void)
{
    // Print Test Header
    printf("====================================\n");
    printf("Tester Name:\tTarek Gohary\n");
    printf("Function Name:\trecieveTransactionDataTest()\n");
    printf("====================================\n");

    // test cases init
    char* test_cases_filename = CONCAT(TEST_DIR, "receiveTransactionData.csv");
    const char testCaseDelimiter[2] = ",";
    // test cases buffer
    char testCase[256];

    ST_transaction_t transactionsDB[4] = {
            {
                    {
                            "Mohamed Salah Mohamed",
                            "4728459258966333",
                            "05/25"
                    },
                    {
                            1000.0f,
                            4000.0f,
                            "03/10/2020"
                    },
                    APPROVED,
                    1
            },
            {
                    {
                            "Alaa Eldin Bayoumi",
                            "4946084897338284",
                            "05/24"
                    },
                    {
                            3500.0f,
                            4000.0f,
                            "05/10/2020"
                    },
                    DECLINED_STOLEN_CARD,
                    2
            },
            {
                    {
                            "Aly Mamdouh Aly",
                            "4728451059691228",
                            "06/25"
                    },
                    {
                            3200.0f,
                            4000.0f,
                            "06/11/2020"
                    },
                    APPROVED,
                    3
            },
            {
                    {
                            "Mostafa Mohamed Mostafa",
                            "4573762093153876",
                            "07/26"
                    },
                    {
                            2500.0f,
                            4000.0f,
                            "07/10/2021"
                    },
                    DECLINED_STOLEN_CARD,
                    4
            }
    };


    FILE* fp_test_cases;
    int i = 0;

    // redirect test case inputData to stdin
    fp_test_cases = fopen(test_cases_filename, "r");

    // read test case inputData
    while (fgets(testCase, sizeof(testCase), fp_test_cases)) {

        // split test case into tokens of input data & expected result (which was delimited by comma)
        char* inputData;
        char* expectedResult;

        printf("\n-----------------------\n");
        printf("Test Case %d\n", i + 1);
        printf("-----------------------\n");

        inputData = strtok(testCase, testCaseDelimiter);
        expectedResult = strtok(NULL, testCaseDelimiter);

        printf("Input Data:\t%s\n", inputData);
        printf("Expected:\t%s\n", expectedResult);


        /************* Execute test case ***************/
    EN_transState_t  ret = recieveTransactionData(&transactionsDB[i]);

        printf("Actual Result:\t");
    switch (ret) {
        case FRAUD_CARD:
            printf("FRAUD_CARD\n");
            break;
        case DECLINED_STOLEN_CARD:
            printf("DECLINED_STOLEN_CARD\n");
            break;
        case DECLINED_INSUFFECIENT_FUND:
            printf("DECLINED_INSUFFECIENT_FUND\n");
            break;
        case INTERNAL_SERVER_ERROR:
            printf("INTERNAL_SERVER_ERROR\n");
            break;
        case APPROVED:
            printf("APPROVED\n");
            break;
    }
        i++; // next test case
    }

    fclose(fp_test_cases);
}

/**
 * Runs test cases for saveTransaction()
 */
void saveTransactionTest(void)
{
    // Print Test Header
    printf("====================================\n");
    printf("Tester Name:\tTarek Gohary\n");
    printf("Function Name:\tgetTransactionDate()\n");
    printf("====================================\n");
    printf("Test Case 1\n");
    printf("Input Data:\tAll transaction data after validation\n");
    printf("Expected Result:\tSERVER_OK\n");

   ST_transaction_t transData = {
           {
                   "Mohamed Salah Mohamed",
                   "4728459258966333",
                   "05/25"
           },
           {
                   1000.0f,
                   4000.0f,
                   "03/10/2020"
           },
           APPROVED,
           1
   };
    EN_serverError_t ret = saveTransaction(&transData);

    switch (ret) {
        case SERVER_OK:
            printf("Actual Result:\tSERVER_OK\n");
            break;
    }
}


/**
 * Call this from main.c to test all project modules
 */
void testAll()
{
    // clear commandline
    system("cls");


    /** CARD MODULE */
    printf("\n\n");
    printf("/**********************************************************************\\\n");
    printf("\t\t\tTESTING CARD MODULE\t\t\t\n");
    printf("/**********************************************************************\\\n");
    printf("\n\n");
    getCardExpiryDateTest();
    getCardHolderNameTest();
    getCardPANTest();

    /** TERMINAL MODULE */
    printf("\n\n");
    printf("/**********************************************************************\\\n");
    printf("\t\t\tTESTING TERMINAL MODULE\t\t\t\n");
    printf("/**********************************************************************\\\n");
    printf("\n\n");
    getTransactionDateTest();
    isCardExpiredTest();
    getTransactionAmountTest();
    isBelowMaxAmountTest();
    setMaxAmountTest();
    isValidCardPANTest();

    /** SERVER MODULE */
    printf("\n\n");
    printf("/**********************************************************************\\\n");
    printf("\t\t\tTESTING SERVER MODULE\t\t\t\n");
    printf("/**********************************************************************\\\n");
    printf("\n\n");
    isValidAccountTest();
    isBlockedAccountTest();
    isAmountAvailableTest();
    listSavedTransactionsTest();
    receiveTransactionDataTest();
    saveTransactionTest();
}
