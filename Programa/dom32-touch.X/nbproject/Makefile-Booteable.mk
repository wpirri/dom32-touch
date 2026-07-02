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

ifdef SUB_IMAGE_ADDRESS

else
SUB_IMAGE_ADDRESS_COMMAND=
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
ImagePath="${DISTDIR}\dom32-touch.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}"
ImageDir="${DISTDIR}"
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
${OBJECTDIR}/_ext/8742029/dili9341.o: ../display/dili9341.c  .generated_files/flags/Booteable/d550f4e553996355c189419f12d4307d634243f4 .generated_files/flags/Booteable/8c9efd018bf36f61fa53e2f3fa7357a06b4304bf
	@${MKDIR} "${OBJECTDIR}/_ext/8742029" 
	@${RM} ${OBJECTDIR}/_ext/8742029/dili9341.o.d 
	@${RM} ${OBJECTDIR}/_ext/8742029/dili9341.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O2 -fno-common -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/8742029/dili9341.o.d" -o ${OBJECTDIR}/_ext/8742029/dili9341.o ../display/dili9341.c    -DXPRJ_Booteable=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/8742029/touch.o: ../display/touch.c  .generated_files/flags/Booteable/a142decc038144cf11f759b6d1957c5750147c46 .generated_files/flags/Booteable/8c9efd018bf36f61fa53e2f3fa7357a06b4304bf
	@${MKDIR} "${OBJECTDIR}/_ext/8742029" 
	@${RM} ${OBJECTDIR}/_ext/8742029/touch.o.d 
	@${RM} ${OBJECTDIR}/_ext/8742029/touch.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O2 -fno-common -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/8742029/touch.o.d" -o ${OBJECTDIR}/_ext/8742029/touch.o ../display/touch.c    -DXPRJ_Booteable=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/8742029/display.o: ../display/display.c  .generated_files/flags/Booteable/fc858deab742251adec34b577962abd7e852117f .generated_files/flags/Booteable/8c9efd018bf36f61fa53e2f3fa7357a06b4304bf
	@${MKDIR} "${OBJECTDIR}/_ext/8742029" 
	@${RM} ${OBJECTDIR}/_ext/8742029/display.o.d 
	@${RM} ${OBJECTDIR}/_ext/8742029/display.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O2 -fno-common -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/8742029/display.o.d" -o ${OBJECTDIR}/_ext/8742029/display.o ../display/display.c    -DXPRJ_Booteable=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/43901184/fsio.o: ../sd/fsio.c  .generated_files/flags/Booteable/47587fb39073474285a0fbdcdd8ef16357a3dd1b .generated_files/flags/Booteable/8c9efd018bf36f61fa53e2f3fa7357a06b4304bf
	@${MKDIR} "${OBJECTDIR}/_ext/43901184" 
	@${RM} ${OBJECTDIR}/_ext/43901184/fsio.o.d 
	@${RM} ${OBJECTDIR}/_ext/43901184/fsio.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O2 -fno-common -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/43901184/fsio.o.d" -o ${OBJECTDIR}/_ext/43901184/fsio.o ../sd/fsio.c    -DXPRJ_Booteable=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/43901184/sd_spi.o: ../sd/sd_spi.c  .generated_files/flags/Booteable/ce10a4cc57eb1a45ec028ace74291e371b70c4a .generated_files/flags/Booteable/8c9efd018bf36f61fa53e2f3fa7357a06b4304bf
	@${MKDIR} "${OBJECTDIR}/_ext/43901184" 
	@${RM} ${OBJECTDIR}/_ext/43901184/sd_spi.o.d 
	@${RM} ${OBJECTDIR}/_ext/43901184/sd_spi.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O2 -fno-common -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/43901184/sd_spi.o.d" -o ${OBJECTDIR}/_ext/43901184/sd_spi.o ../sd/sd_spi.c    -DXPRJ_Booteable=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1472/main.o: ../main.c  .generated_files/flags/Booteable/2c73ba9a9323501a071001acd47be46935f8fbe6 .generated_files/flags/Booteable/8c9efd018bf36f61fa53e2f3fa7357a06b4304bf
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/main.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/main.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O2 -fno-common -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1472/main.o.d" -o ${OBJECTDIR}/_ext/1472/main.o ../main.c    -DXPRJ_Booteable=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1472/log.o: ../log.c  .generated_files/flags/Booteable/4cd72ebc3b2d25c6e4b325426fcfe726e3d31cbc .generated_files/flags/Booteable/8c9efd018bf36f61fa53e2f3fa7357a06b4304bf
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/log.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/log.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O2 -fno-common -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1472/log.o.d" -o ${OBJECTDIR}/_ext/1472/log.o ../log.c    -DXPRJ_Booteable=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1472/config.o: ../config.c  .generated_files/flags/Booteable/c5e04936cf1a609f493a2faa1d20a19771090478 .generated_files/flags/Booteable/8c9efd018bf36f61fa53e2f3fa7357a06b4304bf
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/config.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/config.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O2 -fno-common -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1472/config.o.d" -o ${OBJECTDIR}/_ext/1472/config.o ../config.c    -DXPRJ_Booteable=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1472/delay.o: ../delay.c  .generated_files/flags/Booteable/4e8d993f6bb2a3ac488decb72853a984ea3c7406 .generated_files/flags/Booteable/8c9efd018bf36f61fa53e2f3fa7357a06b4304bf
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/delay.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/delay.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O2 -fno-common -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1472/delay.o.d" -o ${OBJECTDIR}/_ext/1472/delay.o ../delay.c    -DXPRJ_Booteable=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1472/boton.o: ../boton.c  .generated_files/flags/Booteable/5ee904c13a7c58bff35689fc56f16e399c86431 .generated_files/flags/Booteable/8c9efd018bf36f61fa53e2f3fa7357a06b4304bf
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/boton.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/boton.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O2 -fno-common -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1472/boton.o.d" -o ${OBJECTDIR}/_ext/1472/boton.o ../boton.c    -DXPRJ_Booteable=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1472/bitmap.o: ../bitmap.c  .generated_files/flags/Booteable/c2db393bdb76a89ee13b3f7d70a37b5a58f65dd2 .generated_files/flags/Booteable/8c9efd018bf36f61fa53e2f3fa7357a06b4304bf
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/bitmap.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/bitmap.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O2 -fno-common -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1472/bitmap.o.d" -o ${OBJECTDIR}/_ext/1472/bitmap.o ../bitmap.c    -DXPRJ_Booteable=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1472/beep.o: ../beep.c  .generated_files/flags/Booteable/5c59435684d5b2fa6198393a9dc14af94e36ff00 .generated_files/flags/Booteable/8c9efd018bf36f61fa53e2f3fa7357a06b4304bf
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/beep.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/beep.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O2 -fno-common -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1472/beep.o.d" -o ${OBJECTDIR}/_ext/1472/beep.o ../beep.c    -DXPRJ_Booteable=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1472/wifi.o: ../wifi.c  .generated_files/flags/Booteable/a19a88de977f78c54a01c8f68724026ce595bbb5 .generated_files/flags/Booteable/8c9efd018bf36f61fa53e2f3fa7357a06b4304bf
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/wifi.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/wifi.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O2 -fno-common -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1472/wifi.o.d" -o ${OBJECTDIR}/_ext/1472/wifi.o ../wifi.c    -DXPRJ_Booteable=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1472/strfunc.o: ../strfunc.c  .generated_files/flags/Booteable/815598fade976b6623716bdd86d5d89ba5fc9d47 .generated_files/flags/Booteable/8c9efd018bf36f61fa53e2f3fa7357a06b4304bf
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/strfunc.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/strfunc.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O2 -fno-common -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1472/strfunc.o.d" -o ${OBJECTDIR}/_ext/1472/strfunc.o ../strfunc.c    -DXPRJ_Booteable=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1472/http.o: ../http.c  .generated_files/flags/Booteable/ef2c0612197310e7b77fa9fb58988efd7c49f7e3 .generated_files/flags/Booteable/8c9efd018bf36f61fa53e2f3fa7357a06b4304bf
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/http.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/http.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O2 -fno-common -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1472/http.o.d" -o ${OBJECTDIR}/_ext/1472/http.o ../http.c    -DXPRJ_Booteable=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1472/control.o: ../control.c  .generated_files/flags/Booteable/7af8c921dca1466a60c3a4230ef5d03ca0b6fea3 .generated_files/flags/Booteable/8c9efd018bf36f61fa53e2f3fa7357a06b4304bf
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/control.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/control.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O2 -fno-common -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1472/control.o.d" -o ${OBJECTDIR}/_ext/1472/control.o ../control.c    -DXPRJ_Booteable=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1472/rtcc.o: ../rtcc.c  .generated_files/flags/Booteable/2cea861ce6e8d5e1ef2bd8a645237815822d7c51 .generated_files/flags/Booteable/8c9efd018bf36f61fa53e2f3fa7357a06b4304bf
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/rtcc.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/rtcc.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O2 -fno-common -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1472/rtcc.o.d" -o ${OBJECTDIR}/_ext/1472/rtcc.o ../rtcc.c    -DXPRJ_Booteable=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1472/uart3.o: ../uart3.c  .generated_files/flags/Booteable/b75f19f3ff17de3a15caf679695570736fffec07 .generated_files/flags/Booteable/8c9efd018bf36f61fa53e2f3fa7357a06b4304bf
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/uart3.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/uart3.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O2 -fno-common -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1472/uart3.o.d" -o ${OBJECTDIR}/_ext/1472/uart3.o ../uart3.c    -DXPRJ_Booteable=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
else
${OBJECTDIR}/_ext/8742029/dili9341.o: ../display/dili9341.c  .generated_files/flags/Booteable/d038ace107eec7a8ed624345f8d21fa6e075dbcb .generated_files/flags/Booteable/8c9efd018bf36f61fa53e2f3fa7357a06b4304bf
	@${MKDIR} "${OBJECTDIR}/_ext/8742029" 
	@${RM} ${OBJECTDIR}/_ext/8742029/dili9341.o.d 
	@${RM} ${OBJECTDIR}/_ext/8742029/dili9341.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O2 -fno-common -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/8742029/dili9341.o.d" -o ${OBJECTDIR}/_ext/8742029/dili9341.o ../display/dili9341.c    -DXPRJ_Booteable=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/8742029/touch.o: ../display/touch.c  .generated_files/flags/Booteable/587a2f3acfb86005f419e088f89ad69bc2730935 .generated_files/flags/Booteable/8c9efd018bf36f61fa53e2f3fa7357a06b4304bf
	@${MKDIR} "${OBJECTDIR}/_ext/8742029" 
	@${RM} ${OBJECTDIR}/_ext/8742029/touch.o.d 
	@${RM} ${OBJECTDIR}/_ext/8742029/touch.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O2 -fno-common -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/8742029/touch.o.d" -o ${OBJECTDIR}/_ext/8742029/touch.o ../display/touch.c    -DXPRJ_Booteable=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/8742029/display.o: ../display/display.c  .generated_files/flags/Booteable/3529c20ecb885a2694481c771c08f3d37ab200bc .generated_files/flags/Booteable/8c9efd018bf36f61fa53e2f3fa7357a06b4304bf
	@${MKDIR} "${OBJECTDIR}/_ext/8742029" 
	@${RM} ${OBJECTDIR}/_ext/8742029/display.o.d 
	@${RM} ${OBJECTDIR}/_ext/8742029/display.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O2 -fno-common -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/8742029/display.o.d" -o ${OBJECTDIR}/_ext/8742029/display.o ../display/display.c    -DXPRJ_Booteable=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/43901184/fsio.o: ../sd/fsio.c  .generated_files/flags/Booteable/fea763202824f64928f973718a24c4d558ada354 .generated_files/flags/Booteable/8c9efd018bf36f61fa53e2f3fa7357a06b4304bf
	@${MKDIR} "${OBJECTDIR}/_ext/43901184" 
	@${RM} ${OBJECTDIR}/_ext/43901184/fsio.o.d 
	@${RM} ${OBJECTDIR}/_ext/43901184/fsio.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O2 -fno-common -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/43901184/fsio.o.d" -o ${OBJECTDIR}/_ext/43901184/fsio.o ../sd/fsio.c    -DXPRJ_Booteable=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/43901184/sd_spi.o: ../sd/sd_spi.c  .generated_files/flags/Booteable/e6069c3e9d25045794c4e6b75471b34f7d46540 .generated_files/flags/Booteable/8c9efd018bf36f61fa53e2f3fa7357a06b4304bf
	@${MKDIR} "${OBJECTDIR}/_ext/43901184" 
	@${RM} ${OBJECTDIR}/_ext/43901184/sd_spi.o.d 
	@${RM} ${OBJECTDIR}/_ext/43901184/sd_spi.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O2 -fno-common -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/43901184/sd_spi.o.d" -o ${OBJECTDIR}/_ext/43901184/sd_spi.o ../sd/sd_spi.c    -DXPRJ_Booteable=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1472/main.o: ../main.c  .generated_files/flags/Booteable/d200a627da9e6c0093a3f88e42dc493fa0149eaf .generated_files/flags/Booteable/8c9efd018bf36f61fa53e2f3fa7357a06b4304bf
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/main.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/main.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O2 -fno-common -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1472/main.o.d" -o ${OBJECTDIR}/_ext/1472/main.o ../main.c    -DXPRJ_Booteable=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1472/log.o: ../log.c  .generated_files/flags/Booteable/566899bbd63739402fdd3e4f95890101af93fc9b .generated_files/flags/Booteable/8c9efd018bf36f61fa53e2f3fa7357a06b4304bf
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/log.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/log.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O2 -fno-common -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1472/log.o.d" -o ${OBJECTDIR}/_ext/1472/log.o ../log.c    -DXPRJ_Booteable=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1472/config.o: ../config.c  .generated_files/flags/Booteable/c92e8516a8099ae1b8888223a62ac936a38f7837 .generated_files/flags/Booteable/8c9efd018bf36f61fa53e2f3fa7357a06b4304bf
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/config.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/config.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O2 -fno-common -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1472/config.o.d" -o ${OBJECTDIR}/_ext/1472/config.o ../config.c    -DXPRJ_Booteable=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1472/delay.o: ../delay.c  .generated_files/flags/Booteable/3b2d94ba882ff37afa68c4a48d716ae6c6baafb3 .generated_files/flags/Booteable/8c9efd018bf36f61fa53e2f3fa7357a06b4304bf
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/delay.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/delay.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O2 -fno-common -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1472/delay.o.d" -o ${OBJECTDIR}/_ext/1472/delay.o ../delay.c    -DXPRJ_Booteable=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1472/boton.o: ../boton.c  .generated_files/flags/Booteable/92038edf47b6fd4a22da058800acf83a6c49014 .generated_files/flags/Booteable/8c9efd018bf36f61fa53e2f3fa7357a06b4304bf
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/boton.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/boton.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O2 -fno-common -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1472/boton.o.d" -o ${OBJECTDIR}/_ext/1472/boton.o ../boton.c    -DXPRJ_Booteable=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1472/bitmap.o: ../bitmap.c  .generated_files/flags/Booteable/cea8325059e8e94c14a014bf18e1a586f1d7e98b .generated_files/flags/Booteable/8c9efd018bf36f61fa53e2f3fa7357a06b4304bf
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/bitmap.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/bitmap.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O2 -fno-common -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1472/bitmap.o.d" -o ${OBJECTDIR}/_ext/1472/bitmap.o ../bitmap.c    -DXPRJ_Booteable=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1472/beep.o: ../beep.c  .generated_files/flags/Booteable/55380a9006b209a6fd958dabca1a1cca05140970 .generated_files/flags/Booteable/8c9efd018bf36f61fa53e2f3fa7357a06b4304bf
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/beep.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/beep.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O2 -fno-common -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1472/beep.o.d" -o ${OBJECTDIR}/_ext/1472/beep.o ../beep.c    -DXPRJ_Booteable=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1472/wifi.o: ../wifi.c  .generated_files/flags/Booteable/97248f2af10694b793af369961b32bbcbbc29b29 .generated_files/flags/Booteable/8c9efd018bf36f61fa53e2f3fa7357a06b4304bf
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/wifi.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/wifi.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O2 -fno-common -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1472/wifi.o.d" -o ${OBJECTDIR}/_ext/1472/wifi.o ../wifi.c    -DXPRJ_Booteable=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1472/strfunc.o: ../strfunc.c  .generated_files/flags/Booteable/1ad18bfaefd628830283640e3a207cba27aab4f6 .generated_files/flags/Booteable/8c9efd018bf36f61fa53e2f3fa7357a06b4304bf
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/strfunc.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/strfunc.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O2 -fno-common -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1472/strfunc.o.d" -o ${OBJECTDIR}/_ext/1472/strfunc.o ../strfunc.c    -DXPRJ_Booteable=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1472/http.o: ../http.c  .generated_files/flags/Booteable/cc47fe87927f68ef630df7ccaa64b04fd48d5234 .generated_files/flags/Booteable/8c9efd018bf36f61fa53e2f3fa7357a06b4304bf
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/http.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/http.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O2 -fno-common -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1472/http.o.d" -o ${OBJECTDIR}/_ext/1472/http.o ../http.c    -DXPRJ_Booteable=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1472/control.o: ../control.c  .generated_files/flags/Booteable/b4e64d03797f670e70681e19bcea0546cd7d48ec .generated_files/flags/Booteable/8c9efd018bf36f61fa53e2f3fa7357a06b4304bf
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/control.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/control.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O2 -fno-common -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1472/control.o.d" -o ${OBJECTDIR}/_ext/1472/control.o ../control.c    -DXPRJ_Booteable=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1472/rtcc.o: ../rtcc.c  .generated_files/flags/Booteable/824ef29e6c189166a6a1f6a4df24e6f149ea6dfc .generated_files/flags/Booteable/8c9efd018bf36f61fa53e2f3fa7357a06b4304bf
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/rtcc.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/rtcc.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O2 -fno-common -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1472/rtcc.o.d" -o ${OBJECTDIR}/_ext/1472/rtcc.o ../rtcc.c    -DXPRJ_Booteable=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1472/uart3.o: ../uart3.c  .generated_files/flags/Booteable/c484eefedb5997ea01f9452cf3a0af5008fc4b78 .generated_files/flags/Booteable/8c9efd018bf36f61fa53e2f3fa7357a06b4304bf
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/uart3.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/uart3.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O2 -fno-common -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1472/uart3.o.d" -o ${OBJECTDIR}/_ext/1472/uart3.o ../uart3.c    -DXPRJ_Booteable=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
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
	${MP_CC} $(MP_EXTRA_LD_PRE) -g   -mprocessor=$(MP_PROCESSOR_OPTION) -O2 -o ${DISTDIR}/dom32-touch.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX} ${OBJECTFILES_QUOTED_IF_SPACED}          -DXPRJ_Booteable=$(CND_CONF)    $(COMPARISON_BUILD)      -Wl,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_LD_POST)$(MP_LINKER_FILE_OPTION),--defsym=__MPLAB_DEBUG=1,--defsym=__DEBUG=1,-D=__DEBUG_D,--defsym=_min_heap_size=0,--gc-sections,--no-code-in-dinit,--no-dinit-in-serial-mem,-Map="${DISTDIR}/${PROJECTNAME}.${IMAGE_TYPE}.map",-s,--memorysummary,${DISTDIR}/memoryfile.xml -mdfp="${DFP_DIR}"
	
else
${DISTDIR}/dom32-touch.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk   ../../../pic32mmBoot/Programa/app_p32MM0256GPM028.ld
	@${MKDIR} ${DISTDIR} 
	${MP_CC} $(MP_EXTRA_LD_PRE)  -mprocessor=$(MP_PROCESSOR_OPTION) -O2 -o ${DISTDIR}/dom32-touch.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX} ${OBJECTFILES_QUOTED_IF_SPACED}          -DXPRJ_Booteable=$(CND_CONF)    $(COMPARISON_BUILD)  -Wl,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_LD_POST)$(MP_LINKER_FILE_OPTION),--defsym=_min_heap_size=0,--gc-sections,--no-code-in-dinit,--no-dinit-in-serial-mem,-Map="${DISTDIR}/${PROJECTNAME}.${IMAGE_TYPE}.map",-s,--memorysummary,${DISTDIR}/memoryfile.xml -mdfp="${DFP_DIR}"
	${MP_CC_DIR}\\xc32-bin2hex ${DISTDIR}/dom32-touch.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX} 
	@echo Normalizing hex file
	@"C:/Program Files/Microchip/MPLABX/v6.00/mplab_platform/platform/../mplab_ide/modules/../../bin/hexmate" --edf="C:/Program Files/Microchip/MPLABX/v6.00/mplab_platform/platform/../mplab_ide/modules/../../dat/en_msgs.txt" ${DISTDIR}/dom32-touch.X.${IMAGE_TYPE}.hex -o${DISTDIR}/dom32-touch.X.${IMAGE_TYPE}.hex

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
