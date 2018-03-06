#ifndef LCDITEM_H_
#define LCDITEM_H_

/**
 * @brief each menu and sub-menu can be configured to use different types of
 * input for item selection and choice.
 *
 * @note when an item is chosen, it's selected and it's function is executed or
 * it's sub-menu displayed (see itemType) and is selected when
 * LCDMenu.currentSelection is at the item's array index (LCDMenu.LCDItems)
 */
typedef enum selectChooseType {
    /**
     * use a potentiometer to select and/or choose an item the advantage of this
     * being that the selection will be the same after the robot is turned off,
     * making it useful for autonomous selection
     *
     * @note should not be used choose sub menus.
     *
     * @see LCDMenu.selectionType
     * @see LCDMenu.chooseType
     */
    POTENTIOMETER,

    /**
     * use a/some digital sensor(s) (probally bumber switches) to select and or
     * choose items.
     */
    DIGITAL_SENSOR,

    /**
     * use the items built into the LCD.
     */
    LCD_BUTTONS,
}selectChooseType;

/**
 * @brief this enum show if an item can be choosen, and if it can wether or not
 * it's a sub menu or if it executes a function.
 *
 * @see LCDMenu
 */
typedef enum itemType {
    /**
     * exacute the function that LCDItem.function points to when this item is
     * chosen.
     *
     * @see LCDMenu.function
     */
    FUNCTION_EXEC,

    /**
     * if LCDItem.itemType is set to this it means that there's a sub menu in
     * LCDItem.subMenu.
     *
     * @see LCDItem.subMenu
     */
    SUB_MENU,

    /**
     * this means that the item is not a subMenu and does not have a function in
     * the function pointer and thus cannot be chosen.
     */
    SELECTION_ONLY,
}itemType;

/**
 * @brief forward declaration/typedef of LCDItem struct
 */
typedef struct LCDItem LCDItem;

/**
 * @brief this hold all the variables needed for a LCDMenu or sub menu.
 */
typedef struct LCDMenu {
    /**
     * an array of LCDItems, this will be reallocated everytime a new item is
     * added.
     *
     * @see LCDItem
     */
    LCDItem *LCDItems;

    /**
     * the method of input for selecting an item.
     *
     * @see selectChooseType
     */
    selectChooseType selectionType;

    /**
     * the method of input for choosing a selected item.
     *
     * @see selectChooseType
     */
    selectChooseType chooseType;

    /**
     * the index of the item the item that should be displayed  in LCDItems.
     */
    int currentSelection;
}LCDMenu;

/**
 * @brief holds the information for individual items, mainly the text to be
 * displayed.
 */
struct LCDItem {
    /**
     * the text to be displayed on the LCD.
     */
    char *LCDText;

    /**
     * a pointer to the function to be exacuted if this item is choosen (asuming
     * one should be executed).
     *
     * @see itemType
     */
    void (*function)();

    /**
     * @see itemType
     */
    itemType itemType;

    /**
     * if this item is a sub menu, said sub menu will be stored here.
     */
    LCDMenu subMenu;
};

extern LCDItem *LCDMenuItems;
extern int LCDMenuSelection;

extern int (*LCDSelectionSense)(void);

/**
 * @brief this should be started as a task in initialize.
 */
void LCDMenuTask(void *ignore);

/**
 * @brief hadds an item to the menu
 */
void newItem(char* itemText, void (*itemFunction)());
#endif
