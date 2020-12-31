/**
 * Author: Arnold Gihozo
 * Class: AUCSC 370
 * Date Created: October 11,2020
 * Date Last Modified: October 18, 2020
 *
 * Description:
 *  This file contains an overview of the functions within main.c file. These functions are made
 *  in order to make a the translation from English File to Euroglish.
 *
*/


#ifndef EUROENGLISH_HEADER_H
#define EUROENGLISH_HEADER_H
typedef struct node{
    char value;
    struct node* next;
}nodeType;


/**
 * Reads a given .txt file and calls addFileInLinkedList function that will put each character into a
 * singly linked list.
 *
 * @return --> returns the head of the linked list as a nodeType
 */
nodeType * readFile();

/**
 * Function will add a given character into a singly linked list
 *
 * @param letter --> the letter to be added on the linked list as a character
 * @param _head --> the head of the linked list(as nodeType) so we can traverse through it
 *
 */
void addFileInLinkedList(char letter, nodeType **_head);

/**
 * This function will execute all the translation rules as outlined in year 1
 *
 * @param head --> takes the head of the linked list as a parameter to traverse through te
 * linked list
 *
 */
void year1(nodeType *head);

/**
 * This function will execute all the translation rules as outlined in year 2
 *
 * @param head --> takes the head of the linked list as a parameter to traverse through te
 * linked list
 *
 */
void year2(nodeType *head);

/**
 * This function will execute all the translation rules as outlined in year 3
 *
 * @param head --> takes the head of the linked list as a parameter to traverse through te
 * linked list
 *
 */
void year3(nodeType *head);

/**
 * This function will execute all the translation rules as outlined in year 4
 *
 * @param head --> takes the head of the linked list as a parameter to traverse through te
 * linked list
 *
 */
void year4(nodeType *head);

/**
 * This function will turn any given upper case character into a lower case.
 *
 * @param character --> a character that we want to turn into lower case
 * @return --> returns a character converted into the lower case.
 */
char myTolower(char character);

/**
 * Function will delete the next node of a given node. For instance if node A is
 * given, it will delete the next node B and provide the correct connection A will
 * have to make to C(since B is now deleted).
 *
 * @param node --> the node that needs to be reconnected
 * @return --> the new connection that needs to be made
 *
 */
nodeType *deleteNextNode(nodeType *node);

/**
 * This functions will print the linked list
 *
 * @param head --> the head of the linked list so we can traverse through it.
 */
void printLinkedList(nodeType * head);



#endif //EUROENGLISH_HEADER_H
