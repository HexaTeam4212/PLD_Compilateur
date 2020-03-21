OUTPUT=output
GENERATED=antlr4-generated
GRAMMAR=ifcc.g4

# Directories of the docker image
ANTLR4_BINDIR=/usr/bin
ANTLR4_INCDIR=/usr/include/antlr4-runtime
ANTLR4_LIBDIR=/usr/lib/x86_64-linux-gnu

AST = Affectation.cpp Declaration.cpp ExprConstante.cpp Expression.cpp ExprVariable.cpp Function.cpp Instruction.cpp Program.cpp ReturnInstr.cpp
IR = BasicBlock.cpp CFG.cpp IRInstr.cpp IRVariable.cpp

SOURCES = $(AST) $(IR) visitor.cpp main.cpp
OBJECTS = $(SOURCES:.cpp=.o)

CC=clang++
CCARGS=-g -c -I $(ANTLR4_INCDIR) -I $(GENERATED) -std=c++11 -Wno-defaulted-function-deleted -Wno-unknown-warning-option
LDARGS=-g

all: ifcc

ifcc: dirs antlr $(OBJECTS)
	$(CC) $(CCARGS) $(GENERATED)/ifccBaseVisitor.cpp -o $(OUTPUT)/ifccBaseVisitor.o 
	$(CC) $(CCARGS) $(GENERATED)/ifccLexer.cpp -o $(OUTPUT)/ifccLexer.o 
	$(CC) $(CCARGS) $(GENERATED)/ifccVisitor.cpp -o $(OUTPUT)/ifccVisitor.o 
	$(CC) $(CCARGS) $(GENERATED)/ifccParser.cpp -o $(OUTPUT)/ifccParser.o
	$(CC) $(LDARGS) $(OUTPUT)/ifccBaseVisitor.o $(OUTPUT)/ifccLexer.o $(OUTPUT)/ifccVisitor.o $(OUTPUT)/ifccParser.o $(addprefix $(OUTPUT)/,$(OBJECTS)) $(ANTLR4_LIBDIR)/libantlr4-runtime.a -o ifcc

%.o : %.cpp
	$(CC) $(CCARGS) $< -o $(OUTPUT)/$@

antlr: $(GRAMMAR)
	$(ANTLR4_BINDIR)/antlr4 -visitor -no-listener -Dlanguage=Cpp -o $(GENERATED) $(GRAMMAR)

dirs:
	mkdir -p $(OUTPUT) 
	mkdir -p $(GENERATED) 

clean:
	rm -rf $(OUTPUT)
	rm -rf $(GENERATED)
