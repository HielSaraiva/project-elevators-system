#include <stdio.h>
#include <stdlib.h>

typedef struct passengers {
    char name[3]; // For example: P01, P06, P21
    int initial_floor;
    int final_floor;
    int direction; // 1 = up, -1 = down
    int call_cooldown;
} passengers;

typedef struct doubly_linked_passenger_list {
    passengers passengers;
    struct doubly_linked_passenger_list *next;
    struct doubly_linked_passenger_list *prev;
} passenger_list;

typedef struct doubly_linked_floor_list {
    int floor;
    struct doubly_linked_floor_list *next;
    struct doubly_linked_floor_list *prev;
} floor_list;

typedef struct elevators {
    char name[2]; // For example: E1, E4, E6
    int actual_floor;
    int direction; // 1 = up, -1 = down
    struct doubly_linked_floor_list **actual_route; // point to the actual route, that can be up_route or down_route
    struct doubly_linked_floor_list *up_route; // the route the elevator must follow if it's going up
    struct doubly_linked_floor_list *down_route; // the route the elevator must follow if it's going down
    struct doubly_linked_passenger_list *passengers_inside; // the passengers who are inside the elevator
    struct doubly_linked_passenger_list *passengers_to_enter; // the passengers that pressed the button and are waiting for enter the elevator
} elevators;

int search_floor_list(floor_list *list, int floor) {
    floor_list *aux = list;
    if (list != NULL) {
        while (aux != NULL) {
            if (aux->floor == floor) {
                return 1; // the floor already is in the list
            }
            aux = aux->next;
        }
    }
    return 0; // the floor is not in the list yet
}

int insert_floor_list(elevators *elevator, int floor) {
    // this function inserts the floor value in ascending order or in descending order, depending on elevator direction

    // verifying if the value to be added already is in the list (using && to short-circuit)
    if (!((elevator->actual_route) == NULL || *(elevator->actual_route) == NULL) && search_floor_list(*(elevator->actual_route), floor) == 1) {
        return 0; // the floor value was NOT added to the list because it already was in there
    }

    // adding the floor to the list
    if ((elevator->actual_route) == NULL || *(elevator->actual_route) == NULL) {
        // if the list is empty
        floor_list *aux = malloc(sizeof(floor_list));
        aux->floor = floor;
        aux->prev = NULL;
        aux->next = NULL;
        if (elevator->direction == 1) {
            elevator->up_route = aux;
            elevator->actual_route = &(elevator->up_route);
        } else {
            elevator->down_route = aux;
            elevator->actual_route = &(elevator->down_route);
        }
    } else {
        // if the list already has something
        floor_list *aux1 = malloc(sizeof(floor_list));

        // ascending order
        if (elevator->direction == 1) {
            // moving pointer to the immediately next value that is bigger than floor value
            floor_list *aux2 = elevator->up_route;
            while (floor > aux2->floor && aux2->next != NULL) {
                aux2 = aux2->next;
            }

            if (aux2 == elevator->up_route && floor < aux2->floor) {
                // it's at the beginning
                aux1->floor = floor;
                aux1->prev = NULL;
                aux1->next = elevator->up_route;
                elevator->up_route = aux1;
                aux2->prev = aux1;
            } else if (aux2->next == NULL && floor > aux2->floor) {
                // it's at the ending
                aux1->floor = floor;
                aux1->prev = aux2;
                aux1->next = NULL;
                aux2->next = aux1;
            } else {
                // it's at the middle
                aux2 = aux2->prev;
                aux1->floor = floor;
                aux1->prev = aux2;
                aux1->next = aux2->next;
                aux2->next = aux1;
                (aux1->next)->prev = aux1;
            }
        } else {
            // descending order

            // moving pointer to the last value that is bigger than floor value
            floor_list *aux2 = elevator->down_route;
            while (floor < aux2->floor && aux2->next != NULL) {
                aux2 = aux2->next;
            }

            if (aux2 == elevator->down_route && floor > aux2->floor) {
                // it's at the beginning
                aux1->floor = floor;
                aux1->prev = NULL;
                aux1->next = elevator->down_route;
                elevator->down_route = aux1;
                aux2->prev = aux1;
            } else if (aux2->next == NULL && floor < aux2->floor) {
                // it's at the ending
                aux1->floor = floor;
                aux1->prev = aux2;
                aux1->next = NULL;
                aux2->next = aux1;
            } else {
                // it's at the middle
                aux2 = aux2->prev;
                aux1->floor = floor;
                aux1->prev = aux2;
                aux1->next = aux2->next;
                aux2->next = aux1;
                (aux1->next)->prev = aux1;
            }
        }
    }
    return 1; // the floor value was added to the list
}

int remove_floor_list(elevators *elevator) {
    // this function removes floor value from beginning
    if (*(elevator->actual_route) == NULL) {
        return 0; // elevator actual_route is empty
    }
    floor_list *aux = *(elevator->actual_route);
    *(elevator->actual_route) = (*(elevator->actual_route))->next;
    if (*(elevator->actual_route) != NULL) {
        (*(elevator->actual_route))->prev = NULL;
    }
    free(aux);
    return 1;
}

// TO DO
void insert_passenger_list(elevators *elevator, passengers) {
}

// TO DO
int remove_passenger_list(elevators *elevator) {
    return 0;
}

int print_elevator_route(elevators *elevator) {
    if (*(elevator->actual_route) == NULL) {
        printf("[  ]\n");
        return 0; // up_route or down_route is empty
    }
    floor_list *aux = *elevator->actual_route;
    printf("[");
    while (aux != NULL) {
        if (aux->floor != 1) {
            printf(" %d", aux->floor);
        } else {
            printf(" T");
        }
        aux = aux->next;
        if (aux != NULL) {
            printf(" ->");
        }
    }
    printf(" ]\n");
    return 1;
}

// TO DO
int print_elevator_passengers(elevators *elevator) {
    return 0;
}

// TO DO (put printf to elevator_passengers to work)
void print_elevator(elevators *elevator) {
    printf("name: %s\n", elevator->name);
    if (elevator->actual_floor != 1) {
        printf("actual floor: %d\n", elevator->actual_floor);
    } else {
        printf("actual floor: T\n");
    }
    if (elevator->direction == 1) {
        printf("direction: S\n"); // S = "Subindo" = means "going up" in portuguese
    } else {
        printf("direction: D\n"); // D = "Descendo" = means "going down" in portuguese
    }
    print_elevator_route(elevator);
    print_elevator_passengers(elevator);
}

int main(void) {
    // manipulating script.txt


    // creating elevator(s)
    elevators elevator1 = {"E1", 4, 1, NULL, NULL, NULL, NULL, NULL};


    // creating passenger(s)


    // testing some functions
    insert_floor_list(&elevator1, 1);
    insert_floor_list(&elevator1, 9);
    insert_floor_list(&elevator1, 8);
    insert_floor_list(&elevator1, 11);
    insert_floor_list(&elevator1, 3);
    insert_floor_list(&elevator1, 4);
    // insert_floor_list(&elevator1, 8);
    print_elevator_route(&elevator1);

    remove_floor_list(&elevator1);
    print_elevator_route(&elevator1);
    remove_floor_list(&elevator1);
    remove_floor_list(&elevator1);
    remove_floor_list(&elevator1);
    remove_floor_list(&elevator1);
    print_elevator_route(&elevator1);
    remove_floor_list(&elevator1);
    print_elevator_route(&elevator1);

    insert_floor_list(&elevator1, 1);
    insert_floor_list(&elevator1, 9);
    insert_floor_list(&elevator1, 8);
    insert_floor_list(&elevator1, 11);
    insert_floor_list(&elevator1, 3);
    insert_floor_list(&elevator1, 4);
    insert_floor_list(&elevator1, 8);
    print_elevator_route(&elevator1);


    // closing application


    return 0;
}
