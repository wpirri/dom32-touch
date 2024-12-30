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
ifeq "$(wildcard nbproject/Makefile-local-StandAlone.mk)" "nbproject/Makefile-local-StandAlone.mk"
include nbproject/Makefile-local-StandAlone.mk
endif
endif

# Environment
MKDIR=gnumkdir -p
RM=rm -f 
MV=mv 
CP=cp 

# Macros
CND_CONF=StandAlone
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
IMAGE_TYPE=debug
OUTPUT_SUFFIX=elf
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=${DISTDIR}/dom32-touch.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
else
IMAGE_TYPE=production
OUTPUT_SUFFIX=hex
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=${DISTDIR}/dom32-touch.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
endif

ifeq ($(COMPARE_BUILD), true)
COMPARISON_BUILD=-mafrlcsj
else
COMPARISON_BUILD=
endif

# Object Directory
OBJECTDIR=build/${CND_CONF}/${IMAGE_TYPE}

# Distribution Directory
DISTDIR=dist/${CND_CONF}/${IMAGE_TYPE}

# Source Files Quoted if spaced
SOURCEFILES_QUOTED_IF_SPACED=../display/dili9341.c ../display/touch.c ../display/display.c ../sd/fsio.c ../sd/sd_spi.c ../main.c ../log.c ../config.c ../delay.c ../boton.c ../bitmap.c ../beep.c ../wifi.c ../strfunc.c ../http.c ../control.c ../rtcc.c ../uart3.c

# Object Files Quoted if spaced
OBJECTFILES_QUOTED_IF_SPACED=${OBJECTDIR}/_ext/8742029/dili9341.o ${OBJECTDIR}/_ext/8742029/touch.o ${OBJECTDIR}/_ext/8742029/display.o ${OBJECTDIR}/_ext/43901184/fsio.o ${OBJECTDIR}/_ext/43901184/sd_spi.o ${OBJECTDIR}/_ext/1472/main.o ${OBJECTDIR}/_ext/1472/log.o ${OBJECTDIR}/_ext/1472/config.o ${OBJECTDIR}/_ext/1472/delay.o ${OBJECTDIR}/_ext/1472/boton.o ${OBJECTDIR}/_ext/1472/bitmap.o ${OBJECTDIR}/_ext/1472/beep.o ${OBJECTDIR}/_ext/1472/wifi.o ${OBJECTDIR}/_ext/1472/strfunc.o ${OBJECTDIR}/_ext/1472/http.o ${OBJECTDIR}/_ext/1472/control.o ${OBJECTDIR}/_ext/1472/rtcc.o ${OBJECTDIR}/_ext/1472/uart3.o
POSSIBLE_DEPFILES=${OBJECTDIR}/_ext/8742029/dili9341.o.d ${OBJECTDIR}/_ext/8742029/touch.o.d ${OBJECTDIR}/_ext/8742029/display.o.d ${OBJECTDIR}/_ext/43901184/fsio.o.d ${OBJECTDIR}/_ext/43901184/sd_spi.o.d ${OBJECTDIR}/_ext/1472/main.o.d ${OBJECTDIR}/_ext/1472/log.o.d ${OBJECTDIR}/_ext/1472/config.o.d ${OBJECTDIR}/_ext/1472/delay.o.d ${OBJECTDIR}/_ext/1472/boton.o.d ${OBJECTDIR}/_ext/1472/bitmap.o.d ${OBJECTDIR}/_ext/1472/beep.o.d ${OBJECTDIR}/_ext/1472/wifi.o.d ${OBJECTDIR}/_ext/1472/strfunc.o.d ${OBJECTDIR}/_ext/1472/http.o.d ${OBJECTDIR}/_ext/1472/control.o.d ${OBJECTDIR}/_ext/1472/rtcc.o.d ${OBJECTDIR}/_ext/1472/uart3.o.d

# Object Files
OBJECTFILES=${OBJECTDIR}/_ext/8742029/dili9341.o ${OBJECTDIR}/_ext/8742029/touch.o ${OBJECTDIR}/_ext/8742029/display.o ${OBJECTDIR}/_ext/43901184/fsio.o ${OBJECTDIR}/_ext/43901184/sd_spi.o ${OBJECTDIR}/_ext/1472/main.o ${OBJECTDIR}/_ext/1472/log.o ${OBJECTDIR}/_ext/1472/config.o ${OBJECTDIR}/_ext/1472/delay.o ${OBJECTDIR}/_ext/1472/boton.o ${OBJECTDIR}/_ext/1472/bitmap.o ${OBJECTDIR}/_ext/1472/beep.o ${OBJECTDIR}/_ext/1472/wifi.o ${OBJECTDIR}/_ext/1472/strfunc.o ${OBJECTDIR}/_ext/1472/http.o ${OBJECTDIR}/_ext/1472/control.o ${OBJECTDIR}/_ext/1472/rtcc.o ${OBJECTDIR}/_ext/1472/uart3.o

# Source Files
SOURCEFILES=../display/dili9341.c ../display/touch.c ../display/display.c ../sd/fsio.c ../sd/sd_spi.c ../main.c ../log.c ../config.c ../delay.c ../boton.c ../bitmap.c ../beep.c ../wifi.c ../strfunc.c ../http.c ../control.c ../rtcc.c ../uart3.c



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
	${MAKE}  -f nbproject/Makefile-StandAlone.mk ${DISTDIR}/dom32-touch.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}

MP_PROCESSOR_OPTION=32MM0256GPM028
MP_LINKER_FILE_OPTION=
# ------------------------------------------------------------------------------------
# Rules for buildStep: assemble
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: assembleWithPreprocess
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: compile
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${OBJECTDIR}/_ext/8742029/dili9341.o: ../display/dili9341.c  .generated_files/flags/StandAlone/a80ea0ee752c2edcaccbffc89d8a734bdc5d7bfa .generated_files/flags/StandAlone/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/8742029" 
	@${RM} ${OBJECTDIR}/_ext/8742029/dili9341.o.d 
	@${RM} ${OBJECTDIR}/_ext/8742029/dili9341.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -fno-common -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/8742029/dili9341.o.d" -o ${OBJECTDIR}/_ext/8742029/dili9341.o ../display/dili9341.c    -DXPRJ_StandAlone=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/8742029/touch.o: ../display/touch.c  .generated_files/flags/StandAlone/1fec2215206b326ead57cc6e29bae26e1cbbca .generated_files/flags/StandAlone/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/8742029" 
	@${RM} ${OBJECTDIR}/_ext/8742029/touch.o.d 
	@${RM} ${OBJECTDIR}/_ext/8742029/touch.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -fno-common -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/8742029/touch.o.d" -o ${OBJECTDIR}/_ext/8742029/touch.o ../display/touch.c    -DXPRJ_StandAlone=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/8742029/display.o: ../display/display.c  .generated_files/flags/StandAlone/8d6f1162711242d1fb3c16ab680eb1db8151bad6 .generated_files/flags/StandAlone/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/8742029" 
	@${RM} ${OBJECTDIR}/_ext/8742029/display.o.d 
	@${RM} ${OBJECTDIR}/_ext/8742029/display.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -fno-common -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/8742029/display.o.d" -o ${OBJECTDIR}/_ext/8742029/display.o ../display/display.c    -DXPRJ_StandAlone=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/43901184/fsio.o: ../sd/fsio.c  .generated_files/flags/StandAlone/1b34570ba8875055286565f33d633cc1d942aa44 .generated_files/flags/StandAlone/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/43901184" 
	@${RM} ${OBJECTDIR}/_ext/43901184/fsio.o.d 
	@${RM} ${OBJECTDIR}/_ext/43901184/fsio.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -fno-common -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/43901184/fsio.o.d" -o ${OBJECTDIR}/_ext/43901184/fsio.o ../sd/fsio.c    -DXPRJ_StandAlone=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/43901184/sd_spi.o: ../sd/sd_spi.c  .generated_files/flags/StandAlone/9cc26b5e3abb2378d2975fd94634453d76589e89 .generated_files/flags/StandAlone/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/43901184" 
	@${RM} ${OBJECTDIR}/_ext/43901184/sd_spi.o.d 
	@${RM} ${OBJECTDIR}/_ext/43901184/sd_spi.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -fno-common -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/43901184/sd_spi.o.d" -o ${OBJECTDIR}/_ext/43901184/sd_spi.o ../sd/sd_spi.c    -DXPRJ_StandAlone=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1472/main.o: ../main.c  .generated_files/flags/StandAlone/8f4623bb20eac371cf0ecdc38a1be3d6cc8f77b4 .generated_files/flags/StandAlone/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/main.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/main.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -fno-common -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1472/main.o.d" -o ${OBJECTDIR}/_ext/1472/main.o ../main.c    -DXPRJ_StandAlone=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1472/log.o: ../log.c  .generated_files/flags/StandAlone/6d878fad0328adc263d41ec647d2270ebb2b689a .generated_files/flags/StandAlone/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/log.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/log.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -fno-common -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1472/log.o.d" -o ${OBJECTDIR}/_ext/1472/log.o ../log.c    -DXPRJ_StandAlone=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1472/config.o: ../config.c  .generated_files/flags/StandAlone/c15810f2ac6a2ff6855b659058f2b5ba1af8ac6a .generated_files/flags/StandAlone/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/config.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/config.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -fno-common -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1472/config.o.d" -o ${OBJECTDIR}/_ext/1472/config.o ../config.c    -DXPRJ_StandAlone=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1472/delay.o: ../delay.c  .generated_files/flags/StandAlone/e35a73de8c078ed79bf1c077146a8314f49732fa .generated_files/flags/StandAlone/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/delay.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/delay.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -fno-common -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1472/delay.o.d" -o ${OBJECTDIR}/_ext/1472/delay.o ../delay.c    -DXPRJ_StandAlone=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1472/boton.o: ../boton.c  .generated_files/flags/StandAlone/821088b6c5525edf714f4f306b33c5ea462201 .generated_files/flags/StandAlone/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/boton.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/boton.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -fno-common -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1472/boton.o.d" -o ${OBJECTDIR}/_ext/1472/boton.o ../boton.c    -DXPRJ_StandAlone=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1472/bitmap.o: ../bitmap.c  .generated_files/flags/StandAlone/53c253eb96ff0e7861838b095fcfc43258f06773 .generated_files/flags/StandAlone/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/bitmap.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/bitmap.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -fno-common -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1472/bitmap.o.d" -o ${OBJECTDIR}/_ext/1472/bitmap.o ../bitmap.c    -DXPRJ_StandAlone=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1472/beep.o: ../beep.c  .generated_files/flags/StandAlone/399671aa2962a7afb9a3a3b95978012a039c3b5a .generated_files/flags/StandAlone/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/beep.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/beep.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -fno-common -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1472/beep.o.d" -o ${OBJECTDIR}/_ext/1472/beep.o ../beep.c    -DXPRJ_StandAlone=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1472/wifi.o: ../wifi.c  .generated_files/flags/StandAlone/a275d01638760bfb6239d7a1a9727efc5c2e4c44 .generated_files/flags/StandAlone/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/wifi.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/wifi.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -fno-common -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1472/wifi.o.d" -o ${OBJECTDIR}/_ext/1472/wifi.o ../wifi.c    -DXPRJ_StandAlone=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1472/strfunc.o: ../strfunc.c  .generated_files/flags/StandAlone/d90772a0b70db7021e06b8843ee85b149600c5cc .generated_files/flags/StandAlone/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/strfunc.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/strfunc.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -fno-common -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1472/strfunc.o.d" -o ${OBJECTDIR}/_ext/1472/strfunc.o ../strfunc.c    -DXPRJ_StandAlone=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1472/http.o: ../http.c  .generated_files/flags/StandAlone/d5d6c896d12976459265861a257e4b98c0855232 .generated_files/flags/StandAlone/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/http.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/http.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -fno-common -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1472/http.o.d" -o ${OBJECTDIR}/_ext/1472/http.o ../http.c    -DXPRJ_StandAlone=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1472/control.o: ../control.c  .generated_files/flags/StandAlone/f80cbea3a24f4e12c929484cc55d517bf5be868e .generated_files/flags/StandAlone/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/control.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/control.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -fno-common -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1472/control.o.d" -o ${OBJECTDIR}/_ext/1472/control.o ../control.c    -DXPRJ_StandAlone=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1472/rtcc.o: ../rtcc.c  .generated_files/flags/StandAlone/d6e76250c56bfb9d20a2037822dc1fb5d5ce0064 .generated_files/flags/StandAlone/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/rtcc.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/rtcc.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -fno-common -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1472/rtcc.o.d" -o ${OBJECTDIR}/_ext/1472/rtcc.o ../rtcc.c    -DXPRJ_StandAlone=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1472/uart3.o: ../uart3.c  .generated_files/flags/StandAlone/4d86245b33a45ec39af3bfef0e466258151e655d .generated_files/flags/StandAlone/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/uart3.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/uart3.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -fno-common -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1472/uart3.o.d" -o ${OBJECTDIR}/_ext/1472/uart3.o ../uart3.c    -DXPRJ_StandAlone=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
else
${OBJECTDIR}/_ext/8742029/dili9341.o: ../display/dili9341.c  .generated_files/flags/StandAlone/f4a704f19ffa5387b4f43b1b3593f61cc6bc8a6f .generated_files/flags/StandAlone/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/8742029" 
	@${RM} ${OBJECTDIR}/_ext/8742029/dili9341.o.d 
	@${RM} ${OBJECTDIR}/_ext/8742029/dili9341.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -fno-common -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/8742029/dili9341.o.d" -o ${OBJECTDIR}/_ext/8742029/dili9341.o ../display/dili9341.c    -DXPRJ_StandAlone=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/8742029/touch.o: ../display/touch.c  .generated_files/flags/StandAlone/2bed62a4a79ddee07726bc8af86be0ae601672b1 .generated_files/flags/StandAlone/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/8742029" 
	@${RM} ${OBJECTDIR}/_ext/8742029/touch.o.d 
	@${RM} ${OBJECTDIR}/_ext/8742029/touch.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -fno-common -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/8742029/touch.o.d" -o ${OBJECTDIR}/_ext/8742029/touch.o ../display/touch.c    -DXPRJ_StandAlone=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/8742029/display.o: ../display/display.c  .generated_files/flags/StandAlone/7ad61a217d751f49f7f3149224d135e584195f23 .generated_files/flags/StandAlone/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/8742029" 
	@${RM} ${OBJECTDIR}/_ext/8742029/display.o.d 
	@${RM} ${OBJECTDIR}/_ext/8742029/display.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -fno-common -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/8742029/display.o.d" -o ${OBJECTDIR}/_ext/8742029/display.o ../display/display.c    -DXPRJ_StandAlone=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/43901184/fsio.o: ../sd/fsio.c  .generated_files/flags/StandAlone/1ac6b20e9a4a972328398c7da08940e3a49751f3 .generated_files/flags/StandAlone/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/43901184" 
	@${RM} ${OBJECTDIR}/_ext/43901184/fsio.o.d 
	@${RM} ${OBJECTDIR}/_ext/43901184/fsio.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -fno-common -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/43901184/fsio.o.d" -o ${OBJECTDIR}/_ext/43901184/fsio.o ../sd/fsio.c    -DXPRJ_StandAlone=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/43901184/sd_spi.o: ../sd/sd_spi.c  .generated_files/flags/StandAlone/4bc3bdde992e9878d46b1e5b1b720ef182d92db6 .generated_files/flags/StandAlone/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/43901184" 
	@${RM} ${OBJECTDIR}/_ext/43901184/sd_spi.o.d 
	@${RM} ${OBJECTDIR}/_ext/43901184/sd_spi.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -fno-common -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/43901184/sd_spi.o.d" -o ${OBJECTDIR}/_ext/43901184/sd_spi.o ../sd/sd_spi.c    -DXPRJ_StandAlone=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1472/main.o: ../main.c  .generated_files/flags/StandAlone/90cf4fb03c9242cb58b97055ce2b85c7042c482 .generated_files/flags/StandAlone/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/main.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/main.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -fno-common -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1472/main.o.d" -o ${OBJECTDIR}/_ext/1472/main.o ../main.c    -DXPRJ_StandAlone=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1472/log.o: ../log.c  .generated_files/flags/StandAlone/5800be44abce11e7db2a18764943e278094642cb .generated_files/flags/StandAlone/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/log.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/log.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -fno-common -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1472/log.o.d" -o ${OBJECTDIR}/_ext/1472/log.o ../log.c    -DXPRJ_StandAlone=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1472/config.o: ../config.c  .generated_files/flags/StandAlone/2f4e05b72bd05505bab3258affd7ae0554fd19d1 .generated_files/flags/StandAlone/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/config.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/config.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -fno-common -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1472/config.o.d" -o ${OBJECTDIR}/_ext/1472/config.o ../config.c    -DXPRJ_StandAlone=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1472/delay.o: ../delay.c  .generated_files/flags/StandAlone/d75e386855547aa8c455256cffc4f63b9b2cd4aa .generated_files/flags/StandAlone/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/delay.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/delay.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -fno-common -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1472/delay.o.d" -o ${OBJECTDIR}/_ext/1472/delay.o ../delay.c    -DXPRJ_StandAlone=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1472/boton.o: ../boton.c  .generated_files/flags/StandAlone/f5658eb042e2bac3d4309762ff97db462ba3911f .generated_files/flags/StandAlone/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/boton.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/boton.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -fno-common -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1472/boton.o.d" -o ${OBJECTDIR}/_ext/1472/boton.o ../boton.c    -DXPRJ_StandAlone=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1472/bitmap.o: ../bitmap.c  .generated_files/flags/StandAlone/c69cc0e65718b3fbdbdccf3a613c99d34eb1121c .generated_files/flags/StandAlone/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/bitmap.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/bitmap.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -fno-common -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1472/bitmap.o.d" -o ${OBJECTDIR}/_ext/1472/bitmap.o ../bitmap.c    -DXPRJ_StandAlone=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1472/beep.o: ../beep.c  .generated_files/flags/StandAlone/47bdb9b32a27132a08f3a8ba369aaa7f58f68da7 .generated_files/flags/StandAlone/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/beep.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/beep.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -fno-common -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1472/beep.o.d" -o ${OBJECTDIR}/_ext/1472/beep.o ../beep.c    -DXPRJ_StandAlone=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1472/wifi.o: ../wifi.c  .generated_files/flags/StandAlone/316eb0ac558edcfea7d711b4f863ece767cd7875 .generated_files/flags/StandAlone/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/wifi.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/wifi.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -fno-common -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1472/wifi.o.d" -o ${OBJECTDIR}/_ext/1472/wifi.o ../wifi.c    -DXPRJ_StandAlone=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1472/strfunc.o: ../strfunc.c  .generated_files/flags/StandAlone/2cfe726322645bf389db478a36084a85c856821d .generated_files/flags/StandAlone/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/strfunc.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/strfunc.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -fno-common -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1472/strfunc.o.d" -o ${OBJECTDIR}/_ext/1472/strfunc.o ../strfunc.c    -DXPRJ_StandAlone=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1472/http.o: ../http.c  .generated_files/flags/StandAlone/722d6c989839a6ccada257c986b80cbc4ef89637 .generated_files/flags/StandAlone/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/http.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/http.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -fno-common -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1472/http.o.d" -o ${OBJECTDIR}/_ext/1472/http.o ../http.c    -DXPRJ_StandAlone=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1472/control.o: ../control.c  .generated_files/flags/StandAlone/8bd781b5eace3c78f4992a873077b3653608d1e5 .generated_files/flags/StandAlone/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/control.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/control.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -fno-common -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1472/control.o.d" -o ${OBJECTDIR}/_ext/1472/control.o ../control.c    -DXPRJ_StandAlone=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1472/rtcc.o: ../rtcc.c  .generated_files/flags/StandAlone/5a62bae15acb8f286820beffbeba9d0fd6893c87 .generated_files/flags/StandAlone/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/rtcc.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/rtcc.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -fno-common -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1472/rtcc.o.d" -o ${OBJECTDIR}/_ext/1472/rtcc.o ../rtcc.c    -DXPRJ_StandAlone=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1472/uart3.o: ../uart3.c  .generated_files/flags/StandAlone/9ce12e617916919ac1259fd58a71e99408aefd5d .generated_files/flags/StandAlone/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/uart3.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/uart3.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -fno-common -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1472/uart3.o.d" -o ${OBJECTDIR}/_ext/1472/uart3.o ../uart3.c    -DXPRJ_StandAlone=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: compileCPP
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: link
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${DISTDIR}/dom32-touch.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk    
	@${MKDIR} ${DISTDIR} 
	${MP_CC} $(MP_EXTRA_LD_PRE) -g -mdebugger -D__MPLAB_DEBUGGER_PK3=1 -mprocessor=$(MP_PROCESSOR_OPTION)  -o ${DISTDIR}/dom32-touch.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX} ${OBJECTFILES_QUOTED_IF_SPACED}          -DXPRJ_StandAlone=$(CND_CONF)    $(COMPARISON_BUILD)   -mreserve=data@0x0:0x1FC -mreserve=boot@0x1FC00490:0x1FC016FF -mreserve=boot@0x1FC00490:0x1FC00BEF  -Wl,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_LD_POST)$(MP_LINKER_FILE_OPTION),--defsym=__MPLAB_DEBUG=1,--defsym=__DEBUG=1,-D=__DEBUG_D,--defsym=__MPLAB_DEBUGGER_PK3=1,--defsym=_min_heap_size=0,--gc-sections,--no-code-in-dinit,--no-dinit-in-serial-mem,-Map="${DISTDIR}/${PROJECTNAME}.${IMAGE_TYPE}.map",--memorysummary,${DISTDIR}/memoryfile.xml -mdfp="${DFP_DIR}"
	
else
${DISTDIR}/dom32-touch.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk   
	@${MKDIR} ${DISTDIR} 
	${MP_CC} $(MP_EXTRA_LD_PRE)  -mprocessor=$(MP_PROCESSOR_OPTION)  -o ${DISTDIR}/dom32-touch.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX} ${OBJECTFILES_QUOTED_IF_SPACED}          -DXPRJ_StandAlone=$(CND_CONF)    $(COMPARISON_BUILD)  -Wl,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_LD_POST)$(MP_LINKER_FILE_OPTION),--defsym=_min_heap_size=0,--gc-sections,--no-code-in-dinit,--no-dinit-in-serial-mem,-Map="${DISTDIR}/${PROJECTNAME}.${IMAGE_TYPE}.map",--memorysummary,${DISTDIR}/memoryfile.xml -mdfp="${DFP_DIR}"
	${MP_CC_DIR}\\xc32-bin2hex ${DISTDIR}/dom32-touch.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX} 
	@echo Normalizing hex file
	@"C:/Program Files/Microchip/MPLABX/v6.20/mplab_platform/platform/../mplab_ide/modules/../../bin/hexmate" --edf="C:/Program Files/Microchip/MPLABX/v6.20/mplab_platform/platform/../mplab_ide/modules/../../dat/en_msgs.txt" ${DISTDIR}/dom32-touch.X.${IMAGE_TYPE}.hex -o${DISTDIR}/dom32-touch.X.${IMAGE_TYPE}.hex

endif


# Subprojects
.build-subprojects:


# Subprojects
.clean-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${OBJECTDIR}
	${RM} -r ${DISTDIR}

# Enable dependency checking
.dep.inc: .depcheck-impl

DEPFILES=$(wildcard ${POSSIBLE_DEPFILES})
ifneq (${DEPFILES},)
include ${DEPFILES}
endif
