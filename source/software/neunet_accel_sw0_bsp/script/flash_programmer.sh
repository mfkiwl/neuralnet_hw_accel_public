#!/bin/sh
#
# This file was automatically generated.
#
# It can be overwritten by nios2-flash-programmer-generate or nios2-flash-programmer-gui.
#

#
# Converting Binary File: /home/ecegrid/a/695r15/ece695r/proj/neunet_accel/source/software/neunet_accel_sw0_bsp/trained_network.zip to: "../flash/trained_network_generic_tristate_controller_0.flash"
#
bin2flash --input="/home/ecegrid/a/695r15/ece695r/proj/neunet_accel/source/software/neunet_accel_sw0_bsp/trained_network.zip" --output="../flash/trained_network_generic_tristate_controller_0.flash" --location=0x0 

#
# Programming File: "../flash/trained_network_generic_tristate_controller_0.flash" To Device: generic_tristate_controller_0
#
nios2-flash-programmer "../flash/trained_network_generic_tristate_controller_0.flash" --base=0x10000000 --accept-bad-sysid --device=1 --instance=0 '--cable=USB-Blaster on localhost [1-9]' --program 

