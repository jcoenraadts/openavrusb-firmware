/*This file is prepared for Doxygen automatic documentation generation.*/
//! \file *********************************************************************
//!
//! \brief This file manages the generic HID IN/OUT task.
//!
//! - Compiler:           IAR EWAVR and GNU GCC for AVR
//! - Supported devices:  AT90USB162, AT90USB82
//!
//! \author               Atmel Corporation: http://www.atmel.com \n
//!                       Support and FAQ: http://support.atmel.no/
//!
//! ***************************************************************************

/* Copyright (c) 2009 Atmel Corporation. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 * this list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 * this list of conditions and the following disclaimer in the documentation
 * and/or other materials provided with the distribution.
 *
 * 3. The name of Atmel may not be used to endorse or promote products derived
 * from this software without specific prior written permission.
 *
 * 4. This software may only be redistributed and used in connection with an Atmel
 * AVR product.
 *
 * THIS SOFTWARE IS PROVIDED BY ATMEL "AS IS" AND ANY EXPRESS OR IMPLIED
 * WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT ARE EXPRESSLY AND
 * SPECIFICALLY DISCLAIMED. IN NO EVENT SHALL ATMEL BE LIABLE FOR ANY DIRECT,
 * INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
 * THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

//_____  I N C L U D E S ___________________________________________________

#include "conf/config.h"
#include "conf/conf_usb.h"
#include "hid_task.h"
#include "lib_mcu/usb/usb_drv.h"
#include "usb_descriptors.h"
#include "modules/usb/device_chap9/usb_standard_request.h"
#include "usb_specific_request.h"
#include "lib_mcu/util/start_boot.h"
#include "sections/sections.h"
#include "sections/init.h"
#include "IN_report.h"

//_____ M A C R O S ________________________________________________________


//_____ D E F I N I T I O N S ______________________________________________


//_____ D E C L A R A T I O N S ____________________________________________

extern U8 jump_bootloader;

void hid_report_out  (void);
void hid_report_in   (void);

//! @brief This function initializes the target board ressources.
//!
void hid_task_init(void)
{
	//TODO put all init stuff here
	DDRC = 0xFE;		//Make sure that PC0 is not set as output!! Clock will fail!!
	init();
}

//! @brief Entry point of the HID generic communication task
//! This function manages IN/OUT repport management.
//!
void hid_task(void)
{
   if(!Is_device_enumerated())          // Check USB HID is enumerated
      return;

   hid_report_out();
   hid_report_in();
}

#define HID_OUT_DATAPACKET_LENGTH (EP_OUT_LENGTH - 5)
char hid_OUT_dataPkt[HID_OUT_DATAPACKET_LENGTH];

//! @brief Get data report from Host
//!
void hid_report_out(void)
{
   Usb_select_endpoint(EP_HID_OUT);
   if(Is_usb_receive_out())
   {
	   //Message Definition
	   //Section
	   //Instruction
	   //Flags
	   //Flags
	   //datalength

	   //Retrieve message parts
	   unsigned char section, instruction, dataLength, flagH, flagL, i;
       section = Usb_read_byte();
       instruction = Usb_read_byte();
       flagL = Usb_read_byte();
       flagH = Usb_read_byte();
       dataLength = Usb_read_byte();

       for(i = 0; i < HID_OUT_DATAPACKET_LENGTH; i++)	//copy datapacket to global buffer
    	   hid_OUT_dataPkt[i] = Usb_read_byte();

       //handle message
       sectionCall(section, instruction, &hid_OUT_dataPkt[0], dataLength);
       //ack message
       Usb_ack_receive_out();
   }

//   //** Check if we received DFU mode command from host
//   if(jump_bootloader)
//   {
//      U32 volatile tempo;
//      Leds_off();
//      Usb_detach();                          // Detach actual generic HID application
//      for(tempo=0;tempo<70000;tempo++);      // Wait some time before
//      start_boot();                          // Jumping to booltoader
//   }
}


//! @brief Send data report to Host
//!
void hid_report_in(void)
{
   Usb_select_endpoint(EP_HID_IN);
   if(!Is_usb_write_enabled())
      return;                                // Not ready to send report

   setINreport();

}

//! @brief  This function increments the cpt_sof counter each times
//! the USB Start Of Frame interrupt subroutine is executed (1ms)
//! Usefull to manage time delays
//!
void sof_action()
{
   //cpt_sof++;
}
