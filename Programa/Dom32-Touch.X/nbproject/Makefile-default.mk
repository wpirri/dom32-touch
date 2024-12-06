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
MKDIR=gnumkdir -p
RM=rm -f 
MV=mv 
CP=cp 

# Macros
CND_CONF=default
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
ConfName=default
ImagePath="dist\default\${IMAGE_TYPE}\dom32-touch.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}"
ImageDir="dist\default\${IMAGE_TYPE}"
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
	${MAKE}  -f nbproject/Makefile-default.mk ${DISTDIR}/dom32-touch.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
	@echo "--------------------------------------"
	@echo "User defined post-build step: [cp dist\default\production\dom32-touch.X.production.hex domtouch.hex]"
	@cp dist\default\production\dom32-touch.X.production.hex domtouch.hex
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
${OBJECTDIR}/_ext/8742029/dili9341.o: ../display/dili9341.c  .generated_files/flags/default/f47b8ab2d860b20c4b367f8521b02915b4e0fbb2 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/8742029" 
	@${RM} ${OBJECTDIR}/_ext/8742029/dili9341.o.d 
	@${RM} ${OBJECTDIR}/_ext/8742029/dili9341.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -fno-common -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/8742029/dili9341.o.d" -o ${OBJECTDIR}/_ext/8742029/dili9341.o ../display/dili9341.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/8742029/touch.o: ../display/touch.c  .generated_files/flags/default/abce060faa2be75f78b56ee5380612af08fdc3d7 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/8742029" 
	@${RM} ${OBJECTDIR}/_ext/8742029/touch.o.d 
	@${RM} ${OBJECTDIR}/_ext/8742029/touch.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -fno-common -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/8742029/touch.o.d" -o ${OBJECTDIR}/_ext/8742029/touch.o ../display/touch.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/8742029/display.o: ../display/display.c  .generated_files/flags/default/8ad5bb71d9961a14b0b340fe03af9a66b5e9e699 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/8742029" 
	@${RM} ${OBJECTDIR}/_ext/8742029/display.o.d 
	@${RM} ${OBJECTDIR}/_ext/8742029/display.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -fno-common -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/8742029/display.o.d" -o ${OBJECTDIR}/_ext/8742029/display.o ../display/display.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/43901184/fsio.o: ../sd/fsio.c  .generated_files/flags/default/f0258b9f52343ce976735923e0e6b0c3475a6fe .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/43901184" 
	@${RM} ${OBJECTDIR}/_ext/43901184/fsio.o.d 
	@${RM} ${OBJECTDIR}/_ext/43901184/fsio.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -fno-common -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/43901184/fsio.o.d" -o ${OBJECTDIR}/_ext/43901184/fsio.o ../sd/fsio.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/43901184/sd_spi.o: ../sd/sd_spi.c  .generated_files/flags/default/48e55fca6e264f9168b04df6b32706b7bf62ceca .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/43901184" 
	@${RM} ${OBJECTDIR}/_ext/43901184/sd_spi.o.d 
	@${RM} ${OBJECTDIR}/_ext/43901184/sd_spi.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -fno-common -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/43901184/sd_spi.o.d" -o ${OBJECTDIR}/_ext/43901184/sd_spi.o ../sd/sd_spi.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1472/main.o: ../main.c  .generated_files/flags/default/4023cdb297d40aa3942ce24351040bcc02e92aaa .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/main.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/main.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -fno-common -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1472/main.o.d" -o ${OBJECTDIR}/_ext/1472/main.o ../main.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1472/log.o: ../log.c  .generated_files/flags/default/94bdf33ea7afabe4f7379755e1fd52cc663a576c .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/log.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/log.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -fno-common -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1472/log.o.d" -o ${OBJECTDIR}/_ext/1472/log.o ../log.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1472/config.o: ../config.c  .generated_files/flags/default/83a38793fb0e9172d7b444da422a7081482451a7 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/config.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/config.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -fno-common -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1472/config.o.d" -o ${OBJECTDIR}/_ext/1472/config.o ../config.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1472/delay.o: ../delay.c  .generated_files/flags/default/8fb98918ae6e28fca130f0a306e39b1f1cc7ddbf .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/delay.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/delay.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -fno-common -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1472/delay.o.d" -o ${OBJECTDIR}/_ext/1472/delay.o ../delay.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1472/boton.o: ../boton.c  .generated_files/flags/default/63e74e5255aa1513e83989ee90829a484e258e5b .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/boton.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/boton.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -fno-common -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1472/boton.o.d" -o ${OBJECTDIR}/_ext/1472/boton.o ../boton.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1472/bitmap.o: ../bitmap.c  .generated_files/flags/default/9ba9c72c5a2ca9b918a166e284f08ebdc489e75d .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/bitmap.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/bitmap.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -fno-common -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1472/bitmap.o.d" -o ${OBJECTDIR}/_ext/1472/bitmap.o ../bitmap.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1472/beep.o: ../beep.c  .generated_files/flags/default/a3cd4e7cc34bdc7a37efcd56d461d1ee16985841 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/beep.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/beep.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -fno-common -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1472/beep.o.d" -o ${OBJECTDIR}/_ext/1472/beep.o ../beep.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1472/wifi.o: ../wifi.c  .generated_files/flags/default/c8b31802b3b362d209135943291c5ebe113a9fa9 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/wifi.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/wifi.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -fno-common -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1472/wifi.o.d" -o ${OBJECTDIR}/_ext/1472/wifi.o ../wifi.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1472/strfunc.o: ../strfunc.c  .generated_files/flags/default/1c8ebe63aee416c8500d9f49ee2bcbf56137e325 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/strfunc.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/strfunc.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -fno-common -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1472/strfunc.o.d" -o ${OBJECTDIR}/_ext/1472/strfunc.o ../strfunc.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1472/http.o: ../http.c  .generated_files/flags/default/272b202e18dba577836858f5b53318010ec98748 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/http.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/http.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -fno-common -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1472/http.o.d" -o ${OBJECTDIR}/_ext/1472/http.o ../http.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1472/control.o: ../control.c  .generated_files/flags/default/ceb60517be75d8bee30645db3ec79c66e6097162 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/control.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/control.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -fno-common -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1472/control.o.d" -o ${OBJECTDIR}/_ext/1472/control.o ../control.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1472/rtcc.o: ../rtcc.c  .generated_files/flags/default/57d3742b356cc357f5028c31b5882e1e2223fe3d .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/rtcc.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/rtcc.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -fno-common -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1472/rtcc.o.d" -o ${OBJECTDIR}/_ext/1472/rtcc.o ../rtcc.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1472/uart3.o: ../uart3.c  .generated_files/flags/default/f78b8f51ea915f75b88be594a1275e0326a3d5f3 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/uart3.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/uart3.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -fno-common -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1472/uart3.o.d" -o ${OBJECTDIR}/_ext/1472/uart3.o ../uart3.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
else
${OBJECTDIR}/_ext/8742029/dili9341.o: ../display/dili9341.c  .generated_files/flags/default/5dc15f3a79b34ea24706bb40b33225930766fa06 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/8742029" 
	@${RM} ${OBJECTDIR}/_ext/8742029/dili9341.o.d 
	@${RM} ${OBJECTDIR}/_ext/8742029/dili9341.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -fno-common -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/8742029/dili9341.o.d" -o ${OBJECTDIR}/_ext/8742029/dili9341.o ../display/dili9341.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/8742029/touch.o: ../display/touch.c  .generated_files/flags/default/74fd21dae4a4e874f44971f5aebcbbe66a59f516 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/8742029" 
	@${RM} ${OBJECTDIR}/_ext/8742029/touch.o.d 
	@${RM} ${OBJECTDIR}/_ext/8742029/touch.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -fno-common -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/8742029/touch.o.d" -o ${OBJECTDIR}/_ext/8742029/touch.o ../display/touch.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/8742029/display.o: ../display/display.c  .generated_files/flags/default/ad426f27cfb9dbe292870675becbdb6fc51c4ae5 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/8742029" 
	@${RM} ${OBJECTDIR}/_ext/8742029/display.o.d 
	@${RM} ${OBJECTDIR}/_ext/8742029/display.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -fno-common -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/8742029/display.o.d" -o ${OBJECTDIR}/_ext/8742029/display.o ../display/display.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/43901184/fsio.o: ../sd/fsio.c  .generated_files/flags/default/69a04e789575871bc0f6192c1fed9669b3c4f70e .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/43901184" 
	@${RM} ${OBJECTDIR}/_ext/43901184/fsio.o.d 
	@${RM} ${OBJECTDIR}/_ext/43901184/fsio.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -fno-common -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/43901184/fsio.o.d" -o ${OBJECTDIR}/_ext/43901184/fsio.o ../sd/fsio.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/43901184/sd_spi.o: ../sd/sd_spi.c  .generated_files/flags/default/e073acab87a350ef258537c15cf115f339ac8a .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/43901184" 
	@${RM} ${OBJECTDIR}/_ext/43901184/sd_spi.o.d 
	@${RM} ${OBJECTDIR}/_ext/43901184/sd_spi.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -fno-common -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/43901184/sd_spi.o.d" -o ${OBJECTDIR}/_ext/43901184/sd_spi.o ../sd/sd_spi.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1472/main.o: ../main.c  .generated_files/flags/default/7688085681bd7d248c05ac77784e081623421b35 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/main.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/main.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -fno-common -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1472/main.o.d" -o ${OBJECTDIR}/_ext/1472/main.o ../main.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1472/log.o: ../log.c  .generated_files/flags/default/2017f6eb49720a09632f13d30f5c89e2fd6d7374 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/log.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/log.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -fno-common -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1472/log.o.d" -o ${OBJECTDIR}/_ext/1472/log.o ../log.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1472/config.o: ../config.c  .generated_files/flags/default/1a6245923a3a0b4c5cb11774f6941f1ea8f57473 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/config.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/config.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -fno-common -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1472/config.o.d" -o ${OBJECTDIR}/_ext/1472/config.o ../config.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1472/delay.o: ../delay.c  .generated_files/flags/default/20d1fe37b9cb7007d90e68f001ef729512a5f630 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/delay.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/delay.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -fno-common -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1472/delay.o.d" -o ${OBJECTDIR}/_ext/1472/delay.o ../delay.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1472/boton.o: ../boton.c  .generated_files/flags/default/c9c976ee23bdb3ea76f45bd0f2cc74a2e953b64c .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/boton.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/boton.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -fno-common -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1472/boton.o.d" -o ${OBJECTDIR}/_ext/1472/boton.o ../boton.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1472/bitmap.o: ../bitmap.c  .generated_files/flags/default/3c021cda87651a7b48961d824ce37db848bdc57c .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/bitmap.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/bitmap.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -fno-common -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1472/bitmap.o.d" -o ${OBJECTDIR}/_ext/1472/bitmap.o ../bitmap.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1472/beep.o: ../beep.c  .generated_files/flags/default/3f5468f8fb4c56ae852e0803922eb9b285d5672d .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/beep.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/beep.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -fno-common -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1472/beep.o.d" -o ${OBJECTDIR}/_ext/1472/beep.o ../beep.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1472/wifi.o: ../wifi.c  .generated_files/flags/default/abffcde5534d4e513e84267afb1026dc4e3c16b7 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/wifi.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/wifi.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -fno-common -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1472/wifi.o.d" -o ${OBJECTDIR}/_ext/1472/wifi.o ../wifi.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1472/strfunc.o: ../strfunc.c  .generated_files/flags/default/bf686c1fe08d9830a90388e92ec12bcc66b5fd93 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/strfunc.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/strfunc.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -fno-common -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1472/strfunc.o.d" -o ${OBJECTDIR}/_ext/1472/strfunc.o ../strfunc.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1472/http.o: ../http.c  .generated_files/flags/default/56ce119013dd034ba38077a1abfd4581ff7e4392 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/http.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/http.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -fno-common -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1472/http.o.d" -o ${OBJECTDIR}/_ext/1472/http.o ../http.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1472/control.o: ../control.c  .generated_files/flags/default/48e946c3e13a26526a6bc47ae7239f57cecb516f .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/control.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/control.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -fno-common -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1472/control.o.d" -o ${OBJECTDIR}/_ext/1472/control.o ../control.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1472/rtcc.o: ../rtcc.c  .generated_files/flags/default/f8b06c0e8d00b665a712ccc9328b886d791b87bd .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/rtcc.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/rtcc.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -fno-common -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1472/rtcc.o.d" -o ${OBJECTDIR}/_ext/1472/rtcc.o ../rtcc.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1472/uart3.o: ../uart3.c  .generated_files/flags/default/1c3ddb30dee43997d2206966bc54d2e234477489 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/uart3.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/uart3.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -fno-common -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1472/uart3.o.d" -o ${OBJECTDIR}/_ext/1472/uart3.o ../uart3.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
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
	${MP_CC} $(MP_EXTRA_LD_PRE) -g -mdebugger -D__MPLAB_DEBUGGER_PK3=1 -mprocessor=$(MP_PROCESSOR_OPTION)  -o ${DISTDIR}/dom32-touch.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX} ${OBJECTFILES_QUOTED_IF_SPACED}          -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)   -mreserve=data@0x0:0x1FC -mreserve=boot@0x1FC00490:0x1FC016FF -mreserve=boot@0x1FC00490:0x1FC00BEF  -Wl,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_LD_POST)$(MP_LINKER_FILE_OPTION),--defsym=__MPLAB_DEBUG=1,--defsym=__DEBUG=1,-D=__DEBUG_D,--defsym=__MPLAB_DEBUGGER_PK3=1,--defsym=_min_heap_size=0,--gc-sections,--no-code-in-dinit,--no-dinit-in-serial-mem,-Map="${DISTDIR}/${PROJECTNAME}.${IMAGE_TYPE}.map",--memorysummary,${DISTDIR}/memoryfile.xml -mdfp="${DFP_DIR}"
	
else
${DISTDIR}/dom32-touch.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk   ../../../pic32mmBoot/Programa/app_p32MM0256GPM028.ld
	@${MKDIR} ${DISTDIR} 
	${MP_CC} $(MP_EXTRA_LD_PRE)  -mprocessor=$(MP_PROCESSOR_OPTION)  -o ${DISTDIR}/dom32-touch.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX} ${OBJECTFILES_QUOTED_IF_SPACED}          -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -Wl,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_LD_POST)$(MP_LINKER_FILE_OPTION),--defsym=_min_heap_size=0,--gc-sections,--no-code-in-dinit,--no-dinit-in-serial-mem,-Map="${DISTDIR}/${PROJECTNAME}.${IMAGE_TYPE}.map",--memorysummary,${DISTDIR}/memoryfile.xml -mdfp="${DFP_DIR}"
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
