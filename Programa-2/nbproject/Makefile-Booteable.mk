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
FINAL_IMAGE=${DISTDIR}/Programa-2.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
else
IMAGE_TYPE=production
OUTPUT_SUFFIX=hex
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=${DISTDIR}/Programa-2.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
endif

ifeq ($(COMPARE_BUILD), true)
COMPARISON_BUILD=-mafrlcsj
else
COMPARISON_BUILD=
endif

ifdef SUB_IMAGE_ADDRESS

else
SUB_IMAGE_ADDRESS_COMMAND=
endif

# Object Directory
OBJECTDIR=build/${CND_CONF}/${IMAGE_TYPE}

# Distribution Directory
DISTDIR=dist/${CND_CONF}/${IMAGE_TYPE}

# Source Files Quoted if spaced
SOURCEFILES_QUOTED_IF_SPACED=src/display/dili9341.c src/display/display.c src/display/touch.c src/misc/delay.c src/misc/strfunc.c src/misc/beep.c src/misc/bitmap.c src/misc/boton.c src/sd/fsio.c src/sd/sd_spi.c src/wifi/uart3.c src/wifi/wifi.c src/main.c src/system.c src/log.c src/rtcc.c src/control.c src/config.c src/http.c

# Object Files Quoted if spaced
OBJECTFILES_QUOTED_IF_SPACED=${OBJECTDIR}/src/display/dili9341.o ${OBJECTDIR}/src/display/display.o ${OBJECTDIR}/src/display/touch.o ${OBJECTDIR}/src/misc/delay.o ${OBJECTDIR}/src/misc/strfunc.o ${OBJECTDIR}/src/misc/beep.o ${OBJECTDIR}/src/misc/bitmap.o ${OBJECTDIR}/src/misc/boton.o ${OBJECTDIR}/src/sd/fsio.o ${OBJECTDIR}/src/sd/sd_spi.o ${OBJECTDIR}/src/wifi/uart3.o ${OBJECTDIR}/src/wifi/wifi.o ${OBJECTDIR}/src/main.o ${OBJECTDIR}/src/system.o ${OBJECTDIR}/src/log.o ${OBJECTDIR}/src/rtcc.o ${OBJECTDIR}/src/control.o ${OBJECTDIR}/src/config.o ${OBJECTDIR}/src/http.o
POSSIBLE_DEPFILES=${OBJECTDIR}/src/display/dili9341.o.d ${OBJECTDIR}/src/display/display.o.d ${OBJECTDIR}/src/display/touch.o.d ${OBJECTDIR}/src/misc/delay.o.d ${OBJECTDIR}/src/misc/strfunc.o.d ${OBJECTDIR}/src/misc/beep.o.d ${OBJECTDIR}/src/misc/bitmap.o.d ${OBJECTDIR}/src/misc/boton.o.d ${OBJECTDIR}/src/sd/fsio.o.d ${OBJECTDIR}/src/sd/sd_spi.o.d ${OBJECTDIR}/src/wifi/uart3.o.d ${OBJECTDIR}/src/wifi/wifi.o.d ${OBJECTDIR}/src/main.o.d ${OBJECTDIR}/src/system.o.d ${OBJECTDIR}/src/log.o.d ${OBJECTDIR}/src/rtcc.o.d ${OBJECTDIR}/src/control.o.d ${OBJECTDIR}/src/config.o.d ${OBJECTDIR}/src/http.o.d

# Object Files
OBJECTFILES=${OBJECTDIR}/src/display/dili9341.o ${OBJECTDIR}/src/display/display.o ${OBJECTDIR}/src/display/touch.o ${OBJECTDIR}/src/misc/delay.o ${OBJECTDIR}/src/misc/strfunc.o ${OBJECTDIR}/src/misc/beep.o ${OBJECTDIR}/src/misc/bitmap.o ${OBJECTDIR}/src/misc/boton.o ${OBJECTDIR}/src/sd/fsio.o ${OBJECTDIR}/src/sd/sd_spi.o ${OBJECTDIR}/src/wifi/uart3.o ${OBJECTDIR}/src/wifi/wifi.o ${OBJECTDIR}/src/main.o ${OBJECTDIR}/src/system.o ${OBJECTDIR}/src/log.o ${OBJECTDIR}/src/rtcc.o ${OBJECTDIR}/src/control.o ${OBJECTDIR}/src/config.o ${OBJECTDIR}/src/http.o

# Source Files
SOURCEFILES=src/display/dili9341.c src/display/display.c src/display/touch.c src/misc/delay.c src/misc/strfunc.c src/misc/beep.c src/misc/bitmap.c src/misc/boton.c src/sd/fsio.c src/sd/sd_spi.c src/wifi/uart3.c src/wifi/wifi.c src/main.c src/system.c src/log.c src/rtcc.c src/control.c src/config.c src/http.c



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
ProjectDir="C:\Users\walte\OneDrive\Documentos\Git\dom32-touch\Programa-2"
ProjectName=Dom32P-Touch
ConfName=Booteable
ImagePath="${DISTDIR}\Programa-2.${IMAGE_TYPE}.${OUTPUT_SUFFIX}"
ImageDir="${DISTDIR}"
ImageName="Programa-2.${IMAGE_TYPE}.${OUTPUT_SUFFIX}"
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
IsDebug="true"
else
IsDebug="false"
endif

.build-conf:  ${BUILD_SUBPROJECTS}
ifneq ($(INFORMATION_MESSAGE), )
	@echo $(INFORMATION_MESSAGE)
endif
	${MAKE}  -f nbproject/Makefile-Booteable.mk ${DISTDIR}/Programa-2.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
	@echo "--------------------------------------"
	@echo "User defined post-build step: [cp dist/Booteable/production/Programa-2.production.hex ./domtouch.hex]"
	@cp dist/Booteable/production/Programa-2.production.hex ./domtouch.hex
	@echo "--------------------------------------"

MP_PROCESSOR_OPTION=32MM0256GPM028
MP_LINKER_FILE_OPTION=,--script="..\..\pic32mmBoot\Programa\app_p32MM0256GPM028.ld"
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
${OBJECTDIR}/src/display/dili9341.o: src/display/dili9341.c  .generated_files/flags/Booteable/5aaac21f7442dc7eff6247554d7f684f91f78f22 .generated_files/flags/Booteable/2929bbcf261be56c36d51eeaa474451d34a88bb3
	@${MKDIR} "${OBJECTDIR}/src/display" 
	@${RM} ${OBJECTDIR}/src/display/dili9341.o.d 
	@${RM} ${OBJECTDIR}/src/display/dili9341.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -Os -fno-common -Wall -MP -MMD -MF "${OBJECTDIR}/src/display/dili9341.o.d" -o ${OBJECTDIR}/src/display/dili9341.o src/display/dili9341.c    -DXPRJ_Booteable=$(CND_CONF)    $(COMPARISON_BUILD)    
	
${OBJECTDIR}/src/display/display.o: src/display/display.c  .generated_files/flags/Booteable/b9f726739d1a8ffa3b6c89176a77af14373334f8 .generated_files/flags/Booteable/2929bbcf261be56c36d51eeaa474451d34a88bb3
	@${MKDIR} "${OBJECTDIR}/src/display" 
	@${RM} ${OBJECTDIR}/src/display/display.o.d 
	@${RM} ${OBJECTDIR}/src/display/display.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -Os -fno-common -Wall -MP -MMD -MF "${OBJECTDIR}/src/display/display.o.d" -o ${OBJECTDIR}/src/display/display.o src/display/display.c    -DXPRJ_Booteable=$(CND_CONF)    $(COMPARISON_BUILD)    
	
${OBJECTDIR}/src/display/touch.o: src/display/touch.c  .generated_files/flags/Booteable/7e06775d5fac954a1431bca7d0cbaa7ed16e0a23 .generated_files/flags/Booteable/2929bbcf261be56c36d51eeaa474451d34a88bb3
	@${MKDIR} "${OBJECTDIR}/src/display" 
	@${RM} ${OBJECTDIR}/src/display/touch.o.d 
	@${RM} ${OBJECTDIR}/src/display/touch.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -Os -fno-common -Wall -MP -MMD -MF "${OBJECTDIR}/src/display/touch.o.d" -o ${OBJECTDIR}/src/display/touch.o src/display/touch.c    -DXPRJ_Booteable=$(CND_CONF)    $(COMPARISON_BUILD)    
	
${OBJECTDIR}/src/misc/delay.o: src/misc/delay.c  .generated_files/flags/Booteable/ef8fa5b5c55133ec780ea32a0acd70fc9330819f .generated_files/flags/Booteable/2929bbcf261be56c36d51eeaa474451d34a88bb3
	@${MKDIR} "${OBJECTDIR}/src/misc" 
	@${RM} ${OBJECTDIR}/src/misc/delay.o.d 
	@${RM} ${OBJECTDIR}/src/misc/delay.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -Os -fno-common -Wall -MP -MMD -MF "${OBJECTDIR}/src/misc/delay.o.d" -o ${OBJECTDIR}/src/misc/delay.o src/misc/delay.c    -DXPRJ_Booteable=$(CND_CONF)    $(COMPARISON_BUILD)    
	
${OBJECTDIR}/src/misc/strfunc.o: src/misc/strfunc.c  .generated_files/flags/Booteable/eed8476969a43c5d7495a72b36d13547f1644771 .generated_files/flags/Booteable/2929bbcf261be56c36d51eeaa474451d34a88bb3
	@${MKDIR} "${OBJECTDIR}/src/misc" 
	@${RM} ${OBJECTDIR}/src/misc/strfunc.o.d 
	@${RM} ${OBJECTDIR}/src/misc/strfunc.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -Os -fno-common -Wall -MP -MMD -MF "${OBJECTDIR}/src/misc/strfunc.o.d" -o ${OBJECTDIR}/src/misc/strfunc.o src/misc/strfunc.c    -DXPRJ_Booteable=$(CND_CONF)    $(COMPARISON_BUILD)    
	
${OBJECTDIR}/src/misc/beep.o: src/misc/beep.c  .generated_files/flags/Booteable/70fa98a856e495c9b35832998f5e29032e30338f .generated_files/flags/Booteable/2929bbcf261be56c36d51eeaa474451d34a88bb3
	@${MKDIR} "${OBJECTDIR}/src/misc" 
	@${RM} ${OBJECTDIR}/src/misc/beep.o.d 
	@${RM} ${OBJECTDIR}/src/misc/beep.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -Os -fno-common -Wall -MP -MMD -MF "${OBJECTDIR}/src/misc/beep.o.d" -o ${OBJECTDIR}/src/misc/beep.o src/misc/beep.c    -DXPRJ_Booteable=$(CND_CONF)    $(COMPARISON_BUILD)    
	
${OBJECTDIR}/src/misc/bitmap.o: src/misc/bitmap.c  .generated_files/flags/Booteable/abb3586c40127e004d685cefc420ac6e9d68c6e2 .generated_files/flags/Booteable/2929bbcf261be56c36d51eeaa474451d34a88bb3
	@${MKDIR} "${OBJECTDIR}/src/misc" 
	@${RM} ${OBJECTDIR}/src/misc/bitmap.o.d 
	@${RM} ${OBJECTDIR}/src/misc/bitmap.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -Os -fno-common -Wall -MP -MMD -MF "${OBJECTDIR}/src/misc/bitmap.o.d" -o ${OBJECTDIR}/src/misc/bitmap.o src/misc/bitmap.c    -DXPRJ_Booteable=$(CND_CONF)    $(COMPARISON_BUILD)    
	
${OBJECTDIR}/src/misc/boton.o: src/misc/boton.c  .generated_files/flags/Booteable/1e9fc7296261364b75d27160683412dfc5041c6c .generated_files/flags/Booteable/2929bbcf261be56c36d51eeaa474451d34a88bb3
	@${MKDIR} "${OBJECTDIR}/src/misc" 
	@${RM} ${OBJECTDIR}/src/misc/boton.o.d 
	@${RM} ${OBJECTDIR}/src/misc/boton.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -Os -fno-common -Wall -MP -MMD -MF "${OBJECTDIR}/src/misc/boton.o.d" -o ${OBJECTDIR}/src/misc/boton.o src/misc/boton.c    -DXPRJ_Booteable=$(CND_CONF)    $(COMPARISON_BUILD)    
	
${OBJECTDIR}/src/sd/fsio.o: src/sd/fsio.c  .generated_files/flags/Booteable/e8272dfbef8b53a983d9545fa48e52c1281390ea .generated_files/flags/Booteable/2929bbcf261be56c36d51eeaa474451d34a88bb3
	@${MKDIR} "${OBJECTDIR}/src/sd" 
	@${RM} ${OBJECTDIR}/src/sd/fsio.o.d 
	@${RM} ${OBJECTDIR}/src/sd/fsio.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -Os -fno-common -Wall -MP -MMD -MF "${OBJECTDIR}/src/sd/fsio.o.d" -o ${OBJECTDIR}/src/sd/fsio.o src/sd/fsio.c    -DXPRJ_Booteable=$(CND_CONF)    $(COMPARISON_BUILD)    
	
${OBJECTDIR}/src/sd/sd_spi.o: src/sd/sd_spi.c  .generated_files/flags/Booteable/2e6c3eb670e76ceeec045aaf8673b3d3d60bcc17 .generated_files/flags/Booteable/2929bbcf261be56c36d51eeaa474451d34a88bb3
	@${MKDIR} "${OBJECTDIR}/src/sd" 
	@${RM} ${OBJECTDIR}/src/sd/sd_spi.o.d 
	@${RM} ${OBJECTDIR}/src/sd/sd_spi.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -Os -fno-common -Wall -MP -MMD -MF "${OBJECTDIR}/src/sd/sd_spi.o.d" -o ${OBJECTDIR}/src/sd/sd_spi.o src/sd/sd_spi.c    -DXPRJ_Booteable=$(CND_CONF)    $(COMPARISON_BUILD)    
	
${OBJECTDIR}/src/wifi/uart3.o: src/wifi/uart3.c  .generated_files/flags/Booteable/e587f6853f9522390c117e3ccc2ae9d806967b0f .generated_files/flags/Booteable/2929bbcf261be56c36d51eeaa474451d34a88bb3
	@${MKDIR} "${OBJECTDIR}/src/wifi" 
	@${RM} ${OBJECTDIR}/src/wifi/uart3.o.d 
	@${RM} ${OBJECTDIR}/src/wifi/uart3.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -Os -fno-common -Wall -MP -MMD -MF "${OBJECTDIR}/src/wifi/uart3.o.d" -o ${OBJECTDIR}/src/wifi/uart3.o src/wifi/uart3.c    -DXPRJ_Booteable=$(CND_CONF)    $(COMPARISON_BUILD)    
	
${OBJECTDIR}/src/wifi/wifi.o: src/wifi/wifi.c  .generated_files/flags/Booteable/a46c71dbebae86363b9e2f9f22c7ce7ee4d6ef6e .generated_files/flags/Booteable/2929bbcf261be56c36d51eeaa474451d34a88bb3
	@${MKDIR} "${OBJECTDIR}/src/wifi" 
	@${RM} ${OBJECTDIR}/src/wifi/wifi.o.d 
	@${RM} ${OBJECTDIR}/src/wifi/wifi.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -Os -fno-common -Wall -MP -MMD -MF "${OBJECTDIR}/src/wifi/wifi.o.d" -o ${OBJECTDIR}/src/wifi/wifi.o src/wifi/wifi.c    -DXPRJ_Booteable=$(CND_CONF)    $(COMPARISON_BUILD)    
	
${OBJECTDIR}/src/main.o: src/main.c  .generated_files/flags/Booteable/c2dc3efb187ffde77560c6287ea8716c6af77ee1 .generated_files/flags/Booteable/2929bbcf261be56c36d51eeaa474451d34a88bb3
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/main.o.d 
	@${RM} ${OBJECTDIR}/src/main.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -Os -fno-common -Wall -MP -MMD -MF "${OBJECTDIR}/src/main.o.d" -o ${OBJECTDIR}/src/main.o src/main.c    -DXPRJ_Booteable=$(CND_CONF)    $(COMPARISON_BUILD)    
	
${OBJECTDIR}/src/system.o: src/system.c  .generated_files/flags/Booteable/cb4d552b9c1e334898ffc9620d8fe60d3cf52809 .generated_files/flags/Booteable/2929bbcf261be56c36d51eeaa474451d34a88bb3
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/system.o.d 
	@${RM} ${OBJECTDIR}/src/system.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -Os -fno-common -Wall -MP -MMD -MF "${OBJECTDIR}/src/system.o.d" -o ${OBJECTDIR}/src/system.o src/system.c    -DXPRJ_Booteable=$(CND_CONF)    $(COMPARISON_BUILD)    
	
${OBJECTDIR}/src/log.o: src/log.c  .generated_files/flags/Booteable/873bc636a584bf1dc0fed372f50144b396801e29 .generated_files/flags/Booteable/2929bbcf261be56c36d51eeaa474451d34a88bb3
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/log.o.d 
	@${RM} ${OBJECTDIR}/src/log.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -Os -fno-common -Wall -MP -MMD -MF "${OBJECTDIR}/src/log.o.d" -o ${OBJECTDIR}/src/log.o src/log.c    -DXPRJ_Booteable=$(CND_CONF)    $(COMPARISON_BUILD)    
	
${OBJECTDIR}/src/rtcc.o: src/rtcc.c  .generated_files/flags/Booteable/b827dce563c6896b2ac5047d96806184aa3399e8 .generated_files/flags/Booteable/2929bbcf261be56c36d51eeaa474451d34a88bb3
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/rtcc.o.d 
	@${RM} ${OBJECTDIR}/src/rtcc.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -Os -fno-common -Wall -MP -MMD -MF "${OBJECTDIR}/src/rtcc.o.d" -o ${OBJECTDIR}/src/rtcc.o src/rtcc.c    -DXPRJ_Booteable=$(CND_CONF)    $(COMPARISON_BUILD)    
	
${OBJECTDIR}/src/control.o: src/control.c  .generated_files/flags/Booteable/ed9f62dd26a4f00c666203db867a66e689da557a .generated_files/flags/Booteable/2929bbcf261be56c36d51eeaa474451d34a88bb3
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/control.o.d 
	@${RM} ${OBJECTDIR}/src/control.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -Os -fno-common -Wall -MP -MMD -MF "${OBJECTDIR}/src/control.o.d" -o ${OBJECTDIR}/src/control.o src/control.c    -DXPRJ_Booteable=$(CND_CONF)    $(COMPARISON_BUILD)    
	
${OBJECTDIR}/src/config.o: src/config.c  .generated_files/flags/Booteable/53ea7331baed1bc752b1be40cc34b8882ce2dfad .generated_files/flags/Booteable/2929bbcf261be56c36d51eeaa474451d34a88bb3
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/config.o.d 
	@${RM} ${OBJECTDIR}/src/config.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -Os -fno-common -Wall -MP -MMD -MF "${OBJECTDIR}/src/config.o.d" -o ${OBJECTDIR}/src/config.o src/config.c    -DXPRJ_Booteable=$(CND_CONF)    $(COMPARISON_BUILD)    
	
${OBJECTDIR}/src/http.o: src/http.c  .generated_files/flags/Booteable/8a0d593dc00f8914023d26bdc162610003ed923e .generated_files/flags/Booteable/2929bbcf261be56c36d51eeaa474451d34a88bb3
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/http.o.d 
	@${RM} ${OBJECTDIR}/src/http.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -Os -fno-common -Wall -MP -MMD -MF "${OBJECTDIR}/src/http.o.d" -o ${OBJECTDIR}/src/http.o src/http.c    -DXPRJ_Booteable=$(CND_CONF)    $(COMPARISON_BUILD)    
	
else
${OBJECTDIR}/src/display/dili9341.o: src/display/dili9341.c  .generated_files/flags/Booteable/cdaa4710e7e84d3c79c7256bd42e651941f126df .generated_files/flags/Booteable/2929bbcf261be56c36d51eeaa474451d34a88bb3
	@${MKDIR} "${OBJECTDIR}/src/display" 
	@${RM} ${OBJECTDIR}/src/display/dili9341.o.d 
	@${RM} ${OBJECTDIR}/src/display/dili9341.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -Os -fno-common -Wall -MP -MMD -MF "${OBJECTDIR}/src/display/dili9341.o.d" -o ${OBJECTDIR}/src/display/dili9341.o src/display/dili9341.c    -DXPRJ_Booteable=$(CND_CONF)    $(COMPARISON_BUILD)    
	
${OBJECTDIR}/src/display/display.o: src/display/display.c  .generated_files/flags/Booteable/acc9735199725d7c12944c466ef343e1f27b0abf .generated_files/flags/Booteable/2929bbcf261be56c36d51eeaa474451d34a88bb3
	@${MKDIR} "${OBJECTDIR}/src/display" 
	@${RM} ${OBJECTDIR}/src/display/display.o.d 
	@${RM} ${OBJECTDIR}/src/display/display.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -Os -fno-common -Wall -MP -MMD -MF "${OBJECTDIR}/src/display/display.o.d" -o ${OBJECTDIR}/src/display/display.o src/display/display.c    -DXPRJ_Booteable=$(CND_CONF)    $(COMPARISON_BUILD)    
	
${OBJECTDIR}/src/display/touch.o: src/display/touch.c  .generated_files/flags/Booteable/dba798b2a3178919aabd0275979e17b2930475c3 .generated_files/flags/Booteable/2929bbcf261be56c36d51eeaa474451d34a88bb3
	@${MKDIR} "${OBJECTDIR}/src/display" 
	@${RM} ${OBJECTDIR}/src/display/touch.o.d 
	@${RM} ${OBJECTDIR}/src/display/touch.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -Os -fno-common -Wall -MP -MMD -MF "${OBJECTDIR}/src/display/touch.o.d" -o ${OBJECTDIR}/src/display/touch.o src/display/touch.c    -DXPRJ_Booteable=$(CND_CONF)    $(COMPARISON_BUILD)    
	
${OBJECTDIR}/src/misc/delay.o: src/misc/delay.c  .generated_files/flags/Booteable/9996c7f65801d9116ed9ad5ea161bf1b5088b631 .generated_files/flags/Booteable/2929bbcf261be56c36d51eeaa474451d34a88bb3
	@${MKDIR} "${OBJECTDIR}/src/misc" 
	@${RM} ${OBJECTDIR}/src/misc/delay.o.d 
	@${RM} ${OBJECTDIR}/src/misc/delay.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -Os -fno-common -Wall -MP -MMD -MF "${OBJECTDIR}/src/misc/delay.o.d" -o ${OBJECTDIR}/src/misc/delay.o src/misc/delay.c    -DXPRJ_Booteable=$(CND_CONF)    $(COMPARISON_BUILD)    
	
${OBJECTDIR}/src/misc/strfunc.o: src/misc/strfunc.c  .generated_files/flags/Booteable/8d91555a08cf95edc0ec1e75bfd83f838e9417d0 .generated_files/flags/Booteable/2929bbcf261be56c36d51eeaa474451d34a88bb3
	@${MKDIR} "${OBJECTDIR}/src/misc" 
	@${RM} ${OBJECTDIR}/src/misc/strfunc.o.d 
	@${RM} ${OBJECTDIR}/src/misc/strfunc.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -Os -fno-common -Wall -MP -MMD -MF "${OBJECTDIR}/src/misc/strfunc.o.d" -o ${OBJECTDIR}/src/misc/strfunc.o src/misc/strfunc.c    -DXPRJ_Booteable=$(CND_CONF)    $(COMPARISON_BUILD)    
	
${OBJECTDIR}/src/misc/beep.o: src/misc/beep.c  .generated_files/flags/Booteable/f2cc90d66f24e209f6a488b1ebe3be975e36e1a2 .generated_files/flags/Booteable/2929bbcf261be56c36d51eeaa474451d34a88bb3
	@${MKDIR} "${OBJECTDIR}/src/misc" 
	@${RM} ${OBJECTDIR}/src/misc/beep.o.d 
	@${RM} ${OBJECTDIR}/src/misc/beep.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -Os -fno-common -Wall -MP -MMD -MF "${OBJECTDIR}/src/misc/beep.o.d" -o ${OBJECTDIR}/src/misc/beep.o src/misc/beep.c    -DXPRJ_Booteable=$(CND_CONF)    $(COMPARISON_BUILD)    
	
${OBJECTDIR}/src/misc/bitmap.o: src/misc/bitmap.c  .generated_files/flags/Booteable/e4e0926128a5cbce640176cad9ea811f2b9cc007 .generated_files/flags/Booteable/2929bbcf261be56c36d51eeaa474451d34a88bb3
	@${MKDIR} "${OBJECTDIR}/src/misc" 
	@${RM} ${OBJECTDIR}/src/misc/bitmap.o.d 
	@${RM} ${OBJECTDIR}/src/misc/bitmap.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -Os -fno-common -Wall -MP -MMD -MF "${OBJECTDIR}/src/misc/bitmap.o.d" -o ${OBJECTDIR}/src/misc/bitmap.o src/misc/bitmap.c    -DXPRJ_Booteable=$(CND_CONF)    $(COMPARISON_BUILD)    
	
${OBJECTDIR}/src/misc/boton.o: src/misc/boton.c  .generated_files/flags/Booteable/41161918bde8ed120a411d8f33d6157223127f8 .generated_files/flags/Booteable/2929bbcf261be56c36d51eeaa474451d34a88bb3
	@${MKDIR} "${OBJECTDIR}/src/misc" 
	@${RM} ${OBJECTDIR}/src/misc/boton.o.d 
	@${RM} ${OBJECTDIR}/src/misc/boton.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -Os -fno-common -Wall -MP -MMD -MF "${OBJECTDIR}/src/misc/boton.o.d" -o ${OBJECTDIR}/src/misc/boton.o src/misc/boton.c    -DXPRJ_Booteable=$(CND_CONF)    $(COMPARISON_BUILD)    
	
${OBJECTDIR}/src/sd/fsio.o: src/sd/fsio.c  .generated_files/flags/Booteable/43aeef8865694b3b4b01011943beb952cd21d8ba .generated_files/flags/Booteable/2929bbcf261be56c36d51eeaa474451d34a88bb3
	@${MKDIR} "${OBJECTDIR}/src/sd" 
	@${RM} ${OBJECTDIR}/src/sd/fsio.o.d 
	@${RM} ${OBJECTDIR}/src/sd/fsio.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -Os -fno-common -Wall -MP -MMD -MF "${OBJECTDIR}/src/sd/fsio.o.d" -o ${OBJECTDIR}/src/sd/fsio.o src/sd/fsio.c    -DXPRJ_Booteable=$(CND_CONF)    $(COMPARISON_BUILD)    
	
${OBJECTDIR}/src/sd/sd_spi.o: src/sd/sd_spi.c  .generated_files/flags/Booteable/e6bb27050b99c596b1d4b9e577a27bc3d68ea05e .generated_files/flags/Booteable/2929bbcf261be56c36d51eeaa474451d34a88bb3
	@${MKDIR} "${OBJECTDIR}/src/sd" 
	@${RM} ${OBJECTDIR}/src/sd/sd_spi.o.d 
	@${RM} ${OBJECTDIR}/src/sd/sd_spi.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -Os -fno-common -Wall -MP -MMD -MF "${OBJECTDIR}/src/sd/sd_spi.o.d" -o ${OBJECTDIR}/src/sd/sd_spi.o src/sd/sd_spi.c    -DXPRJ_Booteable=$(CND_CONF)    $(COMPARISON_BUILD)    
	
${OBJECTDIR}/src/wifi/uart3.o: src/wifi/uart3.c  .generated_files/flags/Booteable/a570264558fb9c85495dfd9c364ebdfea344aeb4 .generated_files/flags/Booteable/2929bbcf261be56c36d51eeaa474451d34a88bb3
	@${MKDIR} "${OBJECTDIR}/src/wifi" 
	@${RM} ${OBJECTDIR}/src/wifi/uart3.o.d 
	@${RM} ${OBJECTDIR}/src/wifi/uart3.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -Os -fno-common -Wall -MP -MMD -MF "${OBJECTDIR}/src/wifi/uart3.o.d" -o ${OBJECTDIR}/src/wifi/uart3.o src/wifi/uart3.c    -DXPRJ_Booteable=$(CND_CONF)    $(COMPARISON_BUILD)    
	
${OBJECTDIR}/src/wifi/wifi.o: src/wifi/wifi.c  .generated_files/flags/Booteable/a8f6c95db1294564462da3076cc078aacb8c519a .generated_files/flags/Booteable/2929bbcf261be56c36d51eeaa474451d34a88bb3
	@${MKDIR} "${OBJECTDIR}/src/wifi" 
	@${RM} ${OBJECTDIR}/src/wifi/wifi.o.d 
	@${RM} ${OBJECTDIR}/src/wifi/wifi.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -Os -fno-common -Wall -MP -MMD -MF "${OBJECTDIR}/src/wifi/wifi.o.d" -o ${OBJECTDIR}/src/wifi/wifi.o src/wifi/wifi.c    -DXPRJ_Booteable=$(CND_CONF)    $(COMPARISON_BUILD)    
	
${OBJECTDIR}/src/main.o: src/main.c  .generated_files/flags/Booteable/ee2ab47ec40d15e45f5e04aea0a6f69184b0b124 .generated_files/flags/Booteable/2929bbcf261be56c36d51eeaa474451d34a88bb3
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/main.o.d 
	@${RM} ${OBJECTDIR}/src/main.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -Os -fno-common -Wall -MP -MMD -MF "${OBJECTDIR}/src/main.o.d" -o ${OBJECTDIR}/src/main.o src/main.c    -DXPRJ_Booteable=$(CND_CONF)    $(COMPARISON_BUILD)    
	
${OBJECTDIR}/src/system.o: src/system.c  .generated_files/flags/Booteable/670ca47ec44a788da53abfe228268bda04f6f2d2 .generated_files/flags/Booteable/2929bbcf261be56c36d51eeaa474451d34a88bb3
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/system.o.d 
	@${RM} ${OBJECTDIR}/src/system.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -Os -fno-common -Wall -MP -MMD -MF "${OBJECTDIR}/src/system.o.d" -o ${OBJECTDIR}/src/system.o src/system.c    -DXPRJ_Booteable=$(CND_CONF)    $(COMPARISON_BUILD)    
	
${OBJECTDIR}/src/log.o: src/log.c  .generated_files/flags/Booteable/40e7c7ed47350de95af613fedecd723f634f9815 .generated_files/flags/Booteable/2929bbcf261be56c36d51eeaa474451d34a88bb3
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/log.o.d 
	@${RM} ${OBJECTDIR}/src/log.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -Os -fno-common -Wall -MP -MMD -MF "${OBJECTDIR}/src/log.o.d" -o ${OBJECTDIR}/src/log.o src/log.c    -DXPRJ_Booteable=$(CND_CONF)    $(COMPARISON_BUILD)    
	
${OBJECTDIR}/src/rtcc.o: src/rtcc.c  .generated_files/flags/Booteable/723f25fc480aa1f4118f6f92fa8d25ed31d7423a .generated_files/flags/Booteable/2929bbcf261be56c36d51eeaa474451d34a88bb3
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/rtcc.o.d 
	@${RM} ${OBJECTDIR}/src/rtcc.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -Os -fno-common -Wall -MP -MMD -MF "${OBJECTDIR}/src/rtcc.o.d" -o ${OBJECTDIR}/src/rtcc.o src/rtcc.c    -DXPRJ_Booteable=$(CND_CONF)    $(COMPARISON_BUILD)    
	
${OBJECTDIR}/src/control.o: src/control.c  .generated_files/flags/Booteable/5a734f2745d6584c07536185c52c5fe96cab8437 .generated_files/flags/Booteable/2929bbcf261be56c36d51eeaa474451d34a88bb3
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/control.o.d 
	@${RM} ${OBJECTDIR}/src/control.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -Os -fno-common -Wall -MP -MMD -MF "${OBJECTDIR}/src/control.o.d" -o ${OBJECTDIR}/src/control.o src/control.c    -DXPRJ_Booteable=$(CND_CONF)    $(COMPARISON_BUILD)    
	
${OBJECTDIR}/src/config.o: src/config.c  .generated_files/flags/Booteable/64f65d9b0cc9bc289f75793a437d904fa33f5654 .generated_files/flags/Booteable/2929bbcf261be56c36d51eeaa474451d34a88bb3
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/config.o.d 
	@${RM} ${OBJECTDIR}/src/config.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -Os -fno-common -Wall -MP -MMD -MF "${OBJECTDIR}/src/config.o.d" -o ${OBJECTDIR}/src/config.o src/config.c    -DXPRJ_Booteable=$(CND_CONF)    $(COMPARISON_BUILD)    
	
${OBJECTDIR}/src/http.o: src/http.c  .generated_files/flags/Booteable/ae5dc0b9e59e1e084c51f7d51d55a2ef7f4d3a8 .generated_files/flags/Booteable/2929bbcf261be56c36d51eeaa474451d34a88bb3
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/http.o.d 
	@${RM} ${OBJECTDIR}/src/http.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -Os -fno-common -Wall -MP -MMD -MF "${OBJECTDIR}/src/http.o.d" -o ${OBJECTDIR}/src/http.o src/http.c    -DXPRJ_Booteable=$(CND_CONF)    $(COMPARISON_BUILD)    
	
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: compileCPP
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: link
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${DISTDIR}/Programa-2.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk    ../../pic32mmBoot/Programa/app_p32MM0256GPM028.ld
	@${MKDIR} ${DISTDIR} 
	${MP_CC} $(MP_EXTRA_LD_PRE) -g -mdebugger -D__MPLAB_DEBUGGER_PK3=1 -mprocessor=$(MP_PROCESSOR_OPTION) -Os -o ${DISTDIR}/Programa-2.${IMAGE_TYPE}.${OUTPUT_SUFFIX} ${OBJECTFILES_QUOTED_IF_SPACED}          -DXPRJ_Booteable=$(CND_CONF)    $(COMPARISON_BUILD)   -mreserve=data@0x0:0x1FC -mreserve=boot@0x1FC00490:0x1FC016FF -mreserve=boot@0x1FC00490:0x1FC00BEF  -Wl,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_LD_POST)$(MP_LINKER_FILE_OPTION),--defsym=__MPLAB_DEBUG=1,--defsym=__DEBUG=1,-D=__DEBUG_D,--defsym=__MPLAB_DEBUGGER_PK3=1,--defsym=_min_heap_size=0,--gc-sections,--no-code-in-dinit,--no-dinit-in-serial-mem,-Map="${DISTDIR}/${PROJECTNAME}.${IMAGE_TYPE}.map",-s,--memorysummary,${DISTDIR}/memoryfile.xml 
	
else
${DISTDIR}/Programa-2.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk   ../../pic32mmBoot/Programa/app_p32MM0256GPM028.ld
	@${MKDIR} ${DISTDIR} 
	${MP_CC} $(MP_EXTRA_LD_PRE)  -mprocessor=$(MP_PROCESSOR_OPTION) -Os -o ${DISTDIR}/Programa-2.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX} ${OBJECTFILES_QUOTED_IF_SPACED}          -DXPRJ_Booteable=$(CND_CONF)    $(COMPARISON_BUILD)  -Wl,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_LD_POST)$(MP_LINKER_FILE_OPTION),--defsym=_min_heap_size=0,--gc-sections,--no-code-in-dinit,--no-dinit-in-serial-mem,-Map="${DISTDIR}/${PROJECTNAME}.${IMAGE_TYPE}.map",-s,--memorysummary,${DISTDIR}/memoryfile.xml 
	${MP_CC_DIR}\\xc32-bin2hex ${DISTDIR}/Programa-2.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX} 
	@echo Normalizing hex file
	@"C:/Program Files/Microchip/MPLABX/v6.00/mplab_platform/platform/../mplab_ide/modules/../../bin/hexmate" --edf="C:/Program Files/Microchip/MPLABX/v6.00/mplab_platform/platform/../mplab_ide/modules/../../dat/en_msgs.txt" ${DISTDIR}/Programa-2.${IMAGE_TYPE}.hex -o${DISTDIR}/Programa-2.${IMAGE_TYPE}.hex

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

DEPFILES=$(shell mplabwildcard ${POSSIBLE_DEPFILES})
ifneq (${DEPFILES},)
include ${DEPFILES}
endif
