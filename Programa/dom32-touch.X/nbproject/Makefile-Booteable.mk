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
${OBJECTDIR}/_ext/8742029/dili9341.o: ../display/dili9341.c  .generated_files/flags/Booteable/f95a994a78134916d0e6a09d9eabc138fb1b1206 .generated_files/flags/Booteable/2929bbcf261be56c36d51eeaa474451d34a88bb3
	@${MKDIR} "${OBJECTDIR}/_ext/8742029" 
	@${RM} ${OBJECTDIR}/_ext/8742029/dili9341.o.d 
	@${RM} ${OBJECTDIR}/_ext/8742029/dili9341.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O2 -fno-common -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/8742029/dili9341.o.d" -o ${OBJECTDIR}/_ext/8742029/dili9341.o ../display/dili9341.c    -DXPRJ_Booteable=$(CND_CONF)    $(COMPARISON_BUILD)    
	
${OBJECTDIR}/_ext/8742029/touch.o: ../display/touch.c  .generated_files/flags/Booteable/fa0144f9bf333ad761ba6e6e4dca123d643d2158 .generated_files/flags/Booteable/2929bbcf261be56c36d51eeaa474451d34a88bb3
	@${MKDIR} "${OBJECTDIR}/_ext/8742029" 
	@${RM} ${OBJECTDIR}/_ext/8742029/touch.o.d 
	@${RM} ${OBJECTDIR}/_ext/8742029/touch.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O2 -fno-common -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/8742029/touch.o.d" -o ${OBJECTDIR}/_ext/8742029/touch.o ../display/touch.c    -DXPRJ_Booteable=$(CND_CONF)    $(COMPARISON_BUILD)    
	
${OBJECTDIR}/_ext/8742029/display.o: ../display/display.c  .generated_files/flags/Booteable/d50de010f4eb5882f0bd306c115c8046cff33742 .generated_files/flags/Booteable/2929bbcf261be56c36d51eeaa474451d34a88bb3
	@${MKDIR} "${OBJECTDIR}/_ext/8742029" 
	@${RM} ${OBJECTDIR}/_ext/8742029/display.o.d 
	@${RM} ${OBJECTDIR}/_ext/8742029/display.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O2 -fno-common -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/8742029/display.o.d" -o ${OBJECTDIR}/_ext/8742029/display.o ../display/display.c    -DXPRJ_Booteable=$(CND_CONF)    $(COMPARISON_BUILD)    
	
${OBJECTDIR}/_ext/43901184/fsio.o: ../sd/fsio.c  .generated_files/flags/Booteable/d3487c5415542c2cfec45a1e937ec1e306e38d2b .generated_files/flags/Booteable/2929bbcf261be56c36d51eeaa474451d34a88bb3
	@${MKDIR} "${OBJECTDIR}/_ext/43901184" 
	@${RM} ${OBJECTDIR}/_ext/43901184/fsio.o.d 
	@${RM} ${OBJECTDIR}/_ext/43901184/fsio.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O2 -fno-common -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/43901184/fsio.o.d" -o ${OBJECTDIR}/_ext/43901184/fsio.o ../sd/fsio.c    -DXPRJ_Booteable=$(CND_CONF)    $(COMPARISON_BUILD)    
	
${OBJECTDIR}/_ext/43901184/sd_spi.o: ../sd/sd_spi.c  .generated_files/flags/Booteable/ca023bd26a254db6fcbc4068c390a39d70d13fd .generated_files/flags/Booteable/2929bbcf261be56c36d51eeaa474451d34a88bb3
	@${MKDIR} "${OBJECTDIR}/_ext/43901184" 
	@${RM} ${OBJECTDIR}/_ext/43901184/sd_spi.o.d 
	@${RM} ${OBJECTDIR}/_ext/43901184/sd_spi.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O2 -fno-common -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/43901184/sd_spi.o.d" -o ${OBJECTDIR}/_ext/43901184/sd_spi.o ../sd/sd_spi.c    -DXPRJ_Booteable=$(CND_CONF)    $(COMPARISON_BUILD)    
	
${OBJECTDIR}/_ext/1472/main.o: ../main.c  .generated_files/flags/Booteable/81f4e2345544b52e01bd7c528583a4df065024ea .generated_files/flags/Booteable/2929bbcf261be56c36d51eeaa474451d34a88bb3
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/main.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/main.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O2 -fno-common -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1472/main.o.d" -o ${OBJECTDIR}/_ext/1472/main.o ../main.c    -DXPRJ_Booteable=$(CND_CONF)    $(COMPARISON_BUILD)    
	
${OBJECTDIR}/_ext/1472/log.o: ../log.c  .generated_files/flags/Booteable/556bfa25d4d8568450a348c36b7eb936857f584a .generated_files/flags/Booteable/2929bbcf261be56c36d51eeaa474451d34a88bb3
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/log.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/log.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O2 -fno-common -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1472/log.o.d" -o ${OBJECTDIR}/_ext/1472/log.o ../log.c    -DXPRJ_Booteable=$(CND_CONF)    $(COMPARISON_BUILD)    
	
${OBJECTDIR}/_ext/1472/config.o: ../config.c  .generated_files/flags/Booteable/9284d74fbfc81938d95712fcc4be29ce4efdeb8e .generated_files/flags/Booteable/2929bbcf261be56c36d51eeaa474451d34a88bb3
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/config.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/config.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O2 -fno-common -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1472/config.o.d" -o ${OBJECTDIR}/_ext/1472/config.o ../config.c    -DXPRJ_Booteable=$(CND_CONF)    $(COMPARISON_BUILD)    
	
${OBJECTDIR}/_ext/1472/delay.o: ../delay.c  .generated_files/flags/Booteable/e9d992f87b55df31ca898feef186ad016e725142 .generated_files/flags/Booteable/2929bbcf261be56c36d51eeaa474451d34a88bb3
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/delay.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/delay.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O2 -fno-common -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1472/delay.o.d" -o ${OBJECTDIR}/_ext/1472/delay.o ../delay.c    -DXPRJ_Booteable=$(CND_CONF)    $(COMPARISON_BUILD)    
	
${OBJECTDIR}/_ext/1472/boton.o: ../boton.c  .generated_files/flags/Booteable/8903dfd3cbe86393593d7f38abb52d16529562 .generated_files/flags/Booteable/2929bbcf261be56c36d51eeaa474451d34a88bb3
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/boton.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/boton.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O2 -fno-common -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1472/boton.o.d" -o ${OBJECTDIR}/_ext/1472/boton.o ../boton.c    -DXPRJ_Booteable=$(CND_CONF)    $(COMPARISON_BUILD)    
	
${OBJECTDIR}/_ext/1472/bitmap.o: ../bitmap.c  .generated_files/flags/Booteable/b44743964d9bb76a395e97b93a039bc63a8ea94a .generated_files/flags/Booteable/2929bbcf261be56c36d51eeaa474451d34a88bb3
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/bitmap.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/bitmap.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O2 -fno-common -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1472/bitmap.o.d" -o ${OBJECTDIR}/_ext/1472/bitmap.o ../bitmap.c    -DXPRJ_Booteable=$(CND_CONF)    $(COMPARISON_BUILD)    
	
${OBJECTDIR}/_ext/1472/beep.o: ../beep.c  .generated_files/flags/Booteable/800ba2ea7330c8d4168fce74417313b4667f1946 .generated_files/flags/Booteable/2929bbcf261be56c36d51eeaa474451d34a88bb3
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/beep.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/beep.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O2 -fno-common -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1472/beep.o.d" -o ${OBJECTDIR}/_ext/1472/beep.o ../beep.c    -DXPRJ_Booteable=$(CND_CONF)    $(COMPARISON_BUILD)    
	
${OBJECTDIR}/_ext/1472/wifi.o: ../wifi.c  .generated_files/flags/Booteable/dd413080650944248b07d509c866f065aac861b5 .generated_files/flags/Booteable/2929bbcf261be56c36d51eeaa474451d34a88bb3
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/wifi.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/wifi.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O2 -fno-common -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1472/wifi.o.d" -o ${OBJECTDIR}/_ext/1472/wifi.o ../wifi.c    -DXPRJ_Booteable=$(CND_CONF)    $(COMPARISON_BUILD)    
	
${OBJECTDIR}/_ext/1472/strfunc.o: ../strfunc.c  .generated_files/flags/Booteable/acb16d226cffdfb8772aa6fffd1465c121c20d1 .generated_files/flags/Booteable/2929bbcf261be56c36d51eeaa474451d34a88bb3
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/strfunc.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/strfunc.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O2 -fno-common -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1472/strfunc.o.d" -o ${OBJECTDIR}/_ext/1472/strfunc.o ../strfunc.c    -DXPRJ_Booteable=$(CND_CONF)    $(COMPARISON_BUILD)    
	
${OBJECTDIR}/_ext/1472/http.o: ../http.c  .generated_files/flags/Booteable/2ea08975a481e7ddd681a3fb364e7b91e2a2d050 .generated_files/flags/Booteable/2929bbcf261be56c36d51eeaa474451d34a88bb3
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/http.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/http.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O2 -fno-common -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1472/http.o.d" -o ${OBJECTDIR}/_ext/1472/http.o ../http.c    -DXPRJ_Booteable=$(CND_CONF)    $(COMPARISON_BUILD)    
	
${OBJECTDIR}/_ext/1472/control.o: ../control.c  .generated_files/flags/Booteable/1fbf34c56cc6e1f6d35df4ac4e172db723fb186c .generated_files/flags/Booteable/2929bbcf261be56c36d51eeaa474451d34a88bb3
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/control.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/control.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O2 -fno-common -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1472/control.o.d" -o ${OBJECTDIR}/_ext/1472/control.o ../control.c    -DXPRJ_Booteable=$(CND_CONF)    $(COMPARISON_BUILD)    
	
${OBJECTDIR}/_ext/1472/rtcc.o: ../rtcc.c  .generated_files/flags/Booteable/f56f2f049f1ce7846a97d6ab07ac83bde1d0eae8 .generated_files/flags/Booteable/2929bbcf261be56c36d51eeaa474451d34a88bb3
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/rtcc.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/rtcc.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O2 -fno-common -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1472/rtcc.o.d" -o ${OBJECTDIR}/_ext/1472/rtcc.o ../rtcc.c    -DXPRJ_Booteable=$(CND_CONF)    $(COMPARISON_BUILD)    
	
${OBJECTDIR}/_ext/1472/uart3.o: ../uart3.c  .generated_files/flags/Booteable/cf2fc511adda3b39973e004683ed3dbc1a1b1c0e .generated_files/flags/Booteable/2929bbcf261be56c36d51eeaa474451d34a88bb3
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/uart3.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/uart3.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O2 -fno-common -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1472/uart3.o.d" -o ${OBJECTDIR}/_ext/1472/uart3.o ../uart3.c    -DXPRJ_Booteable=$(CND_CONF)    $(COMPARISON_BUILD)    
	
else
${OBJECTDIR}/_ext/8742029/dili9341.o: ../display/dili9341.c  .generated_files/flags/Booteable/f089a4b644e387752111ba8c477067f3fc32e37c .generated_files/flags/Booteable/2929bbcf261be56c36d51eeaa474451d34a88bb3
	@${MKDIR} "${OBJECTDIR}/_ext/8742029" 
	@${RM} ${OBJECTDIR}/_ext/8742029/dili9341.o.d 
	@${RM} ${OBJECTDIR}/_ext/8742029/dili9341.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O2 -fno-common -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/8742029/dili9341.o.d" -o ${OBJECTDIR}/_ext/8742029/dili9341.o ../display/dili9341.c    -DXPRJ_Booteable=$(CND_CONF)    $(COMPARISON_BUILD)    
	
${OBJECTDIR}/_ext/8742029/touch.o: ../display/touch.c  .generated_files/flags/Booteable/7ca8ac5fbe166e8c64f879316d117b5ea9697b05 .generated_files/flags/Booteable/2929bbcf261be56c36d51eeaa474451d34a88bb3
	@${MKDIR} "${OBJECTDIR}/_ext/8742029" 
	@${RM} ${OBJECTDIR}/_ext/8742029/touch.o.d 
	@${RM} ${OBJECTDIR}/_ext/8742029/touch.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O2 -fno-common -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/8742029/touch.o.d" -o ${OBJECTDIR}/_ext/8742029/touch.o ../display/touch.c    -DXPRJ_Booteable=$(CND_CONF)    $(COMPARISON_BUILD)    
	
${OBJECTDIR}/_ext/8742029/display.o: ../display/display.c  .generated_files/flags/Booteable/36d2ddd1e34be5f76590d627f9d07351ee547e8b .generated_files/flags/Booteable/2929bbcf261be56c36d51eeaa474451d34a88bb3
	@${MKDIR} "${OBJECTDIR}/_ext/8742029" 
	@${RM} ${OBJECTDIR}/_ext/8742029/display.o.d 
	@${RM} ${OBJECTDIR}/_ext/8742029/display.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O2 -fno-common -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/8742029/display.o.d" -o ${OBJECTDIR}/_ext/8742029/display.o ../display/display.c    -DXPRJ_Booteable=$(CND_CONF)    $(COMPARISON_BUILD)    
	
${OBJECTDIR}/_ext/43901184/fsio.o: ../sd/fsio.c  .generated_files/flags/Booteable/118281d8cf944d5dbdbe8eb5b9beb8c055054b1d .generated_files/flags/Booteable/2929bbcf261be56c36d51eeaa474451d34a88bb3
	@${MKDIR} "${OBJECTDIR}/_ext/43901184" 
	@${RM} ${OBJECTDIR}/_ext/43901184/fsio.o.d 
	@${RM} ${OBJECTDIR}/_ext/43901184/fsio.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O2 -fno-common -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/43901184/fsio.o.d" -o ${OBJECTDIR}/_ext/43901184/fsio.o ../sd/fsio.c    -DXPRJ_Booteable=$(CND_CONF)    $(COMPARISON_BUILD)    
	
${OBJECTDIR}/_ext/43901184/sd_spi.o: ../sd/sd_spi.c  .generated_files/flags/Booteable/ede0982666c78d9083373bea3d9d5acad92f4090 .generated_files/flags/Booteable/2929bbcf261be56c36d51eeaa474451d34a88bb3
	@${MKDIR} "${OBJECTDIR}/_ext/43901184" 
	@${RM} ${OBJECTDIR}/_ext/43901184/sd_spi.o.d 
	@${RM} ${OBJECTDIR}/_ext/43901184/sd_spi.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O2 -fno-common -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/43901184/sd_spi.o.d" -o ${OBJECTDIR}/_ext/43901184/sd_spi.o ../sd/sd_spi.c    -DXPRJ_Booteable=$(CND_CONF)    $(COMPARISON_BUILD)    
	
${OBJECTDIR}/_ext/1472/main.o: ../main.c  .generated_files/flags/Booteable/f3d1ea5680b7cdf39ec4346bf8163364e6b0a2d0 .generated_files/flags/Booteable/2929bbcf261be56c36d51eeaa474451d34a88bb3
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/main.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/main.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O2 -fno-common -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1472/main.o.d" -o ${OBJECTDIR}/_ext/1472/main.o ../main.c    -DXPRJ_Booteable=$(CND_CONF)    $(COMPARISON_BUILD)    
	
${OBJECTDIR}/_ext/1472/log.o: ../log.c  .generated_files/flags/Booteable/b608a9db2fdd9f6368e6bbde43fa6cde415c29d2 .generated_files/flags/Booteable/2929bbcf261be56c36d51eeaa474451d34a88bb3
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/log.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/log.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O2 -fno-common -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1472/log.o.d" -o ${OBJECTDIR}/_ext/1472/log.o ../log.c    -DXPRJ_Booteable=$(CND_CONF)    $(COMPARISON_BUILD)    
	
${OBJECTDIR}/_ext/1472/config.o: ../config.c  .generated_files/flags/Booteable/1c4ec332fba4298e1b5aa38b807d6bf1076929d7 .generated_files/flags/Booteable/2929bbcf261be56c36d51eeaa474451d34a88bb3
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/config.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/config.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O2 -fno-common -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1472/config.o.d" -o ${OBJECTDIR}/_ext/1472/config.o ../config.c    -DXPRJ_Booteable=$(CND_CONF)    $(COMPARISON_BUILD)    
	
${OBJECTDIR}/_ext/1472/delay.o: ../delay.c  .generated_files/flags/Booteable/ebb84d4301d361790d3a64c919987d30338d87d8 .generated_files/flags/Booteable/2929bbcf261be56c36d51eeaa474451d34a88bb3
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/delay.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/delay.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O2 -fno-common -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1472/delay.o.d" -o ${OBJECTDIR}/_ext/1472/delay.o ../delay.c    -DXPRJ_Booteable=$(CND_CONF)    $(COMPARISON_BUILD)    
	
${OBJECTDIR}/_ext/1472/boton.o: ../boton.c  .generated_files/flags/Booteable/2f6eefebf9ccea09fcd51932a952d4b5146697f5 .generated_files/flags/Booteable/2929bbcf261be56c36d51eeaa474451d34a88bb3
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/boton.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/boton.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O2 -fno-common -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1472/boton.o.d" -o ${OBJECTDIR}/_ext/1472/boton.o ../boton.c    -DXPRJ_Booteable=$(CND_CONF)    $(COMPARISON_BUILD)    
	
${OBJECTDIR}/_ext/1472/bitmap.o: ../bitmap.c  .generated_files/flags/Booteable/f2cc55d27dc70114d44e12da5d0784f7ea112287 .generated_files/flags/Booteable/2929bbcf261be56c36d51eeaa474451d34a88bb3
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/bitmap.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/bitmap.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O2 -fno-common -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1472/bitmap.o.d" -o ${OBJECTDIR}/_ext/1472/bitmap.o ../bitmap.c    -DXPRJ_Booteable=$(CND_CONF)    $(COMPARISON_BUILD)    
	
${OBJECTDIR}/_ext/1472/beep.o: ../beep.c  .generated_files/flags/Booteable/dbf4e6a6baf66c452123e45c6a06488cef617433 .generated_files/flags/Booteable/2929bbcf261be56c36d51eeaa474451d34a88bb3
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/beep.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/beep.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O2 -fno-common -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1472/beep.o.d" -o ${OBJECTDIR}/_ext/1472/beep.o ../beep.c    -DXPRJ_Booteable=$(CND_CONF)    $(COMPARISON_BUILD)    
	
${OBJECTDIR}/_ext/1472/wifi.o: ../wifi.c  .generated_files/flags/Booteable/8c3a8f57dbb2a93f9fe8a5e89e47778eee7155f0 .generated_files/flags/Booteable/2929bbcf261be56c36d51eeaa474451d34a88bb3
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/wifi.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/wifi.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O2 -fno-common -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1472/wifi.o.d" -o ${OBJECTDIR}/_ext/1472/wifi.o ../wifi.c    -DXPRJ_Booteable=$(CND_CONF)    $(COMPARISON_BUILD)    
	
${OBJECTDIR}/_ext/1472/strfunc.o: ../strfunc.c  .generated_files/flags/Booteable/a8c6ea4ad60d52186d0926379a68231713e94fb4 .generated_files/flags/Booteable/2929bbcf261be56c36d51eeaa474451d34a88bb3
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/strfunc.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/strfunc.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O2 -fno-common -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1472/strfunc.o.d" -o ${OBJECTDIR}/_ext/1472/strfunc.o ../strfunc.c    -DXPRJ_Booteable=$(CND_CONF)    $(COMPARISON_BUILD)    
	
${OBJECTDIR}/_ext/1472/http.o: ../http.c  .generated_files/flags/Booteable/147f11687285b613e88c86de2485b7ced319863d .generated_files/flags/Booteable/2929bbcf261be56c36d51eeaa474451d34a88bb3
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/http.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/http.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O2 -fno-common -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1472/http.o.d" -o ${OBJECTDIR}/_ext/1472/http.o ../http.c    -DXPRJ_Booteable=$(CND_CONF)    $(COMPARISON_BUILD)    
	
${OBJECTDIR}/_ext/1472/control.o: ../control.c  .generated_files/flags/Booteable/a567622c9a2126ea0802a942d924dccf56432169 .generated_files/flags/Booteable/2929bbcf261be56c36d51eeaa474451d34a88bb3
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/control.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/control.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O2 -fno-common -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1472/control.o.d" -o ${OBJECTDIR}/_ext/1472/control.o ../control.c    -DXPRJ_Booteable=$(CND_CONF)    $(COMPARISON_BUILD)    
	
${OBJECTDIR}/_ext/1472/rtcc.o: ../rtcc.c  .generated_files/flags/Booteable/a1664783bd35ad9b62e9fcfde7b3412cd894f91e .generated_files/flags/Booteable/2929bbcf261be56c36d51eeaa474451d34a88bb3
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/rtcc.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/rtcc.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O2 -fno-common -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1472/rtcc.o.d" -o ${OBJECTDIR}/_ext/1472/rtcc.o ../rtcc.c    -DXPRJ_Booteable=$(CND_CONF)    $(COMPARISON_BUILD)    
	
${OBJECTDIR}/_ext/1472/uart3.o: ../uart3.c  .generated_files/flags/Booteable/904f582c3bc0c76fa1e72f80300b2e4b830e0fcd .generated_files/flags/Booteable/2929bbcf261be56c36d51eeaa474451d34a88bb3
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/uart3.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/uart3.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O2 -fno-common -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1472/uart3.o.d" -o ${OBJECTDIR}/_ext/1472/uart3.o ../uart3.c    -DXPRJ_Booteable=$(CND_CONF)    $(COMPARISON_BUILD)    
	
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
	${MP_CC} $(MP_EXTRA_LD_PRE) -g   -mprocessor=$(MP_PROCESSOR_OPTION) -O2 -o ${DISTDIR}/dom32-touch.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX} ${OBJECTFILES_QUOTED_IF_SPACED}          -DXPRJ_Booteable=$(CND_CONF)    $(COMPARISON_BUILD)      -Wl,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_LD_POST)$(MP_LINKER_FILE_OPTION),--defsym=__MPLAB_DEBUG=1,--defsym=__DEBUG=1,-D=__DEBUG_D,--defsym=_min_heap_size=0,--gc-sections,--no-code-in-dinit,--no-dinit-in-serial-mem,-Map="${DISTDIR}/${PROJECTNAME}.${IMAGE_TYPE}.map",-s,--memorysummary,${DISTDIR}/memoryfile.xml 
	
else
${DISTDIR}/dom32-touch.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk   ../../../pic32mmBoot/Programa/app_p32MM0256GPM028.ld
	@${MKDIR} ${DISTDIR} 
	${MP_CC} $(MP_EXTRA_LD_PRE)  -mprocessor=$(MP_PROCESSOR_OPTION) -O2 -o ${DISTDIR}/dom32-touch.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX} ${OBJECTFILES_QUOTED_IF_SPACED}          -DXPRJ_Booteable=$(CND_CONF)    $(COMPARISON_BUILD)  -Wl,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_LD_POST)$(MP_LINKER_FILE_OPTION),--defsym=_min_heap_size=0,--gc-sections,--no-code-in-dinit,--no-dinit-in-serial-mem,-Map="${DISTDIR}/${PROJECTNAME}.${IMAGE_TYPE}.map",-s,--memorysummary,${DISTDIR}/memoryfile.xml 
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
