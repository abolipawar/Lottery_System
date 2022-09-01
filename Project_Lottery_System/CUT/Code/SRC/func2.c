/*****************************************************************************************************
**
**   FILENAME    :  func2.c
**
**  DESCRIPTION  : This file contains menu list for ZDA Authority under which thier is plot and
**		   participant database is stored. This file defines all the functions which are
**		   required to create and maintain plot and participant database.
**
** REVISION HISTORY :
** DATE             NAME            REASON
**-------------------------------------------------------------
** 25 Aug 2022   Username             Created menu and declared functions 
**
*****************************************************************************************************/


#include <stdio.h>   //It includes all the header files
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <termios.h>
#include <sys/types.h>
#include <unistd.h>
#include "functions.h"
#define MAXPW 32    //Macro defined

/****************************************************************************************************
**
** FUNCTION NAME  :  ZDA_Authority
** DESCRIPTION    :  This functions contains the menu for ZDA_Authority and all the required functions for
**               	ZDA_Authority.	
**  RETURN          : Returns EXIT_SUCCESS if successful else returns EXIT_FAILURE
**
****************************************************************************************************/

int ZDA_Authority()  //Defining ZDA_Authority function
{
	int choice_sub2=0;
	while(choice_sub2!=5){
		printf("\n         ZDA AUTHORITY \n");           //displaying menu for ZDA Authority
		printf("-----------------------------------\n");
		printf("1.Maintain Plot Datatbase\n2.Maintain Participant Database\n3.Generate Lottery Token\n4.View Lottery report\n5.Back to Main Menu");
		printf("\nEnter your choice: ");
		scanf("%d",&choice_sub2);           //taking user's choice
		switch(choice_sub2){


			case 1: maintain_plot_db(); //Calling maintain_plot_db function
				choice_sub2=0;
				break;
			case 2: maintain_participant_db(); //Calling maintain_participant_db function
				choice_sub2=0;
				break;
			case 3: initialize_queue(); //Calling Initialize_queue  function 
				choice_sub2=0;
				break;
			case 4: view_lottery_report(); //Calling view_lottery_report function 
				choice_sub2=0;
				break;
			case 5: break;
			default:
				printf("\n Invalid choice");
	
		}	
	}
	return EXIT_SUCCESS;
}



/****************************************************************************************************
**
** FUNCTION NAME  : maintain_participant_db
** DESCRIPTION    : This function contains the menu for maintaining participant database.
**		    it also calls the reuired functions to complete the operations.
**  RETURN          : Returns EXIT_SUCCESS if successful else returns EXIT_FAILURE
**
****************************************************************************************************/
int maintain_participant_db()
{
	int ch=0;
	while(ch!=5){                              //displaying menu
		printf("\n      MAINTAIN PARTICIPANT DATABASE \n");
		printf("-----------------------------------------------\n");

		printf("\n1.Add Participant\n2.Edit Participant\n3.Remove Participant\n4.View Participant details\n5.Back to Last  Menu");
		printf("\nEnter your choice: ");
		scanf("%d",&ch);
		switch(ch){
			case 1: add_participant();// Calling add_participant function
				ch=0;
				break;
			case 2: edit_participant();//Calling edit_participant function
				ch=0;
				break;
			case 3: remove_participant();//Calling remove_participant function
				ch=0;
				break;
			case 4:view_participant_details();//Calling view_participant_details function
				ch=0;
				break;
			case 5:
				break;
			default:
				printf("\nInvalid choice");

		}

	}
	return EXIT_SUCCESS;
}

/****************************************************************************************************
**
** FUNCTION NAME  : maintain_plot_db
** DESCRIPTION    : This function contains the menu for maintaining plot detail
**                  It also calls the functions add_plot,edit_plot,Delete_plot and view_plot_details 
**  RETURN          : Returns EXIT_SUCCESS if successful else returns EXIT_FAILURE
****************************************************************************************************/
int maintain_plot_db()
{
	int ch=0;
	while(ch!=5){                           //displaying menu 
		printf("\n            MAINTAIN PLOT DATABASE ");
		printf("\n-----------------------------------------------\n");

		printf("\n1.Add Plot\n2.Edit plot\n3.Remove Plot \n4.View Plot details\n5.Back to Last  Menu");
		printf("\nEnter your choice: ");
		scanf("%d",&ch);
		switch(ch){
			case 1: 
				add_plot();//Calling add_plot function
				ch=0;
				break;
			case 2: edit_plot();//Calling edit_plot function
				ch=0;
				break;
			case 3: delete_plot();//Calling delete_plot function
				ch=0;
				break;
			case 4: view_plot_details();//Calling view_plot_details
				ch=0;
				break;
			case 5:
				break;
			default:
				printf("\nInvalid choice");

		}

	}
	return EXIT_SUCCESS;
}





/****************************************************************************************************
**
** FUNCTION NAME  : view_lottery_report
** DESCRIPTION    : This Function displays the report for lottery ,containing details like serail_no,
**                  name,Family_id,Token,plot_no,amount to be paid.
**  RETURN          : Returns EXIT_SUCCESS if successful else returns EXIT_FAILURE
**
****************************************************************************************************/
int view_lottery_report(){
	if(!start1)
	{
		printf("\nThere is nothing to Display\n\n");
		return EXIT_FAILURE;
	}
	int count=0;       
	printf("                      LOTTERY REPORT     \n");      
	printf("----------------------------------------------------------------------\n");
	printf("Serial_No    Name    Family_id     Token      Plot_no    Remaining_Amount\n");
	printf("----------------------------------------------------------------------\n");
	for(ptr1=start1;(ptr1);ptr1=ptr1->next)
	{
		if(ptr1->plot_no!=0){
			count++;
			printf("\n%5d   %10s  %8d  %5d %5d %8.2lf \n",count,ptr1->name,ptr1->family_id,ptr1->token_no,ptr1->plot_no,ptr1->remaining_amount);
		}
	}
	return EXIT_SUCCESS;
}




/****************************************************************************************************
**
** FUNCTION NAME  : add_plot
** DESCRIPTION    : This functions accepts the plot details like plot number, size of the plot and
**                  price of the plot and checks for all the required validations.
**  RETURN          : Returns EXIT_SUCCESS if successful else returns EXIT_FAILURE
**
****************************************************************************************************/
int add_plot() //Function definition for Adding Record
{
	new=(pt *)malloc(sizeof(pt));
	if(new==NULL)
	{
		printf("\nMemory cannot be allocated\n\n");
		return EXIT_FAILURE;
	}
	while(1) //Validation loop for plot number
	{
		printf("Enter Plot Number: ");
		scanf("%d",&new->plot_no);
		if(new->plot_no<100 || new->plot_no>120)
		{
			printf("Invalid Plot number should be in range of 100-120\n");
			continue;
		}
		if(start)
		{
				for(ptr=start;(ptr) && ptr->plot_no!=new->plot_no ;ptr=ptr->next);
				if((ptr) && ptr->plot_no==new->plot_no)
				{
					printf("Duplicate plot number\n");
					continue;
				}
				else
				{
					break;
				}
		}
		else 
		{
			break;
		}

	}
	while(1) //Validation loop for plot size
	{

		printf("Enter Plot Size: ");
		scanf("%d",&new->size);
		if(new->size<100 || new->size>10000)	
		{
			printf("Invalid Plot size  should be in range 100-10000\n");
			continue;
		}
		else
		{
			break;
		}	
	}

	while(1) // Validation loop for plot price
	{

		printf("Enter Plot Price: ");
		scanf("%lf",&new->price);
		if(new->price<50000.00)
		{
			printf("Invalid Plot price cannot be less then 50000\n");
			continue;
		}
		else
		{
			break;
		}	
	}
	strcpy(new->allot,"NO");
	if(!start) //Inserting record inside the list
	{
		start=new;
		new->next=NULL;
	}
	else if(new->plot_no<start->plot_no)
	{
		new->next=start;
		start=new;
	}
	else 
	{
		for(ptr=start; (ptr) &&  ptr->plot_no<new->plot_no ;prev=ptr,ptr=ptr->next);		
		prev->next=new;
		new->next=ptr;
	}
	return EXIT_SUCCESS;
}


/****************************************************************************************************
**
** FUNCTION NAME  : edit_plot
** DESCRIPTION    : This functions edits the details for plot database.
**  RETURN          : Returns EXIT_SUCCESS if successful else returns EXIT_FAILURE
**
****************************************************************************************************/

int edit_plot()
	//Function definition for editing Literacy rate and population
{
	if(!start)
	{
		printf("\nNo Plot has added by ZDA Authority\n\n");
		return EXIT_FAILURE;
	}
	int code;
	printf("Enter Plot number: ");
	scanf("%d",&code);
	for(ptr=start;(ptr) && ptr->plot_no!=code;ptr=ptr->next);
	if(ptr==NULL)
	{
		printf("\nPlot not found\n\n");
		return EXIT_FAILURE;
	}
	printf("Old Plot size is %d and Plot Price is %lf \n",ptr->size,ptr->price);
	while(1)
	{

		printf("Enter new Plot size: ");
		scanf("%d",&ptr->size);
		if(ptr->size<100 || ptr->size>10000)
		{
			printf("Invalid Plot size should be in range 100-10000");
			continue;
		}
		else
		{
			break;
		}	
	}
	while(1)
	{

		printf("Enter new  Price: ");
		scanf("%lf",&ptr->price);
		if(ptr->price<50000)
		{
			printf("Invalid Price cannot be less then 50000\n");
			continue;
		}
		else
		{
			break;
		}	
	}
	return EXIT_SUCCESS;
}


/****************************************************************************************************
**
** FUNCTION NAME  : delete_plot
** DESCRIPTION    : this function modify's the plot details by deleting the required fileds.
**  RETURN          : Returns EXIT_SUCCESS if successful else returns EXIT_FAILURE
**
****************************************************************************************************/

int delete_plot() //For deleting a particular country record
{
	if(!start)
	{
		printf("No Plot has been added by ZDA Authority\n\n");
		return EXIT_FAILURE;
	}
	int code;
	printf("Enter Plot number: ");
	scanf("%d",&code);
	if(code==start->plot_no)
	{
		ptr=start;
		start=start->next;
		free(ptr);
	}
	else
	{
		for(ptr=start;(ptr) && ptr->plot_no!=code;prev=ptr,ptr=ptr->next);
		if(ptr==NULL)
		{
			printf("Plot number not found\n\n");
			return EXIT_FAILURE;
		}
		prev->next=ptr->next;
		free(ptr);
	}
	return EXIT_SUCCESS;
}



/****************************************************************************************************
**
** FUNCTION NAME  : view_plot_details
** DESCRIPTION    : This function displays the plot details like serial_no , plot_no, size and price
**  RETURN          : Returns EXIT_SUCCESS if successful else returns EXIT_FAILURE
**
**
****************************************************************************************************/

int view_plot_details()
	//Function definition for displaying Records
{
	if(!start)
	{
		printf("No Plot has been added by ZDA Authority\n\n");
		return EXIT_FAILURE;
	}
	int count=0;
	printf("                ALL PLOT DETAILS     \n");
	printf("--------------------------------------------\n");
	printf("\nSerial_No   Plot_No   Size   Price  Alloted\n");
	printf("---------------------------------------------\n");

	for(ptr=start;(ptr);ptr=ptr->next)
	{
		count++;
		printf("\n%5d   %5d  %8d     %5.2lf    %-4s\n",count,ptr->plot_no,ptr->size,ptr->price,ptr->allot);
	}
	return EXIT_SUCCESS;
}


/****************************************************************************************************
**
** FUNCTION NAME  : add_partcipant
** DESCRIPTION    : This function adds the participant details in the participant database.
**
**  RETURN          : Returns EXIT_SUCCESS if successful else returns EXIT_FAILURE
**
****************************************************************************************************/

int add_participant() //Function definition for Adding Record
{
	new1=(p *)malloc(sizeof(p));
	if(new1==NULL)
	{
		printf("\nMemory cannot be allocated\n\n");
		return EXIT_FAILURE;
	}
	while(1) //Validation loop for  Family Id
	{
		printf("Enter Family Id: ");
		scanf("%d",&new1->family_id);
		if(new1->family_id<1000 || new1->family_id>1200)
		{
			printf("Invalid Family ID should be between 1000-1200\n");
			continue;
		}
		if(start)
		{
				for(ptr1=start1;(ptr1) && ptr1->family_id!=new1->family_id ;ptr1=ptr1->next);
				if((ptr1) && ptr1->family_id==new1->family_id)
				{
					printf("Duplicate Family Id\n");
					continue;
				}
				else
				{
					break;
				}
		}
		else 
		{
			break;
		}
	}
	while(1) //Validation loop for Participant Name
	{
		printf("Enter Participant Name: ");
		scanf(" %[^\n]s",new1->name);
		int len=strlen(new1->name);
		if(len<5||len>30)
		{
			printf("Invalid length should be between 5 to 30 characters\n");
			continue;
		}
		int flag=0;
		for(int i=0;new1->name[i]!='\0';i++)
		{
			if(!isalpha(new1->name[i]))
			{
				flag=1;
				break;
			}	
		}
		if(flag==1)
		{
			printf("Name should have alphabets only\n");
			continue;
		}
		else
		{
			break;
		}
	}
	new1->token_no=0;
	new1->remaining_amount=0;
	new1->size=0;
	new1->plot_no=0;
	strcpy(new1->participated_in_lottery,"NO");
	if(start1==NULL) //Inserting record inside the list
	{
		start1=new1;
		new1->next=NULL;
	}
	else if(new1->family_id<start1->family_id)
	{
		new1->next=start1;
		start1=new1;
	}
	else
	{
		for(ptr1=start1;(ptr1) &&  ptr1->family_id<new1->family_id;prev1=ptr1,ptr1=ptr1->next);
		prev1->next=new1;
		new1->next=ptr1;
	}
	return EXIT_SUCCESS;

}


/****************************************************************************************************
**
** FUNCTION NAME  :  edit_participant
** DESCRIPTION    :  This functions edit the detaild in the participant database.
**  RETURN          : Returns EXIT_SUCCESS if successful else returns EXIT_FAILURE
**
****************************************************************************************************/


int edit_participant()
	//Function definition for editing name
{
	if(!start1)
	{
		printf("\nEmpty List\n\n");
		return EXIT_FAILURE;
	}
	int code;
	printf("Enter Family Id:");
	scanf("%d",&code);
	for(ptr1=start1;(ptr1) && ptr1->family_id!=code;ptr1=ptr1->next);
	if(ptr1==NULL)
	{
		printf("\nParticipant not found\n\n");
		return EXIT_FAILURE;
	}
	printf("Old participant name is %s",ptr1->name);
	while(1) //Validation loop for Country Name
	{
		printf("\nEnter new Participant Name: ");
		scanf(" %[^\n]s",new1->name);
		int len=strlen(new1->name);
		if(len<4||len>30)
		{
			printf("Invalid length should be between 5 to 30 characters\n");
			continue;
		}
		int flag=0;
		for(int i=0;new1->name[i]!='\0';i++)
		{
			if(!isalpha(new1->name[i]))
			{
				flag=1;
				break;
			}	
		}
		if(flag==1)
		{
			printf("Name should have alphabets only\n");
			continue;
		}
		else
		{
			break;
		}
	}
	return EXIT_SUCCESS;
}

/****************************************************************************************************
**
** FUNCTION NAME  : view_participant_details
** DESCRIPTION    : This function displays all the details of the participants like serial no, name,
**                  token no , plot no,amount to be paid.
**  RETURN          : Returns EXIT_SUCCESS if successful else returns EXIT_FAILURE
**
****************************************************************************************************/
int view_participant_details()
{
	if(!start1)
	{
		printf("\nEmpty List\n\n");
		return EXIT_FAILURE;
	}
	int count=0;
	printf("                                   ALL PARTICIPANT  DETAILS     \n");
	printf("----------------------------------------------------------------------------------------------------------\n");
	printf("\nSerial_No  Name  Family_id   Token    Plot_no   Plot_Size   Remaining_Amount    Participated_in_Lottery\n");
	printf("-----------------------------------------------------------------------------------------------------------\n");

	for(ptr1=start1;(ptr1);ptr1=ptr1->next)
	{
		count++;
		printf("\n%5d   %-10s  %8d  %5d %5d %5d  %8.2lf %-5s\n",count,ptr1->name,ptr1->family_id,ptr1->token_no,ptr1->plot_no,ptr1->size,ptr1->remaining_amount,ptr1->participated_in_lottery);
	}
	return EXIT_SUCCESS;
}


/****************************************************************************************************
**
** FUNCTION NAME  : remove_participant
** DESCRIPTION    : This function removes the participant from participant details.
**  RETURN          : Returns EXIT_SUCCESS if successful else returns EXIT_FAILURE
**
****************************************************************************************************/
int remove_participant() //For deleting a particular participant
{
	if(!start1)
	{
		printf("\nNo Participant has been added by ZDA Authority\n\n");
		return EXIT_FAILURE;
	}
	int code;
	printf("Enter Family Id : ");
	scanf("%d",&code);
	if(code==start1->family_id)
	{
		ptr1=start1;
		start1=start1->next;
		free(ptr1);
	}
	else
	{
		for(ptr1=start1;(ptr1) && ptr1->family_id!=code;prev1=ptr1,ptr1=ptr1->next);
		if(ptr1==NULL)
		{
			printf("\nParticipant  not found\n\n");
			return EXIT_FAILURE;
		}
		prev1->next=ptr1->next;
		free(ptr1);
	}
	return EXIT_SUCCESS;
}





/****************************************************************************************************
**
** FUNCTION NAME  : getpasswd
** DESCRIPTION    : This function provides  the password for ZDA Authority .
**  RETURN          : Returns EXIT_SUCCESS if successful else returns EXIT_FAILURE
**
****************************************************************************************************/
ssize_t getpasswd (char **pw, size_t sz, int mask, FILE *fp)
{
    if (!pw || !sz || !fp) return -1;       /* validate input   */
#ifdef MAXPW
    if (sz > MAXPW) sz = MAXPW;
#endif

    if (*pw == NULL) {              /* reallocate if no address */
        void *tmp = realloc (*pw, sz * sizeof **pw);
        if (!tmp)
            return -1;
        memset (tmp, 0, sz);    /* initialize memory to 0   */
        *pw =  (char*) tmp;
    }

    size_t idx = 0;         /* index, number of chars in read   */
    int c = 0;

    struct termios old_kbd_mode;    /* orig keyboard settings   */
    struct termios new_kbd_mode;

    if (tcgetattr (0, &old_kbd_mode)) { /* save orig settings   */
        fprintf (stderr, "%s() error: tcgetattr failed.\n", __func__);
        return -1;
    }   /* copy old to new */
    memcpy (&new_kbd_mode, &old_kbd_mode, sizeof(struct termios));

    new_kbd_mode.c_lflag &= ~(ICANON | ECHO);  /* new kbd flags */
    new_kbd_mode.c_cc[VTIME] = 0;
    new_kbd_mode.c_cc[VMIN] = 1;
    if (tcsetattr (0, TCSANOW, &new_kbd_mode)) {
        fprintf (stderr, "%s() error: tcsetattr failed.\n", __func__);
        return -1;
    }

    /* read chars from fp, mask if valid char specified */
    while (((c = fgetc (fp)) != '\n' && c != EOF && idx < sz - 1) ||
            (idx == sz - 1 && c == 127))
    {
        if (c != 127) {
            if (31 < mask && mask < 127)    /* valid ascii char */
                fputc (mask, stdout);
            (*pw)[idx++] = c;
        }
        else if (idx > 0) {         /* handle backspace (del)   */
            if (31 < mask && mask < 127) {
                fputc (0x8, stdout);
                fputc (' ', stdout);
                fputc (0x8, stdout);
            }
            (*pw)[--idx] = 0;
        }
    }
    (*pw)[idx] = 0; /* null-terminate   */

    /* reset original keyboard  */
    if (tcsetattr (0, TCSANOW, &old_kbd_mode)) {
        fprintf (stderr, "%s() error: tcsetattr failed.\n", __func__);
        return -1;
    }

    if (idx == sz - 1 && c != '\n') /* warn if pw truncated */
        fprintf (stderr, " (%s() warning: truncated at %zu chars.)\n",
                __func__, sz - 1);

    return idx; /* number of chars in passwd    */
}




/****************************************************************************************************
**
** FUNCTION NAME  : initialize_queue
** DESCRIPTION    : This Function is used to initialize tokens in queue.
**
****************************************************************************************************/
int initialize_queue()
{
	int token=-1;
	for(ptr1=start1;(ptr1);ptr1=ptr1->next)
	{
		if(ptr1->token_no>token)
		{
			token=ptr1->token_no;
		}
	}
	for(int i=1;i<=10;i++)
	{
		enque(token+i);                      //calling enque for inserting in queue.
	}
	return EXIT_SUCCESS;
}


/****************************************************************************************************
**
** FUNCTION NAME  : enque
** DESCRIPTION    : This Function is used to insert tokens in queue.
**
****************************************************************************************************/

void enque(int token)
{
	new_queue=(q1 *)malloc(sizeof(q1));       //allocating memory for queue
	if(new_queue==NULL)
	{
		printf("\nMemory cannot be allocated\n\n");
	}
	else
	{
		new_queue->token=token;
		if(front==NULL)                           //checking if queue if empty
		{
			front=rear=new_queue;
			new_queue->next=NULL;
		}
		else                                     //inserting data into already existing queue
		{
			rear->next=new_queue;
			rear=new_queue;
			new_queue->next=NULL;
		}
	}
}

/****************************************************************************************************
**
** FUNCTION NAME  : deque
** DESCRIPTION    : This Function is used to delete tokens from queue.
** RETURNS        : returns token if successfull else return FAILURE;
**
****************************************************************************************************/
int deque()
{
	int token;
	if(front==NULL)         //checking if queue is empty 
	{
		printf("\nThere is no token available\n\n");
		return 0;
	}
	else
	{
		ptr_queue=front;
		front=front->next;
		token=ptr_queue->token;
		free(ptr_queue);     //releasing memory
		ptr_queue=NULL;    
	}
	return token;
}
