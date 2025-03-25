#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node
{
    int data;
    struct Node *next;
    char name[16];
} Node;

int edgeCaseChecker(FILE *fp, int numIns)
{
    // check if something is true that shouldn't be
    int errorBool = 0;
    while (errorBool == 0)
    {
        if (fp == NULL)
        {
            errorBool = 1;
            return errorBool;
        }
        if (numIns == 0)
        {
            errorBool = 1;
            return errorBool;
        }
        errorBool = 1;
    }
    return errorBool;
}

void freeMat(int **matrix, int row)
{
    for (int i = 0; i < row; i++)
    {
        free(matrix[i]);
    }
    free(matrix);
}

// doesn't work :()

void freeLinkedList(Node *head)
{
    struct Node *ptr = head;
    struct Node *temp = ptr;
    while (ptr != NULL)
    {
        temp = ptr;
        ptr = ptr->next;
        free(temp);
    }
}

int power(int pow, int exp)
{
    // 2, 2 should be 4
    int ans = pow;
    if (exp == 0)
    {
        return 1;
    }
    else if (exp == 1)
    {
        return ans;
    }
    else
    {
        for (int i = 0; i < exp - 1; i++)
        {
            ans *= pow;
        }
    }
    return ans;
}

typedef struct Logic
{
    // gates as nodes weren't working, I'll try something new
    char operand[16];
    // don't malloc
    char firstIn[16];
    char secIn[16];
    // 16 or 17
    char output[16];
    struct Logic *next;
    int choice;
    Node *storage[];
} Logic;

void freeLog(Logic *first)
{
    struct Logic *ptr = first;
    struct Logic *temp = ptr;
    while (ptr != NULL)
    {
        temp = ptr;
        ptr = ptr->next;
        free(temp);
    }
}

Node *getIndex(Node *listHead, char title[32])
{
    Node *temp = listHead;
    while (temp != NULL)
    {
        if (strcmp(temp->name, title) == 0)
        {
            break;
        }
        if (temp->next == NULL)
        {
            break;
        }
        temp = temp->next;
    }

    if (strcmp(temp->name, title) != 0)
    {
        for (int i = 0; i < 1; i++)
        {
            Node *x = (Node *)malloc(sizeof(struct Node));
            strcpy(x->name, title);
            if (strcmp(x->name, "1") == 0)
            {
                x->data = 1;
            }
            else if (strcmp(x->name, "0") == 0)
            {
                x->data = 0;
            }
            else
            {
                x->data = 3;
            }
            x->next = NULL;
            temp->next = x;
            temp = temp->next;
        }
    }
    return temp;
}

void printTruthTable(int **truthTable, int rows, int cols)
{
    int index = 0;

    for (int row = 0; row < rows; row++)
    {
        int max = power(2, cols - 1);
        int currInd = index;
        for (int col = 0; col < cols; col++)
        {
            if ((currInd - max) >= 0)
            {
                truthTable[row][col] = 1;
                currInd = currInd - max;
            }
            else
            {
                truthTable[row][col] = 0;
            }
            max = max / 2;
        }
        index++;
    }
    return;
}

void gateFunc(Logic *mainGate, Node *sampNode)
{
    while (mainGate != NULL)
    {
        if (strcmp(mainGate->operand, "NOT") == 0)
        {
            Node *temp1 = getIndex(sampNode, mainGate->firstIn);

            Node *temp2 = getIndex(sampNode, mainGate->output);
            if (temp1->data == 0)
            {
                temp2->data = 1;
            }
            else
            {
                temp2->data = 0;
            }
        }
        else if (strcmp(mainGate->operand, "OR") == 0)
        {
            Node *temp1 = getIndex(sampNode, mainGate->firstIn);

            Node *temp2 = getIndex(sampNode, mainGate->secIn);
            Node *temp3 = getIndex(sampNode, mainGate->output);
            if (temp1->data || temp2->data)
            {
                temp3->data = 1;
            }
            else
            {
                temp3->data = 0;
            }
        }
        else if (strcmp(mainGate->operand, "NOR") == 0)
        {
            Node *temp1 = getIndex(sampNode, mainGate->firstIn);
            Node *temp2 = getIndex(sampNode, mainGate->secIn);

            Node *temp3 = getIndex(sampNode, mainGate->output);
            if (temp1->data || temp2->data)
            {
                temp3->data = 0;
            }
            else
            {
                temp3->data = 1;
            }
        }
        else if (strcmp(mainGate->operand, "AND") == 0)
        {
            Node *temp1 = getIndex(sampNode, mainGate->firstIn);

            Node *temp2 = getIndex(sampNode, mainGate->secIn);
            Node *temp3 = getIndex(sampNode, mainGate->output);
            if (temp1->data && temp2->data)
            {
                temp3->data = 1;
            }
            else
            {
                temp3->data = 0;
            }
        }
        else if (strcmp(mainGate->operand, "NAND") == 0)
        {
            Node *temp1 = getIndex(sampNode, mainGate->firstIn);
            Node *temp2 = getIndex(sampNode, mainGate->secIn);
            Node *temp3 = getIndex(sampNode, mainGate->output);
            if (temp1->data && temp2->data)
            {
                temp3->data = 0;
            }
            else
            {
                temp3->data = 1;
            }
        }
        else if (strcmp(mainGate->operand, "XOR") == 0)
        {
            Node *temp1 = getIndex(sampNode, mainGate->firstIn);
            Node *temp2 = getIndex(sampNode, mainGate->secIn);
            Node *temp3 = getIndex(sampNode, mainGate->output);
            if (temp1->data == temp2->data)
            {
                temp3->data = 0;
            }
            else
            {
                temp3->data = 1;
            }
        }
        else if (strcmp(mainGate->operand, "MULTIPLEXER") == 0)
        {
            int x = 0;
            int inputs = mainGate->choice;
            int options = power(2, inputs);
            int current = inputs - 1;
            for (int i = options; i < options + inputs; i++)
            {
                if (mainGate->storage[i]->data == 1)
                {
                    int c = power(2, current);
                    x = x + c;
                }
                current--;
            }
            int z = mainGate->storage[x]->data;
            mainGate->storage[options + inputs]->data = z;
        }
        else if (strcmp(mainGate->operand, "DECODER") == 0)
        {
            int x = 0;
            int y = mainGate->choice;
            for (int i = 0; i < y; i++)
            {
                if (mainGate->storage[i]->data == 1)
                {
                    int c = power(2, y - i - 1);
                    x = x + c;
                }
            }
            int k = power(2, y);
            for (int i = y; i < y + k; i++)
            {
                if (i - y == x)
                {
                    mainGate->storage[i]->data = 1;
                }
                else
                {
                    mainGate->storage[i]->data = 0;
                }
            }
        }
        mainGate = mainGate->next;
    }
}

// method for trying extra credit
//  will take in number of outputs from get num function
int ecAttempt(int numOuts, Logic *main, Node *head)
{
    if (numOuts == 2)
    {
        return 0;
    }
    else
    {
        for (int i = 0; i < numOuts; i++)
        {
            gateFunc(main, head);
        }
    }

    return 0;
}

int main(int argc, char **argv)
{
    //**********************FILE STUFF************
    FILE *fp = fopen(argv[1], "r");
    if (fp == NULL)
    {
        return EXIT_FAILURE;
    }

    //**********************NODE SETUP*************
    Node *mainNode = (Node *)malloc(sizeof(Node));
    mainNode->data = 3;
    mainNode->next = NULL;
    Node *inputStart = mainNode;
    Node *outputStart = mainNode;

    //**************STARTING LOGIC SETUP************

    Logic *order = (Logic *)malloc(sizeof(Logic));
    order->next = NULL;
    Logic *gatePtr = order;
    Node *ptr = mainNode;
    Node *ptr2 = mainNode;

    char storeOper[32];
    int inputNum, outputNum, muxNum, decNum;

    while (fscanf(fp, "%16s", storeOper) == 1)
    {
        if (strcmp(storeOper, "INPUT") == 0)
        {
            fscanf(fp, "%d ", &inputNum);
            for (int i = inputNum; i > 0; i--)
            {
                Node *head = (Node *)malloc(sizeof(Node));
                fscanf(fp, "%s", storeOper);
                strcpy(head->name, storeOper);
                if (strcmp(head->name, "1") == 0)
                {
                    head->data = 1;
                }
                else if (strcmp(head->name, "0") == 0)
                {
                    head->data = 0;
                }
                else
                {
                    head->data = 2;
                }
                head->next = ptr->next;
                ptr->next = head;
                ptr = ptr->next;
                if (i == inputNum)
                {
                    inputStart = head;
                }
            }
            ptr2 = ptr;
        }
        else if (strcmp(storeOper, "OUTPUT") == 0)
        {
            fscanf(fp, "%d ", &outputNum);
            for (int i = outputNum; i > 0; i--)
            {
                Node *head = (Node *)malloc(sizeof(Node));
                fscanf(fp, "%s", storeOper);
                strcpy(head->name, storeOper);
                if (strcmp(head->name, "1") == 0)
                {
                    head->data = 1;
                }
                else if (strcmp(head->name, "0") == 0)
                {
                    head->data = 0;
                }
                else
                {
                    head->data = 2;
                }
                head->next = ptr->next;
                ptr->next = head;
                ptr = ptr->next;
                if (i == outputNum)
                {
                    outputStart = head;
                }
            }
            ptr2 = ptr;
        }

        else if (strcmp(storeOper, "NOT") == 0)
        {
            Logic *first = (Logic *)malloc(sizeof(Logic));
            strcpy(first->operand, storeOper);
            // this works so far
            fscanf(fp, "%16s", storeOper);
            // error here
            strcpy(first->firstIn, storeOper);
            fscanf(fp, "%16s", storeOper);

            // this should be fine
            strcpy(first->output, storeOper);

            ptr = mainNode;
            int valueCurr = -1;
            while (ptr != NULL)
            {
                valueCurr = strcmp(storeOper, ptr->name);
                if (valueCurr == 0)
                {
                    break;
                }
                ptr = ptr->next;
            }
            if (valueCurr != 0)
            {

                Node *head = (Node *)malloc(sizeof(Node));
                strcpy(head->name, storeOper);
                ptr = ptr2;
                if (strcmp(head->name, "1") == 0)
                {
                    head->data = 1;
                }
                else if (strcmp(head->name, "0") == 0)
                {
                    head->data = 0;
                }
                else
                {
                    head->data = 2;
                }
                head->next = ptr->next;
                ptr->next = head;
                ptr = ptr->next;
                ptr2 = ptr;
            }
            else
            {
                valueCurr = -1;
            }

            first->next = NULL;
            gatePtr->next = first;
            gatePtr = gatePtr->next;
        }
        else if (strcmp(storeOper, "MULTIPLEXER") == 0)
        {
            Logic *first = (Logic *)malloc(sizeof(Logic));
            strcpy(first->operand, storeOper);
            fscanf(fp, "%d", &muxNum);
            int lim = power(2, muxNum);
            first = (Logic *)realloc(first, sizeof(Logic) + sizeof(Node) * (lim + muxNum + 1));
            first->choice = muxNum;

            int limit = power(2, muxNum);
            for (int i = 0; i < limit + muxNum + 1; i++)
            {
                fscanf(fp, "%s", storeOper);
                first->storage[i] = getIndex(mainNode, storeOper);
            }

            first->next = NULL;
            gatePtr->next = first;
            gatePtr = gatePtr->next;
        }
        else if (strcmp(storeOper, "DECODER") == 0)
        {
            Logic *first = (Logic *)malloc(sizeof(Logic));
            strcpy(first->operand, storeOper);
            fscanf(fp, "%d", &decNum);
            int lim = power(2, decNum);
            first = (Logic *)realloc(first, sizeof(Logic) + sizeof(Node) * (decNum + lim));
            first->choice = decNum;

            int c = power(2, decNum);
            for (int i = 0; i < decNum + c; i++)
            {
                fscanf(fp, "%s", storeOper);
                first->storage[i] = getIndex(mainNode, storeOper);
            }

            first->next = NULL;
            gatePtr->next = first;
            gatePtr = gatePtr->next;
        }

        else
        {
            Logic *first = (Logic *)malloc(sizeof(Logic));
            // here, we have to handle all the non-MUX gates, decoder gates,
            //  pass gates, etc
            strcpy(first->operand, storeOper);
            // still need to create AND, OR, XOR, NAND, etc gates
            // need to make sure they can handle more than 2 inputs
            //  won't always be 2
            fscanf(fp, "%s ", storeOper);
            // also should be able to free them after
            strcpy(first->firstIn, storeOper);
            // gotta create a route for each one
            fscanf(fp, "%s ", storeOper);
            // this works like it should

            // works
            strcpy(first->secIn, storeOper);
            //:)
            fscanf(fp, "%s ", storeOper);
            strcpy(first->output, storeOper);

            ptr = mainNode;
            int valueCurr = -1;
            while (ptr != NULL)
            {
                valueCurr = strcmp(storeOper, ptr->name);
                if (valueCurr == 0)
                {
                    break;
                }
                ptr = ptr->next;
            }

            if (valueCurr != 0)
            {
                Node *head = (Node *)malloc(sizeof(Node));
                strcpy(head->name, storeOper);
                ptr = ptr2;
                if (strcmp(head->name, "1") == 0)
                {
                    head->data = 1;
                }
                else if (strcmp(head->name, "0") == 0)
                {
                    head->data = 0;
                }
                else
                {
                    head->data = 3;
                }

                head->next = ptr->next;
                ptr->next = head;
                ptr = ptr->next;
                ptr2 = ptr;
                // ec, doesnt work
                ecAttempt(valueCurr, NULL, head);
            }
            else
            {
                valueCurr = -1;
            }

            first->next = NULL;
            gatePtr->next = first;
            gatePtr = gatePtr->next;
        }
    }
    int rows = 1;
    for (int i = 0; i < inputNum; i++)
    {
        rows = rows * 2;
    }
    int **truthTable = malloc(sizeof(int *) * rows);
    for (int i = 0; i < rows; i++)
    {
        truthTable[i] = malloc(sizeof(int) * inputNum);
    }
    printTruthTable(truthTable, rows, inputNum);

    Logic *freed = order;
    order = order->next;
    free(freed);

    Node *freedVar = mainNode;
    mainNode = mainNode->next;
    free(freedVar);

    ptr = mainNode;
    gatePtr = order;

    for (int i = 0; i < rows; i++)
    {
        ptr = inputStart;
        for (int j = 0; j < inputNum; j++)
        {
            ptr->data = truthTable[i][j];
            ptr = ptr->next;
        }

        gateFunc(order, mainNode);

        ptr = inputStart;
        for (int k = 0; k < inputNum; k++)
        {
            printf("%d ", ptr->data);
            ptr = ptr->next;
        }
        printf("%s", "|");
        ptr = outputStart;
        for (int m = 0; m < outputNum; m++)
        {
            printf(" %d", ptr->data);
            ptr = ptr->next;
        }
        printf("\n");
    }

    edgeCaseChecker(fp, inputNum);
    // check for edge cases
    freeLinkedList(mainNode);
    // free the list

    freeLog(order);
    // free all my logic gates
    freeMat(truthTable, rows);
    fclose(fp);
    return EXIT_SUCCESS;
}
