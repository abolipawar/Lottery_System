/********************************************************************************************


**     FILENAME      :         func1.c
**
**    DESCRIPTION    :      This File contains  the menu list for Participant Corner which contains functions like Grab A token,
**			     Participate in Lottery, View Allotment Details .
**
** Revision History  :      
**  DATE            NAME              REASON
**--------------------------------------------------------------------
** 25 AUG 2022       Username       Creation of File, Creating MENU List.
**
*****************************************************************************************/

#include <stdio.h>            
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <pthread.h>
#include <unistd.h>
#include "functions.h"                          


/*******************************************************************************************

**
**  FUNCTION NAME   : Participant_Corner
**  DESCRIPTION     : In this function it displays the menu list for Participant corner
**  RETURN          : Return EXIT_SUCCESS  
**

*******************************************************************************************/

pthread_mutex_t accum_mutex = PTHREAD_MUTEX_INITIALIZER;
int Participant_Corner()
{
	int choice_sub1=0;
	pthread_t th;
	while(choice_sub1!=5)
	{

		printf("\n              Participant Corner");
		printf("\n------------------------------------------------");
		printf("\n1.Grab a Token \n2.Cancel Token \n3.Participate in Lottery \n4.View Allotment Details\n5.Back to Main Menu");
		printf("\nEnter your choice: ");
		scanf("%d",&choice_sub1);
		switch(choice_sub1)
		{
			case 1: pthread_create(&th, NULL,(void *)grab_token,NULL);
       				pthread_join(th,NULL);
				choice_sub1=0;
				break;
			case 2: cancel_token();
				choice_sub1=0;
				break;
			case 3: participate_in_lottery();
				choice_sub1=0;
				break;
			case 4: view_allotment_details();
				choice_sub1=0;
				break;
			case 5:
				break;
			default:
				printf("Invalid choice");
		}
	}
	return  EXIT_SUCCESS;
}


/*******************************************************************************************************

**
**  FUNCTION NAME   : grab_token
**  DESCRIPTION     : In this function the participant grabs a token id to enter in the lottery process
**  RETURN          : Returns EXIT_SUCCESS if successful else returns EXIT_FAILURE
**

*******************************************************************************************************/


int grab_token(){  
   
	int code;
	int token;
	printf("Enter Family Id: ");
	scanf("%d",&code);
	for(ptr1=start1;(ptr1) && ptr1->family_id!=code;ptr1=ptr1->next);
	if(!ptr1)
	{
		printf("\nParticipant not exist with this family id\n\n");
		return EXIT_FAILURE;
	}
	if(ptr1->token_no!=0)
	{
		printf("\nYou have already grabed a token\n\n");
		return EXIT_FAILURE;
	}
	token=deque();
	if(token!=0)
	{
		pthread_mutex_lock(&accum_mutex);
			ptr1->token_no=token;
			printf("\nYour Token number is %d\n\n",token);
		pthread_mutex_unlock(&accum_mutex);
	}
	return  EXIT_SUCCESS;
}



/*******************************************************************************************************

**
**  FUNCTION NAME   : cancel_token
**  DESCRIPTION     : In this function the participant grabs a token id to enter in the lottery process
**  RETURN          : Returns EXIT_SUCCESS if successful else returns EXIT_FAILURE
**

*******************************************************************************************************/

int cancel_token(){  
   
	int code;
	int token;
	printf("Enter Family Id: ");
	scanf("%d",&code);
	for(ptr1=start1;(ptr1) && ptr1->family_id!=code;ptr1=ptr1->next);
	if(!ptr1)
	{
		printf("\nParticipant not exist with this family id\n\n");
		return EXIT_FAILURE;
	}
	if(ptr1->token_no==0)
	{
		printf("\nYou have not grabed a token\n\n");
		return EXIT_FAILURE;
	}
	if((strcmp(ptr1->participated_in_lottery,"YES")==0))
	{
		printf("\nYou have already participated in lottery\nNow you cannot cancel your token\n\n");
	}
	if(ptr1->token_no!=0 && (strcmp(ptr1->participated_in_lottery,"NO")==0))
	{
		ptr1->token_no=0;
		printf("\nYour token has been cancelled successfully\n\n");
	}
	return  EXIT_SUCCESS;
}



/*******************************************************************************************************

**
**  FUNCTION NAME   : participate_in_lottery 
**  DESCRIPTION     : In this function the participant grabs a token id to enter in the lottery process
**  RETURN          : Returns EXIT_SUCCESS if successful else returns EXIT_FAILURE
**

*******************************************************************************************************/

int participate_in_lottery()
{
	int code;
	int lottery_no;
	printf("Enter Family Id: ");
	scanf("%d",&code);
	for(ptr1=start1;(ptr1) && ptr1->family_id!=code ;ptr1=ptr1->next);
	if(!ptr1) 
	{
		printf("\nParticipant with this family id does not exist\n\n");
		return EXIT_FAILURE;
	}
	if(ptr1->token_no==0)
	{
		printf("\nPartcipant has not grab the token\n\n");
		return EXIT_FAILURE;
	}
	if(strcmp(ptr1->participated_in_lottery,"YES")==0)
	{
		printf("\nParticipant you have already participated in lottery\n\n");
		return EXIT_FAILURE;
	}
	if(ptr1->plot_no!=0)
	{
		printf("\nPlot has been already alloted to you!!!\n\n");
		return EXIT_FAILURE;
	}
	lottery_no=(rand() %(UPPER - LOWER + 1)) + LOWER;
	for(ptr=start;(ptr) && ptr->plot_no!=lottery_no;prev=ptr,ptr=ptr->next);
	if((ptr) && ptr->plot_no==lottery_no && (strcmp(ptr->allot,"NO")==0))
	{
		printf("\nCongratulations You have won a lottery\n\n");
		ptr1->plot_no=ptr->plot_no;
		ptr1->size=ptr->size;
		ptr1->remaining_amount=(ptr->price-50000);
		strcpy(ptr->allot,"YES");	
	}
	else
	{
		printf("\nUnfortunately you have not won better luck next time\nWinning Lottery number is %d\n\n",lottery_no);
	}
	strcpy(ptr1->participated_in_lottery,"YES");	
	return  EXIT_SUCCESS;
}



/*******************************************************************************************************

**
**  FUNCTION NAME   : view_allotment_details
**  DESCRIPTION     : In this function the participant grabs a token id to enter in the lottery process
**  RETURN          : Returns EXIT_SUCCESS if successful else returns EXIT_FAILURE
**

*******************************************************************************************************/

int view_allotment_details(){
	if(!start1)
	{
		printf("\nNo Participant has been added by ZDA Authority\n\n");
		return EXIT_FAILURE;
	}
	int code;
	printf("Enter Family Id: ");
	scanf("%d",&code);
	for(ptr1=start1;(ptr1) && ptr1->family_id!=code ;ptr1=ptr1->next);
	if(!ptr1) 
	{
		printf("\nParticipant with this family id does not exist\n\n");
		return EXIT_FAILURE;
	}
	printf("                                   ALLOTMENT DETAILS              \n");
	printf("-----------------------------------------------------------------------------------------------------------------------\n");
	printf("\nSerial_No     Name   Family_id   Token    Plot_no    Plot_size     Remaining_Amount    Participated_in_Lottery\n");
	printf("-----------------------------------------------------------------------------------------------------------------------\n");
	int count=1;
	printf("\n%5d     %-10s    %8d     %5d    %5d    %5d      %8.2lf    %-5s\n\n",count,ptr1->name,ptr1->family_id,ptr1->token_no,ptr1->plot_no,ptr1->size,ptr1->remaining_amount,ptr1->participated_in_lottery);
	return  EXIT_SUCCESS;
}
