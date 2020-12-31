/**
 * Author: Arnold Gihozo
 * Class: AUCSC 370
 * Date Created: October 11, 2020
 * Date Last Modified: October 18, 2020
 *
 * Description:
 * The program bellow translate a file written in English into Euroglish. The program was created within the
 * scope of the AUCSC 370 course from the University of Alberta- Augustana Campus. The program reads a given
 * text file, puts each character into a single linked list and applies the rules to translate it into Euroglish.
 * The rules are broken into 5 steps (5 years) in order to ensure that the translation from english to euroglish happens
 * smoothly. This program is primarly written to translate files written in English to Euroglish, however, may be
 * used for other purpose may the rules of translation applies to other languages as well.
 *
 * Limitations:
 * Throughout the program, you will notice that there is 4 main functions that will execute the translation followed
 * by any other functions that are designed for repetitve tasks. You will also notice that some functions are
 * of length bigger than 10 lines. The reason for this is to ensure that all rules are kept together and that
 * it is easier for anyone reading the code to undurstand the flow of  transaltion. When needed, functions have been
 * split into "sections" for better visualization of what the function is doing at the macro level. Doing so, will
 * limit the amount of recursion we might need to perform, thereofre increasing the speed of translation of our
 * program.
 *
 *
 */
#include <stdio.h>
#include <stdlib.h>
#include "header.h"

/**
 * This function reads every single character of a given textfile and puts it in a link list by calling the function
 * addFileLinkedList.
 *
 * @return-- returns the head of the linked list as a nodeType
 */
nodeType *readFile() {
    char letter;
    nodeType *head = NULL;

    FILE *myFile = fopen(
            "/Users/arnoldgihozo/Desktop/University/Fourth Year/Fall 2020/AUCSC 370/Assignements/Assignement"
            " 2/euroEnglish/testFile.txt",
            "r");
    if (myFile) {
        while (fscanf(myFile, "%c", &letter) != EOF) {
            addFileInLinkedList(letter, &head);
        }// while
        fclose(myFile);
        return head;
    } else {
        printf("My apologies, the file did not open! \n");
        return NULL;
    }// else
}// readFile

/**
 * This functions adds a single character to a linked list. It also ensures that if it is the first character
 * to be added, it sets that as the head.
 *
 * @param letterToBeAdded --> the character to be added on the linked list
 * @param _head --> The head of the linked list. This is a double pointer since we are getting
 * it's address when it is being called in readFile()
 */
void addFileInLinkedList(char letterToBeAdded, nodeType **head) {
    nodeType *temp = NULL;
    nodeType *extra = NULL;

    temp = (nodeType *) malloc(sizeof(nodeType));
    temp->value = letterToBeAdded;
    temp->next = NULL;

    if (*head == NULL) { // if first item to be added in the linked list
        *head = temp;
    } else {
        extra = *head;
        while (extra->next != NULL)
            extra = extra->next;
        extra->next = temp;
    }// else
} //addFileToLinkedlist

/**
 * This function replaces all "c" characters with either s if followed by e,i,y or k if followed by nothing else.
 * This function will also takes into account the capital letters.
 *
 * @param head --> the start of the linked list represented as a nodeType
 */
void year1(nodeType *head) {
    nodeType *temp = head;
    while (temp != NULL) {
        if (temp->value == 'c') {
            if (temp->next->value == 'e' || temp->next->value == 'i'
                || temp->next->value == 'y') {
                temp->value = 's';
            } else {
                temp->value = 'k';
            } // else
        } // outer if
        if (temp->value == 'C') {
            if (temp->next->value == 'e' || temp->next->value == 'i'
                || temp->next->value == 'y') {
                temp->value = 'S';
            } else {
                temp->value = 'K';
            } // else
        } // outer if
        temp = temp->next;
    } // while

}//year1

/**
 * This function will transform all instance of "ph to simply "f". This function takes into account the capital
 * letters and returns the appropriate letter accordingly.
 *
 * @param head --> takes in as a parameter the head of the linked list as a nodetype to be able to traverse through
 * the list.
 */
void year2(nodeType *head) {
    nodeType *current = head;
    while (current != NULL) {
        if (current->value == 'P' || current->value == 'p') {
            if (current->next != NULL && current->next->value == 'h') {
                if (current->value == 'p') {
                    current->value = 'f';
                } else {
                    current->value = 'F';
                }// else
                nodeType *t = current->next;
                current->next = current->next->next;
                free(t);
            }//inner if
        }// outer if
        current = current->next;
    }// while
}// year2

/**
 * This functions execute all the rules from year 3 of translation. In order to ensure the readability of the
 * code, the function has been split into three sections (A,B,C). The function ensures that we are not at the
 * end of the list and that we at least have one character.
 *
 * A --> The first section will check if there are any word that duplicated it and change them to single letter. It will
 * not change any spaces.
 *
 * B --> The second section will check if we have any word that end within "ed" and change them to simply "d".
 *
 * C --> The third section will check if there are any words that end with "e" and that are more than 3 characters long.
 *
 * @param head --> takes in as a parameter the head of the linked list as a nodetype to be able to traverse through
 * the list.
 */
void year3(nodeType *head) {
    nodeType *current = head;
    nodeType *previous = NULL;
    int charLenght = 0;
    while (current != NULL) {
        if (previous != NULL) {

            //=======================================
            // A: Duplicate letter rule
            if (previous->value == current->value) {

                if (previous->value != '\n') {
                    current = deleteNextNode(previous);
                    continue;
                }// if

                //======================================
                // B: word ending with ed section
            } else if (previous->value == 'e' && current->value == 'd') {
                previous->value = 'd';
                current = deleteNextNode(previous);
                continue;

                //======================================
                // C: replacing word ending with "e" that are at least longer than 3 characters
            } else {
                if (current->value == '\n' || current->value == ' ' || current->value == '.'
                    || current->value == ',' || current->value == '?' || current->value == '!') {
                    if (charLenght > 3 && previous->value == 'e') {
                        previous->value = current->value;
                        current = deleteNextNode(previous);
                        charLenght = 0;
                        continue;
                    }// inner if
                    charLenght = 0;
                } else {
                    charLenght++;
                }// else
            }// outer else
        }// outer if
        previous = current;
        current = current->next;
    }// while
}//year3

/**
 * This function executes all the rules that from year 4. In order to ensure the readability of the
 * code, the function has been split into three sections (A,B,C,D). The function ensures that we are not at the
 * end of the list and that we at least have one character. Please note that this function transforms the current
 * and previous character into lowercase if they were upper case by calling another function called myLowerCase.
 * The reason for doing such change is to better evaluate all characters without checking for capitals. However, all
 * capital letters are being respected.
 *
 * A --> This section will change all words with "th" to z.
 *
 * B --> This section will remove all insntances of "o" that appear in "ou"
 *
 * C --> This section will remove all "a" from "ea"
 *
 * Note: please note that all the above sections require a tracker of the previous and current character. Whereas
 * the next section only looks at the current character of the list.
 *
 * D --> remove all instances of "w" and replace it with "v
 *
 * @param head --> takes in as a parameter the head of the linked list as a nodetype to be able to traverse through
 * the list.
 *
 */
void year4(nodeType *head) {
    nodeType *currentNode = head;
    nodeType *previousNode = NULL;

    while (currentNode != NULL) {
        char currentChar = myTolower(currentNode->value);

        if (previousNode != NULL) {
            char previousChar = myTolower(previousNode->value);

            //===============================================
            // Section A
            if (previousChar == 't' && currentChar == 'h') {
                if (previousNode->value == 'T') {
                    previousNode->value = 'Z';
                } else {
                    previousNode->value = 'z';
                }// else
                currentNode = deleteNextNode(previousNode);

                //===============================================
                // Section B
            } else if (previousChar == 'o' && currentChar == 'u') {
                if (previousNode->value == 'O') {
                    previousNode->value = 'U';
                } else {
                    previousNode->value = 'u';
                }// else
                currentNode = deleteNextNode(previousNode);
                continue;
            }// else if

            //===================================================
            //Section C
            if (previousChar == 'e' && currentChar == 'a') {
                currentNode = deleteNextNode(previousNode);
                continue;
            }//if
        }// outer if statement (previous !=null)

        //=====================================================
        //Section D
        if (currentChar == 'w') {
            if (currentNode->value == 'W') {
                currentNode->value = 'V';
            } else {
                currentNode->value = 'v';
            }// else
        }// if

        previousNode = currentNode;
        currentNode = currentNode->next;
    }// while
}//year 4

/**
 * This function puts a given character from a capital letter to a lowercase letter. This helps us to
 * remove complexity into our program since (when not necessary) we can evaluate all lower case.
 *
 * @param character -- character to be transformed into lower letter
 * @return --> returns a character that has been converted into a lower case letter
 *
 */
char myTolower(char character) {
    if (character >= 'A' && character <= 'Z') {
        return character + 32;
    }// if
    return character;
}// myTolower

/**
 * This function deletes the linked list at the very end of the program execution. This is to ensure we do not
 * encounter any issue when it comes to memory leak after we are done
 *
 * @param head --> head of the link list so we can move from the list using it
 */
void deleteList(nodeType *head) {
    nodeType *temp = head;
    while (temp != NULL) {
        nodeType *t = temp;
        temp = temp->next;
        free(t);
    }// while
}// deleteList

/**
 * This function prints a linked list after all translation have been executed.
 *
 * @param head --> takes is a head as nodeType in order to find begining of list.
 */
void printLinkedList(nodeType *head) {
    nodeType *extra = head;
    while (extra != NULL) {
        printf("%c", extra->value);
        extra = extra->next;
    }// while
}// printLinkedList

/**
 * This function helps to delete the next node that is in a given linked list. For a given node, it deletes the next
 * node and returns the new connection that has to be made.
 *
 * @param node--> it takes in the current node that the list is in.
 * @return --> the next position in which a node should be connected
 */
nodeType *deleteNextNode(nodeType *node) {
    nodeType *temp = node->next;
    if (temp != NULL) {
        node->next = temp->next;
        free(temp);
    }// if
    return node->next;
}// deleteNextNode

/**
 * Program execution starts here
 */
int main() {
    nodeType *head = readFile();
    if (head != NULL) {
        year1(head);
        year2(head);
        year3(head);
        year4(head);
        printLinkedList(head);

        deleteList(head);
    }// if

    return 0;
}// main


