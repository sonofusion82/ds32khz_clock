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
ifeq "$(wildcard nbproject/Makefile-local-PIC16F876A_SDCC.mk)" "nbproject/Makefile-local-PIC16F876A_SDCC.mk"
include nbproject/Makefile-local-PIC16F876A_SDCC.mk
endif
endif

# Environment
MKDIR=mkdir -p
RM=rm -f 
MV=mv 
CP=cp 

# Macros
CND_CONF=PIC16F876A_SDCC
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
IMAGE_TYPE=debug
OUTPUT_SUFFIX=cof
DEBUGGABLE_SUFFIX=cof
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/Clock.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
else
IMAGE_TYPE=production
OUTPUT_SUFFIX=hex
DEBUGGABLE_SUFFIX=cof
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/Clock.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
endif

# Object Directory
OBJECTDIR=build/${CND_CONF}/${IMAGE_TYPE}

# Distribution Directory
DISTDIR=dist/${CND_CONF}/${IMAGE_TYPE}

# Source Files Quoted if spaced
SOURCEFILES_QUOTED_IF_SPACED=main.c time_update.c button_update.c

# Object Files Quoted if spaced
OBJECTFILES_QUOTED_IF_SPACED=${OBJECTDIR}/main.o ${OBJECTDIR}/time_update.o ${OBJECTDIR}/button_update.o
POSSIBLE_DEPFILES=${OBJECTDIR}/main.o.d ${OBJECTDIR}/time_update.o.d ${OBJECTDIR}/button_update.o.d

# Object Files
OBJECTFILES=${OBJECTDIR}/main.o ${OBJECTDIR}/time_update.o ${OBJECTDIR}/button_update.o

# Source Files
SOURCEFILES=main.c time_update.c button_update.c


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
Device=PIC16F876A
ProjectDir=/home/ymchen/Electronics/MPLABXProjects/Clock.X
ConfName=PIC16F876A_SDCC
ImagePath=dist/PIC16F876A_SDCC/${IMAGE_TYPE}/Clock.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
ImageDir=dist/PIC16F876A_SDCC/${IMAGE_TYPE}
ImageName=Clock.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
IsDebug="true"
else
IsDebug="false"
endif

.build-conf:  .pre ${BUILD_SUBPROJECTS}
ifneq ($(INFORMATION_MESSAGE), )
	@echo $(INFORMATION_MESSAGE)
endif
	${MAKE}  -f nbproject/Makefile-PIC16F876A_SDCC.mk dist/${CND_CONF}/${IMAGE_TYPE}/Clock.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}

# ------------------------------------------------------------------------------------
# Rules for buildStep: compile
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${OBJECTDIR}/main.o: main.c  nbproject/Makefile-${CND_CONF}.mk
	${MKDIR} ${OBJECTDIR} 
	${RM} ${OBJECTDIR}/main.o 
	${MP_CC} --debug-ralloc --use-non-free --no-pcode-opt --pstack-model=small --opt-code-speed -c -mpic14 -p16f876a main.c  -o${OBJECTDIR}/main.o
	
${OBJECTDIR}/time_update.o: time_update.c  nbproject/Makefile-${CND_CONF}.mk
	${MKDIR} ${OBJECTDIR} 
	${RM} ${OBJECTDIR}/time_update.o 
	${MP_CC} --debug-ralloc --use-non-free --no-pcode-opt --pstack-model=small --opt-code-speed -c -mpic14 -p16f876a time_update.c  -o${OBJECTDIR}/time_update.o
	
${OBJECTDIR}/button_update.o: button_update.c  nbproject/Makefile-${CND_CONF}.mk
	${MKDIR} ${OBJECTDIR} 
	${RM} ${OBJECTDIR}/button_update.o 
	${MP_CC} --debug-ralloc --use-non-free --no-pcode-opt --pstack-model=small --opt-code-speed -c -mpic14 -p16f876a button_update.c  -o${OBJECTDIR}/button_update.o
	
else
${OBJECTDIR}/main.o: main.c  nbproject/Makefile-${CND_CONF}.mk
	${MKDIR} ${OBJECTDIR} 
	${RM} ${OBJECTDIR}/main.o 
	${MP_CC} --debug-ralloc --use-non-free --no-pcode-opt --pstack-model=small --opt-code-speed -c -mpic14 -p16f876a main.c  -o${OBJECTDIR}/main.o
	
${OBJECTDIR}/time_update.o: time_update.c  nbproject/Makefile-${CND_CONF}.mk
	${MKDIR} ${OBJECTDIR} 
	${RM} ${OBJECTDIR}/time_update.o 
	${MP_CC} --debug-ralloc --use-non-free --no-pcode-opt --pstack-model=small --opt-code-speed -c -mpic14 -p16f876a time_update.c  -o${OBJECTDIR}/time_update.o
	
${OBJECTDIR}/button_update.o: button_update.c  nbproject/Makefile-${CND_CONF}.mk
	${MKDIR} ${OBJECTDIR} 
	${RM} ${OBJECTDIR}/button_update.o 
	${MP_CC} --debug-ralloc --use-non-free --no-pcode-opt --pstack-model=small --opt-code-speed -c -mpic14 -p16f876a button_update.c  -o${OBJECTDIR}/button_update.o
	
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: link
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
dist/${CND_CONF}/${IMAGE_TYPE}/Clock.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk    
	${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CC}  --debug-ralloc -Wl-c -Wl-m --use-non-free --no-pcode-opt --pstack-model=small --opt-code-speed -mpic14 -p16f876a ${OBJECTFILES}  -odist/${CND_CONF}/${IMAGE_TYPE}/Clock.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX} 
else
dist/${CND_CONF}/${IMAGE_TYPE}/Clock.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk   
	${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CC}  --debug-ralloc -Wl-c -Wl-m --use-non-free --no-pcode-opt --pstack-model=small --opt-code-speed -mpic14 -p16f876a ${OBJECTFILES}  -odist/${CND_CONF}/${IMAGE_TYPE}/Clock.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX} 
endif

.pre:
	@echo "--------------------------------------"
	@echo "User defined pre-build step: [./generate_current_timestamp.py]"
	@./generate_current_timestamp.py
	@echo "--------------------------------------"

# Subprojects
.build-subprojects:


# Subprojects
.clean-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r build/PIC16F876A_SDCC
	${RM} -r dist/PIC16F876A_SDCC

# Enable dependency checking
.dep.inc: .depcheck-impl

DEPFILES=$(shell "${PATH_TO_IDE_BIN}"mplabwildcard ${POSSIBLE_DEPFILES})
ifneq (${DEPFILES},)
include ${DEPFILES}
endif
