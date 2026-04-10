//Sara Shrouf
//1220481
//sec 1
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// ─── Struct Declarations ────────────────────────────────────────────────────

struct town;
typedef struct town* Node2;

struct town {
    int populatin;
    char townname[50];
    Node2 next;
    Node2 prev;
};
typedef Node2 List2;

struct districts;
typedef struct districts* Node1;
struct districts {
    Node1 prev;
    char data[50];
    int allpop;
    Node2 next_town;
    Node1 next;
};
typedef Node1 List1;

struct global;
typedef struct global* G;
struct global {
    G prev;
    G next;
    int pop;
    char named[50];
    char namet[50];
};
typedef G glob;

// ─── Globals ─────────────────────────────────────────────────────────────────

int isRead = 0;
glob glopal;

List1 extendedSortedList;
List1 unsort;

char token1[200][50];
char token2[200][50];
int  token3;

// ─── Function Prototypes ─────────────────────────────────────────────────────

void displayMainMenu();
List1 createList1();
List2 createList2();
glob  createList3();
int   isEmpty1(List1 L);
int   isEmpty2(List2 L);

int  find(List1 L, char target[50]);
int  find2(List1 L, char target[50], char dis[50]);

void insert1(List1 L, char word[50], int allpop, char town[50]);
void insert11(List1 L, char word[50], int totalpopulation, char town[50]);
void insert3(glob l, char word[50], char word1[50], int pop);
void addnewdistricts(List1 L, char name[50]);

void Deletedistricts(char namedis[50]);
void Deletetown(char nametown[50], List1 L, char district[50]);

int  maxtowpop(List1 L);
int  mintowpop(List1 L);
void changepop(List1 L, char dis[50], char town[50]);
void buble(List1 L);

int  getMaxNumOfChar(List1 L);
void addspase(List1 L);
void RadixSort(List1 L);
void Insert(List1 L, Node1 src);
void DeleteList(List1 L);
void deleteList1(List1 L);

void Print_Sorted_Strings(List1 L);
void printList(List1 L);
void printList1(List1 L);
void printList11(List1 L);
void printList3(glob L);
void printDistricts(List1 L);

void readInputFile();
void saveOutputFile(List1 L);
void removeZeros(List1 L);   /* kept but not required */

// ─── main ────────────────────────────────────────────────────────────────────

int main() {

    extendedSortedList = createList1();
    unsort             = createList1();
    glopal             = createList3();

    displayMainMenu();

    int operation;
    scanf("%d", &operation);
    printf("\n");

    /* BUG-FIX: namedistricts / nametown declared here so all cases can use them */
    char namedistricts[50];
    char nametown[50];

    while (operation != 14) {

        while (operation < 1 || operation > 14) {
            printf("Invalid operation. Try different number..\n\n");
            displayMainMenu();
            scanf("%d", &operation);
            printf("\n");
        }

        switch (operation) {

        /* ── 1: Load file ─────────────────────────────────────── */
        case 1:
            if (isRead == 1) {
                printf("\nThe input file has been read! Choose another operation.\n\n");
                break;
            }
            readInputFile();
            printf("\nReading process was successful.\n\n");
            isRead = 1;
            break;

        /* ── 2: Print before sorting ──────────────────────────── */
        case 2:
            if (isRead == 0) {
                printf("The input file has not been read yet.\nPlease choose to read input file first.\n\n");
                break;
            }
            printf("\nPrinting strings before sorting:\n\n");
            printList3(glopal);
            break;

        /* ── 3: Sort districts alphabetically (Radix) ─────────── */
        case 3:
            if (isRead == 0) {
                printf("\nThe input file has not been read yet.\nPlease choose to read input file first.\n\n");
                break;
            }
            RadixSort(unsort);
            printf("\nDistricts sorted alphabetically.\n\n");
            break;

        /* ── 4: Sort towns by population (bubble) ─────────────── */
        case 4:
            if (isRead == 0) {
                printf("\nThe input file has not been read yet.\nPlease choose to read input file first.\n\n");
                break;
            }
            buble(unsort);
            printf("The towns are arranged in ascending order by population.\n\n");
            break;

        /* ── 5: Print sorted information ──────────────────────── */
        case 5:
            if (isRead == 0) {
                printf("\nThe input file has not been read yet.\nPlease choose to read input file first.\n\n");
                break;
            }
            printf("\nSorted Information:\n\n");
            /* BUG-FIX: printList11 took two params in original but was defined
               with one.  Fixed signature to one param. */
            printList11(unsort);
            break;

        /* ── 6: Add new district ──────────────────────────────── */
        case 6:
            if (isRead == 0) {
                printf("\nThe input file has not been read yet.\nPlease choose to read input file first.\n\n");
                break;
            }
            printf("\nPlease write new district name:\n");
            scanf("%s", namedistricts);
            getchar();
            while (find(unsort, namedistricts)) {
                printf("District already exists. Please try another district name:\n");
                scanf("%s", namedistricts);
                getchar();
            }
            addnewdistricts(unsort, namedistricts);
            /* Re-sort after adding */
            RadixSort(unsort);
            printf("\nThe new district has been added and sorted.\n\n");
            break;

        /* ── 7: Add new town ──────────────────────────────────── */
        case 7:
            if (isRead == 0) {
                printf("\nThe input file has not been read yet.\nPlease choose to read input file first.\n\n");
                break;
            }
            {
                int population;
                printf("\nPlease write name of district:\n");
                scanf("%s", namedistricts);
                getchar();
                while (find(unsort, namedistricts) == 0) {
                    printf("District does not exist. Please try another district:\n");
                    scanf("%s", namedistricts);
                    getchar();
                }
                printf("Enter the name of town: ");
                scanf("%s", nametown);
                getchar();
                while (find2(unsort, nametown, namedistricts) == 1) {
                    printf("Town already exists. Enter another town name:\n");
                    scanf("%s", nametown);
                    getchar();
                }
                printf("Enter the population: ");
                scanf("%d", &population);
                getchar();
                insert1(unsort, namedistricts, population, nametown);
                printf("\nThe new town has been added.\n\n");
                printList1(unsort);
            }
            break;

        /* ── 8: Delete town ───────────────────────────────────── */
        case 8:
            if (isRead == 0) {
                printf("\nThe input file has not been read yet.\nPlease choose to read input file first.\n\n");
                break;
            }
            printf("Enter the name of district: ");
            scanf("%s", namedistricts);
            getchar();
            while (find(unsort, namedistricts) == 0) {
                printf("District does not exist. Please try another district:\n");
                scanf("%s", namedistricts);
                getchar();
            }
            printf("Enter the name of town: ");
            scanf("%s", nametown);
            getchar();
            while (find2(unsort, nametown, namedistricts) == 0) {
                printf("Town does not exist. Enter another town name:\n");
                scanf("%s", nametown);
                getchar();
            }
            Deletetown(nametown, unsort, namedistricts);
            printf("\nTown deleted.\n\n");
            printList1(unsort);
            break;

        /* ── 9: Delete district ───────────────────────────────── */
        case 9:
            if (isRead == 0) {
                printf("\nThe input file has not been read yet.\nPlease choose to read input file first.\n\n");
                break;
            }
            printf("Enter the name of district to delete: ");
            scanf("%s", namedistricts);
            getchar();
            /* BUG-FIX: original used strcmp==1 which is wrong; use find() */
            if (find(unsort, namedistricts)) {
                Deletedistricts(namedistricts);
                printf("\nDistrict deleted.\n\n");
                printList1(unsort);
            } else {
                printf("No such district found.\n\n");
            }
            break;

        /* ── 10: Population stats ─────────────────────────────── */
        case 10:
            if (isRead == 0) {
                printf("\nThe input file has not been read yet.\nPlease choose to read input file first.\n\n");
                break;
            }
            {
                int sum = 0;
                Node1 cur = unsort->next;
                while (cur != NULL) {
                    sum += cur->allpop;
                    cur = cur->next;
                }
                printf("Total population of Palestine: %d\n", sum);
                /* BUG-FIX: guard against empty town lists before calling max/min */
                if (unsort->next != NULL && unsort->next->next_town != NULL) {
                    printf("Max town population: %d\n", maxtowpop(unsort));
                    printf("Min town population: %d\n\n", mintowpop(unsort));
                } else {
                    printf("No towns available for max/min.\n\n");
                }
            }
            break;

        /* ── 11: Print districts only ─────────────────────────── */
        case 11:
            if (isRead == 0) {
                printf("\nThe input file has not been read yet.\nPlease choose to read input file first.\n\n");
                break;
            }
            printDistricts(unsort);
            break;

        /* ── 12: Change town population ───────────────────────── */
        case 12:
            if (isRead == 0) {
                printf("\nThe input file has not been read yet.\nPlease choose to read input file first.\n\n");
                break;
            }
            printf("Enter the name of district: ");
            scanf("%s", namedistricts);
            getchar();
            while (find(unsort, namedistricts) == 0) {
                printf("District does not exist. Please try another district:\n");
                scanf("%s", namedistricts);
                getchar();
            }
            printf("Enter the name of town: ");
            scanf("%s", nametown);
            getchar();
            while (find2(unsort, nametown, namedistricts) == 0) {
                printf("Town does not exist. Enter another town name:\n");
                scanf("%s", nametown);
                getchar();
            }
            changepop(unsort, namedistricts, nametown);
            printf("\nPopulation updated.\n\n");
            break;

        /* ── 13: Save output file ─────────────────────────────── */
        case 13:
            saveOutputFile(unsort);
            printf("The sorted data is now stored in 'output.txt'.\n\n");
            break;

        } /* end switch */

        displayMainMenu();
        scanf("%d", &operation);
        printf("\n");
    }

    printf("Exit\n");
    return 0;
}

// ─── Menu ────────────────────────────────────────────────────────────────────

void displayMainMenu() {
    printf("Select the number of option you want to do:\n\n");
    printf("1.  Load the input file (Palestinian districts and their town with population).\n");
    printf("2.  Print the loaded information before sorting (as in the input file format).\n");
    printf("3.  Sort the districts alphabetically using Radix sort.\n");
    printf("4.  Sort the towns for each district based on population in ascending order.\n");
    printf("5.  Print the sorted information.\n");
    printf("6.  Add a new district to the list of sorted districts (and sort the list).\n");
    printf("7.  Add a new town to a certain district.\n");
    printf("8.  Delete a town from a specific district.\n");
    printf("9.  Delete a complete district.\n");
    printf("10. Calculate the population of Palestine, the max and min town population.\n");
    printf("11. Print the districts and their total population (without towns details).\n");
    printf("12. Change the population of a town.\n");
    printf("13. Save to output file.\n");
    printf("14. Exit.\n\n");
    printf("Operation Num: ");
}

// ─── List creation ───────────────────────────────────────────────────────────

List1 createList1() {
    List1 L = (List1)malloc(sizeof(struct districts));
    if (L == NULL) { printf("\nOut of memory\n"); return NULL; }
    L->next = NULL;
    L->prev = NULL;
    L->next_town = NULL;
    L->allpop = 0;
    return L;
}

List2 createList2() {
    List2 L = (List2)malloc(sizeof(struct town));
    if (L == NULL) { printf("\nOut of memory\n"); return NULL; }
    L->next = NULL;
    L->prev = NULL;
    return L;
}

glob createList3() {
    glob L = (glob)malloc(sizeof(struct global));
    if (L == NULL) { printf("\nOut of memory\n"); return NULL; }
    L->next = NULL;
    L->prev = NULL;
    return L;
}

int isEmpty1(List1 L) { return (L->next == NULL); }
int isEmpty2(List2 L) { return (L->next == NULL); }

// ─── find ────────────────────────────────────────────────────────────────────

int find(List1 L, char target[50]) {
    Node1 cur = L->next;
    while (cur != NULL) {
        if (strcmp(cur->data, target) == 0) return 1;
        cur = cur->next;
    }
    return 0;
}

int find2(List1 L, char target[50], char dis[50]) {
    Node1 cur = L->next;
    while (cur != NULL) {
        if (strcmp(cur->data, dis) == 0) {
            Node2 t = cur->next_town;
            while (t != NULL) {
                if (strcmp(t->townname, target) == 0) return 1;
                t = t->next;
            }
            return 0;
        }
        cur = cur->next;
    }
    return 0;
}

// ─── Insert helpers ───────────────────────────────────────────────────────────

/*  insert1: If district already exists add town to it; otherwise create district. */
void insert1(List1 L, char word[50], int totalpopulation, char town[50]) {

    Node1 temp = L->next;
    while (temp != NULL) {
        if (strcmp(temp->data, word) == 0) {
            /* district exists – append town */
            Node2 newtown = (Node2)malloc(sizeof(struct town));
            strcpy(newtown->townname, town);
            newtown->populatin = totalpopulation;
            newtown->next = NULL;
            newtown->prev = NULL;

            if (temp->next_town == NULL) {
                temp->next_town = newtown;
            } else {
                Node2 tp = temp->next_town;
                while (tp->next != NULL) tp = tp->next;
                tp->next = newtown;
                newtown->prev = tp;
            }
            temp->allpop += totalpopulation;
            return;
        }
        temp = temp->next;
    }

    /* district doesn't exist – create it */
    Node1 newDis = (Node1)malloc(sizeof(struct districts));
    strcpy(newDis->data, word);
    newDis->allpop = totalpopulation;
    newDis->next   = L->next;
    newDis->prev   = L;
    if (L->next != NULL) L->next->prev = newDis;
    L->next = newDis;

    newDis->next_town = (Node2)malloc(sizeof(struct town));
    strcpy(newDis->next_town->townname, town);
    newDis->next_town->populatin = totalpopulation;
    newDis->next_town->next = NULL;
    newDis->next_town->prev = NULL;
}

/* insert11 is identical to insert1 – used for extendedSortedList */
void insert11(List1 L, char word[50], int totalpopulation, char town[50]) {
    insert1(L, word, totalpopulation, town);
}

void insert3(glob L, char word[50], char word1[50], int pop) {
    G temp = (G)malloc(sizeof(struct global));
    temp->next = NULL;
    temp->prev = NULL;
    strcpy(temp->named, word);
    strcpy(temp->namet, word1);
    temp->pop = pop;

    G hed = L;
    while (hed->next != NULL) hed = hed->next;
    hed->next  = temp;
    temp->prev = hed;
}

// ─── addnewdistricts ─────────────────────────────────────────────────────────

void addnewdistricts(List1 L, char name[50]) {
    Node1 newnode = (Node1)malloc(sizeof(struct districts));
    strcpy(newnode->data, name);
    newnode->allpop    = 0;
    newnode->next_town = NULL;
    newnode->next      = NULL;
    newnode->prev      = NULL;

    /* Append at end */
    Node1 temp = L;
    while (temp->next != NULL) temp = temp->next;
    temp->next   = newnode;
    newnode->prev = temp;
}

// ─── Delete district ─────────────────────────────────────────────────────────

void Deletedistricts(char namedis[50]) {
    if (unsort == NULL || isEmpty1(unsort)) return;

    Node1 temp = unsort->next;
    while (temp != NULL) {
        if (strcmp(temp->data, namedis) == 0) {

            /* Free all towns first */
            Node2 ptr2 = temp->next_town;
            while (ptr2 != NULL) {
                Node2 nxt = ptr2->next;
                free(ptr2);
                ptr2 = nxt;
            }
            temp->next_town = NULL;

            /* Unlink district node */
            if (temp->prev != NULL) temp->prev->next = temp->next;
            if (temp->next != NULL) temp->next->prev = temp->prev;

            free(temp);
            return;
        }
        temp = temp->next;
    }
    printf("District not found.\n");
}

// ─── Delete town ─────────────────────────────────────────────────────────────

void Deletetown(char nametown[50], List1 L, char district[50]) {
    Node1 disptr = L->next;
    while (disptr != NULL) {
        if (strcmp(disptr->data, district) == 0) {
            Node2 towptr = disptr->next_town;
            while (towptr != NULL) {
                if (strcmp(towptr->townname, nametown) == 0) {

                    /* Update district population */
                    disptr->allpop -= towptr->populatin;

                    /* BUG-FIX: correct doubly-linked pointer updates */
                    if (towptr->prev == NULL && towptr->next == NULL) {
                        /* only town */
                        disptr->next_town = NULL;
                    } else if (towptr->prev == NULL) {
                        /* first town */
                        disptr->next_town       = towptr->next;
                        towptr->next->prev      = NULL;
                    } else if (towptr->next == NULL) {
                        /* last town */
                        towptr->prev->next = NULL;
                    } else {
                        /* middle town */
                        towptr->prev->next = towptr->next;
                        towptr->next->prev = towptr->prev;
                    }
                    free(towptr);
                    return;
                }
                towptr = towptr->next;
            }
        }
        disptr = disptr->next;
    }
}

// ─── Max / Min town population ────────────────────────────────────────────────

int maxtowpop(List1 L) {
    int max = -1;
    Node1 t = L->next;
    while (t != NULL) {
        Node2 m = t->next_town;
        while (m != NULL) {
            if (m->populatin > max) max = m->populatin;
            m = m->next;
        }
        t = t->next;
    }
    return max;
}

int mintowpop(List1 L) {
    /* BUG-FIX: initialise to a large value, not a pointer cast */
    int min = 2147483647;
    Node1 t = L->next;
    while (t != NULL) {
        Node2 m = t->next_town;
        while (m != NULL) {
            if (m->populatin < min) min = m->populatin;
            m = m->next;
        }
        t = t->next;
    }
    return min;
}

// ─── Change population ────────────────────────────────────────────────────────

void changepop(List1 L, char dis[50], char town[50]) {
    int pop;
    Node1 t = L->next;
    while (t != NULL) {
        if (strcmp(t->data, dis) == 0) {
            t->allpop = 0;
            Node2 ch = t->next_town;
            while (ch != NULL) {
                if (strcmp(ch->townname, town) == 0) {
                    printf("Enter new population: ");
                    scanf("%d", &pop);
                    ch->populatin = pop;
                }
                t->allpop += ch->populatin;
                ch = ch->next;
            }
            return;
        }
        t = t->next;
    }
}

// ─── Bubble sort towns ────────────────────────────────────────────────────────

void buble(List1 L) {
    Node1 D = L->next;
    while (D != NULL) {
        Node2 t = D->next_town;
        if (t == NULL) { D = D->next; continue; }

        int swapped;
        do {
            swapped = 0;
            Node2 cur = D->next_town;
            while (cur != NULL && cur->next != NULL) {
                if (cur->populatin > cur->next->populatin) {
                    /* swap population and name */
                    int tmp = cur->populatin;
                    cur->populatin       = cur->next->populatin;
                    cur->next->populatin = tmp;

                    char tmp2[50];
                    strcpy(tmp2, cur->townname);
                    strcpy(cur->townname, cur->next->townname);
                    strcpy(cur->next->townname, tmp2);

                    swapped = 1;
                }
                cur = cur->next;
            }
        } while (swapped);

        D = D->next;
    }
}

// ─── Radix Sort ───────────────────────────────────────────────────────────────

int getMaxNumOfChar(List1 L) {
    int max = 0;
    if (isEmpty1(L)) return 0;
    Node1 ptr = L->next;
    while (ptr != NULL) {
        int len = strlen(ptr->data);
        if (len > max) max = len;
        ptr = ptr->next;
    }
    return max;
}

void addspase(List1 L) {
    int max = getMaxNumOfChar(L);
    Node1 cur = L->next;
    while (cur != NULL) {
        int len = (int)strlen(cur->data);
        int add = max - len;
        for (int i = 0; i < add; i++)
            strncat(cur->data, " ", sizeof(cur->data) - strlen(cur->data) - 1);
        cur = cur->next;
    }
}

/*  Insert a *copy* of src into list L at the end.
    BUG-FIX: original Insert() did not copy town sub-list, leading to dangling
    pointers after Radix Sort freed old nodes.  We now copy district data only
    and keep the town pointer intact by re-linking after sort.              */
void Insert(List1 L, Node1 src) {
    Node1 newN = (Node1)malloc(sizeof(struct districts));
    strcpy(newN->data, src->data);
    newN->allpop    = src->allpop;
    newN->next_town = src->next_town;   /* share town sub-list for now */
    newN->next      = NULL;
    newN->prev      = NULL;

    Node1 last = L;
    while (last->next != NULL) last = last->next;
    last->next  = newN;
    newN->prev  = last;
}

void DeleteList(List1 L) {
    Node1 cur = L->next;
    while (cur != NULL) {
        Node1 nxt = cur->next;
        /* BUG-FIX: do NOT free towns here – they are owned by the original list */
        free(cur);
        cur = nxt;
    }
    free(L);
}

void RadixSort(List1 L) {
    if (isEmpty1(L)) return;

    int maxLen = getMaxNumOfChar(L);
    addspase(L);

    /* 63 buckets: 0=space, 1-10=digits, 11-36=A-Z, 37-62=a-z */
    List1 R_array[63];
    for (int x = 0; x < 63; x++) R_array[x] = createList1();

    for (int P = maxLen - 1; P >= 0; P--) {
        /* distribute */
        Node1 cur = L->next;
        while (cur != NULL) {
            char c = cur->data[P];
            int idx;
            if      (c == ' ')                     idx = 0;
            else if (c >= '0' && c <= '9')         idx = c - '0' + 1;
            else if (c >= 'A' && c <= 'Z')         idx = c - 'A' + 11;
            else if (c >= 'a' && c <= 'z')         idx = c - 'a' + 37;
            else                                    idx = 0;

            Insert(R_array[idx], cur);
            cur = cur->next;
        }

        /* collect back into L */
        /* First clear L's chain (don't free – nodes owned by R_array copies) */
        /* BUG-FIX: rebuild L->next chain from bucket copies, free old nodes */
        Node1 old = L->next;
        while (old != NULL) {
            Node1 nxt = old->next;
            free(old);          /* free old shell; towns not freed */
            old = nxt;
        }
        L->next = NULL;

        Node1 tail = L;
        for (int i = 0; i < 63; i++) {
            Node1 bcur = R_array[i]->next;
            while (bcur != NULL) {
                Node1 bnxt = bcur->next;
                bcur->next = NULL;
                bcur->prev = tail;
                tail->next = bcur;
                tail       = bcur;
                bcur       = bnxt;
            }
            R_array[i]->next = NULL;
        }
    }

    /* Free bucket header nodes */
    for (int i = 0; i < 63; i++) free(R_array[i]);

    /* Trim trailing spaces from district names */
    Node1 ptr = L->next;
    while (ptr != NULL) {
        int len = (int)strlen(ptr->data);
        while (len > 0 && ptr->data[len - 1] == ' ') {
            ptr->data[--len] = '\0';
        }
        ptr = ptr->next;
    }
}

// ─── Print functions ─────────────────────────────────────────────────────────

void Print_Sorted_Strings(List1 L) {
    printf("Sorted Districts:\n");
    printList(L);
}

void printList(List1 L) {
    Node1 T = L->next;
    while (T != NULL) {
        printf("%s\n", T->data);
        T = T->next;
    }
    printf("\n");
}

void printList1(List1 L) {
    if (L == NULL)       { printf("List Not Found.\n"); return; }
    if (isEmpty1(L))     { printf("List is empty.\n");  return; }

    Node1 temp = L->next;
    while (temp != NULL) {
        printf("%s | %d\n", temp->data, temp->allpop);
        printf("Towns:\n");
        Node2 tt = temp->next_town;
        while (tt != NULL) {
            printf("\t%s | %d\n", tt->townname, tt->populatin);
            tt = tt->next;
        }
        temp = temp->next;
    }
    printf("\n");
}

/* BUG-FIX: signature fixed – original had two params but body used only one */
void printList11(List1 L) {
    if (L == NULL)       { printf("List Not Found.\n"); return; }
    if (isEmpty1(L))     { printf("List is empty.\n");  return; }

    Node1 temp = L->next;
    while (temp != NULL) {
        printf("%s District, Population = %d\n", temp->data, temp->allpop);
        Node2 tt = temp->next_town;
        while (tt != NULL) {
            printf("  %s, %d\n", tt->townname, tt->populatin);
            tt = tt->next;
        }
        temp = temp->next;
    }
    printf("\n");
}

void printDistricts(List1 L) {
    if (L == NULL)       { printf("List Not Found.\n"); return; }
    if (isEmpty1(L))     { printf("List is empty.\n");  return; }

    Node1 temp = L->next;
    while (temp != NULL) {
        printf("%s | %d\n", temp->data, temp->allpop);
        temp = temp->next;
    }
    printf("\n");
}

void printList3(glob L) {
    if (L == NULL) return;

    glob temp = L->next;
    while (temp != NULL) {
        /* BUG-FIX: original called isEmpty1(L) on a glob pointer – removed */
        printf("%s | %s | %d\n", temp->named, temp->namet, temp->pop);
        temp = temp->next;
    }
    printf("\n");
}

// ─── File I/O ────────────────────────────────────────────────────────────────

void readInputFile() {
    FILE* input;
    char fileName[100];
    printf("Please enter the name of input file:\n");
    scanf("%s", fileName);

    input = fopen(fileName, "r");
    while (input == NULL) {
        printf("Failed to open file. Please enter the name of input file:\n");
        scanf("%s", fileName);
        input = fopen(fileName, "r");
    }

    char store[200];
    char tok[50];
    int i = 0;

    while (fgets(store, sizeof(store), input) != NULL) {
        /* Remove trailing newline */
        store[strcspn(store, "\r\n")] = '\0';

        char *token = strtok(store, "|");
        if (token == NULL) continue;
        /* BUG-FIX: trim leading/trailing spaces from tokens */
        while (*token == ' ') token++;
        char *end = token + strlen(token) - 1;
        while (end > token && *end == ' ') *end-- = '\0';
        strcpy(token1[i], token);

        token = strtok(NULL, "|");
        if (token == NULL) continue;
        while (*token == ' ') token++;
        end = token + strlen(token) - 1;
        while (end > token && *end == ' ') *end-- = '\0';
        strcpy(token2[i], token);

        token = strtok(NULL, "|");
        if (token == NULL) continue;
        strcpy(tok, token);
        token3 = atoi(tok);

        insert3(glopal, token1[i], token2[i], token3);
        insert1(unsort, token1[i], token3, token2[i]);
        insert11(extendedSortedList, token1[i], token3, token2[i]);
        i++;
    }
    fclose(input);
}

void saveOutputFile(List1 L) {
    FILE* output = fopen("output.txt", "w");
    if (output == NULL) { printf("Failed to create output file.\n"); return; }

    Node1 D = L->next;
    while (D != NULL) {
        fprintf(output, "%s District, Population = %d\n", D->data, D->allpop);
        Node2 T = D->next_town;
        while (T != NULL) {
            fprintf(output, "%s, %d\n", T->townname, T->populatin);
            T = T->next;
        }
        D = D->next;
    }
    fclose(output);
}

void deleteList1(List1 L) {
    if (L == NULL || isEmpty1(L)) return;
    Node1 ptr = L->next;
    L->next = NULL;
    while (ptr != NULL) {
        Node1 tmp = ptr->next;
        free(ptr);
        ptr = tmp;
    }
}

void removeZeros(List1 L) {
    /* trims trailing spaces – kept for completeness */
    Node1 ptr = L->next;
    while (ptr != NULL) {
        int len = (int)strlen(ptr->data);
        while (len > 0 && ptr->data[len-1] == ' ') ptr->data[--len] = '\0';
        ptr = ptr->next;
    }
}
