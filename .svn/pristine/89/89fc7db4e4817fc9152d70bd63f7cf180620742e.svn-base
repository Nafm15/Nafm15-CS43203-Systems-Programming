/*CS4-53230: Systems Programming \
/*Name: Nafees Mahmood \
/*Date: 1/17/2020 \
/*Assignment#1 Warm Up \
*/

#include <stdio.h>
#include <stdlib.h>

/*structure containing the information about the list*/

struct numlist{
    float *list;
    int len;
    float min;
    float max;
    float avg;
};

/*compute_stats function initializes the min,max and avg of the structure
parameter:listptr - pointer to the numlist structure
*/

void compute_stats(struct numlist *listptr){
    if(listptr->len > 0)  //if len < 1, no element in the list and no need to initialize the members
    {
        float min = (listptr->list)[0]; //min is 1st element
        float max = (listptr->list)[0]; //max is 1st element
        float sum = (listptr->list)[0]; //adds all the elements of the list

        for(int i = 1; i <listptr->len; i++) //traverses the list
        {
            if((listptr->list)[i] > max) //if any element > max, update max
                max = (listptr->list)[i];
            else if((listptr->list)[i] < min) //if any element < min, update min
                min = (listptr->list)[i];

            sum += (listptr->list)[i]; //adds the elements
        }

        listptr->min = min;  //update the min of the structure
        listptr->max = max;  //update the max of the structure
        listptr->avg = sum/(listptr->len);  //update the sum of the structure
    }
}

/*display function shows all the members of the numlist structure */
void display(struct numlist *ptr){
    printf("\n--list--\n");
    for(int i = 0; i < ptr->len; i++)  //traverses the list
    {
        printf("%.2f", (ptr->list)[i]);
    }

    printf("\nlength of the list: %d", ptr->len);
    printf("\nmax element in the list: %.2f", ptr->max);
    printf("\nmin element in the list: %.2f", ptr->min);
    printf("\nAverage: %.2f\n", ptr->avg);
}

/*main function to initialize the program */

int main(int argc, char *argv[])
{
    struct numlist *ptr;  //pointer to the numlist structure
    ptr = (struct numlist*)malloc(sizeof(struct numlist));  //allocates memory for the structure
    if(NULL == ptr)
    {
        printf("Memory allocation failed!");
        exit(-1);
    }

    int size;
    if(size > 0)
    {
        printf("Enter the number of elements: ");
        scanf("%d", &size);
    }

    ptr->list = (float *)malloc(sizeof(float)*size);  //allocate memory for the list of size specified by the size variable
    if(NULL == ptr->list)  //if memory allocation fails
    {
        printf("Memory allocation failed!");
        exit(-1);
    }

    ptr->len = size;  //len member of the structure is initialized

    for(int i = 0; i < ptr->len; i++)  //traverse the empty list
    {
        printf("Enter the element %d: ", i+1);
        scanf("%f", &(ptr->list)[i]);  //stores element entered by user
    }

    compute_stats(ptr);  //calls the compute_stats function to initialize all other members
    display(ptr);  //displays numlist structure

}
