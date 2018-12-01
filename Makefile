# ------------------------------------------------------------
# Nathan Klapstein - CMPUT 379 A4
#
# It is preferred to use Cmake over Makefiles. It is not
# the stone age anymore.
#
# Usage: make // compile programs
#        make tar // create a 'tar.gz' archive of 'allFiles'
#        make clean // remove unneeded files
# ------------------------------------------------------------


# name of the executable to build
BINARY = a4tasks

RM=rm -v -rf
MKDIR = mkdir

CPPFLAGS=-g -pthread -I/sw/include/root -std=c++17 -Wall -lboost_filesystem

BUILDDIR = build
SOURCEDIR = src
HEADERDIR = src
TESTDIR = test

SOURCES := $(shell find $(SOURCEDIR) -name '*.cpp')
SOURCESFILES = $(shell find $(SOURCEDIR) -name '*')
TESTFILES = $(shell find $(TESTDIR) -name '*.txt')
OBJECTS := $(addprefix $(BUILDDIR)/,$(SOURCES:%.cpp=%.o))


.PHONY: all setup clean help tar

# compile a4tasks
all: setup $(BINARY)

$(BINARY): $(OBJECTS)
	$(CXX) $(CPPFLAGS) $(OBJECTS) -o $(BINARY)

$(BUILDDIR)/%.o: %.cpp
	$(CXX) $(CPPFLAGS) -I$(HEADERDIR) -I$(dir $<) -c $< -o $@

setup:
	$(MKDIR) -p $(BUILDDIR)/$(SOURCEDIR)


# make the submission tar file
ALLFILES = README.md LICENSE Makefile CMakeLists.txt $(SOURCESFILES) $(TESTFILES)
TARTARGET = submit

tar:
	touch $(TARTARGET).tar.gz
	mv $(TARTARGET).tar.gz  x$(TARTARGET).tar.gz
	tar -cvf $(TARTARGET).tar $(ALLFILES)
	gzip $(TARTARGET).tar


# clean up make outputs
clean:
	$(RM) $(BUILDDIR)
	$(RM) $(BINARY)
	$(RM) $(TARTARGET).tar.gz
	$(RM) x$(TARTARGET).tar.gz

distclean: clean


# Help Target
help:
	@echo "The following are some of the valid targets for this Makefile:"
	@echo "... all (the default if no target is provided)"
	@echo "... clean"
	@echo "... depend"
	@echo "... $(EXECNAME)"
	@echo "... tar (generate the submission tar)"
