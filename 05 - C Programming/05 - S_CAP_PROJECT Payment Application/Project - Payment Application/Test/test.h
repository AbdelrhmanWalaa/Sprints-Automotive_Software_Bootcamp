#ifndef TEST_H
#define TEST_H

#include <stdlib.h>
#include <io.h>

#include "../Card/card.h"
#include "../Terminal/terminal.h"
#include "../Server/server.h"

#define TEST_DIR "Test/TestCases/"
#define CONCAT(STR1, STR2) STR1 STR2

/**
 * Retrieves full file name for test case (input data / expected result) depending on fileType
 * @param fileType [in] 1 return input data file, 0 return expected result file
 * @param i [in] test case number (0 indexed)
 * @param test_dir [in] main test dir
 * @param testFilename [out] full filename for the file requested
 */
 //void getTestFileName(int i, char * test_dir, char * testFilename, uint8_t fileType);



 /******************** CARD MODULE ********************/

 /** Test function for @see ../Card/card.c:getCardPan() */
void getCardExpiryDateTest(void);
void getCardHolderNameTest(void);
void getCardPANTest(void);


/******************** TERMINAL MODULE ********************/
void getTransactionDateTest(void);
void isCardExpiredTest(void);
void getTransactionAmountTest(void);
void isBelowMaxAmountTest(void);
void setMaxAmountTest(void);
void isValidCardPANTest(void); // (optional) Luhn Number Check

/******************** SERVER MODULE ********************/
void receiveTransactionDataTest(void);
void isValidAccountTest(void);
void isBlockedAccountTest(void);
void isAmountAvailableTest(void);
void saveTransactionTest(void);
void listSavedTransactionsTest(void);

/******************** RUN ALL TESTS ********************/
void testAll();

#endif //TEST_H