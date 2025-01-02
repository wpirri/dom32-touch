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
ifeq "$(wildcard nbproject/Makefile-local-Booteable.mk)" "nbproject/Makefile-local-Booteable.mk"
include nbproject/Makefile-local-Booteable.mk
endif
endif

# Environment
MKDIR=gnumkdir -p
RM=rm -f 
MV=mv 
CP=cp 

# Macros
CND_CONF=Booteable
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

# The following macros may be used in the pre and post step lines
_/_=\\
ShExtension=.bat
Device=PIC32MM0256GPM028
ProjectDir="C:\Users\walte\OneDrive\Documentos\Git\dom32-touch\Programa\dom32-touch.X"
ProjectName=dom32-touch
ConfName=Booteable
ImagePath="dist\Booteable\${IMAGE_TYPE}\dom32-touch.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}"
ImageDir="dist\Booteable\${IMAGE_TYPE}"
ImageName="dom32-touch.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}"
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
IsDebug="true"
else
IsDebug="false"
endif

.build-conf:  ${BUILD_SUBPROJECTS}
ifneq ($(INFORMATION_MESSAGE), )
	@echo $(INFORMATION_MESSAGE)
endif
	${MAKE}  -f nbproject/Makefile-Booteable.mk ${DISTDIR}/dom32-touch.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
	@echo "--------------------------------------"
	@echo "User defined post-build step: [cp dist\Booteable\production\dom32-touch.X.production.hex domtouch.hex]"
	@cp dist\Booteable\production\dom32-touch.X.production.hex domtouch.hex
	@echo "--------------------------------------"

MP_PROCESSOR_OPTION=32MM0256GPM028
MP_LINKER_FILE_OPTION=,--script="..\..\..\pic32mmBoot\Programa\app_p32MM0256GPM028.ld"
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
${OBJECTDIR}/_ext/8742029/dili9341.o: ../display/dili9341.c  .generated_files/flags/Booteable/dc06f10c7677ad1095b2003f4278ddae276e0aee .generated_files/flags/Booteable/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/8742029" 
	@${RM} ${OBJECTDIR}/_ext/8742029/dili9341.o.d 
	@${RM} ${OBJECTDIR}/_ext/8742029/dili9341.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -Os -fno-common -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/8742029/dili9341.o.d" -o ${OBJECTDIR}/_ext/8742029/dili9341.o ../display/dili9341.c    -DXPRJ_Booteable=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/8742029/touch.o: ../display/touch.c  .generated_files/flags/Booteable/e548dc1c0b8d7348ceb2864b6f8fbbb075844469 .generated_files/flags/Booteable/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/8742029" 
	@${RM} ${OBJECTDIR}/_ext/8742029/touch.o.d 
	@${RM} ${OBJECTDIR}/_ext/8742029/touch.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -Os -fno-common -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/8742029/touch.o.d" -o ${OBJECTDIR}/_ext/8742029/touch.o ../display/touch.c    -DXPRJ_Booteable=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/8742029/display.o: ../display/display.c  .generated_files/flags/Booteable/52773cebac1f1d5d700fceccecb87ca5ac8209e2 .generated_files/flags/Booteable/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/8742029" 
	@${RM} ${OBJECTDIR}/_ext/8742029/display.o.d 
	@${RM} ${OBJECTDIR}/_ext/8742029/display.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -Os -fno-common -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/8742029/display.o.d" -o ${OBJECTDIR}/_ext/8742029/display.o ../display/display.c    -DXPRJ_Booteable=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/43901184/fsio.o: ../sd/fsio.c  .generated_files/flags/Booteable/d005d72b50e21e55933aa1bad51108b3b5c74130 .generated_files/flags/Booteable/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/43901184" 
	@${RM} ${OBJECTDIR}/_ext/43901184/fsio.o.d 
	@${RM} ${OBJECTDIR}/_ext/43901184/fsio.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -Os -fno-common -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/43901184/fsio.o.d" -o ${OBJECTDIR}/_ext/43901184/fsio.o ../sd/fsio.c    -DXPRJ_Booteable=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/43901184/sd_spi.o: ../sd/sd_spi.c  .generated_files/flags/Booteable/9b54f4bc0a61620e5860a106f2d7b8955ace1ab1 .generated_files/flags/Booteable/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/43901184" 
	@${RM} ${OBJECTDIR}/_ext/43901184/sd_spi.o.d 
	@${RM} ${OBJECTDIR}/_ext/43901184/sd_spi.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -Os -fno-common -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/43901184/sd_spi.o.d" -o ${OBJECTDIR}/_ext/43901184/sd_spi.o ../sd/sd_spi.c    -DXPRJ_Booteable=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1472/main.o: ../main.c  .generated_files/flags/Booteable/50ae5c5cfe09c722c072c451e95d484ff810c4ed .generated_files/flags/Booteable/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/main.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/main.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -Os -fno-common -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1472/main.o.d" -o ${OBJECTDIR}/_ext/1472/main.o ../main.c    -DXPRJ_Booteable=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1472/log.o: ../log.c  .generated_files/flags/Booteable/116ad1a3dee4fbe5a12ef4ba0fb3b0434fed1b6f .generated_files/flags/Booteable/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/log.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/log.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -Os -fno-common -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1472/log.o.d" -o ${OBJECTDIR}/_ext/1472/log.o ../log.c    -DXPRJ_Booteable=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1472/config.o: ../config.c  .generated_files/flags/Booteable/8c51048f149c62fc834a1f9806ae42a8e680fbd7 .generated_files/flags/Booteable/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/config.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/config.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -Os -fno-common -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1472/config.o.d" -o ${OBJECTDIR}/_ext/1472/config.o ../config.c    -DXPRJ_Booteable=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1472/delay.o: ../delay.c  .generated_files/flags/Booteable/f64130b5f4329efb03d8a160e54eb6d1959175f3 .generated_files/flags/Booteable/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/delay.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/delay.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -Os -fno-common -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1472/delay.o.d" -o ${OBJECTDIR}/_ext/1472/delay.o ../delay.c    -DXPRJ_Booteable=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1472/boton.o: ../boton.c  .generated_files/flags/Booteable/d7467993017f03f7ddee6814151070fd2db31a26 .generated_files/flags/Booteable/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/boton.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/boton.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -Os -fno-common -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1472/boton.o.d" -o ${OBJECTDIR}/_ext/1472/boton.o ../boton.c    -DXPRJ_Booteable=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1472/bitmap.o: ../bitmap.c  .generated_files/flags/Booteable/9ed205f98510e2d6f6de687b2b1992ae8a7a1808 .generated_files/flags/Booteable/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/bitmap.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/bitmap.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -Os -fno-common -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1472/bitmap.o.d" -o ${OBJECTDIR}/_ext/1472/bitmap.o ../bitmap.c    -DXPRJ_Booteable=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1472/beep.o: ../beep.c  .generated_files/flags/Booteable/f992e571b2dbc8f067cab9077352a52a9081655b .generated_files/flags/Booteable/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/beep.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/beep.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -Os -fno-common -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1472/beep.o.d" -o ${OBJECTDIR}/_ext/1472/beep.o ../beep.c    -DXPRJ_Booteable=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1472/wifi.o: ../wifi.c  .generated_files/flags/Booteable/abb2d9c48bc49a5334831660200745856c4b3c11 .generated_files/flags/Booteable/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/wifi.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/wifi.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -Os -fno-common -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1472/wifi.o.d" -o ${OBJECTDIR}/_ext/1472/wifi.o ../wifi.c    -DXPRJ_Booteable=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1472/strfunc.o: ../strfunc.c  .generated_files/flags/Booteable/6f4b5673122c6e991b54f5cd5d2a6963585f5f60 .generated_files/flags/Booteable/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/strfunc.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/strfunc.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -Os -fno-common -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1472/strfunc.o.d" -o ${OBJECTDIR}/_ext/1472/strfunc.o ../strfunc.c    -DXPRJ_Booteable=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1472/http.o: ../http.c  .generated_files/flags/Booteable/33ebe65c4ac58cbc3b8fc484c092c106e03634f8 .generated_files/flags/Booteable/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/http.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/http.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -Os -fno-common -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1472/http.o.d" -o ${OBJECTDIR}/_ext/1472/http.o ../http.c    -DXPRJ_Booteable=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1472/control.o: ../control.c  .generated_files/flags/Booteable/49af38d843bb253b13d2441d5dc61df6aeb4f43c .generated_files/flags/Booteable/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/control.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/control.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -Os -fno-common -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1472/control.o.d" -o ${OBJECTDIR}/_ext/1472/control.o ../control.c    -DXPRJ_Booteable=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1472/rtcc.o: ../rtcc.c  .generated_files/flags/Booteable/640f4a309e954baedd74867d16542d65eefbd38 .generated_files/flags/Booteable/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/rtcc.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/rtcc.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -Os -fno-common -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1472/rtcc.o.d" -o ${OBJECTDIR}/_ext/1472/rtcc.o ../rtcc.c    -DXPRJ_Booteable=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1472/uart3.o: ../uart3.c  .generated_files/flags/Booteable/7838e9d6ac49b521795fd6523569b9a303546e6d .generated_files/flags/Booteable/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/uart3.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/uart3.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -Os -fno-common -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1472/uart3.o.d" -o ${OBJECTDIR}/_ext/1472/uart3.o ../uart3.c    -DXPRJ_Booteable=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
else
${OBJECTDIR}/_ext/8742029/dili9341.o: ../display/dili9341.c  .generated_files/flags/Booteable/4bfe289c51729ec2970d953cdbbe54caedf1e0ee .generated_files/flags/Booteable/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/8742029" 
	@${RM} ${OBJECTDIR}/_ext/8742029/dili9341.o.d 
	@${RM} ${OBJECTDIR}/_ext/8742029/dili9341.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -Os -fno-common -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/8742029/dili9341.o.d" -o ${OBJECTDIR}/_ext/8742029/dili9341.o ../display/dili9341.c    -DXPRJ_Booteable=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/8742029/touch.o: ../display/touch.c  .generated_files/flags/Booteable/c6a0f7180a05be0d63207e056c366a967e1bfd2a .generated_files/flags/Booteable/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/8742029" 
	@${RM} ${OBJECTDIR}/_ext/8742029/touch.o.d 
	@${RM} ${OBJECTDIR}/_ext/8742029/touch.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -Os -fno-common -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/8742029/touch.o.d" -o ${OBJECTDIR}/_ext/8742029/touch.o ../display/touch.c    -DXPRJ_Booteable=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/8742029/display.o: ../display/display.c  .generated_files/flags/Booteable/f2e8ecd673a0707632c12484fba649760c6dd45f .generated_files/flags/Booteable/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/8742029" 
	@${RM} ${OBJECTDIR}/_ext/8742029/display.o.d 
	@${RM} ${OBJECTDIR}/_ext/8742029/display.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -Os -fno-common -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/8742029/display.o.d" -o ${OBJECTDIR}/_ext/8742029/display.o ../display/display.c    -DXPRJ_Booteable=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/43901184/fsio.o: ../sd/fsio.c  .generated_files/flags/Booteable/80662e763eb59b1d930b5ab8dce08aa1b808f21f .generated_files/flags/Booteable/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/43901184" 
	@${RM} ${OBJECTDIR}/_ext/43901184/fsio.o.d 
	@${RM} ${OBJECTDIR}/_ext/43901184/fsio.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -Os -fno-common -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/43901184/fsio.o.d" -o ${OBJECTDIR}/_ext/43901184/fsio.o ../sd/fsio.c    -DXPRJ_Booteable=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/43901184/sd_spi.o: ../sd/sd_spi.c  .generated_files/flags/Booteable/59a8a4058d009bd99461611f271a325637033ae0 .generated_files/flags/Booteable/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/43901184" 
	@${RM} ${OBJECTDIR}/_ext/43901184/sd_spi.o.d 
	@${RM} ${OBJECTDIR}/_ext/43901184/sd_spi.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -Os -fno-common -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/43901184/sd_spi.o.d" -o ${OBJECTDIR}/_ext/43901184/sd_spi.o ../sd/sd_spi.c    -DXPRJ_Booteable=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1472/main.o: ../main.c  .generated_files/flags/Booteable/914f20c191a91fa7606d5aeabcce19af95e166d7 .generated_files/flags/Booteable/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/main.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/main.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -Os -fno-common -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1472/main.o.d" -o ${OBJECTDIR}/_ext/1472/main.o ../main.c    -DXPRJ_Booteable=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1472/log.o: ../log.c  .generated_files/flags/Booteable/5a09f4a65a86731c5cd446c82c5581cc3995fc9b .generated_files/flags/Booteable/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/log.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/log.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -Os -fno-common -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1472/log.o.d" -o ${OBJECTDIR}/_ext/1472/log.o ../log.c    -DXPRJ_Booteable=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1472/config.o: ../config.c  .generated_files/flags/Booteable/5a5744dcaf64f7407d46e619e51d08e25b750e19 .generated_files/flags/Booteable/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/config.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/config.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -Os -fno-common -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1472/config.o.d" -o ${OBJECTDIR}/_ext/1472/config.o ../config.c    -DXPRJ_Booteable=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1472/delay.o: ../delay.c  .generated_files/flags/Booteable/c34006437a67b79ff6717d1a62b7f85098ab3c5 .generated_files/flags/Booteable/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/delay.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/delay.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -Os -fno-common -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1472/delay.o.d" -o ${OBJECTDIR}/_ext/1472/delay.o ../delay.c    -DXPRJ_Booteable=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1472/boton.o: ../boton.c  .generated_files/flags/Booteable/963790b5947085934ea55b7282ba35d59241b02c .generated_files/flags/Booteable/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/boton.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/boton.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -Os -fno-common -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1472/boton.o.d" -o ${OBJECTDIR}/_ext/1472/boton.o ../boton.c    -DXPRJ_Booteable=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1472/bitmap.o: ../bitmap.c  .generated_files/flags/Booteable/4ab8dc4c542644eb5f0d5d76aaf18822799d2a70 .generated_files/flags/Booteable/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/bitmap.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/bitmap.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -Os -fno-common -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1472/bitmap.o.d" -o ${OBJECTDIR}/_ext/1472/bitmap.o ../bitmap.c    -DXPRJ_Booteable=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1472/beep.o: ../beep.c  .generated_files/flags/Booteable/9ea7c1c88b6cf77a35cbd60a0f600429f38f4a99 .generated_files/flags/Booteable/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/beep.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/beep.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -Os -fno-common -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1472/beep.o.d" -o ${OBJECTDIR}/_ext/1472/beep.o ../beep.c    -DXPRJ_Booteable=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1472/wifi.o: ../wifi.c  .generated_files/flags/Booteable/9b54107dd43cd316a2d5943d4e49ea0ab5c50af4 .generated_files/flags/Booteable/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/wifi.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/wifi.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -Os -fno-common -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1472/wifi.o.d" -o ${OBJECTDIR}/_ext/1472/wifi.o ../wifi.c    -DXPRJ_Booteable=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1472/strfunc.o: ../strfunc.c  .generated_files/flags/Booteable/726aaf3f65f3c67589fb9f19abf67225b875c214 .generated_files/flags/Booteable/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/strfunc.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/strfunc.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -Os -fno-common -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1472/strfunc.o.d" -o ${OBJECTDIR}/_ext/1472/strfunc.o ../strfunc.c    -DXPRJ_Booteable=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1472/http.o: ../http.c  .generated_files/flags/Booteable/e766914457d4c0522807d1de01df4501de992668 .generated_files/flags/Booteable/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/http.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/http.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -Os -fno-common -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1472/http.o.d" -o ${OBJECTDIR}/_ext/1472/http.o ../http.c    -DXPRJ_Booteable=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1472/control.o: ../control.c  .generated_files/flags/Booteable/ac3c8d47fdd68dd33f0202dd1e4dc5d5fdc06e7e .generated_files/flags/Booteable/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/control.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/control.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -Os -fno-common -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1472/control.o.d" -o ${OBJECTDIR}/_ext/1472/control.o ../control.c    -DXPRJ_Booteable=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1472/rtcc.o: ../rtcc.c  .generated_files/flags/Booteable/a99bd6417ca29bb705bf7c473de0587194628faf .generated_files/flags/Booteable/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/rtcc.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/rtcc.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -Os -fno-common -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1472/rtcc.o.d" -o ${OBJECTDIR}/_ext/1472/rtcc.o ../rtcc.c    -DXPRJ_Booteable=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1472/uart3.o: ../uart3.c  .generated_files/flags/Booteable/6b2c4f037e7a17ed2c3f39752d6abdaeac61321e .generated_files/flags/Booteable/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/uart3.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/uart3.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -Os -fno-common -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1472/uart3.o.d" -o ${OBJECTDIR}/_ext/1472/uart3.o ../uart3.c    -DXPRJ_Booteable=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: compileCPP
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: link
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${DISTDIR}/dom32-touch.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk    ../../../pic32mmBoot/Programa/app_p32MM0256GPM028.ld
	@${MKDIR} ${DISTDIR} 
	${MP_CC} $(MP_EXTRA_LD_PRE) -g -mdebugger -D__MPLAB_DEBUGGER_PK3=1 -mprocessor=$(MP_PROCESSOR_OPTION)  -Os -o ${DISTDIR}/dom32-touch.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX} ${OBJECTFILES_QUOTED_IF_SPACED}          -DXPRJ_Booteable=$(CND_CONF)    $(COMPARISON_BUILD)   -mreserve=data@0x0:0x1FC -mreserve=boot@0x1FC00490:0x1FC016FF -mreserve=boot@0x1FC00490:0x1FC00BEF  -Wl,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_LD_POST)$(MP_LINKER_FILE_OPTION),--defsym=__MPLAB_DEBUG=1,--defsym=__DEBUG=1,-D=__DEBUG_D,--defsym=__MPLAB_DEBUGGER_PK3=1,--defsym=_min_heap_size=0,--gc-sections,--no-code-in-dinit,--no-dinit-in-serial-mem,-Map="${DISTDIR}/${PROJECTNAME}.${IMAGE_TYPE}.map",-s,--memorysummary,${DISTDIR}/memoryfile.xml -mdfp="${DFP_DIR}"
	
else
${DISTDIR}/dom32-touch.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk   ../../../pic32mmBoot/Programa/app_p32MM0256GPM028.ld
	@${MKDIR} ${DISTDIR} 
	${MP_CC} $(MP_EXTRA_LD_PRE)  -mprocessor=$(MP_PROCESSOR_OPTION)  -Os -o ${DISTDIR}/dom32-touch.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX} ${OBJECTFILES_QUOTED_IF_SPACED}          -DXPRJ_Booteable=$(CND_CONF)    $(COMPARISON_BUILD)  -Wl,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_LD_POST)$(MP_LINKER_FILE_OPTION),--defsym=_min_heap_size=0,--gc-sections,--no-code-in-dinit,--no-dinit-in-serial-mem,-Map="${DISTDIR}/${PROJECTNAME}.${IMAGE_TYPE}.map",-s,--memorysummary,${DISTDIR}/memoryfile.xml -mdfp="${DFP_DIR}"
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
