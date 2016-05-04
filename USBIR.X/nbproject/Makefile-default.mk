#
# Generated Makefile - do not edit!
#
# Edit the Makefile in the project folder instead (../Makefile). Each target
# has a -pre and a -post target defined where you can add customized code.
#
# This makefile implements configuration specific macros and targets.


# Include project Makefile
ifeq "${IGNORE_LOCAL}" "TRUE"
# do not include local makefile. User is passing all local related variables already
else
include Makefile
# Include makefile containing local settings
ifeq "$(wildcard nbproject/Makefile-local-default.mk)" "nbproject/Makefile-local-default.mk"
include nbproject/Makefile-local-default.mk
endif
endif

# Environment
MKDIR=mkdir -p
RM=rm -f 
MV=mv 
CP=cp 

# Macros
CND_CONF=default
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
IMAGE_TYPE=debug
OUTPUT_SUFFIX=elf
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/USBIR.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
else
IMAGE_TYPE=production
OUTPUT_SUFFIX=hex
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/USBIR.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
endif

# Object Directory
OBJECTDIR=build/${CND_CONF}/${IMAGE_TYPE}

# Distribution Directory
DISTDIR=dist/${CND_CONF}/${IMAGE_TYPE}

# Source Files Quoted if spaced
SOURCEFILES_QUOTED_IF_SPACED=../../USBIR/firmware/main.c ../../USBIR/firmware/usb_descriptors.c ../../USBIR/firmware/Usb/usb_device.c ../../USBIR/firmware/Usb/usb_host.c "../../USBIR/firmware/Usb/CDC Device Driver/usb_function_cdc.c"

# Object Files Quoted if spaced
OBJECTFILES_QUOTED_IF_SPACED=${OBJECTDIR}/_ext/1268669853/main.p1 ${OBJECTDIR}/_ext/1268669853/usb_descriptors.p1 ${OBJECTDIR}/_ext/1944252914/usb_device.p1 ${OBJECTDIR}/_ext/1944252914/usb_host.p1 ${OBJECTDIR}/_ext/1335884471/usb_function_cdc.p1
POSSIBLE_DEPFILES=${OBJECTDIR}/_ext/1268669853/main.p1.d ${OBJECTDIR}/_ext/1268669853/usb_descriptors.p1.d ${OBJECTDIR}/_ext/1944252914/usb_device.p1.d ${OBJECTDIR}/_ext/1944252914/usb_host.p1.d ${OBJECTDIR}/_ext/1335884471/usb_function_cdc.p1.d

# Object Files
OBJECTFILES=${OBJECTDIR}/_ext/1268669853/main.p1 ${OBJECTDIR}/_ext/1268669853/usb_descriptors.p1 ${OBJECTDIR}/_ext/1944252914/usb_device.p1 ${OBJECTDIR}/_ext/1944252914/usb_host.p1 ${OBJECTDIR}/_ext/1335884471/usb_function_cdc.p1

# Source Files
SOURCEFILES=../../USBIR/firmware/main.c ../../USBIR/firmware/usb_descriptors.c ../../USBIR/firmware/Usb/usb_device.c ../../USBIR/firmware/Usb/usb_host.c ../../USBIR/firmware/Usb/CDC Device Driver/usb_function_cdc.c


CFLAGS=
ASFLAGS=
LDLIBSOPTIONS=

############# Tool locations ##########################################
# If you copy a project from one host to another, the path where the  #
# compiler is installed may be different.                             #
# If you open this project with MPLAB X in the new host, this         #
# makefile will be regenerated and the paths will be corrected.       #
#######################################################################
# fixDeps replaces a bunch of sed/cat/printf statements that slow down the build
FIXDEPS=fixDeps

.build-conf:  ${BUILD_SUBPROJECTS}
ifneq ($(INFORMATION_MESSAGE), )
	@echo $(INFORMATION_MESSAGE)
endif
	${MAKE}  -f nbproject/Makefile-default.mk dist/${CND_CONF}/${IMAGE_TYPE}/USBIR.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}

MP_PROCESSOR_OPTION=18F2550
# ------------------------------------------------------------------------------------
# Rules for buildStep: compile
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${OBJECTDIR}/_ext/1268669853/main.p1: ../../USBIR/firmware/main.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1268669853" 
	@${RM} ${OBJECTDIR}/_ext/1268669853/main.p1.d 
	@${RM} ${OBJECTDIR}/_ext/1268669853/main.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  -D__DEBUG=1 --debugger=pickit2  --double=24 --float=24 --emi=wordwrite --opt=default,+asm,+asmfile,-speed,+space,-debug --addrqual=ignore --mode=free -P -N255 --warn=0 --asmlist --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,+plib --output=-mcof,+elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/_ext/1268669853/main.p1  ../../USBIR/firmware/main.c 
	@-${MV} ${OBJECTDIR}/_ext/1268669853/main.d ${OBJECTDIR}/_ext/1268669853/main.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/_ext/1268669853/main.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/_ext/1268669853/usb_descriptors.p1: ../../USBIR/firmware/usb_descriptors.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1268669853" 
	@${RM} ${OBJECTDIR}/_ext/1268669853/usb_descriptors.p1.d 
	@${RM} ${OBJECTDIR}/_ext/1268669853/usb_descriptors.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  -D__DEBUG=1 --debugger=pickit2  --double=24 --float=24 --emi=wordwrite --opt=default,+asm,+asmfile,-speed,+space,-debug --addrqual=ignore --mode=free -P -N255 --warn=0 --asmlist --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,+plib --output=-mcof,+elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/_ext/1268669853/usb_descriptors.p1  ../../USBIR/firmware/usb_descriptors.c 
	@-${MV} ${OBJECTDIR}/_ext/1268669853/usb_descriptors.d ${OBJECTDIR}/_ext/1268669853/usb_descriptors.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/_ext/1268669853/usb_descriptors.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/_ext/1944252914/usb_device.p1: ../../USBIR/firmware/Usb/usb_device.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1944252914" 
	@${RM} ${OBJECTDIR}/_ext/1944252914/usb_device.p1.d 
	@${RM} ${OBJECTDIR}/_ext/1944252914/usb_device.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  -D__DEBUG=1 --debugger=pickit2  --double=24 --float=24 --emi=wordwrite --opt=default,+asm,+asmfile,-speed,+space,-debug --addrqual=ignore --mode=free -P -N255 --warn=0 --asmlist --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,+plib --output=-mcof,+elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/_ext/1944252914/usb_device.p1  ../../USBIR/firmware/Usb/usb_device.c 
	@-${MV} ${OBJECTDIR}/_ext/1944252914/usb_device.d ${OBJECTDIR}/_ext/1944252914/usb_device.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/_ext/1944252914/usb_device.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/_ext/1944252914/usb_host.p1: ../../USBIR/firmware/Usb/usb_host.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1944252914" 
	@${RM} ${OBJECTDIR}/_ext/1944252914/usb_host.p1.d 
	@${RM} ${OBJECTDIR}/_ext/1944252914/usb_host.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  -D__DEBUG=1 --debugger=pickit2  --double=24 --float=24 --emi=wordwrite --opt=default,+asm,+asmfile,-speed,+space,-debug --addrqual=ignore --mode=free -P -N255 --warn=0 --asmlist --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,+plib --output=-mcof,+elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/_ext/1944252914/usb_host.p1  ../../USBIR/firmware/Usb/usb_host.c 
	@-${MV} ${OBJECTDIR}/_ext/1944252914/usb_host.d ${OBJECTDIR}/_ext/1944252914/usb_host.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/_ext/1944252914/usb_host.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/_ext/1335884471/usb_function_cdc.p1: ../../USBIR/firmware/Usb/CDC\ Device\ Driver/usb_function_cdc.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1335884471" 
	@${RM} ${OBJECTDIR}/_ext/1335884471/usb_function_cdc.p1.d 
	@${RM} ${OBJECTDIR}/_ext/1335884471/usb_function_cdc.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  -D__DEBUG=1 --debugger=pickit2  --double=24 --float=24 --emi=wordwrite --opt=default,+asm,+asmfile,-speed,+space,-debug --addrqual=ignore --mode=free -P -N255 --warn=0 --asmlist --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,+plib --output=-mcof,+elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/_ext/1335884471/usb_function_cdc.p1  "../../USBIR/firmware/Usb/CDC Device Driver/usb_function_cdc.c" 
	@-${MV} ${OBJECTDIR}/_ext/1335884471/usb_function_cdc.d ${OBJECTDIR}/_ext/1335884471/usb_function_cdc.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/_ext/1335884471/usb_function_cdc.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
else
${OBJECTDIR}/_ext/1268669853/main.p1: ../../USBIR/firmware/main.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1268669853" 
	@${RM} ${OBJECTDIR}/_ext/1268669853/main.p1.d 
	@${RM} ${OBJECTDIR}/_ext/1268669853/main.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  --double=24 --float=24 --emi=wordwrite --opt=default,+asm,+asmfile,-speed,+space,-debug --addrqual=ignore --mode=free -P -N255 --warn=0 --asmlist --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,+plib --output=-mcof,+elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/_ext/1268669853/main.p1  ../../USBIR/firmware/main.c 
	@-${MV} ${OBJECTDIR}/_ext/1268669853/main.d ${OBJECTDIR}/_ext/1268669853/main.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/_ext/1268669853/main.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/_ext/1268669853/usb_descriptors.p1: ../../USBIR/firmware/usb_descriptors.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1268669853" 
	@${RM} ${OBJECTDIR}/_ext/1268669853/usb_descriptors.p1.d 
	@${RM} ${OBJECTDIR}/_ext/1268669853/usb_descriptors.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  --double=24 --float=24 --emi=wordwrite --opt=default,+asm,+asmfile,-speed,+space,-debug --addrqual=ignore --mode=free -P -N255 --warn=0 --asmlist --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,+plib --output=-mcof,+elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/_ext/1268669853/usb_descriptors.p1  ../../USBIR/firmware/usb_descriptors.c 
	@-${MV} ${OBJECTDIR}/_ext/1268669853/usb_descriptors.d ${OBJECTDIR}/_ext/1268669853/usb_descriptors.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/_ext/1268669853/usb_descriptors.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/_ext/1944252914/usb_device.p1: ../../USBIR/firmware/Usb/usb_device.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1944252914" 
	@${RM} ${OBJECTDIR}/_ext/1944252914/usb_device.p1.d 
	@${RM} ${OBJECTDIR}/_ext/1944252914/usb_device.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  --double=24 --float=24 --emi=wordwrite --opt=default,+asm,+asmfile,-speed,+space,-debug --addrqual=ignore --mode=free -P -N255 --warn=0 --asmlist --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,+plib --output=-mcof,+elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/_ext/1944252914/usb_device.p1  ../../USBIR/firmware/Usb/usb_device.c 
	@-${MV} ${OBJECTDIR}/_ext/1944252914/usb_device.d ${OBJECTDIR}/_ext/1944252914/usb_device.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/_ext/1944252914/usb_device.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/_ext/1944252914/usb_host.p1: ../../USBIR/firmware/Usb/usb_host.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1944252914" 
	@${RM} ${OBJECTDIR}/_ext/1944252914/usb_host.p1.d 
	@${RM} ${OBJECTDIR}/_ext/1944252914/usb_host.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  --double=24 --float=24 --emi=wordwrite --opt=default,+asm,+asmfile,-speed,+space,-debug --addrqual=ignore --mode=free -P -N255 --warn=0 --asmlist --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,+plib --output=-mcof,+elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/_ext/1944252914/usb_host.p1  ../../USBIR/firmware/Usb/usb_host.c 
	@-${MV} ${OBJECTDIR}/_ext/1944252914/usb_host.d ${OBJECTDIR}/_ext/1944252914/usb_host.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/_ext/1944252914/usb_host.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/_ext/1335884471/usb_function_cdc.p1: ../../USBIR/firmware/Usb/CDC\ Device\ Driver/usb_function_cdc.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1335884471" 
	@${RM} ${OBJECTDIR}/_ext/1335884471/usb_function_cdc.p1.d 
	@${RM} ${OBJECTDIR}/_ext/1335884471/usb_function_cdc.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  --double=24 --float=24 --emi=wordwrite --opt=default,+asm,+asmfile,-speed,+space,-debug --addrqual=ignore --mode=free -P -N255 --warn=0 --asmlist --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,+plib --output=-mcof,+elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/_ext/1335884471/usb_function_cdc.p1  "../../USBIR/firmware/Usb/CDC Device Driver/usb_function_cdc.c" 
	@-${MV} ${OBJECTDIR}/_ext/1335884471/usb_function_cdc.d ${OBJECTDIR}/_ext/1335884471/usb_function_cdc.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/_ext/1335884471/usb_function_cdc.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: assemble
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: link
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
dist/${CND_CONF}/${IMAGE_TYPE}/USBIR.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk    ../../USBIR/firmware/18f2455.lkr
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CC} $(MP_EXTRA_LD_PRE) --chip=$(MP_PROCESSOR_OPTION) -G -mdist/${CND_CONF}/${IMAGE_TYPE}/USBIR.X.${IMAGE_TYPE}.map  -D__DEBUG=1 --debugger=pickit2  --double=24 --float=24 --emi=wordwrite --opt=default,+asm,+asmfile,-speed,+space,-debug --addrqual=ignore --mode=free -P -N255 --warn=0 --asmlist --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,+plib --output=-mcof,+elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"     --rom=default,-7dc0-7fff --ram=default,-3f4-3ff,-fdb-fdf,-fe3-fe7,-feb-fef,-fd4-fd4,-ffd-fff --memorysummary dist/${CND_CONF}/${IMAGE_TYPE}/memoryfile.xml -odist/${CND_CONF}/${IMAGE_TYPE}/USBIR.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX}  ${OBJECTFILES_QUOTED_IF_SPACED}     
	@${RM} dist/${CND_CONF}/${IMAGE_TYPE}/USBIR.X.${IMAGE_TYPE}.hex 
	
else
dist/${CND_CONF}/${IMAGE_TYPE}/USBIR.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk   ../../USBIR/firmware/18f2455.lkr ../../USBIR/firmware/irmanClone.hex
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CC} $(MP_EXTRA_LD_PRE) --chip=$(MP_PROCESSOR_OPTION) -G -mdist/${CND_CONF}/${IMAGE_TYPE}/USBIR.X.${IMAGE_TYPE}.map  --double=24 --float=24 --emi=wordwrite --opt=default,+asm,+asmfile,-speed,+space,-debug --addrqual=ignore --mode=free -P -N255 --warn=0 --asmlist --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,+plib --output=-mcof,+elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    --memorysummary dist/${CND_CONF}/${IMAGE_TYPE}/memoryfile.xml -odist/${CND_CONF}/${IMAGE_TYPE}/USBIR.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX}  ${OBJECTFILES_QUOTED_IF_SPACED}     
	
	@echo "Creating unified hex file"
	@"/opt/microchip/mplabx/v3.05/mplab_ide/mplab_ide/modules/../../bin/hexmate" --edf="/opt/microchip/mplabx/v3.05/mplab_ide/mplab_ide/modules/../../dat/en_msgs.txt" dist/${CND_CONF}/${IMAGE_TYPE}/USBIR.X.${IMAGE_TYPE}.hex ../../USBIR/firmware/irmanClone.hex -odist/${CND_CONF}/production/USBIR.X.production.unified.hex

endif


# Subprojects
.build-subprojects:


# Subprojects
.clean-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r build/default
	${RM} -r dist/default

# Enable dependency checking
.dep.inc: .depcheck-impl

DEPFILES=$(shell "${PATH_TO_IDE_BIN}"mplabwildcard ${POSSIBLE_DEPFILES})
ifneq (${DEPFILES},)
include ${DEPFILES}
endif
