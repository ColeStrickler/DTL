# Tools
LEX = flex
YACC = bison

# Source files
LEX_FILE = lexer.l
YACC_FILE = parser.yy

# Generated files
LEX_C = lexer.yy.cc
YACC_C = parser.cc
YACC_H = frontend.hh

# Compilers
CXX_RISCV = riscv64-unknown-linux-gnu-g++
CXX_X86   = g++

# LLVM INFRA --> Change this to your LLVM/MLIR install
LLVM_CONFIG   = llvm-config
LLVM_CXXFLAGS := $(shell $(LLVM_CONFIG) --cxxflags)
LLVM_LDFLAGS  := $(shell $(LLVM_CONFIG) --ldflags)
LLVM_SYSTEM   := $(shell $(LLVM_CONFIG) --system-libs)

# Core LLVM libs
LLVM_LIBS := $(shell $(LLVM_CONFIG) --libs core support irreader)

MLIR_LIB_DIR := /home/cole/Documents/llvm-project/build/lib

MLIR_LIBS := -Wl,--start-group $(MLIR_LIB_DIR)/libMLIR*.a -Wl,--end-group
# Final flags
LLVM_INCLUDES := $(LLVM_CXXFLAGS)

LLVM_LDFLAGS_FINAL := \
    $(LLVM_LDFLAGS) \
    -L/home/cole/Documents/llvm-project/build/lib

LLVM_LIBS_FINAL := \
    $(MLIR_LIBS) \
    $(LLVM_LIBS) \
    $(LLVM_SYSTEM)


LLVM_DIR := /home/cole/Documents/llvm-project/llvm/include
MLIR_DIR := /home/cole/Documents/llvm-project/mlir/include
BUILD_DIR := /home/cole/Documents/llvm-project/build/include
TOOLS_INC := /home/cole/Documents/llvm-project/build/tools/mlir/include
LLVM_INCLUDES = -I$(LLVM_DIR) -I$(MLIR_DIR) -I$(BUILD_DIR) -I$(TOOLS_INC)



CFLAGS_COMMON = -O2 -fno-math-errno -fstrict-aliasing -g -std=c++17 -I./
CFLAGS_RISCV  = $(CFLAGS_COMMON)
CFLAGS_X86    = $(CFLAGS_COMMON) $(LLVM_INCLUDES)
CFLAGS_LLVM   = $(CFLAGS_COMMON) 


# All C++ source files in current directory (excluding main.cpp)
CPP_SRCS := $(filter-out main.cpp, $(wildcard *.cpp))
OPT_SRCS := $(wildcard optimizations/*.cpp)
MLIR_SRCS := $(wildcard lowering/*.cpp)
CPP_SRCS += $(OPT_SRCS)
CPP_SRCS += $(MLIR_SRCS)

# Object files for each build
OBJ_RISCV = parser.o lexer.o $(CPP_SRCS:.cpp=.o)
OBJ_X86   = parser.x86.o lexer.x86.o $(CPP_SRCS:.cpp=.x86.o) main.x86.o

# Outputs
LIB_NAME = libdtl.a
DTL_COMPILER = dtlcompiler

# Default target: build both
all: lib dtlcompiler


run: dtlcompiler
	chmod +x ./dtlcompiler
	./dtlcompiler

# ============================================================
# === RISC-V library build (via "make lib") ==================
# ============================================================
lib: $(LIB_NAME)

$(LIB_NAME): $(OBJ_RISCV)
	ar rcs $@ $^

parser.o: parser.cc frontend.hh
	$(CXX_RISCV) $(CFLAGS_RISCV) -MMD -MP -c $< -o $@

lexer.o: lexer.yy.cc
	$(CXX_RISCV) $(CFLAGS_RISCV) -Wno-sign-compare -Wno-sign-conversion \
	    -Wno-old-style-cast -Wno-switch-default -Wno-strict-overflow \
	    -c $< -o $@

%.o: %.cpp
	$(CXX_RISCV) $(CFLAGS_RISCV) -MMD -MP -c $< -o $@

# ============================================================
# === x86 dtlcompiler build (via "make dtlcompiler") =========
# ============================================================
dtlcompiler: $(OBJ_X86)
	$(CXX_X86) $(CFLAGS_X86) -o $@ $(OBJ_X86) $(LLVM_LDFLAGS_FINAL) $(LLVM_LIBS_FINAL)

parser.x86.o: parser.cc frontend.hh
	$(CXX_X86) $(CFLAGS_X86) -MMD -MP -c $< -o $@

lexer.x86.o: lexer.yy.cc
	$(CXX_X86) $(CFLAGS_X86) -Wno-sign-compare -Wno-sign-conversion \
	    -Wno-old-style-cast -Wno-switch-default -Wno-strict-overflow \
	    -c $< -o $@

%.x86.o: %.cpp
	$(CXX_X86) $(CFLAGS_X86) -MMD -MP -c $< -o $@

main.x86.o: main.cpp
	$(CXX_X86) $(CFLAGS_X86) -c $< -o $@

# ============================================================
# === Lex & Yacc rules =======================================
# ============================================================
parser.cc frontend.hh: parser.yy
	$(YACC) -Werror -Wcounterexamples --graph=parser.dot \
	        --defines=frontend.hh -v $<

lexer.yy.cc: lexer.l
	$(LEX) --outfile=lexer.yy.cc $<

# ============================================================
# === Clean ==================================================
# ============================================================
clean:
	rm -rf *.o *.x86.o *.d *.output *.cc *.hh parser.dot parser.png \
	       $(LIB_NAME) $(DTL_COMPILER) lexer.yy.cc frontend.hh 
	