#include "main.h"
#include "LCDMenuSettings.h"

size_t numOfItems = 0;
LCDItem *LCDMenuItems = NULL;
int LCDMenuSelection;

//divides all possible potentiometer values between all the items so that all
//items have an equal size range of values where they're selected.
int selectionSize;
int selectionRangeUpper;
int selectionRangeLower;
int (*LCDSelectionSense)(void);

void LCDMenuTask(void *ignore)
{
    if(!numOfItems)
    {
        return;
    }

    while(true)
    {
        selectionRangeUpper = selectionSize;
        selectionRangeLower = 0;
        //loop through all the items to decide what should be displayed
        for(int i = 0; i < numOfItems; i++)
        {
            //if the potentiometer is within the selection range of item i
            if(LCDSelectionSense() >= selectionRangeLower &&
               LCDSelectionSense() <= selectionRangeUpper)
            {
                //change the current selection to i
                LCDMenuSelection = i;

                //display the selection on line 1 of the LCD pluged int uart1
                lcdPrint(uart1, 1, "%c %s", LCD_POINTER_CHAR,
                         LCDMenuItems[i].LCDText);

                //if there is more than one item and the last item isn't the
                //current selection
                if(numOfItems > 1 && i != numOfItems-1)
                {
                    //display the next selection
                    lcdPrint(uart1, 2, "  %s", LCDMenuItems[i+1].LCDText);
                }

                else
                {
                    lcdSetText(uart1, 2, NULL);
                }
            }

            //set the selection range for i+1
            selectionRangeLower = selectionRangeUpper;
            selectionRangeUpper += selectionSize;
        }
        delay(20);
    }
}

void newItem(char* itemText, void (*itemFunction)())
{
    numOfItems++;
    LCDMenuItems = realloc(LCDMenuItems, numOfItems * sizeof *LCDMenuItems);
    LCDMenuItems[numOfItems-1].LCDText = itemText;
    LCDMenuItems[numOfItems-1].function = itemFunction;
    selectionSize = 4095 / numOfItems;
}
