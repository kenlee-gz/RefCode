/*
 * File contains functions for automatic ;
 * detection of tags - without a PC ;
 * connected. ;
 */
#include "automatic.h"
unsigned char	protocol;

/*
 =======================================================================================================================
 =======================================================================================================================
 */

unsigned char FindTags(unsigned char protocol)
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~*/
	unsigned char	command[10];
	/*~~~~~~~~~~~~~~~~~~~~~~~~*/

	while(1)
	{

		if((protocol == 0x00) || (protocol == 0x01))
		{	// ISO15693 //
			command[0] = ChipStateControl;	// turn on RF driver
			command[1] = 0x21;
			command[2] = ISOControl;		// set register 0x01 for ISO15693 operation
			command[3] = 0x02;
			WriteSingle(command, 4);

			delay_ms(5);
			flags = 0x06; // 16 slots
                        //flags = 0x26; //1 slot

			command[0] = 0x00;
			InventoryRequest(command, 0);	// send Inventory request //

			command[0] = ChipStateControl;	// turn off RF driver //
			command[1] = 0x01;
			WriteSingle(command, 2);
			delay_ms(1);

			command[0] = IRQStatus;
                        command[1] = IRQMask;	

                           if (SPIMODE)
                             ReadCont(command, 2);
                          else
                              ReadSingle(command, 1);	

                        // clear any IRQs //
		}

		if((protocol == 0x00) || (protocol == 0x04))
		{	///* Tag-it
			command[0] = ChipStateControl;
			command[1] = 0x21;
			command[2] = ISOControl;		///* set register 0x01 for TI Tag-it operation
			command[3] = 0x13;
			WriteSingle(command, 4);
			delay_ms(5);
			flags = 0x00;
			command[0] = 0x00;
			TIInventoryRequest(command, 0); ///* Send SID poll command as described in

			///* Tag-it standard
			command[0] = ChipStateControl;	///* turn off RF driver
			command[1] = 0x01;
			WriteSingle(command, 2);
			delay_ms(1);

			command[0] = IRQStatus;
                        command[1] = IRQMask;	
			//ReadCont(command, 2);		
                        if (SPIMODE)
                            ReadCont(command, 2);
                        else
                            ReadSingle(command, 1);	
	
		}

	}	/* while */
}		/* FindTags */




