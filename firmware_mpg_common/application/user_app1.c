/**********************************************************************************************************************
File: user_app1.c                                                                

----------------------------------------------------------------------------------------------------------------------
To start a new task using this user_app1 as a template:
 1. Copy both user_app1.c and user_app1.h to the Application directory
 2. Rename the files yournewtaskname.c and yournewtaskname.h
 3. Add yournewtaskname.c and yournewtaskname.h to the Application Include and Source groups in the IAR project
 4. Use ctrl-h (make sure "Match Case" is checked) to find and replace all instances of "user_app1" with "yournewtaskname"
 5. Use ctrl-h to find and replace all instances of "UserApp1" with "YourNewTaskName"
 6. Use ctrl-h to find and replace all instances of "USER_APP1" with "YOUR_NEW_TASK_NAME"
 7. Add a call to YourNewTaskNameInitialize() in the init section of main
 8. Add a call to YourNewTaskNameRunActiveState() in the Super Loop section of main
 9. Update yournewtaskname.h per the instructions at the top of yournewtaskname.h
10. Delete this text (between the dashed lines) and update the Description below to describe your task
----------------------------------------------------------------------------------------------------------------------

Description:
This is a user_app1.c file template 

------------------------------------------------------------------------------------------------------------------------
API:

Public functions:


Protected System functions:
void UserApp1Initialize(void)
Runs required initialzation for the task.  Should only be called once in main init section.

void UserApp1RunActiveState(void)
Runs current task state.  Should only be called once in main loop.


**********************************************************************************************************************/

#include "configuration.h"
#define ledpart_one  1
#define ledpart_two  2
#define ledpart_three 3
/***********************************************************************************************************************
Global variable definitions with scope across entire project.
All Global variable names shall start with "G_UserApp1"
***********************************************************************************************************************/
/* New variables */
volatile u32 G_u32UserApp1Flags;                       /* Global state flags */


/*--------------------------------------------------------------------------------------------------------------------*/
/* Existing variables (defined in other files -- should all contain the "extern" keyword) */
extern volatile u32 G_u32SystemFlags;                  /* From main.c */
extern volatile u32 G_u32ApplicationFlags;             /* From main.c */

extern volatile u32 G_u32SystemTime1ms;                /* From board-specific source file */
extern volatile u32 G_u32SystemTime1s;                 /* From board-specific source file */


/***********************************************************************************************************************
Global variable definitions with scope limited to this local application.
Variable names shall start with "UserApp1_" and be declared as static.
***********************************************************************************************************************/
static fnCode_type UserApp1_StateMachine;            /* The state machine function pointer */
//static u32 UserApp1_u32Timeout;                      /* Timeout counter used across states */


/**********************************************************************************************************************
Function Definitions
**********************************************************************************************************************/

/*--------------------------------------------------------------------------------------------------------------------*/
/* Public functions                                                                                                   */
/*--------------------------------------------------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------------------------------------------------*/
/* Protected functions                                                                                                */
/*--------------------------------------------------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------------------------------------------------
Function: UserApp1Initialize

Description:
Initializes the State Machine and its variables.

Requires:
  -

Promises:
  - 
*/
void UserApp1Initialize(void)
{
 
  /* If good initialization, set state to Idle */
  if( 1 )
  {
       UserApp1_StateMachine= viclie;
    //UserApp1_StateMachine = UserApp1SM_Idle;
  }
  else
  {
    /* The task isn't properly initialized, so shut it down and don't run */
    UserApp1_StateMachine = UserApp1SM_FailedInit;
  }

}
  void viclie(void)//back and forth the led light
	{
      static u8 u8_counter = 0;//increase the number	 
      const  u16 u16_const = 1000;//const for second
      static u16 u16_constant_for =0;
      static BOOL B_turn_right_left = FALSE;
      static u8 u8_counter_led_patter2 =0; 
      static u8 u8_patter         =0 ;


	 ///other partern led display.
	 if(G_u32SystemTime1ms%5000==0)//5s延续
	 	{
	 	for(u8_counter=0;u8_counter<=7;u8_counter++)
	 	{
	 	    LedOff(u8_counter);
	 	}
	 	  u8_patter = ledpart_one;
		  u8_counter = 0;
		  u16_constant_for =0;
	 	}
	 else if(G_u32SystemTime1ms%10001==0)
	 	{
	 	  for(u8_counter=0;u8_counter<=7;u8_counter++)
	 	{
	 	    LedOff(u8_counter);
	 	}
	 	   u8_patter = ledpart_two;
		   u8_counter = 0;
		  u16_constant_for =0;
	 	}
	 else if (G_u32SystemTime1ms%15001 ==0)//容易出错的地方
	 	{
	 	for(u8_counter=0;u8_counter<=7;u8_counter++)
	 	{
	 	    LedOff(u8_counter);
	 	}
	 	u8_patter    = ledpart_three;
		u8_counter = 0;
		  u16_constant_for =0;
	 	}

	 ///led patter
	 switch (u8_patter)
	 	{
	 	case ledpart_three:///fade the led 
			if(G_u32SystemTime1ms%200==0)
				{for(u8_counter=0;u8_counter<=7;u8_counter++)
					{
					LedPWM(u8_counter,u16_constant_for);
					
					}
			      u16_constant_for++;
				  if(u16_constant_for==20)
				  	u16_constant_for=0;
				}
			break;
	 	case ledpart_one:
			 loop_pattern_one:	 if(u16_constant_for<=u16_const/(u8_counter*6+1))//loop:
								 	{
								 	 //if(B_turn_right_left==FALSE)
								 	  LedOn(4+u8_counter);//forth
									// else
									  LedOn(3-u8_counter);//back
									  //u8
									  u16_constant_for++;
							                  //u8_counter++;
								 	}
						 else
						 	{
								//if(B_turn_right_left == FALSE)
									
							 	LedOff(4+u8_counter);								//else
								LedOff(3-u8_counter);
							 	u16_constant_for = 0;
								if(u8_counter==3)
						                {
						            if(B_turn_right_left==FALSE)
										B_turn_right_left = TRUE;
									else
										B_turn_right_left=FALSE;
									u8_counter   =0;
									goto loop_pattern_one;

									//break;
						                }
			                u8_counter++;
					//
				 	}
		 break;
		 case ledpart_two:
	 
			  loop_pattern_two:	 if(u16_constant_for<=u16_const/(u8_counter*6+1))//loop:
				 	{
				 	 if(B_turn_right_left==FALSE)
				 	  LedOn(u8_counter);//forth
					 else
					  LedOn(7-u8_counter);//back
					  //u8
					  u16_constant_for++;
			                  //u8_counter++;
				 	}
				 else
				 	{
				 	if(B_turn_right_left == FALSE)
						
				 	LedOff(u8_counter);
					else
						LedOff(7-u8_counter);
				 	u16_constant_for = 0;
					if(u8_counter==7)
			                {
			            if(B_turn_right_left==FALSE)
							B_turn_right_left = TRUE;
						else
							B_turn_right_left=FALSE;
						u8_counter   =0;
						goto loop_pattern_two;

						//break;
			                }
			                u8_counter++;
					//
				 	}
		 break;
	 	}
}
/* end UserApp1Initialize() */

  
/*----------------------------------------------------------------------------------------------------------------------
Function UserApp1RunActiveState()

Description:
Selects and runs one iteration of the current state in the state machine.
All state machines have a TOTAL of 1ms to execute, so on average n state machines
may take 1ms / n to execute.

Requires:
  - State machine function pointer points at current state

Promises:
  - Calls the function to pointed by the state machine function pointer
*/
void UserApp1RunActiveState(void)
{
  UserApp1_StateMachine();

} /* end UserApp1RunActiveState */


/*--------------------------------------------------------------------------------------------------------------------*/
/* Private functions                                                                                                  */
/*--------------------------------------------------------------------------------------------------------------------*/


/**********************************************************************************************************************
State Machine Function Definitions
**********************************************************************************************************************/

/*-------------------------------------------------------------------------------------------------------------------*/
/* Wait for ??? */
static void UserApp1SM_Idle(void)
{

} /* end UserApp1SM_Idle() */
    
#if 0
/*-------------------------------------------------------------------------------------------------------------------*/
/* Handle an error */
static void UserApp1SM_Error(void)          
{
  
} /* end UserApp1SM_Error() */
#endif


/*-------------------------------------------------------------------------------------------------------------------*/
/* State to sit in if init failed */
static void UserApp1SM_FailedInit(void)          
{
    
} /* end UserApp1SM_FailedInit() */


/*--------------------------------------------------------------------------------------------------------------------*/
/* End of File                                                                                                        */
/*--------------------------------------------------------------------------------------------------------------------*/
