#include <stdio.h>
#include "Credit_Check.h"

int int main(void)
{

	/*we have two ways to trigger credit check up
   	1. Time-out (Weekly ??) get the trigger from RTC 
       Check credit and send the response

    */
    if(RTC_Sunday){
        Check_Available_Credit();
    }
    
    /*
   	2. Receive a command to check from server (i.e. ubitot ???)
       Check credit and send the response
    */ 
   char cmd_check_credit[]="CUSD"; // receive command from server

       if(CUSD)
       {
       	Check_Available_Credit();
       }
	return 0;
}