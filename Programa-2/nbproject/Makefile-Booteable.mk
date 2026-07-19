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
${OBJECTDIR}/src/display/dili9341.o: src/display/dili9341.c  .generated_files/flags/Booteable/edeb924b1d75c9144b9b81362d851ad3f2e8568f .generated_files/flags/Booteable/89084a3481147dd80e2344e29edcb351eeeb0ca
	@${MKDIR} "${OBJECTDIR}/src/display" 
	@${RM} ${OBJECTDIR}/src/display/dili9341.o.d 
	@${RM} ${OBJECTDIR}/src/display/dili9341.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -Os -fno-common -Wall -MP -MMD -MF "${OBJECTDIR}/src/display/dili9341.o.d" -o ${OBJECTDIR}/src/display/dili9341.o src/display/dili9341.c    -DXPRJ_Booteable=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/src/display/display.o: src/display/display.c  .generated_files/flags/Booteable/444483020651ad79fdc38d4258154922227f6987 .generated_files/flags/Booteable/89084a3481147dd80e2344e29edcb351eeeb0ca
	@${MKDIR} "${OBJECTDIR}/src/display" 
	@${RM} ${OBJECTDIR}/src/display/display.o.d 
	@${RM} ${OBJECTDIR}/src/display/display.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -Os -fno-common -Wall -MP -MMD -MF "${OBJECTDIR}/src/display/display.o.d" -o ${OBJECTDIR}/src/display/display.o src/display/display.c    -DXPRJ_Booteable=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/src/display/touch.o: src/display/touch.c  .generated_files/flags/Booteable/6fec15ee81f7213c06240f42d6fd1bb8a7a45535 .generated_files/flags/Booteable/89084a3481147dd80e2344e29edcb351eeeb0ca
	@${MKDIR} "${OBJECTDIR}/src/display" 
	@${RM} ${OBJECTDIR}/src/display/touch.o.d 
	@${RM} ${OBJECTDIR}/src/display/touch.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -Os -fno-common -Wall -MP -MMD -MF "${OBJECTDIR}/src/display/touch.o.d" -o ${OBJECTDIR}/src/display/touch.o src/display/touch.c    -DXPRJ_Booteable=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/src/misc/delay.o: src/misc/delay.c  .generated_files/flags/Booteable/3e469ac5aeed89d596ea47342fdc93a508fc5596 .generated_files/flags/Booteable/89084a3481147dd80e2344e29edcb351eeeb0ca
	@${MKDIR} "${OBJECTDIR}/src/misc" 
	@${RM} ${OBJECTDIR}/src/misc/delay.o.d 
	@${RM} ${OBJECTDIR}/src/misc/delay.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -Os -fno-common -Wall -MP -MMD -MF "${OBJECTDIR}/src/misc/delay.o.d" -o ${OBJECTDIR}/src/misc/delay.o src/misc/delay.c    -DXPRJ_Booteable=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/src/misc/strfunc.o: src/misc/strfunc.c  .generated_files/flags/Booteable/5bebba9c40f4904cc88ef89ae7783a3e86e971ac .generated_files/flags/Booteable/89084a3481147dd80e2344e29edcb351eeeb0ca
	@${MKDIR} "${OBJECTDIR}/src/misc" 
	@${RM} ${OBJECTDIR}/src/misc/strfunc.o.d 
	@${RM} ${OBJECTDIR}/src/misc/strfunc.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -Os -fno-common -Wall -MP -MMD -MF "${OBJECTDIR}/src/misc/strfunc.o.d" -o ${OBJECTDIR}/src/misc/strfunc.o src/misc/strfunc.c    -DXPRJ_Booteable=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/src/misc/beep.o: src/misc/beep.c  .generated_files/flags/Booteable/ffd8c8cb1a8dde41359fe7ae57e7e0b98306dd64 .generated_files/flags/Booteable/89084a3481147dd80e2344e29edcb351eeeb0ca
	@${MKDIR} "${OBJECTDIR}/src/misc" 
	@${RM} ${OBJECTDIR}/src/misc/beep.o.d 
	@${RM} ${OBJECTDIR}/src/misc/beep.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -Os -fno-common -Wall -MP -MMD -MF "${OBJECTDIR}/src/misc/beep.o.d" -o ${OBJECTDIR}/src/misc/beep.o src/misc/beep.c    -DXPRJ_Booteable=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/src/misc/bitmap.o: src/misc/bitmap.c  .generated_files/flags/Booteable/79741fbc3a1626bdca812673c4809dc21aa232fd .generated_files/flags/Booteable/89084a3481147dd80e2344e29edcb351eeeb0ca
	@${MKDIR} "${OBJECTDIR}/src/misc" 
	@${RM} ${OBJECTDIR}/src/misc/bitmap.o.d 
	@${RM} ${OBJECTDIR}/src/misc/bitmap.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -Os -fno-common -Wall -MP -MMD -MF "${OBJECTDIR}/src/misc/bitmap.o.d" -o ${OBJECTDIR}/src/misc/bitmap.o src/misc/bitmap.c    -DXPRJ_Booteable=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/src/misc/boton.o: src/misc/boton.c  .generated_files/flags/Booteable/b64519a31769fe65a1388dc37ef1f084002c03ea .generated_files/flags/Booteable/89084a3481147dd80e2344e29edcb351eeeb0ca
	@${MKDIR} "${OBJECTDIR}/src/misc" 
	@${RM} ${OBJECTDIR}/src/misc/boton.o.d 
	@${RM} ${OBJECTDIR}/src/misc/boton.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -Os -fno-common -Wall -MP -MMD -MF "${OBJECTDIR}/src/misc/boton.o.d" -o ${OBJECTDIR}/src/misc/boton.o src/misc/boton.c    -DXPRJ_Booteable=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/src/sd/fsio.o: src/sd/fsio.c  .generated_files/flags/Booteable/8752a46f2930217b8ed324644ff901051042d423 .generated_files/flags/Booteable/89084a3481147dd80e2344e29edcb351eeeb0ca
	@${MKDIR} "${OBJECTDIR}/src/sd" 
	@${RM} ${OBJECTDIR}/src/sd/fsio.o.d 
	@${RM} ${OBJECTDIR}/src/sd/fsio.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -Os -fno-common -Wall -MP -MMD -MF "${OBJECTDIR}/src/sd/fsio.o.d" -o ${OBJECTDIR}/src/sd/fsio.o src/sd/fsio.c    -DXPRJ_Booteable=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/src/sd/sd_spi.o: src/sd/sd_spi.c  .generated_files/flags/Booteable/3af691a1bccdd92abdf956775adfee8447b11788 .generated_files/flags/Booteable/89084a3481147dd80e2344e29edcb351eeeb0ca
	@${MKDIR} "${OBJECTDIR}/src/sd" 
	@${RM} ${OBJECTDIR}/src/sd/sd_spi.o.d 
	@${RM} ${OBJECTDIR}/src/sd/sd_spi.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -Os -fno-common -Wall -MP -MMD -MF "${OBJECTDIR}/src/sd/sd_spi.o.d" -o ${OBJECTDIR}/src/sd/sd_spi.o src/sd/sd_spi.c    -DXPRJ_Booteable=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/src/wifi/uart3.o: src/wifi/uart3.c  .generated_files/flags/Booteable/9d17b66cbc2c0a2a55d45633aba03a68ac2e0387 .generated_files/flags/Booteable/89084a3481147dd80e2344e29edcb351eeeb0ca
	@${MKDIR} "${OBJECTDIR}/src/wifi" 
	@${RM} ${OBJECTDIR}/src/wifi/uart3.o.d 
	@${RM} ${OBJECTDIR}/src/wifi/uart3.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -Os -fno-common -Wall -MP -MMD -MF "${OBJECTDIR}/src/wifi/uart3.o.d" -o ${OBJECTDIR}/src/wifi/uart3.o src/wifi/uart3.c    -DXPRJ_Booteable=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/src/wifi/wifi.o: src/wifi/wifi.c  .generated_files/flags/Booteable/eca495c14bc176cb9ff6394359a9e599997574de .generated_files/flags/Booteable/89084a3481147dd80e2344e29edcb351eeeb0ca
	@${MKDIR} "${OBJECTDIR}/src/wifi" 
	@${RM} ${OBJECTDIR}/src/wifi/wifi.o.d 
	@${RM} ${OBJECTDIR}/src/wifi/wifi.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -Os -fno-common -Wall -MP -MMD -MF "${OBJECTDIR}/src/wifi/wifi.o.d" -o ${OBJECTDIR}/src/wifi/wifi.o src/wifi/wifi.c    -DXPRJ_Booteable=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/src/main.o: src/main.c  .generated_files/flags/Booteable/b6f865e9a272346b2232d44ca7c71be3d66ab68a .generated_files/flags/Booteable/89084a3481147dd80e2344e29edcb351eeeb0ca
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/main.o.d 
	@${RM} ${OBJECTDIR}/src/main.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -Os -fno-common -Wall -MP -MMD -MF "${OBJECTDIR}/src/main.o.d" -o ${OBJECTDIR}/src/main.o src/main.c    -DXPRJ_Booteable=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/src/system.o: src/system.c  .generated_files/flags/Booteable/782370ede9678bbe45829b54c58322d50d8082cc .generated_files/flags/Booteable/89084a3481147dd80e2344e29edcb351eeeb0ca
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/system.o.d 
	@${RM} ${OBJECTDIR}/src/system.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -Os -fno-common -Wall -MP -MMD -MF "${OBJECTDIR}/src/system.o.d" -o ${OBJECTDIR}/src/system.o src/system.c    -DXPRJ_Booteable=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/src/log.o: src/log.c  .generated_files/flags/Booteable/d0732f9162a59d6e586029b3b93faa640970b3cc .generated_files/flags/Booteable/89084a3481147dd80e2344e29edcb351eeeb0ca
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/log.o.d 
	@${RM} ${OBJECTDIR}/src/log.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -Os -fno-common -Wall -MP -MMD -MF "${OBJECTDIR}/src/log.o.d" -o ${OBJECTDIR}/src/log.o src/log.c    -DXPRJ_Booteable=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/src/rtcc.o: src/rtcc.c  .generated_files/flags/Booteable/a101ba49513459e8ae9d8063c89845bab2bb2df5 .generated_files/flags/Booteable/89084a3481147dd80e2344e29edcb351eeeb0ca
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/rtcc.o.d 
	@${RM} ${OBJECTDIR}/src/rtcc.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -Os -fno-common -Wall -MP -MMD -MF "${OBJECTDIR}/src/rtcc.o.d" -o ${OBJECTDIR}/src/rtcc.o src/rtcc.c    -DXPRJ_Booteable=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/src/control.o: src/control.c  .generated_files/flags/Booteable/bab7a828f2932f9ddd2cd0ca32d791c988eec4ab .generated_files/flags/Booteable/89084a3481147dd80e2344e29edcb351eeeb0ca
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/control.o.d 
	@${RM} ${OBJECTDIR}/src/control.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -Os -fno-common -Wall -MP -MMD -MF "${OBJECTDIR}/src/control.o.d" -o ${OBJECTDIR}/src/control.o src/control.c    -DXPRJ_Booteable=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/src/config.o: src/config.c  .generated_files/flags/Booteable/551f335deef498fb7ac49aa8833cb22831e46cb7 .generated_files/flags/Booteable/89084a3481147dd80e2344e29edcb351eeeb0ca
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/config.o.d 
	@${RM} ${OBJECTDIR}/src/config.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -Os -fno-common -Wall -MP -MMD -MF "${OBJECTDIR}/src/config.o.d" -o ${OBJECTDIR}/src/config.o src/config.c    -DXPRJ_Booteable=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/src/http.o: src/http.c  .generated_files/flags/Booteable/e7e5807ffe7d1b2f50ff80d26423e6363ab41096 .generated_files/flags/Booteable/89084a3481147dd80e2344e29edcb351eeeb0ca
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/http.o.d 
	@${RM} ${OBJECTDIR}/src/http.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -Os -fno-common -Wall -MP -MMD -MF "${OBJECTDIR}/src/http.o.d" -o ${OBJECTDIR}/src/http.o src/http.c    -DXPRJ_Booteable=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
else
${OBJECTDIR}/src/display/dili9341.o: src/display/dili9341.c  .generated_files/flags/Booteable/edf809abe269f99aefac12b9095837497e3e6ad4 .generated_files/flags/Booteable/89084a3481147dd80e2344e29edcb351eeeb0ca
	@${MKDIR} "${OBJECTDIR}/src/display" 
	@${RM} ${OBJECTDIR}/src/display/dili9341.o.d 
	@${RM} ${OBJECTDIR}/src/display/dili9341.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -Os -fno-common -Wall -MP -MMD -MF "${OBJECTDIR}/src/display/dili9341.o.d" -o ${OBJECTDIR}/src/display/dili9341.o src/display/dili9341.c    -DXPRJ_Booteable=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/src/display/display.o: src/display/display.c  .generated_files/flags/Booteable/b30385808231f51db853fc6575ed48528497c088 .generated_files/flags/Booteable/89084a3481147dd80e2344e29edcb351eeeb0ca
	@${MKDIR} "${OBJECTDIR}/src/display" 
	@${RM} ${OBJECTDIR}/src/display/display.o.d 
	@${RM} ${OBJECTDIR}/src/display/display.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -Os -fno-common -Wall -MP -MMD -MF "${OBJECTDIR}/src/display/display.o.d" -o ${OBJECTDIR}/src/display/display.o src/display/display.c    -DXPRJ_Booteable=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/src/display/touch.o: src/display/touch.c  .generated_files/flags/Booteable/7aaecf045fbbcd6876e193657de4b0ba17f2b620 .generated_files/flags/Booteable/89084a3481147dd80e2344e29edcb351eeeb0ca
	@${MKDIR} "${OBJECTDIR}/src/display" 
	@${RM} ${OBJECTDIR}/src/display/touch.o.d 
	@${RM} ${OBJECTDIR}/src/display/touch.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -Os -fno-common -Wall -MP -MMD -MF "${OBJECTDIR}/src/display/touch.o.d" -o ${OBJECTDIR}/src/display/touch.o src/display/touch.c    -DXPRJ_Booteable=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/src/misc/delay.o: src/misc/delay.c  .generated_files/flags/Booteable/fb13904cdd8d5a88817a9b3edfda6eaee6a6c7b7 .generated_files/flags/Booteable/89084a3481147dd80e2344e29edcb351eeeb0ca
	@${MKDIR} "${OBJECTDIR}/src/misc" 
	@${RM} ${OBJECTDIR}/src/misc/delay.o.d 
	@${RM} ${OBJECTDIR}/src/misc/delay.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -Os -fno-common -Wall -MP -MMD -MF "${OBJECTDIR}/src/misc/delay.o.d" -o ${OBJECTDIR}/src/misc/delay.o src/misc/delay.c    -DXPRJ_Booteable=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/src/misc/strfunc.o: src/misc/strfunc.c  .generated_files/flags/Booteable/c98a948973f1c2f164276c450563755d4078f5a9 .generated_files/flags/Booteable/89084a3481147dd80e2344e29edcb351eeeb0ca
	@${MKDIR} "${OBJECTDIR}/src/misc" 
	@${RM} ${OBJECTDIR}/src/misc/strfunc.o.d 
	@${RM} ${OBJECTDIR}/src/misc/strfunc.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -Os -fno-common -Wall -MP -MMD -MF "${OBJECTDIR}/src/misc/strfunc.o.d" -o ${OBJECTDIR}/src/misc/strfunc.o src/misc/strfunc.c    -DXPRJ_Booteable=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/src/misc/beep.o: src/misc/beep.c  .generated_files/flags/Booteable/393b6a01b0b2a875187c8896ab7c9876657f1cc5 .generated_files/flags/Booteable/89084a3481147dd80e2344e29edcb351eeeb0ca
	@${MKDIR} "${OBJECTDIR}/src/misc" 
	@${RM} ${OBJECTDIR}/src/misc/beep.o.d 
	@${RM} ${OBJECTDIR}/src/misc/beep.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -Os -fno-common -Wall -MP -MMD -MF "${OBJECTDIR}/src/misc/beep.o.d" -o ${OBJECTDIR}/src/misc/beep.o src/misc/beep.c    -DXPRJ_Booteable=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/src/misc/bitmap.o: src/misc/bitmap.c  .generated_files/flags/Booteable/ab9827fadf93ad522caef6f0430369e3d2a29d0f .generated_files/flags/Booteable/89084a3481147dd80e2344e29edcb351eeeb0ca
	@${MKDIR} "${OBJECTDIR}/src/misc" 
	@${RM} ${OBJECTDIR}/src/misc/bitmap.o.d 
	@${RM} ${OBJECTDIR}/src/misc/bitmap.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -Os -fno-common -Wall -MP -MMD -MF "${OBJECTDIR}/src/misc/bitmap.o.d" -o ${OBJECTDIR}/src/misc/bitmap.o src/misc/bitmap.c    -DXPRJ_Booteable=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/src/misc/boton.o: src/misc/boton.c  .generated_files/flags/Booteable/c811ce12a2b6734c3cec0b888bedfc15d15484c0 .generated_files/flags/Booteable/89084a3481147dd80e2344e29edcb351eeeb0ca
	@${MKDIR} "${OBJECTDIR}/src/misc" 
	@${RM} ${OBJECTDIR}/src/misc/boton.o.d 
	@${RM} ${OBJECTDIR}/src/misc/boton.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -Os -fno-common -Wall -MP -MMD -MF "${OBJECTDIR}/src/misc/boton.o.d" -o ${OBJECTDIR}/src/misc/boton.o src/misc/boton.c    -DXPRJ_Booteable=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/src/sd/fsio.o: src/sd/fsio.c  .generated_files/flags/Booteable/2f2ad632aa8ae728571b81b429dc48bbd9ac7729 .generated_files/flags/Booteable/89084a3481147dd80e2344e29edcb351eeeb0ca
	@${MKDIR} "${OBJECTDIR}/src/sd" 
	@${RM} ${OBJECTDIR}/src/sd/fsio.o.d 
	@${RM} ${OBJECTDIR}/src/sd/fsio.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -Os -fno-common -Wall -MP -MMD -MF "${OBJECTDIR}/src/sd/fsio.o.d" -o ${OBJECTDIR}/src/sd/fsio.o src/sd/fsio.c    -DXPRJ_Booteable=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/src/sd/sd_spi.o: src/sd/sd_spi.c  .generated_files/flags/Booteable/1d120125064bae2f8db5d206bd61041bab0237bd .generated_files/flags/Booteable/89084a3481147dd80e2344e29edcb351eeeb0ca
	@${MKDIR} "${OBJECTDIR}/src/sd" 
	@${RM} ${OBJECTDIR}/src/sd/sd_spi.o.d 
	@${RM} ${OBJECTDIR}/src/sd/sd_spi.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -Os -fno-common -Wall -MP -MMD -MF "${OBJECTDIR}/src/sd/sd_spi.o.d" -o ${OBJECTDIR}/src/sd/sd_spi.o src/sd/sd_spi.c    -DXPRJ_Booteable=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/src/wifi/uart3.o: src/wifi/uart3.c  .generated_files/flags/Booteable/c3dc33dcc3750f89cfc655c590374c572bce11a .generated_files/flags/Booteable/89084a3481147dd80e2344e29edcb351eeeb0ca
	@${MKDIR} "${OBJECTDIR}/src/wifi" 
	@${RM} ${OBJECTDIR}/src/wifi/uart3.o.d 
	@${RM} ${OBJECTDIR}/src/wifi/uart3.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -Os -fno-common -Wall -MP -MMD -MF "${OBJECTDIR}/src/wifi/uart3.o.d" -o ${OBJECTDIR}/src/wifi/uart3.o src/wifi/uart3.c    -DXPRJ_Booteable=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/src/wifi/wifi.o: src/wifi/wifi.c  .generated_files/flags/Booteable/2649b5ec03b86a0ec350c089eaeb35edd9484a9d .generated_files/flags/Booteable/89084a3481147dd80e2344e29edcb351eeeb0ca
	@${MKDIR} "${OBJECTDIR}/src/wifi" 
	@${RM} ${OBJECTDIR}/src/wifi/wifi.o.d 
	@${RM} ${OBJECTDIR}/src/wifi/wifi.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -Os -fno-common -Wall -MP -MMD -MF "${OBJECTDIR}/src/wifi/wifi.o.d" -o ${OBJECTDIR}/src/wifi/wifi.o src/wifi/wifi.c    -DXPRJ_Booteable=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/src/main.o: src/main.c  .generated_files/flags/Booteable/36be155dfcc82fcc1c4d540c30b0309a192520cc .generated_files/flags/Booteable/89084a3481147dd80e2344e29edcb351eeeb0ca
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/main.o.d 
	@${RM} ${OBJECTDIR}/src/main.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -Os -fno-common -Wall -MP -MMD -MF "${OBJECTDIR}/src/main.o.d" -o ${OBJECTDIR}/src/main.o src/main.c    -DXPRJ_Booteable=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/src/system.o: src/system.c  .generated_files/flags/Booteable/94c19ad7e1091dde41d125daa78a764c082a646e .generated_files/flags/Booteable/89084a3481147dd80e2344e29edcb351eeeb0ca
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/system.o.d 
	@${RM} ${OBJECTDIR}/src/system.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -Os -fno-common -Wall -MP -MMD -MF "${OBJECTDIR}/src/system.o.d" -o ${OBJECTDIR}/src/system.o src/system.c    -DXPRJ_Booteable=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/src/log.o: src/log.c  .generated_files/flags/Booteable/2baabf6d08bae7d335a9a29b43807d645dda6781 .generated_files/flags/Booteable/89084a3481147dd80e2344e29edcb351eeeb0ca
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/log.o.d 
	@${RM} ${OBJECTDIR}/src/log.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -Os -fno-common -Wall -MP -MMD -MF "${OBJECTDIR}/src/log.o.d" -o ${OBJECTDIR}/src/log.o src/log.c    -DXPRJ_Booteable=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/src/rtcc.o: src/rtcc.c  .generated_files/flags/Booteable/ac38e3da1a63e1ad08dc59ea207a7c1495e332da .generated_files/flags/Booteable/89084a3481147dd80e2344e29edcb351eeeb0ca
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/rtcc.o.d 
	@${RM} ${OBJECTDIR}/src/rtcc.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -Os -fno-common -Wall -MP -MMD -MF "${OBJECTDIR}/src/rtcc.o.d" -o ${OBJECTDIR}/src/rtcc.o src/rtcc.c    -DXPRJ_Booteable=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/src/control.o: src/control.c  .generated_files/flags/Booteable/5a8b817b20dc6c201bfce21ca259696236a4b9e7 .generated_files/flags/Booteable/89084a3481147dd80e2344e29edcb351eeeb0ca
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/control.o.d 
	@${RM} ${OBJECTDIR}/src/control.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -Os -fno-common -Wall -MP -MMD -MF "${OBJECTDIR}/src/control.o.d" -o ${OBJECTDIR}/src/control.o src/control.c    -DXPRJ_Booteable=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/src/config.o: src/config.c  .generated_files/flags/Booteable/225ac92129f29fd7fedaf11df6664dd43ed64fe0 .generated_files/flags/Booteable/89084a3481147dd80e2344e29edcb351eeeb0ca
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/config.o.d 
	@${RM} ${OBJECTDIR}/src/config.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -Os -fno-common -Wall -MP -MMD -MF "${OBJECTDIR}/src/config.o.d" -o ${OBJECTDIR}/src/config.o src/config.c    -DXPRJ_Booteable=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/src/http.o: src/http.c  .generated_files/flags/Booteable/749f78b262631fe0f3a3cf56253d19f5d74ebde0 .generated_files/flags/Booteable/89084a3481147dd80e2344e29edcb351eeeb0ca
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/http.o.d 
	@${RM} ${OBJECTDIR}/src/http.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -Os -fno-common -Wall -MP -MMD -MF "${OBJECTDIR}/src/http.o.d" -o ${OBJECTDIR}/src/http.o src/http.c    -DXPRJ_Booteable=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
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
	${MP_CC} $(MP_EXTRA_LD_PRE) -g -mdebugger -D__MPLAB_DEBUGGER_PK3=1 -mprocessor=$(MP_PROCESSOR_OPTION) -Os -o ${DISTDIR}/Programa-2.${IMAGE_TYPE}.${OUTPUT_SUFFIX} ${OBJECTFILES_QUOTED_IF_SPACED}          -DXPRJ_Booteable=$(CND_CONF)    $(COMPARISON_BUILD)   -mreserve=data@0x0:0x1FC -mreserve=boot@0x1FC00490:0x1FC016FF -mreserve=boot@0x1FC00490:0x1FC00BEF  -Wl,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_LD_POST)$(MP_LINKER_FILE_OPTION),--defsym=__MPLAB_DEBUG=1,--defsym=__DEBUG=1,-D=__DEBUG_D,--defsym=__MPLAB_DEBUGGER_PK3=1,--defsym=_min_heap_size=0,--gc-sections,--no-code-in-dinit,--no-dinit-in-serial-mem,-Map="${DISTDIR}/${PROJECTNAME}.${IMAGE_TYPE}.map",-s,--memorysummary,${DISTDIR}/memoryfile.xml -mdfp="${DFP_DIR}"
	
else
${DISTDIR}/Programa-2.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk   ../../pic32mmBoot/Programa/app_p32MM0256GPM028.ld
	@${MKDIR} ${DISTDIR} 
	${MP_CC} $(MP_EXTRA_LD_PRE)  -mprocessor=$(MP_PROCESSOR_OPTION) -Os -o ${DISTDIR}/Programa-2.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX} ${OBJECTFILES_QUOTED_IF_SPACED}          -DXPRJ_Booteable=$(CND_CONF)    $(COMPARISON_BUILD)  -Wl,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_LD_POST)$(MP_LINKER_FILE_OPTION),--defsym=_min_heap_size=0,--gc-sections,--no-code-in-dinit,--no-dinit-in-serial-mem,-Map="${DISTDIR}/${PROJECTNAME}.${IMAGE_TYPE}.map",-s,--memorysummary,${DISTDIR}/memoryfile.xml -mdfp="${DFP_DIR}"
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
