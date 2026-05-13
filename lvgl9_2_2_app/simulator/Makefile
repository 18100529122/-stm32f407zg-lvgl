#
# Copyright 2025 ANYUI TEAM. All Rights Reserved.
#
# https://anyui.tech
#
ROOT_DIR := ..

LVGL_DIR := ../lvgl
GENERATED_DIR := ../generated
SDK_DIR := ../sdk

SIMULATOR_DIR := .

# Include runtime configuration for Windows only
ifeq ($(OS),Windows_NT)
include runtime.mk
endif

OBJ_DIR := ./build/obj
LIB_DIR := ./build/lib
BIN_DIR := ./build/bin

CC := gcc
CXX := g++
CFLAGS := -O0 -g0
CFLAGS += -Wno-implicit-function-declaration -Wno-unused-function -Wno-unused-variable
CFLAGS += -I$(ROOT_DIR) -I$(LVGL_DIR) -I$(SIMULATOR_DIR) -I$(GENERATED_DIR) -I$(SDK_DIR)
CFLAGS += -DSIMULATOR=1 -DLV_BUILD_TEST=0

rel_path = $(patsubst $(ROOT_DIR)/%,%,$(patsubst ./%,%,$(1)))

# Platform-specific settings
ifeq ($(OS),Windows_NT)
  FIND := find
  MKDIR := mkdir
else
  FIND := find
  MKDIR := mkdir
endif

# Common function to handle file search and collection
define find_sources
$(shell $(FIND) $(1) -type f -name '*.c')
endef

# Common function to handle directory creation
# For Windows, we use a simple mkdir command that works in both Git Bash and Windows Command Prompt
# For Unix-like systems, we use the standard mkdir -p
ifeq ($(OS),Windows_NT)
define MKDIR_P
@if not exist "$(subst /,\,$(1))" mkdir "$(subst /,\,$(1))" >nul 2>&1 || if not exist "$(subst /,\,$(1))" mkdir "$(subst /,\,$(1))" >nul 2>&1 || true
endef
else
define MKDIR_P
@mkdir -p $(1)
endef
endif

ifeq ($(OS),Windows_NT)
CFLAGS += -I$(SDL2_INC_PATH) -MMD -MP
endif

LDFLAGS := -L../lib/x86 -L$(LIB_DIR)
LDLIBS := -lSDL2 -lm -lstdc++ -llvgl_thorvg

ifeq ($(OS),Windows_NT)
LDFLAGS += -L$(SDL2_LIB_PATH)

LD_START_GROUP := -Wl,--start-group
LD_END_GROUP := -Wl,--end-group
else
LD_START_GROUP :=
LD_END_GROUP :=
endif

# Generate object files from source files
define generate_objects
$(patsubst %.c,$(OBJ_DIR)/%.o,$(call rel_path,$(call find_sources,$(1))))
endef

# Source files and object files
LVGL_SOURCES := $(call find_sources,$(LVGL_DIR))
LVGL_OBJS := $(call generate_objects,$(LVGL_DIR))

UI_SOURCES := $(call find_sources,$(GENERATED_DIR))
UI_OBJS := $(call generate_objects,$(GENERATED_DIR))

SDK_SOURCES := $(call find_sources,$(SDK_DIR))
SDK_OBJS := $(call generate_objects,$(SDK_DIR))

SIMULATOR_SOURCES := $(call find_sources,$(SIMULATOR_DIR))
SIMULATOR_OBJS := $(call generate_objects,$(SIMULATOR_DIR))

LVGL_MODULES := core display draw drivers font indev layouts libs misc osal others stdlib themes tick widgets

CORE_OBJS = $(call generate_objects,$(LVGL_DIR)/src/core)
CORE_LIB = $(LIB_DIR)/liblvgl_core.a
DISPLAY_OBJS = $(call generate_objects,$(LVGL_DIR)/src/display)
DISPLAY_LIB = $(LIB_DIR)/liblvgl_display.a
DRAW_OBJS = $(call generate_objects,$(LVGL_DIR)/src/draw)
DRAW_LIB = $(LIB_DIR)/liblvgl_draw.a
DRIVERS_OBJS = $(call generate_objects,$(LVGL_DIR)/src/drivers)
DRIVERS_LIB = $(LIB_DIR)/liblvgl_drivers.a
FONT_OBJS = $(call generate_objects,$(LVGL_DIR)/src/font)
FONT_LIB = $(LIB_DIR)/liblvgl_font.a
INDEV_OBJS = $(call generate_objects,$(LVGL_DIR)/src/indev)
INDEV_LIB = $(LIB_DIR)/liblvgl_indev.a
LAYOUTS_OBJS = $(call generate_objects,$(LVGL_DIR)/src/layouts)
LAYOUTS_LIB = $(LIB_DIR)/liblvgl_layouts.a
LIBS_OBJS = $(call generate_objects,$(LVGL_DIR)/src/libs)
LIBS_LIB = $(LIB_DIR)/liblvgl_libs.a
MISC_OBJS = $(call generate_objects,$(LVGL_DIR)/src/misc)
MISC_LIB = $(LIB_DIR)/liblvgl_misc.a
OSAL_OBJS = $(call generate_objects,$(LVGL_DIR)/src/osal)
OSAL_LIB = $(LIB_DIR)/liblvgl_osal.a
OTHERS_OBJS = $(call generate_objects,$(LVGL_DIR)/src/others)
OTHERS_LIB = $(LIB_DIR)/liblvgl_others.a
STDLIB_OBJS = $(call generate_objects,$(LVGL_DIR)/src/stdlib)
STDLIB_LIB = $(LIB_DIR)/liblvgl_stdlib.a
THEMES_OBJS = $(call generate_objects,$(LVGL_DIR)/src/themes)
THEMES_LIB = $(LIB_DIR)/liblvgl_themes.a
TICK_OBJS = $(call generate_objects,$(LVGL_DIR)/src/tick)
TICK_LIB = $(LIB_DIR)/liblvgl_tick.a
WIDGETS_OBJS = $(call generate_objects,$(LVGL_DIR)/src/widgets)
WIDGETS_LIB = $(LIB_DIR)/liblvgl_widgets.a

LVGL_LIBS := $(foreach m,$(LVGL_MODULES),$(LIB_DIR)/liblvgl_$(m).a)

LV_INIT_OBJ := $(OBJ_DIR)/lvgl/src/lv_init.o

UI_LIB := $(LIB_DIR)/libui.a
SDK_LIB := $(LIB_DIR)/libsdk.a

# Target
BIN := $(BIN_DIR)/simulator

ifeq ($(OS),Windows_NT)
all: $(LVGL_LIBS) $(BIN) cp_lib
else
all: $(LVGL_LIBS) $(BIN)
endif

$(OBJ_DIR)/lvgl/src/lv_init.o:../lvgl/src/lv_init.c
	@echo Compiling: $(abspath $<)
	@$(call MKDIR_P,$(@D))
	@$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR)/%.o: ../%.c
	@echo Compiling: $(abspath $<)
	@$(call MKDIR_P,$(@D))
	@$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR)/%.o: %.c
	@echo Compiling: $(abspath $<)
	@$(call MKDIR_P,$(@D))
	@$(CC) $(CFLAGS) -c $< -o $@

$(CORE_LIB): $(CORE_OBJS)
	@echo Linking: Core lib
	@$(call MKDIR_P,$(@D))
	@$(AR) rcs $@ $^

$(DISPLAY_LIB): $(DISPLAY_OBJS)
	@echo Linking: Display lib
	@$(call MKDIR_P,$(@D))
	@$(AR) rcs $@ $^

$(DRAW_LIB): $(DRAW_OBJS)
	@echo Linking: Draw lib
	@$(call MKDIR_P,$(@D))
	@$(AR) rcs $@ $^

$(DRIVERS_LIB): $(DRIVERS_OBJS)
	@echo Linking: Drivers lib
	@$(call MKDIR_P,$(@D))
	@$(AR) rcs $@ $^

$(FONT_LIB): $(FONT_OBJS)
	@echo Linking: Font lib
	@$(call MKDIR_P,$(@D))
	@$(AR) rcs $@ $^

$(INDEV_LIB): $(INDEV_OBJS)
	@echo Linking: Indev lib
	@$(call MKDIR_P,$(@D))
	@$(AR) rcs $@ $^

$(LAYOUTS_LIB): $(LAYOUTS_OBJS)
	@echo Linking: Layouts lib
	@$(call MKDIR_P,$(@D))
	@$(AR) rcs $@ $^

$(LIBS_LIB): $(LIBS_OBJS)
	@echo Linking: Libs lib
	@$(call MKDIR_P,$(@D))
	@$(AR) rcs $@ $^

$(MISC_LIB): $(MISC_OBJS)
	@echo Linking: Misc lib
	@$(call MKDIR_P,$(@D))
	@$(AR) rcs $@ $^

$(OSAL_LIB): $(OSAL_OBJS)
	@echo Linking: OSAL lib
	@$(call MKDIR_P,$(@D))
	@$(AR) rcs $@ $^

$(OTHERS_LIB): $(OTHERS_OBJS)
	@echo Linking: Others lib
	@$(call MKDIR_P,$(@D))
	@$(AR) rcs $@ $^

$(STDLIB_LIB): $(STDLIB_OBJS)
	@echo Linking: Stdlib lib
	@$(call MKDIR_P,$(@D))
	@$(AR) rcs $@ $^

$(THEMES_LIB): $(THEMES_OBJS)
	@echo Linking: Themes lib
	@$(call MKDIR_P,$(@D))
	@$(AR) rcs $@ $^

$(TICK_LIB): $(TICK_OBJS)
	@echo Linking: Tick lib
	@$(call MKDIR_P,$(@D))
	@$(AR) rcs $@ $^

$(WIDGETS_LIB): $(WIDGETS_OBJS)
	@echo Linking: Widgets lib
	@$(call MKDIR_P,$(@D))
	@$(AR) rcs $@ $^

$(UI_LIB): $(UI_OBJS)
	@echo Linking: UI lib
	@$(call MKDIR_P,$(@D))
	@$(AR) rcs $@ $^

$(SDK_LIB): $(SDK_OBJS)
	@echo Linking: SDK lib
	@$(call MKDIR_P,$(@D))
	@$(AR) rcs $@ $^

$(BIN): $(LVGL_LIBS) $(UI_LIB) $(SDK_LIB) $(SIMULATOR_OBJS) $(LV_INIT_OBJ)
	@echo Linking: $@
	@$(call MKDIR_P,$(@D))
	@$(CXX) -o $@ $(SIMULATOR_OBJS) $(LV_INIT_OBJ) $(LD_START_GROUP) $(LVGL_LIBS) $(UI_LIB) $(SDK_LIB) $(LD_END_GROUP) $(LDFLAGS) $(LDLIBS)

cp_lib:
	$(call MKDIR_P,$(BIN_DIR))
	-@cp $(SDL2_DLL_PATH)/SDL2.dll $(BIN_DIR)/SDL2.dll
	-@cp $(MINGW_DLL_PATH)/libstdc++-6.dll $(BIN_DIR)/libstdc++-6.dll
	-@cp $(MINGW_DLL_PATH)/libgcc_s_dw2-1.dll $(BIN_DIR)/libgcc_s_dw2-1.dll

# Run target - executes the simulator
# ifeq ($(OS),Windows_NT)
# run: $(BIN)
# 	@echo Running target: $(BIN)
# 	cmd /C "set PATH=\"$(SDL2_DLL_PATH)\";%PATH% && \"$(abspath $(BIN))\""
# else
# run: $(BIN)
# 	@echo Running target: $(BIN)
# 	@$(BIN)
# endif
run: $(BIN)
	@echo Running target: $(BIN)
	@$(BIN)

clean:
	@echo === Cleaning ===
	$(RM) -r $(OBJ_DIR) $(LIB_DIR) $(BIN_DIR)
	@echo === Cleaning done ===

info:
	@echo === Project info ===
	@echo OS: $(OS)
	@echo Project root: $(ROOT_DIR)
	@echo LVGL source dir: $(LVGL_DIR)
	@echo UI source dir: $(GENERATED_DIR)
	@echo SDK source dir: $(SDK_DIR)
	@echo SIMULATOR source dir: $(SIMULATOR_DIR)
	@echo === Build options ===
	@echo CC: $(CC)
	@echo CXX: $(CXX)
	@echo LD: $(LD)
	@echo CFLAGS: $(CFLAGS)
	@echo LDFLAGS: $(LDFLAGS)
	@echo LDLIBS: $(LDLIBS)
	@echo === Libraries ===
	@echo LVGL libs: $(LVGL_LIBS)
	@echo UI lib: $(UI_LIB)
	@echo SDK lib: $(SDK_LIB)
	@echo === Target ===
	@echo Target: $(BIN)
	@echo === End of info ===

.PHONY: all env cp_lib clean info run
