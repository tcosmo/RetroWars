# Thanks to Job Vranish (https://spin.atomicobject.com/2016/08/26/makefile-c-projects/)
TARGET_EXEC := RetroWars

BUILD_DIR := ./build
SRC_DIRS := ./src

LD_LIBS := -lSDL2 -lSDL2_image

SRCS := $(shell find $(SRC_DIRS) -name '*.cpp' -or -name '*.c' -or -name '*.s')
OBJS := $(SRCS:%=$(BUILD_DIR)/%.o)
DEPS := $(OBJS:.o=.d)

INC_DIRS := $(shell find $(SRC_DIRS) -type d)
INC_FLAGS := $(addprefix -I,$(INC_DIRS))

CPPFLAGS := $(INC_FLAGS) -MMD -MP -Wall -Wextra -Werror -pedantic -g

.PHONY: all
all: $(BUILD_DIR)/$(TARGET_EXEC)

# Linking
$(BUILD_DIR)/$(TARGET_EXEC): $(OBJS)
	@echo "Linking"
	@ln -sf $(shell pwd)/assets $(BUILD_DIR)
	@$(CXX) $(OBJS) -o $@ $(LDFLAGS) $(LD_LIBS)

# Compile C 
$(BUILD_DIR)/%.c.o: %.c
	@echo "Compiling $<"
	@mkdir -p $(dir $@)
	@$(CC) $(CPPFLAGS) $(CFLAGS) -c $< -o $@

# Compile C++
$(BUILD_DIR)/%.cpp.o: %.cpp
	@echo "Compiling $<"
	@mkdir -p $(dir $@)
	@$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $< -o $@

.PHONY: run
run: $(BUILD_DIR)/$(TARGET_EXEC)
	@echo "\nrunning $(TARGET_EXEC) !\n"
	@$(BUILD_DIR)/$(TARGET_EXEC)

.PHONY: clean
clean: 
	@echo "Clean up"
	@$(RM) -r $(BUILD_DIR) $(T_BUILD_DIR)

.PHONY: pretty
pretty:
	@echo "Beautifying"
	@clang-format -i $(SRC_DIRS)/*.[cpp,h]

# Include the .d makefiles. The - at the front suppresses the errors of missing
# Makefiles. Initially, all the .d files will be missing, and we don't want those
# errors to show up.
DEPS += $(T_OBJS:.o=.d)
-include $(DEPS)
