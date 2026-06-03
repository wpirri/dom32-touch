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

.build-conf:  ${BUILD_SUBPROJECTS}
ifneq ($(INFORMATION_MESSAGE), )
	@echo $(INFORMATION_MESSAGE)
endif
	${MAKE}  -f nbproject/Makefile-default.mk ${DISTDIR}/Programa-2.${IMAGE_TYPE}.${OUTPUT_SUFFIX}

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
${OBJECTDIR}/src/display/dili9341.o: src/display/dili9341.c  .generated_files/flags/default/a2a46a5d0be5507133213ebee007005a3a8221b6 .generated_files/flags/default/89084a3481147dd80e2344e29edcb351eeeb0ca
	@${MKDIR} "${OBJECTDIR}/src/display" 
	@${RM} ${OBJECTDIR}/src/display/dili9341.o.d 
	@${RM} ${OBJECTDIR}/src/display/dili9341.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -Wall -MP -MMD -MF "${OBJECTDIR}/src/display/dili9341.o.d" -o ${OBJECTDIR}/src/display/dili9341.o src/display/dili9341.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/src/display/display.o: src/display/display.c  .generated_files/flags/default/15a24e1cf9e8455499ce0db65cbc67f915d1f66 .generated_files/flags/default/89084a3481147dd80e2344e29edcb351eeeb0ca
	@${MKDIR} "${OBJECTDIR}/src/display" 
	@${RM} ${OBJECTDIR}/src/display/display.o.d 
	@${RM} ${OBJECTDIR}/src/display/display.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -Wall -MP -MMD -MF "${OBJECTDIR}/src/display/display.o.d" -o ${OBJECTDIR}/src/display/display.o src/display/display.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/src/display/touch.o: src/display/touch.c  .generated_files/flags/default/bc5723c99bf02ac13f9045f12b1efc3d636c83b6 .generated_files/flags/default/89084a3481147dd80e2344e29edcb351eeeb0ca
	@${MKDIR} "${OBJECTDIR}/src/display" 
	@${RM} ${OBJECTDIR}/src/display/touch.o.d 
	@${RM} ${OBJECTDIR}/src/display/touch.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -Wall -MP -MMD -MF "${OBJECTDIR}/src/display/touch.o.d" -o ${OBJECTDIR}/src/display/touch.o src/display/touch.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/src/misc/delay.o: src/misc/delay.c  .generated_files/flags/default/dec0e16a606a9db58c8be4bfcb6245f9a8cca229 .generated_files/flags/default/89084a3481147dd80e2344e29edcb351eeeb0ca
	@${MKDIR} "${OBJECTDIR}/src/misc" 
	@${RM} ${OBJECTDIR}/src/misc/delay.o.d 
	@${RM} ${OBJECTDIR}/src/misc/delay.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -Wall -MP -MMD -MF "${OBJECTDIR}/src/misc/delay.o.d" -o ${OBJECTDIR}/src/misc/delay.o src/misc/delay.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/src/misc/strfunc.o: src/misc/strfunc.c  .generated_files/flags/default/c2a8bb05955d48a91223bcea1c4f3a0f17f78a6 .generated_files/flags/default/89084a3481147dd80e2344e29edcb351eeeb0ca
	@${MKDIR} "${OBJECTDIR}/src/misc" 
	@${RM} ${OBJECTDIR}/src/misc/strfunc.o.d 
	@${RM} ${OBJECTDIR}/src/misc/strfunc.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -Wall -MP -MMD -MF "${OBJECTDIR}/src/misc/strfunc.o.d" -o ${OBJECTDIR}/src/misc/strfunc.o src/misc/strfunc.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/src/misc/beep.o: src/misc/beep.c  .generated_files/flags/default/75ac74d4fed0ae732c0f0ad7885b29ec1242885e .generated_files/flags/default/89084a3481147dd80e2344e29edcb351eeeb0ca
	@${MKDIR} "${OBJECTDIR}/src/misc" 
	@${RM} ${OBJECTDIR}/src/misc/beep.o.d 
	@${RM} ${OBJECTDIR}/src/misc/beep.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -Wall -MP -MMD -MF "${OBJECTDIR}/src/misc/beep.o.d" -o ${OBJECTDIR}/src/misc/beep.o src/misc/beep.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/src/misc/bitmap.o: src/misc/bitmap.c  .generated_files/flags/default/ba497260ef6208f358efda53d3756e0938db98aa .generated_files/flags/default/89084a3481147dd80e2344e29edcb351eeeb0ca
	@${MKDIR} "${OBJECTDIR}/src/misc" 
	@${RM} ${OBJECTDIR}/src/misc/bitmap.o.d 
	@${RM} ${OBJECTDIR}/src/misc/bitmap.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -Wall -MP -MMD -MF "${OBJECTDIR}/src/misc/bitmap.o.d" -o ${OBJECTDIR}/src/misc/bitmap.o src/misc/bitmap.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/src/misc/boton.o: src/misc/boton.c  .generated_files/flags/default/85b0e8935eeafdbcce2c0ea169aabb0a743dad57 .generated_files/flags/default/89084a3481147dd80e2344e29edcb351eeeb0ca
	@${MKDIR} "${OBJECTDIR}/src/misc" 
	@${RM} ${OBJECTDIR}/src/misc/boton.o.d 
	@${RM} ${OBJECTDIR}/src/misc/boton.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -Wall -MP -MMD -MF "${OBJECTDIR}/src/misc/boton.o.d" -o ${OBJECTDIR}/src/misc/boton.o src/misc/boton.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/src/sd/fsio.o: src/sd/fsio.c  .generated_files/flags/default/4d93476a95246ccf4b2e886a995cb1cc3865fed9 .generated_files/flags/default/89084a3481147dd80e2344e29edcb351eeeb0ca
	@${MKDIR} "${OBJECTDIR}/src/sd" 
	@${RM} ${OBJECTDIR}/src/sd/fsio.o.d 
	@${RM} ${OBJECTDIR}/src/sd/fsio.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -Wall -MP -MMD -MF "${OBJECTDIR}/src/sd/fsio.o.d" -o ${OBJECTDIR}/src/sd/fsio.o src/sd/fsio.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/src/sd/sd_spi.o: src/sd/sd_spi.c  .generated_files/flags/default/93671c72f047fc8bdb1cd6ab379aa44bc25ebe6 .generated_files/flags/default/89084a3481147dd80e2344e29edcb351eeeb0ca
	@${MKDIR} "${OBJECTDIR}/src/sd" 
	@${RM} ${OBJECTDIR}/src/sd/sd_spi.o.d 
	@${RM} ${OBJECTDIR}/src/sd/sd_spi.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -Wall -MP -MMD -MF "${OBJECTDIR}/src/sd/sd_spi.o.d" -o ${OBJECTDIR}/src/sd/sd_spi.o src/sd/sd_spi.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/src/wifi/uart3.o: src/wifi/uart3.c  .generated_files/flags/default/9e3c211f74b0e2b62be5e7fe272a0a69b3b3e2fb .generated_files/flags/default/89084a3481147dd80e2344e29edcb351eeeb0ca
	@${MKDIR} "${OBJECTDIR}/src/wifi" 
	@${RM} ${OBJECTDIR}/src/wifi/uart3.o.d 
	@${RM} ${OBJECTDIR}/src/wifi/uart3.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -Wall -MP -MMD -MF "${OBJECTDIR}/src/wifi/uart3.o.d" -o ${OBJECTDIR}/src/wifi/uart3.o src/wifi/uart3.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/src/wifi/wifi.o: src/wifi/wifi.c  .generated_files/flags/default/85e86e54cb8fe78c9dc26f191f6e5a2cd7dd04f .generated_files/flags/default/89084a3481147dd80e2344e29edcb351eeeb0ca
	@${MKDIR} "${OBJECTDIR}/src/wifi" 
	@${RM} ${OBJECTDIR}/src/wifi/wifi.o.d 
	@${RM} ${OBJECTDIR}/src/wifi/wifi.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -Wall -MP -MMD -MF "${OBJECTDIR}/src/wifi/wifi.o.d" -o ${OBJECTDIR}/src/wifi/wifi.o src/wifi/wifi.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/src/main.o: src/main.c  .generated_files/flags/default/dc3f959dd907863f8a488aee0108ffe91f69e3ce .generated_files/flags/default/89084a3481147dd80e2344e29edcb351eeeb0ca
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/main.o.d 
	@${RM} ${OBJECTDIR}/src/main.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -Wall -MP -MMD -MF "${OBJECTDIR}/src/main.o.d" -o ${OBJECTDIR}/src/main.o src/main.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/src/system.o: src/system.c  .generated_files/flags/default/8487d22297e0678b027db4a85026d61fd3284393 .generated_files/flags/default/89084a3481147dd80e2344e29edcb351eeeb0ca
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/system.o.d 
	@${RM} ${OBJECTDIR}/src/system.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -Wall -MP -MMD -MF "${OBJECTDIR}/src/system.o.d" -o ${OBJECTDIR}/src/system.o src/system.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/src/log.o: src/log.c  .generated_files/flags/default/9362f649be3ec95944f3c02bdf60e2ae03a02548 .generated_files/flags/default/89084a3481147dd80e2344e29edcb351eeeb0ca
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/log.o.d 
	@${RM} ${OBJECTDIR}/src/log.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -Wall -MP -MMD -MF "${OBJECTDIR}/src/log.o.d" -o ${OBJECTDIR}/src/log.o src/log.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/src/rtcc.o: src/rtcc.c  .generated_files/flags/default/8fbe7c65729527366fdd94e6a9a52c5dd8ef0cb2 .generated_files/flags/default/89084a3481147dd80e2344e29edcb351eeeb0ca
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/rtcc.o.d 
	@${RM} ${OBJECTDIR}/src/rtcc.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -Wall -MP -MMD -MF "${OBJECTDIR}/src/rtcc.o.d" -o ${OBJECTDIR}/src/rtcc.o src/rtcc.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/src/control.o: src/control.c  .generated_files/flags/default/f60a4ae52c60600afbf652b9f2ad097c2945d706 .generated_files/flags/default/89084a3481147dd80e2344e29edcb351eeeb0ca
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/control.o.d 
	@${RM} ${OBJECTDIR}/src/control.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -Wall -MP -MMD -MF "${OBJECTDIR}/src/control.o.d" -o ${OBJECTDIR}/src/control.o src/control.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/src/config.o: src/config.c  .generated_files/flags/default/c577af684082b5cd501d12fcb175114717dd74fc .generated_files/flags/default/89084a3481147dd80e2344e29edcb351eeeb0ca
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/config.o.d 
	@${RM} ${OBJECTDIR}/src/config.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -Wall -MP -MMD -MF "${OBJECTDIR}/src/config.o.d" -o ${OBJECTDIR}/src/config.o src/config.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/src/http.o: src/http.c  .generated_files/flags/default/c0d625dbe5efce981f33fd929e77ba4e320f53 .generated_files/flags/default/89084a3481147dd80e2344e29edcb351eeeb0ca
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/http.o.d 
	@${RM} ${OBJECTDIR}/src/http.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -Wall -MP -MMD -MF "${OBJECTDIR}/src/http.o.d" -o ${OBJECTDIR}/src/http.o src/http.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
else
${OBJECTDIR}/src/display/dili9341.o: src/display/dili9341.c  .generated_files/flags/default/cee1e345adf6e0b583cc1deb2cea44f804fcb54a .generated_files/flags/default/89084a3481147dd80e2344e29edcb351eeeb0ca
	@${MKDIR} "${OBJECTDIR}/src/display" 
	@${RM} ${OBJECTDIR}/src/display/dili9341.o.d 
	@${RM} ${OBJECTDIR}/src/display/dili9341.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -Wall -MP -MMD -MF "${OBJECTDIR}/src/display/dili9341.o.d" -o ${OBJECTDIR}/src/display/dili9341.o src/display/dili9341.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/src/display/display.o: src/display/display.c  .generated_files/flags/default/352e087c26af3f935206e084b3fc06ea3933d579 .generated_files/flags/default/89084a3481147dd80e2344e29edcb351eeeb0ca
	@${MKDIR} "${OBJECTDIR}/src/display" 
	@${RM} ${OBJECTDIR}/src/display/display.o.d 
	@${RM} ${OBJECTDIR}/src/display/display.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -Wall -MP -MMD -MF "${OBJECTDIR}/src/display/display.o.d" -o ${OBJECTDIR}/src/display/display.o src/display/display.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/src/display/touch.o: src/display/touch.c  .generated_files/flags/default/ac8c82af8d10fe66c44b422728fbf9e8f7da8ddd .generated_files/flags/default/89084a3481147dd80e2344e29edcb351eeeb0ca
	@${MKDIR} "${OBJECTDIR}/src/display" 
	@${RM} ${OBJECTDIR}/src/display/touch.o.d 
	@${RM} ${OBJECTDIR}/src/display/touch.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -Wall -MP -MMD -MF "${OBJECTDIR}/src/display/touch.o.d" -o ${OBJECTDIR}/src/display/touch.o src/display/touch.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/src/misc/delay.o: src/misc/delay.c  .generated_files/flags/default/5f6e96e19b7c4bee926ff8b6d3563cd75758e0cc .generated_files/flags/default/89084a3481147dd80e2344e29edcb351eeeb0ca
	@${MKDIR} "${OBJECTDIR}/src/misc" 
	@${RM} ${OBJECTDIR}/src/misc/delay.o.d 
	@${RM} ${OBJECTDIR}/src/misc/delay.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -Wall -MP -MMD -MF "${OBJECTDIR}/src/misc/delay.o.d" -o ${OBJECTDIR}/src/misc/delay.o src/misc/delay.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/src/misc/strfunc.o: src/misc/strfunc.c  .generated_files/flags/default/42c2149f40b88aa1d533acfe3dbb927cce7ecddc .generated_files/flags/default/89084a3481147dd80e2344e29edcb351eeeb0ca
	@${MKDIR} "${OBJECTDIR}/src/misc" 
	@${RM} ${OBJECTDIR}/src/misc/strfunc.o.d 
	@${RM} ${OBJECTDIR}/src/misc/strfunc.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -Wall -MP -MMD -MF "${OBJECTDIR}/src/misc/strfunc.o.d" -o ${OBJECTDIR}/src/misc/strfunc.o src/misc/strfunc.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/src/misc/beep.o: src/misc/beep.c  .generated_files/flags/default/c4a09d754d07bfc18b80a7f30cce198734b87e94 .generated_files/flags/default/89084a3481147dd80e2344e29edcb351eeeb0ca
	@${MKDIR} "${OBJECTDIR}/src/misc" 
	@${RM} ${OBJECTDIR}/src/misc/beep.o.d 
	@${RM} ${OBJECTDIR}/src/misc/beep.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -Wall -MP -MMD -MF "${OBJECTDIR}/src/misc/beep.o.d" -o ${OBJECTDIR}/src/misc/beep.o src/misc/beep.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/src/misc/bitmap.o: src/misc/bitmap.c  .generated_files/flags/default/a18f91857a2474301f0d38b59d31592ee06acab0 .generated_files/flags/default/89084a3481147dd80e2344e29edcb351eeeb0ca
	@${MKDIR} "${OBJECTDIR}/src/misc" 
	@${RM} ${OBJECTDIR}/src/misc/bitmap.o.d 
	@${RM} ${OBJECTDIR}/src/misc/bitmap.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -Wall -MP -MMD -MF "${OBJECTDIR}/src/misc/bitmap.o.d" -o ${OBJECTDIR}/src/misc/bitmap.o src/misc/bitmap.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/src/misc/boton.o: src/misc/boton.c  .generated_files/flags/default/9efd1dfbe41e29681c112ef297f9f2127f75c856 .generated_files/flags/default/89084a3481147dd80e2344e29edcb351eeeb0ca
	@${MKDIR} "${OBJECTDIR}/src/misc" 
	@${RM} ${OBJECTDIR}/src/misc/boton.o.d 
	@${RM} ${OBJECTDIR}/src/misc/boton.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -Wall -MP -MMD -MF "${OBJECTDIR}/src/misc/boton.o.d" -o ${OBJECTDIR}/src/misc/boton.o src/misc/boton.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/src/sd/fsio.o: src/sd/fsio.c  .generated_files/flags/default/9f36902baf44f526a56bc5a4cb9227e5dd0dad36 .generated_files/flags/default/89084a3481147dd80e2344e29edcb351eeeb0ca
	@${MKDIR} "${OBJECTDIR}/src/sd" 
	@${RM} ${OBJECTDIR}/src/sd/fsio.o.d 
	@${RM} ${OBJECTDIR}/src/sd/fsio.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -Wall -MP -MMD -MF "${OBJECTDIR}/src/sd/fsio.o.d" -o ${OBJECTDIR}/src/sd/fsio.o src/sd/fsio.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/src/sd/sd_spi.o: src/sd/sd_spi.c  .generated_files/flags/default/974b4c87028d143f0a16716f19783d702e3e1e2d .generated_files/flags/default/89084a3481147dd80e2344e29edcb351eeeb0ca
	@${MKDIR} "${OBJECTDIR}/src/sd" 
	@${RM} ${OBJECTDIR}/src/sd/sd_spi.o.d 
	@${RM} ${OBJECTDIR}/src/sd/sd_spi.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -Wall -MP -MMD -MF "${OBJECTDIR}/src/sd/sd_spi.o.d" -o ${OBJECTDIR}/src/sd/sd_spi.o src/sd/sd_spi.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/src/wifi/uart3.o: src/wifi/uart3.c  .generated_files/flags/default/26671fe63e9d3837d9b621d16e482f730dffb661 .generated_files/flags/default/89084a3481147dd80e2344e29edcb351eeeb0ca
	@${MKDIR} "${OBJECTDIR}/src/wifi" 
	@${RM} ${OBJECTDIR}/src/wifi/uart3.o.d 
	@${RM} ${OBJECTDIR}/src/wifi/uart3.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -Wall -MP -MMD -MF "${OBJECTDIR}/src/wifi/uart3.o.d" -o ${OBJECTDIR}/src/wifi/uart3.o src/wifi/uart3.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/src/wifi/wifi.o: src/wifi/wifi.c  .generated_files/flags/default/1905e78cd01fe8d915fcfb496e1f22f2a6cf0b61 .generated_files/flags/default/89084a3481147dd80e2344e29edcb351eeeb0ca
	@${MKDIR} "${OBJECTDIR}/src/wifi" 
	@${RM} ${OBJECTDIR}/src/wifi/wifi.o.d 
	@${RM} ${OBJECTDIR}/src/wifi/wifi.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -Wall -MP -MMD -MF "${OBJECTDIR}/src/wifi/wifi.o.d" -o ${OBJECTDIR}/src/wifi/wifi.o src/wifi/wifi.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/src/main.o: src/main.c  .generated_files/flags/default/cc5b1f55a0ea53bcde77246208e9e040910d7b3a .generated_files/flags/default/89084a3481147dd80e2344e29edcb351eeeb0ca
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/main.o.d 
	@${RM} ${OBJECTDIR}/src/main.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -Wall -MP -MMD -MF "${OBJECTDIR}/src/main.o.d" -o ${OBJECTDIR}/src/main.o src/main.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/src/system.o: src/system.c  .generated_files/flags/default/d9af71f2dfa30c322963df6656b12466357415e7 .generated_files/flags/default/89084a3481147dd80e2344e29edcb351eeeb0ca
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/system.o.d 
	@${RM} ${OBJECTDIR}/src/system.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -Wall -MP -MMD -MF "${OBJECTDIR}/src/system.o.d" -o ${OBJECTDIR}/src/system.o src/system.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/src/log.o: src/log.c  .generated_files/flags/default/dfe7121c9c6b4d3789e57136650d0991c344bea1 .generated_files/flags/default/89084a3481147dd80e2344e29edcb351eeeb0ca
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/log.o.d 
	@${RM} ${OBJECTDIR}/src/log.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -Wall -MP -MMD -MF "${OBJECTDIR}/src/log.o.d" -o ${OBJECTDIR}/src/log.o src/log.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/src/rtcc.o: src/rtcc.c  .generated_files/flags/default/26bffa9fe7633ea0ce7c13eb6b29ab079f824b93 .generated_files/flags/default/89084a3481147dd80e2344e29edcb351eeeb0ca
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/rtcc.o.d 
	@${RM} ${OBJECTDIR}/src/rtcc.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -Wall -MP -MMD -MF "${OBJECTDIR}/src/rtcc.o.d" -o ${OBJECTDIR}/src/rtcc.o src/rtcc.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/src/control.o: src/control.c  .generated_files/flags/default/45b1635746c07463238727d471aae869899bf2a5 .generated_files/flags/default/89084a3481147dd80e2344e29edcb351eeeb0ca
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/control.o.d 
	@${RM} ${OBJECTDIR}/src/control.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -Wall -MP -MMD -MF "${OBJECTDIR}/src/control.o.d" -o ${OBJECTDIR}/src/control.o src/control.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/src/config.o: src/config.c  .generated_files/flags/default/9c65a81e897c919491035c3afd55416e1d47d0e1 .generated_files/flags/default/89084a3481147dd80e2344e29edcb351eeeb0ca
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/config.o.d 
	@${RM} ${OBJECTDIR}/src/config.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -Wall -MP -MMD -MF "${OBJECTDIR}/src/config.o.d" -o ${OBJECTDIR}/src/config.o src/config.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/src/http.o: src/http.c  .generated_files/flags/default/433b73ff32d38bf747a4c417494f07157b1c3de8 .generated_files/flags/default/89084a3481147dd80e2344e29edcb351eeeb0ca
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/http.o.d 
	@${RM} ${OBJECTDIR}/src/http.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -Wall -MP -MMD -MF "${OBJECTDIR}/src/http.o.d" -o ${OBJECTDIR}/src/http.o src/http.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: compileCPP
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: link
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${DISTDIR}/Programa-2.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk    
	@${MKDIR} ${DISTDIR} 
	${MP_CC} $(MP_EXTRA_LD_PRE) -g -mdebugger -D__MPLAB_DEBUGGER_PK3=1 -mprocessor=$(MP_PROCESSOR_OPTION)  -o ${DISTDIR}/Programa-2.${IMAGE_TYPE}.${OUTPUT_SUFFIX} ${OBJECTFILES_QUOTED_IF_SPACED}          -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)   -mreserve=data@0x0:0x1FC -mreserve=boot@0x1FC00490:0x1FC016FF -mreserve=boot@0x1FC00490:0x1FC00BEF  -Wl,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_LD_POST)$(MP_LINKER_FILE_OPTION),--defsym=__MPLAB_DEBUG=1,--defsym=__DEBUG=1,-D=__DEBUG_D,--defsym=__MPLAB_DEBUGGER_PK3=1,--defsym=_min_heap_size=0,--gc-sections,--no-code-in-dinit,--no-dinit-in-serial-mem,-Map="${DISTDIR}/${PROJECTNAME}.${IMAGE_TYPE}.map",--memorysummary,${DISTDIR}/memoryfile.xml -mdfp="${DFP_DIR}"
	
else
${DISTDIR}/Programa-2.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk   
	@${MKDIR} ${DISTDIR} 
	${MP_CC} $(MP_EXTRA_LD_PRE)  -mprocessor=$(MP_PROCESSOR_OPTION)  -o ${DISTDIR}/Programa-2.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX} ${OBJECTFILES_QUOTED_IF_SPACED}          -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -Wl,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_LD_POST)$(MP_LINKER_FILE_OPTION),--defsym=_min_heap_size=0,--gc-sections,--no-code-in-dinit,--no-dinit-in-serial-mem,-Map="${DISTDIR}/${PROJECTNAME}.${IMAGE_TYPE}.map",--memorysummary,${DISTDIR}/memoryfile.xml -mdfp="${DFP_DIR}"
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
