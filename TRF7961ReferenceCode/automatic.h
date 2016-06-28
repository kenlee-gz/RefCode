//-----------------------------------------------------------
//Header file for automatic tag detection

#include <MSP430x23x0.h> 	
#include <stdio.h>
#include "hardware.h"
#include "globals.h"
#include "host.h"
#include "parallel.h"
#include "SPI.h"
#include "anticollision.h"
#include "tiris.h"
//--------------------------------------------------------

unsigned char FindTags(unsigned char protocol);
extern unsigned char protocol;

