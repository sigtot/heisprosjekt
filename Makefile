TARGET   = heis

CC       = gcc
# compiling flags here
CFLAGS   = -std=c99 -Wall -I.

LINKER   = gcc
# linking flags here
LFLAGS   = -Wall -I. -lcomedi -lm -lcurl

# change these to proper directories where each file should be
SRCDIR   = src
OBJDIR   = obj
BINDIR   = bin
DRIVERDIR 	= $(SRCDIR)/driver
CONTROLLERDIR 	= $(SRCDIR)/controller
TESTSDIR	= $(SRCDIR)/tests

SOURCES 	:= $(wildcard $(SRCDIR)/*.c) $(wildcard $(DRIVERDIR)/*.c) $(wildcard $(CONTROLLERDIR)/*.c) $(wildcard $(TESTSDIR)/*.c)
INCLUDES	:= $(wildcard $(SRCDIR)/*.h)
OBJECTS		:= $(SOURCES:$(SRCDIR)/%.c=$(OBJDIR)/%.o)
rm			= rm -rf
mkdir		= mkdir -p


$(BINDIR)/$(TARGET): $(OBJECTS)
	@$(mkdir) $(BINDIR)
	@$(LINKER) $(OBJECTS) $(LFLAGS) -o $@
	@echo "Linking complete!"

$(OBJECTS): $(OBJDIR)/%.o : $(SRCDIR)/%.c
	@$(mkdir) $(BINDIR) $(@D)
	@$(CC) $(CFLAGS) -c $< -o $@
	@echo "Compiled "$<" successfully!"

.PHONY: clean
clean:
	@$(rm) $(OBJDIR) $(BINDIR)
	@echo "Cleanup complete!"

.PHONY: rebuild
rebuild: clean $(BINDIR)/$(TARGET)
