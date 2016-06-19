#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct person_ll {
    char szName[12];
    struct person_ll* next;
};

int compare_person(const void *a, const void *b) {
    struct person_ll *person_a = *(struct person_ll **) a;
    struct person_ll *person_b = *(struct person_ll **) b;
    return strcmp(person_a->szName,person_b->szName);
}

int add_person_sorted(struct person_ll **person_ll,struct person_ll *new_person) {
    struct person_ll *loop = NULL;
    struct person_ll *previous = NULL;
    int  bFound = 0;
    
    loop = *person_ll;

    while (loop) {
        int iCompare = strcmp(loop->szName,new_person->szName);
        printf("Compare Person: %s with %s result: %d\n",loop->szName,new_person->szName,iCompare);
        if (iCompare>=0 ) {
            printf("Adding before Person: %p = %s\n",loop,loop->szName);
            bFound = 1;
            if (previous ==NULL) {
                // add to head
                new_person->next=*person_ll;
                *person_ll = new_person;
            } else {
                previous->next = new_person;
                new_person->next = loop;
            }
            break;
        }
        previous = loop;
        loop = loop->next;
    }
    if (!bFound ) {
        if (*person_ll != NULL) {
            // add to end of list
            previous->next = new_person; 
            new_person->next = NULL;
        } else {
            // the list was empty at the start
            *person_ll = new_person;
        }
    }
}

void write_person_ll(struct person_ll *person_ll ) {
    struct person_ll *loop = NULL;
    loop = person_ll;
    while (loop) {
        printf("Person: %p = %s\n",loop,loop->szName);
        loop = loop->next;
    }
}

void write_person_list(struct person_ll **list, int iNrofEntries ) {
    int i = 0;

    for(i=0;i<iNrofEntries;i++) {
        printf("Person:%d, %p = %s\n",i,list[i],list[i]->szName);
    }

}

int sort_person(struct person_ll **person_ll ) {
    struct person_ll *loop = NULL;
    struct person_ll **list = NULL;
    struct person_ll *sortedList = NULL;
    
    int i =0;
    int iNrofEntries = 0;

    // allocate enough memory
    loop = *person_ll;
    while (loop) {
        loop = loop->next;
        i++;
    }
    iNrofEntries = i;

    list = (struct person_ll **) malloc (sizeof(struct person_ll *) * (iNrofEntries));
    
    loop = *person_ll;
 //   list = (struct person_ll **) malloc (sizeof(struct person_ll *));
    i=0;
    while (loop) {
   //     list[i] = (struct person_ll *) malloc (sizeof(struct person_ll *));
        list[i] = loop;
        loop = loop->next;
        i++;
    }
    iNrofEntries = i;
    
    write_person_list(list,iNrofEntries);
    
    qsort(list,iNrofEntries,sizeof(struct person_ll *),compare_person);
    
    sortedList = list[0];
    loop =sortedList;
    for(i=1;i<iNrofEntries;i++) {
        loop->next = list[i];
        loop = loop->next;
    }
    loop->next = NULL;
    
    //free the pointers in the temp list
    free(list);
    
    *person_ll = sortedList;
}

int main()
{
    struct person_ll person1;
    struct person_ll person2;
    struct person_ll person3;
    struct person_ll person4;
    struct person_ll person5;
    struct person_ll person6;
    struct person_ll *list = &person1;
    
    strcpy(person1.szName, "Frank");
    strcpy(person2.szName, "Kees");
    strcpy(person3.szName, "Anke");
    strcpy(person4.szName, "Bert");
    strcpy(person5.szName, "Aafje");
    strcpy(person6.szName, "Xmen");
    person1.next = &person2;
    person2.next = &person3;
    person3.next = NULL;
    
    write_person_ll(list);
    
    sort_person(&list);
    printf("After sort:\n");
    write_person_ll(list);
    
    add_person_sorted(&list,&person4);
    printf("After adding Bert:\n");
    write_person_ll(list);
    
    add_person_sorted(&list,&person5);
    printf("After adding Aafje:\n");
    write_person_ll(list);
    
    add_person_sorted(&list,&person6);
    printf("After adding Xmen:\n");
    write_person_ll(list);
    
    return 0;
}

