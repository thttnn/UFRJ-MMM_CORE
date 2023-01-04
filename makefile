# Model compilation options
# LSD options
TARGET=LSD
FUN=fun_MMM_CORE

# Additional model files
FUN_EXTRA= mmm_core_time_step.h mmm_core_analysis.h mmm_core_macro.h mmm_core_macro_sfc.h mmm_core_classes.h mmm_core_external_sector.h mmm_core_government.h  mmm_core_sector_aggregates.h mmm_core_sector_demand.h mmm_core_entry_exit.h mmm_core_firm_capital.h mmm_core_firm_finance.h mmm_core_firm_investment.h mmm_core_firm_price.h mmm_core_firm_production.h mmm_core_firm_profit.h mmm_core_firm_rnd.h mmm_core_firm_sales.h mmm_core_firm_inputs.h mmm_core_capital_goods.h mmm_core_sector_analysis.h  mmm_core_calibration.h

# Compiler options
SWITCH_CC=-O0 -ggdb3
SWITCH_CC_LNK=

# System compilation options
# LSD options
LSDROOT=C:/Users/thttn/LSD
SRC=src

# Libraries options
TCL_VERSION=86
PATH_TCLTK_HEADER=$(LSDROOT)/gnu/include
PATH_TCLTK_LIB=$(LSDROOT)/gnu/lib
TCLTK_LIB=-ltcl$(TCL_VERSION) -ltk$(TCL_VERSION)
PATH_HEADER=$(LSDROOT)/gnu/include
PATH_LIB=$(LSDROOT)/gnu/lib
LIB=-lz

# Compiler options
WRC=windres
CC=g++
GLOBAL_CC=-march=native -w
SSWITCH_CC=-mthreads -mwindows -O3

# Body of makefile (from makefile_windows.txt)
# specify where are the sources of LSD
SRC_DIR=$(LSDROOT)/$(SRC)/

# location of tcl/tk and other headers
INCLUDE=-I$(LSDROOT)/$(SRC) -I$(PATH_TCLTK_HEADER) -I$(PATH_HEADER)

# OS command to delete files
RM=rm -f

# link executable
$(TARGET).exe: $(FUN).o $(SRC_DIR)common.o $(SRC_DIR)lsdmain.o $(SRC_DIR)analysis.o \
$(SRC_DIR)debug.o $(SRC_DIR)draw.o $(SRC_DIR)edit.o $(SRC_DIR)edit_dat.o \
$(SRC_DIR)file.o $(SRC_DIR)interf.o $(SRC_DIR)nets.o $(SRC_DIR)object.o \
$(SRC_DIR)report.o $(SRC_DIR)runtime.o $(SRC_DIR)set_all.o $(SRC_DIR)show_eq.o \
$(SRC_DIR)util.o $(SRC_DIR)variab.o $(SRC_DIR)lsd_manifest.o
	$(CC) $(GLOBAL_CC) $(SWITCH_CC) $(FUN).o $(SRC_DIR)common.o $(SRC_DIR)lsdmain.o \
	$(SRC_DIR)analysis.o $(SRC_DIR)debug.o $(SRC_DIR)draw.o $(SRC_DIR)edit.o \
	$(SRC_DIR)edit_dat.o $(SRC_DIR)file.o $(SRC_DIR)interf.o $(SRC_DIR)nets.o \
	$(SRC_DIR)object.o $(SRC_DIR)report.o $(SRC_DIR)runtime.o $(SRC_DIR)set_all.o \
	$(SRC_DIR)show_eq.o $(SRC_DIR)util.o $(SRC_DIR)variab.o $(SRC_DIR)lsd_manifest.o \
	$(SWITCH_CC_LNK) -L$(PATH_TCLTK_LIB) $(TCLTK_LIB) -L$(PATH_LIB) $(LIB) -o $(TARGET)

# compile modules
$(FUN).o: $(FUN).cpp $(FUN_EXTRA) model_options.txt $(SRC_DIR)check.h \
$(SRC_DIR)decl.h.gch $(SRC_DIR)fun_head.h $(SRC_DIR)fun_head_fast.h
	$(CC) $(GLOBAL_CC) $(SWITCH_CC) $(INCLUDE) -c $(FUN).cpp -o $(FUN).o
	
$(SRC_DIR)common.o: $(SRC_DIR)common.cpp $(SRC_DIR)common.h $(SRC_DIR)system_options.txt
	$(CC) $(GLOBAL_CC) $(SSWITCH_CC) $(INCLUDE) -c $(SRC_DIR)common.cpp -o $(SRC_DIR)common.o

$(SRC_DIR)lsdmain.o: $(SRC_DIR)lsdmain.cpp $(SRC_DIR)decl.h.gch
	$(CC) $(GLOBAL_CC) $(SSWITCH_CC) $(INCLUDE) -c $(SRC_DIR)lsdmain.cpp -o $(SRC_DIR)lsdmain.o

$(SRC_DIR)analysis.o: $(SRC_DIR)analysis.cpp $(SRC_DIR)decl.h.gch
	$(CC) $(GLOBAL_CC) $(SSWITCH_CC) $(INCLUDE) -c $(SRC_DIR)analysis.cpp -o $(SRC_DIR)analysis.o

$(SRC_DIR)debug.o: $(SRC_DIR)debug.cpp $(SRC_DIR)decl.h.gch
	$(CC) $(GLOBAL_CC) $(SSWITCH_CC) $(INCLUDE) -c $(SRC_DIR)debug.cpp -o $(SRC_DIR)debug.o

$(SRC_DIR)draw.o: $(SRC_DIR)draw.cpp $(SRC_DIR)decl.h.gch
	$(CC) $(GLOBAL_CC) $(SSWITCH_CC) $(INCLUDE) -c $(SRC_DIR)draw.cpp -o $(SRC_DIR)draw.o

$(SRC_DIR)edit.o: $(SRC_DIR)edit.cpp $(SRC_DIR)decl.h.gch
	$(CC) $(GLOBAL_CC) $(SSWITCH_CC) $(INCLUDE) -c $(SRC_DIR)edit.cpp -o $(SRC_DIR)edit.o

$(SRC_DIR)edit_dat.o: $(SRC_DIR)edit_dat.cpp $(SRC_DIR)decl.h.gch
	$(CC) $(GLOBAL_CC) $(SSWITCH_CC) $(INCLUDE) -c $(SRC_DIR)edit_dat.cpp -o $(SRC_DIR)edit_dat.o

$(SRC_DIR)file.o: $(SRC_DIR)file.cpp $(SRC_DIR)decl.h.gch
	$(CC) $(GLOBAL_CC) $(SSWITCH_CC) $(INCLUDE) -c $(SRC_DIR)file.cpp -o $(SRC_DIR)file.o

$(SRC_DIR)interf.o: $(SRC_DIR)interf.cpp $(SRC_DIR)decl.h.gch
	$(CC) $(GLOBAL_CC) $(SSWITCH_CC) $(INCLUDE) -c $(SRC_DIR)interf.cpp -o $(SRC_DIR)interf.o

$(SRC_DIR)nets.o: $(SRC_DIR)nets.cpp $(SRC_DIR)decl.h.gch
	$(CC) $(GLOBAL_CC) $(SSWITCH_CC) $(INCLUDE) -c $(SRC_DIR)nets.cpp -o $(SRC_DIR)nets.o

$(SRC_DIR)object.o: $(SRC_DIR)object.cpp $(SRC_DIR)decl.h.gch
	$(CC) $(GLOBAL_CC) $(SSWITCH_CC) $(INCLUDE) -c $(SRC_DIR)object.cpp -o $(SRC_DIR)object.o

$(SRC_DIR)report.o: $(SRC_DIR)report.cpp $(SRC_DIR)decl.h.gch
	$(CC) $(GLOBAL_CC) $(SSWITCH_CC) $(INCLUDE) -c $(SRC_DIR)report.cpp -o $(SRC_DIR)report.o

$(SRC_DIR)runtime.o: $(SRC_DIR)runtime.cpp $(SRC_DIR)decl.h.gch
	$(CC) $(GLOBAL_CC) $(SSWITCH_CC) $(INCLUDE) -c $(SRC_DIR)runtime.cpp -o $(SRC_DIR)runtime.o

$(SRC_DIR)set_all.o: $(SRC_DIR)set_all.cpp $(SRC_DIR)nolh.h $(SRC_DIR)decl.h.gch
	$(CC) $(GLOBAL_CC) $(SSWITCH_CC) $(INCLUDE) -c $(SRC_DIR)set_all.cpp -o $(SRC_DIR)set_all.o

$(SRC_DIR)show_eq.o: $(SRC_DIR)show_eq.cpp $(SRC_DIR)decl.h.gch
	$(CC) $(GLOBAL_CC) $(SSWITCH_CC) $(INCLUDE) -c $(SRC_DIR)show_eq.cpp -o $(SRC_DIR)show_eq.o

$(SRC_DIR)util.o: $(SRC_DIR)util.cpp $(SRC_DIR)decl.h.gch
	$(CC) $(GLOBAL_CC) $(SSWITCH_CC) $(INCLUDE) -c $(SRC_DIR)util.cpp -o $(SRC_DIR)util.o

$(SRC_DIR)variab.o: $(SRC_DIR)variab.cpp $(SRC_DIR)decl.h.gch
	$(CC) $(GLOBAL_CC) $(SSWITCH_CC) $(INCLUDE) -c $(SRC_DIR)variab.cpp -o $(SRC_DIR)variab.o

$(SRC_DIR)lsd_manifest.o: $(SRC_DIR)lsd_manifest.rc $(SRC_DIR)lsd.exe.manifest
	$(WRC) -i $(SRC_DIR)lsd_manifest.rc -o $(SRC_DIR)lsd_manifest.o $(INCLUDE)

$(SRC_DIR)decl.h.gch: $(SRC_DIR)decl.h $(SRC_DIR)common.h $(SRC_DIR)system_options.txt
	$(CC) $(GLOBAL_CC) $(SSWITCH_CC) $(INCLUDE) -c $(SRC_DIR)decl.h -o $(SRC_DIR)decl.h.gch

# remove compiled files
clean:
	$(RM) $(SRC_DIR)*.o $(SRC_DIR)*.gch $(FUN).o $(TARGET).exe
