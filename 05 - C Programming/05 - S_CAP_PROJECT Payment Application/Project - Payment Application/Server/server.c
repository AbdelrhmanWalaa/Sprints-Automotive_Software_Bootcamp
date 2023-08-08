/*
 * @Title      	: Server Module
 * @Filename   	: server.c
 * @Author     	: Mahmoud Mowafey
 * @Origin Date	: Mar 30, 2023
 * @Version		: 1.0.0
 * @Compiler	: MinGW
 * @Target     	: General Purpose Processor / PCs
 * @Notes		: The code is written with ANSI_C Standard.
 *
 * THIS SOFTWARE IS PROVIDED BY HACKER KERMIT- TEAM_1 at Sprints_Automotiv_BC_W11.
 *
 *
 */
#include "server.h"

/* Accounts Database */
ST_accountsDB_t  accountsDB[255] =               /* Visa */                               /* MasterCard */
        /* Balance |  State |        PAN       */  /* Balance |  State |        PAN       */
        {{  12000.0f   , BLOCKED, "4728459258966333"}, {  68600.3f   , RUNNING, "5183150660610263"},
         {  5805.5f    , RUNNING, "4946084897338284"}, {  5000.3f    , RUNNING, "5400829062340903"},
         {  90360.12f  , RUNNING, "4728451059691228"}, {  1800000.0f , RUNNING, "5191786640828580"},
         {  16800.58f  , RUNNING, "4573762093153876"}, {  40800.0f   , RUNNING, "5367052744350494"},
         {  520.9f     , RUNNING, "4127856791257426"}, {  18900.45f  , RUNNING, "5248692364161088"},
         {  6900.33f   , RUNNING, "4946099660091878"}, {  1047751.0f , RUNNING, "5419558003040483"},
         {  200000.0f  , RUNNING, "4834699064563433"}, {  3026239.0f , RUNNING, "5116136307216426"},
         {  5000000.0f , RUNNING, "4946069587908256"}, {  9362076.0f , RUNNING, "5335847432506029"},
         {  25600.0f   , RUNNING, "4946085117749481"}, {  10662670.0f, RUNNING, "5424438206113309"},
         {  895000.0f  , RUNNING, "4946099683908835"}, {  1824.0f    , RUNNING, "5264166325336492"}};

uint8_t Glb_AccountsDBIndex = 0;

/* Transactions Database */
ST_transaction_t transactionsDB[255] = {0};
/* Transactions Database Index */
static uint8_t Glb_TransactionsDBIndex = 0;

/***********************************************************************************************************************/

 /**
 * @author         : Tarek Gohry
 * @brief          : Take all transaction data and validate its data 
 * Description     :
    - It checks the account details and amount availability 
 * Return          :
    - FRAUD_CARD if the account does not exist 
    - DECLINED_INSUFFECIENT_FUND if the amount is not available
	- DECLINED_STOLEN_CARD if the account is blocked 
	- INTERNAL_SERVER_ERROR if a transaction can't be saved
	- APPROVED Otherwise
 */
 EN_transState_t recieveTransactionData(ST_transaction_t *transData) {
     ST_accountsDB_t accountReference;

     if (isValidAccount(&transData->cardHolderData, &accountReference) == ACCOUNT_NOT_FOUND) {
         transData->transState = FRAUD_CARD;
         if(saveTransaction(transData) == SERVER_OK) return FRAUD_CARD;
     }

     else if (isBlockedAccount(&accountReference) == BLOCKED_ACCOUNT) {
         transData->transState = DECLINED_STOLEN_CARD;
         if(saveTransaction(transData) == SERVER_OK) return DECLINED_STOLEN_CARD;
     }

     else if (isAmountAvailable(&transData->terminalData, &accountReference) == LOW_BALANCE) {
         transData->transState = DECLINED_INSUFFECIENT_FUND;
         if(saveTransaction(transData) == SERVER_OK) return DECLINED_INSUFFECIENT_FUND;
     }

     else// if(transData->transState == APPROVED)
     {
         transData->transState = APPROVED;
         accountsDB[Glb_AccountsDBIndex].balance -= transData->terminalData.transAmount;
         if(saveTransaction(transData) == SERVER_OK)
         {
             printf(" New Balance is %0.2f\n", accountsDB[Glb_AccountsDBIndex].balance);
             return APPROVED;
         }
     }

     transData->transState = INTERNAL_SERVER_ERROR;
     return INTERNAL_SERVER_ERROR;
 }

/**
Name: isValidAccount
Input: Pointer to Card Data structure,
Input: Pointer to Card Data structure, Pointer to AccountsDB structure
Output: EN_sreverError_t Error or No Error
Description: 1. This function will take card data and validate if the account related to this card exists or not.
             2. It checks if the PAN exists or not in the server's database (searches for the card PAN in the DB).
             3. If the PAN doesn't exist will return ACCOUNT_NOT_FOUND, else will return SERVER_OK and return a reference
                to this account in the DB.
*/
EN_serverError_t isValidAccount(ST_cardData_t *cardData, ST_accountsDB_t *accountRefrence)
{
    /* Define local variable to set the error state, No Error */
    EN_serverError_t Loc_ErrorState = SERVER_OK;
    /* Define local variable to set the flag state, Flag Down */
    EN_flagState_t Loc_Flag = FLAG_DOWN;

    /* Loop: Until Account is found or until the end of accountsDB */
    for (uint8_t Loc_Index = 0; Loc_Index < 255; Loc_Index++)
    {
        /* Check 1: Account is found */
        if (!strcmp((char *)cardData->primaryAccountNumber, (char *)accountsDB[Loc_Index].primaryAccountNumber))
        {
            /* Copy Account details from accountsDB to passed pointer */
            *accountRefrence = accountsDB[Loc_Index];

            /* Update accountsDB Index */
            Glb_AccountsDBIndex = Loc_Index;

            /* Update flag state, Account is Found! */
            Loc_Flag = FLAG_UP;
            break;
        }
    }

    /* Check 2: Account is not found */
    if (Loc_Flag == FLAG_DOWN)
    {
        /* Update error state, Account Not Found! */
        Loc_ErrorState = ACCOUNT_NOT_FOUND;
    }

    return Loc_ErrorState;
}

/************************************************************************************************************
 * Function : isBlockedAccount()
 *//**
  * Description:
  *
  * This function is used to check the user-account status, to validate if the account is blocked or running.
  *
  * PRE-CONDITION:  the Account_Data_Base should be exist.
  *
  * POST-CONDITION: the Account has been checked if it is blocked or running.
  *
  * @param [in]		accountRefrence is a pointer to the ST_accountsDB_t structure that holding data
  * 					about user-account.
  *
  * @return 			EN_serverError_t is a enumeration that contains server errors.
  * \b Example:
  * @code
  * EN_serverError_t var = isBlockedAccount();
  * @endcode
  *
  *
  ************************************************************************************************************/
EN_serverError_t isBlockedAccount(ST_accountsDB_t* accountRefrence)
{
    if (accountRefrence->state == BLOCKED)
    {
        return BLOCKED_ACCOUNT;
    }
    else
    {
        return SERVER_OK;
    }

}

/*****************************************************************************************/
/*    Function Description    : This function will take terminal data and a reference to the account in the database
*								and check if the account has a sufficient amount to withdraw or not.*/
/*    Parameter in            : ST_terminalData_t* termData
*								ST_accountsDB_t* accountRefrence	*/
/*    Parameter inout         : None */
/*    Parameter out           : None */
/*    Return value            : return LOW_BALANCE If the transaction amount is greater than the balance in the database
*								return SERVER_OK otherwise */
/*    Requirment              : None */
/*****************************************************************************************/
EN_serverError_t isAmountAvailable(ST_terminalData_t* termData, ST_accountsDB_t* accountRefrence)
{
    if (termData->transAmount > accountRefrence->balance)
        return LOW_BALANCE;
    return SERVER_OK;
}

/**
* @author         : Tarek Gohry
* @brief          : Store all transaction data in the transaction database
* Description     :
   - It gives a sequence number to a transaction
   - This number is incremented once a transaction is processed into the server
   - Must check the last sequence number in the server to give the new transaction a new sequence number
   - It saves ant type of a transaction. APPROVED, DECLINED_INSUFFECIENT_FUND, DECLINED_STOLEN_CARD,
     FRUAD_CARD, INTERNAL_SERVER_ERROR
   - List all saved transactions using the listSavedTransactions function
* Return          :
   - SERVER_OK, Assuming that the connection between the terminal and server is always connected
*/
EN_serverError_t saveTransaction(ST_transaction_t *transData)
{
    static int trxSeqNumber = 32500;

    transactionsDB[Glb_TransactionsDBIndex].cardHolderData = transData->cardHolderData;
    transactionsDB[Glb_TransactionsDBIndex].terminalData = transData->terminalData;
    transactionsDB[Glb_TransactionsDBIndex].transState = transData->transState;
    transactionsDB[Glb_TransactionsDBIndex].transactionSequenceNumber = trxSeqNumber;

    listSavedTransactions();

    trxSeqNumber++;
    Glb_TransactionsDBIndex++;
    return SERVER_OK;
}


/*
 Name: listSavedTransactions
 Input: void
 Output: void
 Description:
*/
void listSavedTransactions(void)
{
    for(uint8_t Loc_u8Index = 0; Loc_u8Index <= Glb_TransactionsDBIndex; Loc_u8Index++)
    {
        printf("\n");

        printf(" ##########################\n");
        printf(" Transaction Sequence Number: %d\n", transactionsDB[Loc_u8Index].transactionSequenceNumber);
        printf(" Transaction Date: %s\n", transactionsDB[Loc_u8Index].terminalData.transactionDate);
        printf(" Transaction Amount: %.3f\n", transactionsDB[Loc_u8Index].terminalData.transAmount);
        printf(" Transaction State: ");
        switch (transactionsDB[Loc_u8Index].transState) {
            case APPROVED:
                printf("APPROVED\n");
                break;
            case DECLINED_INSUFFECIENT_FUND:
                printf("DECLINED_INSUFFECIENT_FUND\n");
                break;
            case DECLINED_STOLEN_CARD:
                printf("DECLINED_STOLEN_CARD\n");
                break;
            case FRAUD_CARD:
                printf("FRAUD_CARD\n");
                break;
            case INTERNAL_SERVER_ERROR:
                printf("INTERNAL_SERVER_ERROR\n");
                break;
        }
        printf(" Terminal Max Amount: %.3f\n", transactionsDB[Loc_u8Index].terminalData.maxTransAmount);
        printf(" Cardholder Name: %s\n", transactionsDB[Loc_u8Index].cardHolderData.cardHolderName);
        printf(" PAN: %s\n", transactionsDB[Loc_u8Index].cardHolderData.primaryAccountNumber);
        printf(" Card Expiration Date: %s\n", transactionsDB[Loc_u8Index].cardHolderData.cardExpirationDate);
        printf(" ##########################\n");

        printf("\n");
    }
}