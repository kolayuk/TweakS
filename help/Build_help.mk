do_nothing :
	@rem do_nothing

# build the help from the MAKMAKE step so the header file generated
# will be found by cpp.exe when calculating the dependency information
# in the mmp makefiles.

MAKMAKE : TweakS.h01 TweakS.h16 TweakS.h26
TweakS.h01 : TweakS_01.xml TweakS_01.cshlp Custom.xml
TweakS.h16 : TweakS_16.xml TweakS_16.cshlp Custom.xml
TweakS.h26 : TweakS_26.xml TweakS_26.cshlp Custom.xml
	cshlpcmp TweakS_16.cshlp
	cshlpcmp TweakS_01.cshlp
	cshlpcmp TweakS_26.cshlp
ifeq (WINSCW,$(findstring WINSCW, $(PLATFORM)))
	md $(EPOCROOT)epoc32\$(PLATFORM)\c\resource\help
	copy TweakS.h01 $(EPOCROOT)epoc32\$(PLATFORM)\c\resource\help
endif

BLD : do_nothing

CLEAN :
	del TweakS.hlp
	del TweakS.hlp.hrh

LIB : do_nothing

CLEANLIB : do_nothing

RESOURCE : do_nothing
		
FREEZE : do_nothing

SAVESPACE : do_nothing

RELEASABLES :
	@echo TweakS.hlp

FINAL : do_nothing
